/****************************************************************************
** Meta object code from reading C++ file 'conn.h'
**
** Created: Thu Nov 18 19:21:50 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../conn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Conn[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      17,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   28,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Conn[] = {
    "Conn\0\0plugDone()\0HttpDone()\0r\0"
    "requestDone(QNetworkReply*)\0"
};

const QMetaObject Conn::staticMetaObject = {
    { &QNetworkAccessManager::staticMetaObject, qt_meta_stringdata_Conn,
      qt_meta_data_Conn, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Conn::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Conn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Conn::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Conn))
        return static_cast<void*>(const_cast< Conn*>(this));
    return QNetworkAccessManager::qt_metacast(_clname);
}

int Conn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QNetworkAccessManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: plugDone(); break;
        case 1: HttpDone(); break;
        case 2: requestDone((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Conn::plugDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Conn::HttpDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
