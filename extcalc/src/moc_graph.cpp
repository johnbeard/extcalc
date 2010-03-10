/****************************************************************************
** Meta object code from reading C++ file 'graph.h'
**
** Created: Wed Mar 10 16:19:03 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graph.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphArea[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GraphArea[] = {
    "GraphArea\0\0sizeChanged()\0"
};

const QMetaObject GraphArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GraphArea,
      qt_meta_data_GraphArea, 0 }
};

const QMetaObject *GraphArea::metaObject() const
{
    return &staticMetaObject;
}

void *GraphArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphArea))
        return static_cast<void*>(const_cast< GraphArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int GraphArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sizeChanged(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GraphArea::sizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_GraphWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      37,   12,   12,   12, 0x05,
      61,   58,   12,   12, 0x05,
     101,   12,   12,   12, 0x05,
     121,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     154,  146,   12,   12, 0x0a,
     184,   12,   12,   12, 0x0a,
     207,   12,   12,   12, 0x0a,
     218,   12,   12,   12, 0x0a,
     233,   12,   12,   12, 0x0a,
     247,   12,   12,   12, 0x0a,
     273,   12,   12,   12, 0x0a,
     293,   12,   12,   12, 0x0a,
     318,   12,   12,   12, 0x0a,
     337,   12,   12,   12, 0x0a,
     351,   12,   12,   12, 0x0a,
     365,   12,   12,   12, 0x0a,
     381,   12,   12,   12, 0x0a,
     400,  398,   12,   12, 0x0a,
     424,   12,   12,   12, 0x0a,
     462,  454,   12,   12, 0x0a,
     489,  483,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphWidget[] = {
    "GraphWidget\0\0prefChange(Preferences)\0"
    "solveTypeSignal(int)\0,,\0"
    "drawPointsSignal(long double*,int,bool)\0"
    "removeLinesSignal()\0statisticsRedrawSignal()\0"
    "row,col\0selectionChangedSlot(int,int)\0"
    "tableEditSlot(QString)\0drawSlot()\0"
    "maximizeSlot()\0modeSlot(int)\0"
    "inputTextChanged(QString)\0inputTextFinished()\0"
    "buttonInputSlot(QString)\0solveTypeSlot(int)\0"
    "editSlot(int)\0catalogSlot()\0graphSizeSlot()\0"
    "dockWindowSlot()\0,\0inequalitySlot(int,int)\0"
    "graphProcessingFinishedSlot()\0newPref\0"
    "getPref(Preferences)\0fType\0"
    "functionTypeSlot(int)\0"
};

const QMetaObject GraphWidget::staticMetaObject = {
    { &TabWidget::staticMetaObject, qt_meta_stringdata_GraphWidget,
      qt_meta_data_GraphWidget, 0 }
};

const QMetaObject *GraphWidget::metaObject() const
{
    return &staticMetaObject;
}

void *GraphWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphWidget))
        return static_cast<void*>(const_cast< GraphWidget*>(this));
    return TabWidget::qt_metacast(_clname);
}

int GraphWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: solveTypeSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: drawPointsSignal((*reinterpret_cast< long double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: removeLinesSignal(); break;
        case 4: statisticsRedrawSignal(); break;
        case 5: selectionChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: tableEditSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: drawSlot(); break;
        case 8: maximizeSlot(); break;
        case 9: modeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: inputTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: inputTextFinished(); break;
        case 12: buttonInputSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: solveTypeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: editSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: catalogSlot(); break;
        case 16: graphSizeSlot(); break;
        case 17: dockWindowSlot(); break;
        case 18: inequalitySlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: graphProcessingFinishedSlot(); break;
        case 20: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 21: functionTypeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void GraphWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphWidget::solveTypeSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GraphWidget::drawPointsSignal(long double * _t1, int _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GraphWidget::removeLinesSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GraphWidget::statisticsRedrawSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
