/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptio.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

The ScriptIO class runs the scripts and provides a direct interface to the running script.
The ScriptGL class provides the 3D-graphics window for scripts with GL commands.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef SCRIPTIOH
#define SCRIPTIOH

#include "buttons.h"
#include <qwidget.h>
#include <qpainter.h>
#include <qclipboard.h>
#include <qthread.h>
#include <qevent.h>
#include <qmutex.h>
#include <qscrollbar.h>
#include <qtimer.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <qpopupmenu.h>
#include <qgl.h>
#include "list.h"

#define IMDEFAULT		1
#define IMSCRIPTING		2
#define IMGETLINE		3
#define IMGETKEY		4

#define BUFFER_LENGTH 100



struct GlTextInfo
{
	int x,y;
	QString text;
};

class ScriptThread :public QThread
{
	Script* script;
	QObject*parent;

	public:
		ScriptThread(Script* s,QObject*p) :QThread()
		{
			script=s;
			parent=p;

		}

	protected:
		virtual void run()
		{
			script->exec();
		}
};

class ScriptGL :public QGLWidget
{
	GLuint axes;
	int xRotation,yRotation,mouseX,mouseY,zMove;
	bool unlock;
	Preferences pref;
	List <GLuint> staticLists;
	List <GLuint> drawLists;
	List <GlTextInfo> textList;
	
	
	bool drawListActive,staticListActive,paintActive;
	GLuint currentList;
	
	Q_OBJECT
	public:
		ScriptGL(QWidget*parent,Preferences p,QGLWidget*shareWidget=NULL) :QGLWidget(parent,0,shareWidget)
		{
			pref=p;
			pref.xmin=pref.ymin=pref.zmin=-10.0;
			pref.xmax=pref.ymax=pref.zmax=10.0;
			axes=0xffffffff;
			unlock=false;
			drawListActive=staticListActive=paintActive=false;
			currentList=0;
		}

		GLuint draw3dAxes();
		
		void resetRotation()
		{xRotation=yRotation=0;zMove=0;}
		void setPref(Preferences p)
		{
			pref=p;
			pref.xmin=pref.ymin=pref.zmin=-10.0;
			pref.xmax=pref.ymax=pref.zmax=10.0;
		}
		
//inline gl things
		void drawListControl()
		{
			if(staticListActive)
			{
//				perror("End StaticList");

				glEndList();
				staticLists.NewItem(currentList);
				staticListActive=false;
			}
			if(paintActive)
			{
//				perror("End Paint");

				glEnd();
				paintActive=false;
			}
			if(drawListActive)
			{
//				perror("End DrawList "+QString::number(drawLists.GetLen()));
				drawListActive=false;
				glEndList();
				drawLists.NewItem(currentList);
			}
			else {
//				perror("Begin DrawList");

				drawListActive=true;
				currentList=glGenLists(1);
				glNewList(currentList,GL_COMPILE);
				controlLists();
			}
		}

		void scrBegin(GLuint type)
		{
			if(!staticListActive && !drawListActive)
			{
				drawListControl();
			}
			paintActive=true;
			glBegin(type);
//			perror("Begin Paint");

		}

		void scrEnd()
		{
			if(paintActive)
			{
				glEnd();
				paintActive=false;
//				perror("End Paint");
			}

		}

		void scrVertex(float x,float y,float z)
		{
			if(!drawListActive && !staticListActive)
				drawListControl();
			if(paintActive)
				glVertex3f(x,y,z);
		}
		
		void scrStartList()
		{
			if(drawListActive || staticListActive)
				drawListControl();
			staticListActive=true;
			currentList=glGenLists(1);
			glNewList(currentList,GL_COMPILE);

		}
		
		int scrEndList()
		{
			if(staticListActive)
			{
				staticListActive=false;
				if(paintActive)
				{
					glEnd();
					paintActive=false;
				}
				glEndList();
				staticLists.NewItem(currentList);
				controlLists();
			}
			return staticLists.GetLen()-1;
		}
		
		void scrCallList(int num)
		{
			bool restart=false;
			if(num>=0 && num<staticLists.GetLen())
			{
				if(drawListActive)
				{
					restart=true;
					drawListControl();
				}
				drawLists.NewItem(staticLists[num]);
				controlLists();
				if(restart)
					drawListControl();
			}
		}
		void controlLists()
		{
			if(drawLists.GetLen()>500 || textList.GetLen()>200)
				scrClear();
			if(staticLists.GetLen()>200)
				initializeGL();
		}
		
