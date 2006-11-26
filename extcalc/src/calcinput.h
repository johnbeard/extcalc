#ifndef CALCINPUT_H
#define CALCINPUT_H


#include "global.h"
#include <qtextedit.h>
#include <qfont.h>
#include <qpopupmenu.h>
#include <qthread.h>
#include <qevent.h>
#include "list.h"

/*
class ScriptThread :public QThread
{
	Script* script;
	QObject*parent;
//	Q_OBJECT
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
*/




class CalcInput :public QTextEdit
{
	int lineLength;
	int charLength;
	QString line;
	int lineCursor;
	QFont *stdFont;
	int lineCount;
	Variable*vars;
	Vector*vecs;
	bool scriptExec;
	List <int>resultParagraphs; 
//	ScriptThread*script;
	Script*scriptObject;
	ThreadSync*threadData;

	Preferences pref;
	
	Q_OBJECT
	public:
		CalcInput(QWidget*parentWin,Variable*va,Vector*ve) :QTextEdit((QWidget*)parentWin)
		{
			vars=va;
			vecs=ve;
			scriptExec=false;
//			script=NULL;
			stdFont=new QFont("Courier");
			stdFont->setPixelSize(16);
			stdFont->setFixedPitch(true);
			setFont(*stdFont);
			setTextFormat(Qt::PlainText);

			threadData=new ThreadSync;
			threadData->mutex=NULL;
			threadData->eventReciver=this;
			threadData->status=0;
			threadData->exit=false;
			threadData->usleep=false;
			threadData->bbreak=false;
			threadData->bcontinue=false;
			threadData->data=NULL;
			threadData->sleepTime=1000;
			threadData->vars=new Number*[27];
			for(int c=0; c<27;c++)
			{
				threadData->vars[c]=(Number*)malloc(sizeof(Number));
				threadData->numlen[c]=1;
				threadData->vars[c][0].type=NNONE;
			}

			QFontMetrics fontSize=fontMetrics();
			charLength=fontSize.size(0,QString("m")).width();
			setWrapPolicy(QTextEdit::AtWordOrDocumentBoundary);

			lineLength=width()/charLength-1;

			line="";
			lineCursor=0;
			lineCount=0;
			connect(this,SIGNAL(clicked(int,int)),this,SLOT(cursorSlot(int,int)));
		}


		void calculateKey();
		void deleteKey();
		void backKey();
		void clearAll();
		void cursorKey(int key);
		void textInput(QString text);
		void setPref(Preferences newPref)
		{
			pref=newPref;
		}


	protected:
		virtual void keyPressEvent(QKeyEvent*);
		virtual void resizeEvent(QResizeEvent*);
//		virtual void customEvent(QCustomEvent*ev);
		virtual QPopupMenu *createPopupMenu(const QPoint&);
	
	public slots:
		void cursorSlot(int para,int pos);
		void menuSlot(int item);
//		void scriptSlot(QString*code);

	signals:
		void prefChange(Preferences);
};





#endif


