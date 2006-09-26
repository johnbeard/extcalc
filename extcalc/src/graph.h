
#ifndef GRAPHH
#define GRAPHH

#include <stdio.h>
#include <stdlib.h>
#include <qapplication.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qgl.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
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







class GraphWidget :public QWidget
{
	GraphOutput*graph;
	Preferences pref;
	ExtButtons *extButtons;
	StandardButtons *standardButtons;
	FunctionTable* functionTable;
	QPushButton *drawButton,*maximizeButton,*solveButton;
	QLineEdit *inputLine;
	QComboBox *solveType,*functionType;
	GraphSolveWidget *solveWidget;
	bool maximized;
	bool solveMode;
	Variable*vars;
//	List<int>tableFunctionMap;
//	QStringList colors;
//	QStringList colorList,graphTypeList;
	int changedRow;
	bool functionChanged;
	
	
Q_OBJECT
	public:
	GraphWidget(QWidget*parent,Preferences pr,Variable*va) :QWidget(parent)
	{
		pref=pr;
		vars=va;
		maximized=false;
		solveMode=false;
		functionChanged=false;
		changedRow=-1;


		graph=new GraphOutput(this,vars);
		standardButtons=new StandardButtons(this);
		extButtons=new ExtButtons(this);
		functionTable=new FunctionTable((QWidget*)this,pref);
		drawButton=new QPushButton(GRAPHH_STR1,this);
		maximizeButton=new QPushButton(GRAPHH_STR2,this);
		solveButton=new QPushButton(GRAPHH_STR3,this);
		solveType=new QComboBox(this);
		functionType=new QComboBox(this);
		solveWidget=new GraphSolveWidget(this,pref,vars);
		solveType->hide();
		functionType->hide();
		solveWidget->hide();
		inputLine=new QLineEdit(this);

		solveType->insertItem(GRAPHH_STR4,-2);
		solveType->insertItem(GRAPHH_STR5,-3);
		solveType->insertItem(GRAPHH_STR6,-3);
		solveType->insertItem(GRAPHH_STR7,-4);
		solveType->insertItem(GRAPHH_STR8,-5);
		solveType->insertItem(GRAPHH_STR9,-6);
		solveType->insertItem(GRAPHH_STR10,-7);
		solveType->insertItem(GRAPHH_STR11,-8);
		solveType->insertItem("Save and modify",-9);
		
		functionType->insertItem(TABLEH_STR3);
		functionType->insertItem(TABLEH_STR4);
		functionType->insertItem(TABLEH_STR5);
		functionType->insertItem(TABLEH_STR6);
		functionType->insertItem(TABLEH_STR7);


		QObject::connect(functionTable,SIGNAL(currentChanged(int,int)),this,SLOT(selectionChangedSlot(int,int)));
		QObject::connect(functionTable,SIGNAL(textEditStarted(QString)),this,SLOT(tableEditSlot(QString)));
		QObject::connect(drawButton,SIGNAL(clicked()),graph,SLOT(resetRotation()));
		QObject::connect(drawButton,SIGNAL(clicked()),graph,SLOT(removeLines()));
		QObject::connect(drawButton,SIGNAL(clicked()),this,SLOT(drawSlot()));
		QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeSlot()));
		QObject::connect(solveButton,SIGNAL(clicked()),this,SLOT(solveSlot()));
		QObject::connect(standardButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(standardButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
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
		QObject::connect(solveWidget,SIGNAL(drawInequaityIntersection(int, int)),graph,SLOT(inequaityIntersectionSlot(int,int)));
		QObject::connect(solveWidget,SIGNAL(redrawGraphs()),this,SLOT(drawSlot()));
		QObject::connect(graph,SIGNAL(redrawSignal()),this,SLOT(drawSlot()));
		QObject::connect(graph,SIGNAL(screenshotSignal(QPixmap*)),solveWidget,SLOT(screenshotSlot(QPixmap*)));
		QObject::connect(solveWidget,SIGNAL(getScreenshotSignal(int,int)),graph,SLOT(screenshotSlot(int,int)));
		QObject::connect(solveWidget,SIGNAL(drawSignal(int,QColor,int)),graph,SLOT(drawSlot(int,QColor,int)));

	}
	
void setPref(Preferences newPref)
{
	pref=newPref;
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
	
	

	graph->setPref(pref);
	standardButtons->setPref(pref);
	extButtons->setPref(pref);
	solveWidget->setPref(pref);
	functionTable->setPref(pref);
	

	resizeEvent(NULL);

}

public slots:
	
	void selectionChangedSlot(int row,int col);
	void tableEditSlot(QString);
	void drawSlot();
	void maximizeSlot();
	void solveSlot();
	void inputTextChanged(const QString&);
	void inputTextFinished();
	void buttonInputSlot(QString);
	void solveTypeSlot(int);
	void editSlot(int);
	void getPref(Preferences newPref)
	{
		emit prefChange(newPref);
	}
	void functionTypeSlot(int fType);


protected:
	virtual void resizeEvent(QResizeEvent*);

signals:
	void prefChange(Preferences);
	void solveTypeSignal(int);
	
};


#endif


