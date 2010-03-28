/****************************************************************************
** Meta object code from reading C++ file 'graphsetdialog.h'
**
** Created: Sun Mar 28 18:04:11 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphsetdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphsetdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphSetDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      25,   15,   15,   15, 0x0a,
      38,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphSetDialog[] = {
    "GraphSetDialog\0\0okSlot()\0removeSlot()\0"
    "renameSlot()\0"
};

const QMetaObject GraphSetDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GraphSetDialog,
      qt_meta_data_GraphSetDialog, 0 }
};

const QMetaObject *GraphSetDialog::metaObject() const
{
    return &staticMetaObject;
}

void *GraphSetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphSetDialog))
        return static_cast<void*>(const_cast< GraphSetDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int GraphSetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: okSlot(); break;
        case 1: removeSlot(); break;
        case 2: renameSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
