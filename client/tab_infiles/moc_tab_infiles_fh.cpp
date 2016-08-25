/****************************************************************************
** Meta object code from reading C++ file 'tab_infiles_fh.h'
**
** Created: Mon Sep 1 18:06:45 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tab_infiles_fh.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tab_infiles_fh.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_FileHandler[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      23,   12,   12,   12, 0x05,
      35,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FileHandler[] = {
    "FileHandler\0\0tick(int)\0tick(Case*)\0"
    "tick(KData*)\0"
};

const QMetaObject FileHandler::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FileHandler,
      qt_meta_data_FileHandler, 0 }
};

const QMetaObject *FileHandler::metaObject() const
{
    return &staticMetaObject;
}

void *FileHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileHandler))
	return static_cast<void*>(const_cast< FileHandler*>(this));
    return QThread::qt_metacast(_clname);
}

int FileHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: tick((*reinterpret_cast< Case*(*)>(_a[1]))); break;
        case 2: tick((*reinterpret_cast< KData*(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FileHandler::tick(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileHandler::tick(Case * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileHandler::tick(KData * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
