#ifndef SCRIPTPREFH
#define SCRIPTPREFH

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
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
	Preferences pref;
	
	
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
		
		saveButton=new QPushButton(SCRIPTPREFH_STR5,this);
		cancelButton=new QPushButton(SCRIPTPREFH_STR6,this);
		fileDialogButton=new QPushButton(SCRIPTPREFH_STR7,this);
		
		setGeometry(0,0,410,310);
		setFixedWidth(410);
		setFixedHeight(310);
		
		infoLabel->setGeometry(20,10,380,20);
		mainPathLabel->setGeometry(20,60,380,20);
		scriptPathLabel->setGeometry(20,130,380,20);
		dataPathLabel->setGeometry(20,200,380,20);
		
		mainPathLine->setGeometry(20,90,280,20);
		scriptPathLine->setGeometry(20,160,280,20);
		dataPathLine->setGeometry(20,230,280,20);
		
		saveButton->setGeometry(40,270,100,30);
		cancelButton->setGeometry(180,270,100,30);
		fileDialogButton->setGeometry(310,90,80,30);
		
		mainPathLine->setText(pref.scriptPath);
		scriptPathLine->setText(pref.scriptDirName);
		dataPathLine->setText(pref.dataDirName);
		
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




