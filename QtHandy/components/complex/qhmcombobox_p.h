#ifndef QHMCOMBOBOX_P_H
#define QHMCOMBOBOX_P_H

#include <QListWidget>
#include <QList>
#include <QElapsedTimer>
#include "qhlineedit.h"
#include "qhmcombobox.h"
#include "qhcheckbox.h"

class QhMComboBoxPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhMComboBoxPrivate)

public:
    QhMComboBoxPrivate(QhMComboBox *pbox);
    ~QhMComboBoxPrivate();

    void init();
    bool eventFilter(QObject *obj, QEvent *event) override;
    void clearItems();
    void setShowItems(const QList<QPair<QString, QVariant>> &items);
    void addShowItem(const QString &text, const QVariant &userData = QVariant());

    QElapsedTimer eTimer;

    QhMComboBox *mComboBox;
    QListWidget *listWidget = nullptr;
    QhLineEdit *lineEditSearch = nullptr;
    QhLineEdit *lineEditText = nullptr;

    QList<QhCheckBox*> checkBoxs;
    QStringList selectItemNames;

    QString showSeparator = "/";
    int showSearchEditCount = 10;
    QList<QPair<QString, QVariant>> items;

public slots:
    void onItemStateChanged(int state);
    void onTextChanged(const QString &text);
};

#endif // QHMCOMBOBOX_P_H
