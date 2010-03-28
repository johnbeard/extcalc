/****************************************************************************
** Meta object code from reading C++ file 'scriptdisplay.h'
**
** Created: Tue Mar 23 19:30:30 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scriptdisplay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptdisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptDisplay[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ScriptDisplay[] = {
    "ScriptDisplay\0\0,\0pointVisibleSignal(int,int)\0"
};

const QMetaObject ScriptDisplay::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScriptDisplay,
      qt_meta_data_ScriptDisplay, 0 }
};

const QMetaObject *ScriptDisplay::metaObject() const
{
    return &staticMetaObject;
}

void *ScriptDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptDisplay))
        return static_cast<void*>(const_cast< ScriptDisplay*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScriptDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pointVisibleSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ScriptDisplay::pointVisibleSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
