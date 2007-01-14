#ifndef GRAPHOUTH
#define GRAPHOUTH


#include <qgl.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qtimer.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qpainter.h>
#include <qinputdialog.h>
#include "list.h"
#include "global.h"

#define PRECISION2D current2dSteps
#define PRECISION3D current3dSteps
#define TEXTURESIZE (256<<pref.solvePrec)
#define BACKSTEPS 3


////////////////drawRules//////////////////////////////////////////
//
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
//	there exists one objectInfo element and one ObjectCoordinates element for every object. They all have the same index

struct ObjectInfo
{
	int type;
	bool dynamic;
	double dynamicParameter;
	int length;
	char* function;
	char* function2;
	QColor color;
};

struct DrawData
{
	int type;
	float x;
	float y;
	QColor color;
};


class GraphOutput :public QGLWidget
{
	
	GLuint axes;
	Preferences pref;
	List <GLuint> objects;
	List <GLuint> additionalObjects;
	List <int* > drawRules;
	List <double*> objectCoordinates;
	List <ObjectInfo> objectInfo;
	Variable*vars;
	ThreadSync*threadData;
	int xRotation,yRotation,mouseX,mouseY,zMove;
	bool unlock;
	float middle, lowerMiddle,upperMiddle;
	int dynamicSteps;
	double dynamicStart,dynamicEnd;
	bool isDynamic;
	int dynamicPos;
	QTimer * timer;
	int ineq1,ineq2;
	double oldX,oldY;
	double oldXMin,oldXMax;
	QPixmap scr;
	bool drawScreenshot;
	int drawState;
	QColor drawColor;
	int drawPen,previewPen;
	QPixmap*drawMap;
	QImage*drawImage;
	GLuint texture;
	QPainter *draw;
	int backCursor;
	QPixmap**backMap;
	QString drawString;
	int current3dSteps;
	int current2dSteps;
	int currentSolvePrec;
	
	
Q_OBJECT
public:
	GraphOutput(QWidget*parent,Variable*va,ThreadSync*td) :QGLWidget(parent)
	{
		axes=0xffffffff;
		pref.solvePrec=currentSolvePrec=1;
		drawImage=new QImage(TEXTURESIZE,TEXTURESIZE,32);
		drawImage->fill(0x00000000);
		drawImage->setAlphaBuffer(true);
		drawMap=new QPixmap(*drawImage);
		backCursor=0;
		backMap=new QPixmap*[BACKSTEPS];
		for(int c=0; c<BACKSTEPS; c++)
			backMap[c]=NULL;
		
		draw=new QPainter();
		texture=0xffffffff;
		current2dSteps=200;
		current3dSteps=50;
		drawState=DRAWFREE;
		previewPen=drawPen=1;
		drawColor=QColor(0,0,0);
		drawScreenshot=false;
		vars=va;
		threadData=td;

		xRotation=yRotation=zMove=0;
		ineq1=ineq2=-1;
		unlock=false;
		isDynamic=false;
		dynamicPos=0;
		timer = new QTimer(this);
		QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
	}
	
	
	void processStdFunction(QString);
	void processPolarFunction(QString);
	void processParameterFunction(QString);
	void process3dFunction(QString);
	void processInequaityFunction(QString,QString,int);
	void processComplexFunction(QString,bool);
	void processFunction(int);
	bool updateFunctions(double,double);
	GLuint generateGLList(int);
	GLuint drawStdAxes();
	GLuint drawPolarAxes();
	GLuint draw3dAxes();
	void generateTexture();

	
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
	void screenshotSlot(int,int);
	void drawSlot(int,QColor,int);
	void timerStartSlot(bool);

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
	void redrawSignal();
	void screenshotSignal(QPixmap*);

};


#endif
