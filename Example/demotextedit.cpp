#include "demotextedit.h"
#include <QVBoxLayout>
#include <qhlabel.h>

DemoTextEdit::DemoTextEdit(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Normal TextEdit");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *textEdit = new QhTextEdit;
        textEdit->setObjectName("LineEditNormal");  // qss style

        ly->addWidget(label);
        ly->addWidget(textEdit);
    }

    {
        auto *label = new QhLabel("TextEdit  (length limit)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *textEdit = new QhTextEdit;
        textEdit->setObjectName("LineEditLimit");  // qss style
        textEdit->setTextMaxLenght(30);

        ly->addWidget(label);
        ly->addWidget(textEdit);
    }

    ly->addStretch(1);
}
