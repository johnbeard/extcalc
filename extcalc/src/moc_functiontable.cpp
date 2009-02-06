/****************************************************************************
** Meta object code from reading C++ file 'functiontable.h'
**
** Created: Wed Dec 31 16:18:04 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "functiontable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'functiontable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FunctionTable[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      39,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   64,   14,   14, 0x0a,
      97,   64,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FunctionTable[] = {
    "FunctionTable\0\0prefChange(Preferences)\0"
    "textEditStarted(QString)\0row,col\0"
    "cellChangedSlot(int,int)\0"
    "editStartedSlot(int,int)\0"
};

const QMetaObject FunctionTable::staticMetaObject = {
    { &CalcTable::staticMetaObject, qt_meta_stringdata_FunctionTable,
      qt_meta_data_FunctionTable, 0 }
};

const QMetaObject *FunctionTable::metaObject() const
{
    return &staticMetaObject;
}

void *FunctionTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FunctionTable))
        return static_cast<void*>(const_cast< FunctionTable*>(this));
    return CalcTable::qt_metacast(_clname);
}

int FunctionTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CalcTable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: textEditStarted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: cellChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: editStartedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FunctionTable::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FunctionTable::textEditStarted(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
