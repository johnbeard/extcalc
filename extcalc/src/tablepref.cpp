#include "tablepref.h"



void TablePreferences::saveSlot()
{
	if(typeBox->currentText()==TABLEH_STR4)
		pref.tableType=TABLEPOLAR;
	else if(typeBox->currentText()==TABLEH_STR5)
		pref.tableType=TABLEPARAMETER;
	else if(typeBox->currentText()==TABLEH_STR6)
		pref.tableType=TABLEINEQUAITY;
	else if(typeBox->currentText()==TABLEH_STR7)
		pref.tableType=TABLE3D;
	else pref.tableType=TABLENORMAL;
	
	pref.tableXStart=xStart->text().toDouble();
	pref.tableXEnd=xEnd->text().toDouble();
	pref.tableZStart=zStart->text().toDouble();
	pref.tableZEnd=zEnd->text().toDouble();
	pref.tableXSteps=xStep->text().toInt();
	pref.tableZSteps=zStep->text().toInt();
	
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



