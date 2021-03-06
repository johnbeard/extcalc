/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         functiontable.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "functiontable.h"
//Added by qt3to4:
#include <QKeyEvent>


void FunctionTable::cellChangedSlot(int row,int col)
{
	
	
	Q3ComboTableItem *colorItem=(Q3ComboTableItem*)item(row,1);
	Q3CheckTableItem*activeItem=(Q3CheckTableItem*)item(row,2);
	Q3ComboTableItem *typeItem=(Q3ComboTableItem*)item(row,3);
	Q3CheckTableItem*dynamicItem=(Q3CheckTableItem*)item(row,4);
	Q3CheckTableItem*logicItem=(Q3CheckTableItem*)item(row,5);
		
	pref.activeFunctions[tableFunctionMap[row]]=activeItem->isChecked();
	pref.dynamicFunctions[tableFunctionMap[row]]=dynamicItem->isChecked();
	pref.logicFunctions[tableFunctionMap[row]]=logicItem->isChecked();
	pref.functionColors[tableFunctionMap[row]]=getColor(colorItem->text());

	if(typeItem->currentText() == GRAPHH_STR17)
		pref.functionTypes[tableFunctionMap[row]]=GRAPHPARAMETER;
	else if(typeItem->currentText() == GRAPHH_STR16)
		pref.functionTypes[tableFunctionMap[row]]=GRAPHPOLAR;
	else if(typeItem->currentText() == GRAPHH_STR18)
		pref.functionTypes[tableFunctionMap[row]]=GRAPH3D;
	else if(typeItem->currentText() == GRAPHH_STR21)
		pref.functionTypes[tableFunctionMap[row]]=GRAPHIEL;
	else if(typeItem->currentText() == GRAPHH_STR23)
		pref.functionTypes[tableFunctionMap[row]]=GRAPHIELE;
	else if(typeItem->currentText() == GRAPHH_STR20)
		pref.functionTypes[tableFunctionMap[row]]=GRAPHIEG;
	else if(typeItem->currentText() == GRAPHH_STR22)
		pref.functionTypes[tableFunctionMap[row]]=GRAPHIEGE;
	else if(typeItem->currentText() == "Nyquist Plot")
		pref.functionTypes[tableFunctionMap[row]]=GRAPHCOMPLEX;
	else if(typeItem->currentText() == "3D Nyquist Plot")
		pref.functionTypes[tableFunctionMap[row]]=GRAPHCOMP3D;
	else pref.functionTypes[tableFunctionMap[row]]=GRAPHSTD;
	
	
	
	QString*functionStrings=new QString[20];
	for(int c=0; c<tableFunctionMap.GetLen(); c++)
	{
		if(text(c,0).length() <=0)
			functionStrings[tableFunctionMap[c]]+="";
		else functionStrings[tableFunctionMap[c]]+=text(c,0);
		if(c < tableFunctionMap.GetLen()-1)
			if(tableFunctionMap[c]==tableFunctionMap[c+1])
			{
				if(pref.functionTypes[tableFunctionMap[c]] == GRAPHPARAMETER)
					functionStrings[tableFunctionMap[c]]+="\\";
				else functionStrings[tableFunctionMap[c]]="";
			}
	}
	if(pref.functions != NULL)
		delete[]pref.functions;
	pref.functions=functionStrings;
	
	

	if(col==6)
	{
		if(row>0 && tableFunctionMap[row]==tableFunctionMap[row-1])
			setText(row,col,"");
		else pref.functionComments[tableFunctionMap[row]]=text(row,col);
	}
	
	

	emit(prefChange(pref));
}


