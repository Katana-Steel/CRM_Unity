/****************************************************************************
** Meta object code from reading C++ file 'stat_sogning_dato.h'
**
** Created: Tue Sep 2 12:40:26 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stat_sogning_dato.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stat_sogning_dato.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResDatoDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x08,
      34,   28,   11,   11, 0x08,
      52,   28,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ResDatoDlg[] = {
    "ResDatoDlg\0\0i\0showDato(int)\0r,col\0"
    "showTOKA(int,int)\0showKnd(int,int)\0"
};

const QMetaObject ResDatoDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ResDatoDlg,
      qt_meta_data_ResDatoDlg, 0 }
};

const QMetaObject *ResDatoDlg::metaObject() const
{
    return &staticMetaObject;
}

void *ResDatoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResDatoDlg))
        return static_cast<void*>(const_cast< ResDatoDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int ResDatoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showDato((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: showTOKA((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: showKnd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
