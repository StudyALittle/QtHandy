#ifndef QHSINGLETONPROCESS_H
#define QHSINGLETONPROCESS_H

/**
 * @brief The QSingletonProcess class：保证一个应用程序只能有一个实例
 */

#include <QObject>
#include "QH_global.h"

class QhSingletonProcessPrivate;

class QTHANDY_EXPORT QhSingletonProcess: public QObject
{
    Q_OBJECT

public:
    enum MsgType {
        MT_Confirm,     // 确认消息（客户端确认服务端是否正常运行）
        MT_Activated,   // 激活消息（客户端激活服务端进程，需要服务连接receivedMessage处理）
        MT_Custom = 10, // 自定义消息（客户端发送自定义消息，需要服务端处理）
    };

    struct Message
    {
        MsgType type;   // message type
        QString data;   // message data
    };

    QhSingletonProcess();
    ~QhSingletonProcess();

    static QhSingletonProcess &instance();

    /// @brief bind：绑定进程实例
    /// @param bUserIsolation: 用户隔离（默认为true）
    /// @param name: 服务名称
    /// @param type: 消息类型
    /// @param msg: 自定义消息内容
    /// @return 返回false表示另外的进程正在正常运行，true表示绑定进程实例成功
    bool bind(bool bUserIsolation, const QString &name);

    /// @brief bind：绑定进程实例（start的重载函数）
    bool bind(const QString &name);

    /// @brief stop：取消绑定进程实例
    void unbind();

    /// @brief sendMessage：发送消息
    void sendMessage(MsgType type, const QString &data = QByteArray());

signals:
    /// @brief receivedMessage：接收到消息
    /// @param type：消息类型(MsgType)
    /// @param data：消息内容
    void receivedMessage(int type, const QString &data);

private:
    QScopedPointer<QhSingletonProcessPrivate> d;
    Q_DISABLE_COPY(QhSingletonProcess)
    friend class QhBasePopupPrivate;
};

#endif // QHSINGLETONPROCESS_H
