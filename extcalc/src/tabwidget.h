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
#include <QGridLayout>
#include <QToolBar>



class TabWidget :public QWidget
{



	QGridLayout *mainLayout,*buttonLayout,*maximizeLayout;
	int subWidgetCount;
	int dockAreaPos;
	QWidget*mainWidget;
	QWidget**subWidgets;
  QString descriptor;
	bool maximized;
	
	
	Q_OBJECT
			
	protected:
	Preferences pref;
	Variable *vars;
  ThreadSync*threadData;
  QToolBar *toolBar;
  QWidget *parent;
	
	public:
    TabWidget(QWidget*par,Preferences p,Variable *va,ThreadSync*td,QString desc, bool max);
	
		virtual void setPref(Preferences newPref)=0;
		bool isMaximized()
		{return maximized;}

    QString getDescriptor()
    {return descriptor;}

    virtual QToolBar*getToolBar()
    {
      return toolBar;
    }

	protected:
		void setMainWidget(QWidget*);
		void addSubWidget(QWidget*);
		void replaceSubWidget(QWidget*,int);
		void removeSubWidget(int);


	public slots:

		virtual void getPref(Preferences newPref)=0;
		void maximizeSlot(bool maximize);


};

 
#endif

