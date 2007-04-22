#include "tablepref.h"



void TablePreferences::saveSlot()
{
	Variable*vars=new Variable[27];
	if(typeBox->currentText()==TABLEH_STR4)
		pref.tableType=TABLEPOLAR;
	else if(typeBox->currentText()==TABLEH_STR5)
		pref.tableType=TABLEPARAMETER;
	else if(typeBox->currentText()==TABLEH_STR6)
		pref.tableType=TABLEINEQUAITY;
	else if(typeBox->currentText()==TABLEH_STR7)
		pref.tableType=TABLE3D;
	else if(typeBox->currentText()==TABLEH_STR9)
		pref.tableType=TABLECOMPLEX;
	else pref.tableType=TABLENORMAL;
	
	pref.tableXStart=runCalc(xStart->text(),&pref,vars);
	pref.tableXEnd=runCalc(xEnd->text(),&pref,vars);
	pref.tableZStart=runCalc(zStart->text(),&pref,vars);
	pref.tableZEnd=runCalc(zEnd->text(),&pref,vars);
	pref.tableAValue=runCalc(aValue->text(),&pref,vars);
	pref.tableXSteps=xStep->value();
	pref.tableZSteps=zStep->value();
	
	if(pref.tableXStart==NAN)
		MessageBox(TABLEPREFC_STR1);
	else if(pref.tableXEnd==NAN)
		MessageBox(TABLEPREFC_STR2);
	else if(pref.tableZStart==NAN)
		MessageBox(TABLEPREFC_STR3);
	else if(pref.tableZEnd==NAN)
		MessageBox(TABLEPREFC_STR4);
	else if(pref.tableXEnd<=pref.tableXStart)
		MessageBox(TABLEPREFC_STR5);
	else if(pref.tableZEnd<=pref.tableZStart)
		MessageBox(TABLEPREFC_STR6);
	else if(pref.tableXSteps<1)
		MessageBox(TABLEPREFC_STR7);
	else if(pref.tableZSteps<1)
		MessageBox(TABLEPREFC_STR8);
	else {
		emit prefChange(pref);
		close();
	}
}


void TablePreferences::windowActivationChange(bool)
{
	if(!isActiveWindow())
	{
		setActiveWindow();
	}
}



