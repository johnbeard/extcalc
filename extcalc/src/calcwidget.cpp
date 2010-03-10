/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         calcwidget.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "calcwidget.h"
//Added by qt3to4:
#include <QResizeEvent>



CalcWidget::CalcWidget(QWidget*parent,Preferences p,Variable *va,ThreadSync*td) :TabWidget(parent,p,va,td,false)
{

	textEdit=new CalcInput(this,vars,threadData);

	setMainWidget(textEdit);
	addSubWidget(calcButtons);
	addSubWidget(extButtons);
	setDockArea(1);

	minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
	maximizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_remove.png"));
	angleIcon=new QPixmap(INSTALLDIR+QString("/data/angle.png"));
	scientificIcon=new QPixmap(INSTALLDIR+QString("/data/scientific.png"));
	baseIcon=new QPixmap(INSTALLDIR+QString("/data/binary.png"));
	catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));
		
	toolBar=new Q3ToolBar();
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


void CalcWidget::getPref(Preferences newPref)
{
	emit prefChange(newPref);
}


void CalcWidget::viewSlot()
{
	if(isMaximized())
	{
		maximizeSlot(false);
		viewButton->setIconSet(*maximizeIcon);
	}
	else{
		maximizeSlot(true);
		viewButton->setIconSet(*minimizeIcon);
	}
}

void CalcWidget::baseSlot(int index)
{
	if(index == 0 && pref.base!=BIN)		//bin
	{
		pref.base=BIN;
		emit prefChange(pref);
	}
	else if(index==1 && pref.base!=OCT)		//oct
	{
		pref.base=OCT;
		emit prefChange(pref);
	}
	else if(index==2 && pref.base!=DEC)		//dec
	{
		pref.base=DEC;
		emit prefChange(pref);
	}
	else if(index==3 && pref.base!=HEX)		//hex
	{
		pref.base=HEX;
		emit prefChange(pref);
	}
}

void CalcWidget::angleSlot(int index)
{
	if(index == 0 && pref.angle!=DEG)			//deg
	{
		pref.angle=DEG;
		emit prefChange(pref);
	}
	else if(index==1 && pref.angle!=RAD)		//rad
	{
		pref.angle=RAD;
		emit prefChange(pref);
	}
	else if(index==2 && pref.angle!=GRA)		//gra
	{
		pref.angle=GRA;
		emit prefChange(pref);
	}	
}

void CalcWidget::typeSlot(int index)
{
	if(index == 0 && pref.calcType!=SCIENTIFIC)		//scientific
	{
		pref.calcType=SCIENTIFIC;
		emit prefChange(pref);
	}
	else if(index==1 && pref.calcType!=BASE)		//base
	{
		pref.calcType=BASE;
		emit prefChange(pref);
	}
}


void CalcWidget::editSlot(int type)
{
	if(textEdit->hasFocus())
	{
		switch(type)
		{
			case EDITUNDO:
				textEdit->menuSlot(1);
				break;
			case EDITREDO:
				textEdit->menuSlot(2);
				break;
			case EDITCUT:
				textEdit->menuSlot(3);
				break;
			case EDITCOPY:
				textEdit->menuSlot(4);
				break;
			case EDITPASTE:
				textEdit->menuSlot(5);
				break;
		}
	}
}


void CalcWidget::catalogSlot()
{
	catalog->exec(toolBar->mapToGlobal(QPoint(catalogButton->x(),catalogButton->y()+catalogButton->height())));
}

void CalcWidget::constantsSlot()
{
	constants->exec(toolBar->mapToGlobal(QPoint(constantsButton->x(),constantsButton->y()+constantsButton->height())));
}

void CalcWidget::dockWindowSlot()
{
	dockArea->moveDockWindow(toolBar);
}

void CalcWidget::setPref(Preferences newPref)
{
	pref=newPref;
	
	if(pref.calcType==BASE)
	{
		typeBox->setCurrentItem(1);
		angleBox->hide();
		baseBox->show();
	}
	else
	{
		typeBox->setCurrentItem(0);
		angleBox->show();
		baseBox->hide();
	}
	switch(pref.angle)
	{
		case DEG:
			angleBox->setCurrentItem(0);
			break;
		case RAD:
			angleBox->setCurrentItem(1);
			break;
		case GRA:
			angleBox->setCurrentItem(2);
			break;
	}
	switch(pref.base)
	{
		case BIN:
			baseBox->setCurrentItem(0);
			break;
		case OCT:
			baseBox->setCurrentItem(1);
			break;
		case DEC:
			baseBox->setCurrentItem(2);
			break;
		case HEX:
			baseBox->setCurrentItem(3);
			break;
	}
		
	calcButtons->setPref(pref);
	extButtons->setPref(pref);
	textEdit->setPref(pref);
	constants->setPref(pref);
}

