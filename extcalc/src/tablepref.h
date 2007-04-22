#ifndef TABLEPREF_H
#define TABLEPREF_H

#include "global.h"
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qspinbox.h>


class TablePreferences :public QWidget
{

	QComboBox *typeBox;
	QPushButton*saveButton,*cancelButton;
	QLabel *topLabel;
	QLabel *typeLabel,*xStepLabel,*zStepLabel,*xStartLabel,*xEndLabel,*zStartLabel,*zEndLabel,*xLabel,*zLabel,*aLabel;
	QSpinBox *xStep,*zStep;
	QLineEdit *xStart,*xEnd,*zStart,*zEnd,*aValue;
	Preferences pref;
	
Q_OBJECT
public:
	TablePreferences(Preferences p,QWidget*parent) 
	:QWidget(parent,TABLEPREFH_STR11,Qt::WStyle_Dialog | Qt::WType_Dialog)
	{
		pref=p;
		topLabel=new QLabel(TABLEPREFH_STR1,this);
		typeLabel=new QLabel(TABLEPREFH_STR2,this);
		xLabel=new QLabel(TABLEPREFH_STR12,this);
		zLabel=new QLabel(TABLEPREFH_STR13,this);
		aLabel=new QLabel(TABLEPREFH_STR14,this);
		xStartLabel=new QLabel(TABLEPREFH_STR15,this);
		xStepLabel=new QLabel(TABLEPREFH_STR16,this);
		xEndLabel=new QLabel(TABLEPREFH_STR17,this);
		zStartLabel=new QLabel(TABLEPREFH_STR15,this);
		zEndLabel=new QLabel(TABLEPREFH_STR17,this);
		zStepLabel=new QLabel(TABLEPREFH_STR16,this);
		typeBox=new QComboBox(false,this);
		saveButton=new QPushButton(TABLEPREFH_STR9,this);
		cancelButton=new QPushButton(TABLEPREFH_STR10,this);
		xStart=new QLineEdit(this);
		xEnd=new QLineEdit(this);
		zStart=new QLineEdit(this);
		zEnd=new QLineEdit(this);
		aValue=new QLineEdit(this);
		xStep=new QSpinBox(1,1000,1,this);
		zStep=new QSpinBox(1,1000,1,this);

		setGeometry(0,0,460,350);
		setFixedWidth(460);
		setFixedHeight(350);

		topLabel->setGeometry(10,10,380,20);
		xLabel->setGeometry(10,50,380,20);
		xStartLabel->setGeometry(10,80,75,20);
		xStart->setGeometry(90,80,65,20);
		xEndLabel->setGeometry(160,80,75,20);
		xEnd->setGeometry(240,80,65,20);
		xStepLabel->setGeometry(310,80,75,20);
		xStep->setGeometry(390,80,65,20);
		
		zLabel->setGeometry(10,120,380,20);
		zStartLabel->setGeometry(10,150,75,20);
		zStart->setGeometry(90,150,65,20);
		zEndLabel->setGeometry(160,150,75,20);
		zEnd->setGeometry(240,150,65,20);
		zStepLabel->setGeometry(310,150,75,20);
		zStep->setGeometry(390,150,65,20);
		
		aLabel->setGeometry(10,190,225,20);
		aValue->setGeometry(240,190,65,20);
		
		typeLabel->setGeometry(10,230,150,30);
		typeBox->setGeometry(160,230,145,30);
		saveButton->setGeometry(70,300,110,30);
		cancelButton->setGeometry(280,300,110,30);
		
		typeBox->insertItem(TABLEH_STR3);
		typeBox->insertItem(TABLEH_STR4);
		typeBox->insertItem(TABLEH_STR5);
		typeBox->insertItem(TABLEH_STR6);
		typeBox->insertItem(TABLEH_STR7);
		typeBox->insertItem(TABLEH_STR9);
		
		xStart->setText(QString::number(pref.tableXStart));
		xEnd->setText(QString::number(pref.tableXEnd));
		zStart->setText(QString::number(pref.tableZStart));
		zEnd->setText(QString::number(pref.tableZEnd));
		aValue->setText(QString::number(pref.tableAValue));
		xStep->setValue(pref.tableXSteps);
		zStep->setValue(pref.tableZSteps);
		
		if(pref.tableType==TABLENORMAL)
			typeBox->setCurrentText(TABLEH_STR3);
		else if(pref.tableType==TABLEPOLAR)
			typeBox->setCurrentText(TABLEH_STR4);
		else if(pref.tableType==TABLEPARAMETER)
			typeBox->setCurrentText(TABLEH_STR5);
		else if(pref.tableType==TABLEINEQUAITY)
			typeBox->setCurrentText(TABLEH_STR6);
		else if(pref.tableType==TABLE3D)
			typeBox->setCurrentText(TABLEH_STR7);
		else if(pref.tableType==TABLECOMPLEX)
			typeBox->setCurrentText(TABLEH_STR9);

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



