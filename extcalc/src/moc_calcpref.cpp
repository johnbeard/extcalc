/****************************************************************************
** Meta object code from reading C++ file 'calcpref.h'
**
** Created: Wed Dec 31 16:18:02 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calcpref.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calcpref.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalcPreferences[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CalcPreferences[] = {
    "CalcPreferences\0\0prefChange(Preferences)\0"
    "saveSlot()\0"
};

const QMetaObject CalcPreferences::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CalcPreferences,
      qt_meta_data_CalcPreferences, 0 }
};

const QMetaObject *CalcPreferences::metaObject() const
{
    return &staticMetaObject;
}

void *CalcPreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalcPreferences))
        return static_cast<void*>(const_cast< CalcPreferences*>(this));
    return QWidget::qt_metacast(_clname);
}

int CalcPreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: saveSlot(); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CalcPreferences::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
