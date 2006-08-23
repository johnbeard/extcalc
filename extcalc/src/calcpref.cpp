#include "calcpref.h"

void CalcPreferences::saveSlot()
{
	if(angleBox->currentText() == "DEG")
		pref.angle=DEG;
	else if(angleBox->currentText() == "RAD")
		pref.angle=RAD;
	else if(angleBox->currentText() == "GRA")
		pref.angle=GRA;
	
	if(outputBox->currentText() == "Fixed Number of Digits")
		pref.outputType=FIXEDNUM;
	else if(outputBox->currentText() == "Variable Number of Digits")
		pref.outputType=VARIABLENUM;
	else if(outputBox->currentText() == "With Symbols")
		pref.outputType=EXPSYM;
	
	if(calcModeBox->currentText() == "Scientific")
		pref.calcType=SCIENTIFIC;
	else if(calcModeBox->currentText() == "Base")
		pref.calcType=BASE;
	
	if(baseBox->currentText() == "hex")
		pref.base=HEX;
	else if(baseBox->currentText() == "dec")
		pref.base=DEC;
	else if(baseBox->currentText() == "oct")
		pref.base=OCT;
	else if(baseBox->currentText() == "bin")
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




