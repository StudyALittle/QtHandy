#include "qhsingletonprocess.h"
#include "qhsingletonprocess_p.h"
#include <QTimer>
#include "util/qhutil.h"

QhSingletonProcess &QhSingletonProcess::instance()
{
    static QhSingletonProcess g_singletonProcess;
    return g_singletonProcess;
}

QhSingletonProcess::QhSingletonProcess():
    d(new QhSingletonProcessPrivate(this))
{
    connect(d.get(), &QhSingletonProcessPrivate::receivedMessage,
        this, &QhSingletonProcess::receivedMessage);
}

QhSingletonProcess::~QhSingletonProcess()
{
    unbind();
}

bool QhSingletonProcess::bind(bool bUserIsolation, const QString &name)
{
    return d->bind(bUserIsolation, name);
}

bool QhSingletonProcess::bind(const QString &name)
{
    return d->bind(name);
}

void QhSingletonProcess::unbind()
{
    d->unbind();
}

void QhSingletonProcess::sendMessage(MsgType type, const QString &data)
{
    d->sendMessage(type, data);
}

////////////////////////////// QhSingletonProcessPrivate //////////////////////////////
QhSingletonProcessPrivate::QhSingletonProcessPrivate(QhSingletonProcess *q):
    q_ptr(q)
{
    m_server = new QhSingletonProcessServer(this);
    m_client = new QhSingletonProcessClient(this);

    connect(m_server, &QhSingletonProcessServer::receivedMessage,
            this, &QhSingletonProcessPrivate::receivedMessage);
}

QhSingletonProcessPrivate::~QhSingletonProcessPrivate()
{
    unbind();
}

bool QhSingletonProcessPrivate::bind(bool bUserIsolation, const QString &name)
{
    m_bUserIsolation = bUserIsolation;
    return bind(name);
}

bool QhSingletonProcessPrivate::bind(const QString &name)
{
    // server name
    m_serveName = QString("SingletonProcess_%1").arg(name);
    if (m_bUserIsolation) {
        m_serveName.append("_");
        m_serveName.append(QhUtil::systemLoginUserName());
    }

    m_client->setServerName(m_serveName);
    m_server->setServerName(m_serveName);

    // shared memory
    if (m_shareMenory)
        m_shareMenory->setKey(m_serveName);
    else
        m_shareMenory = new QSharedMemory(m_serveName, this);

    // shared memory is occupied (process is running)
    if (!m_shareMenory->create(32) && m_shareMenory->error() == QSharedMemory::AlreadyExists) {
        // check if the process is normal
        QhSingletonProcessMessage::RequestMsgItem item{QhSingletonProcess::MT_Confirm, QByteArray()};
        auto res = m_client->sendMessageToServer(item);
        if (res.code != 0) {
            // sleep for a while, ensure that when two applications start at the same time, the previous one has already started successfully
            QEventLoop eloop;
            QTimer::singleShot(300, this, [&eloop]() { eloop.exit(); });
            eloop.exec();

            // re-try connection
            res = m_client->sendMessageToServer(item);
        }

        if (res.code != 0) { // connection failed (the previous process is abnormal)
            // attach to shared memory
            m_shareMenory->attach();
            // remove previous service
            if (QLocalServer::removeServer(m_serveName)) {
                // start server
                return m_server->startServer(m_serveName);
            } else {
                m_shareMenory->deleteLater();
                m_shareMenory = nullptr;
                return false;
            }
        } else {
            // the same program is still running, cannot start the current instance
            m_shareMenory->deleteLater();
            m_shareMenory = nullptr;
            return false;
        }
    } else {
        // no same process exists
        // remove previous service
        QLocalServer::removeServer(m_serveName);
        return m_server->startServer(m_serveName);
    }

    return true;
}

void QhSingletonProcessPrivate::unbind()
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

