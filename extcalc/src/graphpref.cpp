#include "graphpref.h"



int CoordinatePreferences::savePref()
{
	pref.xmin=runCalc(xmin->text(),&pref,vars);
	pref.xmax=runCalc(xmax->text(),&pref,vars);
	pref.ymin=runCalc(ymin->text(),&pref,vars);
	pref.ymax=runCalc(ymax->text(),&pref,vars);
	pref.zmin=runCalc(zmin->text(),&pref,vars);
	pref.zmax=runCalc(zmax->text(),&pref,vars);
	pref.radiusMax=runCalc(radius->text(),&pref,vars);
	pref.angleMax=runCalc(angle->text(),&pref,vars);
	pref.rasterSizeX=runCalc(rasterSizeX->text(),&pref,vars);
	pref.rasterSizeY=runCalc(rasterSizeY->text(),&pref,vars);
	pref.rasterSizeZ=runCalc(rasterSizeZ->text(),&pref,vars);
	pref.rasterSizeRadius=runCalc(rasterSizeRadius->text(),&pref,vars);
	pref.rasterSizeAngle=runCalc(rasterSizeAngle->text(),&pref,vars);
	pref.axis=axis->isChecked();
	pref.raster=raster->isChecked();
	pref.label=label->isChecked();
	pref.autosize=autosize->isChecked();
	
	if(pref.xmax <= pref.xmin)
	{
		MessageBox(GRAPHPREFC_STR1);
		return -1;
	}
	else if(pref.ymax <= pref.ymin)
	{
		MessageBox(GRAPHPREFC_STR2);
		return -1;
	}
	else if(pref.zmax <= pref.zmin)
	{
		MessageBox(GRAPHPREFC_STR13);
		return -1;
	}	
	else if(pref.angleMax <=0.0)
	{
		MessageBox(GRAPHPREFC_STR7);
		return -1;
	}
	else if(pref.radiusMax <=0.0)
	{
		MessageBox(GRAPHPREFC_STR8);
		return -1;
	}
	else if(pref.rasterSizeX <= 0.0)
	{
		MessageBox(GRAPHPREFC_STR3);	
		return -1;
	}
	else if(pref.rasterSizeY <= 0.0)
	{
		MessageBox(GRAPHPREFC_STR4);	
		return -1;
	}
	else if(pref.rasterSizeZ <= 0.0)
	{
		MessageBox(GRAPHPREFC_STR12);	
		return -1;
	}
	else if(pref.rasterSizeAngle <=0.0)
	{
		MessageBox(GRAPHPREFC_STR9+rasterSizeAngle->text());
		return -1;
	}
	else if(pref.rasterSizeRadius <=0.0)
	{
		MessageBox(GRAPHPREFC_STR10);
		return -1;
	}
	emit prefChange(pref);
	return 0;
}


void CoordinatePreferences::stdButtonSlot()
{
	xmin->setText("-10");
	xmax->setText("10");
	ymin->setText("-10");
	ymax->setText("10");
	zmin->setText("-10");
	zmax->setText("10");
	rasterSizeX->setText("1");
	rasterSizeY->setText("1");
	rasterSizeZ->setText("1");
	if(pref.angle==DEG)
	{
		angle->setText("360");
		radius->setText("10");
		rasterSizeAngle->setText("15");
		rasterSizeRadius->setText("2");
	}
	else if(pref.angle==RAD)
	{
		angle->setText("6.28318");
		radius->setText("10");
		rasterSizeAngle->setText("0.314159");
		rasterSizeRadius->setText("2");
	}
	else if(pref.angle==GRA)
	{
		angle->setText("400");
		radius->setText("10");
		rasterSizeAngle->setText("20");
		rasterSizeRadius->setText("2");
	}
}

