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

    bool bind(bool bUserIsolation, const QString &name);
    bool bind(const QString &name);
    void unbind();

    void sendMessage(int type, const QString &data);

signals:
    void receivedMessage(int type, const QString &data);

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
    using QObject::QObject;

    /// @brief request message Item
    struct RequestMsgItem
    {
        int type;
        QString data;
    };

    /// @brief response message Item
    struct ResponseMsgItem
    {
        int type;       // message type(RequestMsgItem type)
        int code;       // message code, 0: success, other: failed
        QString data;   // message data
    };

    static QByteArray packMsg(const QString &serverName, const RequestMsgItem &item);
    static ResponseMsgItem unpackMsg(const QString &serverName, const QByteArray &msg);

signals:
    void receivedMessage(int type, const QString &data);
};

class QhSingletonProcessServer: public QhSingletonProcessMessage
{
    Q_OBJECT

public:
    QhSingletonProcessServer(QObject *parent = nullptr);
    ~QhSingletonProcessServer();

    void setServerName(const QString &serveName);

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

    void setServerName(const QString &serveName);

    /// @brief 发送消息给服务
    ResponseMsgItem sendMessageToServer(const RequestMsgItem &item, int timeout = 2000);

    /// @brief 异步发送消息给服务
    void sendMessageToServerAsync(const RequestMsgItem &item);

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
    ResponseMsgItem m_responseMsg;
    QLocalSocket *m_client = nullptr;
};

#endif // QHSINGLETONPROCESS_P_H
