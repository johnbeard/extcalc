/****************************************************************************
** Meta object code from reading C++ file 'calctable.h'
**
** Created: Wed Dec 31 16:18:00 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calctable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calctable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalcTable[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CalcTable[] = {
    "CalcTable\0\0,\0cellEditStarted(int,int)\0"
};

const QMetaObject CalcTable::staticMetaObject = {
    { &Q3Table::staticMetaObject, qt_meta_stringdata_CalcTable,
      qt_meta_data_CalcTable, 0 }
};

const QMetaObject *CalcTable::metaObject() const
{
    return &staticMetaObject;
}

void *CalcTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalcTable))
        return static_cast<void*>(const_cast< CalcTable*>(this));
    return Q3Table::qt_metacast(_clname);
}

int CalcTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3Table::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cellEditStarted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CalcTable::cellEditStarted(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