void CoordinatePreferences::angleButtonSlot()
{
	if(pref.angle==DEG)
	{
		xmin->setText("-360");
		xmax->setText("360");
		zmin->setText("-360");
		zmax->setText("360");
		ymin->setText("-2");
		ymax->setText("2");
		rasterSizeX->setText("90");
		rasterSizeZ->setText("90");
		rasterSizeY->setText("0.5");
		angle->setText("360");
		radius->setText("10");
		rasterSizeAngle->setText("15");
		rasterSizeRadius->setText("2");
	}
	else if(pref.angle==RAD)
	{
		xmin->setText("-6.28318");
		xmax->setText("6.28318");
		ymin->setText("-2");
		ymax->setText("2");
		zmin->setText("-6.28318");
		zmax->setText("6.28318");
		rasterSizeX->setText("1.5708");
		rasterSizeY->setText("0.5");
		rasterSizeZ->setText("1.5708");
		angle->setText("6.28318");
		radius->setText("10");
		rasterSizeAngle->setText("0.314159");
		rasterSizeRadius->setText("2");
	}
	else if(pref.angle==GRA)
	{
		xmin->setText("-400");
		xmax->setText("400");
		ymin->setText("-2");
		ymax->setText("2");
		zmin->setText("-400");
		zmax->setText("400");
		rasterSizeX->setText("100");
		rasterSizeY->setText("0.5");
		rasterSizeZ->setText("100");
		angle->setText("400");
		radius->setText("10");
		rasterSizeAngle->setText("20");
		rasterSizeRadius->setText("2");
	}
}



void CoordinatePreferences::graphTypeSlot(int)
{
	QString string=graphType->currentText();
	if(string==GRAPHPREFH_STR16)		//polar
	{
		xmin->setEnabled(false);
		xmax->setEnabled(false);
		ymin->setEnabled(false);
		ymax->setEnabled(false);
		zmin->setEnabled(false);
		zmax->setEnabled(false);
		rasterSizeX->setEnabled(false);
		rasterSizeY->setEnabled(false);
		rasterSizeZ->setEnabled(false);
		
		radius->setEnabled(true);
		angle->setEnabled(true);
		rasterSizeRadius->setEnabled(true);
		rasterSizeAngle->setEnabled(true);
		pref.graphType=GRAPHPOLAR;
	}
	else if(string==GRAPHPREFH_STR17)	//3D
	{
		xmin->setEnabled(true);
		xmax->setEnabled(true);
		ymin->setEnabled(true);
		ymax->setEnabled(true);
		zmin->setEnabled(true);
		zmax->setEnabled(true);
		rasterSizeX->setEnabled(true);
		rasterSizeY->setEnabled(true);
		rasterSizeZ->setEnabled(true);
		
		radius->setEnabled(false);
		angle->setEnabled(false);
		rasterSizeRadius->setEnabled(false);
		rasterSizeAngle->setEnabled(false);

		pref.graphType=GRAPH3D;

	}
	else{
		xmin->setEnabled(true);
		xmax->setEnabled(true);
		ymin->setEnabled(true);
		ymax->setEnabled(true);
		zmin->setEnabled(false);
		zmax->setEnabled(false);
		rasterSizeX->setEnabled(true);
		rasterSizeY->setEnabled(true);
		rasterSizeZ->setEnabled(false);
		
		radius->setEnabled(false);
		angle->setEnabled(false);
		rasterSizeRadius->setEnabled(false);
		rasterSizeAngle->setEnabled(false);
		
		pref.graphType=GRAPHSTD;
	}
}

void CoordinatePreferences::getPref(Preferences pr)
{
	pref=pr;
}



void DynamicPreferences::standardButtonSlot()
{
	parameterStart->setText("0");
	parameterEnd->setText("10");
	
	if(logNyquistBox->isChecked())
	{
		nyquistStart->setText("-3");
		nyquistEnd->setText("3");		
	}
	else {
		nyquistStart->setText("0");
		nyquistEnd->setText("100");
	}
	
	dynamicSteps->setText("10");
	dynamicStart->setText("1");
	dynamicEnd->setText("10");
	time->setText("10");
	
}

