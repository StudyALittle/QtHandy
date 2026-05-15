/****************************************************************************
** Meta object code from reading C++ file 'dirtoolgroupui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../DirFileTool/ui/dirtoolgroupui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dirtoolgroupui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DirToolGroupUi_t {
    QByteArrayData data[12];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DirToolGroupUi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DirToolGroupUi_t qt_meta_stringdata_DirToolGroupUi = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DirToolGroupUi"
QT_MOC_LITERAL(1, 15, 19), // "deleteGroupFinished"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 1), // "b"
QT_MOC_LITERAL(4, 38, 17), // "editGroupFinished"
QT_MOC_LITERAL(5, 56, 13), // "onDeleteGroup"
QT_MOC_LITERAL(6, 70, 11), // "onEditGroup"
QT_MOC_LITERAL(7, 82, 8), // "onAddDir"
QT_MOC_LITERAL(8, 91, 10), // "onOpenDirs"
QT_MOC_LITERAL(9, 102, 11), // "onDeleteDir"
QT_MOC_LITERAL(10, 114, 9), // "onOpenDir"
QT_MOC_LITERAL(11, 124, 9) // "onEditDir"

    },
    "DirToolGroupUi\0deleteGroupFinished\0\0"
    "b\0editGroupFinished\0onDeleteGroup\0"
    "onEditGroup\0onAddDir\0onOpenDirs\0"
    "onDeleteDir\0onOpenDir\0onEditDir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DirToolGroupUi[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   65,    2, 0x08 /* Private */,
       6,    0,   66,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DirToolGroupUi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DirToolGroupUi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleteGroupFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->editGroupFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onDeleteGroup(); break;
        case 3: _t->onEditGroup(); break;
        case 4: _t->onAddDir(); break;
        case 5: _t->onOpenDirs(); break;
        case 6: _t->onDeleteDir(); break;
        case 7: _t->onOpenDir(); break;
        case 8: _t->onEditDir(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DirToolGroupUi::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirToolGroupUi::deleteGroupFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DirToolGroupUi::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirToolGroupUi::editGroupFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DirToolGroupUi::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DirToolGroupUi.data,
    qt_meta_data_DirToolGroupUi,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DirToolGroupUi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DirToolGroupUi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DirToolGroupUi.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DirToolGroupUi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DirToolGroupUi::deleteGroupFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DirToolGroupUi::editGroupFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
