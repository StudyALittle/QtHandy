#ifndef POPUPWAY2_H
#define POPUPWAY2_H

#include <QWidget>
#include <qhbasepopup.h>
#include <qhbasepopupcontent.h>

namespace Ui {
class PopupWay2;
}

class PopupWay2 : public QhBasePopupContent
{
    Q_OBJECT

public:
    explicit PopupWay2(QWidget *parent = nullptr);
    ~PopupWay2();

    static bool exec(const QString &title);

protected:
    bool afterButtonOk() override;
    bool afterButtonCancel() override;
    bool afterButtonClose() override;

private:
    Ui::PopupWay2 *ui;
};

#endif // POPUPWAY2_H
