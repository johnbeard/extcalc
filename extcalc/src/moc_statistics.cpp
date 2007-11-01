/****************************************************************************
** StatisticsWidget meta object code from reading C++ file 'statistics.h'
**
** Created: Thu Nov 1 13:25:03 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "statistics.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StatisticsWidget::className() const
{
    return "StatisticsWidget";
}

QMetaObject *StatisticsWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StatisticsWidget( "StatisticsWidget", &StatisticsWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StatisticsWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StatisticsWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StatisticsWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StatisticsWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StatisticsWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_0 = {"getPref", 1, param_slot_0 };
    static const QUMethod slot_1 = {"maximizeButtonSlot", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"typeBoxSlot", 1, param_slot_2 };
    static const QUMethod slot_3 = {"calculateButtonSlot", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"itemChangedSlot", 2, param_slot_4 };
    static const QUMethod slot_5 = {"copyButtonSlot", 0, 0 };
    static const QUMethod slot_6 = {"printButtonSlot", 0, 0 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"buttonInputSlot", 1, param_slot_7 };
    static const QUMethod slot_8 = {"redrawGraphSlot", 0, 0 };
    static const QUMethod slot_9 = {"dockWindowSlot", 0, 0 };
    static const QUMethod slot_10 = {"catalogSlot", 0, 0 };
    static const QUParameter param_slot_11[] = {
	{ "row", &static_QUType_int, 0, QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"selectionChangedSlot", 2, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"tableEditSlot", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"inputTextChanged", 1, param_slot_13 };
    static const QUMethod slot_14 = {"inputTextFinished", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "getPref(Preferences)", &slot_0, QMetaData::Public },
	{ "maximizeButtonSlot()", &slot_1, QMetaData::Public },
	{ "typeBoxSlot(int)", &slot_2, QMetaData::Public },
	{ "calculateButtonSlot()", &slot_3, QMetaData::Public },
	{ "itemChangedSlot(int,int)", &slot_4, QMetaData::Public },
	{ "copyButtonSlot()", &slot_5, QMetaData::Public },
	{ "printButtonSlot()", &slot_6, QMetaData::Public },
	{ "buttonInputSlot(QString)", &slot_7, QMetaData::Public },
	{ "redrawGraphSlot()", &slot_8, QMetaData::Public },
	{ "dockWindowSlot()", &slot_9, QMetaData::Public },
	{ "catalogSlot()", &slot_10, QMetaData::Public },
	{ "selectionChangedSlot(int,int)", &slot_11, QMetaData::Public },
	{ "tableEditSlot(QString)", &slot_12, QMetaData::Public },
	{ "inputTextChanged(const QString&)", &slot_13, QMetaData::Public },
	{ "inputTextFinished()", &slot_14, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QUMethod signal_1 = {"printSignal", 0, 0 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"changeTabSignal", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ 0, &static_QUType_ptr, "long double", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"drawPointsSignal", 3, param_signal_3 };
    static const QUMethod signal_4 = {"removeLinesSignal", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Protected },
	{ "printSignal()", &signal_1, QMetaData::Protected },
	{ "changeTabSignal(int)", &signal_2, QMetaData::Protected },
	{ "drawPointsSignal(long double*,int,bool)", &signal_3, QMetaData::Protected },
	{ "removeLinesSignal()", &signal_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"StatisticsWidget", parentObject,
	slot_tbl, 15,
	signal_tbl, 5,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StatisticsWidget.setMetaObject( metaObj );
    return metaObj;
}

void* StatisticsWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StatisticsWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void StatisticsWidget::prefChange( Preferences t0 )
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

// SIGNAL printSignal
void StatisticsWidget::printSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

// SIGNAL changeTabSignal
void StatisticsWidget::changeTabSignal( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

// SIGNAL drawPointsSignal
void StatisticsWidget::drawPointsSignal( long double* t0, int t1, bool t2 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 3 );
    if ( !clist )
	return;
    QUObject o[4];
    static_QUType_ptr.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    static_QUType_bool.set(o+3,t2);
    activate_signal( clist, o );
}

// SIGNAL removeLinesSignal
void StatisticsWidget::removeLinesSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 4 );
}

bool StatisticsWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: maximizeButtonSlot(); break;
    case 2: typeBoxSlot((int)static_QUType_int.get(_o+1)); break;
    case 3: calculateButtonSlot(); break;
    case 4: itemChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 5: copyButtonSlot(); break;
    case 6: printButtonSlot(); break;
    case 7: buttonInputSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 8: redrawGraphSlot(); break;
    case 9: dockWindowSlot(); break;
    case 10: catalogSlot(); break;
    case 11: selectionChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 12: tableEditSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 13: inputTextChanged((const QString&)static_QUType_QString.get(_o+1)); break;
    case 14: inputTextFinished(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool StatisticsWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: printSignal(); break;
    case 2: changeTabSignal((int)static_QUType_int.get(_o+1)); break;
    case 3: drawPointsSignal((long double*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2),(bool)static_QUType_bool.get(_o+3)); break;
    case 4: removeLinesSignal(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool StatisticsWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool StatisticsWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
