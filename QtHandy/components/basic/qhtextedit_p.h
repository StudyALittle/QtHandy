#ifndef QHTEXTEDIT_P_H
#define QHTEXTEDIT_P_H

#include "qhtextedit.h"

class QhTextEditPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhTextEditPrivate)

public:
    QhTextEditPrivate(QhTextEdit *p);
    ~QhTextEditPrivate();

    void init();
    void resetLabelPos(const QSize &size);
    void resetLabelText();

    QhTextEdit *ptr;
    int textMaxLenght = 0;

    QLabel *label = nullptr;
    QMargins labelMargins = QMargins(0, 0, 0, 0);

public slots:
    void onTextChanged();
};

#endif // QHTEXTEDIT_P_H
