/****************************************************************************
** MatrixWidget meta object code from reading C++ file 'matrixwidget.h'
**
** Created: Sun Apr 22 05:26:31 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "matrixwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MatrixWidget::className() const
{
    return "MatrixWidget";
}

QMetaObject *MatrixWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MatrixWidget( "MatrixWidget", &MatrixWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MatrixWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MatrixWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MatrixWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MatrixWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MatrixWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUMethod slot_1 = {"sprodButtonSlot", 0, 0 };
    static const QUMethod slot_2 = {"invertButtonSlot", 0, 0 };
    static const QUMethod slot_3 = {"detButtonSlot", 0, 0 };
    static const QUMethod slot_4 = {"braceOpenButtonSlot", 0, 0 };
    static const QUMethod slot_5 = {"braceCloseButtonSlot", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"operationBoxSlot", 1, param_slot_6 };
    static const QUMethod slot_7 = {"enterSlot", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"buttonInputSlot", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"varSelectionSlot", 2, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"varChangedSlot", 2, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"outputChangedSlot", 2, param_slot_11 };
    static const QUMethod slot_12 = {"calcButtonSlot", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"matrixBoxSlot", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"vectorBoxSlot", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"size1BoxSlot", 1, param_slot_15 };
    static const QUMethod slot_16 = {"sizeButtonSlot", 0, 0 };
    static const QUParameter param_slot_17[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_17 = {"typeBoxSlot", 1, param_slot_17 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "sprodButtonSlot()", &slot_1, QMetaData::Public },
	{ "invertButtonSlot()", &slot_2, QMetaData::Public },
	{ "detButtonSlot()", &slot_3, QMetaData::Public },
	{ "braceOpenButtonSlot()", &slot_4, QMetaData::Public },
	{ "braceCloseButtonSlot()", &slot_5, QMetaData::Public },
	{ "operationBoxSlot(int)", &slot_6, QMetaData::Public },
	{ "enterSlot()", &slot_7, QMetaData::Public },
	{ "buttonInputSlot(QString)", &slot_8, QMetaData::Public },
	{ "varSelectionSlot(int,int)", &slot_9, QMetaData::Public },
	{ "varChangedSlot(int,int)", &slot_10, QMetaData::Public },
	{ "outputChangedSlot(int,int)", &slot_11, QMetaData::Public },
	{ "calcButtonSlot()", &slot_12, QMetaData::Public },
	{ "matrixBoxSlot(int)", &slot_13, QMetaData::Public },
	{ "vectorBoxSlot(int)", &slot_14, QMetaData::Public },
	{ "size1BoxSlot(int)", &slot_15, QMetaData::Public },
	{ "sizeButtonSlot()", &slot_16, QMetaData::Public },
	{ "typeBoxSlot(int)", &slot_17, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MatrixWidget", parentObject,
	slot_tbl, 18,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MatrixWidget.setMetaObject( metaObj );
    return metaObj;
}

void* MatrixWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MatrixWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void MatrixWidget::prefChange( Preferences t0 )
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

bool MatrixWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: sprodButtonSlot(); break;
    case 2: invertButtonSlot(); break;
    case 3: detButtonSlot(); break;
    case 4: braceOpenButtonSlot(); break;
    case 5: braceCloseButtonSlot(); break;
    case 6: operationBoxSlot((int)static_QUType_int.get(_o+1)); break;
    case 7: enterSlot(); break;
    case 8: buttonInputSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 9: varSelectionSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 10: varChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 11: outputChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 12: calcButtonSlot(); break;
    case 13: matrixBoxSlot((int)static_QUType_int.get(_o+1)); break;
    case 14: vectorBoxSlot((int)static_QUType_int.get(_o+1)); break;
    case 15: size1BoxSlot((int)static_QUType_int.get(_o+1)); break;
    case 16: sizeButtonSlot(); break;
    case 17: typeBoxSlot((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MatrixWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool MatrixWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MatrixWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES