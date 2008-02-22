/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         graphsolve.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

The class in this file includes the graph analysis sub-window and the code of the graph analysis
functions.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef GRAPHSOLVEH
#define GRAPHSOLVEH

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qcolordialog.h>
#include "calctable.h"
#include "global.h"




#define INTEGRAL3DSTEPS	(250<<pref.solvePrec)
#define TEXTURESIZE	(256<<pref.solvePrec)
#define ANALYSESTEPS (1000<<pref.solvePrec)
#define EXACTANALYSESTEPS (100<<pref.solvePrec)



class GraphSolveWidget :public QWidget
{

	Preferences pref;
	QLabel *xLabel,*x2Label,*x3Label,*x4Label,*yLabel,*aLabel,*formatLabel,*penLabel;
	QLineEdit*xLine,*x2Line,*x3Line,*x4Line,*aLine;
	QSpinBox*spinBox,*spinBox2,*spinBox3;
	CalcTable*outputTable;
	QPushButton*solveButton,*saveButton,*openButton;
	QPushButton*freeButton,*lineButton,*rectButton,*circleButton,*rubberButton,*textButton;
	QPushButton*backButton,*forwardButton,*clearButton,*colorButton;
	QComboBox*functionBox,*functionBox2;
	QComboBox*formatBox;
	int solveType,solveOptions;
	Variable*vars;
	ThreadSync*threadData;
	int*functionIndices;
	int functionType;
	bool aVisible;
	QPixmap *openIcon,*freeIcon,*lineIcon,*rectIcon,*circleIcon,*rubberIcon,*colorIcon,*textIcon;
	QColor paintColor;
	int drawState;
	
	
	Q_OBJECT
public:
	
