#ifndef QHPAGING_P_H
#define QHPAGING_P_H

#include <QMap>
#include <QButtonGroup>
#include "qhpaging.h"

class QhPagingPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhPagingPrivate)

public:
    QhPagingPrivate(QhPaging *p);
    ~QhPagingPrivate();

    QhPaging *p = nullptr;

    int nButtonPageMinWidth = 32;

    QhLabel *labelTotalNumber = nullptr;         // Total number of data entries
    QhLineEdit *lineEditPageJump = nullptr;     // Page redirection lineEdit
    QhComboBox *comboxPageSize = nullptr;       // Page number switch combo box
    QVector<QPushButton*> buttonPages;          // page button, "1,2,3,4,5,6"
    QPushButton *buttonMoreBegin = nullptr;     // begin more button, "..."
    QPushButton *buttonMoreEnd = nullptr;       // end more button, "..."
    QPushButton *pushButtonPrePage = nullptr;   // previous Page, "<"
    QPushButton *pushButtonNextPage = nullptr;  // next page, ">"
    QPushButton *pushButtonToPage = nullptr;    // Page jump button

    QList<QPair<int, QString> > pageSizeList;   // Number per page selection list
    int nTotalNumber = 0;  // Total number of data entries
    int nTotalPage = 1;    // Total Pages (minimum of 1)
    int nPageSize = 0;     // Quantity per page
    int nPageIndex = 1;    // Selected page index (starting from 1)

    // 最多显示几个页面切换按钮（最大值为19，最小值为5，必须为奇数）
    // How many page switching buttons should be displayed at most (the maximum value is 19, the minimum value is 5, and it must be an odd number)
    int nMaxPageChooseSize = 7;

    QPushButton *lastChooseButton = nullptr;  // Previous selected page button
    QMap<QPushButton*, int> buttonPageIndexs; // The page corresponding to the button 记录按钮对应的页面
    QButtonGroup buttonGroup;

public:
    void init();
    void initWidgets();
    void setButtonNumber(QPushButton *btn, int number);

public slots:
    void onPageSizeChanged(int index);
    void onToPrePage();
    void onToNextPage();
    void onToJumpPage();

    void resetPage();
    void onPageIndexMoreClicked();
    void toPageIndex(int index);
};

#endif // QHPAGING_P_H
