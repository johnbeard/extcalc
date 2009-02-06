/****************************************************************************
** Meta object code from reading C++ file 'statistics.h'
**
** Created: Wed Dec 31 16:18:11 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "statistics.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statistics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatisticsWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      42,   17,   17,   17, 0x05,
      56,   17,   17,   17, 0x05,
      80,   77,   17,   17, 0x05,
     120,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     140,   17,   17,   17, 0x0a,
     161,   17,   17,   17, 0x0a,
     182,   17,   17,   17, 0x0a,
     199,   17,   17,   17, 0x0a,
     223,  221,   17,   17, 0x0a,
     248,   17,   17,   17, 0x0a,
     265,   17,   17,   17, 0x0a,
     283,   17,   17,   17, 0x0a,
     308,   17,   17,   17, 0x0a,
     326,   17,   17,   17, 0x0a,
     343,   17,   17,   17, 0x0a,
     365,  357,   17,   17, 0x0a,
     395,   17,   17,   17, 0x0a,
     418,   17,   17,   17, 0x0a,
     444,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StatisticsWidget[] = {
    "StatisticsWidget\0\0prefChange(Preferences)\0"
    "printSignal()\0changeTabSignal(int)\0"
    ",,\0drawPointsSignal(long double*,int,bool)\0"
    "removeLinesSignal()\0getPref(Preferences)\0"
    "maximizeButtonSlot()\0typeBoxSlot(int)\0"
    "calculateButtonSlot()\0,\0"
    "itemChangedSlot(int,int)\0copyButtonSlot()\0"
    "printButtonSlot()\0buttonInputSlot(QString)\0"
    "redrawGraphSlot()\0dockWindowSlot()\0"
    "catalogSlot()\0row,col\0"
    "selectionChangedSlot(int,int)\0"
    "tableEditSlot(QString)\0inputTextChanged(QString)\0"
    "inputTextFinished()\0"
};

const QMetaObject StatisticsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StatisticsWidget,
      qt_meta_data_StatisticsWidget, 0 }
};

const QMetaObject *StatisticsWidget::metaObject() const
{
    return &staticMetaObject;
}

void *StatisticsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatisticsWidget))
        return static_cast<void*>(const_cast< StatisticsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StatisticsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: printSignal(); break;
        case 2: changeTabSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: drawPointsSignal((*reinterpret_cast< long double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: removeLinesSignal(); break;
        case 5: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 6: maximizeButtonSlot(); break;
        case 7: typeBoxSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: calculateButtonSlot(); break;
        case 9: itemChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: copyButtonSlot(); break;
        case 11: printButtonSlot(); break;
        case 12: buttonInputSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: redrawGraphSlot(); break;
        case 14: dockWindowSlot(); break;
        case 15: catalogSlot(); break;
        case 16: selectionChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: tableEditSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: inputTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: inputTextFinished(); break;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void StatisticsWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StatisticsWidget::printSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void StatisticsWidget::changeTabSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StatisticsWidget::drawPointsSignal(long double * _t1, int _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StatisticsWidget::removeLinesSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