void DynamicPreferences::getPref(Preferences pr)
{
	pref=pr;
}

int PerformancePreferences::savePref()
{
	pref.prec2dSteps=steps2d->value();
	pref.prec3dSteps=steps3d->value();
	pref.parameterSteps=stepsParam->value();
	pref.nyquistSteps=stepsNyquist->value();
	pref.show3dGrid=polygon3dBox->isChecked();
	
	if(solvePrecisionBox->currentText()==GRAPHPREFH_STR40)
		pref.solvePrec=0;
	else if(solvePrecisionBox->currentText()==GRAPHPREFH_STR42)
		pref.solvePrec=2;
	else pref.solvePrec=1;
	
	emit prefChange(pref);
	return 0;
}

void PerformancePreferences::lowButtonSlot()
{
	steps2d->setValue(100);
	steps3d->setValue(30);
	stepsParam->setValue(100);
	stepsNyquist->setValue(100);
	solvePrecisionBox->setCurrentText(GRAPHPREFH_STR40);
	polygon3dBox->setChecked(true);
}

void PerformancePreferences::standardButtonSlot()
{
	steps2d->setValue(400);
	steps3d->setValue(50);
	stepsParam->setValue(400);
	stepsNyquist->setValue(400);
	solvePrecisionBox->setCurrentText(GRAPHPREFH_STR41);
	polygon3dBox->setChecked(true);
}

void PerformancePreferences::highButtonSlot()
{
	steps2d->setValue(1000);
	steps3d->setValue(80);
	stepsParam->setValue(1000);
	stepsNyquist->setValue(1000);
	solvePrecisionBox->setCurrentText(GRAPHPREFH_STR42);
	polygon3dBox->setChecked(true);
}

void PerformancePreferences::getPref(Preferences pr)
{
	pref=pr;
}

int DynamicPreferences::savePref()
{
	pref.dynamicStart=runCalc(dynamicStart->text(),&pref,vars);
	pref.dynamicEnd=runCalc(dynamicEnd->text(),&pref,vars);
	pref.dynamicSteps=dynamicSteps->text().toInt();
	if(singleStepBox->isChecked())
		pref.dynamicDelay=time->text().toInt();
	else pref.dynamicDelay=0;
	
	if(pref.dynamicEnd <=pref.dynamicStart)
	{
		MessageBox(GRAPHPREFC_STR15);
		return -1;
	}
	else if(pref.dynamicSteps <=0)
	{
		MessageBox(GRAPHPREFC_STR14);
		return -1;
	}
	else if(pref.dynamicDelay <=0 && singleStepBox->isChecked())
	{
		MessageBox(GRAPHPREFC_STR16);
		return -1;
	}
	
	pref.parameterStart=runCalc(parameterStart->text(),&pref,vars);
	pref.parameterEnd=runCalc(parameterEnd->text(),&pref,vars);

	if(pref.parameterStart>=pref.parameterEnd)
	{
		MessageBox(GRAPHPREFC_STR11);
		return -1;
	}

	
	pref.nyquistStart=runCalc(nyquistStart->text(),&pref,vars);
	pref.nyquistEnd=runCalc(nyquistEnd->text(),&pref,vars);

	if(pref.nyquistStart>=pref.nyquistEnd)
	{
		MessageBox(GRAPHPREFC_STR11);
		return -1;
	}

	pref.logNyquistSteps=logNyquistBox->isChecked();
	
	if(upButton->isChecked())
		pref.moveUpDown=false;
	else pref.moveUpDown=true;
	
	emit prefChange(pref);
	return 0;

}

void GraphPreferences::saveButtonSlot()
{
	if(coordinateWidget->savePref() >=0)
//		if(parameterWidget->savePref()>=0)
			if(dynamicWidget->savePref()>=0)
				if(performanceWidget->savePref()>=0)
					close();
}

void GraphPreferences::windowActivationChange(bool)
{

	if(!isActiveWindow())
	{
		setActiveWindow();
	}
}


