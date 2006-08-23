/****************************************************************************
** CoordinatePreferences meta object code from reading C++ file 'graphpref.h'
**
** Created: Sun Aug 20 19:44:27 2006
**      by: The Qt MOC ($Id: moc_graphpref.cpp,v 1.28 2006/08/21 16:41:40 rainer1223 Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "graphpref.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CoordinatePreferences::className() const
{
    return "CoordinatePreferences";
}

QMetaObject *CoordinatePreferences::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CoordinatePreferences( "CoordinatePreferences", &CoordinatePreferences::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CoordinatePreferences::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CoordinatePreferences", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CoordinatePreferences::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CoordinatePreferences", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CoordinatePreferences::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"stdButtonSlot", 0, 0 };
    static const QUMethod slot_1 = {"angleButtonSlot", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"graphTypeSlot", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "pref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_3 = {"getPref", 1, param_slot_3 };
    static const QMetaData slot_tbl[] = {
	{ "stdButtonSlot()", &slot_0, QMetaData::Public },
	{ "angleButtonSlot()", &slot_1, QMetaData::Public },
	{ "graphTypeSlot(int)", &slot_2, QMetaData::Public },
	{ "getPref(Preferences)", &slot_3, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CoordinatePreferences", parentObject,
	slot_tbl, 4,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CoordinatePreferences.setMetaObject( metaObj );
    return metaObj;
}

void* CoordinatePreferences::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CoordinatePreferences" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void CoordinatePreferences::prefChange( Preferences t0 )
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

bool CoordinatePreferences::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: stdButtonSlot(); break;
    case 1: angleButtonSlot(); break;
    case 2: graphTypeSlot((int)static_QUType_int.get(_o+1)); break;
    case 3: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CoordinatePreferences::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CoordinatePreferences::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool CoordinatePreferences::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *ParameterPreferences::className() const
{
    return "ParameterPreferences";
}

QMetaObject *ParameterPreferences::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ParameterPreferences( "ParameterPreferences", &ParameterPreferences::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ParameterPreferences::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ParameterPreferences", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ParameterPreferences::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ParameterPreferences", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ParameterPreferences::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "pref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUMethod slot_1 = {"standardButtonSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "standardButtonSlot()", &slot_1, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ParameterPreferences", parentObject,
	slot_tbl, 2,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ParameterPreferences.setMetaObject( metaObj );
    return metaObj;
}

void* ParameterPreferences::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ParameterPreferences" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL prefChange
void ParameterPreferences::prefChange( Preferences t0 )
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

bool ParameterPreferences::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: standardButtonSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ParameterPreferences::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ParameterPreferences::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ParameterPreferences::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *DynamicPreferences::className() const
{
    return "DynamicPreferences";
}

QMetaObject *DynamicPreferences::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DynamicPreferences( "DynamicPreferences", &DynamicPreferences::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString DynamicPreferences::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DynamicPreferences", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DynamicPreferences::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DynamicPreferences", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DynamicPreferences::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "pref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"DynamicPreferences", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DynamicPreferences.setMetaObject( metaObj );
    return metaObj;
}

void* DynamicPreferences::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DynamicPreferences" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL prefChange
void DynamicPreferences::prefChange( Preferences t0 )
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

bool DynamicPreferences::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DynamicPreferences::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool DynamicPreferences::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool DynamicPreferences::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *GraphPreferences::className() const
{
    return "GraphPreferences";
}

QMetaObject *GraphPreferences::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GraphPreferences( "GraphPreferences", &GraphPreferences::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GraphPreferences::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphPreferences", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GraphPreferences::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphPreferences", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GraphPreferences::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTabWidget::staticMetaObject();
    static const QUMethod slot_0 = {"saveButtonSlot", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "pr", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_1 = {"getPref", 1, param_slot_1 };
    static const QMetaData slot_tbl[] = {
	{ "saveButtonSlot()", &slot_0, QMetaData::Public },
	{ "getPref(Preferences)", &slot_1, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GraphPreferences", parentObject,
	slot_tbl, 2,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GraphPreferences.setMetaObject( metaObj );
    return metaObj;
}

void* GraphPreferences::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GraphPreferences" ) )
	return this;
    return QTabWidget::qt_cast( clname );
}

// SIGNAL prefChange
void GraphPreferences::prefChange( Preferences t0 )
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

bool GraphPreferences::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: saveButtonSlot(); break;
    case 1: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QTabWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GraphPreferences::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QTabWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GraphPreferences::qt_property( int id, int f, QVariant* v)
{
    return QTabWidget::qt_property( id, f, v);
}

bool GraphPreferences::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
