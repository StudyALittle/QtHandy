#ifndef HOMEUI_H
#define HOMEUI_H

#include <QWidget>
#include <qhpagemanager.h>
#include <qhnavbar.h>

class HomeUi : public QWidget, public QhPageManager
{
    Q_OBJECT

public:
    HomeUi(QWidget *parent = nullptr);

protected:
    QWidget *createPage(qint64 id) override;

private:
    QhNavbar *m_navbar = nullptr;
};

#endif // HOMEUI_H
