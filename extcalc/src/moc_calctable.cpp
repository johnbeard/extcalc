/****************************************************************************
** CalcTable meta object code from reading C++ file 'calctable.h'
**
** Created: Thu Mar 1 08:11:21 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "calctable.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CalcTable::className() const
{
    return "CalcTable";
}

QMetaObject *CalcTable::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CalcTable( "CalcTable", &CalcTable::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CalcTable::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CalcTable", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CalcTable::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CalcTable", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CalcTable::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTable::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"cellEditStarted", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "cellEditStarted(int,int)", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"CalcTable", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CalcTable.setMetaObject( metaObj );
    return metaObj;
}

void* CalcTable::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CalcTable" ) )
	return this;
    return QTable::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL cellEditStarted
void CalcTable::cellEditStarted( int t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

bool CalcTable::qt_invoke( int _id, QUObject* _o )
{
    return QTable::qt_invoke(_id,_o);
}

bool CalcTable::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: cellEditStarted((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    default:
	return QTable::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CalcTable::qt_property( int id, int f, QVariant* v)
{
    return QTable::qt_property( id, f, v);
}

bool CalcTable::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