void QhSingletonProcessPrivate::sendMessage(int type, const QString &data)
{
    if (m_client) {
        QhSingletonProcessMessage::RequestMsgItem item{type, data};
        m_client->sendMessageToServer(item);
    }
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

void QhSingletonProcessServer::setServerName(const QString & serveName)
{
    m_serveName = serveName;
}

bool QhSingletonProcessServer::startServer(QString serveNam)
{
    m_serveName = serveNam;
    if (!m_server) {
        m_server = new QLocalServer;
        connect(m_server, &QLocalServer::newConnection, this, &QhSingletonProcessServer::onNewConnection);
    }

    if (m_server->listen(m_serveName)) {
        return true;
    } else {
        qWarning() << "SingletonProcess server listen error, may be the service is already exist!";
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

    // ready read
    connect(socket, &QLocalSocket::readyRead, this, &QhSingletonProcessServer::onReadyRead);
    // destory 
    connect(socket, &QLocalSocket::disconnected, [=]() {
        socket->close();
        socket->deleteLater();
    });
    // error, destory 
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    connect(socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),
            [=](QLocalSocket::LocalSocketError) {
#else
    connect(socket, &QLocalSocket::errorOccurred, [=](QLocalSocket::LocalSocketError socketError) {
#endif
        socket->close();
        socket->deleteLater();
    });
}

void QhSingletonProcessServer::onReadyRead()
{
    auto *socket = static_cast<QLocalSocket*>(sender());
    if (!socket)
        return;

    QByteArray data = socket->readAll();
    auto msg = unpackMsg(m_serveName, data);

    // Reply to the message
    auto ackMsg = packMsg(m_serveName, 
        QhSingletonProcessMessage::RequestMsgItem{msg.type, QByteArray()});
    socket->write(ackMsg);
    socket->flush();

    // Communication once and close the resource (short connection)
    socket->close();
    socket->deleteLater();

    if (msg.code != 0)
        return;

    emit receivedMessage(msg.type, msg.data);
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

void QhSingletonProcessClient::setServerName(const QString & serveName)
{
    m_serveName = serveName;
}

QhSingletonProcessMessage::ResponseMsgItem QhSingletonProcessClient::sendMessageToServer(
    const QhSingletonProcessMessage::RequestMsgItem &item, int timeout)
{
    m_responseMsg.type = item.type;
    m_responseMsg.code = 1;
    m_responseMsg.data = "";

    // connect to server
    if (!connectToServer()) {
        return m_responseMsg;
    }

    // send message
    m_client->write(packMsg(m_serveName, item));
    m_client->flush();

    // timeout handling
    QTimer::singleShot(timeout, this, [this]() {
        m_eloop.exit();
    });
    m_eloop.exec();

    disconnectFromServer();
    return m_responseMsg;
}

void QhSingletonProcessClient::sendMessageToServerAsync(const RequestMsgItem & item)
{
    if (!connectToServer())
        return;

    m_client->write(packMsg(m_serveName, item));
    m_client->flush();
}

bool QhSingletonProcessClient::connectToServer()
{
    if (!m_client) {
        m_client = new QLocalSocket;
        connect(m_client, &QLocalSocket::readyRead, this, &QhSingletonProcessClient::onReadyRead);
    }

    // connect to server
    m_client->connectToServer(m_serveName);
    if (m_client->waitForConnected(6000)) {
        qDebug() << "SingletonProcess connect server process success!";
        return true;
    } else {
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
    disconnectFromServer();

    auto msg = unpackMsg(m_serveName, data);
    if (msg.code != 0) {
        return;
    }

    m_responseMsg = msg;
    m_eloop.exit();
}

////////////////////////////// QhSingletonProcessMessage //////////////////////////////
QByteArray QhSingletonProcessMessage::packMsg(const QString &serverName, const QhSingletonProcessMessage::RequestMsgItem &item)
{
    QString strFlag;
    switch (item.type) {
    case QhSingletonProcess::MT_Confirm:       { strFlag = "CONFIRM"; break; };
    case QhSingletonProcess::MT_Activated: { strFlag = "ACTIVATED"; break; }
    case QhSingletonProcess::MT_Custom:    { strFlag = "CUSTOM"; break; }
    }

    return QString("%1#MSG:%2#%3").arg(serverName, strFlag, item.data).toLocal8Bit();
}

QhSingletonProcessMessage::ResponseMsgItem QhSingletonProcessMessage::unpackMsg(const QString &serveName, const QByteArray &_msg)
{
    ResponseMsgItem msgItem;
    QString msg = QString::fromLocal8Bit(_msg);

    auto strs = msg.split("#", QString::KeepEmptyParts);
    if (strs.size() < 2 || strs.at(0) != serveName || !strs.at(1).startsWith("MSG:"))
        return msgItem;

    QString strType = strs.at(1).mid(4);
    if (strType == "CONFIRM") {
        msgItem.type = QhSingletonProcess::MT_Confirm;
    } else if (strType == "ACTIVATED") {
        msgItem.type = QhSingletonProcess::MT_Activated;
    } else if (strType == "CUSTOM") {
        msgItem.type = QhSingletonProcess::MT_Custom;
    } else {
        msgItem.code = 1;
        return msgItem;
    }

    msgItem.code = 0;

    strs.removeAt(0);
    strs.removeAt(0);

    if (strs.size() > 1) {
        msgItem.data = strs.join("#");
    } else if (strs.size() == 1) {
        msgItem.data = strs.first();
    }

    return msgItem;
}
