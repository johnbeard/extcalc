/****************************************************************************
** Meta object code from reading C++ file 'scriptedit.h'
**
** Created: Fri Feb 6 17:36:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scriptedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      38,   13,   13,   13, 0x05,
      58,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   13,   13,   13, 0x0a,
     102,   13,   13,   13, 0x0a,
     127,   13,   13,   13, 0x0a,
     148,   13,   13,   13, 0x0a,
     162,   13,   13,   13, 0x0a,
     191,  188,   13,   13, 0x0a,
     246,  241,   13,   13, 0x0a,
     271,   13,   13,   13, 0x0a,
     289,   13,   13,   13, 0x0a,
     300,   13,   13,   13, 0x0a,
     318,  316,   13,   13, 0x0a,
     339,   13,   13,   13, 0x0a,
     353,   13,   13,   13, 0x0a,
     363,   13,   13,   13, 0x0a,
     376,   13,   13,   13, 0x0a,
     389,   13,   13,   13, 0x0a,
     406,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptWidget[] = {
    "ScriptWidget\0\0prefChange(Preferences)\0"
    "runScript(QString*)\0controlScriptMenu(int)\0"
    "getPref(Preferences)\0buttonInputSlot(QString)\0"
    "maximizeButtonSlot()\0editSlot(int)\0"
    "showFile(Q3ListViewItem*)\0,,\0"
    "createFileBrowserMenu(Q3ListViewItem*,QPoint,int)\0"
    "item\0fileBrowserMenuSlot(int)\0"
    "textChangedSlot()\0saveSlot()\0"
    "runButtonSlot()\0,\0lineNumSlot(int,int)\0"
    "saveallSlot()\0newSlot()\0importSlot()\0"
    "exportSlot()\0dockWindowSlot()\0"
    "catalogSlot()\0"
};

const QMetaObject ScriptWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScriptWidget,
      qt_meta_data_ScriptWidget, 0 }
};

const QMetaObject *ScriptWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ScriptWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptWidget))
        return static_cast<void*>(const_cast< ScriptWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScriptWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: runScript((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 2: controlScriptMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 4: buttonInputSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: maximizeButtonSlot(); break;
        case 6: editSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: showFile((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 8: createFileBrowserMenu((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: fileBrowserMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: textChangedSlot(); break;
        case 11: saveSlot(); break;
        case 12: runButtonSlot(); break;
        case 13: lineNumSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: saveallSlot(); break;
        case 15: newSlot(); break;
        case 16: importSlot(); break;
        case 17: exportSlot(); break;
        case 18: dockWindowSlot(); break;
        case 19: catalogSlot(); break;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void ScriptWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScriptWidget::runScript(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScriptWidget::controlScriptMenu(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
