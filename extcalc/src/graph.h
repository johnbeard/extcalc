/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         graph.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Class of the graphics tab window

////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef GRAPHH
#define GRAPHH

#include <stdio.h>
#include <stdlib.h>
#include <qapplication.h>
#include <QWidget>
#include <qpainter.h>
#include <qmessagebox.h>
#include <QGLWidget>
#include <QtOpenGL>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <QToolBar>
#include <qicon.h>
#include <qtooltip.h>
#include <qsplitter.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <Q3ValueList>
#include <QPixmap>
#include <math.h>
#include "list.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "functiontable.h"
#include "graphout.h"
#include "buttons.h"
#include "catalog.h"
#include "tabwidget.h"
#include "screenshotdialog.h"


class GraphArea :public QWidget
{
	Q_OBJECT
			
	public:
	GraphArea(QWidget*parent) :QWidget(parent)
	{
	;
	}
	
	protected:
	virtual void resizeEvent(QResizeEvent*)
	{
		emit sizeChanged();
	}
	
	signals:
	void sizeChanged();	
};





class GraphWidget :public TabWidget
{
	GraphOutput*graph;
	FunctionTable* functionTable;
	GraphArea*graphArea;

  StandardButtons*calcButtons;
  ExtButtons*extButtons;

	QLineEdit *inputLine;

//	GraphSolveWidget *solveWidget;
  ScreenshotDialog *screenshotDialog;

  QComboBox *solveType,*modeBox;
//	QPixmap *minimizeIcon,*maximizeIcon,*printIcon,*catalogIcon;
	Catalog *catalog;
//	QPushButton *drawButton,*maximizeButton,*catalogButton;
	QSplitter *horzSplit,*vertSplit;

  QAction*maximizeAction,*catalogAction;                 //global
  QAction*drawAction;                                    //graphics


	bool solveMode;
	int changedRow;
	bool functionChanged;
	bool dynamicStart;
	int menuBottom;
	bool processStarted;
	
Q_OBJECT
	public:
  GraphWidget(QWidget*parent,Preferences pr,Variable*va,ThreadSync*td,ScreenshotDialog *sd,StandardButtons*cb,ExtButtons*eB);
	
void setPref(Preferences newPref)
{
	pref=newPref;
	if(modeBox->currentItem()!=2)
	{
/*		if(!(functionType->currentItem() == 0 ||
				functionType->currentItem() == 2 ||
				functionType->currentItem() == 3) && pref.graphType==GRAPHSTD)
		{
//			solveWidget->setFunctionType(0);
			functionType->setCurrentItem(0);
			functionTypeSlot(0);
		}
		else if(functionType->currentItem() != 1 && pref.graphType==GRAPHPOLAR)
		{
//			solveWidget->setFunctionType(1);
			functionType->setCurrentItem(1);
			functionTypeSlot(1);
		}
		else if(functionType->currentItem() != 4 && pref.graphType==GRAPH3D)
		{
//			solveWidget->setFunctionType(4);
			functionType->setCurrentItem(4);
			functionTypeSlot(4);
    }*/
	}
	
	

	graph->setPref(pref);
//	calcButtons->setPref(pref);
//	extButtons->setPref(pref);
//	solveWidget->setPref(pref);
	functionTable->setPref(pref);
	

	

	graphSizeSlot();

}

void getUIState(int*sizes)
{
	for(int c=0; c<6; c++)
		sizes[c]=functionTable->columnWidth(c);
}
void setUIState(int*sizes)
{
	for(int c=0; c<6; c++)
		functionTable->setColumnWidth(c,sizes[c]);
}

QGLWidget*getShareContext()
{
	return (QGLWidget*)graph;
}

private:
  void updateUIState();

public slots:
	
	void selectionChangedSlot(int row,int col);
	void tableEditSlot(QString);
	void drawSlot();
	void modeSlot(int);
	void inputTextChanged(const QString&);
	void inputTextFinished();
  void processText(QString);
	void solveTypeSlot(int);
	void editSlot(int);
	void catalogSlot();
	void graphSizeSlot();
  void viewSlot(bool);
	void dockWindowSlot();
	void inequalitySlot(int,int);
	void graphProcessingFinishedSlot();
	void getPref(Preferences newPref)
	{
		emit prefChange(newPref);
	}
	void functionTypeSlot(int fType);


protected:
//	virtual void resizeEvent(QResizeEvent*);

signals:
	void prefChange(Preferences);
	void solveTypeSignal(int);
	void drawPointsSignal(long double*,int,bool);
	void removeLinesSignal();
	void statisticsRedrawSignal();
	
};


#endif


