#include "demopaging.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <qhpaging.h>
#include <qhlineedit.h>

DemoPaging::DemoPaging(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);

    {
        auto *topLy = new QHBoxLayout;
        auto *label = new QhLabel(tr("total number:"));
        auto *lineEdit = new QhLineEdit;
        lineEdit->setText("10");
        auto *button = new QPushButton(tr("SET"));
        topLy->addStretch(1);
        topLy->addWidget(label);
        topLy->addWidget(lineEdit);
        topLy->addWidget(button);
        ly->addLayout(topLy);

        auto *paging = new QhPaging;
        ly->addWidget(paging);

        connect(button, &QPushButton::clicked, this, [=]() {
            paging->setTotalNumber(lineEdit->text().toInt());
        });
    }

    ly->addStretch(1);
}
