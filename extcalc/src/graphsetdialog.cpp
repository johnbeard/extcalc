#include "graphsetdialog.h"
#include <stdio.h>


GraphSetDialog::GraphSetDialog(Preferences p,QWidget*parent) 
	:QWidget(parent,EXTCALCH_STR14,Qt::WStyle_Dialog | Qt::WType_Dialog)
{
	pref=p;
	dialog=false;
	okButton=new QPushButton(tr("Ok"),this);
	cancelButton=new QPushButton(tr("Cancel"),this);
	renameButton=new QPushButton(tr("Rename"),this);
	removeButton=new QPushButton(tr("Remove"),this);
	mainLabel=new QLabel(tr("Sets"),this);
	table=new QListBox(this);

	mainLabel->setGeometry(20,20,150,20);
	table->setGeometry(20,50,200,150);
	renameButton->setGeometry(230,50,70,20);
	removeButton->setGeometry(230,80,70,20);
	
	okButton->setGeometry(120,220,80,30);
	cancelButton->setGeometry(220,220,80,30);

	setFixedWidth(320);
	setFixedHeight(270);
	
	graphsDir=new QDir(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR));
	QStringList dir=graphsDir->entryList(QDir::Files);
	table->insertStringList(dir);



	QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(okSlot()));
	QObject::connect(removeButton,SIGNAL(clicked()),this,SLOT(removeSlot()));
	QObject::connect(renameButton,SIGNAL(clicked()),this,SLOT(renameSlot()));
	QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
}


void GraphSetDialog::windowActivationChange(bool)
{
	if(!isActiveWindow()&&!dialog)
		setActiveWindow();

}
void GraphSetDialog::removeSlot()
{
	dialog=true;
	QString current=table->currentText();
	if(current==pref.currentSet)
	{
		ErrorBox(tr("Can't remove active graph set!"));
		dialog=false;
		return;
	}

	int ret=YesNoCancelBox(tr("Do you really want to remove %1?").arg(current));

	if(ret==0)
	{
		int ret=remove(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+current);
		if(ret!=0)
			ErrorBox(tr("Unable to remove file %1").arg(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+current));
	}
	dialog=false;
	QStringList dir=graphsDir->entryList(QDir::Files);
	table->clear();
	table->insertStringList(dir);
}
void GraphSetDialog::renameSlot()
{
	dialog=true;
	QString current=table->currentText();
	bool ok;
	QString newString=QInputDialog::getText(tr("Rename Graph Set"),tr("Insert new name for %1:").arg(current),QLineEdit::Normal,QString(),&ok);
	dialog=false;
	
	if(newString.find("/")!=-1 || newString.find("\\")!=-1)
	{
		ErrorBox(tr("Invalid graph set name %1").arg(newString));
		return;
	}
	if(ok && newString.length()>0)
	{
		bool exist=false;
		QStringList dir=graphsDir->entryList(QDir::Files);
		for(int c=0; c<(signed)dir.count(); c++)
		{
			if(dir[c]==newString)
			{
				exist=true;
				break;
			}
		}
		if(exist)
		{
			int ret=YesNoCancelBox(tr("%1 already exists!\n\nOverwrite it?").arg(newString));
			if(ret!=0)
				return;
		}
		int ret=rename(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+current,QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+newString);
		if(ret!=0)
			ErrorBox(tr("Unable to rename file %1").arg(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+current));
	}
	QStringList dir=graphsDir->entryList(QDir::Files);
	table->clear();
	table->insertStringList(dir);
}
void GraphSetDialog::okSlot()
{
	close();
}



