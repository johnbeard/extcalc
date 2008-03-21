#include "importdialog.h"


ImportDialog::ImportDialog(Preferences p,QWidget*parent,bool importF,bool func) 
	:QWidget(parent,EXTCALCH_STR14,Qt::WStyle_Dialog | Qt::WType_Dialog)
{
	dialog=false;
	importFile=importF;
	function=func;
	pref=p;
	if(function)
		directory=QString(getenv("HOME"))+"/"+QString(GRAPHSDIR);
	else directory=pref.scriptPath+"/"+pref.scriptDirName+"/";
	if(importFile)
	{
		mainLabel=new QLabel(EXTCALCH_STR15,this);
		openPathLabel=new QLabel(EXTCALCH_STR16,this);
	}
	else {
		mainLabel=new QLabel(EXTCALCH_STR18,this);
		openPathLabel=new QLabel(EXTCALCH_STR19,this);
	}
	openPathLine=new QLineEdit(this);
	savePathLine=new QLineEdit(this);
	savePathLabel=new QLabel(EXTCALCH_STR17,this);
	openDialogButton=new QPushButton(SCRIPTPREFH_STR7,this);
	saveDialogButton=new QPushButton(SCRIPTPREFH_STR7,this);
	saveButton=new QPushButton(SCRIPTPREFH_STR5,this);
	cancelButton=new QPushButton(SCRIPTPREFH_STR6,this);
	



	setGeometry(0,0,410,260);
	setFixedWidth(410);
	setFixedHeight(260);
	mainLabel->setGeometry(20,10,380,20);
	openPathLabel->setGeometry(20,60,380,20);
	savePathLabel->setGeometry(20,130,380,20);
		
	openPathLine->setGeometry(20,90,280,20);
	savePathLine->setGeometry(20,160,280,20);
		
	saveButton->setGeometry(40,210,100,30);
	cancelButton->setGeometry(180,210,100,30);
	openDialogButton->setGeometry(310,90,80,20);
	saveDialogButton->setGeometry(310,160,80,20);
	
	QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(saveSlot()));
	QObject::connect(openDialogButton,SIGNAL(clicked()),this,SLOT(openDialogSlot()));
	QObject::connect(saveDialogButton,SIGNAL(clicked()),this,SLOT(saveDialogSlot()));
	QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
}


void ImportDialog::windowActivationChange(bool)
{
	if(!isActiveWindow()&&!dialog)
		setActiveWindow();

}

void ImportDialog::saveSlot()
{
	QString savePath=savePathLine->text(),openPath=openPathLine->text();
	
	if(savePath.find("/") <0 && importFile)
		savePath=directory+savePath;
	
	if(openPath.find("/") <0 && !importFile)
		openPath=directory+openPath;
	
	if((savePath.find(directory) !=0 && importFile) || 
		   (openPath.find(directory) !=0 && !importFile))
	{
		ErrorBox(EXTCALCC_MSG6+savePath);
	}
	else
	{
		struct stat testStat;
		
		if(lstat(savePath,&testStat)==0)
		{
			if(YesNoBox(EXTCALCC_MSG8+savePath)==1)
				return;
		}
		else
		{
			system("cp -f "+openPath+" "+savePath);
			emit updateScriptSignal(FILEUPDATE);
		}
		
		close();
	}
}


void ImportDialog::openDialogSlot()
{
	QString startPath,dialogText;
	dialog=true;
	if(!importFile) {
		startPath=directory;
		dialogText=QString(EXTCALCC_MSG9);
	}
	else {
		dialogText=QString(EXTCALCC_MSG10);
		startPath=QString(getenv("HOME"));
	}
	
	QString path = QFileDialog::getOpenFileName(
			startPath,
   QString::null,
   this,
   EXTCALCC_MSG11,
   dialogText);
	dialog=false;
	if(!path.isNull())
		openPathLine->setText(path);

}


void ImportDialog::saveDialogSlot()
{
	dialog=true;
	QString startPath;
	if(importFile)
		startPath=directory;
	else startPath=QString(getenv("HOME"));
	QString path = QFileDialog::getSaveFileName(
			startPath,
   QString::null,
   this,
   EXTCALCC_MSG12,
   EXTCALCC_MSG13 );
	dialog=false;
	if(!path.isNull())
		savePathLine->setText(path);
}


