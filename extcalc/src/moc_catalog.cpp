/****************************************************************************
** Meta object code from reading C++ file 'catalog.h'
**
** Created: Wed Dec 31 16:18:12 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "catalog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'catalog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConstantDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   15,   15,   15, 0x0a,
      50,   15,   15,   15, 0x0a,
      62,   15,   15,   15, 0x0a,
      83,   75,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConstantDialog[] = {
    "ConstantDialog\0\0prefChange(Preferences)\0"
    "boxSlot()\0applySlot()\0removeSlot()\0"
    "newPref\0setPref(Preferences)\0"
};

const QMetaObject ConstantDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConstantDialog,
      qt_meta_data_ConstantDialog, 0 }
};

const QMetaObject *ConstantDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ConstantDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConstantDialog))
        return static_cast<void*>(const_cast< ConstantDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConstantDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: boxSlot(); break;
        case 2: applySlot(); break;
        case 3: removeSlot(); break;
        case 4: setPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ConstantDialog::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_Catalog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      29,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,    8,    8,    8, 0x0a,
      75,    8,    8,    8, 0x0a,
     102,    8,    8,    8, 0x0a,
     124,    8,    8,    8, 0x0a,
     143,    8,    8,    8, 0x0a,
     159,    8,    8,    8, 0x0a,
     183,    8,    8,    8, 0x0a,
     203,    8,    8,    8, 0x0a,
     227,    8,    8,    8, 0x0a,
     245,    8,    8,    8, 0x0a,
     265,    8,    8,    8, 0x0a,
     289,  284,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Catalog[] = {
    "Catalog\0\0menuSignal(QString)\0"
    "prefChange(Preferences)\0mathStandardSlot(int)\0"
    "mathTrigonometricSlot(int)\0"
    "mathExtendedSlot(int)\0mathLogicSlot(int)\0"
    "matrixSlot(int)\0scriptStandardSlot(int)\0"
    "scriptTextSlot(int)\0scriptGraphicsSlot(int)\0"
    "scriptGLSlot(int)\0scriptFileSlot(int)\0"
    "constantsSlot(int)\0pref\0getPref(Preferences)\0"
};

const QMetaObject Catalog::staticMetaObject = {
    { &Q3PopupMenu::staticMetaObject, qt_meta_stringdata_Catalog,
      qt_meta_data_Catalog, 0 }
};

const QMetaObject *Catalog::metaObject() const
{
    return &staticMetaObject;
}

void *Catalog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Catalog))
        return static_cast<void*>(const_cast< Catalog*>(this));
    return Q3PopupMenu::qt_metacast(_clname);
}

int Catalog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3PopupMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: menuSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: mathStandardSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: mathTrigonometricSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: mathExtendedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: mathLogicSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: matrixSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: scriptStandardSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: scriptTextSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: scriptGraphicsSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: scriptGLSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: scriptFileSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: constantsSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Catalog::menuSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Catalog::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
