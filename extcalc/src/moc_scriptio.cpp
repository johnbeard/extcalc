/****************************************************************************
** ScriptIOWidget meta object code from reading C++ file 'scriptio.h'
**
** Created: Tue Sep 26 19:15:11 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "scriptio.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ScriptIOWidget::className() const
{
    return "ScriptIOWidget";
}

QMetaObject *ScriptIOWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ScriptIOWidget( "ScriptIOWidget", &ScriptIOWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ScriptIOWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ScriptIOWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ScriptIOWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ScriptIOWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ScriptIOWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "newPref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUMethod slot_1 = {"maximizeSlot", 0, 0 };
    static const QUMethod slot_2 = {"killSlot", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"processText", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "code", &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod slot_4 = {"runScript", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"editSlot", 1, param_slot_5 };
    static const QUMethod slot_6 = {"timerSlot", 0, 0 };
    static const QUMethod slot_7 = {"runSlot", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"scrollbarSlot", 1, param_slot_8 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "maximizeSlot()", &slot_1, QMetaData::Public },
	{ "killSlot()", &slot_2, QMetaData::Public },
	{ "processText(QString)", &slot_3, QMetaData::Public },
	{ "runScript(QString*)", &slot_4, QMetaData::Public },
	{ "editSlot(int)", &slot_5, QMetaData::Public },
	{ "timerSlot()", &slot_6, QMetaData::Public },
	{ "runSlot()", &slot_7, QMetaData::Public },
	{ "scrollbarSlot(int)", &slot_8, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ScriptIOWidget", parentObject,
	slot_tbl, 9,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ScriptIOWidget.setMetaObject( metaObj );
    return metaObj;
}

void* ScriptIOWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ScriptIOWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void ScriptIOWidget::prefChange( Preferences t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

bool ScriptIOWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: maximizeSlot(); break;
    case 2: killSlot(); break;
    case 3: processText((QString)static_QUType_QString.get(_o+1)); break;
    case 4: runScript((QString*)static_QUType_varptr.get(_o+1)); break;
    case 5: editSlot((int)static_QUType_int.get(_o+1)); break;
    case 6: timerSlot(); break;
    case 7: runSlot(); break;
    case 8: scrollbarSlot((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ScriptIOWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ScriptIOWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ScriptIOWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
