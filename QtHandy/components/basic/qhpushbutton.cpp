#include "qhpushbutton.h"
#include "qhpushbutton_p.h"
#include <QStyleOptionButton>
#include <QPainter>
#include <QDebug>
#include "qhimageutil.h"

#define SET_IMAGES(Value) \
    d->attribute(QhQss::StateNormal)->images[idx].Value = Value; \
    d->attribute(QhQss::StateDisabled)->images[idx].Value = Value; \
    d->attribute(QhQss::StateHover)->images[idx].Value = Value; \
    d->attribute(QhQss::StatePressed)->images[idx].Value = Value; \
    d->attribute(QhQss::StateChecked)->images[idx].Value = Value;

#define SET_IMAGES_COLORS(Value) \
    d->attribute(QhQss::StateNormal)->color = Value; \
    d->attribute(QhQss::StateDisabled)->color = Value; \
    d->attribute(QhQss::StateHover)->color = Value; \
    d->attribute(QhQss::StatePressed)->color = Value; \
    d->attribute(QhQss::StateChecked)->color = Value;

#define D_RESIZE() \
    QStyleOptionButton option; \
    initStyleOption(&option); \
    d->resize(option);

QhPushButton::QhPushButton(QWidget *parent):
    QPushButton(parent),
    d(new QhPushButtonPrivate(this))
{
    d->init();
}

QhPushButton::QhPushButton(const QString &text, QWidget *parent):
    QPushButton(QString(), parent),
    d(new QhPushButtonPrivate(this))
{
    d->init();
    setText(text);
}

QhPushButton::QhPushButton(const QIcon &icon, const QString &text, QWidget *parent):
    QPushButton(icon, QString(), parent),
    d(new QhPushButtonPrivate(this))
{
    d->init();
    setText(text);
}

QhPushButton::~QhPushButton()
{

}

bool QhPushButton::isImageMode() const
{
    return d->bImageMode;
}

QString QhPushButton::text() const
{
    return d->text;
}

void QhPushButton::setImageMode(bool b)
{
    d->bImageMode = b;
    if (d->bImageMode) {
        QPushButton::setText(QString());
    }

    D_RESIZE()
    this->update();
}

void QhPushButton::setText(const QString &text)
{
    d->text = text;
    if (d->bImageMode) {
        QPushButton::setText(QString());
        D_RESIZE()
    } else {
        QPushButton::setText(text);
    }
    this->update();
}

void QhPushButton::resizeUpdate()
{
    D_RESIZE()
            this->update();
}

QhQss *QhPushButton::handyQss()
{
    return d->handyQss;
}

void QhPushButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QStyleOptionButton option;
    initStyleOption(&option);
    d->draw(&p, option);
}

QhPushButtonPrivate::QhPushButtonPrivate(QhPushButton *p):
    handyQss(new QhQss(p)), ptr(p)
{

}

void QhPushButtonPrivate::init()
{
    handyQss->init(std::bind(&QhPushButtonPrivate::qssReloaded, this));
    connect(handyQss, &QhQss::propertyTypesChanged, this, [this]() {
        ptr->resizeUpdate();
    });
}

void QhPushButtonPrivate::qssReloaded()
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
    setPropertyTypes(QhQss::SSC_Left);
    setPropertyTypes(QhQss::SSC_Right);

    ptr->resizeUpdate();
}

QhQss::PseudoState QhPushButtonPrivate::currentState(QStyleOptionButton &option)
{
    QhQss::PseudoState state;
    if (!ptr->isEnabled()) {
        // disable
        state = QhQss::SPS_Disabled;
    } else if ((option.state & QStyle::State_Sunken) == QStyle::State_Sunken) {
        // pressed
        state = QhQss::SPS_Pressed;
    } else if ((option.state & QStyle::State_MouseOver) == QStyle::State_MouseOver) {
        // hover
        state = QhQss::SPS_Hover;
    } else {
        // normal
        state = QhQss::SPS_Normal;
    }
    return state;
}

void QhPushButtonPrivate::resize(QStyleOptionButton &option)
{
    if (!bImageMode)
        return;

    auto state = currentState(option);

    auto pTypes = handyQss->propertyTypes(state);
    auto pLeftTypes = handyQss->propertyTypes(QhQss::SSC_Left, state);
    auto pRightTypes = handyQss->propertyTypes(QhQss::SSC_Right, state);

    bool bLeftImg = pLeftTypes.visible;
    bool bRightImg = pRightTypes.visible;

    QSizeF leftImgSize = pLeftTypes.imageSize;
    QSizeF rightImgSize = pLeftTypes.imageSize;

    QFontMetricsF fm(ptr->font());
    qreal tw = fm.horizontalAdvance(text);

    qreal maxh = fm.height();
    qreal w = tw + pTypes.padding.left() + pTypes.padding.right();
    if (bLeftImg) {
        w += (pTypes.space + leftImgSize.width());
        maxh = qMax(maxh, leftImgSize.height());
    }
    if (bRightImg) {
        w += (pTypes.space + rightImgSize.width());
        maxh = qMax(maxh, rightImgSize.height());
    }
    qreal h = maxh + pTypes.padding.top() + pTypes.padding.bottom();
    ptr->resize(w, h);
}

