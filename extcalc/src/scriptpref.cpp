#include "scriptpref.h"


void ScriptPreferences::windowActivationChange(bool)
{

	if(!isActiveWindow())
	{
		setActiveWindow();
	}
}  

void ScriptPreferences::saveSlot()
{
	QString mainPath=mainPathLine->text();
	if(mainPath[mainPath.length()-1]=='/')
		mainPath=mainPath.left(mainPath.length()-1);
	if(mainPath[0]!='/')
	{
		MessageBox(SCRIPTPREFC_STR1);
		return;
	}
	
	

	if(mainPath.length()>0)
	{
		
		if(mkdir(mainPath,0750) ==-1)
		{
			struct stat dirStat;
			if(lstat(mainPath,&dirStat) != -1)
			{
				if(!S_ISDIR(dirStat.st_mode))
				{
					MessageBox(SCRIPTPREFC_STR2);
					return;
				}
			}
			else {
				MessageBox(SCRIPTPREFC_STR2);
				return;
			}
		}
		pref.scriptPath=mainPath;
	}
	else {
		MessageBox(SCRIPTPREFC_STR3);
		return;
	}
	QString scriptPath=scriptPathLine->text();
	if(scriptPath[scriptPath.length()-1]=='/')
		scriptPath=scriptPath.left(scriptPath.length()-1);
		
	if(scriptPath.length()>0 && scriptPath.find(".") ==-1 && scriptPath.find("/")==-1)
	{
		if(mkdir(mainPath+"/"+scriptPath,0750) ==-1)
		{
			struct stat dirStat;
			if(lstat(mainPath+"/"+scriptPath,&dirStat) != -1)
			{
				if(!S_ISDIR(dirStat.st_mode))
				{
					MessageBox(SCRIPTPREFC_STR4);
					return;
				}
			}
			else {
				MessageBox(SCRIPTPREFC_STR4);
				return;
			}
		}
		pref.scriptDirName=scriptPath;
		
	}
	else
	{
		MessageBox(SCRIPTPREFC_STR5);
		return;
	}
	
	QString dataPath=dataPathLine->text();
	if(dataPath[dataPath.length()-1]=='/')
		dataPath=dataPath.left(dataPath.length()-1);
	
	if(dataPath.length()>0 && dataPath.find(".") ==-1 && dataPath.find("/")==-1)
	{
		if(mkdir(mainPath+"/"+dataPath,0750) ==-1)
		{
			struct stat dirStat;
			if(lstat(mainPath+"/"+dataPath,&dirStat) != -1)
			{
				if(!S_ISDIR(dirStat.st_mode))
				{
					MessageBox(SCRIPTPREFC_STR6);
					return;
				}
			}
			else {
				MessageBox(SCRIPTPREFC_STR6);
				return;
			}
		}
		pref.dataDirName=dataPath;
		
	}
	else {
		MessageBox(SCRIPTPREFC_STR7);
		return;
	}	
	
	
	
	emit prefChange(pref);
	close();
}


void ScriptPreferences::fileDialogSlot()
{
	QString path=QFileDialog::getExistingDirectory(getenv("HOME"),this,"getdir",SCRIPTPREFC_STR8,true);
	
	if(!path.isNull())
		mainPathLine->setText(path);
}





