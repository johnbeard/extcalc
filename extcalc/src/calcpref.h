#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include "global.h"

#ifndef CALCPREF_H
#define CALCPREF_H


/////////preferences:
//
//	- angle type (deg, rad, gra)
//	- output format (const length, variable length, with eng. symbols)
//	- output length
//	- calculator mode (scientific, logic)
//
//
//
//
//
//



class CalcPreferences :public QWidget
{

	QComboBox *angleBox, *outputBox, *calcModeBox, *baseBox;
	QSpinBox *outputLenBox;
	QPushButton*saveButton,*cancelButton;
	QLabel *angleLabel,*outputLabel,*outputLenLabel,*calcModeLabel,*baseLabel;
	Preferences pref;
	
	Q_OBJECT
	public:
		CalcPreferences(Preferences p,QWidget*parent) :QWidget(parent,"Calculator Preferences",Qt::WStyle_Dialog | Qt::WType_Dialog)
		{
			pref=p;
		
			saveButton=new QPushButton("Save",this);
			cancelButton=new QPushButton("Cancel",this);
			angleBox=new QComboBox(false,this);
			outputBox=new QComboBox(false,this);
			calcModeBox=new QComboBox(false,this);
			baseBox=new QComboBox(false,this);
			outputLenBox=new QSpinBox(2,pref.precision,1,this);
			angleLabel=new QLabel("Angle",this);
			outputLabel=new QLabel("Output Type",this);
			outputLenLabel=new QLabel("Output Digits",this);
			calcModeLabel=new QLabel("Mode",this);
			baseLabel=new QLabel("Base",this);
			
			setGeometry(0,0,400,260);
			setFixedWidth(400);
			setFixedHeight(260);
			
			angleLabel->setGeometry(10,10,150,20);
			angleBox->setGeometry(160,10,120,30);
			outputLabel->setGeometry(10,50,150,20);
			outputBox->setGeometry(160,50,230,30);
			outputLenLabel->setGeometry(10,90,150,20);
			outputLenBox->setGeometry(160,90,80,30);
			calcModeLabel->setGeometry(10,130,150,20);
			calcModeBox->setGeometry(160,130,160,30);
			baseLabel->setGeometry(10,170,150,20);
			baseBox->setGeometry(160,170,120,30);
			saveButton->setGeometry(90,220,100,30);
			cancelButton->setGeometry(210,220,100,30);
			
			angleBox->insertItem("DEG");
			angleBox->insertItem("RAD");
			angleBox->insertItem("GRA");
			
			outputBox->insertItem("Fixed Number of Digits");
			outputBox->insertItem("Variable Number of Digits");
			outputBox->insertItem("With Symbols");
			
			calcModeBox->insertItem("Scientific");
			calcModeBox->insertItem("Base");
			
			baseBox->insertItem("hex");
			baseBox->insertItem("dec");
			baseBox->insertItem("oct");
			baseBox->insertItem("bin");
			
			if(pref.angle==DEG)
				angleBox->setCurrentText("DEG");
			else if(pref.angle==GRA)
				angleBox->setCurrentText("GRA");
			else if(pref.angle==RAD)
				angleBox->setCurrentText("RAD");
			
			if(pref.outputType==FIXEDNUM)
				outputBox->setCurrentText("Fixed Number of Digits");
			else if(pref.outputType==VARIABLENUM)
				outputBox->setCurrentText("Variable Number of Digits");
			else if(pref.outputType==EXPSYM)
				outputBox->setCurrentText("With Symbols");
		
			if(pref.calcType==BASE)
				calcModeBox->setCurrentText("Base");
			else if(pref.calcType==SCIENTIFIC)
				calcModeBox->setCurrentText("Scientific");
			
			if(pref.base==HEX)
				baseBox->setCurrentText("hex");
			else if(pref.base==DEC)
				baseBox->setCurrentText("dec");
			else if(pref.base==OCT)
				baseBox->setCurrentText("oct");
			else if(pref.base==BIN)
				baseBox->setCurrentText("bin");
			
			outputLenBox->setValue(pref.outputLength);
			
			QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(saveSlot()));
			QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
		}

	
	protected:
		virtual void windowActivationChange(bool);


	
	public slots:
	
		void saveSlot();

	
	signals:
		void prefChange(Preferences);
	
	
	
};














#endif






