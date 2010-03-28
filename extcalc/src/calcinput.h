/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         calcinput.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This class creates the normal calculator user interface. It receives the user input, runs the
math classes and shows the user output.
////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef CALCINPUT_H
#define CALCINPUT_H


#include "global.h"
#include <q3textedit.h>
#include <qfont.h>
#include <q3popupmenu.h>
#include <qthread.h>
#include <qevent.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QKeyEvent>
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




class CalcInput :public Q3TextEdit
{
	int lineLength;
	int charLength;
	QString line;
	int lineCursor;
	QFont *stdFont;
	int lineCount;
	Variable*vars;
	bool scriptExec;
	List <int>resultParagraphs; 
//	ScriptThread*script;
	Script*scriptObject;
	ThreadSync*threadData;
	bool ansAvailable,ansDone,autoBrace;

	Preferences pref;
	
	Q_OBJECT
	public:
		CalcInput(QWidget*parentWin,Variable*va,ThreadSync*td,bool aB=false) :Q3TextEdit((QWidget*)parentWin)
		{
			vars=va;
			threadData=td;
			scriptExec=false;
			autoBrace=aB;
//			script=NULL;
      stdFont=new QFont("monospace",10);
			stdFont->setFixedPitch(true);
			setFont(*stdFont);
			setTextFormat(Qt::PlainText);
			ansAvailable=false;
			ansDone=false;


			QFontMetrics fontSize=fontMetrics();
			charLength=fontSize.size(0,QString("m")).width();
			setWrapPolicy(Q3TextEdit::AtWordOrDocumentBoundary);

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
		virtual Q3PopupMenu *createPopupMenu(const QPoint&);
	
	public slots:
		void cursorSlot(int para,int pos);
		void menuSlot(int item);
//		void scriptSlot(QString*code);

	signals:
		void prefChange(Preferences);
		void calcSignal();
};





#endif


