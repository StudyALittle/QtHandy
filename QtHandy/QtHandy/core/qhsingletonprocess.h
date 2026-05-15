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
    enum EMsgType {
        EMsgError,      // 错误消息
        EMsgAck,        // 应答消息
        EMsgActivated,  // 激活消息
        EMsgCustom      // 自定义消息
    };

    QhSingletonProcess();
    ~QhSingletonProcess();

    static QhSingletonProcess *instance();
    static void delInstance();

    /**
     * @brief bind：绑定进程实例
     * @param bUserIsolation：用户隔离
     * @param name：服务名称
     * @param type：消息类型
     * @param msg：自定义消息内容
     * @return 返回false表示另外的进程正在正常运行，true表示绑定进程实例成功
     */
    bool bind(bool bUserIsolation, const QString &name, EMsgType type, const QString &msg = QString());
    bool bind(const QString &name, EMsgType type, const QString &msg = QString());

    /**
     * @brief unbind：取消绑定
     */
    void unbind();

signals:
    /**
     * @brief recvMessage：接收消息
     * @param type：EMsgType
     * @param data：消息内容
     */
    void recvMessage(int type, const QString &data);

private:
    QScopedPointer<QhSingletonProcessPrivate> d;
    Q_DISABLE_COPY(QhSingletonProcess)
    friend class QhBasePopupPrivate;
};

#endif // QHSINGLETONPROCESS_H
