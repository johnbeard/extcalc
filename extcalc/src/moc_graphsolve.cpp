/****************************************************************************
** GraphSolveWidget meta object code from reading C++ file 'graphsolve.h'
**
** Created: Thu Mar 27 18:08:49 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "graphsolve.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GraphSolveWidget::className() const
{
    return "GraphSolveWidget";
}

QMetaObject *GraphSolveWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GraphSolveWidget( "GraphSolveWidget", &GraphSolveWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GraphSolveWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphSolveWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GraphSolveWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphSolveWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GraphSolveWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"solveButtonSlot", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_double, 0, QUParameter::In },
	{ 0, &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"graphLMButtonPressed", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "newSolveType", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setState", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "fType", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"setFunctionType", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_varptr, "\x06", QUParameter::In }
    };
    static const QUMethod slot_4 = {"screenshotSlot", 1, param_slot_4 };
    static const QUMethod slot_5 = {"openButtonSlot", 0, 0 };
    static const QUMethod slot_6 = {"colorButtonSlot", 0, 0 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"penValueSlot", 1, param_slot_7 };
    static const QUMethod slot_8 = {"forwardButtonSlot", 0, 0 };
    static const QUMethod slot_9 = {"backButtonSlot", 0, 0 };
    static const QUMethod slot_10 = {"clearButtonSlot", 0, 0 };
    static const QUMethod slot_11 = {"freeButtonSlot", 0, 0 };
    static const QUMethod slot_12 = {"lineButtonSlot", 0, 0 };
    static const QUMethod slot_13 = {"rectButtonSlot", 0, 0 };
    static const QUMethod slot_14 = {"circleButtonSlot", 0, 0 };
    static const QUMethod slot_15 = {"rubberButtonSlot", 0, 0 };
    static const QUMethod slot_16 = {"textButtonSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "solveButtonSlot()", &slot_0, QMetaData::Public },
	{ "graphLMButtonPressed(double,double)", &slot_1, QMetaData::Public },
	{ "setState(int)", &slot_2, QMetaData::Public },
	{ "setFunctionType(int)", &slot_3, QMetaData::Public },
	{ "screenshotSlot(QPixmap*)", &slot_4, QMetaData::Public },
	{ "openButtonSlot()", &slot_5, QMetaData::Public },
	{ "colorButtonSlot()", &slot_6, QMetaData::Public },
	{ "penValueSlot(int)", &slot_7, QMetaData::Public },
	{ "forwardButtonSlot()", &slot_8, QMetaData::Public },
	{ "backButtonSlot()", &slot_9, QMetaData::Public },
	{ "clearButtonSlot()", &slot_10, QMetaData::Public },
	{ "freeButtonSlot()", &slot_11, QMetaData::Public },
	{ "lineButtonSlot()", &slot_12, QMetaData::Public },
	{ "rectButtonSlot()", &slot_13, QMetaData::Public },
	{ "circleButtonSlot()", &slot_14, QMetaData::Public },
	{ "rubberButtonSlot()", &slot_15, QMetaData::Public },
	{ "textButtonSlot()", &slot_16, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "x", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"addVerticalLine", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "y", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"addHorizontalLine", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ "angle", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"addPolarLine", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ "radius", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"addCircle", 1, param_signal_3 };
    static const QUParameter param_signal_4[] = {
	{ "y", &static_QUType_double, 0, QUParameter::In },
	{ "z", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_4 = {"add3dXLine", 2, param_signal_4 };
    static const QUParameter param_signal_5[] = {
	{ "x", &static_QUType_double, 0, QUParameter::In },
	{ "z", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_5 = {"add3dYLine", 2, param_signal_5 };
    static const QUParameter param_signal_6[] = {
	{ "x", &static_QUType_double, 0, QUParameter::In },
	{ "y", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_6 = {"add3dZLine", 2, param_signal_6 };
    static const QUMethod signal_7 = {"removeLines", 0, 0 };
    static const QUParameter param_signal_8[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_8 = {"prefChange", 1, param_signal_8 };
    static const QUParameter param_signal_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_9 = {"drawInequaityIntersection", 2, param_signal_9 };
    static const QUMethod signal_10 = {"redrawGraphs", 0, 0 };
    static const QUParameter param_signal_11[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_11 = {"getScreenshotSignal", 2, param_signal_11 };
    static const QUParameter param_signal_12[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_varptr, "\x0a", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_12 = {"drawSignal", 3, param_signal_12 };
    static const QMetaData signal_tbl[] = {
	{ "addVerticalLine(double)", &signal_0, QMetaData::Public },
	{ "addHorizontalLine(double)", &signal_1, QMetaData::Public },
	{ "addPolarLine(double)", &signal_2, QMetaData::Public },
	{ "addCircle(double)", &signal_3, QMetaData::Public },
	{ "add3dXLine(double,double)", &signal_4, QMetaData::Public },
	{ "add3dYLine(double,double)", &signal_5, QMetaData::Public },
	{ "add3dZLine(double,double)", &signal_6, QMetaData::Public },
	{ "removeLines()", &signal_7, QMetaData::Public },
	{ "prefChange(Preferences)", &signal_8, QMetaData::Public },
	{ "drawInequaityIntersection(int,int)", &signal_9, QMetaData::Public },
	{ "redrawGraphs()", &signal_10, QMetaData::Public },
	{ "getScreenshotSignal(int,int)", &signal_11, QMetaData::Public },
	{ "drawSignal(int,QColor,int)", &signal_12, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GraphSolveWidget", parentObject,
	slot_tbl, 17,
	signal_tbl, 13,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GraphSolveWidget.setMetaObject( metaObj );
    return metaObj;
}

void* GraphSolveWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GraphSolveWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL addVerticalLine
void GraphSolveWidget::addVerticalLine( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL addHorizontalLine
void GraphSolveWidget::addHorizontalLine( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

// SIGNAL addPolarLine
void GraphSolveWidget::addPolarLine( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

// SIGNAL addCircle
void GraphSolveWidget::addCircle( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 3, t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL add3dXLine
void GraphSolveWidget::add3dXLine( double t0, double t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 4 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_double.set(o+1,t0);
    static_QUType_double.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL add3dYLine
void GraphSolveWidget::add3dYLine( double t0, double t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 5 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_double.set(o+1,t0);
    static_QUType_double.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL add3dZLine
void GraphSolveWidget::add3dZLine( double t0, double t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 6 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_double.set(o+1,t0);
    static_QUType_double.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL removeLines
void GraphSolveWidget::removeLines()
{
    activate_signal( staticMetaObject()->signalOffset() + 7 );
}

// SIGNAL prefChange
void GraphSolveWidget::prefChange( Preferences t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 8 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL drawInequaityIntersection
void GraphSolveWidget::drawInequaityIntersection( int t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 9 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL redrawGraphs
void GraphSolveWidget::redrawGraphs()
{
    activate_signal( staticMetaObject()->signalOffset() + 10 );
}

// SIGNAL getScreenshotSignal
void GraphSolveWidget::getScreenshotSignal( int t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 11 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL drawSignal
void GraphSolveWidget::drawSignal( int t0, QColor t1, int t2 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 12 );
    if ( !clist )
	return;
    QUObject o[4];
    static_QUType_int.set(o+1,t0);
    static_QUType_varptr.set(o+2,&t1);
    static_QUType_int.set(o+3,t2);
    activate_signal( clist, o );
}

bool GraphSolveWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: solveButtonSlot(); break;
    case 1: graphLMButtonPressed((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 2: setState((int)static_QUType_int.get(_o+1)); break;
    case 3: setFunctionType((int)static_QUType_int.get(_o+1)); break;
    case 4: screenshotSlot((QPixmap*)static_QUType_varptr.get(_o+1)); break;
    case 5: openButtonSlot(); break;
    case 6: colorButtonSlot(); break;
    case 7: penValueSlot((int)static_QUType_int.get(_o+1)); break;
    case 8: forwardButtonSlot(); break;
    case 9: backButtonSlot(); break;
    case 10: clearButtonSlot(); break;
    case 11: freeButtonSlot(); break;
    case 12: lineButtonSlot(); break;
    case 13: rectButtonSlot(); break;
    case 14: circleButtonSlot(); break;
    case 15: rubberButtonSlot(); break;
    case 16: textButtonSlot(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GraphSolveWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: addVerticalLine((double)static_QUType_double.get(_o+1)); break;
    case 1: addHorizontalLine((double)static_QUType_double.get(_o+1)); break;
    case 2: addPolarLine((double)static_QUType_double.get(_o+1)); break;
    case 3: addCircle((double)static_QUType_double.get(_o+1)); break;
    case 4: add3dXLine((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 5: add3dYLine((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 6: add3dZLine((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 7: removeLines(); break;
    case 8: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 9: drawInequaityIntersection((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 10: redrawGraphs(); break;
    case 11: getScreenshotSignal((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 12: drawSignal((int)static_QUType_int.get(_o+1),(QColor)(*((QColor*)static_QUType_ptr.get(_o+2))),(int)static_QUType_int.get(_o+3)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GraphSolveWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool GraphSolveWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
