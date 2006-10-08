#include "calcpref.h"

void CalcPreferences::saveSlot()
{
	if(angleBox->currentItem() == 0)
		pref.angle=DEG;
	else if(angleBox->currentItem() == 1)
		pref.angle=RAD;
	else if(angleBox->currentItem() == 2)
		pref.angle=GRA;
	
	if(outputBox->currentItem() == 0)
		pref.outputType=FIXEDNUM;
	else if(outputBox->currentItem() == 1)
		pref.outputType=VARIABLENUM;
	else if(outputBox->currentItem() == 2)
		pref.outputType=EXPSYM;
	
	if(calcModeBox->currentItem() == 0)
		pref.calcType=SCIENTIFIC;
	else if(calcModeBox->currentItem() == 1)
		pref.calcType=BASE;
	
	if(baseBox->currentItem() == 0)
		pref.base=HEX;
	else if(baseBox->currentItem() == 1)
		pref.base=DEC;
	else if(baseBox->currentItem() == 2)
		pref.base=OCT;
	else if(baseBox->currentItem() == 3)
		pref.base=BIN;
	
	pref.outputLength=outputLenBox->value();
		
	emit prefChange(pref);
	close();
}


void CalcPreferences::windowActivationChange(bool)
{

	if(!isActiveWindow())
	{
		setActiveWindow();
	}
}




