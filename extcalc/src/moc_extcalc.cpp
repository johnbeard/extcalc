/****************************************************************************
** Meta object code from reading C++ file 'extcalc.h'
**
** Created: Sun Mar 28 18:03:51 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "extcalc.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extcalc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainObject[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   11,   11,   11, 0x05,
      48,   11,   11,   11, 0x05,
      68,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     101,   96,   11,   11, 0x0a,
     119,   96,   11,   11, 0x0a,
     137,   96,   11,   11, 0x0a,
     160,  155,   11,   11, 0x0a,
     179,   96,   11,   11, 0x0a,
     199,   96,   11,   11, 0x0a,
     223,   96,   11,   11, 0x0a,
     246,   96,   11,   11, 0x0a,
     265,   96,   11,   11, 0x0a,
     287,   11,   11,   11, 0x0a,
     305,   96,   11,   11, 0x0a,
     323,   96,   11,   11, 0x0a,
     341,   96,   11,   11, 0x0a,
     359,   96,   11,   11, 0x0a,
     381,   96,   11,   11, 0x0a,
     400,   96,   11,   11, 0x0a,
     420,   96,   11,   11, 0x0a,
     444,   96,   11,   11, 0x0a,
     467,   96,   11,   11, 0x0a,
     489,   96,   11,   11, 0x0a,
     513,   11,   11,   11, 0x0a,
     538,   11,   11,   11, 0x0a,
     562,   11,   11,   11, 0x0a,
     587,  581,   11,   11, 0x0a,
     614,  606,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainObject[] = {
    "MainObject\0\0editSignal(int)\0"
    "runScript(QString*)\0matrixEnterSignal()\0"
    "removeGraphicsLinesSignal()\0item\0"
    "fileMenuSlot(int)\0editMenuSlot(int)\0"
    "viewMenuSlot(int)\0type\0angleMenuSlot(int)\0"
    "outputMenuSlot(int)\0coordinateMenuSlot(int)\0"
    "graphTypeMenuSlot(int)\0graphMenuSlot(int)\0"
    "calcModeMenuSlot(int)\0calcComplexSlot()\0"
    "baseMenuSlot(int)\0helpMenuSlot(int)\0"
    "prefMenuSlot(int)\0languageMenuSlot(int)\0"
    "tableMenuSlot(int)\0scriptMenuSlot(int)\0"
    "statisticsMenuSlot(int)\0tableTypeMenuSlot(int)\0"
    "graphSetMenuSlot(int)\0floatPointMenuSlot(int)\0"
    "updateGraphSetMenuSlot()\0"
    "runScriptSlot(QString*)\0changeTabSlot(int)\0"
    "index\0tabChangeSlot(int)\0newPref\0"
    "getPref(Preferences)\0"
};

const QMetaObject MainObject::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainObject,
      qt_meta_data_MainObject, 0 }
};

const QMetaObject *MainObject::metaObject() const
{
    return &staticMetaObject;
}

void *MainObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainObject))
        return static_cast<void*>(const_cast< MainObject*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: runScript((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 2: matrixEnterSignal(); break;
        case 3: removeGraphicsLinesSignal(); break;
        case 4: fileMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: editMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: viewMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: angleMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: outputMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: coordinateMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: graphTypeMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: graphMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: calcModeMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: calcComplexSlot(); break;
        case 14: baseMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: helpMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: prefMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: languageMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: tableMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: scriptMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: statisticsMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: tableTypeMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: graphSetMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: floatPointMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: updateGraphSetMenuSlot(); break;
        case 25: runScriptSlot((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 26: changeTabSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: tabChangeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void MainObject::editSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainObject::runScript(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainObject::matrixEnterSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainObject::removeGraphicsLinesSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_HelpBrowser[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HelpBrowser[] = {
    "HelpBrowser\0\0zoominSlot()\0zoomoutSlot()\0"
    "sourceSlot(QString)\0"
};

const QMetaObject HelpBrowser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HelpBrowser,
      qt_meta_data_HelpBrowser, 0 }
};

const QMetaObject *HelpBrowser::metaObject() const
{
    return &staticMetaObject;
}

void *HelpBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HelpBrowser))
        return static_cast<void*>(const_cast< HelpBrowser*>(this));
    return QWidget::qt_metacast(_clname);
}

int HelpBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: zoominSlot(); break;
        case 1: zoomoutSlot(); break;
        case 2: sourceSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_InfoDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_InfoDialog[] = {
    "InfoDialog\0"
};

const QMetaObject InfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InfoDialog,
      qt_meta_data_InfoDialog, 0 }
};

const QMetaObject *InfoDialog::metaObject() const
{
    return &staticMetaObject;
}

void *InfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InfoDialog))
        return static_cast<void*>(const_cast< InfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
