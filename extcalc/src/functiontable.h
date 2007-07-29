/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         functiontable.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This class manages the functions for graph drawing and function tables.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <calctable.h>
#include "list.h"


class FunctionTable :public CalcTable
{
	
	
	Preferences pref;
	List<int>tableFunctionMap;
	QStringList colorList,graphTypeList;
	
	Q_OBJECT
	
public:
	FunctionTable(QWidget*parent,Preferences p) :CalcTable(parent,0,false)
	{
		pref=p;
		
	
		QStringList rowLabels;
		for(int c=0; c<20; c++)
		{
			if(pref.functionTypes[c]==GRAPHPOLAR)
			{
				rowLabels+="r"+QString::number(c+1)+"(x):";
				tableFunctionMap.NewItem(c);
			}
			else if(pref.functionTypes[c]==GRAPH3D)
			{
				rowLabels+="y"+QString::number(c+1)+"(x,z):";
				tableFunctionMap.NewItem(c);
			}
			else if(pref.functionTypes[c]==GRAPHPARAMETER)
			{
				rowLabels+="x"+QString::number(c+1)+"(T)";
				rowLabels+="y"+QString::number(c+1)+"(T)";
				tableFunctionMap.NewItem(c);
				tableFunctionMap.NewItem(c);
			}
			else {
				rowLabels+="y"+QString::number(c+1)+"(x):";
				tableFunctionMap.NewItem(c);
			}
		}
		
		setNumRows(tableFunctionMap.GetLen());
		setNumCols(5);
		
		setRowLabels(rowLabels);
		
		QStringList colLabels(GRAPHH_STR12);
		colLabels +=GRAPHH_STR13;
		colLabels +=GRAPHH_STR14;
		colLabels +=GRAPHH_STR24;
		colLabels +="dynamic";
		setColumnLabels(colLabels);

		for(int c=0; c<tableFunctionMap.GetLen(); c++)
			setItem(c,2,new QCheckTableItem(this,""));
		
		colorList+=GRAPHH_COL1;
		colorList+=GRAPHH_COL2;
		colorList+=GRAPHH_COL3;
		colorList+=GRAPHH_COL4;
		colorList+=GRAPHH_COL5;
		colorList+=GRAPHH_COL6;
		colorList+=GRAPHH_COL7;
		colorList+=GRAPHH_COL8;
		colorList+=GRAPHH_COL9;
		colorList+=GRAPHH_COL10;
		colorList+=GRAPHH_COL11;
		
		for(int c=0; c<tableFunctionMap.GetLen(); c++)
			setItem(c,1,new QComboTableItem(this,colorList));
		
		graphTypeList+=GRAPHH_STR15;
		graphTypeList+=GRAPHH_STR16;
		graphTypeList+=GRAPHH_STR17;
		graphTypeList+=GRAPHH_STR18;
		graphTypeList+=GRAPHH_STR20;
		graphTypeList+=GRAPHH_STR21;
		graphTypeList+=GRAPHH_STR22;
		graphTypeList+=GRAPHH_STR23;
		graphTypeList+="Nyquist Plot";
		graphTypeList+="3D Nyquist Plot";
		for(int c=0; c<tableFunctionMap.GetLen(); c++)
			setItem(c,3,new QComboTableItem(this,graphTypeList));
			

		for(int c=0; c<tableFunctionMap.GetLen(); c++)
			setItem(c,4,new QCheckTableItem(this,""));


		for(int c=0; c<tableFunctionMap.GetLen(); c++)
			setRowHeight(c,25);
		QObject::connect(this,SIGNAL(valueChanged(int,int)),this,SLOT(cellChangedSlot(int,int)));
		QObject::connect(this,SIGNAL(cellEditStarted(int,int)),this,SLOT(editStartedSlot(int,int)));
	
	}
	
	
	void setPref(Preferences newPref);
	void setFunctionText(QString newText,int row=-1);
	
protected:
	virtual void keyPressEvent(QKeyEvent*);

	
public slots:
	void cellChangedSlot(int row,int col);
	void editStartedSlot(int row,int col);

	
	
	
	
signals:
	void prefChange(Preferences);
	void textEditStarted(QString);
	
	
	
};










#endif



