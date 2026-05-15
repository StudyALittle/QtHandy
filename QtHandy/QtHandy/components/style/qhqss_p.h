#ifndef QHQSS_P_H
#define QHQSS_P_H

#include "qhqss.h"

class QhQssPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhQssPrivate)

public:
    explicit QhQssPrivate(QhQss *p, QWidget *widget);

    QWidget *widget = nullptr;
    QVector<QhQssParser::Item::Ptr> qssItems;
    std::function<void()> funcQssReloaded = nullptr;
    QMap<QhQss::SubControl, QMap<QhQss::PseudoState, QhQss::PropertyTypes> > propertyTypes;

    void init(std::function<void()> cbFuncQssReloaded);
    void parserQss();

    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:
    void onObjectNameChanged(const QString &objectName);

private:
    // QhQssLoader *loader = nullptr;
    QhQss *ptr;
};

#endif // QHQSS_P_H
