/****************************************************************************
** Meta object code from reading C++ file 'scriptio.h'
**
** Created: Sun Mar 28 18:04:06 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scriptio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptGL[] = {

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

static const char qt_meta_stringdata_ScriptGL[] = {
    "ScriptGL\0"
};

const QMetaObject ScriptGL::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ScriptGL,
      qt_meta_data_ScriptGL, 0 }
};

const QMetaObject *ScriptGL::metaObject() const
{
    return &staticMetaObject;
}

void *ScriptGL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptGL))
        return static_cast<void*>(const_cast< ScriptGL*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ScriptGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ScriptIOWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   40,   15,   15, 0x0a,
      69,   15,   15,   15, 0x0a,
      90,   15,   15,   15, 0x0a,
     106,  101,   15,   15, 0x0a,
     132,  127,   15,   15, 0x0a,
     152,   15,   15,   15, 0x0a,
     166,   15,   15,   15, 0x0a,
     178,   15,   15,   15, 0x0a,
     188,   15,   15,   15, 0x0a,
     203,   15,   15,   15, 0x0a,
     220,   15,   15,   15, 0x0a,
     243,  241,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptIOWidget[] = {
    "ScriptIOWidget\0\0prefChange(Preferences)\0"
    "newPref\0getPref(Preferences)\0"
    "maximizeButtonSlot()\0killSlot()\0text\0"
    "processText(QString)\0code\0runScript(QString*)\0"
    "editSlot(int)\0timerSlot()\0runSlot()\0"
    "clearMemSlot()\0dockWindowSlot()\0"
    "contextMenuSlot(int)\0,\0scrollPointSlot(int,int)\0"
};

const QMetaObject ScriptIOWidget::staticMetaObject = {
    { &TabWidget::staticMetaObject, qt_meta_stringdata_ScriptIOWidget,
      qt_meta_data_ScriptIOWidget, 0 }
};

const QMetaObject *ScriptIOWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ScriptIOWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptIOWidget))
        return static_cast<void*>(const_cast< ScriptIOWidget*>(this));
    return TabWidget::qt_metacast(_clname);
}

int ScriptIOWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 1: getPref((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: maximizeButtonSlot(); break;
        case 3: killSlot(); break;
        case 4: processText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: runScript((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 6: editSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: timerSlot(); break;
        case 8: runSlot(); break;
        case 9: clearMemSlot(); break;
        case 10: dockWindowSlot(); break;
        case 11: contextMenuSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: scrollPointSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ScriptIOWidget::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
