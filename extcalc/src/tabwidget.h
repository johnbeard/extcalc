/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         tabwidget.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This is the class provides an empty tab subwindow.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef TABWIDGETH
#define TABWIDGETH



#include "buttons.h"
#include <QWidget>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <QGridLayout>



class TabWidget :public QWidget
{


	bool maximized;
	
	QGridLayout *mainLayout,*buttonLayout,*maximizeLayout;
	int subWidgetCount;
	int dockAreaPos;
	QWidget*mainWidget;
	QWidget**subWidgets;
	
	
	Q_OBJECT
			
	protected:
	StandardButtons*calcButtons;
	ExtButtons*extButtons;
	Preferences pref;
	Variable *vars;
	ThreadSync*threadData;
	Q3DockArea*dockArea;
	
	public:
		TabWidget(QWidget*parent,Preferences p,Variable *va,ThreadSync*td, bool max);
	
		virtual void setPref(Preferences newPref)=0;
		bool isMaximized()
		{return maximized;}

	protected:
		void setMainWidget(QWidget*);
		void addSubWidget(QWidget*);
		void replaceSubWidget(QWidget*,int);
		void removeSubWidget(int);
		void setDockArea(int pos);


	public slots:

		virtual void getPref(Preferences newPref)=0;
		void maximizeSlot(bool maximize);
};

 
#endif

