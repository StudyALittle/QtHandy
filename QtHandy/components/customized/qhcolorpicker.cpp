#include "qhcolorpicker.h"
#include "qhcolorpicker_p.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#pragma execution_character_set("utf-8")

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

void QhColorPicker::setZoom(qreal zoom)
{
    d->setZoom(zoom);
}

void QhColorPicker::setColor(const QColor &color)
{
    d->setColor(color);
}

qreal QhColorPicker::zoom() const
{
    return d->zoom;
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
    buttonGroup = new QButtonGroup(this);
    buttonMonochrome = new QPushButton(tr("单色"));
    buttonLinearColor = new QPushButton(tr("线性"));
    gradientSlider = new QhGradientSlider;
    labelColor = new QLabel;
    lineEditColor = new QLineEdit;
    buttonColorAbsorber = new QPushButton;
    alphaSlider = new QhAlphaSlider;
    lineEditAlpha = new QLineEdit;
    svPanel = new QhSVPanel;
    hueSlider = new QhHueSlider(Qt::Horizontal);

    buttonMonochrome->setCheckable(true);
    buttonLinearColor->setCheckable(true);
    buttonGroup->addButton(buttonMonochrome);
    buttonGroup->addButton(buttonLinearColor);

    setZoom(zoom);

    colorPicker->setFocusPolicy(Qt::StrongFocus);

    auto *ly = new QVBoxLayout(colorPicker);

    {
        auto *lyButton = new QHBoxLayout;
        lyButton->addWidget(buttonMonochrome);
        lyButton->addWidget(buttonLinearColor);
        lyButton->addStretch(1);
        lyButton->setSpacing(0);
        ly->addLayout(lyButton);
    }
    {
        auto *lyGradient = new QHBoxLayout;
        lyGradient->addWidget(gradientSlider);
        ly->addLayout(lyGradient);
    }
    {
        auto *lyColor = new QHBoxLayout;
        lyColor->addWidget(labelColor);
        lyColor->addWidget(lineEditColor, 1);
        lyColor->addWidget(lineEditAlpha);
        lyColor->addWidget(buttonColorAbsorber);
        ly->addLayout(lyColor);
    }
    {
        auto *lyAlpha = new QHBoxLayout;
        lyAlpha->addWidget(alphaSlider, 1);
        ly->addLayout(lyAlpha);
    }
    {
        auto *lyHue = new QVBoxLayout;
        lyHue->addWidget(svPanel, 1);
        lyHue->addWidget(hueSlider);
        lyHue->setSpacing(6);
        ly->addLayout(lyHue);
    }

    setColor(Qt::red);

    connect(buttonGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
        this, &QhColorPickerPrivate::onButtonToggled);
    connect(lineEditColor, &QLineEdit::textChanged,
        this, &QhColorPickerPrivate::onEditColorTextChanged);
    connect(alphaSlider, &QhAlphaSlider::alphaChanged,
        this, &QhColorPickerPrivate::onAlphaChanged);
    connect(svPanel, &QhSVPanel::selectedColorChanged,
        this, &QhColorPickerPrivate::onSVSelectedColorChanged);
    connect(hueSlider, &QhHueSlider::hueChanged,
        this, &QhColorPickerPrivate::onHueChanged);
    connect(gradientSlider, &QhGradientSlider::selectedColorChanged,
            this, &QhColorPickerPrivate::onGradientSelectedColorChanged);

    buttonMonochrome->setChecked(true);
}

void QhColorPickerPrivate::setZoom(qreal zoom)
{
    this->zoom = zoom;

    qreal s1 = 22.0f * zoom;
    qreal s2 = 20.0f * zoom;
    qreal s3 = s2 + 6.0f * zoom;
    gradientSlider->setFixedHeight(s3);
    alphaSlider->setFixedHeight(s2);
    hueSlider->setFixedHeight(s2);
    lineEditAlpha->setFixedSize(36.0f * zoom, s2);
    labelColor->setFixedSize(s1, s1);
    lineEditColor->setFixedHeight(s1);
    buttonColorAbsorber->setFixedSize(s1, s1);
    svPanel->setMinimumSize(220.0f * zoom, 170.0f * zoom);
}

void QhColorPickerPrivate::setColor(const QColor &color)
{
    if (selectedColor == color)
        return;

    lineEditAlpha->setText(QString::number((int)(color.alphaF() * 100.0f)));
    selectedColor = color;

    labelColor->setStyleSheet(
        QString("border: 1px solid #E6E6E6; background: rgba(%1, %2, %3, %4);")
            .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));

    // 透明度
    alphaSlider->setColor(color);

    QColor showColor = color;
    showColor.setAlphaF(1.0f);

    // 只显RGB
    lineEditColor->setText(showColor.name().toUpper());

    // 渐变色
    gradientSlider->blockSignals(true);
    gradientSlider->setSelectColor(color);
    gradientSlider->blockSignals(false);

    // SV
    svPanel->blockSignals(true);
    svPanel->setColor(showColor);
    svPanel->blockSignals(false);

    // 色相
    hueSlider->blockSignals(true);
    hueSlider->setHue(showColor.hueF());
    hueSlider->blockSignals(false);
}

void QhColorPickerPrivate::onButtonToggled(QAbstractButton *button, bool checked)
{
    if (button == buttonMonochrome && checked) {
        gradientSlider->setVisible(false);
    } else if (button == buttonLinearColor && checked) {
        gradientSlider->setVisible(true);
    }
}

void QhColorPickerPrivate::onEditColorTextChanged(const QString &text)
{
    QColor color(text);
    if (!color.isValid())
        return;

    setColor(color);
}

void QhColorPickerPrivate::onAlphaChanged(qreal alpha)
{
    Q_UNUSED(alpha)

    QColor color = selectedColor;
    color.setAlphaF(alpha);
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
