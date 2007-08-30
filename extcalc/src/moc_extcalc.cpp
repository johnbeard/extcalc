/****************************************************************************
** MainObject meta object code from reading C++ file 'extcalc.h'
**
** Created: Thu Aug 30 18:34:57 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "extcalc.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainObject::className() const
{
    return "MainObject";
}

QMetaObject *MainObject::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainObject( "MainObject", &MainObject::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainObject::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainObject", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainObject::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainObject", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainObject::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTabWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"fileMenuSlot", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"editMenuSlot", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"viewMenuSlot", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"angleMenuSlot", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_ptr, "QWidget", QUParameter::In }
    };
    static const QUMethod slot_4 = {"tabChangeSlot", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"outputMenuSlot", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"coordinateMenuSlot", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"graphTypeMenuSlot", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"floatPointMenuSlot", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"calcTypeMenuSlot", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"baseMenuSlot", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"helpMenuSlot", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"prefMenuSlot", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"tableMenuSlot", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"scriptMenuSlot", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"statisticsMenuSlot", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"tableTypeMenuSlot", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ 0, &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod slot_17 = {"runScriptSlot", 1, param_slot_17 };
    static const QUParameter param_slot_18[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_18 = {"changeTabSlot", 1, param_slot_18 };
    static const QUParameter param_slot_19[] = {
	{ "newPref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_19 = {"getPref", 1, param_slot_19 };
    static const QMetaData slot_tbl[] = {
	{ "fileMenuSlot(int)", &slot_0, QMetaData::Public },
	{ "editMenuSlot(int)", &slot_1, QMetaData::Public },
	{ "viewMenuSlot(int)", &slot_2, QMetaData::Public },
	{ "angleMenuSlot(int)", &slot_3, QMetaData::Public },
	{ "tabChangeSlot(QWidget*)", &slot_4, QMetaData::Public },
	{ "outputMenuSlot(int)", &slot_5, QMetaData::Public },
	{ "coordinateMenuSlot(int)", &slot_6, QMetaData::Public },
	{ "graphTypeMenuSlot(int)", &slot_7, QMetaData::Public },
	{ "floatPointMenuSlot(int)", &slot_8, QMetaData::Public },
	{ "calcTypeMenuSlot(int)", &slot_9, QMetaData::Public },
	{ "baseMenuSlot(int)", &slot_10, QMetaData::Public },
	{ "helpMenuSlot(int)", &slot_11, QMetaData::Public },
	{ "prefMenuSlot(int)", &slot_12, QMetaData::Public },
	{ "tableMenuSlot(int)", &slot_13, QMetaData::Public },
	{ "scriptMenuSlot(int)", &slot_14, QMetaData::Public },
	{ "statisticsMenuSlot(int)", &slot_15, QMetaData::Public },
	{ "tableTypeMenuSlot(int)", &slot_16, QMetaData::Public },
	{ "runScriptSlot(QString*)", &slot_17, QMetaData::Public },
	{ "changeTabSlot(int)", &slot_18, QMetaData::Public },
	{ "getPref(Preferences)", &slot_19, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"editSignal", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod signal_1 = {"runScript", 1, param_signal_1 };
    static const QUMethod signal_2 = {"matrixEnterSignal", 0, 0 };
    static const QUMethod signal_3 = {"removeGraphicsLinesSignal", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "editSignal(int)", &signal_0, QMetaData::Public },
	{ "runScript(QString*)", &signal_1, QMetaData::Public },
	{ "matrixEnterSignal()", &signal_2, QMetaData::Public },
	{ "removeGraphicsLinesSignal()", &signal_3, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainObject", parentObject,
	slot_tbl, 20,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainObject.setMetaObject( metaObj );
    return metaObj;
}

void* MainObject::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainObject" ) )
	return this;
    return QTabWidget::qt_cast( clname );
}

// SIGNAL editSignal
void MainObject::editSignal( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL runScript
void MainObject::runScript( QString* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_varptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL matrixEnterSignal
void MainObject::matrixEnterSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

// SIGNAL removeGraphicsLinesSignal
void MainObject::removeGraphicsLinesSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 3 );
}

bool MainObject::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: fileMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 1: editMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 2: viewMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 3: angleMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 4: tabChangeSlot((QWidget*)static_QUType_ptr.get(_o+1)); break;
    case 5: outputMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 6: coordinateMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 7: graphTypeMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 8: floatPointMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 9: calcTypeMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 10: baseMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 11: helpMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 12: prefMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 13: tableMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 14: scriptMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 15: statisticsMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 16: tableTypeMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 17: runScriptSlot((QString*)static_QUType_varptr.get(_o+1)); break;
    case 18: changeTabSlot((int)static_QUType_int.get(_o+1)); break;
    case 19: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QTabWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainObject::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: editSignal((int)static_QUType_int.get(_o+1)); break;
    case 1: runScript((QString*)static_QUType_varptr.get(_o+1)); break;
    case 2: matrixEnterSignal(); break;
    case 3: removeGraphicsLinesSignal(); break;
    default:
	return QTabWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool MainObject::qt_property( int id, int f, QVariant* v)
{
    return QTabWidget::qt_property( id, f, v);
}

bool MainObject::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *ImportDialog::className() const
{
    return "ImportDialog";
}

QMetaObject *ImportDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ImportDialog( "ImportDialog", &ImportDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ImportDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ImportDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ImportDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ImportDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ImportDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"saveSlot", 0, 0 };
    static const QUMethod slot_1 = {"openDialogSlot", 0, 0 };
    static const QUMethod slot_2 = {"saveDialogSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "saveSlot()", &slot_0, QMetaData::Public },
	{ "openDialogSlot()", &slot_1, QMetaData::Public },
	{ "saveDialogSlot()", &slot_2, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"updateScriptSignal", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "updateScriptSignal(int)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ImportDialog", parentObject,
	slot_tbl, 3,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ImportDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ImportDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ImportDialog" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL updateScriptSignal
void ImportDialog::updateScriptSignal( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool ImportDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: saveSlot(); break;
    case 1: openDialogSlot(); break;
    case 2: saveDialogSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ImportDialog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: updateScriptSignal((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ImportDialog::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ImportDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
