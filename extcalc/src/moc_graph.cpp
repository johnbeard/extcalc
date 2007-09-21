/****************************************************************************
** GraphArea meta object code from reading C++ file 'graph.h'
**
** Created: Fri Sep 21 09:10:30 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "graph.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GraphArea::className() const
{
    return "GraphArea";
}

QMetaObject *GraphArea::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GraphArea( "GraphArea", &GraphArea::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GraphArea::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphArea", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GraphArea::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphArea", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GraphArea::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod signal_0 = {"sizeChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "sizeChanged()", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"GraphArea", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GraphArea.setMetaObject( metaObj );
    return metaObj;
}

void* GraphArea::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GraphArea" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL sizeChanged
void GraphArea::sizeChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool GraphArea::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool GraphArea::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: sizeChanged(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GraphArea::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool GraphArea::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *GraphWidget::className() const
{
    return "GraphWidget";
}

QMetaObject *GraphWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GraphWidget( "GraphWidget", &GraphWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GraphWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GraphWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GraphWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "row", &static_QUType_int, 0, QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"selectionChangedSlot", 2, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"tableEditSlot", 1, param_slot_1 };
    static const QUMethod slot_2 = {"drawSlot", 0, 0 };
    static const QUMethod slot_3 = {"maximizeSlot", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"modeSlot", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"inputTextChanged", 1, param_slot_5 };
    static const QUMethod slot_6 = {"inputTextFinished", 0, 0 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"buttonInputSlot", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"solveTypeSlot", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"editSlot", 1, param_slot_9 };
    static const QUMethod slot_10 = {"catalogSlot", 0, 0 };
    static const QUMethod slot_11 = {"graphSizeSlot", 0, 0 };
    static const QUMethod slot_12 = {"dockWindowSlot", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ "newPref", &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod slot_13 = {"getPref", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ "fType", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"functionTypeSlot", 1, param_slot_14 };
    static const QMetaData slot_tbl[] = {
	{ "selectionChangedSlot(int,int)", &slot_0, QMetaData::Public },
	{ "tableEditSlot(QString)", &slot_1, QMetaData::Public },
	{ "drawSlot()", &slot_2, QMetaData::Public },
	{ "maximizeSlot()", &slot_3, QMetaData::Public },
	{ "modeSlot(int)", &slot_4, QMetaData::Public },
	{ "inputTextChanged(const QString&)", &slot_5, QMetaData::Public },
	{ "inputTextFinished()", &slot_6, QMetaData::Public },
	{ "buttonInputSlot(QString)", &slot_7, QMetaData::Public },
	{ "solveTypeSlot(int)", &slot_8, QMetaData::Public },
	{ "editSlot(int)", &slot_9, QMetaData::Public },
	{ "catalogSlot()", &slot_10, QMetaData::Public },
	{ "graphSizeSlot()", &slot_11, QMetaData::Public },
	{ "dockWindowSlot()", &slot_12, QMetaData::Public },
	{ "getPref(Preferences)", &slot_13, QMetaData::Public },
	{ "functionTypeSlot(int)", &slot_14, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"solveTypeSignal", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_ptr, "long double", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"drawPointsSignal", 3, param_signal_2 };
    static const QUMethod signal_3 = {"removeLinesSignal", 0, 0 };
    static const QUMethod signal_4 = {"statisticsRedrawSignal", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Protected },
	{ "solveTypeSignal(int)", &signal_1, QMetaData::Protected },
	{ "drawPointsSignal(long double*,int,bool)", &signal_2, QMetaData::Protected },
	{ "removeLinesSignal()", &signal_3, QMetaData::Protected },
	{ "statisticsRedrawSignal()", &signal_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"GraphWidget", parentObject,
	slot_tbl, 15,
	signal_tbl, 5,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GraphWidget.setMetaObject( metaObj );
    return metaObj;
}

void* GraphWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GraphWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void GraphWidget::prefChange( Preferences t0 )
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

// SIGNAL solveTypeSignal
void GraphWidget::solveTypeSignal( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

// SIGNAL drawPointsSignal
void GraphWidget::drawPointsSignal( long double* t0, int t1, bool t2 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[4];
    static_QUType_ptr.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    static_QUType_bool.set(o+3,t2);
    activate_signal( clist, o );
}

// SIGNAL removeLinesSignal
void GraphWidget::removeLinesSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 3 );
}

// SIGNAL statisticsRedrawSignal
void GraphWidget::statisticsRedrawSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 4 );
}

bool GraphWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: selectionChangedSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 1: tableEditSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 2: drawSlot(); break;
    case 3: maximizeSlot(); break;
    case 4: modeSlot((int)static_QUType_int.get(_o+1)); break;
    case 5: inputTextChanged((const QString&)static_QUType_QString.get(_o+1)); break;
    case 6: inputTextFinished(); break;
    case 7: buttonInputSlot((QString)static_QUType_QString.get(_o+1)); break;
    case 8: solveTypeSlot((int)static_QUType_int.get(_o+1)); break;
    case 9: editSlot((int)static_QUType_int.get(_o+1)); break;
    case 10: catalogSlot(); break;
    case 11: graphSizeSlot(); break;
    case 12: dockWindowSlot(); break;
    case 13: getPref((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 14: functionTypeSlot((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GraphWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: solveTypeSignal((int)static_QUType_int.get(_o+1)); break;
    case 2: drawPointsSignal((long double*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2),(bool)static_QUType_bool.get(_o+3)); break;
    case 3: removeLinesSignal(); break;
    case 4: statisticsRedrawSignal(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GraphWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool GraphWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
