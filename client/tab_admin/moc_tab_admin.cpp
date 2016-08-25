/****************************************************************************
** Meta object code from reading C++ file 'tab_admin.h'
**
** Created: Tue Sep 2 12:44:16 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tab_admin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tab_admin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_tabAdmin[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      28,    9,    9,    9, 0x08,
      48,    9,    9,    9, 0x08,
      66,    9,    9,    9, 0x08,
      78,    9,    9,    9, 0x08,
      88,    9,    9,    9, 0x08,
     102,    9,    9,    9, 0x08,
     116,    9,    9,    9, 0x08,
     129,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_tabAdmin[] = {
    "tabAdmin\0\0radioChanged(int)\0"
    "availableUsers(int)\0showUserData(int)\0"
    "sendQuery()\0resetUD()\0sendUpdMail()\0"
    "addMailRule()\0updateRule()\0rmMailRule()\0"
};

const QMetaObject tabAdmin::staticMetaObject = {
    { &TabInterface::staticMetaObject, qt_meta_stringdata_tabAdmin,
      qt_meta_data_tabAdmin, 0 }
};

const QMetaObject *tabAdmin::metaObject() const
{
    return &staticMetaObject;
}

void *tabAdmin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tabAdmin))
        return static_cast<void*>(const_cast< tabAdmin*>(this));
    if (!strcmp(_clname, "dk.bhsribe.helhed/tabs/1.3"))
        return static_cast< TabInterface*>(const_cast< tabAdmin*>(this));
    return TabInterface::qt_metacast(_clname);
}

int tabAdmin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: radioChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: availableUsers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: showUserData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: sendQuery(); break;
        case 4: resetUD(); break;
        case 5: sendUpdMail(); break;
        case 6: addMailRule(); break;
        case 7: updateRule(); break;
        case 8: rmMailRule(); break;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
