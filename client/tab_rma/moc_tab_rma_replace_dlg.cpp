/****************************************************************************
** Meta object code from reading C++ file 'tab_rma_replace_dlg.h'
**
** Created: Mon Sep 1 18:06:57 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tab_rma_replace_dlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tab_rma_replace_dlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ReplaceDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      20,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ReplaceDlg[] = {
    "ReplaceDlg\0\0check()\0okay()\0"
};

const QMetaObject ReplaceDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReplaceDlg,
      qt_meta_data_ReplaceDlg, 0 }
};

const QMetaObject *ReplaceDlg::metaObject() const
{
    return &staticMetaObject;
}

void *ReplaceDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReplaceDlg))
	return static_cast<void*>(const_cast< ReplaceDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReplaceDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: check(); break;
        case 1: okay(); break;
        }
        _id -= 2;
    }
    return _id;
}
