/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         graphout.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GL Window class for processing and drawing function graphs.
It also includes the interfaces for screenshot generation, drawing functions and graph analysis.

////////////////////////////////////////////////////////////////////////////////////////////*/
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
#include <qthread.h>
//Added by qt3to4:
#include <QCustomEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include "list.h"
#include "global.h"

#define PRECISION2D current2dSteps
#define PRECISION3D current3dSteps
#define TEXTURESIZE (256<<pref.solvePrec)
#define BACKSTEPS 3
#define THREADS 4


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
//
// processFunction() creates the ObjectInfo and objects enteries without calculating the data
// a seperate method walks through all ObjectInfo objects and processes the data when necessary
// this method creates a new thread for the calculation
// for better performance, this method should be able to process several objects when needed
//

struct ObjectInfo
{
	int type;
	bool dynamic;
	bool logic;
	double dynamicParameter;
	int length;
	char* function;
	char* function2;
	QColor color;
	bool processed,glCreated;
	GLuint glObject;
	double*coordinates;
	
};

struct DrawData
{
	int type;
	float x;
	float y;
	QColor color;
};

class GraphicsThread :public QThread
{
	int index;
	QGLWidget*parent;
	ThreadSync*threadData;
	Variable*vars;
	public:
	GraphicsThread(QGLWidget*p) :QThread()
	{
		
		parent=p;
		index=-1;
		
		vars=new Variable[27];
		
		threadData=new ThreadSync;
		threadData->mutex=NULL;
		threadData->eventReciver=parent;
		threadData->status=0;
		threadData->eventCount=0;
		threadData->exit=false;
		threadData->usleep=false;
		threadData->bbreak=false;
		threadData->bcontinue=false;
		threadData->calcMode=true;
		threadData->data=NULL;
		threadData->sleepTime=1000;
		threadData->vars=new Number*[VARNUM];
		for(int c=0; c<VARNUM;c++)
		{
			threadData->vars[c]=(Number*)malloc(sizeof(Number));
			threadData->numlen[c]=1;
			threadData->vars[c][0].type=NNONE;
			threadData->vars[c][0].cval=NULL;
			threadData->vars[c][0].fval=Complex(0.0,0.0);
			for(int c1=0; c1<VARDIMENSIONS; c1++)
				threadData->dimension[c][c1]=1;
		}
	}
	
	~GraphicsThread()
	{
		delete[] vars;
		for(int c=0; c<VARNUM;c++)
		{
			free(threadData->vars[c]);
		}
		free(threadData->vars);
	}
	
	void setIndex(int i)
	{
		index=i;
	}
	
	protected:
		void run();
};



class GraphOutput :public QGLWidget
{
	
	GLuint axes;
	Preferences pref;
	List <GLuint> additionalObjects;
	List <int* > drawRules;
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
	QTimer * timer,*threadTimer;
	double oldX,oldY;
	double oldXMin,oldXMax;
	QPixmap scr;
	bool drawScreenshot;
	int drawState;
	QColor drawColor;
	int drawPen,previewPen;
	QPixmap*drawMap;
	QPixmap*backupDrawMap;
	QImage*drawImage;
	GLuint texture;
	QPainter *draw;
	int backCursor;
	QPixmap**backMap;
	QString drawString;
	int current3dSteps;
	int current2dSteps;
	int currentSolvePrec;
	bool hasSolveObjects,hasStatisticsObjects;
	GraphicsThread* threads[THREADS];
	bool graphProcess;

Q_OBJECT
public:
	GraphOutput(QWidget*parent,Variable*va,ThreadSync*td,QGLWidget*shareWidget=NULL) :QGLWidget(parent,0,shareWidget)
	{
		graphProcess=false;
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

		hasSolveObjects=hasStatisticsObjects=false;
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
		unlock=false;
		isDynamic=false;
		dynamicPos=0;
		timer = new QTimer(this);
		threadTimer=new QTimer(this);
		for(int c=0; c<THREADS; c++)
			threads[c]=new GraphicsThread((QGLWidget*)this);
		QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
		QObject::connect(threadTimer,SIGNAL(timeout()),this,SLOT(threadTimerSlot()));
		
	}


	void processStdFunction(int,ThreadSync*,Variable*);
	void processPolarFunction(int,ThreadSync*,Variable*);
	void processParameterFunction(int,ThreadSync*,Variable*);
	void process3dFunction(int,ThreadSync*,Variable*);
	void processInequalityFunction(int,ThreadSync*,Variable*);
	void processComplexFunction(int,ThreadSync*,Variable*);
	void processFunction(QString, QString, int, QColor, bool, bool);

	bool updateFunctions(double,double);
	GLuint generateGLList(int);
	void calculateGraphData();
	void processGraph(int i,ThreadSync*,Variable*);
	void createGLLists();
	GLuint drawStdAxes();
	GLuint drawPolarAxes();
	GLuint draw3dAxes();
	void generateTexture();
	
	void setPref(Preferences newPref);
	void clearGL();
	void setGLColor(float y);
	
private:
	inline void drawTriangle(float[3],float[3],float[3],bool colored);

public slots:
	void drawHorizontalLine(double y);
	void drawVerticalLine(double x);
	void drawCircle(double radius);
	void drawPolarLine(double angle);
	void drawPoints(long double *coordinates,int num,bool con);
	void draw3dXLine(double y,double z);
	void draw3dYLine(double x,double z);
	void draw3dZLine(double x,double y);
	void removeLines();
	void resetRotation();
	void timerSlot();
	void threadTimerSlot();
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
	void customEvent(QCustomEvent*);

	
signals:
	void prefChange(Preferences);
	void leftMButtonPressed(double,double);
	void redrawSignal();
	void screenshotSignal(QPixmap*);
	void solveRedrawSignal();
	void statisticsRedrawSignal();
	void processingFinished();
};


#endif
