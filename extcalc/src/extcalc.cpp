#include "extcalc.h"


MainObject *mainObj;


int main( int argc, char **argv ) {
//	lastResult=0.0F;
	QApplication a( argc, argv );
	MainObject * mainObject = new MainObject;
	mainObj=mainObject;
//	a.setStyle("cde");
	QFont stdFont("Helvetica");
	stdFont.setPixelSize(14);
	a.setFont(stdFont);
	
#ifdef LANGUAGE_DE
	QTranslator german(NULL);

	if(german.load("data/qt_de.qm",INSTALLDIR))
		a.installTranslator(&german);
	else MessageBox("QT-Sprachpaket konnte nicht geladen werden");
#endif

//root		8730
//Pi		960   (982)
//Euler		65349 (1214)
//Mega		65325 (1052)
//Giga		65319 (1292)
//Terra		65332 (1196)

	a.setMainWidget(mainObj);
	mainObj->show();
	return a.exec();
}





void MainObject::closeEvent(QCloseEvent*e)
{
	writeConfigFile();
	if(scripting->quitProgram())
	{
		e->accept();
		delete[] pref.functions;
	}
	

}


// Return values of readConfigFile()
//	 0	no problems
//	-1	configfile didn't exist, but could be created
//	-2	configfile didn't exist and could not be created
//	-3	configfile exists but can't be read