void QhPushButtonPrivate::draw(QPainter *p, QStyleOptionButton &option)
{
    if (!bImageMode)
        return;

    auto state = currentState(option);

    auto pTypes = handyQss->propertyTypes(state);
    auto pLeftTypes = handyQss->propertyTypes(QhQss::SSC_Left, state);
    auto pRightTypes = handyQss->propertyTypes(QhQss::SSC_Right, state);

    bool bLeftImg = pLeftTypes.visible;
    bool bRightImg = pRightTypes.visible;

    qreal w = ptr->width();
    qreal h = ptr->height();
    qreal x = pTypes.padding.left(), y = 0;

    QPixmap pixmapBegin, pixmapEnd;
    if (pLeftTypes.imagePath.endsWith(".svg")) {
        pixmapBegin = QhImageUtil::svgToPixmap(
            pLeftTypes.imagePath, pLeftTypes.imageColor, pLeftTypes.imageSize);
    } else {
        pixmapBegin = QhImageUtil::pixmap(
            pLeftTypes.imagePath, pLeftTypes.imageSize);
    }

    if (pRightTypes.imagePath.endsWith(".svg")) {
        pixmapEnd = QhImageUtil::svgToPixmap(
            pRightTypes.imagePath, pRightTypes.imageColor, pRightTypes.imageSize);
    } else {
        pixmapEnd = QhImageUtil::pixmap(
            pRightTypes.imagePath, pRightTypes.imageSize);
    }

    QString wtext = text;

    // Calculate text width
    QFontMetricsF fm(ptr->font());
    qreal tw = fm.horizontalAdvance(text);

    // Actual text width that can be drawn
    if (text.isEmpty()) {
        tw = 0;
    } else {
        qreal enablew = w - pTypes.padding.left() - pTypes.padding.right();
        if (bLeftImg) {
            enablew -= (pTypes.space + pLeftTypes.imageSize.width());
        }
        if (bRightImg) {
            enablew -= (pTypes.space + pRightTypes.imageSize.width());
        }
        if (tw > enablew) {
            tw = enablew;
            wtext = fm.elidedText(text, Qt::ElideRight, enablew);
        }
    }

    // p->setFont(ptr->font());
    p->setPen(pTypes.color);

    if (pTypes.align == Qt::AlignCenter) {
        // draw center text
        qreal tx = (w - tw) / 2.0f;
        y = (h - fm.height()) / 2.0f;
        p->drawText(QRectF(tx, y, tw, fm.height()), Qt::AlignCenter, wtext);

        // draw left image
        if (bLeftImg) {
            auto &img = pixmapBegin;
            QSizeF imgSize = img.size();

            y = (h - imgSize.height()) / 2.0f;
            if (pRightTypes.relativePos == QhQss::FollowText) {
                x = tx - pTypes.space - imgSize.width();
            }
            p->drawPixmap(x, y, imgSize.width(), imgSize.height(), pixmapBegin);
        }
        x = tx + tw + pTypes.space;
    } else if (pTypes.align == Qt::AlignLeft) {
        // draw left image
        if (bLeftImg) {
            auto &img = pixmapBegin;
            QSizeF imgSize = img.size();

            y = (h - imgSize.height()) / 2.0f;
            p->drawPixmap(x, y, imgSize.width(), imgSize.height(), img);
            x += (imgSize.width() + pTypes.space);
        }

        // draw center text
        y = (h - fm.height()) / 2.0f;
        p->drawText(QRectF(x, y, tw, fm.height()), Qt::AlignCenter, wtext);
        x += (tw + pTypes.space);
    } else if (pTypes.align == Qt::AlignRight) {
        // draw center text
        qreal tx = pTypes.padding.right() - tw;
        if (bRightImg) {
            tx -= (pTypes.space + pRightTypes.imageSize.width());
        }
        y = (h - fm.height()) / 2.0f;
        p->drawText(QRectF(tx, y, tw, fm.height()), Qt::AlignCenter, wtext);

        // draw left image
        if (bLeftImg) {
            auto &img = pixmapBegin;
            QSizeF imgSize = img.size();

            y = (h - imgSize.height()) / 2.0f;
            if (pRightTypes.relativePos == QhQss::FollowText) {
                x = tx - pTypes.space - imgSize.width();
            }
            p->drawPixmap(x, y, imgSize.width(), imgSize.height(), img);
        }
        x = tx + tw + pTypes.space;
    }

    // draw right image
    if (bRightImg) {
        auto &img = pixmapEnd;
        QSizeF imgSize = img.size();

        y = (h - imgSize.height()) / 2.0f;
        if (pRightTypes.relativePos == QhQss::NearBorder) {
            x = w - pTypes.padding.right() - imgSize.width();
        }
        p->drawPixmap(x, y, imgSize.width(), imgSize.height(), img);
    }
}















