/****************************************************************************
** ConstantDialog meta object code from reading C++ file 'catalog.h'
**
** Created: Fri Mar 21 10:10:58 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "catalog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ConstantDialog::className() const
{
    return "ConstantDialog";
}

QMetaObject *ConstantDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ConstantDialog( "ConstantDialog", &ConstantDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ConstantDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ConstantDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ConstantDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ConstantDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ConstantDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"boxSlot", 0, 0 };
    static const QUMethod slot_1 = {"applySlot", 0, 0 };
    static const QUMethod slot_2 = {"removeSlot", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "newPref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_3 = {"setPref", 1, param_slot_3 };
    static const QMetaData slot_tbl[] = {
	{ "boxSlot()", &slot_0, QMetaData::Public },
	{ "applySlot()", &slot_1, QMetaData::Public },
	{ "removeSlot()", &slot_2, QMetaData::Public },
	{ "setPref(Preferences)", &slot_3, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ConstantDialog", parentObject,
	slot_tbl, 4,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ConstantDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ConstantDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ConstantDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void ConstantDialog::prefChange( Preferences t0 )
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

bool ConstantDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: boxSlot(); break;
    case 1: applySlot(); break;
    case 2: removeSlot(); break;
    case 3: setPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ConstantDialog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QDialog::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ConstantDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool ConstantDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


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
    static const QUMethod slot_10 = {"constantsSlot", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "pref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_11 = {"getPref", 1, param_slot_11 };
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
	{ "constantsSlot(int)", &slot_10, QMetaData::Public },
	{ "getPref(Preferences)", &slot_11, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"menuSignal", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_1 = {"prefChange", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "menuSignal(QString)", &signal_0, QMetaData::Public },
	{ "prefChange(Preferences)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Catalog", parentObject,
	slot_tbl, 12,
	signal_tbl, 2,
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

// SIGNAL prefChange
void Catalog::prefChange( Preferences t0 )
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
    case 10: constantsSlot((int)static_QUType_int.get(_o+1)); break;
    case 11: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QPopupMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Catalog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: menuSignal((QString)static_QUType_QString.get(_o+1)); break;
    case 1: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
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
