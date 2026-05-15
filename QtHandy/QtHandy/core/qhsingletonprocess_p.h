#ifndef QHSINGLETONPROCESS_P_H
#define QHSINGLETONPROCESS_P_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QSharedMemory>
#include <QEventLoop>
#include "qhsingletonprocess.h"

class QhSingletonProcessServer;
class QhSingletonProcessClient;

class QhSingletonProcessPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhSingletonProcessPrivate)
    Q_DECLARE_PUBLIC(QhSingletonProcess)

public:
    QhSingletonProcessPrivate(QhSingletonProcess *q);
    ~QhSingletonProcessPrivate();

    bool start(bool bUserIsolation, const QString &name, int type, const QString &msg);
    bool start(const QString &name, int type, const QString &msg);
    void stop();

signals:
    void recvMessage(int type, const QString &data);

private:
    QhSingletonProcess *const q_ptr;

    bool m_bUserIsolation = true;
    QSharedMemory *m_shareMenory = nullptr;
    QhSingletonProcessServer *m_server = nullptr;
    QhSingletonProcessClient *m_client = nullptr;
    QString m_serveName;
};

class QhSingletonProcessMessage: public QObject
{
    Q_OBJECT

public:
    struct MsgItem
    {
        int type;
        QString data;
    };

    using QObject::QObject;

    static QByteArray packMsg(const QString &serveName, int type, const QString &data = QString());
    static MsgItem unpackMsg(const QString &serveName, const QByteArray &msg);

signals:
    void recvMessage(int type, const QString &data);
};

class QhSingletonProcessServer: public QhSingletonProcessMessage
{
    Q_OBJECT

public:
    QhSingletonProcessServer(QObject *parent = nullptr);
    ~QhSingletonProcessServer();

    /// @brief 开启服务
    bool startServer(QString serveName);
    /// @brief 停止服务
    void stopServer();

private slots:
    /// @brief 新连接
    void onNewConnection();
    /// @brief 收到数据
    void onReadyRead();

private:
    QString m_serveName;
    QLocalServer *m_server = nullptr;
};

class QhSingletonProcessClient: public QhSingletonProcessMessage
{
    Q_OBJECT

public:
    QhSingletonProcessClient(QObject *parent = nullptr);
    ~QhSingletonProcessClient();

    /// @brief 发送消息给服务
    bool sendMessageToServer(QString serveName, int type, const QString &data);
    /// @brief 断开连接
    void disconnectFromServer();

protected:
    /// @brief 连接到服务
    bool connectToServer();

private slots:
    /// @brief 读取到数据
    void onReadyRead();

private:
    QString m_serveName;

    QEventLoop m_eloop;
    bool m_bRecvAckMsg = false;
    MsgItem m_sendMsg;
    QLocalSocket *m_client = nullptr;
};

#endif // QHSINGLETONPROCESS_P_H
