/****************************************************************************
** Meta object code from reading C++ file 'tab_infiles.h'
**
** Created: Tue Sep 2 12:44:26 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tab_infiles.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tab_infiles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_tabInFiles[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      64,   60,   11,   11, 0x08,
      79,   60,   11,   11, 0x08,
      95,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     141,  137,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_tabInFiles[] = {
    "tabInFiles\0\0addGross()\0OpenFile()\0"
    "resetReady()\0startParse()\0str\0"
    "addCase(Case*)\0addCust(KData*)\0"
    "searchGross()\0multiUpdate()\0multiDelete()\0"
    "twi\0valueUpdate(QTableWidgetItem*)\0"
};

const QMetaObject tabInFiles::staticMetaObject = {
    { &TabInterface::staticMetaObject, qt_meta_stringdata_tabInFiles,
      qt_meta_data_tabInFiles, 0 }
};

const QMetaObject *tabInFiles::metaObject() const
{
    return &staticMetaObject;
}

void *tabInFiles::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tabInFiles))
        return static_cast<void*>(const_cast< tabInFiles*>(this));
    if (!strcmp(_clname, "dk.bhsribe.helhed/tabs/1.3"))
        return static_cast< TabInterface*>(const_cast< tabInFiles*>(this));
    return TabInterface::qt_metacast(_clname);
}

int tabInFiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addGross(); break;
        case 1: OpenFile(); break;
        case 2: resetReady(); break;
        case 3: startParse(); break;
        case 4: addCase((*reinterpret_cast< Case*(*)>(_a[1]))); break;
        case 5: addCust((*reinterpret_cast< KData*(*)>(_a[1]))); break;
        case 6: searchGross(); break;
        case 7: multiUpdate(); break;
        case 8: multiDelete(); break;
        case 9: valueUpdate((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
