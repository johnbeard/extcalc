/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         table.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

The tab window for function tables 

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef TABLEH
#define TABLEH 

#include <QWidget>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qinputdialog.h>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <qicon.h>
#include <qtooltip.h>
#include <qsplitter.h>
//Added by qt3to4:
#include <QPixmap>
#include <QResizeEvent>
#include <Q3ValueList>
#include "functiontable.h"
#include "buttons.h"
#include "catalog.h"
#include "tabwidget.h"





class TableWidget :public TabWidget
{
	
//	Preferences pref;
//	ExtButtons *extButtons;
//	StandardButtons *standardButtons;
	FunctionTable* functionTable;
	QLineEdit*inputLine;
	CalcTable*outputTable;
	QPushButton*calculateButton,*maximizeButton,*catalogButton;
	QPixmap *minimizeIcon,*maximizeIcon,*catalogIcon;
	QComboBox*typeBox;
	Q3ToolBar*toolBar;
//	Q3DockArea*dockArea;
	Catalog *catalog;
	QSplitter *horzSplit,*vertSplit;
//	Variable*vars;
//	bool fullscreen;
	List <double>vertValues;
	List <double>horzValues;
	Q3Header*horzHeader,*vertHeader;
//	ThreadSync*threadData;
//	int menuBottom;
	
	Q_OBJECT
public:
	TableWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td) :TabWidget(parent,p,va,td,false)
	{
//		pref=p;
//		vars=va;
//		threadData=td;
//		menuBottom=mB;
//		fullscreen=false;
//		extButtons=new ExtButtons(this);
//		standardButtons=new StandardButtons(this);
		horzSplit=new QSplitter(Qt::Horizontal,this);
		vertSplit=new QSplitter(Qt::Vertical,horzSplit);
		functionTable=new FunctionTable(vertSplit,pref);
		inputLine=new QLineEdit(vertSplit);
		outputTable=new CalcTable(horzSplit,0,true);
		outputTable->setNumRows(10);
		outputTable->setNumCols(4);
		horzHeader=outputTable->horizontalHeader();
		vertHeader=outputTable->verticalHeader();
		horzHeader->setClickEnabled(true);
		vertHeader->setClickEnabled(true);
		catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX,this);
//		dockArea=new Q3DockArea(Qt::Horizontal,Q3DockArea::Normal,this);
		toolBar=new Q3ToolBar();
		dockArea->moveDockWindow(toolBar);
		
		setMainWidget(horzSplit);
		addSubWidget(calcButtons);
		addSubWidget(extButtons);
		setDockArea(1);
		
		minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
		maximizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_remove.png"));
		catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));
		
		
		calculateButton=new QPushButton(TABLEH_STR1,toolBar);
		maximizeButton=new QPushButton(*maximizeIcon,"",toolBar);
		typeBox=new QComboBox(toolBar);
		catalogButton=new QPushButton(*catalogIcon,"",toolBar);
		catalogButton->setFixedWidth(30);
		maximizeButton->setFixedWidth(30);
		
		QToolTip::add(maximizeButton,TABLEH_STR13);
		QToolTip::add(typeBox,TABLEH_STR14);
		QToolTip::add(catalogButton,TABLEH_STR15);
		
		typeBox->insertItem(TABLEH_STR3);
		typeBox->insertItem(TABLEH_STR4);
		typeBox->insertItem(TABLEH_STR5);
		typeBox->insertItem(TABLEH_STR6);
		typeBox->insertItem(TABLEH_STR7);
		typeBox->insertItem(TABLEH_STR9);
		
		Q3ValueList<int> s = horzSplit->sizes();
		s[1]=300;
		s[0]=300;
		horzSplit->setSizes(s);
		
		QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(functionTable,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(functionTable,SIGNAL(currentChanged(int,int)),this,SLOT(selectionChangedSlot(int,int)));
		QObject::connect(functionTable,SIGNAL(textEditStarted(QString)),this,SLOT(tableEditSlot(QString)));
		QObject::connect(inputLine,SIGNAL(returnPressed()),this,SLOT(inputTextChanged()));
		QObject::connect(inputLine,SIGNAL(lostFocus()),this,SLOT(inputTextChanged()));
		QObject::connect(calculateButton,SIGNAL(clicked()),this,SLOT(calculateButtonSlot()));
		QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeButtonSlot()));
		QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(typeBox,SIGNAL(activated(const QString&)),this,SLOT(typeBoxSlot(const QString&)));
		QObject::connect(horzHeader,SIGNAL(clicked(int)),this,SLOT(horzHeaderSlot(int)));
		QObject::connect(vertHeader,SIGNAL(clicked(int)),this,SLOT(vertHeaderSlot(int)));
		QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(catalogButton,SIGNAL(clicked()),this,SLOT(catalogSlot()));
	}
	
	void setPref(Preferences);
	
public slots:
	void getPref(Preferences);
	void selectionChangedSlot(int row,int col);
	void tableEditSlot(QString);
	void inputTextChanged();
	void calculateButtonSlot();
	void typeBoxSlot(const QString&);
	void maximizeButtonSlot();
	void buttonInputSlot(QString);
	void editSlot(int);
	void horzHeaderSlot(int);
	void vertHeaderSlot(int);
	void tableMenuSlot(int);
	void dockWindowSlot();
	void catalogSlot();
	
//protected:
//	virtual void resizeEvent(QResizeEvent*);
	
	
signals:
	void prefChange(Preferences);
	
};






#endif






