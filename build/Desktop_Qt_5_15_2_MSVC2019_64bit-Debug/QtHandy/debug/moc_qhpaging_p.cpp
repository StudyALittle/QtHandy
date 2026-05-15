/****************************************************************************
** Meta object code from reading C++ file 'qhpaging_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../QtHandy/components/complex/qhpaging_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhpaging_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QhPagingPrivate_t {
    QByteArrayData data[10];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhPagingPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhPagingPrivate_t qt_meta_stringdata_QhPagingPrivate = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QhPagingPrivate"
QT_MOC_LITERAL(1, 16, 17), // "onPageSizeChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 11), // "onToPrePage"
QT_MOC_LITERAL(5, 53, 12), // "onToNextPage"
QT_MOC_LITERAL(6, 66, 12), // "onToJumpPage"
QT_MOC_LITERAL(7, 79, 9), // "resetPage"
QT_MOC_LITERAL(8, 89, 22), // "onPageIndexMoreClicked"
QT_MOC_LITERAL(9, 112, 11) // "toPageIndex"

    },
    "QhPagingPrivate\0onPageSizeChanged\0\0"
    "index\0onToPrePage\0onToNextPage\0"
    "onToJumpPage\0resetPage\0onPageIndexMoreClicked\0"
    "toPageIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhPagingPrivate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    1,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void QhPagingPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhPagingPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onPageSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onToPrePage(); break;
        case 2: _t->onToNextPage(); break;
        case 3: _t->onToJumpPage(); break;
        case 4: _t->resetPage(); break;
        case 5: _t->onPageIndexMoreClicked(); break;
        case 6: _t->toPageIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QhPagingPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QhPagingPrivate.data,
    qt_meta_data_QhPagingPrivate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhPagingPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhPagingPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhPagingPrivate.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QhPagingPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
