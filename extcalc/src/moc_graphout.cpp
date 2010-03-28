/****************************************************************************
** Meta object code from reading C++ file 'graphout.h'
**
** Created: Sun Mar 28 18:03:57 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphout.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphOutput[] = {

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
      39,   37,   12,   12, 0x05,
      73,   12,   12,   12, 0x05,
      88,   12,   12,   12, 0x05,
     115,   12,   12,   12, 0x05,
     135,   12,   12,   12, 0x05,
     160,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     183,  181,   12,   12, 0x0a,
     212,  210,   12,   12, 0x0a,
     244,  237,   12,   12, 0x0a,
     269,  263,   12,   12, 0x0a,
     311,  291,   12,   12, 0x0a,
     349,  345,   12,   12, 0x0a,
     380,  376,   12,   12, 0x0a,
     411,  407,   12,   12, 0x0a,
     438,   12,   12,   12, 0x0a,
     452,   12,   12,   12, 0x0a,
     468,   12,   12,   12, 0x0a,
     480,   12,   12,   12, 0x0a,
     498,   37,   12,   12, 0x0a,
     525,  522,   12,   12, 0x0a,
     550,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphOutput[] = {
    "GraphOutput\0\0prefChange(Preferences)\0"
    ",\0leftMButtonPressed(double,double)\0"
    "redrawSignal()\0screenshotSignal(QPixmap*)\0"
    "solveRedrawSignal()\0statisticsRedrawSignal()\0"
    "processingFinished()\0y\0"
    "drawHorizontalLine(double)\0x\0"
    "drawVerticalLine(double)\0radius\0"
    "drawCircle(double)\0angle\0drawPolarLine(double)\0"
    "coordinates,num,con\0"
    "drawPoints(long double*,int,bool)\0y,z\0"
    "draw3dXLine(double,double)\0x,z\0"
    "draw3dYLine(double,double)\0x,y\0"
    "draw3dZLine(double,double)\0removeLines()\0"
    "resetRotation()\0timerSlot()\0"
    "threadTimerSlot()\0screenshotSlot(int,int)\0"
    ",,\0drawSlot(int,QColor,int)\0"
    "timerStartSlot(bool)\0"
};

const QMetaObject GraphOutput::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GraphOutput,
      qt_meta_data_GraphOutput, 0 }
};

const QMetaObject *GraphOutput::metaObject() const
{
    return &staticMetaObject;
}

void *GraphOutput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphOutput))
        return static_cast<void*>(const_cast< GraphOutput*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GraphOutput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: leftMButtonPressed((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: redrawSignal(); break;
        case 3: screenshotSignal((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        case 4: solveRedrawSignal(); break;
        case 5: statisticsRedrawSignal(); break;
        case 6: processingFinished(); break;
        case 7: drawHorizontalLine((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: drawVerticalLine((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: drawCircle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: drawPolarLine((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: drawPoints((*reinterpret_cast< long double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 12: draw3dXLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 13: draw3dYLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 14: draw3dZLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 15: removeLines(); break;
        case 16: resetRotation(); break;
        case 17: timerSlot(); break;
        case 18: threadTimerSlot(); break;
        case 19: screenshotSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: drawSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 21: timerStartSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void GraphOutput::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphOutput::leftMButtonPressed(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GraphOutput::redrawSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GraphOutput::screenshotSignal(QPixmap * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GraphOutput::solveRedrawSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void GraphOutput::statisticsRedrawSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void GraphOutput::processingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
