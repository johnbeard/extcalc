/****************************************************************************
** Meta object code from reading C++ file 'table.h'
**
** Created: Sun Mar 28 18:04:02 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "table.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'table.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TableWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   12,   12,   12, 0x0a,
      66,   58,   12,   12, 0x0a,
      96,   12,   12,   12, 0x0a,
     119,   12,   12,   12, 0x0a,
     138,   12,   12,   12, 0x0a,
     160,   12,   12,   12, 0x0a,
     181,   12,   12,   12, 0x0a,
     202,   12,   12,   12, 0x0a,
     227,   12,   12,   12, 0x0a,
     241,   12,   12,   12, 0x0a,
     261,   12,   12,   12, 0x0a,
     281,   12,   12,   12, 0x0a,
     300,   12,   12,   12, 0x0a,
     317,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TableWidget[] = {
    "TableWidget\0\0prefChange(Preferences)\0"
    "getPref(Preferences)\0row,col\0"
    "selectionChangedSlot(int,int)\0"
    "tableEditSlot(QString)\0inputTextChanged()\0"
    "calculateButtonSlot()\0typeBoxSlot(QString)\0"
    "maximizeButtonSlot()\0buttonInputSlot(QString)\0"
    "editSlot(int)\0horzHeaderSlot(int)\0"
    "vertHeaderSlot(int)\0tableMenuSlot(int)\0"
    "dockWindowSlot()\0catalogSlot()\0"
};

const QMetaObject TableWidget::staticMetaObject = {
    { &TabWidget::staticMetaObject, qt_meta_stringdata_TableWidget,
      qt_meta_data_TableWidget, 0 }
};

const QMetaObject *TableWidget::metaObject() const
{
    return &staticMetaObject;
}

void *TableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableWidget))
        return static_cast<void*>(const_cast< TableWidget*>(this));
    return TabWidget::qt_metacast(_clname);
}

int TableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: selectionChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: tableEditSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: inputTextChanged(); break;
        case 5: calculateButtonSlot(); break;
        case 6: typeBoxSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: maximizeButtonSlot(); break;
        case 8: buttonInputSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: editSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: horzHeaderSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: vertHeaderSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: tableMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: dockWindowSlot(); break;
        case 14: catalogSlot(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void TableWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
