/****************************************************************************
** GraphOutput meta object code from reading C++ file 'graphout.h'
**
** Created: Sat Dec 23 15:02:18 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "graphout.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GraphOutput::className() const
{
    return "GraphOutput";
}

QMetaObject *GraphOutput::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GraphOutput( "GraphOutput", &GraphOutput::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GraphOutput::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphOutput", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GraphOutput::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GraphOutput", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GraphOutput::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "y", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"drawHorizontalLine", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "x", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"drawVerticalLine", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "radius", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"drawCircle", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "angle", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"drawPolarLine", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "y", &static_QUType_double, 0, QUParameter::In },
	{ "z", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"draw3dXLine", 2, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "x", &static_QUType_double, 0, QUParameter::In },
	{ "z", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"draw3dYLine", 2, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "x", &static_QUType_double, 0, QUParameter::In },
	{ "y", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"draw3dZLine", 2, param_slot_6 };
    static const QUMethod slot_7 = {"removeLines", 0, 0 };
    static const QUMethod slot_8 = {"resetRotation", 0, 0 };
    static const QUMethod slot_9 = {"timerSlot", 0, 0 };
    static const QUParameter param_slot_10[] = {
	{ "i1", &static_QUType_int, 0, QUParameter::In },
	{ "i2", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"inequaityIntersectionSlot", 2, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"screenshotSlot", 2, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_varptr, "\x0a", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"drawSlot", 3, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"timerStartSlot", 1, param_slot_13 };
    static const QMetaData slot_tbl[] = {
	{ "drawHorizontalLine(double)", &slot_0, QMetaData::Public },
	{ "drawVerticalLine(double)", &slot_1, QMetaData::Public },
	{ "drawCircle(double)", &slot_2, QMetaData::Public },
	{ "drawPolarLine(double)", &slot_3, QMetaData::Public },
	{ "draw3dXLine(double,double)", &slot_4, QMetaData::Public },
	{ "draw3dYLine(double,double)", &slot_5, QMetaData::Public },
	{ "draw3dZLine(double,double)", &slot_6, QMetaData::Public },
	{ "removeLines()", &slot_7, QMetaData::Public },
	{ "resetRotation()", &slot_8, QMetaData::Public },
	{ "timerSlot()", &slot_9, QMetaData::Public },
	{ "inequaityIntersectionSlot(int,int)", &slot_10, QMetaData::Public },
	{ "screenshotSlot(int,int)", &slot_11, QMetaData::Public },
	{ "drawSlot(int,QColor,int)", &slot_12, QMetaData::Public },
	{ "timerStartSlot(bool)", &slot_13, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "Preferences", QUParameter::In }
    };
    static const QUMethod signal_0 = {"prefChange", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_double, 0, QUParameter::In },
	{ 0, &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"leftMButtonPressed", 2, param_signal_1 };
    static const QUMethod signal_2 = {"redrawSignal", 0, 0 };
    static const QUParameter param_signal_3[] = {
	{ 0, &static_QUType_varptr, "\x06", QUParameter::In }
    };
    static const QUMethod signal_3 = {"screenshotSignal", 1, param_signal_3 };
    static const QMetaData signal_tbl[] = {
	{ "prefChange(Preferences)", &signal_0, QMetaData::Protected },
	{ "leftMButtonPressed(double,double)", &signal_1, QMetaData::Protected },
	{ "redrawSignal()", &signal_2, QMetaData::Protected },
	{ "screenshotSignal(QPixmap*)", &signal_3, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"GraphOutput", parentObject,
	slot_tbl, 14,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GraphOutput.setMetaObject( metaObj );
    return metaObj;
}

void* GraphOutput::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GraphOutput" ) )
	return this;
    return QGLWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL prefChange
void GraphOutput::prefChange( Preferences t0 )
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

// SIGNAL leftMButtonPressed
void GraphOutput::leftMButtonPressed( double t0, double t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_double.set(o+1,t0);
    static_QUType_double.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL redrawSignal
void GraphOutput::redrawSignal()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

// SIGNAL screenshotSignal
void GraphOutput::screenshotSignal( QPixmap* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 3 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_varptr.set(o+1,t0);
    activate_signal( clist, o );
}

bool GraphOutput::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: drawHorizontalLine((double)static_QUType_double.get(_o+1)); break;
    case 1: drawVerticalLine((double)static_QUType_double.get(_o+1)); break;
    case 2: drawCircle((double)static_QUType_double.get(_o+1)); break;
    case 3: drawPolarLine((double)static_QUType_double.get(_o+1)); break;
    case 4: draw3dXLine((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 5: draw3dYLine((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 6: draw3dZLine((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 7: removeLines(); break;
    case 8: resetRotation(); break;
    case 9: timerSlot(); break;
    case 10: inequaityIntersectionSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 11: screenshotSlot((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 12: drawSlot((int)static_QUType_int.get(_o+1),(QColor)(*((QColor*)static_QUType_ptr.get(_o+2))),(int)static_QUType_int.get(_o+3)); break;
    case 13: timerStartSlot((bool)static_QUType_bool.get(_o+1)); break;
    default:
	return QGLWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GraphOutput::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: prefChange((Preferences)(*((Preferences*)static_QUType_ptr.get(_o+1)))); break;
    case 1: leftMButtonPressed((double)static_QUType_double.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    case 2: redrawSignal(); break;
    case 3: screenshotSignal((QPixmap*)static_QUType_varptr.get(_o+1)); break;
    default:
	return QGLWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GraphOutput::qt_property( int id, int f, QVariant* v)
{
    return QGLWidget::qt_property( id, f, v);
}

bool GraphOutput::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
