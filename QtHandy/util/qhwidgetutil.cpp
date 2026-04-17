#include <QApplication>
#include <QStyle>
#include <QLayout>
#include <QLayoutItem>
#include <QPainter>
#include <QStyleOption>
#include "qhwidgetutil.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#pragma comment (lib,"User32.lib")
#endif

void QhWidgetUtil::moveToScreenCenter(QWidget *w, QScreen *screen)
{
    if (!screen)
        screen = screenUnderWidget(w);

    auto screenRt = screen->availableGeometry();

    // 居中显示
    int x = (screenRt.width() - w->width()) / 2;
    int y = (screenRt.height() - w->height()) / 2;
    if (y < 0)
        y = 0;
    w->move(x, y);
}

QWidget *QhWidgetUtil::topParentWidget(QWidget *w)
{
    auto *pw = w->parentWidget();
    if (pw && pw->parentWidget())
        return topParentWidget(pw);
    else if (pw)
        return pw;

    return w;
}

bool QhWidgetUtil::isParentWidget(QWidget *parent, QWidget *w)
{
    if (parent == w)
        return true;

    if (w->parentWidget()) {
        if (w->parentWidget() == parent)
            return true;

        return isParentWidget(parent, w->parentWidget());
    }
    return false;
}

QScreen *QhWidgetUtil::screenUnderWidget(QWidget *w)
{
    QScreen *screen = nullptr;
    if (w) {
        auto *topW = topParentWidget(w);
        auto *win = topW->windowHandle();
        if (!win) {
            screen = QApplication::primaryScreen();
        } else {
            screen = win->screen();
        }
    }

    if (!screen)
        screen = QApplication::primaryScreen();

    return screen;
}

void QhWidgetUtil::activateWindow(QWidget *w)
{
    if (w->isMinimized()) {
#ifdef Q_OS_WIN
        auto hwnd = (HWND)(w->window()->winId());
        ::ShowWindow(hwnd, SW_SHOWNOACTIVATE);
        ::ShowWindow(hwnd, SW_SHOW);
#else
        w->showNormal();
#endif
    }

    w->raise();
    w->show();
    w->activateWindow();
}

void QhWidgetUtil::updateQssStyle(QWidget *w)
{
    w->style()->unpolish(w);
    w->style()->polish(w);
    w->update();
}

void QhWidgetUtil::updateQssStyles(const QList<QWidget *> &ws)
{
    foreach (auto *w, ws)
        updateQssStyle(w);
}

QList<QWidget *> QhWidgetUtil::clearLayout(
        QLayout *layout, bool bDelWidget, const QList<QLayout *> &ignoreDelLys)
{
    QList<QWidget*> rts;
    if (!layout)
        return rts;

    QLayoutItem *child = layout->takeAt(0);
    while (child) {
        auto *w = child->widget();
        auto *ly = child->layout();
        if(w) {
            // setParent为nullptr，防止删除之后界面不消失
            if (bDelWidget) {
                w->setParent(nullptr);
                delete w;
            }
            rts.append(w);
        } else if (ly) {
            if (!ignoreDelLys.contains(ly)) {
                auto srts = clearLayout(ly, bDelWidget, ignoreDelLys);
                ly->deleteLater();
                rts.append(srts);
            } else {
                child = layout->takeAt(0);
                continue;
            }
        }
        delete child;
        child = layout->takeAt(0);
    }
    return rts;
}

QList<QWidget *> QhWidgetUtil::layoutWidgets(QLayout *layout)
{
    QList<QWidget*> rts;
    if (!layout)
        return rts;

    int cnt = layout->count();
    for (int n = 0; n < cnt; ++n) {
        QLayoutItem *child = layout->itemAt(n);

        auto *w = child->widget();
        auto *ly = child->layout();
        if(w) {
            rts.append(w);
        } else if (ly) {
            auto ws = layoutWidgets(ly);
            rts.append(ws);
        }
    }
    return rts;
}

void QhWidgetUtil::paintEventQssStyleReset(QWidget *w)
{
    QStyleOption opt;
    opt.initFrom(w);
    QPainter p(w);
    w->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, w);
}

QPoint QhWidgetUtil::posAtTopWidget(QWidget *w, QWidget **topw)
{
    auto *pw = w->parentWidget();
    if (!pw) {  // 没有父类
        if (topw)
            *topw = w;
        return QPoint(0, 0);
    } else {    // 有父类
        // 自己的位置（相对于父类）
        QPoint pos = w->pos();
        // 相对于父类-》父类的位置
        QPoint ppos = posAtTopWidget(pw, topw);
        // 加上父类-》父类的位置
        pos += ppos;
        return pos;
    }
}

void QhWidgetUtil::hideRetainSize(QWidget *w)
{
    QSizePolicy retain = w->sizePolicy();
    retain.setRetainSizeWhenHidden(true);
    w->setSizePolicy(retain);
    w->hide();
}

void QhWidgetUtil::setButtonFocus(QAbstractButton *btn, const QList<QKeySequence> &keySequences)
{
    btn->setFocus();
    foreach (auto key, keySequences)
        btn->setShortcut(key);
}

void QhWidgetUtil::layoutDestroyItemAt(QLayout *ly, int index)
{
    auto *item = ly->itemAt(index);
    if (item) {
        ly->removeItem(item);
        delete item;
    }
}
