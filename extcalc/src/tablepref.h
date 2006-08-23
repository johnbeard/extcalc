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
	QLabel *typeLabel,*xStepLabel,*zStepLabel,*xStartLabel,*xEndLabel,*zStartLabel,*zEndLabel;
	QLineEdit *xStep,*zStep;
	QLineEdit *xStart,*xEnd,*zStart,*zEnd;
	Preferences pref;
	
Q_OBJECT
public:
	TablePreferences(Preferences p,QWidget*parent) 
	:QWidget(parent,"Table Preferences",Qt::WStyle_Dialog | Qt::WType_Dialog)
	{
		pref=p;
		topLabel=new QLabel(TABLEPREFH_STR1,this);
		typeLabel=new QLabel(TABLEPREFH_STR2,this);
		xStartLabel=new QLabel(TABLEPREFH_STR3,this);
		xStepLabel=new QLabel(TABLEPREFH_STR4,this);
		xEndLabel=new QLabel(TABLEPREFH_STR5,this);
		zStartLabel=new QLabel(TABLEPREFH_STR6,this);
		zEndLabel=new QLabel(TABLEPREFH_STR7,this);
		zStepLabel=new QLabel(TABLEPREFH_STR8,this);
		typeBox=new QComboBox(false,this);
		saveButton=new QPushButton(TABLEPREFH_STR9,this);
		cancelButton=new QPushButton(TABLEPREFH_STR10,this);
		xStart=new QLineEdit(this);
		xEnd=new QLineEdit(this);
		zStart=new QLineEdit(this);
		zEnd=new QLineEdit(this);
		xStep=new QLineEdit(this);
		zStep=new QLineEdit(this);
		
		setGeometry(0,0,460,350);
		setFixedWidth(460);
		setFixedHeight(350);
		
		topLabel->setGeometry(20,10,380,20);
		xStartLabel->setGeometry(10,50,210,20);
		zStartLabel->setGeometry(240,50,210,20);
		xStart->setGeometry(10,75,210,20);
		zStart->setGeometry(240,75,210,20);
		xEndLabel->setGeometry(10,110,210,20);
		zEndLabel->setGeometry(240,110,210,20);
		xEnd->setGeometry(10,135,210,20);
		zEnd->setGeometry(240,135,210,20);
		xStepLabel->setGeometry(10,170,210,20);
		zStepLabel->setGeometry(240,170,210,20);
		xStep->setGeometry(10,195,210,20);
		zStep->setGeometry(240,195,210,20);
		
		typeLabel->setGeometry(10,250,150,30);
		typeBox->setGeometry(160,250,170,30);
		saveButton->setGeometry(70,300,110,30);
		cancelButton->setGeometry(280,300,110,30);
		
		typeBox->insertItem(TABLEH_STR3);
		typeBox->insertItem(TABLEH_STR4);
		typeBox->insertItem(TABLEH_STR5);
		typeBox->insertItem(TABLEH_STR6);
		typeBox->insertItem(TABLEH_STR7);
		
		xStart->setText(QString::number(pref.tableXStart));
		xEnd->setText(QString::number(pref.tableXEnd));
		zStart->setText(QString::number(pref.tableZStart));
		zEnd->setText(QString::number(pref.tableZEnd));
		xStep->setText(QString::number(pref.tableXSteps));
		zStep->setText(QString::number(pref.tableZSteps));
		
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



