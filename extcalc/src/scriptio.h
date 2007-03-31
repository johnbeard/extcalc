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
#include "list.h"

#define IMDEFAULT		1
#define IMSCRIPTING		2
#define IMGETLINE		3
#define IMGETKEY		4

#define BUFFER_LENGTH 100




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

class ScriptIOWidget :public QWidget
{
	Variable *vars;
	
	StandardButtons*calcButtons;
	ExtButtons*extButtons;
	Preferences pref,runningPref;
	QPushButton*maximizeButton,*killButton,*runButton;
	QPopupMenu*contextMenu;
	
	bool maximized;
	int ioFieldWidth,ioFieldHeight;
	QPixmap*buffer;
	QFont*drawFont;
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

	Q_OBJECT

	public:
		ScriptIOWidget(QWidget*parent,Preferences pr,Variable *) :QWidget(parent)
		{
		//	vars=va;
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
		void selectText(int startx,int starty,int endx,int endy);

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

