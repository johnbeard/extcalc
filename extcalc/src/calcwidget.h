/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         calcwidget.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This is the class for the calculator tab window.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef CALCWIDGETH
#define CALCWIDGETH



#include "buttons.h"
#include "calcinput.h"
#include "catalog.h"
#include <qcombobox.h>

#include <qtoolbar.h>
#include <qdockarea.h>
#include <qiconset.h>
#include <qpopupmenu.h>
#include <qtooltip.h>



class CalcWidget :public QWidget
{
	CalcInput*textEdit;
	StandardButtons*calcButtons;
	ExtButtons*extButtons;
	Preferences pref;
	int menuBottom;

	bool maximized;
	Variable *vars;
	ThreadSync*threadData;
	
	QToolBar*toolBar;
	QDockArea*dockArea;
	QComboBox *angleBox,*baseBox,*typeBox;
	QPixmap *minimizeIcon,*angleIcon,*maximizeIcon,*scientificIcon,*baseIcon,*catalogIcon;
	Catalog *catalog,*constants;
	QPushButton* catalogButton,*viewButton,*constantsButton;

	Q_OBJECT

//	QLabel *text1,*text2,*text3;
//	QLabel *num1,*num2,*num3,*num4;



	
	public:
	CalcWidget(QWidget*parent,Preferences p,Variable *va,ThreadSync*td,int mB) :QWidget(parent)
	{
		vars=va;
		threadData=td;
		pref=p;
		menuBottom=mB;
		maximized=false;	
		textEdit=new CalcInput(this,vars,threadData);
		calcButtons=new  StandardButtons(this);
		extButtons=new ExtButtons(this);

		minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
		maximizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_remove.png"));
		angleIcon=new QPixmap(INSTALLDIR+QString("/data/angle.png"));
		scientificIcon=new QPixmap(INSTALLDIR+QString("/data/scientific.png"));
		baseIcon=new QPixmap(INSTALLDIR+QString("/data/binary.png"));
		catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));
		
		dockArea=new QDockArea(Qt::Horizontal,QDockArea::Normal,this);
		toolBar=new QToolBar();
		dockArea->moveDockWindow(toolBar);
		
		viewButton=new QPushButton(*maximizeIcon,"",toolBar);
		viewButton->setFixedWidth(30);

		typeBox=new QComboBox(toolBar);
		typeBox->insertItem(*scientificIcon,"scientific");
		typeBox->insertItem(*baseIcon,"base");

		angleBox=new QComboBox(toolBar);
		angleBox->insertItem(*angleIcon,"DEG");
		angleBox->insertItem(*angleIcon,"RAD");
		angleBox->insertItem(*angleIcon,"GRA");
		if(pref.angle==DEG)	angleBox->setCurrentItem(0);
		else if(pref.angle==RAD) angleBox->setCurrentItem(1);
		else angleBox->setCurrentItem(2);
		
		baseBox=new QComboBox(toolBar);
		baseBox->insertItem("BIN");
		baseBox->insertItem("OCT");
		baseBox->insertItem("DEC");
		baseBox->insertItem("HEX");
		if(pref.base==BIN) baseBox->setCurrentItem(0);
		else if(pref.base==OCT) baseBox->setCurrentItem(1);
		else if(pref.base==HEX) baseBox->setCurrentItem(3);
		else baseBox->setCurrentItem(2);
		
		catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX | CATMATRIX | CATMATHLOGIC,toolBar);
		catalog->show();
		catalogButton=new QPushButton(*catalogIcon,"",toolBar);
		catalogButton->setFixedWidth(30);
		
		constants=new Catalog(CATCONSTANTS,toolBar,&pref);
		constants->show();
		constantsButton=new QPushButton("C",toolBar);
		constantsButton->setFixedWidth(30);
		
		
		QToolTip::add(viewButton,CALCWIDGETH_STR4);
		QToolTip::add(typeBox,CALCWIDGETH_STR5);
		QToolTip::add(baseBox,CALCWIDGETH_STR6);
		QToolTip::add(angleBox,CALCWIDGETH_STR7);
		QToolTip::add(catalogButton,CALCWIDGETH_STR8);
		QToolTip::add(constantsButton,tr("Constants and conversation"));


		
		if(pref.calcType==BASE)
		{
			typeBox->setCurrentItem(1);
			angleBox->hide();
		}
		else
		{
			typeBox->setCurrentItem(0);
			baseBox->hide();
		}
		
			
			
		textEdit->setGeometry(20,50,600,310);
		calcButtons->setGeometry(20,380,280,200);
		extButtons->setGeometry(320,420,300,160);
		
		QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(processText(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(processText(QString)));
		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(constants,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(textEdit,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(viewButton,SIGNAL(clicked()),this,SLOT(viewSlot()));
		QObject::connect(baseBox,SIGNAL(activated(int)),this,SLOT(baseSlot(int)));
		QObject::connect(angleBox,SIGNAL(activated(int)),this,SLOT(angleSlot(int)));
		QObject::connect(typeBox,SIGNAL(activated(int)),this,SLOT(typeSlot(int)));
		QObject::connect(catalogButton,SIGNAL(clicked()),this,SLOT(catalogSlot()));
		QObject::connect(constantsButton,SIGNAL(clicked()),this,SLOT(constantsSlot()));
		QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(processText(QString)));
		QObject::connect(constants,SIGNAL(menuSignal(QString)),this,SLOT(processText(QString)));
		
		
	}
	
	void setPref(Preferences newPref);

	

protected:
	
	virtual void resizeEvent(QResizeEvent*);

	
public slots:

	void getPref(Preferences newPref);
	void viewSlot();
	void baseSlot(int);
	void angleSlot(int);
	void typeSlot(int);
	void editSlot(int);
	void catalogSlot();
	void constantsSlot();
	void dockWindowSlot();

	
	void processText(QString text)
	{
	if(text == "calculate")
		textEdit->calculateKey();
	else if(text == "backkey")
		textEdit->backKey();
	else if(text == "clearall")
		textEdit->clearAll();
	else {
		textEdit->setBold(false);
		textEdit->textInput(text);
		}
	}
signals:
	void prefChange(Preferences);
	void runScript(QString*);
};

 
#endif

