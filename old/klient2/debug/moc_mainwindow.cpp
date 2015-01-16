/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata[450];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 10),
QT_MOC_LITERAL(4, 37, 29),
QT_MOC_LITERAL(5, 67, 25),
QT_MOC_LITERAL(6, 93, 9),
QT_MOC_LITERAL(7, 103, 10),
QT_MOC_LITERAL(8, 114, 10),
QT_MOC_LITERAL(9, 125, 17),
QT_MOC_LITERAL(10, 143, 11),
QT_MOC_LITERAL(11, 155, 13),
QT_MOC_LITERAL(12, 169, 13),
QT_MOC_LITERAL(13, 183, 19),
QT_MOC_LITERAL(14, 203, 21),
QT_MOC_LITERAL(15, 225, 18),
QT_MOC_LITERAL(16, 244, 21),
QT_MOC_LITERAL(17, 266, 14),
QT_MOC_LITERAL(18, 281, 28),
QT_MOC_LITERAL(19, 310, 36),
QT_MOC_LITERAL(20, 347, 33),
QT_MOC_LITERAL(21, 381, 28),
QT_MOC_LITERAL(22, 410, 39)
    },
    "MainWindow\0set_user_data\0\0user_data*\0"
    "on_actionPolaczenie_triggered\0"
    "on_actionSzukaj_triggered\0find_user\0"
    "add_friend\0user_click\0user_window_close\0"
    "msg_message\0text_message*\0msg_user_data\0"
    "msg_user_data_login\0msg_challenge_log_ack\0"
    "challenge_log_ack*\0msg_challenge_reg_ack\0"
    "challenge_reg*\0on_actionLogowanie_triggered\0"
    "on_actionZarejestruj_konto_triggered\0"
    "on_actionZablokuj_konto_triggered\0"
    "on_actionUsu_konto_triggered\0"
    "on_actionZmie_klucz_publiczny_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  102,    2, 0x0a /* Public */,
       5,    0,  103,    2, 0x0a /* Public */,
       6,    1,  104,    2, 0x0a /* Public */,
       7,    1,  107,    2, 0x0a /* Public */,
       8,    1,  110,    2, 0x0a /* Public */,
       9,    1,  113,    2, 0x0a /* Public */,
      10,    1,  116,    2, 0x0a /* Public */,
      12,    1,  119,    2, 0x0a /* Public */,
      13,    1,  122,    2, 0x0a /* Public */,
      14,    1,  125,    2, 0x0a /* Public */,
      16,    1,  128,    2, 0x0a /* Public */,
      18,    0,  131,    2, 0x08 /* Private */,
      19,    0,  132,    2, 0x08 /* Private */,
      20,    0,  133,    2, 0x08 /* Private */,
      21,    0,  134,    2, 0x08 /* Private */,
      22,    0,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->set_user_data((*reinterpret_cast< user_data*(*)>(_a[1]))); break;
        case 1: _t->on_actionPolaczenie_triggered(); break;
        case 2: _t->on_actionSzukaj_triggered(); break;
        case 3: _t->find_user((*reinterpret_cast< user_data*(*)>(_a[1]))); break;
        case 4: _t->add_friend((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->user_click((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->user_window_close((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->msg_message((*reinterpret_cast< text_message*(*)>(_a[1]))); break;
        case 8: _t->msg_user_data((*reinterpret_cast< user_data*(*)>(_a[1]))); break;
        case 9: _t->msg_user_data_login((*reinterpret_cast< user_data*(*)>(_a[1]))); break;
        case 10: _t->msg_challenge_log_ack((*reinterpret_cast< challenge_log_ack*(*)>(_a[1]))); break;
        case 11: _t->msg_challenge_reg_ack((*reinterpret_cast< challenge_reg*(*)>(_a[1]))); break;
        case 12: _t->on_actionLogowanie_triggered(); break;
        case 13: _t->on_actionZarejestruj_konto_triggered(); break;
        case 14: _t->on_actionZablokuj_konto_triggered(); break;
        case 15: _t->on_actionUsu_konto_triggered(); break;
        case 16: _t->on_actionZmie_klucz_publiczny_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(user_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::set_user_data)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::set_user_data(user_data * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
