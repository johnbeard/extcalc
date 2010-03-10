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
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <qicon.h>
#include <q3popupmenu.h>
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
#include "graphsolve.h"
#include "catalog.h"
#include "tabwidget.h"


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
//	Preferences pref;
//	ExtButtons *extButtons;
//	StandardButtons *standardButtons;
	FunctionTable* functionTable;
	GraphArea*graphArea;

	QLineEdit *inputLine;

	GraphSolveWidget *solveWidget;
	
	Q3ToolBar*toolBar;
//	Q3DockArea*dockArea;
	QComboBox *solveType,*functionType,*modeBox;
	QPixmap *minimizeIcon,*maximizeIcon,*printIcon,*catalogIcon;
	Catalog *catalog;
	QPushButton *drawButton,*maximizeButton,*catalogButton;
	QSplitter *horzSplit,*vertSplit;
	
//	bool maximized;
	bool solveMode;
//	Variable*vars;
//	ThreadSync*threadData;
//	List<int>tableFunctionMap;
//	QStringList colors;
//	QStringList colorList,graphTypeList;
	int changedRow;
	bool functionChanged;
	bool dynamicStart;
	int menuBottom;
	bool processStarted;
	
Q_OBJECT
	public:
	GraphWidget(QWidget*parent,Preferences pr,Variable*va,ThreadSync*td) :TabWidget(parent,pr,va,td,false)
	{
//		pref=pr;
//		vars=va;
//		menuBottom=mB;
//		threadData=td;
//		maximized=false;
		solveMode=false;
		functionChanged=false;
		changedRow=-1;
		dynamicStart=false;
		processStarted=false;


		horzSplit=new QSplitter(Qt::Horizontal,this);
		vertSplit=new QSplitter(Qt::Vertical,horzSplit);
//		standardButtons=new StandardButtons(this);
//		extButtons=new ExtButtons(this);
		functionTable=new FunctionTable((QWidget*)vertSplit,pref);
		graphArea=new GraphArea(horzSplit);
		graph=new GraphOutput(graphArea,vars,threadData);
		catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX,this);
		
		setMainWidget(horzSplit);
		addSubWidget(calcButtons);
		addSubWidget(extButtons);
		setDockArea(1);
		

		minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
		maximizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_remove.png"));
		printIcon=new QPixmap(INSTALLDIR+QString("/data/print.png"));
		catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));

