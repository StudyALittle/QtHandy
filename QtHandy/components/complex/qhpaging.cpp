#include "qhpaging.h"
#include "qhpaging_p.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

QhPaging::QhPaging(QWidget *parent):
    QWidget(parent),
    d(new QhPagingPrivate(this))
{
    d->init();
}

QhPaging::~QhPaging()
{

}

QList<QPair<int, QString> > QhPaging::pageSizeList()
{
    return d->pageSizeList;
}

int QhPaging::totalNumber()
{
    return d->nTotalNumber;
}

int QhPaging::totalPage()
{
    return d->nTotalPage;
}

int QhPaging::pageSize()
{
    return d->nPageSize;
}

int QhPaging::pageIndex()
{
    return d->nPageIndex;
}

int QhPaging::getButtonPageMinWidth()
{
    return d->nButtonPageMinWidth;
}

void QhPaging::setPageSizeList(const QList<QPair<int, QString> > &lists)
{
    int oldIndex = d->comboxPageSize->currentIndex();
    int oldPageSize =
            (oldIndex >= 0 && oldIndex < d->pageSizeList.size()) ?
                d->pageSizeList.at(oldIndex).first : -1;

    d->pageSizeList = lists;
    while (d->comboxPageSize->count()) {
        d->comboxPageSize->removeItem(0);
    }

    int newIndex = 0;
    QStringList labels;
    for (int n = 0; n < lists.size(); ++n) {
        auto item = lists.at(n);
        if (oldPageSize == item.first)
            newIndex = n;
        labels.append(item.second);
    }
    d->comboxPageSize->addItems(labels);
    d->comboxPageSize->setCurrentIndex(newIndex);
}

void QhPaging::setTotalNumber(int n)
{
    d->nTotalNumber = n;
    d->labelTotalNumber->setText(tr("Total %1 records").arg(d->nTotalNumber));

    int totalPage = d->nTotalNumber / pageSize();
    if (d->nTotalNumber % pageSize())
        ++totalPage;

    if (totalPage <= 0)
        totalPage = 1;

    setTotalPage(totalPage);

    // 选中第一页，上一页按钮禁用
    // 选中最后一页，下一页按钮禁用
    d->pushButtonPrePage->setEnabled(d->nPageIndex > 1);
    d->pushButtonNextPage->setEnabled(d->nPageIndex < totalPage);
}

void QhPaging::setTotalPage(int n)
{
    d->nTotalPage = n;
    d->resetPage();
}

void QhPaging::setPageSize(int n)
{
    d->nPageSize = n;
    for (int i = 0; i < d->pageSizeList.size(); ++i) {
        if (d->pageSizeList.at(i).first == n) {
            d->comboxPageSize->setCurrentIndex(i);
            break;
        }
    }
    setTotalNumber(d->nTotalNumber);
}

void QhPaging::setPageIndex(int n)
{
    d->toPageIndex(n);
}

void QhPaging::setButtonPageMinWidth(int width)
{
    d->nButtonPageMinWidth = width;
    for (int n = 0; n < d->nMaxPageChooseSize; ++n) {
        auto *btn = d->buttonPages[n];
        d->setButtonNumber(btn, n + 1);
    }
}

QhPagingPrivate::QhPagingPrivate(QhPaging *p):
    p(p)
{

}

QhPagingPrivate::~QhPagingPrivate()
{

}

void QhPagingPrivate::init()
{
    p->setAttribute(Qt::WA_StyledBackground);

    initWidgets();

    connect(buttonMoreBegin, &QPushButton::clicked, this, &QhPagingPrivate::onPageIndexMoreClicked);
    connect(buttonMoreEnd, &QPushButton::clicked, this, &QhPagingPrivate::onPageIndexMoreClicked);
    connect(pushButtonPrePage, &QPushButton::clicked, this, &QhPagingPrivate::onToPrePage);
    connect(pushButtonNextPage, &QPushButton::clicked, this, &QhPagingPrivate::onToNextPage);
    connect(pushButtonToPage, &QPushButton::clicked, this, &QhPagingPrivate::onToJumpPage);
    connect(lineEditPageJump, &QLineEdit::returnPressed, this, &QhPagingPrivate::onToJumpPage);
    connect(comboxPageSize, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QhPagingPrivate::onPageSizeChanged);

    p->setPageSizeList({
        {5, tr("5 items per page")}, {10, tr("10 items per page")},
        {15, tr("15 items per page")}, {20, tr("20 items per page")},
        {30, tr("30 items per page")}, {50, tr("50 items per page")} });
    p->setPageSize(20);

    p->setTotalNumber(0);
    toPageIndex(1);

    p->setButtonPageMinWidth(nButtonPageMinWidth);
}

