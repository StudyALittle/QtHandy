#include "qhcolorpicker.h"
#include "qhcolorpicker_p.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

QhColorPicker::QhColorPicker(QWidget *parent):
    QWidget(parent), d(new QhColorPickerPrivate(this))
{
    d->init();
}

QhColorPicker::~QhColorPicker()
{

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
    labelColor = new QLabel;
    lineEditColor = new QLineEdit;
    svPanel = new QhSVPanel;
    hueSlider = new QhHueSlider(Qt::Vertical);

    labelColor->setFixedSize(30, 30);
    lineEditColor->setFixedHeight(30);
    svPanel->setMinimumSize(220, 170);
    hueSlider->setFixedWidth(20);

    auto *ly = new QVBoxLayout(colorPicker);

    {
        auto *colorLy = new QHBoxLayout;
        colorLy->addWidget(labelColor);
        colorLy->addWidget(lineEditColor, 1);
        ly->addLayout(colorLy);
    }
    {
        auto *svHue = new QHBoxLayout;
        svHue->addWidget(svPanel, 1);
        svHue->addWidget(hueSlider);
        ly->addLayout(svHue);
    }

    connect(svPanel, &QhSVPanel::colorChanged, this, &QhColorPickerPrivate::onSVColorChanged);
    connect(hueSlider, &QhHueSlider::hueChanged, this, &QhColorPickerPrivate::onHueChanged);
}

void QhColorPickerPrivate::onSVColorChanged(const QColor &color)
{
    labelColor->setStyleSheet(
        QString("border: 1px solid #E6E6E6; background: %1;").arg(color.name()));
    lineEditColor->setText(color.name());
}

void QhColorPickerPrivate::onHueChanged(qreal hue)
{
    Q_UNUSED(hue)
    auto oldHue = svPanel->hue();
    svPanel->setColor(hueSlider->color());
    // svPanel->setHue(oldHue);
}
