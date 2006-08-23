/****************************************************************************
** StandardButtons meta object code from reading C++ file 'buttons.h'
**
** Created: Sun Aug 20 19:44:27 2006
**      by: The Qt MOC ($Id: moc_buttons.cpp,v 1.28 2006/08/21 16:41:40 rainer1223 Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "buttons.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StandardButtons::className() const
{
    return "StandardButtons";
}

QMetaObject *StandardButtons::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StandardButtons( "StandardButtons", &StandardButtons::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StandardButtons::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StandardButtons", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StandardButtons::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StandardButtons", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StandardButtons::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QButtonGroup::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"buttonSlot", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "buttonSlot(int)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"emitText", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_1 = {"prefChange", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "emitText(QString)", &signal_0, QMetaData::Public },
	{ "prefChange(Preferences)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"StandardButtons", parentObject,
	slot_tbl, 1,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StandardButtons.setMetaObject( metaObj );
    return metaObj;
}

void* StandardButtons::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StandardButtons" ) )
	return this;
    return QButtonGroup::qt_cast( clname );
}

// SIGNAL emitText
void StandardButtons::emitText( QString t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void StandardButtons::prefChange( Preferences t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

bool StandardButtons::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: buttonSlot((int)static_QUType_int.get(_o+1)); break;
    default:
	return QButtonGroup::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool StandardButtons::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: emitText((QString)static_QUType_QString.get(_o+1)); break;
    case 1: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QButtonGroup::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool StandardButtons::qt_property( int id, int f, QVariant* v)
{
    return QButtonGroup::qt_property( id, f, v);
}

bool StandardButtons::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *ExtButtons::className() const
{
    return "ExtButtons";
}

QMetaObject *ExtButtons::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ExtButtons( "ExtButtons", &ExtButtons::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ExtButtons::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ExtButtons", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ExtButtons::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ExtButtons", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ExtButtons::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QButtonGroup::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"buttonSlot", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "buttonSlot(int)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"emitText", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_1 = {"prefChange", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "emitText(QString)", &signal_0, QMetaData::Public },
	{ "prefChange(Preferences)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ExtButtons", parentObject,
	slot_tbl, 1,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ExtButtons.setMetaObject( metaObj );
    return metaObj;
}

void* ExtButtons::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ExtButtons" ) )
	return this;
    return QButtonGroup::qt_cast( clname );
}

// SIGNAL emitText
void ExtButtons::emitText( QString t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL prefChange
void ExtButtons::prefChange( Preferences t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

bool ExtButtons::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: buttonSlot((int)static_QUType_int.get(_o+1)); break;
    default:
	return QButtonGroup::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ExtButtons::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: emitText((QString)static_QUType_QString.get(_o+1)); break;
    case 1: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QButtonGroup::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ExtButtons::qt_property( int id, int f, QVariant* v)
{
    return QButtonGroup::qt_property( id, f, v);
}

bool ExtButtons::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