		void scrRotate(double angle,double x,double y,double z)
		{
			
			if(!drawListActive && !staticListActive)
				drawListControl();
			glRotatef(angle,x,y,z);
		}
		void scrTranslate(double x,double y,double z)
		{
			if(!drawListActive && !staticListActive)
				drawListControl();
				glTranslatef(x,y,z);
		}
		void scrScale(double x,double y,double z)
		{
			if(!drawListActive && !staticListActive)
				drawListControl();
			glScalef(x,y,z);
			
		}
		void scrIdentity()
		{
			if(!drawListActive && !staticListActive)
				drawListControl();
			glLoadIdentity();
			
		}
		void scrText(int x,int y,char*text)
		{
			GlTextInfo i;
			i.x=x;
			i.y=y;
			i.text=QString(text);
			textList.NewItem(i);
		}
		
		void scrColor(int r,int g,int b)
		{
			if(!drawListActive && !staticListActive)
				drawListControl();
			qglColor(QColor(r,g,b));
		}
		
		void scrClear()
		{
			while(drawLists.GetLen()>0)
			{
				bool clear=true;
				for(int c=0; c<staticLists.GetLen(); c++)
					if(staticLists[c]==drawLists[0])
				{
					clear=false;
					break;
				}
				
				if(clear)
					glDeleteLists(drawLists[0],1);
				drawLists.DeleteItem(0);
			}
			
			while(textList.GetLen()>0)
				textList.DeleteItem(0);
		}

		void scrReset()
		{
			initializeGL();
		}

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int,int);
		void mousePressEvent(QMouseEvent*);
		void mouseMoveEvent(QMouseEvent*);
		void mouseReleaseEvent(QMouseEvent*);
		void wheelEvent(QWheelEvent*);
};

class ScriptIOWidget :public QWidget
{
	Variable *vars;
	
	StandardButtons*calcButtons;
	ExtButtons*extButtons;
	ScriptGL*glWindow;
	Preferences pref,runningPref;
	QPushButton*maximizeButton,*killButton,*runButton;
	QPopupMenu*contextMenu;
	
	bool maximized;
	int ioFieldWidth,ioFieldHeight;
	QPixmap*buffer;
	QFont*drawFont;
	QPen*drawPen;
	int charWidth,charHeight;
	int lineNum,charNum;
	
	List <QString> lines;
	int cursorX,cursorY;
	
	int inputMode;
	int bufferCursor;
	char*inputBuffer;
	
	List <int>semicolonLines;
	int countDifference;
	bool errorFlag;
	
	bool scriptExec;
	ScriptThread*script;
	Script*scriptObject;
	ThreadSync*threadData;
	QMutex*mutex;
	
	QScrollBar * scrollBar;
	
	QTimer*t;
	int timerInterval,redrawTime;
	struct timeval drawTime,currentTime,startTime;
	int selectStartLine,selectStartRow,selectEndLine,selectEndRow;
	int displayType;
	int modeRequest;
	bool autosize;

	Q_OBJECT

