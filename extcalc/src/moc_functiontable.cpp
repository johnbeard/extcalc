/****************************************************************************
** FunctionTable meta object code from reading C++ file 'functiontable.h'
**
** Created: Sat May 19 19:59:26 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "functiontable.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FunctionTable::className() const
{
    return "FunctionTable";
}

QMetaObject *FunctionTable::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FunctionTable( "FunctionTable", &FunctionTable::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FunctionTable::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FunctionTable", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FunctionTable::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FunctionTable", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FunctionTable::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = CalcTable::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "row", &static_QUType_int, 0, QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"cellChangedSlot", 2, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "row", &static_QUType_int, 0, QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"editStartedSlot", 2, param_slot_1 };
    static const QMetaData slot_tbl[] = {
	{ "cellChangedSlot(int,int)", &slot_0, QMetaData::Public },
	{ "editStartedSlot(int,int)", &slot_1, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"textEditStarted", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public },
	{ "textEditStarted(QString)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"FunctionTable", parentObject,
	slot_tbl, 2,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FunctionTable.setMetaObject( metaObj );
    return metaObj;
}

void* FunctionTable::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FunctionTable" ) )
	return this;
    return CalcTable::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void FunctionTable::prefChange( Preferences t0 )
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

// SIGNAL textEditStarted
void FunctionTable::textEditStarted( QString t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

bool FunctionTable::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: cellChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 1: editStartedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    default:
	return CalcTable::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool FunctionTable::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: textEditStarted((QString)static_QUType_QString.get(_o+1)); break;
    default:
	return CalcTable::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool FunctionTable::qt_property( int id, int f, QVariant* v)
{
    return CalcTable::qt_property( id, f, v);
}

bool FunctionTable::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