int MainObject::readConfigFile()
{
	FILE*configFile;
	int ret=0;

	chdir(getenv("HOME"));

	int fileLen;
	struct stat fileStat;

	if(lstat(CONFIGFILE,&fileStat) != 0)				//default configfile
	{

		mkdir(".extcalc", S_IRUSR | S_IWUSR | S_IXUSR);
		configFile=fopen(CONFIGFILE,"w");
		if(configFile != NULL)
		{
			ret=-1;
			fwrite("ANGLE=rad\n",10,1,configFile);
			fwrite("OUTPUTTYPE=variablenum\n",23,1,configFile);
			fwrite("OUTPUTLENGTH=10\n",16,1,configFile);
			fwrite("AXIS=true\n",10,1,configFile);
			fwrite("RASTER=true\n",12,1,configFile);
			fwrite("LABEL=false\n",12,1,configFile);
			fwrite("AUTOSIZE=false\n",15,1,configFile);
			fwrite("XMIN=-10.0\n",11,1,configFile);
			fwrite("XMAX=10.0\n",10,1,configFile);
			fwrite("YMIN=-10.0\n",11,1,configFile);
			fwrite("YMAX=10.0\n",10,1,configFile);
			fwrite("ZMIN=-10.0\n",11,1,configFile);
			fwrite("ZMAX=10.0\n",10,1,configFile);
			fwrite("RASTERSIZEX=1\n",14,1,configFile);
			fwrite("RASTERSIZEY=1\n",14,1,configFile);
			fwrite("RASTERSIZEZ=1\n",14,1,configFile);
			fwrite("RADIUSMAX=10\n",13,1,configFile);
			fwrite("ANGLEMAX=360\n",13,1,configFile);
			fwrite("RASTERSIZERADIUS=1\n",19,1,configFile);
			fwrite("RASTERSIZEANGLE=15\n",19,1,configFile);
			fwrite("PARAMETERSTART=0\n",17,1,configFile);
			fwrite("PARAMETEREND=10\n",16,1,configFile);
			fwrite("PARAMETERSTEPS=200\n",19,1,configFile);
			fwrite("DYNAMICSTART=0\n",15,1,configFile);
			fwrite("DYNAMICEND=10\n",14,1,configFile);
			fwrite("DYNAMICSTEPS=10\n",16,1,configFile);
			fwrite("DYNAMICDELAY=1\n",15,1,configFile);
			fwrite("DYNAMICMOVEUPDOWN=true\n",23,1,configFile);
			fwrite("TABLESTARTX=0\n",14,1,configFile);
			fwrite("TABLESTARTZ=0\n",14,1,configFile);
			fwrite("TABLEENDX=10\n",12,1,configFile);
			fwrite("TABLEENDZ=10\n",12,1,configFile);
			fwrite("TABLESTEPSX=11\n",14,1,configFile);
			fwrite("TABLESTEPSZ=11\n",14,1,configFile);
			fwrite("GRAPHTYPE=std\n",14,1,configFile);
			fwrite("CALCTYPE=scientific\n",20,1,configFile);
			fwrite("TABLETYPE=normal\n",17,1,configFile);
			fwrite("BASE=dec\n",9,1,configFile);
			fwrite("SHOWWIN1=true\n",14,1,configFile);
			fwrite("SHOWWIN2=false\n",15,1,configFile);
			fwrite("SHOWWIN3=true\n",14,1,configFile);
			fwrite("SHOWWIN4=true\n",14,1,configFile);
			fwrite("SHOWWIN5=true\n",15,1,configFile);
			fwrite("SHOWWIN6=false\n",15,1,configFile);
			fwrite("SCRIPTROOT=\n",12,1,configFile);
			fwrite("CODEPATH=\n",10,1,configFile);
			fwrite("DATAPATH=\n",10,1,configFile);
			
			fwrite("F1=sinX\n",8,1,configFile);
			for(int c=1; c<9; c++)
				fwrite("F"+QString::number(c+1)+"=\n",4,1,configFile);
			for(int c=9; c<20; c++)
				fwrite("F"+QString::number(c+1)+"=\n",5,1,configFile);
			fwrite("F1ACTIVE=true\n",14,1,configFile);
			for(int c=1; c<9; c++)
				fwrite("F"+QString::number(c+1)+"ACTIVE=false\n",15,1,configFile);
			for(int c=9; c<20; c++)
				fwrite("F"+QString::number(c+1)+"ACTIVE=false\n",16,1,configFile);
			for(int c=0; c<9; c++)
				fwrite("F"+QString::number(c+1)+"COLOR="+QString(GRAPHH_COL1)+"\n",9+strlen(GRAPHH_COL1),1,configFile);
			for(int c=9; c<20; c++)
				fwrite("F"+QString::number(c+1)+"COLOR="+QString(GRAPHH_COL1)+"\n",10+strlen(GRAPHH_COL1),1,configFile);
			for(int c=0; c<9; c++)
				fwrite("F"+QString::number(c+1)+"TYPE=std\n",11,1,configFile);
			for(int c=9; c<20; c++)
				fwrite("F"+QString::number(c+1)+"TYPE=std\n",12,1,configFile);
			for(int c=0; c<9; c++)
				fwrite("F"+QString::number(c+1)+"DYNAMIC=false\n",16,1,configFile);
			for(int c=9; c<20; c++)
				fwrite("F"+QString::number(c+1)+"DYNAMIC=false\n",17,1,configFile);
			fclose(configFile);
			
			if(lstat(CONFIGFILE,&fileStat) != 0)
			{
				MessageBox(EXTCALCC_MSG3+QString(CONFIGFILE));
				return -3;
			}
				
		}
		else {
			MessageBox(EXTCALCC_MSG1+QString(CONFIGFILE)+EXTCALCC_MSG2);
			ret=-2;
		}
	}
	fileLen=fileStat.st_size;



	configFile = fopen(CONFIGFILE,"r");
	if(configFile == NULL)
	{
		MessageBox(EXTCALCC_MSG3+QString(CONFIGFILE));
		return -3;
	}
	char* cConfFile = new char[fileLen+1];
	fread((void*)cConfFile,fileLen,1,configFile);
	cConfFile[fileLen]=(char)0;
	QString confFile(cConfFile);
	delete[]cConfFile;
	

	QString angle=getConfigString(&confFile,"ANGLE");
	if(angle=="deg")
		pref.angle=DEG;
	else if(angle=="rad")
		pref.angle=RAD;
	else if(angle=="gra")
		pref.angle=GRA;
	QString outputType=getConfigString(&confFile,"OUTPUTTYPE");
	if(outputType == "fixednum")
		pref.outputType=FIXEDNUM;
	else if(outputType == "variablenum")
		pref.outputType=VARIABLENUM;
	else if(outputType == "expsym")
		pref.outputType=EXPSYM;
	
	
	QString outputLength=getConfigString(&confFile,"OUTPUTLENGTH");
	if(outputLength.length()>0)
	{
		int outLen=outputLength.toInt();
		if(outLen > pref.precision)
			outLen = pref.precision;
		if(outLen < 2)
			outLen = 2;
		pref.outputLength=outLen;
	}
	QString xMinStr=getConfigString(&confFile,"XMIN");
	if(xMinStr.length()>0)
	{
		double xMin=xMinStr.toDouble();
		if(xMin == NAN)
			xMin=-10.0;
		pref.xmin=xMin;
	}
	
	QString xMaxStr=getConfigString(&confFile,"XMAX");
	if(xMaxStr.length()>0)
	{
		double xMax=xMaxStr.toDouble();
		if(xMax == NAN)
			xMax=10.0;
		if(xMax <= pref.xmin)
			xMax=pref.xmin+=10.0;
		pref.xmax=xMax;
	}
	QString yMinStr=getConfigString(&confFile,"YMIN");
	if(yMinStr.length()>0)
	{
		double yMin=yMinStr.toDouble();
		if(yMin == NAN)
			yMin=-10.0;
		pref.ymin=yMin;
	}
	
	QString yMaxStr=getConfigString(&confFile,"YMAX");
	if(yMaxStr.length()>0)
	{
		double yMax=yMaxStr.toDouble();
		if(yMax == NAN)
			yMax=10.0;
		if(yMax <= pref.ymin)
			yMax=pref.ymin+=10.0;
		pref.ymax=yMax;
	}
	QString zMinStr=getConfigString(&confFile,"ZMIN");
	if(zMinStr.length()>0)
	{
		double zMin=zMinStr.toDouble();
		if(zMin == NAN)
			zMin=-10.0;
		pref.zmin=zMin;
	}
	
	QString zMaxStr=getConfigString(&confFile,"ZMAX");
	if(zMaxStr.length()>0)
	{
		double zMax=zMaxStr.toDouble();
		if(zMax == NAN)
			zMax=10.0;
		if(zMax <= pref.zmin)
			zMax=pref.zmin+=10.0;
		pref.zmax=zMax;
	}
		
	QString radiusMaxStr=getConfigString(&confFile,"RADIUSMAX");
	if(radiusMaxStr.length()>0)
	{
		double radiusMax=radiusMaxStr.toDouble();
		if(radiusMax >0.0 && radiusMax!=NAN)
			pref.radiusMax=radiusMax;
		else pref.radiusMax=10.0;
	}

	
	QString anlgeMaxStr=getConfigString(&confFile,"ANGLEMAX");
	if(anlgeMaxStr.length()>0)
	{
		double anlgeMax=anlgeMaxStr.toDouble();
		if(anlgeMax >0.0 && anlgeMax!=NAN)
			pref.angleMax=anlgeMax;
		else pref.angleMax=360.0;
	}
	
	QString radiusRasterStr=getConfigString(&confFile,"RASTERSIZERADIUS");
	if(radiusRasterStr.length()>0)
	{
		double radiusRaster=radiusRasterStr.toDouble();
		if(radiusRaster >0.0 && radiusRaster!=NAN)
			pref.rasterSizeRadius=radiusRaster;
		else pref.rasterSizeRadius=1.0;
	}
	
	QString angleRasterStr=getConfigString(&confFile,"RASTERSIZEANGLE");
	if(angleRasterStr.length()>0)
	{
		double angleRaster=angleRasterStr.toDouble();
		if(angleRaster >0.0 && angleRaster!=NAN)
			pref.rasterSizeAngle=angleRaster;
		else pref.rasterSizeAngle=15.0;
	}
	
	QString xRasterStr=getConfigString(&confFile,"RASTERSIZEX");
	if(xRasterStr.length()>0)
	{
		double xRaster=xRasterStr.toDouble();
		if(xRaster == NAN)
			xRaster=1.0;
		if(xRaster <=0.0)
			xRaster=1.0;
		pref.rasterSizeX=xRaster;
	}
	QString yRasterStr=getConfigString(&confFile,"RASTERSIZEY");
	if(yRasterStr.length()>0)
	{
		double yRaster=yRasterStr.toDouble();
		if(yRaster == NAN)
			yRaster=1.0;
		if(yRaster <=0.0)
			yRaster=1.0;
		pref.rasterSizeY=yRaster;
	}
	QString zRasterStr=getConfigString(&confFile,"RASTERSIZEZ");
	if(zRasterStr.length()>0)
	{
		double zRaster=zRasterStr.toDouble();
		if(zRaster == NAN)
			zRaster=1.0;
		if(zRaster <=0.0)
			zRaster=1.0;
		pref.rasterSizeZ=zRaster;
	}
	QString dynStartStr=getConfigString(&confFile,"DYNAMICSTART");
	if(dynStartStr.length()>0)
	{
		double dynStart=dynStartStr.toDouble();
		if(dynStart == NAN)
			dynStart=0.0;
		pref.dynamicStart=dynStart;
	}
	QString dynEndStr=getConfigString(&confFile,"DYNAMICEND");
	if(dynEndStr.length()>0)
	{
		double dynEnd=dynEndStr.toDouble();
		if(dynEnd == NAN)
			dynEnd=0.0;
		if(dynEnd <=pref.dynamicStart)
			dynEnd=pref.dynamicStart+10.0;
		pref.dynamicEnd=dynEnd;
	}
	QString dynStepsStr=getConfigString(&confFile,"DYNAMICSTEPS");
	if(dynStepsStr.length()>0)
	{
		int dynSteps=dynStepsStr.toInt();
		if(dynSteps <1)
			dynSteps=10;
		pref.dynamicSteps=dynSteps;
	}
	
	QString dynDelayStr=getConfigString(&confFile,"DYNAMICDELAY");
	if(dynDelayStr.length()>0)
	{
		int dynDelay=dynDelayStr.toInt();
		if(dynDelay <0)
			dynDelay=1;
		pref.dynamicDelay=dynDelay;
	}
	QString paraEndStr=getConfigString(&confFile,"PARAMETEREND");
	if(paraEndStr.length()>0)
	{
		double paraEnd=paraEndStr.toDouble();
		if(paraEnd == NAN || paraEnd <= pref.parameterStart)
			paraEnd=pref.parameterStart+10.0;
		pref.parameterEnd=paraEnd;
	}	
	QString paraStepStr=getConfigString(&confFile,"PARAMETERSTEPS");
	if(paraStepStr.length()>0)
	{
		int paraStep=paraStepStr.toInt();
		if(paraStep <=0)
			paraStep=200;
		pref.parameterSteps=paraStep;
	}
	QString tableStartXStr=getConfigString(&confFile,"TABLESTARTX");
	if(tableStartXStr.length()>0)
	{
		double tableStartX=tableStartXStr.toDouble();
		if(tableStartX == NAN)
			tableStartX=0.0;
		pref.tableXStart=tableStartX;
	}
	QString tableEndXStr=getConfigString(&confFile,"TABLEENDX");
	if(tableEndXStr.length()>0)
	{
		double tableEndX=tableEndXStr.toDouble();
		if(tableEndX == NAN || tableEndX<=pref.tableXStart)
			tableEndX=0.0;
		pref.tableXEnd=tableEndX;
	}
	QString tableStartZStr=getConfigString(&confFile,"TABLESTARTZ");
	if(tableStartZStr.length()>0)
	{
		double tableStartZ=tableStartZStr.toDouble();
		if(tableStartZ == NAN)
			tableStartZ=0.0;
		pref.tableZStart=tableStartZ;
	}
	QString tableEndZStr=getConfigString(&confFile,"TABLEENDZ");
	if(tableEndZStr.length()>0)
	{
		double tableEndZ=tableEndZStr.toDouble();
		if(tableEndZ == NAN || tableEndZ<=pref.tableXStart)
			tableEndZ=0.0;
		pref.tableZEnd=tableEndZ;
	}
	QString tableStepsXStr=getConfigString(&confFile,"TABLESTEPSX");
	if(tableStepsXStr.length()>0)
	{
		int tableXSteps=tableStepsXStr.toInt();
		if(tableXSteps <1)
			tableXSteps=10;
		pref.tableXSteps=tableXSteps;
	}
	QString tableStepsZStr=getConfigString(&confFile,"TABLESTEPSZ");
	if(tableStepsZStr.length()>0)
	{
		int tableZSteps=tableStepsZStr.toInt();
		if(tableZSteps <1)
			tableZSteps=10;
		pref.tableZSteps=tableZSteps;
	}
	QString rasterStr=getConfigString(&confFile,"RASTER");
	if(rasterStr.length()>0)
	{
		if(rasterStr.lower() == "true")
			pref.raster=true;
		else pref.raster=false;
	}

	QString axisStr=getConfigString(&confFile,"AXIS");
	if(axisStr.length()>0)
	{
		if(axisStr.lower() == "true")
			pref.axis=true;
		else pref.axis=false;
	}

	QString labelStr=getConfigString(&confFile,"LABEL");
	if(labelStr.length()>0)
	{
		if(labelStr.lower() == "true")
			pref.label=true;
		else pref.label=false;
	}
	
	QString autosizeStr=getConfigString(&confFile,"AUTOSIZE");
	if(autosizeStr.length()>0)
	{
		if(autosizeStr.lower() == "true")
			pref.autosize=true;
		else pref.autosize=false;
	}	
	QString moveStr=getConfigString(&confFile,"DYNAMICMOVEUPDOWN");
	if(moveStr.length()>0)
	{
		if(moveStr.lower() == "true")
			pref.moveUpDown=true;
		else pref.moveUpDown=false;
	}	
	QString graphType=getConfigString(&confFile,"GRAPHTYPE");
	if(graphType.length()>0)
	{
		if(graphType.lower() == "polar")
			pref.graphType=GRAPHPOLAR;
		else if(graphType.lower() == "3d")
			pref.graphType=GRAPH3D;
		else pref.graphType=GRAPHSTD;
	}
	
	QString calcType=getConfigString(&confFile,"CALCTYPE");
	if(calcType.length()>0)
	{
		if(calcType.lower() == "base")
			pref.calcType=BASE;
		else pref.calcType=SCIENTIFIC;
	}

	QString base=getConfigString(&confFile,"BASE");
	if(base.length()>0)
	{
		if(base.lower() == "bin")
			pref.base=BIN;
		else if(base.lower() == "oct")
			pref.base=OCT;
		else if(base.lower() == "hex")
			pref.base=HEX;
		else if(base.lower() == "dec")
			pref.base=DEC;
		
	}
	QString tableType=getConfigString(&confFile,"TABLETYPE");
	if(tableType.length()>0)
	{
		if(tableType.lower() == "normal")
			pref.tableType=TABLENORMAL;
		else if(tableType.lower() == "polar")
			pref.tableType=TABLEPOLAR;
		else if(tableType.lower() == "parameter")
			pref.tableType=TABLEPARAMETER;
		else if(tableType.lower() == "inequaity")
			pref.tableType=TABLEINEQUAITY;
		else if(tableType.lower() == "3d")
			pref.tableType=TABLE3D;
		
	}
	for(int c=0; c<6; c++)
	{
		QString showWinString=getConfigString(&confFile,"SHOWWIN"+QString::number(c+1));
		if(showWinString.lower() =="false")
			pref.showWindows[c]=false;
		else pref.showWindows[c]=true;
	}
	
	QString*functionStrings=new QString[20];
	
	for(int c=0; c<20; c++)
	{
		functionStrings[c]=getConfigString(&confFile,"F"+QString::number(c+1));
		if(functionStrings[c].length()<=0)
			functionStrings[c]="";
	}
	if(pref.functions!=NULL)
		delete[]pref.functions;
	pref.functions=functionStrings;
	
	bool*activeFunctions=new bool[20];
	
	for(int c=0; c<20; c++)
	{
		QString activeString=getConfigString(&confFile,"F"+QString::number(c+1)+"ACTIVE");
		if(activeString.lower() =="true" &&activeString.length()>0)
			activeFunctions[c]=true;
		else activeFunctions[c]=false;
	}
	if(pref.activeFunctions!=NULL)
		delete[]pref.activeFunctions;
	pref.activeFunctions=activeFunctions;
	
	bool*dynamicFunctions=new bool[20];
	for(int c=0; c<20; c++)
	{
		QString dynamicString=getConfigString(&confFile,"F"+QString::number(c+1)+"DYNAMIC");
		if(dynamicString.lower() =="true" &&dynamicString.length()>0)
			dynamicFunctions[c]=true;
		else dynamicFunctions[c]=false;
	}
	if(pref.dynamicFunctions!=NULL)
		delete[]pref.dynamicFunctions;
	pref.dynamicFunctions=dynamicFunctions;

	QString scriptPath=getConfigString(&confFile,"SCRIPTROOT");
	if(scriptPath.length()<=0)
		scriptPath="";
	pref.scriptPath=scriptPath;
	
	QString codePath=getConfigString(&confFile,"CODEPATH");
	if(codePath.length()<=0)
		codePath="";
	pref.scriptDirName=codePath;
	
	QString dataPath=getConfigString(&confFile,"DATAPATH");
	if(dataPath.length()<=0)
		dataPath="";
	pref.dataDirName=dataPath;

	QColor*functionColors=new QColor[20];
	for(int c=0; c<20; c++)
	{
		QString colorName=getConfigString(&confFile,"F"+QString::number(c+1)+"COLOR");
		if(colorName.length()<=0)
			functionColors[c]=getColor(GRAPHH_COL1);
		else functionColors[c]=getColor(colorName);
	}
	if(pref.functionColors!=NULL)
		delete[]pref.functionColors;
	pref.functionColors=functionColors;

	int*types=new int[20];
	for(int c=0; c<20; c++)
	{
		QString typeString=getConfigString(&confFile,"F"+QString::number(c+1)+"TYPE");
		if(typeString.length()>0)
		{
			if(typeString.lower() == "std")
				types[c]=GRAPHSTD;
			else if(typeString.lower() == "parameter")
				types[c]=GRAPHPARAMETER;
			else if(typeString.lower() == "polar")
				types[c]=GRAPHPOLAR;
			else if(typeString.lower() == "3d")
				types[c]=GRAPH3D;
			else if(typeString.lower() == "iel")
				types[c]=GRAPHIEL;
			else if(typeString.lower() == "iele")
				types[c]=GRAPHIELE;
			else if(typeString.lower() == "ieg")
				types[c]=GRAPHIEG;
			else if(typeString.lower() == "iege")
				types[c]=GRAPHIEGE;
		}
		else types[c]=GRAPHSTD;
	}
	if(pref.functionTypes!=NULL)
		delete[]pref.functionTypes;
	pref.functionTypes=types;

	getPref(pref);
	return ret;
}

