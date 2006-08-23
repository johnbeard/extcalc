#include "graphpref.h"



int CoordinatePreferences::savePref()
{
	pref.xmin=(xmin->text()).toDouble();
	pref.xmax=(xmax->text()).toDouble();
	pref.ymin=(ymin->text()).toDouble();
	pref.ymax=(ymax->text()).toDouble();
	pref.zmin=(zmin->text()).toDouble();
	pref.zmax=(zmax->text()).toDouble();
	pref.radiusMax=(radius->text()).toDouble();
	pref.angleMax=(angle->text()).toDouble();
	pref.rasterSizeX=(rasterSizeX->text()).toDouble();
	pref.rasterSizeY=(rasterSizeY->text()).toDouble();
	pref.rasterSizeZ=(rasterSizeZ->text()).toDouble();
	pref.rasterSizeRadius=(rasterSizeRadius->text()).toDouble();
	pref.rasterSizeAngle=(rasterSizeAngle->text()).toDouble();
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
		MessageBox(GRAPHPREFC_STR9);
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



void ParameterPreferences::getPref(Preferences pr)
{
	pref=pr;
}


int ParameterPreferences::savePref()
{
	pref.parameterStart=(parameterStart->text()).toDouble();
	pref.parameterEnd=(parameterEnd->text()).toDouble();
	pref.parameterSteps=(parameterSteps->text()).toInt();


	if(pref.parameterStart>=pref.parameterEnd)
	{
		MessageBox(GRAPHPREFC_STR11);
		return -1;
	}
	if(pref.parameterSteps<=0)
	{
		MessageBox("Steps must be greather than 0");
		return -1;
	}
	
	
	emit prefChange(pref);
	return 0;
}

void ParameterPreferences::standardButtonSlot()
{
	parameterStart->setText("0");
	parameterEnd->setText("10");
	parameterSteps->setText("200");
}

void DynamicPreferences::getPref(Preferences pr)
{
	pref=pr;
}


int DynamicPreferences::savePref()
{
	pref.dynamicStart=parameterStart->text().toDouble();
	pref.dynamicEnd=parameterEnd->text().toDouble();
	pref.dynamicSteps=parameterSteps->text().toInt();
	pref.dynamicDelay=time->text().toInt();
	
	if(pref.parameterEnd <=pref.parameterStart)
	{
		MessageBox("Dynamic parameter end must be greather than start!");
		return -1;
	}
	else if(pref.dynamicSteps <=0)
	{
		MessageBox("Steps must be greather than 0");
		return -1;
	}
	else if(pref.dynamicDelay <=0)
	{
		MessageBox("Steps must be greather than 0");
		return -1;
	}
	
	if(upButton->isChecked())
		pref.moveUpDown=false;
	else pref.moveUpDown=true;
	
	emit prefChange(pref);
	return 0;

}

void GraphPreferences::saveButtonSlot()
{
	if(coordinateWidget->savePref() >=0)
		if(parameterWidget->savePref()>=0)
			if(dynamicWidget->savePref()>=0)
				close();
}

void GraphPreferences::windowActivationChange(bool)
{

	if(!isActiveWindow())
	{
		setActiveWindow();
	}
}


