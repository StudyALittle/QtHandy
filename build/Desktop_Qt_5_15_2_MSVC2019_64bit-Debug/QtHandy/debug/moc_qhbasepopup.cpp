/****************************************************************************
** Meta object code from reading C++ file 'qhbasepopup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../QtHandy/components/customized/qhbasepopup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhbasepopup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QhBasePopup_t {
    QByteArrayData data[12];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhBasePopup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhBasePopup_t qt_meta_stringdata_QhBasePopup = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QhBasePopup"
QT_MOC_LITERAL(1, 12, 24), // "pWidgetTitleSpaceChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 26), // "pWidgetButtonsSpaceChanged"
QT_MOC_LITERAL(4, 65, 26), // "pWidgetTitleMarginsChanged"
QT_MOC_LITERAL(5, 92, 28), // "pWidgetButtonsMarginsChanged"
QT_MOC_LITERAL(6, 121, 21), // "pTitleIconSizeChanged"
QT_MOC_LITERAL(7, 143, 17), // "pWidgetTitleSpace"
QT_MOC_LITERAL(8, 161, 19), // "pWidgetButtonsSpace"
QT_MOC_LITERAL(9, 181, 19), // "pWidgetTitleMargins"
QT_MOC_LITERAL(10, 201, 21), // "pWidgetButtonsMargins"
QT_MOC_LITERAL(11, 223, 14) // "pTitleIconSize"

    },
    "QhBasePopup\0pWidgetTitleSpaceChanged\0"
    "\0pWidgetButtonsSpaceChanged\0"
    "pWidgetTitleMarginsChanged\0"
    "pWidgetButtonsMarginsChanged\0"
    "pTitleIconSizeChanged\0pWidgetTitleSpace\0"
    "pWidgetButtonsSpace\0pWidgetTitleMargins\0"
    "pWidgetButtonsMargins\0pTitleIconSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhBasePopup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00495003,
       8, QMetaType::Int, 0x00495003,
       9, QMetaType::QString, 0x00495003,
      10, QMetaType::QString, 0x00495003,
      11, QMetaType::QSize, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void QhBasePopup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhBasePopup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pWidgetTitleSpaceChanged(); break;
        case 1: _t->pWidgetButtonsSpaceChanged(); break;
        case 2: _t->pWidgetTitleMarginsChanged(); break;
        case 3: _t->pWidgetButtonsMarginsChanged(); break;
        case 4: _t->pTitleIconSizeChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QhBasePopup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhBasePopup::pWidgetTitleSpaceChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QhBasePopup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhBasePopup::pWidgetButtonsSpaceChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QhBasePopup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhBasePopup::pWidgetTitleMarginsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QhBasePopup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhBasePopup::pWidgetButtonsMarginsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QhBasePopup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhBasePopup::pTitleIconSizeChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QhBasePopup *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getWidgetTitleSpace(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getWidgetButtonsSpace(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getWidgetTitleMargins(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getWidgetButtonsMargins(); break;
        case 4: *reinterpret_cast< QSize*>(_v) = _t->getTitleIconSize(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QhBasePopup *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidgetTitleSpace(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setWidgetButtonsSpace(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setWidgetTitleMargins(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setWidgetButtonsMargins(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setTitleIconSize(*reinterpret_cast< QSize*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QhBasePopup::staticMetaObject = { {
    QMetaObject::SuperData::link<QhFramelessDialog::staticMetaObject>(),
    qt_meta_stringdata_QhBasePopup.data,
    qt_meta_data_QhBasePopup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhBasePopup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhBasePopup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhBasePopup.stringdata0))
        return static_cast<void*>(this);
    return QhFramelessDialog::qt_metacast(_clname);
}

int QhBasePopup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QhFramelessDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QhBasePopup::pWidgetTitleSpaceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QhBasePopup::pWidgetButtonsSpaceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QhBasePopup::pWidgetTitleMarginsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QhBasePopup::pWidgetButtonsMarginsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QhBasePopup::pTitleIconSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