//		dockArea=new Q3DockArea(Qt::Horizontal,Q3DockArea::Normal,this);
		toolBar=new Q3ToolBar();
		dockArea->moveDockWindow(toolBar);
		
		drawButton=new QPushButton(*printIcon,GRAPHH_STR1,toolBar);
		maximizeButton=new QPushButton(*maximizeIcon,"",toolBar);
		modeBox=new QComboBox(toolBar);
		catalogButton=new QPushButton(*catalogIcon,"",toolBar);
		catalogButton->setFixedWidth(30);
		maximizeButton->setFixedWidth(30);
		
		drawButton->setFixedHeight(25);
		
		solveType=new QComboBox(toolBar);
		functionType=new QComboBox(this);
		solveWidget=new GraphSolveWidget(this,pref,vars,threadData);
		solveType->hide();
		functionType->hide();
		solveWidget->hide();
		inputLine=new QLineEdit(vertSplit);
		inputLine->setFixedHeight(25);
		Q3ValueList<int> s = horzSplit->sizes();
		s[1]=300;
		s[0]=300;
		horzSplit->setSizes(s);
		
		
		

		solveType->insertItem(GRAPHH_STR4,-2);
		solveType->insertItem(GRAPHH_STR5,-3);
		solveType->insertItem(GRAPHH_STR6,-3);
		solveType->insertItem(GRAPHH_STR7,-4);
		solveType->insertItem(GRAPHH_STR8,-5);
		solveType->insertItem(GRAPHH_STR9,-6);
		solveType->insertItem(GRAPHH_STR10,-7);
		solveType->insertItem(GRAPHH_STR11,-8);
		solveType->insertItem(GRAPHH_STR26,-9);
		
		functionType->insertItem(TABLEH_STR3);
		functionType->insertItem(TABLEH_STR4);
		functionType->insertItem(TABLEH_STR5);
		functionType->insertItem(TABLEH_STR6);
		functionType->insertItem(TABLEH_STR7);
		functionType->insertItem(GRAPHH_STR30);
		modeBox->insertItem(GRAPHH_STR27);
		modeBox->insertItem(GRAPHH_STR28);
		modeBox->insertItem(GRAPHH_STR29);
		modeBox->setCurrentItem(0);


		QObject::connect(functionTable,SIGNAL(currentChanged(int,int)),this,SLOT(selectionChangedSlot(int,int)));
		QObject::connect(functionTable,SIGNAL(textEditStarted(QString)),this,SLOT(tableEditSlot(QString)));
		QObject::connect(drawButton,SIGNAL(released()),graph,SLOT(resetRotation()));
		QObject::connect(drawButton,SIGNAL(released()),graph,SLOT(removeLines()));
		QObject::connect(drawButton,SIGNAL(released()),this,SLOT(drawSlot()));
		QObject::connect(maximizeButton,SIGNAL(released()),this,SLOT(maximizeSlot()));
		QObject::connect(modeBox,SIGNAL(activated(int)),this,SLOT(modeSlot(int)));
		QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(graph,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(functionTable,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(solveWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(inputLine,SIGNAL(returnPressed()),this,SLOT(inputTextFinished()));
		QObject::connect(inputLine,SIGNAL(textChanged(const QString&)),this,SLOT(inputTextChanged(const QString&)));
		QObject::connect(graph,SIGNAL(leftMButtonPressed(double,double)),solveWidget,SLOT(graphLMButtonPressed(double,double)));
		QObject::connect(solveWidget,SIGNAL(addHorizontalLine(double)),graph,SLOT(drawHorizontalLine(double)));
		QObject::connect(solveWidget,SIGNAL(addVerticalLine(double)),graph,SLOT(drawVerticalLine(double)));
		QObject::connect(solveWidget,SIGNAL(addPolarLine(double)),graph,SLOT(drawPolarLine(double)));
		QObject::connect(solveWidget,SIGNAL(addCircle(double)),graph,SLOT(drawCircle(double)));
		QObject::connect(solveWidget,SIGNAL(add3dXLine(double,double)),graph,SLOT(draw3dXLine(double,double)));
		QObject::connect(solveWidget,SIGNAL(add3dYLine(double,double)),graph,SLOT(draw3dYLine(double,double)));
		QObject::connect(solveWidget,SIGNAL(add3dZLine(double,double)),graph,SLOT(draw3dZLine(double,double)));
		QObject::connect(solveWidget,SIGNAL(removeLines()),graph,SLOT(removeLines()));
		QObject::connect(solveType,SIGNAL(activated(int)),this,SLOT(solveTypeSlot(int)));
		QObject::connect(this,SIGNAL(solveTypeSignal(int)),solveWidget,SLOT(setState(int)));
		QObject::connect(functionType,SIGNAL(activated(int)),solveWidget,SLOT(setFunctionType(int)));
		QObject::connect(functionType,SIGNAL(activated(int)),this,SLOT(functionTypeSlot(int)));
		QObject::connect(solveWidget,SIGNAL(drawInequalityIntersection(int, int)),this,SLOT(inequalitySlot(int,int)));
		QObject::connect(solveWidget,SIGNAL(redrawGraphs()),this,SLOT(drawSlot()));
		QObject::connect(graph,SIGNAL(redrawSignal()),this,SLOT(drawSlot()));
		QObject::connect(graph,SIGNAL(screenshotSignal(QPixmap*)),solveWidget,SLOT(screenshotSlot(QPixmap*)));
		QObject::connect(solveWidget,SIGNAL(getScreenshotSignal(int,int)),graph,SLOT(screenshotSlot(int,int)));
		QObject::connect(solveWidget,SIGNAL(drawSignal(int,QColor,int)),graph,SLOT(drawSlot(int,QColor,int)));
		QObject::connect(this,SIGNAL(drawPointsSignal(long double*,int,bool)),graph,SLOT(drawPoints(long double*,int,bool)));
		QObject::connect(this,SIGNAL(removeLinesSignal()),graph,SLOT(removeLines()));
		QObject::connect(graph,SIGNAL(statisticsRedrawSignal()),this,SIGNAL(statisticsRedrawSignal()));
		QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(catalogButton,SIGNAL(clicked()),this,SLOT(catalogSlot()));
		QObject::connect(graphArea,SIGNAL(sizeChanged()),this,SLOT(graphSizeSlot()));
		QObject::connect(graph,SIGNAL(processingFinished()),this,SLOT(graphProcessingFinishedSlot()));

	}
	
void setPref(Preferences newPref)
{
	pref=newPref;
	if(modeBox->currentItem()!=2)
	{
		if(!(functionType->currentItem() == 0 ||
				functionType->currentItem() == 2 ||
				functionType->currentItem() == 3) && pref.graphType==GRAPHSTD)
		{
			solveWidget->setFunctionType(0);
			functionType->setCurrentItem(0);
			functionTypeSlot(0);
		}
		else if(functionType->currentItem() != 1 && pref.graphType==GRAPHPOLAR)
		{
			solveWidget->setFunctionType(1);
			functionType->setCurrentItem(1);
			functionTypeSlot(1);
		}
		else if(functionType->currentItem() != 4 && pref.graphType==GRAPH3D)
		{
			solveWidget->setFunctionType(4);
			functionType->setCurrentItem(4);
			functionTypeSlot(4);
		}
	}
	
	

	graph->setPref(pref);
	calcButtons->setPref(pref);
	extButtons->setPref(pref);
	solveWidget->setPref(pref);
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

public slots:
	
	void selectionChangedSlot(int row,int col);
	void tableEditSlot(QString);
	void drawSlot();
	void maximizeSlot();
	void modeSlot(int);
	void inputTextChanged(const QString&);
	void inputTextFinished();
	void buttonInputSlot(QString);
	void solveTypeSlot(int);
	void editSlot(int);
	void catalogSlot();
	void graphSizeSlot();
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


