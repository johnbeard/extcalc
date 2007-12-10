/****************************************************************************
** Catalog meta object code from reading C++ file 'catalog.h'
**
** Created: Sun Dec 9 19:59:33 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "catalog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Catalog::className() const
{
    return "Catalog";
}

QMetaObject *Catalog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Catalog( "Catalog", &Catalog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Catalog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Catalog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Catalog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Catalog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Catalog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QPopupMenu::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"mathStandardSlot", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"mathTrigonometricSlot", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"mathExtendedSlot", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"mathLogicSlot", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"matrixSlot", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"scriptStandardSlot", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"scriptTextSlot", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"scriptGraphicsSlot", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"scriptGLSlot", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"scriptFileSlot", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"constantsMathSlot", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"constantsPhysicsSlot", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"constantsConvSlot", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"constantsUserSlot", 1, param_slot_13 };
    static const QMetaData slot_tbl[] = {
	{ "mathStandardSlot(int)", &slot_0, QMetaData::Public },
	{ "mathTrigonometricSlot(int)", &slot_1, QMetaData::Public },
	{ "mathExtendedSlot(int)", &slot_2, QMetaData::Public },
	{ "mathLogicSlot(int)", &slot_3, QMetaData::Public },
	{ "matrixSlot(int)", &slot_4, QMetaData::Public },
	{ "scriptStandardSlot(int)", &slot_5, QMetaData::Public },
	{ "scriptTextSlot(int)", &slot_6, QMetaData::Public },
	{ "scriptGraphicsSlot(int)", &slot_7, QMetaData::Public },
	{ "scriptGLSlot(int)", &slot_8, QMetaData::Public },
	{ "scriptFileSlot(int)", &slot_9, QMetaData::Public },
	{ "constantsMathSlot(int)", &slot_10, QMetaData::Public },
	{ "constantsPhysicsSlot(int)", &slot_11, QMetaData::Public },
	{ "constantsConvSlot(int)", &slot_12, QMetaData::Public },
	{ "constantsUserSlot(int)", &slot_13, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"menuSignal", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "menuSignal(QString)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Catalog", parentObject,
	slot_tbl, 14,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Catalog.setMetaObject( metaObj );
    return metaObj;
}

void* Catalog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Catalog" ) )
	return this;
    return QPopupMenu::qt_cast( clname );
}

// SIGNAL menuSignal
void Catalog::menuSignal( QString t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool Catalog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: mathStandardSlot((int)static_QUType_int.get(_o+1)); break;
    case 1: mathTrigonometricSlot((int)static_QUType_int.get(_o+1)); break;
    case 2: mathExtendedSlot((int)static_QUType_int.get(_o+1)); break;
    case 3: mathLogicSlot((int)static_QUType_int.get(_o+1)); break;
    case 4: matrixSlot((int)static_QUType_int.get(_o+1)); break;
    case 5: scriptStandardSlot((int)static_QUType_int.get(_o+1)); break;
    case 6: scriptTextSlot((int)static_QUType_int.get(_o+1)); break;
    case 7: scriptGraphicsSlot((int)static_QUType_int.get(_o+1)); break;
    case 8: scriptGLSlot((int)static_QUType_int.get(_o+1)); break;
    case 9: scriptFileSlot((int)static_QUType_int.get(_o+1)); break;
    case 10: constantsMathSlot((int)static_QUType_int.get(_o+1)); break;
    case 11: constantsPhysicsSlot((int)static_QUType_int.get(_o+1)); break;
    case 12: constantsConvSlot((int)static_QUType_int.get(_o+1)); break;
    case 13: constantsUserSlot((int)static_QUType_int.get(_o+1)); break;
    default:
	return QPopupMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Catalog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: menuSignal((QString)static_QUType_QString.get(_o+1)); break;
    default:
	return QPopupMenu::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Catalog::qt_property( int id, int f, QVariant* v)
{
    return QPopupMenu::qt_property( id, f, v);
}

bool Catalog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
