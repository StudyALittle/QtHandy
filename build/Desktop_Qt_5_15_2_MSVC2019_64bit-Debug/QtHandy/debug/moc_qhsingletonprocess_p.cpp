/****************************************************************************
** Meta object code from reading C++ file 'qhsingletonprocess_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../QtHandy/core/qhsingletonprocess_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhsingletonprocess_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QhSingletonProcessPrivate_t {
    QByteArrayData data[5];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhSingletonProcessPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhSingletonProcessPrivate_t qt_meta_stringdata_QhSingletonProcessPrivate = {
    {
QT_MOC_LITERAL(0, 0, 25), // "QhSingletonProcessPrivate"
QT_MOC_LITERAL(1, 26, 11), // "recvMessage"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 4), // "type"
QT_MOC_LITERAL(4, 44, 4) // "data"

    },
    "QhSingletonProcessPrivate\0recvMessage\0"
    "\0type\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhSingletonProcessPrivate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

       0        // eod
};

void QhSingletonProcessPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhSingletonProcessPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recvMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QhSingletonProcessPrivate::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhSingletonProcessPrivate::recvMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QhSingletonProcessPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QhSingletonProcessPrivate.data,
    qt_meta_data_QhSingletonProcessPrivate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhSingletonProcessPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhSingletonProcessPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhSingletonProcessPrivate.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QhSingletonProcessPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QhSingletonProcessPrivate::recvMessage(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_QhSingletonProcessMessage_t {
    QByteArrayData data[5];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhSingletonProcessMessage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhSingletonProcessMessage_t qt_meta_stringdata_QhSingletonProcessMessage = {
    {
QT_MOC_LITERAL(0, 0, 25), // "QhSingletonProcessMessage"
QT_MOC_LITERAL(1, 26, 11), // "recvMessage"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 4), // "type"
QT_MOC_LITERAL(4, 44, 4) // "data"

    },
    "QhSingletonProcessMessage\0recvMessage\0"
    "\0type\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhSingletonProcessMessage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

       0        // eod
};

void QhSingletonProcessMessage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhSingletonProcessMessage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recvMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QhSingletonProcessMessage::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QhSingletonProcessMessage::recvMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QhSingletonProcessMessage::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QhSingletonProcessMessage.data,
    qt_meta_data_QhSingletonProcessMessage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhSingletonProcessMessage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhSingletonProcessMessage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhSingletonProcessMessage.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QhSingletonProcessMessage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QhSingletonProcessMessage::recvMessage(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_QhSingletonProcessServer_t {
    QByteArrayData data[4];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhSingletonProcessServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhSingletonProcessServer_t qt_meta_stringdata_QhSingletonProcessServer = {
    {
QT_MOC_LITERAL(0, 0, 24), // "QhSingletonProcessServer"
QT_MOC_LITERAL(1, 25, 15), // "onNewConnection"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 11) // "onReadyRead"

    },
    "QhSingletonProcessServer\0onNewConnection\0"
    "\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhSingletonProcessServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QhSingletonProcessServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhSingletonProcessServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewConnection(); break;
        case 1: _t->onReadyRead(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QhSingletonProcessServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QhSingletonProcessMessage::staticMetaObject>(),
    qt_meta_stringdata_QhSingletonProcessServer.data,
    qt_meta_data_QhSingletonProcessServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhSingletonProcessServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhSingletonProcessServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhSingletonProcessServer.stringdata0))
        return static_cast<void*>(this);
    return QhSingletonProcessMessage::qt_metacast(_clname);
}

int QhSingletonProcessServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QhSingletonProcessMessage::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_QhSingletonProcessClient_t {
    QByteArrayData data[3];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QhSingletonProcessClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QhSingletonProcessClient_t qt_meta_stringdata_QhSingletonProcessClient = {
    {
QT_MOC_LITERAL(0, 0, 24), // "QhSingletonProcessClient"
QT_MOC_LITERAL(1, 25, 11), // "onReadyRead"
QT_MOC_LITERAL(2, 37, 0) // ""

    },
    "QhSingletonProcessClient\0onReadyRead\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QhSingletonProcessClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QhSingletonProcessClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QhSingletonProcessClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onReadyRead(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QhSingletonProcessClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QhSingletonProcessMessage::staticMetaObject>(),
    qt_meta_stringdata_QhSingletonProcessClient.data,
    qt_meta_data_QhSingletonProcessClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QhSingletonProcessClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QhSingletonProcessClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QhSingletonProcessClient.stringdata0))
        return static_cast<void*>(this);
    return QhSingletonProcessMessage::qt_metacast(_clname);
}

int QhSingletonProcessClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QhSingletonProcessMessage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
