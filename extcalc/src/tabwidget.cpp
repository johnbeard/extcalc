/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         tabwidget.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "tabwidget.h"
#include <QResizeEvent>

TabWidget::TabWidget(QWidget*par,Preferences p,Variable *va,ThreadSync*td,QString desc, bool max) :QWidget(par)
{
	vars=va;
	threadData=td;
	pref=p;
	maximized=false;	
  descriptor=desc;
  toolBar=NULL;
  parent=par;

	mainLayout=new QGridLayout(this);
  buttonLayout=new QGridLayout((QWidget*)NULL);
  maximizeLayout=new QGridLayout((QWidget*)NULL);
	mainLayout->addLayout(maximizeLayout,0,0,1,1);
	subWidgetCount=0;
	dockAreaPos=-1;
	subWidgets=NULL;
	mainWidget=NULL;
	if(max)
		maximizeSlot(max);
	maximizeLayout->setRowStretch(0,0);
	maximizeLayout->setRowStretch(1,1);
  mainLayout->setRowStretch(0,1);
  mainLayout->setRowStretch(1,0);
}


void TabWidget::maximizeSlot(bool maximize)
{
	int c;
	if(maximize)
	{
		for(c=0; c<subWidgetCount; c++)
			subWidgets[c]->hide();
		maximized=true;
		if(dockAreaPos!=-1)
		{
//			buttonLayout->removeWidget(dockArea);
//			maximizeLayout->addWidget(dockArea,0,0,1,1);
		}
	}
	else {

		maximized=false;
		if(dockAreaPos!=-1)
		{
//			maximizeLayout->removeWidget(dockArea);
//			buttonLayout->addWidget(dockArea,0,0,1,1);
		}
		for(c=0; c<subWidgetCount; c++)
			subWidgets[c]->show();
	}
	
}


void TabWidget::setMainWidget(QWidget*mainW)
{
	if(mainWidget!=NULL)
		maximizeLayout->removeWidget(mainWidget);
	mainWidget=mainW;
	maximizeLayout->addWidget(mainW,1,0,1,1);
}

void TabWidget::addSubWidget(QWidget* subW)
{
	subWidgetCount++;	

	mainLayout->removeItem(maximizeLayout);
	mainLayout->addItem(maximizeLayout,0,0,1,subWidgetCount);
	
	subWidgets=(QWidget**)realloc(subWidgets,subWidgetCount*sizeof(QWidget*));
	subWidgets[subWidgetCount-1]=subW;
	mainLayout->addWidget(subW,1,subWidgetCount-1,1,1);
	

	if(maximized)
		subW->hide();
}

void TabWidget::replaceSubWidget(QWidget*newSubW,int pos)
{
	if(pos>=0 && pos<subWidgetCount && newSubW!=subWidgets[pos])
	{
		subWidgets[pos]->hide();
		newSubW->show();
		if(pos==dockAreaPos)
		{
			buttonLayout->removeWidget(subWidgets[pos]);
			buttonLayout->addWidget(newSubW,1,0);
		}
		else {
			mainLayout->removeWidget(subWidgets[pos]);
			mainLayout->addWidget(newSubW,1,pos);
		}
		subWidgets[pos]=newSubW;	
		
	}
}

void TabWidget::removeSubWidget(int pos)
{
	if(pos>=0 && pos < subWidgetCount)
	{
		if(pos==dockAreaPos)
			buttonLayout->removeWidget(subWidgets[pos]);
		else mainLayout->removeWidget(subWidgets[pos]);
		subWidgets[pos]->hide();
	}
	
}

/*void TabWidget::setDockArea(int pos)
{
	if(pos>subWidgetCount-1)
		return;
	
	if(maximized)
	{
		if(dockAreaPos<0)
		{
			mainLayout->removeWidget(subWidgets[pos]);
			mainLayout->addLayout(buttonLayout,1,pos);
			buttonLayout->addWidget(subWidgets[pos],1,0);
		}
		else maximizeLayout->removeWidget(dockArea);

		maximizeLayout->addWidget(dockArea,0,0,1,1);
		dockAreaPos=pos;
		return;
	}
	
	if(dockAreaPos!=pos)
	{
		if(dockAreaPos!=-1)
		{
			buttonLayout->removeWidget(dockArea);
			buttonLayout->removeWidget(subWidgets[dockAreaPos]);
			mainLayout->removeItem(buttonLayout);
			mainLayout->addWidget(subWidgets[dockAreaPos],1,dockAreaPos,1,1);
		}
		else mainLayout->removeItem(buttonLayout);
		
		mainLayout->removeWidget(subWidgets[pos]);
		mainLayout->addLayout(buttonLayout,1,pos);
		buttonLayout->addWidget(dockArea,0,0);
		buttonLayout->addWidget(subWidgets[pos],1,0);
		
		dockAreaPos=pos;
	}

}*/




