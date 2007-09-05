/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptpref.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Scripting preferences dialog.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef SCRIPTPREFH
#define SCRIPTPREFH

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qcheckbox.h>
#include "global.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


class ScriptPreferences :public QWidget
{
	QPushButton*saveButton,*cancelButton,*fileDialogButton;
	QLabel *infoLabel,*mainPathLabel,*scriptPathLabel,*dataPathLabel;
	QLineEdit *mainPathLine,*scriptPathLine,*dataPathLine;
	QCheckBox *memoryBox;
	Preferences pref;
	bool dialog;
	
	
	Q_OBJECT
public:
	ScriptPreferences(Preferences p,QWidget*parent) 
	:QWidget(parent,"Script Preferences",Qt::WStyle_Dialog | Qt::WType_Dialog)
	{
		pref=p;
		infoLabel=new QLabel(SCRIPTPREFH_STR1,this);
		mainPathLabel=new QLabel(SCRIPTPREFH_STR2,this);
		scriptPathLabel=new QLabel(SCRIPTPREFH_STR3,this);
		dataPathLabel=new QLabel(SCRIPTPREFH_STR4,this);
		mainPathLine=new QLineEdit(this);
		scriptPathLine=new QLineEdit(this);
		dataPathLine=new QLineEdit(this);
		memoryBox=new QCheckBox(SCRIPTPREFH_STR8,this);
		
		saveButton=new QPushButton(SCRIPTPREFH_STR5,this);
		cancelButton=new QPushButton(SCRIPTPREFH_STR6,this);
		fileDialogButton=new QPushButton(SCRIPTPREFH_STR7,this);
		
		setGeometry(0,0,410,350);
		setFixedWidth(410);
		setFixedHeight(350);
		
		infoLabel->setGeometry(20,10,380,20);
		mainPathLabel->setGeometry(20,60,380,20);
		scriptPathLabel->setGeometry(20,130,380,20);
		dataPathLabel->setGeometry(20,200,380,20);
		
		mainPathLine->setGeometry(20,90,280,20);
		scriptPathLine->setGeometry(20,160,280,20);
		dataPathLine->setGeometry(20,230,280,20);
		
		memoryBox->setGeometry(20,270,280,20);
		
		
		saveButton->setGeometry(40,310,100,30);
		cancelButton->setGeometry(180,310,100,30);
		fileDialogButton->setGeometry(310,90,80,30);
		
		mainPathLine->setText(pref.scriptPath);
		scriptPathLine->setText(pref.scriptDirName);
		dataPathLine->setText(pref.dataDirName);
		memoryBox->setChecked(pref.clearScriptMemory);
		
		QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(saveSlot()));
		QObject::connect(fileDialogButton,SIGNAL(clicked()),this,SLOT(fileDialogSlot()));
		QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
	}
	
protected:
	virtual void windowActivationChange(bool);



public slots:

	void saveSlot();
	void fileDialogSlot();


signals:
	void prefChange(Preferences);
};


#endif




