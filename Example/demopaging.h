#ifndef DEMOPAGING_H
#define DEMOPAGING_H

#include <QWidget>
#include <qhpage.h>

class DemoPaging: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoPaging(QWidget *parent = nullptr);
};

#endif // DEMOPAGING_H
