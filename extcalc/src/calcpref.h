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



class CalcPreferences :public QWidget
{

	QComboBox *angleBox, *outputBox, *calcModeBox, *baseBox;
	QSpinBox *outputLenBox;
	QPushButton*saveButton,*cancelButton;
	QCheckBox*complexBox;
	QLabel *angleLabel,*outputLabel,*outputLenLabel,*calcModeLabel,*baseLabel;
	Preferences pref;
	
	Q_OBJECT
	public:
		CalcPreferences(Preferences p,QWidget*parent) :QWidget(parent,"Calculator Preferences",Qt::WStyle_Dialog | Qt::WType_Dialog)
		{
			pref=p;
			saveButton=new QPushButton(CALCPREFH_STR1,this);
			cancelButton=new QPushButton(CALCPREFH_STR2,this);
			angleBox=new QComboBox(false,this);
			outputBox=new QComboBox(false,this);
			calcModeBox=new QComboBox(false,this);
			baseBox=new QComboBox(false,this);
			outputLenBox=new QSpinBox(2,pref.precision,1,this);
			angleLabel=new QLabel(CALCPREFH_STR3,this);
			outputLabel=new QLabel(CALCPREFH_STR4,this);
			outputLenLabel=new QLabel(CALCPREFH_STR5,this);
			calcModeLabel=new QLabel(CALCPREFH_STR6,this);
			baseLabel=new QLabel(CALCPREFH_STR7,this);
			complexBox=new QCheckBox(CALCPREFH_STR13,this);
			
			setGeometry(0,0,400,290);
			setFixedWidth(400);
			setFixedHeight(290);
			
			angleLabel->setGeometry(10,10,150,20);
			angleBox->setGeometry(160,10,120,30);
			outputLabel->setGeometry(10,50,150,20);
			outputBox->setGeometry(160,50,230,30);
			outputLenLabel->setGeometry(10,90,150,20);
			outputLenBox->setGeometry(160,90,80,30);
			calcModeLabel->setGeometry(10,130,150,20);
			calcModeBox->setGeometry(160,130,160,30);
			complexBox->setGeometry(160,165,300,20);
			baseLabel->setGeometry(10,200,150,20);
			baseBox->setGeometry(160,200,120,30);
			saveButton->setGeometry(90,250,100,30);
			cancelButton->setGeometry(210,250,100,30);
			
			angleBox->insertItem("DEG");
			angleBox->insertItem("RAD");
			angleBox->insertItem("GRA");
			
			outputBox->insertItem(CALCPREFH_STR8);
			outputBox->insertItem(CALCPREFH_STR9);
			outputBox->insertItem(CALCPREFH_STR10);
			
			calcModeBox->insertItem(CALCPREFH_STR11);
			calcModeBox->insertItem(CALCPREFH_STR12);
			
			complexBox->setChecked(pref.complex);
			
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
				outputBox->setCurrentText(CALCPREFH_STR8);
			else if(pref.outputType==VARIABLENUM)
				outputBox->setCurrentText(CALCPREFH_STR9);
			else if(pref.outputType==EXPSYM)
				outputBox->setCurrentText(CALCPREFH_STR10);
		
			if(pref.calcType==BASE)
				calcModeBox->setCurrentText(CALCPREFH_STR12);
			else if(pref.calcType==SCIENTIFIC)
				calcModeBox->setCurrentText(CALCPREFH_STR11);
			
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






