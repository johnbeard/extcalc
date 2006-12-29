/****************************************************************************
** MainObject meta object code from reading C++ file 'extcalc.h'
**
** Created: Thu Dec 28 21:00:07 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "extcalc.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
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
    static const QUMethod slot_14 = {"tableTypeMenuSlot", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ 0, &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod slot_15 = {"runScriptSlot", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "newPref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_16 = {"getPref", 1, param_slot_16 };
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
	{ "tableTypeMenuSlot(int)", &slot_14, QMetaData::Public },
	{ "runScriptSlot(QString*)", &slot_15, QMetaData::Public },
	{ "getPref(Preferences)", &slot_16, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"editSignal", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod signal_1 = {"runScript", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "editSignal(int)", &signal_0, QMetaData::Public },
	{ "runScript(QString*)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainObject", parentObject,
	slot_tbl, 17,
	signal_tbl, 2,
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
    case 14: tableTypeMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 15: runScriptSlot((QString*)static_QUType_varptr.get(_o+1)); break;
    case 16: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
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
