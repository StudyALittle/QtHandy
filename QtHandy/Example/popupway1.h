#ifndef POPUPWAY1_H
#define POPUPWAY1_H

#include <qhbasepopup.h>

class PopupWay1: public QhBasePopup
{
    Q_OBJECT

public:
    PopupWay1(const QString &title, QWidget *parent = nullptr);

protected:
    bool afterButtonOk() override;
    bool afterButtonCancel() override;
    bool afterButtonClose() override;
};

#endif // POPUPWAY1_H
