#ifndef DEMOTEXTEDIT_H
#define DEMOTEXTEDIT_H

#include <qhtextedit.h>
#include <qhpage.h>

class DemoTextEdit: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoTextEdit(QWidget *parent = nullptr);
};

#endif // DEMOTEXTEDIT_H
