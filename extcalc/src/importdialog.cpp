#include "importdialog.h"


ImportDialog::ImportDialog(Preferences p,QWidget*parent,bool importF,bool func) 
	:QWidget(parent,EXTCALCH_STR14,Qt::WStyle_Dialog | Qt::WType_Dialog)
{
	pref=p;
	tmpPref.activeFunctions=NULL;
	dialog=false;
	importFile=importF;
	function=func;
			
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
	
	table=new CalcTable(this,0,false);
	table->setNumCols(3);
	
	if(function)
	{
		QStringList header(tr("Function"));
		if(importFile)
		{
			header.append(tr("Import to"));
			table->setNumRows(0);
			savePathLabel->hide();
			savePathLine->hide();
			saveDialogButton->hide();
		}
		else 
		{
			table->setNumRows(20);
			header.append(tr("Export"));
			for(int c=0; c<20; c++)
			{
				table->setText(c,0,pref.functions[c]);
				table->setItem(c,1,new QCheckTableItem(table,""));
				table->changeColor(c,pref.functionColors[c]);
				table->setText(c,2,pref.functionComments[c]);
			}
			openPathLabel->hide();
			openPathLine->hide();
			openDialogButton->hide();
		}
		header.append(tr("Comment"));
		table->setColumnLabels(header);
		table->adjustColumn(0);
		table->adjustColumn(1);
	}
	else {
		table->hide();
	}





	if(function)
	{
		setGeometry(0,0,410,460);
		setFixedWidth(410);
		setFixedHeight(460);
		
		mainLabel->setGeometry(20,10,380,20);
		if(importF)
		{
			openPathLabel->setGeometry(20,60,380,20);
			openPathLine->setGeometry(20,90,280,20);
			openDialogButton->setGeometry(310,90,80,20);
			table->setGeometry(20,130,380,250);
		}
		else {
			table->setGeometry(20,60,380,250);
			savePathLabel->setGeometry(20,330,380,20);
			savePathLine->setGeometry(20,360,280,20);
			saveDialogButton->setGeometry(310,360,80,20);
		}
			
		saveButton->setGeometry(40,410,100,30);
		cancelButton->setGeometry(180,410,100,30);
		
		
	}
	else
	{
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
	}
	
	QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(saveSlot()));
	QObject::connect(openDialogButton,SIGNAL(clicked()),this,SLOT(openDialogSlot()));
	QObject::connect(saveDialogButton,SIGNAL(clicked()),this,SLOT(saveDialogSlot()));
	QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
	QObject::connect(openPathLine,SIGNAL(returnPressed()),this,SLOT(openTextChangedSlot()));
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
		savePath=pref.scriptPath+"/"+pref.scriptDirName+"/"+savePath;
	
	if(openPath.find("/") <0 && !importFile)
		openPath=pref.scriptPath+"/"+pref.scriptDirName+"/"+openPath;
	
	if((savePath.find(pref.scriptPath+"/"+pref.scriptDirName) !=0 && importFile) || 
		   (openPath.find(pref.scriptPath+"/"+pref.scriptDirName) !=0 && !importFile))
	{
		ErrorBox(EXTCALCC_MSG6+savePath);
	}
	else
	{
		struct stat testStat;
		
		if(lstat(savePath,&testStat)==0 &&!(function&&importFile))
		{
			if(YesNoBox(EXTCALCC_MSG8+savePath)==1)
				return;
		}
		if(function && !importFile)
		{
			tmpPref.functions=pref.functions;
			tmpPref.functionComments=pref.functionComments;
			tmpPref.functionColors=pref.functionColors;
			tmpPref.logicFunctions=pref.logicFunctions;
			tmpPref.functionTypes=pref.functionTypes;
			tmpPref.dynamicFunctions=pref.dynamicFunctions;
			tmpPref.activeFunctions=new bool[20];
			for(int c=0; c<20; c++)
				tmpPref.activeFunctions[c]=((QCheckTableItem*)table->item(c,1))->isChecked();
			QString saveFile=writeFunctionFile(tmpPref);
			if(saveFile.length()<=0)
			{
				ErrorBox(tr("Error\n\nNo functions marked for export!"));
				return;
			}
			delete[] tmpPref.activeFunctions;
			
			FILE*functionFile=fopen(savePath.latin1(),"w");
			if(functionFile==NULL)
			{
				ErrorBox(tr("Unable to write file: ")+QString(VARSFILE)+"\n\n"+getErrorMessage());
				return;
			}
			fwrite(saveFile.latin1(),saveFile.length(),1,functionFile);
			fclose(functionFile);
		}
		else if(function && importFile)
		{
			for(int c=0; c<table->numRows(); c++)
			{
				int num=((QComboTableItem*)table->item(c,1))->currentItem();
				if(num!=0)
				{
					num--;
					int ret=0;
					if(pref.functions[num].length()>0)
						ret=YesNoCancelBox(tr("Really overwrite F%1?").arg(QString::number(num+1)));
					
					if(ret==0)
					{
						pref.functions[num]=tmpPref.functions[c];
						pref.functionComments[num]=tmpPref.functionComments[c];
						pref.functionColors[num]=tmpPref.functionColors[c];
						pref.dynamicFunctions[num]=tmpPref.dynamicFunctions[c];
						pref.logicFunctions[num]=tmpPref.logicFunctions[c];
						pref.functionTypes[num]=tmpPref.functionTypes[c];
					}
				}
			}
				emit prefChange(pref);
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
		startPath=pref.scriptPath+"/"+pref.scriptDirName;
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
	
	if(importFile && function)
		openTextChangedSlot();
}

void ImportDialog::openTextChangedSlot()
{
	qDebug("openTextChangedSlot");
	if(function && importFile)
	{
		int fileLen;
		struct stat fileStat;

		if(lstat(openPathLine->text().latin1(),&fileStat) != 0)
			return;
		else fileLen=fileStat.st_size;
	
		FILE*f = fopen(openPathLine->text().latin1(),"r");
		if(f == NULL)
		{
			MessageBox(tr("Unable to open file: ")+openPathLine->text());
			return;
		}
		char* cFile = new char[fileLen+1];
		fread((void*)cFile,fileLen,1,f);
		cFile[fileLen]=(char)0;
		QString functionFile(cFile);
		if(tmpPref.activeFunctions!=NULL)
		{
			delete [] tmpPref.activeFunctions;
			delete [] tmpPref.logicFunctions;
			delete [] tmpPref.dynamicFunctions;
			delete [] tmpPref.functions;
			delete [] tmpPref.functionComments;
			delete [] tmpPref.functionColors;
		}
		tmpPref=readFunctionFile(functionFile);
		delete[]cFile;
		fclose(f);
		updateTable();
	}
}

void ImportDialog::saveDialogSlot()
{
	dialog=true;
	QString startPath;
	if(importFile)
		startPath=pref.scriptPath+"/"+pref.scriptDirName;
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

//#config color...
//#config type...
//#config dynamicon/off
//#config logicon/off
//function
Preferences ImportDialog::readFunctionFile(QString file)
{
	Preferences p;
	p.functions=new QString[20];
	p.functionComments=new QString[20];
	p.functionColors=new QColor[20];
	p.logicFunctions=new bool[20];
	p.functionTypes=new int[20];
	p.dynamicFunctions=new bool[20];
	p.activeFunctions=new bool[20];
	int pos1=0,pos2=0,functionCount=0;
	QString config[4],func,comment;
	for(int c=0; c<20; c++)
		p.activeFunctions[c]=false;


	while(1)
	{
		for(int c=0; c<4; c++)
		{
			pos1=file.find("#config ",pos2);
			if(pos1==-1)
				break;
			pos1+=8;
			pos2=file.find("\n",pos1);
			if(pos2==-1)
				break;
			config[c]=file.mid(pos1,pos2-pos1);
			qDebug("config: "+config[c]);
			pos2++;
		}
		if(pos1==-1 || pos2==-1)
			break;
		pos1=file.find("\n",pos2);
		if(pos1==-1 || pos2==-1)
			break;
		comment=file.mid(pos2+2,pos1-pos2-2);
		pos2=pos1+1;
		pos1=file.find("\n",pos2);
		if(pos1==-1 || pos2==-1)
			break;
		func=file.mid(pos2,pos1-pos2);
		pos2=pos1+1;


		
		
		pos1=config[0].find("color");
		if(pos1==-1)
			break;
		config[0]=config[0].right(config[0].length()-pos1-5);
		qDebug("Color: /"+config[0]+"/");
		p.functionColors[functionCount]=getColor(config[0]);
		
		
		pos1=config[1].find("type");
		if(pos1==-1)
			break;
		config[1]=config[1].right(config[1].length()-4-pos1);
		

		if(config[1].lower() == "nyquist3d")
			p.functionTypes[functionCount]=GRAPHCOMP3D;
		else if(config[1].lower() == "parameter")
			p.functionTypes[functionCount]=GRAPHPARAMETER;
		else if(config[1].lower() == "polar")
			p.functionTypes[functionCount]=GRAPHPOLAR;
		else if(config[1].lower() == "3d")
			p.functionTypes[functionCount]=GRAPH3D;
		else if(config[1].lower() == "iel")
			p.functionTypes[functionCount]=GRAPHIEL;
		else if(config[1].lower() == "iele")
			p.functionTypes[functionCount]=GRAPHIELE;
		else if(config[1].lower() == "ieg")
			p.functionTypes[functionCount]=GRAPHIEG;
		else if(config[1].lower() == "iege")
			p.functionTypes[functionCount]=GRAPHIEGE;
		else if(config[1].lower() == "nyquist2d")
			p.functionTypes[functionCount]=GRAPHCOMPLEX;
		else p.functionTypes[functionCount]=GRAPHSTD;
		
		pos1=config[2].find("dynamic");
		if(pos1==-1)
			break;
		config[2]=config[2].right(config[2].length()-7-pos1);
		qDebug("dynamic: /"+config[2]+"/");
		if(config[2]=="on")
			p.dynamicFunctions[functionCount]=true;
		else p.dynamicFunctions[functionCount]=false;
		
		pos1=config[3].find("logic");
		if(pos1==-1)
			break;
		config[3]=config[3].right(config[3].length()-5-pos1);
		qDebug("logic: /"+config[3]+"/");
		if(config[3]=="on")
			p.logicFunctions[functionCount]=true;
		else p.logicFunctions[functionCount]=false;

		p.functions[functionCount]=resetConfigString(func);
		p.functionComments[functionCount]=comment;
		p.activeFunctions[functionCount]=true;
		functionCount++;
	}
	return p;
}

QString ImportDialog::writeFunctionFile(Preferences p)
{
	QString expFile("");
	for(int c=0; c<20; c++)
	{
		if(p.activeFunctions[c])
		{
			expFile+="#config color"+getColorName(pref.functionColors[c])+"\n";
			expFile+="#config type";
			switch(p.functionTypes[c])
			{
				case GRAPHPOLAR:
					expFile+="polar";break;
				case GRAPHPARAMETER:
					expFile+="parameter";break;
				case GRAPH3D:
					expFile+="3d";break;
				case GRAPHIEL:
					expFile+="iel";break;
				case GRAPHIELE:
					expFile+="iele";break;
				case GRAPHIEG:
					expFile+="ieg";break;
				case GRAPHIEGE:
					expFile+="iege";break;
				case GRAPHCOMPLEX:
					expFile+="nyquist2d";break;
				case GRAPHCOMP3D:
					expFile+="nyquist3d";break;
				default:
					expFile+="std";
			}
			expFile+="\n";
			expFile+="#config dynamic";
			if(p.dynamicFunctions[c])
				expFile+="on\n";
			else expFile+="off\n";
			expFile+="#config logic";
			if(p.logicFunctions[c])
				expFile+="on\n";
			else expFile+="off\n";
			expFile+="//"+p.functionComments[c]+"\n";
			expFile+=cleanConfigString("",p.functions[c])+"\n";
		}
	}
	return expFile;
}

void ImportDialog::updateTable()
{
	while(table->numRows()>0)
		table->removeRow(0);
	
	if(tmpPref.activeFunctions==NULL)
		return;
	
	QStringList boxContent(tr("None"));
	for(int c1=0; c1<20; c1++)
		boxContent.append("F"+QString::number(c1+1));
	int index=0;
	for(int c=0; c<20; c++)
	{
		qDebug("function: "+QString::number(c));
		if(tmpPref.activeFunctions[c]==false)
			continue;
		table->setNumRows(table->numRows()+1);

		table->setItem(index,1,new QComboTableItem(table,boxContent,false));
		table->setText(index,0,tmpPref.functions[c]);
		table->setText(index,2,tmpPref.functionComments[c]);
		table->changeColor(index,tmpPref.functionColors[c]);
		index++;
	}
	table->adjustColumn(0);
	table->adjustColumn(1);
	
	int c2=0;
	for(int c1=0; c1<table->numRows(); c1++)
	{
		while(c2<20)
		{
			if(pref.functions[c2].length()<=0)
			{
				c2++;
				((QComboTableItem*)table->item(c1,1))->setCurrentItem(c2);
				break;
			}
			else c2++;
		}
		if(c2==20)
			break;
	}
		

}


