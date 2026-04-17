#ifndef QHBASEPOPUP_P_H
#define QHBASEPOPUP_P_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "qhbasepopup.h"
#include "qhbasepopupcontent.h"

#pragma execution_character_set("utf-8")

class QhBasePopupPrivate : public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhBasePopupPrivate)
    Q_DECLARE_PUBLIC(QhBasePopup)

public:
    QhBasePopupPrivate(QhBasePopup *q) : q_ptr(q)
    {
    }

    bool bBasePopupContent = false;
    QWidget *widgetTitle = nullptr;
    QWidget *widgetContent = nullptr; // external settings
    QWidget *widgetButtons = nullptr;
    QLabel *labelIcon = nullptr;
    QLabel *labelTitle = nullptr;
    QPushButton *buttonOk = nullptr;
    QPushButton *buttonCancel = nullptr;
    QPushButton *buttonClose = nullptr;

    QMargins widgetTitleMargins = QMargins(24, 12, 24, 12);
    QMargins widgetButtonsMargins = QMargins(24, 12, 24, 12);
    int widgetTitleSpace = 12;
    int widgetButtonsSpace = 12;

    void init()
    {
        q_ptr->setAttribute(Qt::WA_StyledBackground);

        labelIcon = new QLabel;
        labelIcon->setObjectName("LabelIcon");
        labelTitle = new QLabel;
        labelTitle->setObjectName("LabelTitle");
        buttonOk = new QPushButton(tr("确定"));
        buttonOk->setObjectName("ButtonOk");
        buttonCancel = new QPushButton(tr("取消"));
        buttonCancel->setObjectName("ButtonCancel");
        buttonClose = new QPushButton;
        buttonClose->setObjectName("ButtonClose");
        buttonClose->setFixedSize(16, 16);

        widgetTitle = new QWidget;
        widgetTitle->setObjectName("WidgetTitle");
        auto *lyTitle = new QHBoxLayout(widgetTitle);
        lyTitle->addWidget(labelIcon);
        lyTitle->addWidget(labelTitle);
        lyTitle->addStretch(1);
        lyTitle->addWidget(buttonClose);
        lyTitle->setSpacing(widgetTitleSpace);
        lyTitle->setContentsMargins(widgetTitleMargins);

        widgetButtons = new QWidget;
        widgetButtons->setObjectName("WidgetBottom");
        auto *lyButtons = new QHBoxLayout(widgetButtons);
        lyButtons->addStretch(1);
        lyButtons->addWidget(buttonCancel);
        lyButtons->addWidget(buttonOk);
#ifdef Q_OS_MAC
        lyButtons->addStretch(1);
#endif
        lyButtons->setSpacing(widgetButtonsSpace);
        lyButtons->setContentsMargins(widgetButtonsMargins);

        auto *ly = new QVBoxLayout(q_ptr);
        ly->addWidget(widgetTitle);
        ly->addWidget(widgetButtons);
        ly->setContentsMargins(0, 0, 0, 0);

        connect(buttonOk, &QPushButton::clicked, this, &QhBasePopupPrivate::onOkButtonClicked);
        connect(buttonCancel, &QPushButton::clicked, this, &QhBasePopupPrivate::onCancelButtonClicked);
        connect(buttonClose, &QPushButton::clicked, this, &QhBasePopupPrivate::onCloseButtonClicked);

        q_ptr->setTitleBar(widgetTitle);
        q_ptr->setTitleBarEnableChilds({labelIcon, labelTitle});
    }

    void setWidgetContent(QWidget *w)
    {
        widgetContent = w;
        static_cast<QVBoxLayout *>(q_ptr->layout())->insertWidget(1, w, 1);

        connect(w, &QWidget::destroyed, this, [this](QObject *obj) {
            if (obj != widgetContent)
                return;

            if (widgetContent) {
                widgetContent->setParent(nullptr);
                widgetContent = nullptr;
            }
        });
    }
    void setWidgetContent(QhBasePopupContent *w)
    {
        bBasePopupContent = true;
        setWidgetContent((QWidget *)w);
    }

    void setWidgetTitleSpace(int space)
    {
        widgetTitle->layout()->setSpacing(space);
    }

    void setWidgetButtonsSpace(int space)
    {
        widgetButtons->layout()->setSpacing(space);
    }

    void setWidgetTitleMargins(const QMargins &mgs)
    {
        widgetTitle->layout()->setContentsMargins(mgs);
    }

    void setWidgetButtonsMargins(const QMargins &mgs)
    {
        widgetButtons->layout()->setContentsMargins(mgs);
    }

    QhBasePopup *const q_ptr;
    QhBasePopup::Buttons buttons =
        static_cast<QhBasePopup::Buttons>(QhBasePopup::ButtonOk | QhBasePopup::ButtonCancel | QhBasePopup::ButtonClose);

    QhBasePopup::Button closedButton;

    QhBasePopupContent *widgetBaseContent()
    {
        return (bBasePopupContent && widgetContent) ? static_cast<QhBasePopupContent *>(widgetContent) : nullptr;
    }

protected slots:
    void onOkButtonClicked()
    {
        if (q_ptr->afterButtonOk() && (!widgetBaseContent() || widgetBaseContent()->afterButtonOk())) {
            closedButton = QhBasePopup::ButtonOk;
            q_ptr->accept();
        }
    }

    void onCancelButtonClicked()
    {
        if (q_ptr->afterButtonCancel() && (!widgetBaseContent() || widgetBaseContent()->afterButtonCancel())) {
            closedButton = QhBasePopup::ButtonCancel;
            q_ptr->reject();
        }
    }

    void onCloseButtonClicked()
    {
        if (q_ptr->afterButtonClose() && (!widgetBaseContent() || widgetBaseContent()->afterButtonClose())) {
            closedButton = QhBasePopup::ButtonClose;
            q_ptr->reject();
        }
    }
};

#endif // QHBASEPOPUP_P_H
