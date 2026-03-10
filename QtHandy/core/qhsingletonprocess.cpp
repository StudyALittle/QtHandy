#include "qhsingletonprocess.h"
#include "qhsingletonprocess_p.h"
#include <QTimer>
#include "util/qhutil.h"

static QhSingletonProcess *g_singletonProcess = nullptr;

QhSingletonProcess *QhSingletonProcess::instance()
{
    if (!g_singletonProcess)
        g_singletonProcess = new QhSingletonProcess;
    return g_singletonProcess;
}

void QhSingletonProcess::delInstance()
{
    if (g_singletonProcess)
        delete g_singletonProcess;
    g_singletonProcess = nullptr;
}

QhSingletonProcess::QhSingletonProcess():
    d(new QhSingletonProcessPrivate(this))
{
    connect(d.get(), &QhSingletonProcessPrivate::recvMessage,
            this, &QhSingletonProcess::recvMessage);
}

QhSingletonProcess::~QhSingletonProcess()
{
    unbind();
}

bool QhSingletonProcess::bind(bool bUserIsolation, const QString &name, EMsgType type, const QString &msg)
{
    return d->start(bUserIsolation, name, type, msg);
}

bool QhSingletonProcess::bind(const QString &name, EMsgType type, const QString &msg)
{
    return d->start(name, type, msg);
}

void QhSingletonProcess::unbind()
{
    d->stop();
}

////////////////////////////// QhSingletonProcessPrivate //////////////////////////////
QhSingletonProcessPrivate::QhSingletonProcessPrivate(QhSingletonProcess *q):
    q_ptr(q)
{
    m_server = new QhSingletonProcessServer(this);
    m_client = new QhSingletonProcessClient(this);

    connect(m_server, &QhSingletonProcessServer::recvMessage,
            this, &QhSingletonProcessPrivate::recvMessage);
}

QhSingletonProcessPrivate::~QhSingletonProcessPrivate()
{
    stop();
}

bool QhSingletonProcessPrivate::start(bool bUserIsolation, const QString &name, int type, const QString &msg)
{
    m_bUserIsolation = bUserIsolation;
    return start(name, type, msg);
}

bool QhSingletonProcessPrivate::start(const QString &name, int type, const QString &msg)
{
    // 服务标志
    m_serveName = QString("SingletonProcess_%1").arg(name);
    if (m_bUserIsolation) {
        m_serveName.append("_");
        m_serveName.append(QhUtil::systemLoginUserName());
    }
    // 共享内存
    if (!m_shareMenory)
        m_shareMenory = new QSharedMemory(m_serveName);
    else
        m_shareMenory->setKey(m_serveName);

    // 共享内存被占用（进程在运行中）
    if (!m_shareMenory->create(42)
            && m_shareMenory->error() == QSharedMemory::AlreadyExists) {
        // 判断进程是否正常
        bool bCon = m_client->sendMessageToServer(m_serveName, type, msg);
        if (!bCon) {
            // 睡眠一会，保证同时启动两个应用时，上一个已经启动成功
            QEventLoop eloop;
            QTimer::singleShot(300, [&eloop]() { eloop.exit(); });
            eloop.exec();

            // 重新尝试连接
            bCon = m_client->sendMessageToServer(m_serveName, type, msg);
        }

        if (!bCon) { // 连接失败 (已经启动的程序异常)
            // 附加到共享内存
            m_shareMenory->attach();
            // 移除之前的服务
            if (QLocalServer::removeServer(m_serveName)) {
                // 启动服务
                return m_server->startServer(m_serveName);
            } else {
                m_shareMenory->deleteLater();
                m_shareMenory = nullptr;
                return false;
            }
        } else {
            // 同样的程序还在运行，不能启动当前实例
            m_shareMenory->deleteLater();
            m_shareMenory = nullptr;
            return false;
        }
    } else {
        // 未存在相同的进程
        // 移除之前的服务
        QLocalServer::removeServer(m_serveName);
        return m_server->startServer(m_serveName);
    }

    return true;
}

void QhSingletonProcessPrivate::stop()
{
    if (m_shareMenory) {
        m_shareMenory->detach();
        delete m_shareMenory;
    }
    m_shareMenory = nullptr;

    if (m_server) {
        m_server->stopServer();
        delete m_server;
    }
    if (m_client) {
        m_client->disconnectFromServer();
        delete m_client;
    }
    m_client = nullptr;
    m_server = nullptr;
}

////////////////////////////// QhSingletonProcessServer //////////////////////////////
QhSingletonProcessServer::QhSingletonProcessServer(QObject *parent):
    QhSingletonProcessMessage(parent)
{

}

QhSingletonProcessServer::~QhSingletonProcessServer()
{
    stopServer();
    if (m_server) {
        delete m_server;
        m_server = nullptr;
    }
}

bool QhSingletonProcessServer::startServer(QString serveNam)
{
    m_serveName = serveNam;
    if (!m_server) {
        m_server = new QLocalServer;
        connect(m_server, &QLocalServer::newConnection,
                this, &QhSingletonProcessServer::onNewConnection);
    }

    if (m_server->listen(m_serveName)) {
        // 监听成功
        return true;
    } else {
        // 监听失败（或许服务已经存在）
        qWarning() << "SingletonProcess server listen error!";
        return false;
    }
}

void QhSingletonProcessServer::stopServer()
{
    if (m_server)
        m_server->close();
}

