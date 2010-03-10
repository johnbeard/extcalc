/****************************************************************************
** Meta object code from reading C++ file 'graphpref.h'
**
** Created: Wed Mar 10 16:19:05 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphpref.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphpref.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CoordinatePreferences[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   22,   22,   22, 0x0a,
      63,   22,   22,   22, 0x0a,
      81,   22,   22,   22, 0x0a,
     105,  100,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CoordinatePreferences[] = {
    "CoordinatePreferences\0\0prefChange(Preferences)\0"
    "stdButtonSlot()\0angleButtonSlot()\0"
    "graphTypeSlot(int)\0pref\0getPref(Preferences)\0"
};

const QMetaObject CoordinatePreferences::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CoordinatePreferences,
      qt_meta_data_CoordinatePreferences, 0 }
};

const QMetaObject *CoordinatePreferences::metaObject() const
{
    return &staticMetaObject;
}

void *CoordinatePreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoordinatePreferences))
        return static_cast<void*>(const_cast< CoordinatePreferences*>(this));
    return QWidget::qt_metacast(_clname);
}

int CoordinatePreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: stdButtonSlot(); break;
        case 2: angleButtonSlot(); break;
        case 3: graphTypeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CoordinatePreferences::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_PerformancePreferences[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   48,   23,   23, 0x0a,
      74,   23,   23,   23, 0x0a,
      90,   23,   23,   23, 0x0a,
     111,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PerformancePreferences[] = {
    "PerformancePreferences\0\0prefChange(Preferences)\0"
    "pref\0getPref(Preferences)\0lowButtonSlot()\0"
    "standardButtonSlot()\0highButtonSlot()\0"
};

const QMetaObject PerformancePreferences::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PerformancePreferences,
      qt_meta_data_PerformancePreferences, 0 }
};

const QMetaObject *PerformancePreferences::metaObject() const
{
    return &staticMetaObject;
}

void *PerformancePreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PerformancePreferences))
        return static_cast<void*>(const_cast< PerformancePreferences*>(this));
    return QWidget::qt_metacast(_clname);
}

int PerformancePreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: lowButtonSlot(); break;
        case 3: standardButtonSlot(); break;
        case 4: highButtonSlot(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PerformancePreferences::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_DynamicPreferences[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   44,   19,   19, 0x0a,
      70,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DynamicPreferences[] = {
    "DynamicPreferences\0\0prefChange(Preferences)\0"
    "pref\0getPref(Preferences)\0"
    "standardButtonSlot()\0"
};

const QMetaObject DynamicPreferences::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DynamicPreferences,
      qt_meta_data_DynamicPreferences, 0 }
};

const QMetaObject *DynamicPreferences::metaObject() const
{
    return &staticMetaObject;
}

void *DynamicPreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DynamicPreferences))
        return static_cast<void*>(const_cast< DynamicPreferences*>(this));
    return QWidget::qt_metacast(_clname);
}

int DynamicPreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: standardButtonSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DynamicPreferences::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_GraphPreferences[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   17,   17,   17, 0x0a,
      62,   59,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphPreferences[] = {
    "GraphPreferences\0\0prefChange(Preferences)\0"
    "saveButtonSlot()\0pr\0getPref(Preferences)\0"
};

const QMetaObject GraphPreferences::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_GraphPreferences,
      qt_meta_data_GraphPreferences, 0 }
};

const QMetaObject *GraphPreferences::metaObject() const
{
    return &staticMetaObject;
}

void *GraphPreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphPreferences))
        return static_cast<void*>(const_cast< GraphPreferences*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int GraphPreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: saveButtonSlot(); break;
        case 2: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GraphPreferences::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
