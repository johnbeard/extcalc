/****************************************************************************
** Meta object code from reading C++ file 'matrixwidget.h'
**
** Created: Sun Mar 28 18:04:07 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "matrixwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'matrixwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MatrixWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   13,   13,   13, 0x0a,
      59,   13,   13,   13, 0x0a,
      77,   13,   13,   13, 0x0a,
      96,   13,   13,   13, 0x0a,
     112,   13,   13,   13, 0x0a,
     134,   13,   13,   13, 0x0a,
     146,   13,   13,   13, 0x0a,
     173,  171,   13,   13, 0x0a,
     199,  171,   13,   13, 0x0a,
     223,  171,   13,   13, 0x0a,
     250,   13,   13,   13, 0x0a,
     267,   13,   13,   13, 0x0a,
     286,   13,   13,   13, 0x0a,
     305,   13,   13,   13, 0x0a,
     323,   13,   13,   13, 0x0a,
     340,   13,   13,   13, 0x0a,
     357,   13,   13,   13, 0x0a,
     374,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MatrixWidget[] = {
    "MatrixWidget\0\0prefChange(Preferences)\0"
    "getPref(Preferences)\0sprodButtonSlot()\0"
    "invertButtonSlot()\0detButtonSlot()\0"
    "operationBoxSlot(int)\0enterSlot()\0"
    "buttonInputSlot(QString)\0,\0"
    "varSelectionSlot(int,int)\0"
    "varChangedSlot(int,int)\0"
    "outputChangedSlot(int,int)\0calcButtonSlot()\0"
    "matrixBoxSlot(int)\0vectorBoxSlot(int)\0"
    "size1BoxSlot(int)\0sizeButtonSlot()\0"
    "typeBoxSlot(int)\0dockWindowSlot()\0"
    "catalogSlot()\0"
};

const QMetaObject MatrixWidget::staticMetaObject = {
    { &TabWidget::staticMetaObject, qt_meta_stringdata_MatrixWidget,
      qt_meta_data_MatrixWidget, 0 }
};

const QMetaObject *MatrixWidget::metaObject() const
{
    return &staticMetaObject;
}

void *MatrixWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MatrixWidget))
        return static_cast<void*>(const_cast< MatrixWidget*>(this));
    return TabWidget::qt_metacast(_clname);
}

int MatrixWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: sprodButtonSlot(); break;
        case 3: invertButtonSlot(); break;
        case 4: detButtonSlot(); break;
        case 5: operationBoxSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: enterSlot(); break;
        case 7: buttonInputSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: varSelectionSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: varChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: outputChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: calcButtonSlot(); break;
        case 12: matrixBoxSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: vectorBoxSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: size1BoxSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: sizeButtonSlot(); break;
        case 16: typeBoxSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: dockWindowSlot(); break;
        case 18: catalogSlot(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MatrixWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
