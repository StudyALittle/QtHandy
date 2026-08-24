#include "qhmcombobox.h"
#include "qhmcombobox_p.h"
#include <QCheckBox>
#include <QGuiApplication>
#include <QStyleHints>

#pragma execution_character_set("utf-8")

QhMComboBox::QhMComboBox(QWidget *parent):
    QhComboBox(parent), d(new QhMComboBoxPrivate(this))
{
    d->init();
}

QhMComboBox::~QhMComboBox()
{

}

void QhMComboBox::addItem(const QString &text, const QVariant &userData)
{
    d->listWidget->item(0)->setHidden(d->items.size() < d->showSearchEditCount);
    d->items.append({text, userData});
    d->addShowItem(text, userData);
}

void QhMComboBox::addItems(const QStringList &texts)
{
    for (auto &text: texts)
        addItem(text);
}

void QhMComboBox::setSelects(const QStringList &texts)
{
    d->selectItemNames = texts;
    for (auto &checkBox: d->checkBoxs) {
        if (d->selectItemNames.contains(checkBox->text()))
            checkBox->setChecked(true);
    }
}

QStringList QhMComboBox::selectTexts() const
{
    return d->selectItemNames;
}

void QhMComboBox::hidePopup()
{
    this->view()->scrollTo(this->model()->index(0, 0));
    d->lineEditSearch->clear();
    if (d->eTimer.isValid())
        d->eTimer.restart();
    else
        d->eTimer.start();
    QhComboBox::hidePopup();
}

void QhMComboBox::showPopup()
{
    QhComboBox::showPopup();
}

QhMComboBoxPrivate::QhMComboBoxPrivate(QhMComboBox *pbox):
    mComboBox(pbox)
{

}

QhMComboBoxPrivate::~QhMComboBoxPrivate()
{

}

void QhMComboBoxPrivate::init()
{
    lineEditText = new QhLineEdit;
    lineEditText->setObjectName("lineEditText");
    lineEditText->setReadOnly(true);
    lineEditText->installEventFilter(this);
    mComboBox->setLineEdit(lineEditText);

    listWidget  = new QListWidget(mComboBox);

    lineEditSearch = new QhLineEdit;
    lineEditSearch->setPlaceholderText(tr("搜索文本"));
    lineEditSearch->setClearButtonEnabled(true);
    // lineEditSearch->installEventFilter(this);
    connect(lineEditSearch, &QLineEdit::textChanged, this, &QhMComboBoxPrivate::onTextChanged);

    auto *serarchItem = new QListWidgetItem;
    serarchItem->setFlags(serarchItem->flags() & ~ Qt::ItemIsSelectable);
    listWidget->addItem(serarchItem);
    listWidget->setItemWidget(serarchItem, lineEditSearch);

    mComboBox->setModel(listWidget->model());
    mComboBox->setView(listWidget);

    mComboBox->setMaxVisibleItems(10);
}

bool QhMComboBoxPrivate::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == lineEditText
            && !QGuiApplication::styleHints()->setFocusOnTouchRelease()
            && event->type() == QEvent::MouseButtonPress
            && !mComboBox->view()->parentWidget()->isVisible()) {
        auto *mEvent = static_cast<QMouseEvent*>(event);
        if (mEvent->button() == Qt::LeftButton && eTimer.hasExpired(50)) {
            mComboBox->showPopup();
            event->ignore();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void QhMComboBoxPrivate::clearItems()
{
    int count = listWidget->count();
    for (int n = 1; n < count; ++n) {
        auto *item = listWidget->item(1);
        listWidget->removeItemWidget(item);
        delete listWidget->takeItem(1);
    }
    checkBoxs.clear();
}

void QhMComboBoxPrivate::setShowItems(const QList<QPair<QString, QVariant> > &items)
{
    for (auto &item: items)
        addShowItem(item.first, item.second);
}

void QhMComboBoxPrivate::addShowItem(const QString &text, const QVariant &userData)
{
    auto *item = new QListWidgetItem;
    item->setData(Qt::UserRole, userData);
    item->setFlags(item->flags() & ~ Qt::ItemIsSelectable);

    auto *checkBox = new QhCheckBox(text);
    checkBox->setSelectOutsideText(true);

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
    checkBox->setSizePolicy(sizePolicy);

    if (selectItemNames.contains(text))
        checkBox ->setChecked(true);

    connect(checkBox, &QCheckBox::stateChanged,
        this, &QhMComboBoxPrivate::onItemStateChanged);

    listWidget->addItem(item);
    listWidget->setItemWidget(item, checkBox);
    checkBoxs.append(checkBox);
}

void QhMComboBoxPrivate::onItemStateChanged(int state)
{
    Q_UNUSED(state)

    auto findCheckBox = [this](const QString &name) -> QhCheckBox* {
        for (auto &cbox: checkBoxs) {
            if (cbox->text() == name) {
                return cbox;
            }
        }
        return nullptr;
    };

    auto oldSelects = selectItemNames;
    selectItemNames.clear();
    for (auto &item: items) {
        auto *cbox = findCheckBox(item.first);
        if (!cbox) {
            if (oldSelects.contains(item.first)) {
                selectItemNames.append(item.first);
            }
        } else if (cbox->isChecked()) {
            selectItemNames.append(cbox->text());
        }
    }
    lineEditText->setText(selectItemNames.join(showSeparator));
}

void QhMComboBoxPrivate::onTextChanged(const QString &text)
{
    clearItems();
    if (text.isEmpty()) {
        setShowItems(items);
        return;
    }

    QList<QPair<QString, QVariant> > showItems;
    for (auto &item: items) {
        if (item.first.contains(text)) {
            showItems.append(item);
        }
    }
    setShowItems(showItems);
}
