#ifndef GRAPHOUTH
#define GRAPHOUTH


#include <qgl.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qtimer.h>
#include "list.h"
#include "global.h"

////////////////drawRules//////////////////////////////////////////
//
// drawRules[4] drawRules[0] drawRules[1] drawRules[2] drawRules[3]
//                  |            |             |            |
//                  1            3             1            3
//                  |            |             |            |
//               object1      object4      object5       object2
//                               |                          |
//                            object3                    object7
//                               |                          |
//                            object6                    object8
//
//
// objects[8]
//   GLuint list1
//   GLuint list2
//   GLuint list3
//   GLuint list4
//   GLuint list5
//   GLuint list6
//   GLuint list7
//   GLuint list8
//



class GraphOutput :public QGLWidget
{
	
	GLuint axes;
	Preferences pref;
	List <GLuint> objects;
	List <GLuint> additionalObjects;
	List <int* > drawRules;
	Variable*vars;
	int xRotation,yRotation,mouseX,mouseY,zMove;
	bool unlock;
	float middle, lowerMiddle,upperMiddle;
	int dynamicSteps;
	double dynamicStart,dynamicEnd;
	bool isDynamic;
	int dynamicPos;
	QTimer * timer;
	int ineq1,ineq2;
	
Q_OBJECT
public:
	GraphOutput(QWidget*parent,Variable*va) :QGLWidget(parent)
	{
		vars=va;
		xRotation=yRotation=zMove=0;
		ineq1=ineq2=-1;
		unlock=false;
		isDynamic=false;
		dynamicPos=0;
		timer = new QTimer(this);
		QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
		
		
	}
	void processStdFunction(QString,QColor);
	void processPolarFunction(QString,QColor);
	void processParameterFunction(QString,QColor);
	void process3dFunction(QString,QColor);
	void processInequaityFunction(QString,QColor,int,QString iFunction=QString(""),QColor iColor=QColor(0,0,0),int iType=GRAPHIEL);
	void processFunction(int);
	GLuint drawStdAxes();
	GLuint drawPolarAxes();
	GLuint draw3dAxes();
	
	void setPref(Preferences newPref);
	void clearGL();
	void setGLColor(float y);
	
public slots:
	void drawHorizontalLine(double y);
	void drawVerticalLine(double x);
	void drawCircle(double radius);
	void drawPolarLine(double angle);
	void draw3dXLine(double y,double z);
	void draw3dYLine(double x,double z);
	void draw3dZLine(double x,double y);
	void removeLines();
	void resetRotation();
	void timerSlot();
	void inequaityIntersectionSlot(int i1, int i2);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int,int);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void wheelEvent(QWheelEvent*);
	
signals:
	void prefChange(Preferences);
	void leftMButtonPressed(double,double);

};


#endif
