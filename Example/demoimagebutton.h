#ifndef DEMOIMAGEBUTTON_H
#define DEMOIMAGEBUTTON_H

#include <qhimagebutton.h>
#include <qhpage.h>

class DemoImageButton: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoImageButton(QWidget *parent = nullptr);
};

#endif // DEMOIMAGEBUTTON_H