void QhSingletonProcessServer::onNewConnection()
{
    auto *socket = m_server->nextPendingConnection();
    if (!socket)
        return;

    // 接收信息
    connect(socket, &QLocalSocket::readyRead,
            this, &QhSingletonProcessServer::onReadyRead);
    // 断开链接释放资源
    connect(socket, &QLocalSocket::disconnected, [=]() {
        socket->close();
        socket->deleteLater();
    });
    // 链接错误释放资源
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    connect(socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),
            [=](QLocalSocket::LocalSocketError socketError) {
#else
    connect(socket, &QLocalSocket::errorOccurred, [=](QLocalSocket::LocalSocketError socketError) {
#endif
        socket->close();
        socket->deleteLater();
    });

    // 回复消息给客户端
    auto ackMsg = packMsg(m_serveName, QhSingletonProcess::EMsgAck);
    socket->write(ackMsg);
    socket->flush();
}

void QhSingletonProcessServer::onReadyRead()
{
    auto *socket = static_cast<QLocalSocket*>(sender());
    if (!socket)
        return;

    QByteArray data = socket->readAll();
    auto msg = unpackMsg(m_serveName, data);

    // 通信一次就关闭释放资源（短链接）
    socket->close();
    socket->deleteLater();

    if (msg.type == QhSingletonProcess::EMsgError)
        return;

    emit recvMessage(msg.type, msg.data);
}

////////////////////////////// QhSingletonProcessClient //////////////////////////////
QhSingletonProcessClient::QhSingletonProcessClient(QObject *parent):
    QhSingletonProcessMessage(parent)
{

}

QhSingletonProcessClient::~QhSingletonProcessClient()
{
    disconnectFromServer();
    if (m_client) {
        delete m_client;
        m_client = nullptr;
    }
}

bool QhSingletonProcessClient::sendMessageToServer(QString serveName, int type, const QString &data)
{
    m_serveName = serveName;
    m_bRecvAckMsg = false;
    m_sendMsg.type = type;
    m_sendMsg.data = data;

    // 连接服务端
    if (!connectToServer())
        return false;

    // 超时处理
    QTimer::singleShot(2000, this, [=]() {
        m_eloop.exit();
    });
    m_eloop.exec();

    disconnectFromServer();
    return m_bRecvAckMsg;
}

bool QhSingletonProcessClient::connectToServer()
{
    // 开启客户端，通知已经打开的程序打开界面
    if (!m_client) {
        m_client = new QLocalSocket;
        connect(m_client, &QLocalSocket::readyRead,
                this, &QhSingletonProcessClient::onReadyRead);
    }

    m_client->connectToServer(m_serveName);
    if (m_client->waitForConnected(6000)) {
        qDebug() << "SingletonProcess connect server process success!";
        return true;
    } else {
        // 连接失败
        qWarning() << "SingletonProcess connect server process error!";
        return false;
    }
}

void QhSingletonProcessClient::disconnectFromServer()
{
    if (m_client) {
        m_client->disconnectFromServer();
        m_client->close();
    }
}

void QhSingletonProcessClient::onReadyRead()
{
    QByteArray data = m_client->readAll();
    auto msg = unpackMsg(m_serveName, data);
    if (msg.type != QhSingletonProcess::EMsgAck)
        return;

    // 收到确认信息，发送消息给服务端
    auto sendMsg = packMsg(m_serveName, m_sendMsg.type, m_sendMsg.data);
    auto ret = m_client->write(sendMsg);
    m_client->flush();

    m_bRecvAckMsg = (ret > 0);
    m_eloop.exit();
}

////////////////////////////// QhSingletonProcessMessage //////////////////////////////
QByteArray QhSingletonProcessMessage::packMsg(const QString &serveName, int type, const QString &data)
{
    QString strFlag;
    switch (type) {
    case QhSingletonProcess::EMsgError:     { return QByteArray(); }
    case QhSingletonProcess::EMsgAck:       { strFlag = "ACK"; break; };
    case QhSingletonProcess::EMsgActivated: { strFlag = "ACTIVATED"; break; }
    case QhSingletonProcess::EMsgCustom:    { strFlag = "CUSTOM"; break; }
    }

    return QString("%1#MSG:%2#%3")
            .arg(serveName).arg(strFlag).arg(data)
            .toLocal8Bit();
}

QhSingletonProcessMessage::MsgItem QhSingletonProcessMessage::unpackMsg(const QString &serveName, const QByteArray &_msg)
{
    MsgItem msgItem;
    msgItem.type = QhSingletonProcess::EMsgError;

    QString msg = QString::fromLocal8Bit(_msg);

    auto strs = msg.split("#", QString::KeepEmptyParts);
    if (strs.size() < 2
            || strs.at(0) != serveName
            || !strs.at(1).startsWith("MSG:"))
        return msgItem;

    QString strType = strs.at(1).mid(4);
    if (strType == "ACK") {
        msgItem.type = QhSingletonProcess::EMsgAck;
    } else if (strType == "ACTIVATED") {
        msgItem.type = QhSingletonProcess::EMsgActivated;
    } else if (strType == "CUSTOM") {
        msgItem.type = QhSingletonProcess::EMsgCustom;
    } else {
        msgItem.type = QhSingletonProcess::EMsgError;
        return msgItem;
    }

    strs.removeAt(0);
    strs.removeAt(1);

    if (strs.size() > 1) {
        msgItem.data = strs.join("#");
    } else if (strs.size() == 1) {
        msgItem.data = strs.first();
    }

    return msgItem;
}
