/****************************************************************************
** Meta object code from reading C++ file 'calcwidget.h'
**
** Created: Sun Mar 28 18:03:54 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calcwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calcwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalcWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      36,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   56,   11,   11, 0x0a,
      85,   11,   11,   11, 0x0a,
      96,   11,   11,   11, 0x0a,
     110,   11,   11,   11, 0x0a,
     125,   11,   11,   11, 0x0a,
     139,   11,   11,   11, 0x0a,
     153,   11,   11,   11, 0x0a,
     167,   11,   11,   11, 0x0a,
     183,   11,   11,   11, 0x0a,
     205,  200,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CalcWidget[] = {
    "CalcWidget\0\0prefChange(Preferences)\0"
    "runScript(QString*)\0newPref\0"
    "getPref(Preferences)\0viewSlot()\0"
    "baseSlot(int)\0angleSlot(int)\0typeSlot(int)\0"
    "editSlot(int)\0catalogSlot()\0constantsSlot()\0"
    "dockWindowSlot()\0text\0processText(QString)\0"
};

const QMetaObject CalcWidget::staticMetaObject = {
    { &TabWidget::staticMetaObject, qt_meta_stringdata_CalcWidget,
      qt_meta_data_CalcWidget, 0 }
};

const QMetaObject *CalcWidget::metaObject() const
{
    return &staticMetaObject;
}

void *CalcWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalcWidget))
        return static_cast<void*>(const_cast< CalcWidget*>(this));
    return TabWidget::qt_metacast(_clname);
}

int CalcWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: runScript((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 2: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 3: viewSlot(); break;
        case 4: baseSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: angleSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: typeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: editSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: catalogSlot(); break;
        case 9: constantsSlot(); break;
        case 10: dockWindowSlot(); break;
        case 11: processText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CalcWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalcWidget::runScript(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