void MainObject::writeConfigFile()
{

	FILE*configFile;

	chdir(getenv("HOME"));
	configFile = fopen(CONFIGFILE,"w");
	if(configFile == NULL)
	{
		MessageBox(EXTCALCC_MSG4+QString(CONFIGFILE));
		return;
	}
	QString configuration="";
	
	configuration+="ANGLE=";
	if(pref.angle==DEG)
		configuration+="deg";
	else if(pref.angle==RAD)
		configuration+="rad";
	else if(pref.angle==GRA)
		configuration+="gra";
	configuration+="\nOUTPUTTYPE=";
	if(pref.outputType==FIXEDNUM)
		configuration+="fixednum";
	else if(pref.outputType==VARIABLENUM)
		configuration+="variablenum";
	else if(pref.outputType==EXPSYM)
		configuration+="expsym";
	configuration+="\nOUTPUTLENGTH=";
	configuration+=QString::number(pref.outputLength);
	configuration+="\nXMIN=";
	configuration+=QString::number(pref.xmin);
	configuration+="\nXMAX=";
	configuration+=QString::number(pref.xmax);
	configuration+="\nYMIN=";
	configuration+=QString::number(pref.ymin);
	configuration+="\nYMAX=";
	configuration+=QString::number(pref.ymax);
	configuration+="\nZMIN=";
	configuration+=QString::number(pref.zmin);
	configuration+="\nZMAX=";
	configuration+=QString::number(pref.zmax);
	configuration+="\nRADIUSMAX=";
	configuration+=QString::number(pref.radiusMax);
	configuration+="\nANGLEMAX=";
	configuration+=QString::number(pref.angleMax);
	configuration+="\nRASTERSIZEX=";
	configuration+=QString::number(pref.rasterSizeX);
	configuration+="\nRASTERSIZEY=";
	configuration+=QString::number(pref.rasterSizeY);
	configuration+="\nRASTERSIZEZ=";
	configuration+=QString::number(pref.rasterSizeZ);
	configuration+="\nRASTERSIZEANGLE=";
	configuration+=QString::number(pref.rasterSizeAngle);
	configuration+="\nRASTERSIZERADIUS=";
	configuration+=QString::number(pref.rasterSizeRadius);
	configuration+="\nPARAMETERSTART=";
	configuration+=QString::number(pref.parameterStart);
	configuration+="\nPARAMETEREND=";
	configuration+=QString::number(pref.parameterEnd);
	configuration+="\nPARAMETERSTEPS=";
	configuration+=QString::number(pref.parameterSteps);
	configuration+="\nDYNAMICSTART=";
	configuration+=QString::number(pref.dynamicStart);
	configuration+="\nDYNAMICEND=";
	configuration+=QString::number(pref.dynamicEnd);
	configuration+="\nDYNAMICSTEPS=";
	configuration+=QString::number(pref.dynamicSteps);
	configuration+="\nDYNAMICDELAY=";
	configuration+=QString::number(pref.dynamicDelay);
	configuration+="\nTABLESTARTX=";
	configuration+=QString::number(pref.tableXStart);
	configuration+="\nTABLEENDX=";
	configuration+=QString::number(pref.tableXEnd);
	configuration+="\nTABLESTARTZ=";
	configuration+=QString::number(pref.tableZStart);
	configuration+="\nTABLEENDZ=";
	configuration+=QString::number(pref.tableZEnd);
	configuration+="\nTABLESTEPSX=";
	configuration+=QString::number(pref.tableXSteps);
	configuration+="\nTABLESTEPSZ=";
	configuration+=QString::number(pref.tableZSteps);
	configuration+="\nSCRIPTROOT=";
	configuration+=pref.scriptPath;
	configuration+="\nCODEPATH=";
	configuration+=pref.scriptDirName;
	configuration+="\nDATAPATH=";
	configuration+=pref.dataDirName;
	configuration+="\nRASTER=";
	if(pref.raster == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nAXIS=";
	if(pref.axis == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nLABEL=";
	if(pref.label == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nAUTOSIZE=";
	if(pref.autosize == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nDYNAMICMOVEUPDOWN=";
	if(pref.moveUpDown == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nGRAPHTYPE=";
	if(pref.graphType == GRAPHPOLAR)
		configuration+="polar";
	else if(pref.graphType == GRAPH3D)
		configuration+="3d";
	else configuration+="std";
	configuration+="\nCALCTYPE=";
	if(pref.calcType == BASE)
		configuration+="base";
	else configuration+="scientific";
	configuration+="\nTABLETYPE=";
	if(pref.tableType==TABLENORMAL)
		configuration+="normal";
	else if(pref.tableType==TABLEPOLAR)
		configuration+="polar";
	else if(pref.tableType==TABLEPARAMETER)
		configuration+="parameter";
	else if(pref.tableType==TABLEINEQUAITY)
		configuration+="inequaity";
	else if(pref.tableType==TABLE3D)
		configuration+="3d";
	configuration+="\nBASE=";
	if(pref.base == HEX)
		configuration+="hex";
	else if(pref.base == OCT)
		configuration+="oct";
	else if(pref.base == BIN)
		configuration+="bin";
	else if(pref.base == DEC)
		configuration+="dec";
	configuration+="\n";
	
	
	
	
	
	for(int c=0; c<6;c++)
	{
		configuration+="SHOWWIN";
		configuration+=QString::number(c+1);
		configuration+="=";
		if(pref.showWindows[c])
			configuration+="true\n";
		else configuration+="false\n";
	}
	
	for(int c=0; c<20;c++)
	{
		configuration+=cleanConfigString("F"+QString::number(c+1),pref.functions[c]);
	}
	for(int c=0; c<20;c++)
	{
		configuration+="F";
		configuration+=QString::number(c+1);
		configuration+="ACTIVE=";
		if(pref.activeFunctions[c])
			configuration+="true\n";
		else configuration+="false\n";
	}
	for(int c=0; c<20;c++)
	{
		configuration+="F";
		configuration+=QString::number(c+1);
		configuration+="DYNAMIC=";
		if(pref.dynamicFunctions[c])
			configuration+="true\n";
		else configuration+="false\n";
	}
	for(int c=0; c<20;c++)
	{
		configuration+="F";
		configuration+=QString::number(c+1);
		configuration+="COLOR=";
		configuration+=getColorName(pref.functionColors[c]);
		configuration+="\n";
	}
	for(int c=0; c<20;c++)
	{
		configuration+="F";
		configuration+=QString::number(c+1);
		configuration+="TYPE=";
		switch(pref.functionTypes[c])
		{
			case GRAPHPOLAR:
				configuration+="polar";
				break;
			case GRAPHPARAMETER:
				configuration+="parameter";
				break;
			case GRAPH3D:
				configuration+="3d";
				break;
			case GRAPHIEL:
				configuration+="iel";
				break;
			case GRAPHIELE:
				configuration+="iele";
				break;
			case GRAPHIEG:
				configuration+="ieg";
				break;
			case GRAPHIEGE:
				configuration+="iege";
				break;
			default:
				configuration+="std";

		}
		configuration+="\n";
	}
	
	fwrite(configuration,configuration.length(),1,configFile);
	fclose(configFile);
}


void MainObject::tabChangeSlot(QWidget*activeWidget)
{
	if(activeWidget==(QWidget*)calculator || activeWidget==(QWidget*)calculator2 || activeWidget==(QWidget*)scripting || activeWidget==(QWidget*)scriptIO)
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,false);
	}
	else if(activeWidget==(QWidget*)graph)
	{
		mainMenu->setItemVisible(GRAPH,true);
		mainMenu->setItemVisible(TABLE,false);
	}
	else if(activeWidget==(QWidget*)table)
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,true);
	}
	
	if(activeWidget!=(QWidget*)calculator && activeWidget!=(QWidget*)calculator2)
	{
		if(calcFocus)
		{
			calcFocus=false;
			if(pref.calcType == BASE)
			{
				pref.calcType=SCIENTIFIC;
				getPref(pref);
				calcModeChanged=true;
			}
		}
	}
	else {
		calcFocus=true;
		if(calcModeChanged)
		{
			pref.calcType=BASE;
			getPref(pref);
			calcModeChanged=false;
		}
		
	}
	
}

void MainObject::angleMenuSlot(int type)
{
	pref.angle=type;
	getPref(pref);
}

void MainObject::outputMenuSlot(int item)
{
	pref.outputType=item;
	getPref(pref);
}

void MainObject::calcTypeMenuSlot(int item)
{
	if(calcFocus || item==SCIENTIFIC)
	{
		pref.calcType=item;
		getPref(pref);
	}
}
void MainObject::baseMenuSlot(int item)
{
	if(pref.calcType==BASE)
	{
		pref.base=item;
		getPref(pref);
	}
}

void MainObject::floatPointMenuSlot(int item)
{
	pref.outputLength=item;
	getPref(pref);
}

void MainObject::helpMenuSlot(int item)
{
	switch(item)
	{
	case EXTHELP:
		helpProcess->clearArguments();
		helpProcess->addArgument("konqueror");
#ifdef LANGUAGE_DE
		helpProcess->addArgument(QString(INSTALLDIR)+"/doc/help_de.html");
#endif
#ifdef LANGUAGE_EN
		helpProcess->addArgument(QString(INSTALLDIR)+"/doc/help_en.html");
#endif
		helpProcess->start();
		break;
	case INFO:
		infoDialog->exec();
		break;
	}	
} 

void MainObject::coordinateMenuSlot(int item)
{
	switch(item)
	{
	case SHOWAXES:
		pref.axis=!pref.axis;
		break;
	case SHOWLABELS:
		pref.label=!pref.label;
		break;
	case SHOWRASTER:
		pref.raster=!pref.raster;
		break;
	case CONSTRATIO:
		pref.autosize=!pref.autosize;
		break;
	case STANDARDCOORDS:
		pref.xmin=pref.ymin=pref.zmin=-10.0;
		pref.xmax=pref.ymax=pref.zmax=10.0;
		pref.rasterSizeX=pref.rasterSizeY=pref.rasterSizeZ=1.0;
		pref.radiusMax=10.0;
		pref.rasterSizeRadius=1.0;
		pref.parameterStart=0.0;
		pref.parameterEnd=10.0;
		if(pref.angle==GRA)
		{
			pref.angleMax=400.0;
			pref.rasterSizeAngle=20.0;
		}
		else if(pref.angle==RAD)
		{
			pref.angleMax=2.0*PI;
			pref.rasterSizeAngle=PI/10.0;
		} 
		else
		{
			pref.angleMax=360.0;
			pref.rasterSizeAngle=15.0;
		} 
		break;
	case TRIGONOMETRICCOORDS:
		pref.parameterStart=0.0;
		pref.parameterEnd=10.0;
		switch(pref.angle)
		{
		case DEG:
			pref.xmin=pref.zmin=-360;
			pref.ymin=-2;
			pref.xmax=pref.zmax=360;
			pref.ymax=2;
			pref.rasterSizeX=pref.rasterSizeZ=90;
			pref.rasterSizeY=0.5;
			pref.radiusMax=10.0;
			pref.rasterSizeRadius=1.0;
			pref.angleMax=360.0;
			pref.rasterSizeAngle=15.0;
			break;
		case RAD:
			pref.xmin=pref.zmin=-2*PI;
			pref.ymin=-2;
			pref.xmax=pref.zmax=2*PI;
			pref.ymax=2;
			pref.rasterSizeX=pref.rasterSizeZ=PI/2;
			pref.rasterSizeY=0.5;
			pref.radiusMax=10.0;
			pref.rasterSizeRadius=1.0;
			pref.angleMax=2.0*PI;
			pref.rasterSizeAngle=PI/10.0;
			break;
		case GRA:
			pref.xmin=pref.zmin=-400;
			pref.ymin=-2;
			pref.xmax=pref.zmax=400;
			pref.ymax=2;
			pref.rasterSizeX=pref.rasterSizeZ=100;
			pref.rasterSizeY=0.5;
			pref.radiusMax=10.0;
			pref.rasterSizeRadius=1.0;
			pref.angleMax=400.0;
			pref.rasterSizeAngle=20.0;
			break;
		}
		break;
	}
	getPref(pref);
}
void MainObject::graphTypeMenuSlot(int item)
{
	pref.graphType=item;
	getPref(pref);
}

void MainObject::tableMenuSlot(int item)
{
	
	if(item==STANDARDTABLE)
	{
		pref.tableXStart=0;
		pref.tableXEnd=10;
		pref.tableZStart=0;
		pref.tableZEnd=10;
		pref.tableXSteps=11;
		pref.tableZSteps=11;
		pref.tableType=TABLENORMAL;
		getPref(pref);
	}
}
void MainObject::tableTypeMenuSlot(int item)
{

	pref.tableType=item;
	getPref(pref);	

}

void MainObject::prefMenuSlot(int item)
{
	switch(item)
	{
		case GPREF:
			if(grPref != NULL)
				delete grPref;
			grPref=new GraphPreferences(pref,(QWidget*)this);
			QObject::connect(grPref,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));

			grPref->show();
			break;
		case CPREF:
			if(calcPref != NULL)
				delete calcPref;
			calcPref=new CalcPreferences(pref,(QWidget*)this);
			QObject::connect(calcPref,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));

			calcPref->show();
			break;
		case TPREF:
			if(tablePref != NULL)
				delete tablePref;
			tablePref=new TablePreferences(pref,(QWidget*)this);
			QObject::connect(tablePref,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));

			tablePref->show();
			break;
		case SPREF:
			if(scriptPref != NULL)
				delete scriptPref;
			scriptPref=new ScriptPreferences(pref,(QWidget*)this);
			QObject::connect(scriptPref,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			
			scriptPref->show();
			break;
	}
}

