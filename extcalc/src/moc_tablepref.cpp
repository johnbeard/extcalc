/****************************************************************************
** TablePreferences meta object code from reading C++ file 'tablepref.h'
**
** Created: Thu Feb 22 12:16:27 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "tablepref.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TablePreferences::className() const
{
    return "TablePreferences";
}

QMetaObject *TablePreferences::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TablePreferences( "TablePreferences", &TablePreferences::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString TablePreferences::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TablePreferences", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TablePreferences::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TablePreferences", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TablePreferences::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"saveSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "saveSlot()", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"TablePreferences", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TablePreferences.setMetaObject( metaObj );
    return metaObj;
}

void* TablePreferences::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TablePreferences" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void TablePreferences::prefChange( Preferences t0 )
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

bool TablePreferences::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: saveSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool TablePreferences::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool TablePreferences::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool TablePreferences::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
