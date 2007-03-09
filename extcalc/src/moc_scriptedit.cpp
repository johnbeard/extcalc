/****************************************************************************
** ScriptWidget meta object code from reading C++ file 'scriptedit.h'
**
** Created: Fri Mar 9 13:17:43 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "scriptedit.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ScriptWidget::className() const
{
    return "ScriptWidget";
}

QMetaObject *ScriptWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ScriptWidget( "ScriptWidget", &ScriptWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ScriptWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ScriptWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ScriptWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ScriptWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ScriptWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"buttonInputSlot", 1, param_slot_1 };
    static const QUMethod slot_2 = {"maximizeButtonSlot", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"editSlot", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_4 = {"showFile", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In },
	{ 0, &static_QUType_varptr, "\x0e", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"createFileBrowserMenu", 3, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "item", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"fileBrowserMenuSlot", 1, param_slot_6 };
    static const QUMethod slot_7 = {"textChangedSlot", 0, 0 };
    static const QUMethod slot_8 = {"saveSlot", 0, 0 };
    static const QUMethod slot_9 = {"runButtonSlot", 0, 0 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"lineNumSlot", 2, param_slot_10 };
    static const QUMethod slot_11 = {"saveallSlot", 0, 0 };
    static const QUMethod slot_12 = {"newSlot", 0, 0 };
    static const QUMethod slot_13 = {"importSlot", 0, 0 };
    static const QUMethod slot_14 = {"exportSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "buttonInputSlot(QString)", &slot_1, QMetaData::Public },
	{ "maximizeButtonSlot()", &slot_2, QMetaData::Public },
	{ "editSlot(int)", &slot_3, QMetaData::Public },
	{ "showFile(QListViewItem*)", &slot_4, QMetaData::Public },
	{ "createFileBrowserMenu(QListViewItem*,const QPoint&,int)", &slot_5, QMetaData::Public },
	{ "fileBrowserMenuSlot(int)", &slot_6, QMetaData::Public },
	{ "textChangedSlot()", &slot_7, QMetaData::Public },
	{ "saveSlot()", &slot_8, QMetaData::Public },
	{ "runButtonSlot()", &slot_9, QMetaData::Public },
	{ "lineNumSlot(int,int)", &slot_10, QMetaData::Public },
	{ "saveallSlot()", &slot_11, QMetaData::Public },
	{ "newSlot()", &slot_12, QMetaData::Public },
	{ "importSlot()", &slot_13, QMetaData::Public },
	{ "exportSlot()", &slot_14, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_varptr, "\x03", QUParameter::In }
    };
    static const QUMethod signal_1 = {"runScript", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"controlScriptMenu", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Protected },
	{ "runScript(QString*)", &signal_1, QMetaData::Protected },
	{ "controlScriptMenu(int)", &signal_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"ScriptWidget", parentObject,
	slot_tbl, 15,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ScriptWidget.setMetaObject( metaObj );
    return metaObj;
}

void* ScriptWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ScriptWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void ScriptWidget::prefChange( Preferences t0 )
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

// SIGNAL runScript
void ScriptWidget::runScript( QString* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_varptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL controlScriptMenu
void ScriptWidget::controlScriptMenu( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

bool ScriptWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: buttonInputSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 2: maximizeButtonSlot(); break;
    case 3: editSlot((int)static_QUType_int.get(_o+1)); break;
    case 4: showFile((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 5: createFileBrowserMenu((QListViewItem*)static_QUType_ptr.get(_o+1),(const QPoint&)*((const QPoint*)static_QUType_ptr.get(_o+2)),(int)static_QUType_int.get(_o+3)); break;
    case 6: fileBrowserMenuSlot((int)static_QUType_int.get(_o+1)); break;
    case 7: textChangedSlot(); break;
    case 8: saveSlot(); break;
    case 9: runButtonSlot(); break;
    case 10: lineNumSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 11: saveallSlot(); break;
    case 12: newSlot(); break;
    case 13: importSlot(); break;
    case 14: exportSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ScriptWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: runScript((QString*)static_QUType_varptr.get(_o+1)); break;
    case 2: controlScriptMenu((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ScriptWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ScriptWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
