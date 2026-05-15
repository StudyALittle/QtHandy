#ifndef QHLABEL_P_H
#define QHLABEL_P_H

#include "qhlabel.h"

class QhLabelPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLabelPrivate)

public:
    explicit QhLabelPrivate() {}

    void resetText(QhLabel *label);
    void drawRequired(QhLabel *label);

    QString placeholderText;

    // real text
    QString text;
    // It is effective when WordWrap is set to true
    int maxLine = 1;
    // Whether to display ellipsis when the text is too long
    bool bEllipsis = false;
    // placeholder pattern
    QhLabel::RequiredMode requiredMode = QhLabel::NoRequired;

    QString requiredPlaceholderText = "  ";
    QString requiredMarkText = "*";
};

#endif // QHLABEL_P_H
