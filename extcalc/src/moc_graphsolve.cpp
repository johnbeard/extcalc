/****************************************************************************
** Meta object code from reading C++ file 'graphsolve.h'
**
** Created: Wed Dec 31 16:17:59 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphsolve.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphsolve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphSolveWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x05,
      46,   44,   17,   17, 0x05,
      78,   72,   17,   17, 0x05,
     106,   99,   17,   17, 0x05,
     128,  124,   17,   17, 0x05,
     158,  154,   17,   17, 0x05,
     188,  184,   17,   17, 0x05,
     214,   17,   17,   17, 0x05,
     228,   17,   17,   17, 0x05,
     254,  252,   17,   17, 0x05,
     290,   17,   17,   17, 0x05,
     305,  252,   17,   17, 0x05,
     337,  334,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     364,   17,   17,   17, 0x0a,
     382,  252,   17,   17, 0x0a,
     431,  418,   17,   17, 0x0a,
     451,  445,   17,   17, 0x0a,
     472,   17,   17,   17, 0x0a,
     497,   17,   17,   17, 0x0a,
     514,   17,   17,   17, 0x0a,
     532,   17,   17,   17, 0x0a,
     550,   17,   17,   17, 0x0a,
     570,   17,   17,   17, 0x0a,
     587,   17,   17,   17, 0x0a,
     605,   17,   17,   17, 0x0a,
     622,   17,   17,   17, 0x0a,
     639,   17,   17,   17, 0x0a,
     656,   17,   17,   17, 0x0a,
     675,   17,   17,   17, 0x0a,
     694,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphSolveWidget[] = {
    "GraphSolveWidget\0\0x\0addVerticalLine(double)\0"
    "y\0addHorizontalLine(double)\0angle\0"
    "addPolarLine(double)\0radius\0"
    "addCircle(double)\0y,z\0add3dXLine(double,double)\0"
    "x,z\0add3dYLine(double,double)\0x,y\0"
    "add3dZLine(double,double)\0removeLines()\0"
    "prefChange(Preferences)\0,\0"
    "drawInequalityIntersection(int,int)\0"
    "redrawGraphs()\0getScreenshotSignal(int,int)\0"
    ",,\0drawSignal(int,QColor,int)\0"
    "solveButtonSlot()\0graphLMButtonPressed(double,double)\0"
    "newSolveType\0setState(int)\0fType\0"
    "setFunctionType(int)\0screenshotSlot(QPixmap*)\0"
    "openButtonSlot()\0colorButtonSlot()\0"
    "penValueSlot(int)\0forwardButtonSlot()\0"
    "backButtonSlot()\0clearButtonSlot()\0"
    "freeButtonSlot()\0lineButtonSlot()\0"
    "rectButtonSlot()\0circleButtonSlot()\0"
    "rubberButtonSlot()\0textButtonSlot()\0"
};

const QMetaObject GraphSolveWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GraphSolveWidget,
      qt_meta_data_GraphSolveWidget, 0 }
};

const QMetaObject *GraphSolveWidget::metaObject() const
{
    return &staticMetaObject;
}

void *GraphSolveWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphSolveWidget))
        return static_cast<void*>(const_cast< GraphSolveWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GraphSolveWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addVerticalLine((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: addHorizontalLine((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: addPolarLine((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: addCircle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: add3dXLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: add3dYLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: add3dZLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: removeLines(); break;
        case 8: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 9: drawInequalityIntersection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: redrawGraphs(); break;
        case 11: getScreenshotSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: drawSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: solveButtonSlot(); break;
        case 14: graphLMButtonPressed((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 15: setState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: setFunctionType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: screenshotSlot((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        case 18: openButtonSlot(); break;
        case 19: colorButtonSlot(); break;
        case 20: penValueSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: forwardButtonSlot(); break;
        case 22: backButtonSlot(); break;
        case 23: clearButtonSlot(); break;
        case 24: freeButtonSlot(); break;
        case 25: lineButtonSlot(); break;
        case 26: rectButtonSlot(); break;
        case 27: circleButtonSlot(); break;
        case 28: rubberButtonSlot(); break;
        case 29: textButtonSlot(); break;
        }
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void GraphSolveWidget::addVerticalLine(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphSolveWidget::addHorizontalLine(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GraphSolveWidget::addPolarLine(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GraphSolveWidget::addCircle(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GraphSolveWidget::add3dXLine(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GraphSolveWidget::add3dYLine(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GraphSolveWidget::add3dZLine(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GraphSolveWidget::removeLines()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void GraphSolveWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GraphSolveWidget::drawInequalityIntersection(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GraphSolveWidget::redrawGraphs()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void GraphSolveWidget::getScreenshotSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GraphSolveWidget::drawSignal(int _t1, QColor _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
