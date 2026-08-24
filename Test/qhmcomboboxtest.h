#ifndef QHMCOMBOBOXTEST_H
#define QHMCOMBOBOXTEST_H

#include <QWidget>

namespace Ui {
class QhMComboBoxTest;
}

class QhMComboBoxTest : public QWidget
{
    Q_OBJECT

public:
    explicit QhMComboBoxTest(QWidget *parent = nullptr);
    ~QhMComboBoxTest();

private:
    Ui::QhMComboBoxTest *ui;
};

#endif // QHMCOMBOBOXTEST_H