void FunctionTable::setPref(Preferences newPref)
{
	
	pref=newPref;
	for(int c=0;c<tableFunctionMap.GetLen()-1;c++)	// insert extra functionTable row when functionType changed
	{												// to GRAPHPARAMETER
		if(pref.functionTypes[tableFunctionMap[c]]==GRAPHPARAMETER &&
				 tableFunctionMap[c]!=tableFunctionMap[c+1])
		{
			if(c>0)
				if(tableFunctionMap[c]==tableFunctionMap[c-1])
					continue;
			insertRows(c,1);
			setItem(c,2,new Q3CheckTableItem(this,""));
			setItem(c,4,new Q3CheckTableItem(this,""));
			setItem(c,5,new Q3CheckTableItem(this,""));
			setItem(c,1,new Q3ComboTableItem(this,colorList));
			setItem(c,3,new Q3ComboTableItem(this,graphTypeList));
			verticalHeader()->setLabel(c,"x"+QString::number(tableFunctionMap[c]+1)+"(T)");
			verticalHeader()->setLabel(c+1,"y"+QString::number(tableFunctionMap[c]+1)+"(T)");
			setRowHeight(c,25);
			tableFunctionMap.NewItem(0);
			for(int c1=tableFunctionMap.GetLen()-1; c1>c; c1--)
				tableFunctionMap[c1]=tableFunctionMap[c1-1];
			tableFunctionMap[c]=tableFunctionMap[c+1];
		}
		else if(pref.functionTypes[tableFunctionMap[c]]==GRAPHPOLAR)
			(verticalHeader())->setLabel(c,"r"+QString::number(tableFunctionMap[c]+1)+"(x)");
		else if(pref.functionTypes[tableFunctionMap[c]]==GRAPH3D)
			(verticalHeader())->setLabel(c,"y"+QString::number(tableFunctionMap[c]+1)+"(x,z)");
		else if(pref.functionTypes[tableFunctionMap[c]]==GRAPHSTD)
			(verticalHeader())->setLabel(c,"y"+QString::number(tableFunctionMap[c]+1)+"(x)");
		else if(pref.functionTypes[tableFunctionMap[c]]==GRAPHSTD)
			(verticalHeader())->setLabel(c,"y"+QString::number(tableFunctionMap[c]+1)+"(x)");
		else if(pref.functionTypes[tableFunctionMap[c]]==GRAPHCOMPLEX || pref.functionTypes[tableFunctionMap[c]]==GRAPHCOMP3D)
			(verticalHeader())->setLabel(c,"F"+QString::number(tableFunctionMap[c]+1)+"(Z)");
		
	}
	for(int c=0;c<tableFunctionMap.GetLen(); c++)
	{
		if(c<tableFunctionMap.GetLen()-1)	//remove second functionTable row when functionType
		{									//changes from GRAPHPARAMETER to any other
			if(tableFunctionMap[c]==tableFunctionMap[c+1]
						&& pref.functionTypes[tableFunctionMap[c]] != GRAPHPARAMETER)
			{
				removeRow(c);
				tableFunctionMap.DeleteItem(c);
			}
		}
		Q3ComboTableItem *typeItem=(Q3ComboTableItem*)item(c,3);
		if(typeItem!=NULL)
		{
			switch(pref.functionTypes[tableFunctionMap[c]])
			{
				case GRAPHSTD:
					typeItem->setCurrentItem(GRAPHH_STR15);
					break;
				case GRAPHPOLAR:
					typeItem->setCurrentItem(GRAPHH_STR16);
					break;
				case GRAPHPARAMETER:
					typeItem->setCurrentItem(GRAPHH_STR17);
					break;
				case GRAPH3D:
					typeItem->setCurrentItem(GRAPHH_STR18);
					break;
				case GRAPHIEL:
					typeItem->setCurrentItem(GRAPHH_STR21);
					break;
				case GRAPHIELE:
					typeItem->setCurrentItem(GRAPHH_STR23);
					break;
				case GRAPHIEG:
					typeItem->setCurrentItem(GRAPHH_STR20);
					break;
				case GRAPHIEGE:
					typeItem->setCurrentItem(GRAPHH_STR22);
					break;
				case GRAPHCOMPLEX:
					typeItem->setCurrentItem("Nyquist Plot");
					break;
				case GRAPHCOMP3D:
					typeItem->setCurrentItem("3D Nyquist Plot");
					break;
			}
		}
	}
	if(pref.functions!=NULL)
	{
		int tableIndex=0;
		for(int c=0; c<20;c++)
		{
			if(tableIndex < tableFunctionMap.GetLen()-1)
			{
				if(tableFunctionMap[tableIndex] == tableFunctionMap[tableIndex+1])
				{
					QString func1,func2;
					int sep=pref.functions[c].find("\\");
					if(sep<0)
					{
						func1=pref.functions[c];
						func2="";
					}
					else {
						func1=pref.functions[c].left(sep);
						func2=pref.functions[c].right(pref.functions[c].length()-1-sep);
					}
					setText(tableIndex,0,func1);
					setText(tableIndex+1,0,func2);
					tableIndex+=2;
				}
				else {
					setText(tableIndex,0,pref.functions[c]);
					tableIndex++;
				}
			}
			else {
				setText(tableIndex,0,pref.functions[c]);
				tableIndex++;
			}
		}
	}
	if(pref.activeFunctions!=NULL)
		for(int c=0; c<tableFunctionMap.GetLen();c++)
	{
		Q3CheckTableItem *checkItem=(Q3CheckTableItem*)item(c,2);
		if(checkItem!=NULL)
			checkItem->setChecked(pref.activeFunctions[tableFunctionMap[c]]);
		checkItem=(Q3CheckTableItem*)item(c,4);
		if(checkItem!=NULL)
			checkItem->setChecked(pref.dynamicFunctions[tableFunctionMap[c]]);
		checkItem=(Q3CheckTableItem*)item(c,5);
		if(checkItem!=NULL)
			checkItem->setChecked(pref.logicFunctions[tableFunctionMap[c]]);
	}
	for(int c=0;c<tableFunctionMap.GetLen(); c++)
	{
		Q3ComboTableItem *colorItem=(Q3ComboTableItem*)item(c,1);
		if(colorItem!=NULL)
		{
			colorItem->setCurrentItem(getColorName(pref.functionColors[tableFunctionMap[c]]));
			changeColor(c,pref.functionColors[tableFunctionMap[c]]);
		}
	}
	if(pref.functionComments!=NULL)
	{
		for(int c=0;c<tableFunctionMap.GetLen(); c++)
		{
			if(c==0 || tableFunctionMap[c-1] != tableFunctionMap[c])
				setText(c,6,pref.functionComments[tableFunctionMap[c]]);
	
		}
	}


	repaint();
//	resizeEvent(NULL);
//	adjustColumn(0);
//	adjustColumn(1);
//	adjustColumn(2);
	adjustColumn(6);
}


void FunctionTable::editStartedSlot(int row,int col)
{
	if(col==0)
		emit textEditStarted(text(row,0));
}

void FunctionTable::keyPressEvent(QKeyEvent*e)
{
	if(currentColumn()==0)
		emit textEditStarted(e->text());
}


void FunctionTable::setFunctionText(QString newText,int row)
{
	if(row==-1 || row>=numRows())
		row=currentRow();
	if(newText.length()>0)
		pref.activeFunctions[tableFunctionMap[row]]=true;
	else pref.activeFunctions[tableFunctionMap[row]]=false;
	if(pref.functionTypes[tableFunctionMap[row]]==GRAPHPARAMETER)
	{
		if(row>0)
		{
			if(tableFunctionMap[row]==tableFunctionMap[row-1])
				pref.functions[tableFunctionMap[row]]=text(row-1,0)+"\\"+newText;
			else pref.functions[tableFunctionMap[row]]=newText+"\\"+text(row+1,0);
		}
		else pref.functions[tableFunctionMap[row]]=newText+"\\"+text(row+1,0);
	}
	else pref.functions[tableFunctionMap[row]]=newText;
	emit prefChange(pref);
}