	GraphSolveWidget(QWidget*parent,Preferences pr,Variable*va,ThreadSync*td) :QWidget(parent)
	{
		aVisible=false;
		vars=va;
		threadData=td;
		pref=pr;
		functionType=GRAPHSTD;
		functionIndices=new int[20];
		xLabel=new QLabel(" ",this);
		x2Label=new QLabel(" ",this);
		x3Label=new QLabel(" ",this);
		x4Label=new QLabel(" ",this);
		yLabel=new QLabel(" ",this);
		aLabel=new QLabel(GRAPHSOLVEH_STR2,this);
		formatLabel=new QLabel(" ",this);
		penLabel = new QLabel(GRAPHSOLVEH_STR3,this);
		xLine=new QLineEdit(this);
		x2Line=new QLineEdit(this);
		x3Line=new QLineEdit(this);
		x4Line=new QLineEdit(this);
		aLine=new QLineEdit(this);
		drawState=DRAWNONE;
		
		spinBox=new QSpinBox(1,10000,1,this);
		spinBox->setValue(5);
		spinBox2=new QSpinBox(1,10000,1,this);
		spinBox2->setValue(5);
		spinBox3=new QSpinBox(1,10,1,this);
		spinBox3->setValue(1);
		
		outputTable=new CalcTable(this,0);
//		outputTable->setDragEnabled(true);
		solveButton=new QPushButton(GRAPHSOLVEH_STR1,this);
		saveButton=new QPushButton(GRAPHSOLVEH_STR4,this);
		functionBox=new QComboBox(this);
		functionBox2=new QComboBox(this);
		formatBox=new QComboBox(this);
		openButton=new QPushButton("",this);
		openIcon=new QPixmap(INSTALLDIR+QString("/data/open.png"));
		openButton->setPixmap(*openIcon);

		backButton=new QPushButton(GRAPHSOLVEH_STR5,this);
		forwardButton=new QPushButton(GRAPHSOLVEH_STR6,this);
		clearButton=new QPushButton(GRAPHSOLVEH_STR7,this);
		freeButton=new QPushButton("",this);
		rectButton=new QPushButton("",this);
		lineButton=new QPushButton("",this);
		circleButton=new QPushButton("",this);
		rubberButton=new QPushButton("",this);
		textButton=new QPushButton("",this);

		freeIcon=new QPixmap(INSTALLDIR+QString("/data/free.png"));
		rectIcon=new QPixmap(INSTALLDIR+QString("/data/rect.png"));
		lineIcon=new QPixmap(INSTALLDIR+QString("/data/line.png"));
		circleIcon=new QPixmap(INSTALLDIR+QString("/data/circle.png"));
		rubberIcon=new QPixmap(INSTALLDIR+QString("/data/rubber.png"));
		textIcon=new QPixmap(INSTALLDIR+QString("/data/text.png"));
		colorIcon=new QPixmap(20,20);
		paintColor.setRgb(255,0,0);
		colorIcon->fill(paintColor);
		colorButton=new QPushButton(*colorIcon,GRAPHSOLVEH_STR8,this);

		freeButton->setToggleButton(true); 
		rectButton->setToggleButton(true); 
		lineButton->setToggleButton(true); 
		circleButton->setToggleButton(true); 
		rubberButton->setToggleButton(true); 
		textButton->setToggleButton(true); 

		freeButton->setPixmap(*freeIcon);
		rectButton->setPixmap(*rectIcon);
		lineButton->setPixmap(*lineIcon);
		circleButton->setPixmap(*circleIcon);
		rubberButton->setPixmap(*rubberIcon);
		textButton->setPixmap(*textIcon);

		solveType=CALCYVAL;
		solveOptions=0;

		QObject::connect(solveButton,SIGNAL(clicked()),this,SLOT(solveButtonSlot()));
		QObject::connect(openButton,SIGNAL(clicked()),this,SLOT(openButtonSlot()));
		QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(solveButtonSlot()));
		QObject::connect(colorButton,SIGNAL(clicked()),this,SLOT(colorButtonSlot()));
		QObject::connect(spinBox3,SIGNAL(valueChanged(int)),this,SLOT(penValueSlot(int)));
		QObject::connect(forwardButton,SIGNAL(clicked()),this,SLOT(forwardButtonSlot()));
		QObject::connect(backButton,SIGNAL(clicked()),this,SLOT(backButtonSlot()));
		QObject::connect(clearButton,SIGNAL(clicked()),this,SLOT(clearButtonSlot()));
		QObject::connect(freeButton,SIGNAL(clicked()),this,SLOT(freeButtonSlot()));
		QObject::connect(lineButton,SIGNAL(clicked()),this,SLOT(lineButtonSlot()));
		QObject::connect(rectButton,SIGNAL(clicked()),this,SLOT(rectButtonSlot()));
		QObject::connect(circleButton,SIGNAL(clicked()),this,SLOT(circleButtonSlot()));
		QObject::connect(rubberButton,SIGNAL(clicked()),this,SLOT(rubberButtonSlot()));
		QObject::connect(textButton,SIGNAL(clicked()),this,SLOT(textButtonSlot()));
		
		resetDialog();
	}
	

	void resetDialog();
//	void updateFunctions(QString*,int);
	void setPref(Preferences newPref);
	void calculateYVal(QString);
	int calculateRoots(QString,long double, long double,long double**,int varIndex,long double,bool forceScript);
	long double calculateValue(QString,long double,int varIndex,bool forceScript);
	void showRoots(QString,QColor color);
	void calculateNewton(QString,bool forceScript);
	void setFunctionBox(QComboBox*fBox);
	
protected:

	virtual void resizeEvent(QResizeEvent*);
	
	
public slots:
	void solveButtonSlot();
	void graphLMButtonPressed(double,double);
	void setState(int newSolveType);
	void setFunctionType(int fType);
	void screenshotSlot(QPixmap*);
	void openButtonSlot();
	void colorButtonSlot();
	void penValueSlot(int);
	void forwardButtonSlot();
	void backButtonSlot();
	void clearButtonSlot();
	void freeButtonSlot();
	void lineButtonSlot();
	void rectButtonSlot();
	void circleButtonSlot();
	void rubberButtonSlot();
	void textButtonSlot();
	
signals:
	void addVerticalLine(double x);
	void addHorizontalLine(double y);
	void addPolarLine(double angle);
	void addCircle(double radius);
	void add3dXLine(double y,double z);
	void add3dYLine(double x,double z);
	void add3dZLine(double x,double y);
	void removeLines();
	void prefChange(Preferences);
	void drawInequaityIntersection(int, int);
	void redrawGraphs();
	void getScreenshotSignal(int,int);
	void drawSignal(int,QColor,int);
	
};















#endif

