/****************************************************************************
** Meta object code from reading C++ file 'buttons.h'
**
** Created: Wed Mar 10 16:19:01 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "buttons.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buttons.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StandardButtons[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      35,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      59,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StandardButtons[] = {
    "StandardButtons\0\0emitText(QString)\0"
    "prefChange(Preferences)\0buttonSlot(int)\0"
};

const QMetaObject StandardButtons::staticMetaObject = {
    { &Q3ButtonGroup::staticMetaObject, qt_meta_stringdata_StandardButtons,
      qt_meta_data_StandardButtons, 0 }
};

const QMetaObject *StandardButtons::metaObject() const
{
    return &staticMetaObject;
}

void *StandardButtons::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StandardButtons))
        return static_cast<void*>(const_cast< StandardButtons*>(this));
    return Q3ButtonGroup::qt_metacast(_clname);
}

int StandardButtons::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3ButtonGroup::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: emitText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: buttonSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void StandardButtons::emitText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StandardButtons::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ExtButtons[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      30,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExtButtons[] = {
    "ExtButtons\0\0emitText(QString)\0"
    "prefChange(Preferences)\0buttonSlot(int)\0"
};

const QMetaObject ExtButtons::staticMetaObject = {
    { &Q3ButtonGroup::staticMetaObject, qt_meta_stringdata_ExtButtons,
      qt_meta_data_ExtButtons, 0 }
};

const QMetaObject *ExtButtons::metaObject() const
{
    return &staticMetaObject;
}

void *ExtButtons::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExtButtons))
        return static_cast<void*>(const_cast< ExtButtons*>(this));
    return Q3ButtonGroup::qt_metacast(_clname);
}

int ExtButtons::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3ButtonGroup::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: emitText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: buttonSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ExtButtons::emitText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtButtons::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
