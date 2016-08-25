/****************************************************************************
** Meta object code from reading C++ file 'mwin.h'
**
** Created: Thu Nov 18 19:17:23 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MWin[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      13,    5,    5,    5, 0x0a,
      30,    5,    5,    5, 0x08,
      37,    5,    5,    5, 0x08,
      63,   59,    5,    5, 0x08,
      88,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MWin[] = {
    "MWin\0\0show()\0setVisible(bool)\0done()\0"
    "ready(QNetworkReply*)\0v,t\0"
    "updateBar(qint64,qint64)\0readNet()\0"
};

const QMetaObject MWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MWin,
      qt_meta_data_MWin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MWin))
        return static_cast<void*>(const_cast< MWin*>(this));
    return QWidget::qt_metacast(_clname);
}

int MWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: show(); break;
        case 1: setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: done(); break;
        case 3: ready((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: updateBar((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: readNet(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
