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






void CalcWidget::getPref(Preferences newPref)
{
	emit prefChange(newPref);
}

void CalcWidget::maximizeSlot()
{
	if(maximized)
	{
		maximized=false;
		calcButtons->show();
		extButtons->show();
		maximizeButton->setText(CALCWIDGETC_STR1);
		resizeEvent(NULL);
	}
	else {
		calcButtons->hide();
		extButtons->hide();
		maximizeButton->setText(CALCWIDGETC_STR2);
		maximized=true;
		resizeEvent(NULL);

	}
	
	
	
}




void CalcWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right()-geometry().left();
	int height=geometry().bottom()-geometry().top();

	if(maximized)
	{
		textEdit->setGeometry(20,50,width-50,height-100);
		maximizeButton->setGeometry(10,height-45,90,35);
		baseButton->setGeometry(110,height-45,90,35);
		prefBox->setGeometry(210,height-45,90,35);
		
	}
	else {
		textEdit->setGeometry(20,50,width-40,height-290);
		calcButtons->setGeometry(20,height-220,280,200);
		extButtons->setGeometry(320,height-180,300,160);
		maximizeButton->setGeometry(325,height-220,90,35);
		baseButton->setGeometry(425,height-220,90,35);
		prefBox->setGeometry(525,height-220,90,35);
	}

} 

void CalcWidget::baseSlot()
{
	if(pref.calcType == SCIENTIFIC)
		pref.calcType=BASE;
	else pref.calcType=SCIENTIFIC;
	
	emit(prefChange(pref));
}



void CalcWidget::prefBoxSlot(int)
{
	QString newText=prefBox->currentText();
	if(pref.calcType==SCIENTIFIC)
	{
		if(newText=="DEG")
			pref.angle=DEG;
		else if(newText=="GRA")
			pref.angle=GRA;
		else pref.angle=RAD;
	}
	else {
		if(newText=="BIN")
			pref.base=BIN;
		else if(newText=="OCT")
			pref.base=OCT;
		else if(newText=="HEX")
			pref.base=HEX;
		else pref.base=DEC;
	}
	emit prefChange(pref);
	
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
