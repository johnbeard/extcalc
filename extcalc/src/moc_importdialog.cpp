/****************************************************************************
** ImportDialog meta object code from reading C++ file 'importdialog.h'
**
** Created: Thu Mar 27 18:08:50 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "importdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

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
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_1 = {"prefChange", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "updateScriptSignal(int)", &signal_0, QMetaData::Public },
	{ "prefChange(Preferences)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ImportDialog", parentObject,
	slot_tbl, 3,
	signal_tbl, 2,
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

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void ImportDialog::prefChange( Preferences t0 )
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
    case 1: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
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
