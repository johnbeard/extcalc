/****************************************************************************
** CalcWidget meta object code from reading C++ file 'calcwidget.h'
**
** Created: Mon Sep 10 15:00:39 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "calcwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CalcWidget::className() const
{
    return "CalcWidget";
}

QMetaObject *CalcWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CalcWidget( "CalcWidget", &CalcWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CalcWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CalcWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CalcWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CalcWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CalcWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "newPref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUMethod slot_1 = {"viewSlot", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"baseSlot", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"angleSlot", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"typeSlot", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"editSlot", 1, param_slot_5 };
    static const QUMethod slot_6 = {"catalogSlot", 0, 0 };
    static const QUMethod slot_7 = {"dockWindowSlot", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"processText", 1, param_slot_8 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "viewSlot()", &slot_1, QMetaData::Public },
	{ "baseSlot(int)", &slot_2, QMetaData::Public },
	{ "angleSlot(int)", &slot_3, QMetaData::Public },
	{ "typeSlot(int)", &slot_4, QMetaData::Public },
	{ "editSlot(int)", &slot_5, QMetaData::Public },
	{ "catalogSlot()", &slot_6, QMetaData::Public },
	{ "dockWindowSlot()", &slot_7, QMetaData::Public },
	{ "processText(QString)", &slot_8, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod signal_1 = {"runScript", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public },
	{ "runScript(QString*)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CalcWidget", parentObject,
	slot_tbl, 9,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CalcWidget.setMetaObject( metaObj );
    return metaObj;
}

void* CalcWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CalcWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void CalcWidget::prefChange( Preferences t0 )
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

// SIGNAL runScript
void CalcWidget::runScript( QString* t0 )
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

bool CalcWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: viewSlot(); break;
    case 2: baseSlot((int)static_QUType_int.get(_o+1)); break;
    case 3: angleSlot((int)static_QUType_int.get(_o+1)); break;
    case 4: typeSlot((int)static_QUType_int.get(_o+1)); break;
    case 5: editSlot((int)static_QUType_int.get(_o+1)); break;
    case 6: catalogSlot(); break;
    case 7: dockWindowSlot(); break;
    case 8: processText((QString)static_QUType_QString.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CalcWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: runScript((QString*)static_QUType_varptr.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CalcWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool CalcWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
