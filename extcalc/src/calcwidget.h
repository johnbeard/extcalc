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

#include <QWidget>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <qicon.h>
#include <q3popupmenu.h>
#include <qtooltip.h>
//Added by qt3to4:
#include <QPixmap>
#include <QResizeEvent>
#include "tabwidget.h"



class CalcWidget :public TabWidget
{
	CalcInput*textEdit;
//	StandardButtons*calcButtons;
//	ExtButtons*extButtons;
//	Preferences pref;
	int menuBottom;

//	bool maximized;
//	Variable *vars;
//	ThreadSync*threadData;
	
	Q3ToolBar*toolBar;
//	Q3DockArea*dockArea;
	QComboBox *angleBox,*baseBox,*typeBox;
	QPixmap *minimizeIcon,*angleIcon,*maximizeIcon,*scientificIcon,*baseIcon,*catalogIcon;
	Catalog *catalog,*constants;
	QPushButton* catalogButton,*viewButton,*constantsButton;

	Q_OBJECT

//	QLabel *text1,*text2,*text3;
//	QLabel *num1,*num2,*num3,*num4;




	public:
	CalcWidget(QWidget*parent,Preferences p,Variable *va,ThreadSync*td);
	
	void setPref(Preferences newPref);

	

protected:
	
//	virtual void resizeEvent(QResizeEvent*);

	
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

