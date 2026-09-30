#include "qhcolorpicker.h"
#include "qhcolorpicker_p.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

QhColorPicker::QhColorPicker(QWidget *parent):
    QWidget(parent), d(new QhColorPickerPrivate(this))
{
    this->setObjectName("QhColorPicker");
    d->init();
    this->setStyleSheet("QhColorPicker { background: #FFFFFF; }");
}

QhColorPicker::~QhColorPicker()
{

}

void QhColorPicker::setColor(const QColor &color)
{
    d->setColor(color);
}

QhColorPickerPrivate::QhColorPickerPrivate(QhColorPicker *colorPicker):
    colorPicker(colorPicker)
{

}

QhColorPickerPrivate::~QhColorPickerPrivate()
{

}

void QhColorPickerPrivate::init()
{
    gradientSlider = new QhGradientSlider;
    labelColor = new QLabel;
    lineEditColor = new QLineEdit;
    alphaSlider = new QhAlphaSlider;
    svPanel = new QhSVPanel;
    hueSlider = new QhHueSlider(Qt::Vertical);

    gradientSlider->setFixedHeight(32);
    labelColor->setFixedSize(30, 30);
    lineEditColor->setFixedHeight(30);
    alphaSlider->setFixedHeight(24);
    svPanel->setMinimumSize(220, 170);
    hueSlider->setFixedWidth(24);

    colorPicker->setFocusPolicy(Qt::StrongFocus);

    auto *ly = new QVBoxLayout(colorPicker);

    {
        auto *lyGradient = new QHBoxLayout;
        lyGradient->addWidget(gradientSlider);
        ly->addLayout(lyGradient);
    }
    {
        auto *lyColor = new QHBoxLayout;
        lyColor->addWidget(labelColor);
        lyColor->addWidget(lineEditColor, 1);
        ly->addLayout(lyColor);
    }
    {
        auto *lyAlpha = new QHBoxLayout;
        lyAlpha->addWidget(alphaSlider);
        ly->addLayout(lyAlpha);
    }
    {
        auto *lyHue = new QHBoxLayout;
        lyHue->addWidget(svPanel, 1);
        lyHue->addWidget(hueSlider);
        ly->addLayout(lyHue);
    }

    setColor(Qt::red);

    connect(lineEditColor, &QLineEdit::textChanged,
        this, &QhColorPickerPrivate::onEditColorTextChanged);
    connect(svPanel, &QhSVPanel::selectedColorChanged,
        this, &QhColorPickerPrivate::onSVSelectedColorChanged);
    connect(hueSlider, &QhHueSlider::hueChanged,
        this, &QhColorPickerPrivate::onHueChanged);
    connect(gradientSlider, &QhGradientSlider::selectedColorChanged,
            this, &QhColorPickerPrivate::onGradientSelectedColorChanged);
}

void QhColorPickerPrivate::setColor(const QColor &color)
{
    if (selectedColor == color)
        return;

    selectedColor = color;

    labelColor->setStyleSheet(
        QString("border: 1px solid #E6E6E6; background: %1;").arg(color.name()));
    lineEditColor->setText(color.name());

    // 透明度
    alphaSlider->setColor(color);

    // 渐变色
    gradientSlider->blockSignals(true);
    gradientSlider->setSelectColor(color);
    gradientSlider->blockSignals(false);

    // SV
    svPanel->blockSignals(true);
    svPanel->setColor(color);
    svPanel->blockSignals(false);

    // 色相
    hueSlider->blockSignals(true);
    hueSlider->setHue(color.hueF());
    hueSlider->blockSignals(false);
}

void QhColorPickerPrivate::onEditColorTextChanged(const QString &text)
{
    QColor color(text);
    if (!color.isValid())
        return;

    setColor(color);
}

void QhColorPickerPrivate::onSVSelectedColorChanged(const QColor &color)
{
    setColor(color);
}

void QhColorPickerPrivate::onHueChanged(qreal hue)
{
    Q_UNUSED(hue)

    QColor color;
    svPanel->blockSignals(true);
    auto oldPos = svPanel->selectedPos();
    svPanel->setColor(hueSlider->color());
    svPanel->setSelectPos(oldPos);
    color = svPanel->selectedColor();
    svPanel->blockSignals(false);

    setColor(color);
}

void QhColorPickerPrivate::onGradientSelectedColorChanged(const QColor &color)
{
    setColor(color);
}
