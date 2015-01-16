/****************************************************************************
** Meta object code from reading C++ file 'read_write_socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../read_write_socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'read_write_socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_read_write_socket_t {
    QByteArrayData data[23];
    char stringdata[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_read_write_socket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_read_write_socket_t qt_meta_stringdata_read_write_socket = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 11),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 13),
QT_MOC_LITERAL(4, 45, 13),
QT_MOC_LITERAL(5, 59, 10),
QT_MOC_LITERAL(6, 70, 19),
QT_MOC_LITERAL(7, 90, 21),
QT_MOC_LITERAL(8, 112, 18),
QT_MOC_LITERAL(9, 131, 21),
QT_MOC_LITERAL(10, 153, 14),
QT_MOC_LITERAL(11, 168, 17),
QT_MOC_LITERAL(12, 186, 10),
QT_MOC_LITERAL(13, 197, 18),
QT_MOC_LITERAL(14, 216, 11),
QT_MOC_LITERAL(15, 228, 21),
QT_MOC_LITERAL(16, 250, 13),
QT_MOC_LITERAL(17, 264, 5),
QT_MOC_LITERAL(18, 270, 11),
QT_MOC_LITERAL(19, 282, 12),
QT_MOC_LITERAL(20, 295, 28),
QT_MOC_LITERAL(21, 324, 12),
QT_MOC_LITERAL(22, 337, 22)
    },
    "read_write_socket\0msg_message\0\0"
    "text_message*\0msg_user_data\0user_data*\0"
    "msg_user_data_login\0msg_challenge_log_ack\0"
    "challenge_log_ack*\0msg_challenge_reg_ack\0"
    "challenge_reg*\0send_text_message\0"
    "send_login\0send_challenge_reg\0std::string\0"
    "encoded_random_string\0send_reg_data\0"
    "login\0msg_wrap_up\0displayError\0"
    "QAbstractSocket::SocketError\0time_to_read\0"
    "connection_established"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_read_write_socket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       7,    1,   88,    2, 0x06 /* Public */,
       9,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    1,   96,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,
      18,    0,  102,    2, 0x0a /* Public */,
      19,    1,  103,    2, 0x08 /* Private */,
      21,    0,  106,    2, 0x08 /* Private */,
      22,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   17,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void read_write_socket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        read_write_socket *_t = static_cast<read_write_socket *>(_o);
        switch (_id) {
        case 0: _t->msg_message((*reinterpret_cast< text_message*(*)>(_a[1]))); break;
        case 1: _t->msg_user_data((*reinterpret_cast< user_data*(*)>(_a[1]))); break;
        case 2: _t->msg_user_data_login((*reinterpret_cast< user_data*(*)>(_a[1]))); break;
        case 3: _t->msg_challenge_log_ack((*reinterpret_cast< challenge_log_ack*(*)>(_a[1]))); break;
        case 4: _t->msg_challenge_reg_ack((*reinterpret_cast< challenge_reg*(*)>(_a[1]))); break;
        case 5: _t->send_text_message(); break;
        case 6: _t->send_login(); break;
        case 7: _t->send_challenge_reg((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->send_reg_data((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 9: _t->msg_wrap_up(); break;
        case 10: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: _t->time_to_read(); break;
        case 12: _t->connection_established(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (read_write_socket::*_t)(text_message * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&read_write_socket::msg_message)) {
                *result = 0;
            }
        }
        {
            typedef void (read_write_socket::*_t)(user_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&read_write_socket::msg_user_data)) {
                *result = 1;
            }
        }
        {
            typedef void (read_write_socket::*_t)(user_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&read_write_socket::msg_user_data_login)) {
                *result = 2;
            }
        }
        {
            typedef void (read_write_socket::*_t)(challenge_log_ack * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&read_write_socket::msg_challenge_log_ack)) {
                *result = 3;
            }
        }
        {
            typedef void (read_write_socket::*_t)(challenge_reg * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&read_write_socket::msg_challenge_reg_ack)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject read_write_socket::staticMetaObject = {
    { &QAbstractSocket::staticMetaObject, qt_meta_stringdata_read_write_socket.data,
      qt_meta_data_read_write_socket,  qt_static_metacall, 0, 0}
};


const QMetaObject *read_write_socket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *read_write_socket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_read_write_socket.stringdata))
        return static_cast<void*>(const_cast< read_write_socket*>(this));
    return QAbstractSocket::qt_metacast(_clname);
}

int read_write_socket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void read_write_socket::msg_message(text_message * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void read_write_socket::msg_user_data(user_data * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void read_write_socket::msg_user_data_login(user_data * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void read_write_socket::msg_challenge_log_ack(challenge_log_ack * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void read_write_socket::msg_challenge_reg_ack(challenge_reg * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
