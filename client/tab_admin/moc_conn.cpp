/****************************************************************************
** Meta object code from reading C++ file 'conn.h'
**
** Created: Mon Sep 1 18:06:32 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/conn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_Conn[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Conn[] = {
    "Conn\0\0plugDone()\0"
};

const QMetaObject Conn::staticMetaObject = {
    { &QHttp::staticMetaObject, qt_meta_stringdata_Conn,
      qt_meta_data_Conn, 0 }
};

const QMetaObject *Conn::metaObject() const
{
    return &staticMetaObject;
}

void *Conn::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Conn))
	return static_cast<void*>(const_cast< Conn*>(this));
    return QHttp::qt_metacast(_clname);
}

int Conn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHttp::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: plugDone(); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Conn::plugDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
