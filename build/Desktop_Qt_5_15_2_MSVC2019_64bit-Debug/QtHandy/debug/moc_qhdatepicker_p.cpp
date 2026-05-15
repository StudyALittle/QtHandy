/****************************************************************************
** Meta object code from reading C++ file 'qhdatepicker_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../QtHandy/components/complex/qhdatepicker_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhdatepicker_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QhDatePickerItemPrivate_t {
    QByteArrayData data[16];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhDatePickerItemPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhDatePickerItemPrivate_t qt_meta_stringdata_QhDatePickerItemPrivate = {
    {
QT_MOC_LITERAL(0, 0, 23), // "QhDatePickerItemPrivate"
QT_MOC_LITERAL(1, 24, 5), // "dated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "date"
QT_MOC_LITERAL(4, 36, 20), // "pageYearMonthChanged"
QT_MOC_LITERAL(5, 57, 4), // "year"
QT_MOC_LITERAL(6, 62, 5), // "month"
QT_MOC_LITERAL(7, 68, 13), // "onToYearsPage"
QT_MOC_LITERAL(8, 82, 14), // "onToMonthsPage"
QT_MOC_LITERAL(9, 97, 12), // "onToDaysPage"
QT_MOC_LITERAL(10, 110, 7), // "onToDay"
QT_MOC_LITERAL(11, 118, 12), // "onYearAddSub"
QT_MOC_LITERAL(12, 131, 13), // "onMonthAddSub"
QT_MOC_LITERAL(13, 145, 14), // "resetPageYears"
QT_MOC_LITERAL(14, 160, 13), // "resetPageDays"
QT_MOC_LITERAL(15, 174, 22) // "updateRangeDaysChoosed"

    },
    "QhDatePickerItemPrivate\0dated\0\0date\0"
    "pageYearMonthChanged\0year\0month\0"
    "onToYearsPage\0onToMonthsPage\0onToDaysPage\0"
    "onToDay\0onYearAddSub\0onMonthAddSub\0"
    "resetPageYears\0resetPageDays\0"
    "updateRangeDaysChoosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhDatePickerItemPrivate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   77,    2, 0x0a /* Public */,
       8,    0,   78,    2, 0x0a /* Public */,
       9,    0,   79,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    0,   82,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,
      14,    2,   86,    2, 0x0a /* Public */,
      15,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,

       0        // eod
};

void QhDatePickerItemPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhDatePickerItemPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dated((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->pageYearMonthChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->onToYearsPage(); break;
        case 3: _t->onToMonthsPage(); break;
        case 4: _t->onToDaysPage(); break;
        case 5: _t->onToDay(); break;
        case 6: _t->onYearAddSub(); break;
        case 7: _t->onMonthAddSub(); break;
        case 8: _t->resetPageYears((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->resetPageDays((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->updateRangeDaysChoosed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QhDatePickerItemPrivate::*)(const QDate & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhDatePickerItemPrivate::dated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QhDatePickerItemPrivate::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhDatePickerItemPrivate::pageYearMonthChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QhDatePickerItemPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QhDatePickerItemPrivate.data,
    qt_meta_data_QhDatePickerItemPrivate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhDatePickerItemPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhDatePickerItemPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhDatePickerItemPrivate.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QhDatePickerItemPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QhDatePickerItemPrivate::dated(const QDate & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QhDatePickerItemPrivate::pageYearMonthChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_QhDatePickerPrivate_t {
    QByteArrayData data[11];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhDatePickerPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhDatePickerPrivate_t qt_meta_stringdata_QhDatePickerPrivate = {
    {
QT_MOC_LITERAL(0, 0, 19), // "QhDatePickerPrivate"
QT_MOC_LITERAL(1, 20, 5), // "dated"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "date"
QT_MOC_LITERAL(4, 32, 10), // "dateRanged"
QT_MOC_LITERAL(5, 43, 18), // "QPair<QDate,QDate>"
QT_MOC_LITERAL(6, 62, 9), // "dateRange"
QT_MOC_LITERAL(7, 72, 7), // "onDated"
QT_MOC_LITERAL(8, 80, 22), // "onPageYearMonthChanged"
QT_MOC_LITERAL(9, 103, 4), // "year"
QT_MOC_LITERAL(10, 108, 5) // "month"

    },
    "QhDatePickerPrivate\0dated\0\0date\0"
    "dateRanged\0QPair<QDate,QDate>\0dateRange\0"
    "onDated\0onPageYearMonthChanged\0year\0"
    "month"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhDatePickerPrivate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   40,    2, 0x09 /* Protected */,
       8,    2,   43,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,

       0        // eod
};

void QhDatePickerPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhDatePickerPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dated((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->dateRanged((*reinterpret_cast< const QPair<QDate,QDate>(*)>(_a[1]))); break;
        case 2: _t->onDated((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->onPageYearMonthChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QhDatePickerPrivate::*)(const QDate & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhDatePickerPrivate::dated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QhDatePickerPrivate::*)(const QPair<QDate,QDate> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhDatePickerPrivate::dateRanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QhDatePickerPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QhDatePickerPrivate.data,
    qt_meta_data_QhDatePickerPrivate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhDatePickerPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhDatePickerPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhDatePickerPrivate.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QhDatePickerPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QhDatePickerPrivate::dated(const QDate & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QhDatePickerPrivate::dateRanged(const QPair<QDate,QDate> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
