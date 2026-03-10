#include "qhimagebutton.h"
#include "qhimagebutton_p.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOptionButton>
#include "qhimageutil.h"
#include "qhwidgetutil.h"

QhImageButton::QhImageButton(QWidget *parent):
    QPushButton(parent),
    d(new QhImageButtonPrivate(this))
{
    d->init();
}

QhImageButton::QhImageButton(const QString &text, QWidget *parent):
    QPushButton(parent),
    d(new QhImageButtonPrivate(this))
{
    d->init();
    setText(text);
}

QhImageButton::~QhImageButton()
{

}

QString QhImageButton::text() const
{
    return d->text;
}

bool QhImageButton::isLeftIconVisible() const
{
    return d->iconLeft->isVisible();
}

bool QhImageButton::isRightIconVisible() const
{
    return d->iconRight->isVisible();
}

void QhImageButton::setText(const QString &text)
{
    d->text = text;
    if (!d->iconLeft->isVisible()
            &&!d->iconRight->isVisible()) {
        // QPushButton::setText(text);
    } else {
        // QPushButton::setText(QString());
    }
    this->update();
}

void QhImageButton::setLeftIconVisible(bool b)
{
    d->iconLeft->setVisible(b);
    setText(d->text);
}

void QhImageButton::setRightIconVisible(bool b)
{
    d->iconRight->setVisible(b);
    setText(d->text);
}

QSize QhImageButton::getLeftIconSize() const
{
    return d->leftIconSize;
}

QString QhImageButton::getLeftIconPath() const
{
    return d->leftIconPath;
}

QSize QhImageButton::getRightIconSize() const
{
    return d->rightIconSize;
}

QString QhImageButton::getRightIconPath() const
{
    return d->rightIconPath;
}

int QhImageButton::getTextOffset() const
{
    return d->textOffset;
}

void QhImageButton::setLeftIconSize(const QSize &size)
{
    d->leftIconSize = size;
    d->iconLeft->setFixedSize(size);
    this->update();
}

void QhImageButton::setLeftIconPath(const QString &path)
{
    d->leftIconPath = path;
    // d->iconLeft->setPixmap(QPixmap(path));
    this->update();
}

void QhImageButton::setRightIconSize(const QSize &size)
{
    d->rightIconSize = size;
    d->iconRight->setFixedSize(size);
    this->update();
}

void QhImageButton::setRightIconPath(const QString &path)
{
    d->rightIconPath = path;
    // d->iconRight->setPixmap(QPixmap(path));
    this->update();
}

void QhImageButton::setTextOffset(int n)
{
    d->textOffset = n;
    this->update();
}

void QhImageButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    if (!d->iconLeft->isVisible()
            &&!d->iconRight->isVisible()) {
        // return;
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QStyleOptionButton option;
    initStyleOption(&option);
    // d->draw(&p, option);

    auto state = d->currentState(option);

    // draw text
    QFontMetricsF fm(this->font());
    qreal tw = fm.horizontalAdvance(d->text);
    QColor tcolor = d->handyQss->attributeValue(
        QhQss::stateToString(state), "color");
    p.setPen(tcolor);

    QFont ft = p.font();
    d->handyQss->readAttribute(QhQss::SSC_Not, state, ft);
    p.setFont(ft);

    if (d->iconLeft->isVisible()) {
        p.drawText(QRectF(d->iconLeft->x()
                          + d->iconLeft->width()
                          + d->textOffset, 0, tw, this->height()),
            Qt::AlignVCenter, d->text);
    } else {
        p.drawText(QRectF(this->layout()->contentsMargins().left(), 0, tw, this->height()),
            Qt::AlignVCenter, d->text);
    }

    // draw image
    QString leftIconPath = d->handyQss->attributeValue(
        QhQss::stateToString(state), "qproperty-pLeftIconPath");
    if (leftIconPath.isEmpty())
        leftIconPath = d->handyQss->attributeValue(
            QhQss::stateToString(QhQss::SPS_Normal), "qproperty-pLeftIconPath");
    QString rightIconPath = d->handyQss->attributeValue(
        QhQss::stateToString(state), "qproperty-pRightIconPath");
    if (rightIconPath.isEmpty())
        rightIconPath = d->handyQss->attributeValue(
            QhQss::stateToString(QhQss::SPS_Normal), "qproperty-pRightIconPath");

    if (d->iconLeft->isVisible())
        d->iconLeft->setPixmap(QhImageUtil::pixmap(leftIconPath, d->leftIconSize));
    if (d->iconRight->isVisible())
        d->iconRight->setPixmap(QhImageUtil::pixmap(rightIconPath, d->rightIconSize));
}

