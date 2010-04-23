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
#include <QToolBar>
#include <qicon.h>
#include <qtooltip.h>
//Added by qt3to4:
#include <QPixmap>
#include <QResizeEvent>
#include "tabwidget.h"



class CalcWidget :public TabWidget
{
	CalcInput*textEdit;

	int menuBottom;	

	QComboBox *angleBox,*baseBox,*typeBox;
	Catalog *catalog,*constants;
  QAction*maximizeAction,*catalogAction,*constantsAction;
  StandardButtons*calcButtons;
  ExtButtons*extButtons;

	Q_OBJECT

	public:
  CalcWidget(QWidget*parent,Preferences p,Variable *va,ThreadSync*td,StandardButtons*cB,ExtButtons*eB);
	
	void setPref(Preferences newPref);

  private:
  void updateUI();

public slots:

	void getPref(Preferences newPref);
  void viewSlot(bool);
	void baseSlot(int);
	void angleSlot(int);
	void typeSlot(int);
	void editSlot(int);
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

