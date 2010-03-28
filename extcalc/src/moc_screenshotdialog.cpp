/****************************************************************************
** Meta object code from reading C++ file 'screenshotdialog.h'
**
** Created: Sun Mar 28 16:45:56 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "screenshotdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenshotdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScreenshotDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x05,
      52,   49,   17,   17, 0x05,
      79,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      94,   17,   17,   17, 0x0a,
     119,   17,   17,   17, 0x0a,
     136,   17,   17,   17, 0x0a,
     154,   17,   17,   17, 0x0a,
     172,   17,   17,   17, 0x0a,
     192,   17,   17,   17, 0x0a,
     209,   17,   17,   17, 0x0a,
     227,   17,   17,   17, 0x0a,
     244,   17,   17,   17, 0x0a,
     261,   17,   17,   17, 0x0a,
     278,   17,   17,   17, 0x0a,
     297,   17,   17,   17, 0x0a,
     316,   17,   17,   17, 0x0a,
     333,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScreenshotDialog[] = {
    "ScreenshotDialog\0\0,\0getScreenshotSignal(int,int)\0"
    ",,\0drawSignal(int,QColor,int)\0"
    "redrawGraphs()\0screenshotSlot(QPixmap*)\0"
    "openButtonSlot()\0colorButtonSlot()\0"
    "penValueSlot(int)\0forwardButtonSlot()\0"
    "backButtonSlot()\0clearButtonSlot()\0"
    "freeButtonSlot()\0lineButtonSlot()\0"
    "rectButtonSlot()\0circleButtonSlot()\0"
    "rubberButtonSlot()\0textButtonSlot()\0"
    "saveButtonSlot()\0"
};

const QMetaObject ScreenshotDialog::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ScreenshotDialog,
      qt_meta_data_ScreenshotDialog, 0 }
};

const QMetaObject *ScreenshotDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ScreenshotDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenshotDialog))
        return static_cast<void*>(const_cast< ScreenshotDialog*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ScreenshotDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getScreenshotSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: drawSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: redrawGraphs(); break;
        case 3: screenshotSlot((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        case 4: openButtonSlot(); break;
        case 5: colorButtonSlot(); break;
        case 6: penValueSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: forwardButtonSlot(); break;
        case 8: backButtonSlot(); break;
        case 9: clearButtonSlot(); break;
        case 10: freeButtonSlot(); break;
        case 11: lineButtonSlot(); break;
        case 12: rectButtonSlot(); break;
        case 13: circleButtonSlot(); break;
        case 14: rubberButtonSlot(); break;
        case 15: textButtonSlot(); break;
        case 16: saveButtonSlot(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ScreenshotDialog::getScreenshotSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScreenshotDialog::drawSignal(int _t1, QColor _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScreenshotDialog::redrawGraphs()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
