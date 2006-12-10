#include "functiontable.h"


void FunctionTable::cellChangedSlot(int row,int)
{
	
	
	QComboTableItem *colorItem=(QComboTableItem*)item(row,1);
	QCheckTableItem*activeItem=(QCheckTableItem*)item(row,2);
	QComboTableItem *typeItem=(QComboTableItem*)item(row,3);
	QCheckTableItem*dynamicItem=(QCheckTableItem*)item(row,4);
		
	pref.activeFunctions[tableFunctionMap[row]]=activeItem->isChecked();
	pref.dynamicFunctions[tableFunctionMap[row]]=dynamicItem->isChecked();
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
			setItem(c,2,new QCheckTableItem(this,""));
			setItem(c,4,new QCheckTableItem(this,""));
			setItem(c,1,new QComboTableItem(this,colorList));
			setItem(c,3,new QComboTableItem(this,graphTypeList));
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
		QComboTableItem *typeItem=(QComboTableItem*)item(c,3);
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
		QCheckTableItem *checkItem=(QCheckTableItem*)item(c,2);
		if(checkItem!=NULL)
			checkItem->setChecked(pref.activeFunctions[tableFunctionMap[c]]);
		checkItem=(QCheckTableItem*)item(c,4);
		if(checkItem!=NULL)
			checkItem->setChecked(pref.dynamicFunctions[tableFunctionMap[c]]);
	}
	for(int c=0;c<tableFunctionMap.GetLen(); c++)
	{
		QComboTableItem *colorItem=(QComboTableItem*)item(c,1);
		if(colorItem!=NULL)
		{
			colorItem->setCurrentItem(getColorName(pref.functionColors[tableFunctionMap[c]]));
			changeColor(c,pref.functionColors[tableFunctionMap[c]]);
		}
	}


	repaint();
//	resizeEvent(NULL);
	adjustColumn(0);
	adjustColumn(1);
	adjustColumn(2);
	adjustColumn(3);	
	
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