void MainObject::fileMenuSlot(int item)
{
	
	if(item==QUIT)
		qApp->quit();
}

void MainObject::editMenuSlot(int item)
{
	emit editSignal(item);
}

void MainObject::viewMenuSlot(int item)
{

	bool resetFocus=false;

	
	switch(item)
	{
		case VIEWCALC1:
			pref.showWindows[0]=!pref.showWindows[0];
			getPref(pref);
			if(pref.showWindows[0])
				showPage(calculator);
			else {
				
				resetFocus=true;
				calculator->hide();
			}
			break;
		case VIEWCALC2:
			pref.showWindows[1]=!pref.showWindows[1];
			getPref(pref);
			if(pref.showWindows[1])
				showPage(calculator2);
			else {
				resetFocus=true;
				calculator2->hide();
			}
			break;
		case VIEWGRAPH:
			pref.showWindows[2]=!pref.showWindows[2];
			getPref(pref);
			if(pref.showWindows[2])
				showPage(graph);
			else {
				resetFocus=true;
				graph->hide();
			}
			break;
		case VIEWTABLE:
			pref.showWindows[3]=!pref.showWindows[3];
			getPref(pref);
			if(pref.showWindows[3])
				showPage(table);
			else {
				resetFocus=true;
				table->hide();
			}
			break;
		case VIEWSCRIPTING:
			pref.showWindows[4]=!pref.showWindows[4];
			getPref(pref);
			if(pref.showWindows[4])
				showPage(scripting);
			else {
				resetFocus=true;
				scripting->hide();
			}
			break;
		case VIEWSCRIPTIO:
			pref.showWindows[5]=!pref.showWindows[5];
			getPref(pref);
			if(pref.showWindows[5])
				showPage(scriptIO);
			else {
				resetFocus=true;
				scriptIO->hide();
			}
			break;
	}
	
	if(resetFocus)
	{
		if(indexOf(calculator)!=-1)
			showPage(calculator);
		else if(indexOf(calculator2)!=-1)
			showPage(calculator2);
		else if(indexOf(table)!=-1)
			showPage(table);
		else if(indexOf(graph)!=-1)
			showPage(graph);
		else if(indexOf(scripting)!=-1)
			showPage(scripting);
		else if(indexOf(scriptIO)!=-1)
			showPage(scriptIO);
	}
	
}

void MainObject::runScriptSlot(QString*)
{
	if(indexOf(scriptIO) == -1)
		viewMenuSlot(VIEWSCRIPTIO);
	else showPage(scriptIO);
}


