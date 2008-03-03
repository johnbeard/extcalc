/****************************************************************************
** TableWidget meta object code from reading C++ file 'table.h'
**
** Created: Mon Mar 3 19:22:40 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "table.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TableWidget::className() const
{
    return "TableWidget";
}

QMetaObject *TableWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TableWidget( "TableWidget", &TableWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString TableWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TableWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TableWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TableWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TableWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "row", &static_QUType_int, 0, QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"selectionChangedSlot", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"tableEditSlot", 1, param_slot_2 };
    static const QUMethod slot_3 = {"inputTextChanged", 0, 0 };
    static const QUMethod slot_4 = {"calculateButtonSlot", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"typeBoxSlot", 1, param_slot_5 };
    static const QUMethod slot_6 = {"maximizeButtonSlot", 0, 0 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"buttonInputSlot", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"editSlot", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"horzHeaderSlot", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"vertHeaderSlot", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"tableMenuSlot", 1, param_slot_11 };
    static const QUMethod slot_12 = {"dockWindowSlot", 0, 0 };
    static const QUMethod slot_13 = {"catalogSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "selectionChangedSlot(int,int)", &slot_1, QMetaData::Public },
	{ "tableEditSlot(QString)", &slot_2, QMetaData::Public },
	{ "inputTextChanged()", &slot_3, QMetaData::Public },
	{ "calculateButtonSlot()", &slot_4, QMetaData::Public },
	{ "typeBoxSlot(const QString&)", &slot_5, QMetaData::Public },
	{ "maximizeButtonSlot()", &slot_6, QMetaData::Public },
	{ "buttonInputSlot(QString)", &slot_7, QMetaData::Public },
	{ "editSlot(int)", &slot_8, QMetaData::Public },
	{ "horzHeaderSlot(int)", &slot_9, QMetaData::Public },
	{ "vertHeaderSlot(int)", &slot_10, QMetaData::Public },
	{ "tableMenuSlot(int)", &slot_11, QMetaData::Public },
	{ "dockWindowSlot()", &slot_12, QMetaData::Public },
	{ "catalogSlot()", &slot_13, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"TableWidget", parentObject,
	slot_tbl, 14,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TableWidget.setMetaObject( metaObj );
    return metaObj;
}

void* TableWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TableWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void TableWidget::prefChange( Preferences t0 )
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

bool TableWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: selectionChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: tableEditSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 3: inputTextChanged(); break;
    case 4: calculateButtonSlot(); break;
    case 5: typeBoxSlot((const QString&)static_QUType_QString.get(_o+1)); break;
    case 6: maximizeButtonSlot(); break;
    case 7: buttonInputSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 8: editSlot((int)static_QUType_int.get(_o+1)); break;
    case 9: horzHeaderSlot((int)static_QUType_int.get(_o+1)); break;
    case 10: vertHeaderSlot((int)static_QUType_int.get(_o+1)); break;
    case 11: tableMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 12: dockWindowSlot(); break;
    case 13: catalogSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool TableWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool TableWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool TableWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
