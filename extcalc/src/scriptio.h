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
#include <QWidget>
#include <qpainter.h>
#include <qclipboard.h>
#include <qthread.h>
#include <qevent.h>
#include <qmutex.h>
#include <QScrollArea>
#include <qtimer.h>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <qicon.h>
#include <q3popupmenu.h>
#include <qtooltip.h>
#include <QApplication>
#include <QKeyEvent>
#include <QCustomEvent>
#include <QPixmap>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QStringList>
#include <QWheelEvent>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <q3popupmenu.h>
#include <qgl.h>
#include "list.h"
#include "tabwidget.h"
#include "scriptdisplay.h"

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
			makeCurrent();
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



/**
 * @class ScriptIOWidget
 * @brief This class controls the execution of script programs and provides an interface to the output windows
 *
 * To execute a script, the script source code is handed to this class which runs the script parser and does
 * the initialization. This is done by calling the runScript() method. The script is executed by pressing
 * the run butten which is connected to The runSlot() slot.
 * An event-based interface for graphics output and text input and output as well as file input and output
 * is also provided by this class via the customEvent() event handler method.
 *
 */
class ScriptIOWidget :public TabWidget
{
//	Variable *vars;

  /// GL outputrendering widget
	ScriptGL*glWindow;
  /// 2D-Graphics and text input/output widget
  ScriptDisplay *output2D;
  /// Copy of the preferences for a running script. This is necessary to provied fixed settings for a running script code.
	Preferences runningPref;
  /// PushButton for maximizeing and minimizing the script display widget
  QPushButton*maximizeButton;
  /// Kill button to stop a running script
  QPushButton*killButton;
  /// Start button to execute script
  QPushButton*runButton;
  /// Context menu for text area
	Q3PopupMenu*contextMenu;
	
  ///
  int ioFieldWidth;
  int ioFieldHeight;
	QFont*drawFont;
	QPen*drawPen;
	int charWidth,charHeight;
	int lineNum,charNum;
	
	int cursorX,cursorY;
	
	int inputMode;
	int bufferCursor;
	char*inputBuffer;

	List <int>semicolonLines;
	int countDifference;
	bool errorFlag;

	Q3ToolBar*toolBar;

	bool scriptExec;
	ScriptThread*script;
	Script*scriptObject;
//	ThreadSync*threadData;
	QMutex*mutex;

  QScrollArea * scrollArea;
	QPixmap *maximizeIcon,*minimizeIcon,*runIcon,*killIcon;
	
	QTimer*t;
	int timerInterval,redrawTime;
	struct timeval drawTime,currentTime,startTime;
  int selectStartColumn,selectStartRow,selectEndColumn,selectEndRow;
	int displayType;
	int modeRequest;
//	int menuBottom;
	bool autosize;

	Q_OBJECT

	public:
		ScriptIOWidget(QWidget*parent,Preferences pr,Variable *va,QGLWidget*shareContext);

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
		virtual void customEvent(QEvent*);
		virtual void wheelEvent(QWheelEvent*);

	public slots:
		void getPref(Preferences newPref);
		void maximizeButtonSlot();
		void killSlot();
		void processText(QString text);
		void runScript(QString*code);
		void editSlot(int);
		void timerSlot();
		void runSlot();
//		void scrollbarSlot(int);
		void clearMemSlot();
		void dockWindowSlot();
		void contextMenuSlot(int);
    void scrollPointSlot(int, int);

	signals:
		void prefChange(Preferences);
};

 
#endif

