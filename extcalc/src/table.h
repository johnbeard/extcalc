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
#include <QToolBar>
#include <qicon.h>
#include <qtooltip.h>
#include <qsplitter.h>
//Added by qt3to4:
#include <QPixmap>
#include <QAction>
#include <QResizeEvent>
#include <Q3ValueList>
#include "functiontable.h"
#include "buttons.h"
#include "catalog.h"
#include "tabwidget.h"





class TableWidget :public TabWidget
{
  ExtButtons *extButtons;
  StandardButtons *calcButtons;
	FunctionTable* functionTable;
	QLineEdit*inputLine;
	CalcTable*outputTable;
  QAction *calculateAction,*maximizeAction,*catalogAction;
	QPixmap *minimizeIcon,*maximizeIcon,*catalogIcon;
	QComboBox*typeBox;
	Catalog *catalog;
	QSplitter *horzSplit,*vertSplit;
	List <double>vertValues;
	List <double>horzValues;
	Q3Header*horzHeader,*vertHeader;
	
	Q_OBJECT
public:
  TableWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td,StandardButtons*cB,ExtButtons*eB);
	
	void setPref(Preferences);

  private:

  void updateUI();
	
public slots:
	void getPref(Preferences);
	void selectionChangedSlot(int row,int col);
	void tableEditSlot(QString);
	void inputTextChanged();
	void calculateButtonSlot();
	void typeBoxSlot(const QString&);
  void viewSlot(bool);
  void processText(QString);
	void editSlot(int);
	void horzHeaderSlot(int);
	void vertHeaderSlot(int);
	void tableMenuSlot(int);
	void dockWindowSlot();
	
//protected:
//	virtual void resizeEvent(QResizeEvent*);
	
	
signals:
	void prefChange(Preferences);
	
};






#endif






