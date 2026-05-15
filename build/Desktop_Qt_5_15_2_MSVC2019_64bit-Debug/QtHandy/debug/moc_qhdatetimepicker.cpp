/****************************************************************************
** Meta object code from reading C++ file 'qhdatetimepicker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../QtHandy/components/complex/qhdatetimepicker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhdatetimepicker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QhDateTimePicker_t {
    QByteArrayData data[7];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhDateTimePicker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhDateTimePicker_t qt_meta_stringdata_QhDateTimePicker = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QhDateTimePicker"
QT_MOC_LITERAL(1, 17, 9), // "datetimed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "dateTime"
QT_MOC_LITERAL(4, 37, 14), // "datetimeRanged"
QT_MOC_LITERAL(5, 52, 26), // "QPair<QDateTime,QDateTime>"
QT_MOC_LITERAL(6, 79, 7) // "dtrange"

    },
    "QhDateTimePicker\0datetimed\0\0dateTime\0"
    "datetimeRanged\0QPair<QDateTime,QDateTime>\0"
    "dtrange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhDateTimePicker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDateTime,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void QhDateTimePicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhDateTimePicker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->datetimed((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 1: _t->datetimeRanged((*reinterpret_cast< const QPair<QDateTime,QDateTime>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QhDateTimePicker::*)(const QDateTime & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhDateTimePicker::datetimed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QhDateTimePicker::*)(const QPair<QDateTime,QDateTime> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhDateTimePicker::datetimeRanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QhDateTimePicker::staticMetaObject = { {
    QMetaObject::SuperData::link<QhFloating::staticMetaObject>(),
    qt_meta_stringdata_QhDateTimePicker.data,
    qt_meta_data_QhDateTimePicker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhDateTimePicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhDateTimePicker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhDateTimePicker.stringdata0))
        return static_cast<void*>(this);
    return QhFloating::qt_metacast(_clname);
}

int QhDateTimePicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QhFloating::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QhDateTimePicker::datetimed(const QDateTime & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QhDateTimePicker::datetimeRanged(const QPair<QDateTime,QDateTime> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