	public:
		ScriptIOWidget(QWidget*parent,Preferences pr,Variable *va,QGLWidget*shareContext) :QWidget(parent)
		{
			vars=va;
			vars=new Variable [VARNUM];
			for(int c=0; c<VARNUM;c++)
				vars[c]=0.0;
			pref=pr;
			maximized=true;
			scriptExec=false;
			script=NULL;
			inputMode=IMDEFAULT;
			inputBuffer=(char*)calloc(1,1);
			bufferCursor=0;
			scriptObject=NULL;
			displayType=SCRIPTTEXT;
			modeRequest=SCRIPTTEXT;
			autosize=true;
			
			mutex=new QMutex();
			threadData=new ThreadSync;
			threadData->mutex=mutex;
			threadData->eventReciver=this;
			threadData->status=0;
			threadData->exit=false;
			threadData->usleep=false;
			threadData->bbreak=false;
			threadData->bcontinue=false;
			threadData->calcMode=false;
			threadData->data=NULL;
			threadData->sleepTime=1000;
			threadData->vars=new Number*[VARNUM];
			for(int c=0; c<VARNUM;c++)
			{
				threadData->vars[c]=(Number*)malloc(sizeof(Number));
				threadData->numlen[c]=1;
				threadData->vars[c][0].type=NNONE;
				threadData->vars[c][0].cval=NULL;
				for(int c1=0; c1<VARDIMENSIONS; c1++)
					threadData->dimension[c][c1]=1;
			}
			
			t=new QTimer(this);
			timerInterval=25;
			redrawTime=20000;

			selectStartLine=selectStartRow=selectEndLine=selectEndRow=0;
			
			calcButtons=new  StandardButtons(this);
			extButtons=new ExtButtons(this);
			glWindow=new ScriptGL(this,pref,shareContext);
			maximizeButton=new QPushButton(CALCWIDGETC_STR2,this);
			killButton=new QPushButton(SCRIPTIO_STR1,this);
			killButton->setEnabled(false);
			runButton=new QPushButton(SCRIPTIO_STR7,this);
			runButton->setEnabled(false);
			contextMenu=new QPopupMenu(this);
			contextMenu->insertItem(SCRIPTIO_STR12,EDITCOPY);
			contextMenu->insertItem(SCRIPTIO_STR13,EDITPASTE);
			contextMenu->insertSeparator();
			contextMenu->insertItem(SCRIPTIO_STR14,EDITSELECTALL);
			contextMenu->insertSeparator();
			contextMenu->insertItem(SCRIPTIO_STR15,EDITCUT);

			ioFieldWidth=600;
			ioFieldHeight=310;
			cursorX=cursorY=0;
			buffer=new QPixmap(ioFieldWidth,ioFieldHeight,-1,QPixmap::BestOptim);
			drawFont=new QFont("Courier");
			drawFont->setPixelSize(16);
			drawFont->setFixedPitch(true);
			drawPen=new QPen(QColor(0,0,0));
			
			scrollBar=new QScrollBar(Qt::Vertical,this);
			ioFieldWidth-=20;
			scrollBar->setValue(0);
			
			QFontMetrics fontSize(*drawFont);
			charWidth=fontSize.size(0,QString("m")).width();
			charHeight=fontSize.size(0,QString("m")).height();
			charNum=ioFieldWidth/charWidth;
			lineNum=ioFieldHeight/charHeight;
			for(int c=0; c<lineNum; c++)
				lines.NewItem(QString(""));
			
			scrollBar->setMinValue(0);
			scrollBar->setMaxValue(0);
			scrollBar->setLineStep(1);
			scrollBar->setPageStep(lineNum);
			scrollBar->setGeometry(600,50,20,ioFieldHeight);
			
			calcButtons->setGeometry(20,380,280,200);
			extButtons->setGeometry(320,420,300,160);
			
			calcButtons->hide();
			extButtons->hide();
			glWindow->hide();
			


			setFocusPolicy(QWidget::StrongFocus);

			QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(processText(QString)));
			QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(processText(QString)));
			QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeSlot()));
			QObject::connect(killButton,SIGNAL(clicked()),this,SLOT(killSlot()));
			QObject::connect(runButton,SIGNAL(clicked()),this,SLOT(runSlot()));
			QObject::connect(t,SIGNAL(timeout()),this,SLOT(timerSlot()));
			QObject::connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollbarSlot(int)));
			QObject::connect(contextMenu,SIGNAL(activated(int)),this,SLOT(contextMenuSlot(int)));
		}
		~ScriptIOWidget()
		{
			delete[]vars;
		}

		void setPref(Preferences newPref)
		{
			pref=newPref;
			calcButtons->setPref(pref);
			extButtons->setPref(pref);
		}

		void insert(QString text,bool redraw=true);
		void backKey();
		void deleteKey();
		void clearAll();
		void searchScripts(QString*code);
		void loadSubScripts();
		void initDebugging(QString *code);
		int preferencesPreprocessor(QString *code,Preferences*pref);
		int macroPreprocessor(QString*code);
		void selectText(int startx,int starty,int endx,int endy);
		void setDisplayMode(int);

	protected:
		virtual void resizeEvent(QResizeEvent*);
		virtual void paintEvent(QPaintEvent*);
		virtual void keyPressEvent(QKeyEvent*);
		virtual void customEvent(QCustomEvent*);
		virtual void mousePressEvent(QMouseEvent*);
		virtual void mouseReleaseEvent(QMouseEvent*);
		virtual void mouseMoveEvent(QMouseEvent*);
		virtual void wheelEvent(QWheelEvent*);

	public slots:

		void getPref(Preferences newPref);
		void maximizeSlot();
		void killSlot();
		void processText(QString text);
		void runScript(QString*code);
		void editSlot(int);
		void timerSlot();
		void runSlot();
		void scrollbarSlot(int);
		void clearMemSlot();
		void contextMenuSlot(int);

	signals:
		void prefChange(Preferences);
};

 
#endif

