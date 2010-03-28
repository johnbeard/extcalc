/****************************************************************************
** Meta object code from reading C++ file 'importdialog.h'
**
** Created: Sun Mar 28 18:04:10 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "importdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'importdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImportDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      38,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   13,   13,   13, 0x0a,
      73,   13,   13,   13, 0x0a,
      90,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImportDialog[] = {
    "ImportDialog\0\0updateScriptSignal(int)\0"
    "prefChange(Preferences)\0saveSlot()\0"
    "openDialogSlot()\0saveDialogSlot()\0"
};

const QMetaObject ImportDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImportDialog,
      qt_meta_data_ImportDialog, 0 }
};

const QMetaObject *ImportDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ImportDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImportDialog))
        return static_cast<void*>(const_cast< ImportDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImportDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateScriptSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: prefChange((*reinterpret_cast< Preferences(*)>(_a[1]))); break;
        case 2: saveSlot(); break;
        case 3: openDialogSlot(); break;
        case 4: saveDialogSlot(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ImportDialog::updateScriptSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImportDialog::prefChange(Preferences _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