QhImageButtonPrivate::QhImageButtonPrivate(QhImageButton *q):
    ptr(q), handyQss(new QhQss(q))
{

}

QhImageButtonPrivate::~QhImageButtonPrivate()
{

}

void QhImageButtonPrivate::init()
{
    handyQss->init(std::bind(&QhImageButtonPrivate::qssReloaded, this));
    connect(handyQss, &QhQss::propertyTypesChanged, this, [this]() {
        ptr->update();
    });

    auto *ly = new QHBoxLayout(ptr);

    iconLeft = new QLabel;
    iconLeft->setObjectName("IconLeft");
    iconLeft->setFixedSize(leftIconSize);
    iconRight = new QLabel;
    iconRight->setObjectName("IconRight");
    iconRight->setFixedSize(rightIconSize);

    iconLeft->setMouseTracking(true);
    iconRight->setMouseTracking(true);

    ly->addWidget(iconLeft);
    ly->addStretch(1);
    ly->addWidget(iconRight);
    ly->setContentsMargins(12, 0, 12, 0);
}

void QhImageButtonPrivate::qssReloaded()
{
    if (!handyQss)
        return;

    if (handyQss->items().isEmpty()) {
        return;
    }

    auto setPropertyTypes = [this](QhQss::SubControl subControl)
    {
        auto typeNormal = handyQss->attributes(subControl, QhQss::SPS_Normal);
        handyQss->setPropertyTypes(subControl, QhQss::SPS_Normal, typeNormal);

        auto typeDisabled = handyQss->attributes(subControl, QhQss::SPS_Disabled);
        handyQss->setDefaultAttribute(subControl, QhQss::SPS_Disabled, typeNormal, typeDisabled);
        handyQss->setPropertyTypes(subControl, QhQss::SPS_Disabled, typeDisabled);

        auto typeHover = handyQss->attributes(subControl, QhQss::SPS_Hover);
        handyQss->setDefaultAttribute(subControl, QhQss::SPS_Hover, typeNormal, typeHover);
        handyQss->setPropertyTypes(subControl, QhQss::SPS_Hover, typeHover);

        auto typePressed = handyQss->attributes(subControl, QhQss::SPS_Pressed);
        handyQss->setDefaultAttribute(subControl, QhQss::SPS_Pressed, typeNormal, typePressed);
        handyQss->setPropertyTypes(subControl, QhQss::SPS_Pressed, typePressed);

        auto typeChecked = handyQss->attributes(subControl, QhQss::SPS_Checked);
        handyQss->setDefaultAttribute(subControl, QhQss::SPS_Checked, typeNormal, typeChecked);
        handyQss->setPropertyTypes(subControl, QhQss::SPS_Checked, typeChecked);
    };

    setPropertyTypes(QhQss::SSC_Not);
    ptr->update();
}

QhQss::PseudoState QhImageButtonPrivate::currentState(QStyleOptionButton &option)
{
    QhQss::PseudoState state;
    if (!ptr->isEnabled()) {                                                            // disable
        state = QhQss::SPS_Disabled;
    } else if ((option.state & QStyle::State_Sunken) == QStyle::State_Sunken) {         // pressed
        state = QhQss::SPS_Pressed;
    } else if ((option.state & QStyle::State_MouseOver) == QStyle::State_MouseOver) {   // hover
        state = QhQss::SPS_Hover;
    } else if ((option.state & QStyle::State_Selected) == QStyle::State_Selected) {     // checked
        state = QhQss::SPS_Checked;
    } else {                                                                            // normal
        state = QhQss::SPS_Normal;
    }
    return state;
}
