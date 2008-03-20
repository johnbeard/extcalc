/****************************************************************************
** GraphSetDialog meta object code from reading C++ file 'graphsetdialog.h'
**
** Created: Thu Mar 20 18:02:38 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "graphsetdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GraphSetDialog::className() const
{
    return "GraphSetDialog";
}

QMetaObject *GraphSetDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GraphSetDialog( "GraphSetDialog", &GraphSetDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GraphSetDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphSetDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GraphSetDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphSetDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GraphSetDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"okSlot", 0, 0 };
    static const QUMethod slot_1 = {"removeSlot", 0, 0 };
    static const QUMethod slot_2 = {"renameSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "okSlot()", &slot_0, QMetaData::Public },
	{ "removeSlot()", &slot_1, QMetaData::Public },
	{ "renameSlot()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GraphSetDialog", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GraphSetDialog.setMetaObject( metaObj );
    return metaObj;
}

void* GraphSetDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GraphSetDialog" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool GraphSetDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: okSlot(); break;
    case 1: removeSlot(); break;
    case 2: renameSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GraphSetDialog::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool GraphSetDialog::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool GraphSetDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
