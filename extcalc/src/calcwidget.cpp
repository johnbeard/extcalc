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




void CalcWidget::getPref(Preferences newPref)
{
	emit prefChange(newPref);
}


void CalcWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right()-geometry().left();
	int height=geometry().bottom()-geometry().top();

	if(maximized)
	{
		textEdit->setGeometry(20,menuBottom+40,width-40,height-90);
		dockArea->setGeometry(0,menuBottom,width,35);
	}
	else
	{
		textEdit->setGeometry(20,50,width-40,height-290);
		calcButtons->setGeometry(20,height-220,280,200);
		extButtons->setGeometry(320,height-180,300,160);
		dockArea->setGeometry(320,height-220,width-340,30);
	}

} 

void CalcWidget::viewSlot()
{
	if(maximized)
	{
		viewButton->setIconSet(*maximizeIcon);
		calcButtons->show();
		extButtons->show();
		maximized=false;
		resizeEvent(NULL);

	}
	else
	{
		viewButton->setIconSet(*minimizeIcon);
		calcButtons->hide();
		extButtons->hide();
		maximized=true;
		resizeEvent(NULL);
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