void QhPagingPrivate::initWidgets()
{
    /// [Total of 10 data entries] [<][1][...][4][5][6][7][8][...][100] jump[ 10 ]page[jump] [ 5count/page V ]

    labelTotalNumber = new QhLabel;             // Total number of data entries
    lineEditPageJump = new QhLineEdit;          // Page redirection lineEdit
    comboxPageSize = new QhComboBox;            // Page number switch combo box
    buttonMoreBegin = new QPushButton;   // begin more button, "..."
    buttonMoreEnd = new QPushButton;     // end more button, "..."
    pushButtonPrePage = new QPushButton;        // previous Page, "<"
    pushButtonNextPage = new QPushButton;       // next page, ">"
    pushButtonToPage = new QPushButton;         // Page jump button

    labelTotalNumber->setObjectName("LabelTotalNumber");
    pushButtonPrePage->setObjectName("ButtonPrePage");
    pushButtonNextPage->setObjectName("ButtonNextPage");
    buttonMoreBegin->setObjectName("ButtonMoreBegin");
    buttonMoreEnd->setObjectName("ButtonMoreEnd");
    pushButtonToPage->setObjectName("ButtonToPage");

    buttonMoreBegin->setMaximumWidth(42);
    buttonMoreEnd->setMaximumWidth(42);

    buttonPages.resize(nMaxPageChooseSize);     // page button, "1,2,3,4,5,6"
    for (int n = 0; n < nMaxPageChooseSize; ++n) {
        auto *btn = new QPushButton;
        if (n == 0)
            btn->setText("1");
        btn->setObjectName("ButtonIndex");
        btn->setCheckable(true);

        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            if (!buttonPageIndexs.contains(btn))
                return;

            toPageIndex(buttonPageIndexs[btn]);
        });

        buttonPages[n] = btn;
        buttonGroup.addButton(btn);
    }

    // layout
    auto *ly = new QHBoxLayout(p);

    // page buttons
    auto *lyPages = new QHBoxLayout;
    lyPages->addWidget(pushButtonPrePage);
    lyPages->addWidget(buttonPages.first());
    lyPages->addWidget(buttonMoreBegin);
    for (int n = 1; n < nMaxPageChooseSize - 1; ++n) {
        lyPages->addWidget(buttonPages[n]);
    }
    lyPages->addWidget(buttonMoreEnd);
    lyPages->addWidget(buttonPages.last());
    lyPages->addWidget(pushButtonNextPage);
    lyPages->setContentsMargins(0, 0, 0, 0);
    lyPages->setSpacing(6);

    // jump
    auto *lyJump = new QHBoxLayout;
    lyJump->addWidget(new QhLabel(tr("jump to")));
    lyJump->addWidget(lineEditPageJump);
    lyJump->addWidget(new QhLabel(tr("page")));
    lyJump->setContentsMargins(0, 0, 0, 0);
    lyJump->setSpacing(2);

    ly->addStretch(1);
    ly->addWidget(labelTotalNumber);
    ly->addLayout(lyPages);
    ly->addLayout(lyJump);
    ly->addWidget(comboxPageSize);
    ly->setContentsMargins(0, 0, 0, 0);
    ly->setSpacing(10);
}

void QhPagingPrivate::setButtonNumber(QPushButton *btn, int num)
{
    btn->setText(QString::number(num));
    buttonPageIndexs[btn] = num;

    int fixedWeight = nButtonPageMinWidth;
    QString calcText;
    if (num <= 99) {
        if (btn->width() != fixedWeight)
            btn->setFixedWidth(fixedWeight);
        return;
    } else if (num <= 999) {
        calcText = "999";
    } else if (num <= 9999) {
        calcText = "9999";
    } else if (num <= 99999) {
        calcText = "99999";
    } else if (num <= 999999) {
        calcText = "999999";
    } else if (num <= 9999999) {
        calcText = "9999999";
    } else if (num <= 99999999) {
        calcText = "99999999";
    } else if (num <= 999999999) {
        calcText = "999999999";
    } else {
        calcText = "9999999999";
    }

    QFontMetrics fm(btn->font());
    fixedWeight = fm.horizontalAdvance(calcText) + 8 * 2;

    if (btn->width() != fixedWeight)
        btn->setFixedWidth(fixedWeight);
}

void QhPagingPrivate::onPageSizeChanged(int index)
{
    if (index < 0 || index >= pageSizeList.size())
        return;

    int pageSize = pageSizeList.at(index).first;
    if (pageSize == nPageSize)
        return;

    nPageSize = pageSize;
    emit p->pageSizeChanged(pageSize);
}

void QhPagingPrivate::onToPrePage()
{
    toPageIndex(nPageIndex - 1);
}

void QhPagingPrivate::onToNextPage()
{
    toPageIndex(nPageIndex + 1);
}

void QhPagingPrivate::onToJumpPage()
{
    if (lineEditPageJump->text().isEmpty())
        return;

    toPageIndex(lineEditPageJump->text().toInt());
}

void QhPagingPrivate::resetPage()
{
    if (nTotalPage <= nMaxPageChooseSize) {
        // 页面数量小于最大展示页码
        buttonMoreBegin->setVisible(false);
        buttonMoreEnd->setVisible(false);

        for (int n = 0; n < nMaxPageChooseSize; ++n) {
            auto *btn = buttonPages[n];
            if (n < nTotalPage) {
                btn->setVisible(true);
                setButtonNumber(btn, n + 1);

                if (nPageIndex == n + 1)
                    btn->setChecked(true);
            } else {
                btn->setVisible(false);
            }
        }
    } else {
        // 页面数量大于最大展示页码
        // int halfNum = (maxPageChooseSize - 2) / 2;
        // bool bMoreLeft = (pageIndex - halfNum - 1) > 1;
        // bool bMoreRight = (pageIndex + halfNum + 1) < totalPage;
        int halfNum = nMaxPageChooseSize / 2;
        bool bMoreLeft = nPageIndex - 1 > halfNum;
        bool bMoreRight = nTotalPage - nPageIndex > halfNum;

        // 显示全部页面切换按钮
        foreach (auto *btn, buttonPages) {
            btn->setVisible(true);
        }

        setButtonNumber(buttonPages.first(), 1);
        setButtonNumber(buttonPages.last(), nTotalPage);

        if (bMoreLeft && bMoreRight) {
            buttonMoreBegin->setVisible(true);
            buttonMoreEnd->setVisible(true);

            // 选中按钮在中间
            for (int n = 0; n < halfNum; ++n) {
                if (n == 0) {
                    auto *btn = buttonPages[halfNum];
                    setButtonNumber(btn, nPageIndex);
                    btn->setChecked(true);
                } else {
                    auto *btnPre = buttonPages[halfNum - n];
                    setButtonNumber(btnPre, nPageIndex - n);

                    auto *btnNext = buttonPages[halfNum + n];
                    setButtonNumber(btnNext, nPageIndex + n);
                }
            }
        } else if (bMoreLeft) {
            buttonMoreBegin->setVisible(true);
            buttonMoreEnd->setVisible(false);

            // 右边不显示更多
            for (int n = nMaxPageChooseSize - 1, m = 0; n > 0; --n, ++m) {
                auto *btn = buttonPages[n];
                int pageIndex = nTotalPage - m;
                setButtonNumber(btn, pageIndex);

                if (pageIndex == nPageIndex)
                    btn->setChecked(true);
            }
        } else if (bMoreRight) {
            buttonMoreBegin->setVisible(false);
            buttonMoreEnd->setVisible(true);

            // 左边不显示更多
            for (int n = 0; n < nMaxPageChooseSize - 1; ++n) {
                auto *btn = buttonPages[n];
                int pageIndex = 1 + n;
                setButtonNumber(btn, pageIndex);

                if (pageIndex == nPageIndex)
                    btn->setChecked(true);
            }
        }
    }
}

void QhPagingPrivate::onPageIndexMoreClicked()
{
    if (sender() == buttonMoreBegin) {
        int pageIndex = nPageIndex - (nMaxPageChooseSize - 2);
        if (pageIndex < 1)
            pageIndex = 1;
        toPageIndex(pageIndex);
    } else {
        int pageIndex = nPageIndex + (nMaxPageChooseSize - 2);
        if (pageIndex > nTotalPage)
            pageIndex = nTotalPage;
        toPageIndex(pageIndex);
    }
}

void QhPagingPrivate::toPageIndex(int index)
{
    if (index < 1 || index > nTotalPage)
        return;

    // 选中第一页，上一页按钮禁用
    // 选中最后一页，下一页按钮禁用
    pushButtonPrePage->setEnabled(index > 1);
    pushButtonNextPage->setEnabled(index < nTotalPage);

    if (nPageIndex != index) {
        nPageIndex = index;
        emit p->pageIndexChanged(index);
    }
    resetPage();
}

