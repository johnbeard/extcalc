/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         extcalc.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "extcalc.h"
//Added by qt3to4:
#include <QResizeEvent>
#include <QPixmap>
#include <QCloseEvent>
#include <QTranslator>
#include <QCustomEvent>


MainObject *mainObj;


int main( int argc, char **argv ) {

	int language=LANG_EN;
	struct stat fileStat;
	QTranslator trans(NULL),qtTrans(NULL);
	chdir(getenv("HOME"));
	if(lstat(CONFIGFILE,&fileStat) == 0)
	{
		FILE*configFile = fopen(CONFIGFILE,"r");
		if(configFile != NULL)
		{
			char* cConfFile = new char[fileStat.st_size+1];
			fread((void*)cConfFile,fileStat.st_size,1,configFile);
			cConfFile[fileStat.st_size]=(char)0;
			QString confFile(cConfFile);

			QString sLang=getConfigString(&confFile,"LANGUAGE");
			if(sLang.lower()=="de")
				language=LANG_DE;
			else if(sLang.lower()=="fr")
				language=LANG_FR;
			delete[]cConfFile;
			fclose(configFile);
		}
	}

  Q_INIT_RESOURCE(icons);

	QApplication a( argc, argv );
	
	if(language==LANG_DE)
	{
		if(trans.load("data/german.qm",INSTALLDIR))
			a.installTranslator(&trans);
		else MessageBox("Extcalc-Sprachpaket konnte nicht geladen werden");
		
		if(qtTrans.load("data/qt_de.qm",INSTALLDIR))
			a.installTranslator(&qtTrans);
		else MessageBox("QT-Sprachpaket konnte nicht geladen werden");
	}
	else if(language==LANG_FR)
	{
		if(trans.load("data/french.qm",INSTALLDIR))
			a.installTranslator(&trans);
		else MessageBox("Error loading Extcalc language file");
		
		if(qtTrans.load("data/qt_fr.qm",INSTALLDIR))
			a.installTranslator(&qtTrans);
		else MessageBox("Error loading Qt language file");
	}

	MainObject * mainObject = new MainObject;
	mainObj=mainObject;

	setlocale(LC_NUMERIC,"C");	//use . for floating point values in every language

	a.setMainWidget(mainObj);
	mainObj->show();
	return a.exec();
}


MainObject::MainObject() :QMainWindow()
{
  helpBrowser=NULL;
  graphsDir=NULL;
  QAction *tmpAction;
  vars=new Variable [27];
  for(int c=0; c<27;c++)
    vars[c]=0.0;
  Number n0;
  n0.type=NFLOAT;
  vecs=new Vector [VARNUM];
  for(int c=0; c<VARNUM;c++)
    vecs[c].NewItem(n0);

   lastTab=NULL;
    
  appIcon=new QPixmap(QString(INSTALLDIR)+"/data/icon22.png");
  if(!appIcon->isNull())
    setIcon(*appIcon);
    
  calcFocus=true;
  calcModeChanged=false;
    
  struct timeval rndTime;
  gettimeofday(&rndTime,NULL);
  srand(rndTime.tv_usec*rndTime.tv_sec);
    
  setGeometry(10,10,640,630); 
  setMinimumWidth(640);
  setMinimumHeight(400);
  setDockNestingEnabled(true);
  helpProcess=new Q3Process(this);
    
  infoDialog=new InfoDialog(this);

  grPref=NULL;
  calcPref=NULL;
  tablePref=NULL;
  scriptPref=NULL;
  importDialog=NULL;
  exportDialog=NULL;
  functionDialog=NULL;
  graphSetDialog=NULL;



  mainMenu=menuBar();
//  toolBar=this->tols

//standard preferences
#ifndef NO_LONG_DOUBLE
  pref.precision=LDBL_DIG;
#else 
  pref.precision=DBL_DIG;
#endif
  pref.angle=DEG;
  pref.outputType=VARIABLENUM;
  pref.outputLength=10;
  pref.shift=false;
  pref.alpha=false;
  pref.hyp=false;
  pref.raster=true;
  pref.axis=true;
  pref.label=false;
  pref.complex=false;
  pref.clearScriptMemory=true;
  pref.functions=NULL;
  pref.functionComments=NULL;
  pref.activeFunctions=new bool[20];
  for(int c=0; c<20;c++)
    pref.activeFunctions[c]=false;
  pref.functionColors=new QColor[20];
  for(int c=0; c<20; c++)
    pref.functionColors[c]=QColor(0,0,0);
  pref.functionTypes=new int[20];
  for(int c=0; c<20; c++)
    pref.functionTypes[c]=GRAPHSTD;
  pref.dynamicFunctions=new bool[20];
  for(int c=0; c<20; c++)
    pref.dynamicFunctions[c]=false;
  pref.logicFunctions=new bool[20];
  for(int c=0; c<20; c++)
    pref.logicFunctions[c]=false;
  pref.xmin=pref.ymin=pref.zmin=-10.0;
  pref.xmax=pref.ymax=pref.zmax=10.0;
  pref.rasterSizeX=pref.rasterSizeY=pref.rasterSizeZ=1.0;
  pref.rasterSizeRadius=1.0;
  pref.rasterSizeAngle=10.0;
  pref.radiusMax=10.0;
  pref.angleMax=360.0;
  pref.parameterStart=0.0;
  pref.parameterEnd=10.0;
  pref.parameterSteps=400;
  pref.graphType=GRAPHSTD;
  pref.calcType=SCIENTIFIC;
  pref.base=DEC;
  pref.dynamicStart=0.0;
  pref.dynamicEnd=10.0;
  pref.nyquistStart=-3.0;
  pref.nyquistEnd=3.0;
  pref.nyquistSteps=400;
  pref.prec2dSteps=400;
  pref.prec3dSteps=50;
  pref.solvePrec=1;
  pref.show3dGrid=true;
  pref.logNyquistSteps=true;
  pref.dynamicSteps=10;
  pref.dynamicDelay=1;
  pref.moveUpDown=false;
  pref.tableXStart=pref.tableZStart=0.0;
  pref.tableXEnd=pref.tableZEnd=10.0;
  pref.tableAValue=0.0;
  pref.tableXSteps=pref.tableZSteps=10;
  pref.tableType=TABLENORMAL;
  pref.statAutoClear=true;
  pref.showStatLines=false;
  pref.showStatPoints=true;
  pref.showWindows[0]=pref.showWindows[2]=pref.showWindows[3]=pref.showWindows[4]=pref.showWindows[6]=true;
  pref.showWindows[1]=pref.showWindows[5]=pref.showWindows[7]=false;
  pref.language=LANG_EN;
  pref.constList=NULL;
  pref.constLen=pref.userConstLen=0;


  threadData=new ThreadSync;
  threadData->mutex=NULL;
  threadData->eventReciver=this;
  threadData->status=0;
  threadData->eventCount=0;
  threadData->exit=false;
  threadData->usleep=false;
  threadData->bbreak=false;
  threadData->bcontinue=false;
  threadData->calcMode=true;
  threadData->data=NULL;
  threadData->sleepTime=1000;
  threadData->vars=new Number*[VARNUM];
  for(int c=0; c<VARNUM;c++)
  {
    threadData->vars[c]=(Number*)malloc(sizeof(Number));
    threadData->numlen[c]=1;
    threadData->vars[c][0].type=NNONE;
    threadData->vars[c][0].cval=NULL;
    threadData->vars[c][0].fval=Complex(0.0,0.0);
    for(int c1=0; c1<VARDIMENSIONS; c1++)
      threadData->dimension[c][c1]=1;
  }

  angleMapper=new QSignalMapper(this);
  angleMenu=new QMenu(this);
  angleActions=new QActionGroup(this);
  tmpAction=angleMenu->addAction("DEG");
  tmpAction->setData(QVariant(DEG));
  tmpAction->setCheckable(true);
  angleActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),angleMapper,SLOT(map()));
  angleMapper->setMapping(tmpAction,DEG);
  tmpAction=angleMenu->addAction("RAD");
  tmpAction->setCheckable(true);
  tmpAction->setData(QVariant(RAD));
  angleActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),angleMapper,SLOT(map()));
  angleMapper->setMapping(tmpAction,RAD);
  tmpAction=angleMenu->addAction("GRA");
  tmpAction->setCheckable(true);
  tmpAction->setData(QVariant(GRA));
  angleActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),angleMapper,SLOT(map()));
  angleMapper->setMapping(tmpAction,GRA);
  QObject::connect(angleMapper,SIGNAL(mapped(int)),this,SLOT(angleMenuSlot(int)));

  floatPointMapper=new QSignalMapper(this);
  floatPointMenu=new QMenu("Number of digits",this);
  floatPointActions=new QActionGroup(this);
  for(int c=2;c<=pref.precision; c++)
  {
    tmpAction=floatPointMenu->addAction(QString::number(c));
	tmpAction->setData(QVariant(c));
	tmpAction->setCheckable(true);
	floatPointActions->addAction(tmpAction);
	connect(tmpAction,SIGNAL(triggered()),floatPointMapper,SLOT(map()));
	floatPointMapper->setMapping(tmpAction,c);
  }
  QObject::connect(floatPointMapper,SIGNAL(mapped(int)),this,SLOT(floatPointMenuSlot(int)));

  outputMapper=new QSignalMapper(this);
  outputMenu=new QMenu(this);
  outputActions=new QActionGroup(this);
  tmpAction=outputMenu->addAction("Fixed number of digits");
  tmpAction->setData(QVariant(FIXEDNUM));
  tmpAction->setCheckable(true);
  outputActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),outputMapper,SLOT(map()));
  outputMapper->setMapping(tmpAction,FIXEDNUM);
  tmpAction=outputMenu->addAction("Variable number of digits");
  tmpAction->setData(QVariant(VARIABLENUM));
  tmpAction->setCheckable(true);
  outputActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),outputMapper,SLOT(map()));
  outputMapper->setMapping(tmpAction,VARIABLENUM);
  tmpAction=outputMenu->addAction("With symbol");
  tmpAction->setData(QVariant(EXPSYM));
  tmpAction->setCheckable(true);
  outputActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),outputMapper,SLOT(map()));
  outputMapper->setMapping(tmpAction,EXPSYM);
  QObject::connect(outputMapper,SIGNAL(mapped(int)),this,SLOT(outputMenuSlot(int)));
  outputMenu->addMenu(floatPointMenu);

  baseMapper=new QSignalMapper(this);
  baseMenu=new QMenu(this);
  baseActions=new QActionGroup(this);
  
  tmpAction=baseMenu->addAction(tr("Binary (BIN)"));
  tmpAction->setData(QVariant(BIN));
  tmpAction->setCheckable(true);
  baseActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),baseMapper,SLOT(map()));
  baseMapper->setMapping(tmpAction,BIN);
  
  tmpAction=baseMenu->addAction(tr("Octal (OCT)"));
  tmpAction->setData(QVariant(OCT));
  tmpAction->setCheckable(true);
  baseActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),baseMapper,SLOT(map()));
  baseMapper->setMapping(tmpAction,OCT);
  
  tmpAction=baseMenu->addAction(tr("Decimal (DEC)"));
  tmpAction->setData(QVariant(DEC));
  tmpAction->setCheckable(true);
  baseActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),baseMapper,SLOT(map()));
  baseMapper->setMapping(tmpAction,DEC);
  
  tmpAction=baseMenu->addAction(tr("Hexadecimal (HEX)"));
  tmpAction->setData(QVariant(HEX));
  tmpAction->setCheckable(true);
  baseActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),baseMapper,SLOT(map()));
  baseMapper->setMapping(tmpAction,HEX);
  
  QObject::connect(outputMapper,SIGNAL(mapped(int)),this,SLOT(baseMenuSlot(int)));
    
  calcModeMenu=new QMenu(this);
  calcModeActions=new QActionGroup(this);
  calcModeMapper=new QSignalMapper(this);
  tmpAction=calcModeMenu->addAction(tr("Scientific"));
  tmpAction->setData(QVariant(SCIENTIFIC));
  tmpAction->setCheckable(true);
  calcModeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),calcModeMapper,SLOT(map()));
  calcModeMapper->setMapping(tmpAction,SCIENTIFIC);
  tmpAction=calcModeMenu->addAction(tr("Base"));
  tmpAction->setData(QVariant(BASE));
  tmpAction->setCheckable(true);
  calcModeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),calcModeMapper,SLOT(map()));
  calcModeMapper->setMapping(tmpAction,BASE);
  QObject::connect(calcModeMapper,SIGNAL(mapped(int)),this,SLOT(calcModeMenuSlot(int)));

  complexAction=calcModeMenu->addAction(tr("Complex"));
  QObject::connect(complexAction,SIGNAL(triggered()),this,SLOT(calcComplexSlot()));

  calcModeMenu->insertItem(EXTCALCH_MENU67,COMPLEXMENU);
  calcModeMenu->insertItem(EXTCALCH_MENU33,baseMenu,BASEMENU);
//  QObject::connect(calcTypeMenu,SIGNAL(activated(int)),this,SLOT(calcTypeMenuSlot(int)));
  baseMenu->setItemChecked(pref.base,true);


  calcMenu=new Q3PopupMenu;
  calcMenu->insertItem(EXTCALCH_MENU8,angleMenu,ANGLE);
  calcMenu->insertItem(EXTCALCH_MENU9,outputMenu,OUTPUT);
  calcMenu->insertItem(EXTCALCH_MENU34,calcModeMenu,MODE);
//  angleMenu->setItemChecked(pref.angle,true);
//  outputMenu->setItemChecked(pref.outputType,true);
//  calcTypeMenu->setItemChecked(pref.calcType,true);
    
  coordinateMenu=new Q3PopupMenu;
  coordinateMenu->insertItem(EXTCALCH_MENU19,STANDARDCOORDS);
  coordinateMenu->insertItem(EXTCALCH_MENU20,TRIGONOMETRICCOORDS);
  coordinateMenu->insertItem(EXTCALCH_MENU21,SHOWAXES);
  coordinateMenu->insertItem(EXTCALCH_MENU22,SHOWLABELS);
  coordinateMenu->insertItem(EXTCALCH_MENU23,SHOWRASTER);
  coordinateMenu->insertItem(EXTCALCH_MENU24,CONSTRATIO);
  QObject::connect(coordinateMenu,SIGNAL(activated(int)),this,SLOT(coordinateMenuSlot(int)));


  graphTypeMenu=new QMenu(this);
  graphTypeActions=new QActionGroup(this);
  graphTypeMapper=new QSignalMapper(this);

  tmpAction=graphTypeMenu->addAction(tr("Standard"));
  tmpAction->setData(QVariant(GRAPHSTD));
  tmpAction->setCheckable(true);
  graphTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),graphTypeMapper,SLOT(map()));
  graphTypeMapper->setMapping(tmpAction,GRAPHSTD);
  
  tmpAction=graphTypeMenu->addAction(tr("Polar"));
  tmpAction->setData(QVariant(GRAPHPOLAR));
  tmpAction->setCheckable(true);
  graphTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),graphTypeMapper,SLOT(map()));
  graphTypeMapper->setMapping(tmpAction,GRAPHPOLAR);
  
  tmpAction=graphTypeMenu->addAction(tr("3D-Graph"));
  tmpAction->setData(QVariant(GRAPH3D));
  tmpAction->setCheckable(true);
  graphTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),graphTypeMapper,SLOT(map()));
  graphTypeMapper->setMapping(tmpAction,GRAPH3D);

  QObject::connect(graphTypeMapper,SIGNAL(mapped(int)),this,SLOT(graphTypeMenuSlot(int)));

  
  graphSetMenu=new QMenu(this);
  graphSetMapper=new QSignalMapper(this);
  graphSetActions=new QActionGroup(this);
  QObject::connect(graphSetMapper,SIGNAL(mapped(int)),this,SLOT(graphSetMenuSlot(int))); 
    
  graphMenu=new Q3PopupMenu;
  graphMenu->insertItem(EXTCALCH_MENU25,coordinateMenu,COORDINATE);
  graphMenu->insertItem(EXTCALCH_MENU26,graphTypeMenu,GRAPHTYPE);
  graphMenu->insertSeparator();
  graphMenu->insertItem(tr("Choose Current Set"),graphSetMenu,GRAPHSETCH);
  graphMenu->insertItem(tr("Manage Sets"),GRAPHSETMANAGE);
  graphMenu->insertItem(tr("Save Current Set As"),GRAPHSAVECURR);
  graphMenu->insertItem(tr("Create New Set"),GRAPHCREATESET);
  graphMenu->insertItem(tr("Import Graphs"),GRAPHIMPORT);
  graphMenu->insertItem(tr("Export Graphs"),GRAPHEXPORT);
  QObject::connect(graphMenu,SIGNAL(activated(int)),this,SLOT(graphMenuSlot(int)));

  
  tableTypeMenu=new QMenu(this);
  tableTypeActions=new QActionGroup(this);
  tableTypeMapper=new QSignalMapper(this);
  
  tmpAction=tableTypeMenu->addAction(tr("Normal"));
  tmpAction->setData(QVariant(TABLENORMAL));
  tmpAction->setCheckable(true);
  tableTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),tableTypeMapper,SLOT(map()));
  tableTypeMapper->setMapping(tmpAction,TABLENORMAL);
  
  tmpAction=tableTypeMenu->addAction(tr("Polar"));
  tmpAction->setData(QVariant(TABLEPOLAR));
  tmpAction->setCheckable(true);
  tableTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),tableTypeMapper,SLOT(map()));
  tableTypeMapper->setMapping(tmpAction,TABLEPOLAR);
    
  tmpAction=tableTypeMenu->addAction(tr("Parameter"));
  tmpAction->setData(QVariant(TABLEPARAMETER));
  tmpAction->setCheckable(true);
  tableTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),tableTypeMapper,SLOT(map()));
  tableTypeMapper->setMapping(tmpAction,TABLEPARAMETER);
    
  tmpAction=tableTypeMenu->addAction(tr("Inequality"));
  tmpAction->setData(QVariant(TABLEINEQUALITY));
  tmpAction->setCheckable(true);
  tableTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),tableTypeMapper,SLOT(map()));
  tableTypeMapper->setMapping(tmpAction,TABLEINEQUALITY);
    
  tmpAction=tableTypeMenu->addAction(tr("3D"));
  tmpAction->setData(QVariant(TABLE3D));
  tmpAction->setCheckable(true);
  tableTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),tableTypeMapper,SLOT(map()));
  tableTypeMapper->setMapping(tmpAction,TABLE3D);
    
  tmpAction=tableTypeMenu->addAction(tr("Complex"));
  tmpAction->setData(QVariant(TABLECOMPLEX));
  tmpAction->setCheckable(true);
  tableTypeActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),tableTypeMapper,SLOT(map()));
  tableTypeMapper->setMapping(tmpAction,TABLECOMPLEX);

  QObject::connect(tableTypeMapper,SIGNAL(mapped(int)),this,SLOT(tableTypeMenuSlot(int)));
    
  tableMenu=new Q3PopupMenu;
  tableMenu->insertItem(EXTCALCH_MENU43,STANDARDTABLE);
  tableMenu->insertItem(EXTCALCH_MENU68,RESETTABLE);
  tableMenu->insertItem(EXTCALCH_MENU44,tableTypeMenu,TABLETYPE);
  QObject::connect(tableMenu,SIGNAL(activated(int)),this,SLOT(tableMenuSlot(int)));


  scriptMenu=new Q3PopupMenu;
  scriptMenu->insertItem(EXTCALCH_MENU62,EXPORTSCRIPT);
  scriptMenu->insertItem(EXTCALCH_MENU63,IMPORTSCRIPT);
  scriptMenu->insertSeparator();
  scriptMenu->insertItem(EXTCALCH_MENU64,CLEARMEMALWAYS);
  scriptMenu->insertItem(EXTCALCH_MENU65,CLEARMEMNOW);
  QObject::connect(scriptMenu,SIGNAL(activated(int)),this,SLOT(scriptMenuSlot(int)));
    
  statisticsMenu=new Q3PopupMenu;
  statisticsMenu->insertItem(EXTCALCH_MENU69,STATCLEAR);
  statisticsMenu->insertItem(EXTCALCH_MENU70,STATAUTOCLEAR);
  statisticsMenu->insertSeparator();
  statisticsMenu->insertItem(EXTCALCH_MENU71,STATPOINTS);
  statisticsMenu->insertItem(EXTCALCH_MENU72,STATLINES);
  QObject::connect(statisticsMenu,SIGNAL(activated(int)),this,SLOT(statisticsMenuSlot(int)));
    
  languageMenu=new QMenu(this);
  languageActions=new QActionGroup(this);
  languageMapper=new QSignalMapper(this);
  
  tmpAction=languageMenu->addAction(tr("English"));
  tmpAction->setData(QVariant(LANG_EN));
  tmpAction->setCheckable(true);
  languageActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),languageMapper,SLOT(map()));
  languageMapper->setMapping(tmpAction,LANG_EN);
  
  tmpAction=languageMenu->addAction(tr("French"));
  tmpAction->setData(QVariant(LANG_FR));
  tmpAction->setCheckable(true);
  languageActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),languageMapper,SLOT(map()));
  languageMapper->setMapping(tmpAction,LANG_FR);
  
  tmpAction=languageMenu->addAction(tr("German"));
  tmpAction->setData(QVariant(LANG_DE));
  tmpAction->setCheckable(true);
  languageActions->addAction(tmpAction);
  connect(tmpAction,SIGNAL(triggered()),languageMapper,SLOT(map()));
  languageMapper->setMapping(tmpAction,LANG_DE);
  
  QObject::connect(languageMapper,SIGNAL(mapped(int)),this,SLOT(languageMenuSlot(int)));



  prefMenu=new Q3PopupMenu;
  prefMenu->insertItem(EXTCALCH_MENU10,CPREF);
  prefMenu->insertItem(EXTCALCH_MENU11,GPREF);
  prefMenu->insertItem(EXTCALCH_MENU45,TPREF);
  prefMenu->insertItem(EXTCALCH_MENU60,SPREF);
  prefMenu->insertSeparator();
  prefMenu->insertItem(tr("Language"),languageMenu,LPREF);

  helpMenu=new Q3PopupMenu;
  helpMenu->insertItem(EXTCALCH_MENU12,EXTHELP);
  helpMenu->insertItem(EXTCALCH_MENU13,INFO);

  editMapper=new QSignalMapper(this);
  editMenu=new QMenu(this);
  tmpAction=editMenu->addAction("Undo");
  connect(tmpAction,SIGNAL(triggered()),editMapper,SLOT(map()));
  editMapper->setMapping(tmpAction,EDITUNDO);
  tmpAction=editMenu->addAction("Redo");
  connect(tmpAction,SIGNAL(triggered()),editMapper,SLOT(map()));
  editMapper->setMapping(tmpAction,EDITREDO);
  tmpAction=editMenu->addAction("Cut");
  connect(tmpAction,SIGNAL(triggered()),editMapper,SLOT(map()));
  editMapper->setMapping(tmpAction,EDITCUT);
  tmpAction=editMenu->addAction("Copy");
  connect(tmpAction,SIGNAL(triggered()),editMapper,SLOT(map()));
  editMapper->setMapping(tmpAction,EDITCOPY);
  tmpAction=editMenu->addAction("Paste");
  connect(tmpAction,SIGNAL(triggered()),editMapper,SLOT(map()));
  editMapper->setMapping(tmpAction,EDITPASTE);
  QObject::connect(editMapper,SIGNAL(mapped(int)),this,SLOT(editMenuSlot(int)));

  viewMenu=new Q3PopupMenu;
  viewMenu->insertItem(EXTCALCH_MENU52,VIEWCALC1);
  viewMenu->insertItem(EXTCALCH_MENU53,VIEWCALC2);
  viewMenu->insertItem(EXTCALCH_MENU54,VIEWGRAPH);
  viewMenu->insertItem(EXTCALCH_MENU55,VIEWTABLE);
  viewMenu->insertItem(EXTCALCH_MENU73,VIEWMATRIX);
  viewMenu->insertItem(EXTCALCH_MENU74,VIEWSTATISTICS);
  viewMenu->insertItem(EXTCALCH_MENU56,VIEWSCRIPTING);
  viewMenu->insertItem(EXTCALCH_MENU61,VIEWSCRIPTIO);
  QObject::connect(viewMenu,SIGNAL(activated(int)),this,SLOT(viewMenuSlot(int)));
    
  fileMenu=new Q3PopupMenu;
  fileMenu->insertItem(EXTCALCH_MENU57,QUIT);
  QObject::connect(fileMenu,SIGNAL(activated(int)),this,SLOT(fileMenuSlot(int)));
    


  mainMenu->insertItem(EXTCALCH_MENU14,fileMenu,FILEM);
  mainMenu->insertItem(EXTCALCH_MENU58,editMenu,EDIT);
  mainMenu->insertItem(EXTCALCH_MENU59,viewMenu,VIEW);
  mainMenu->insertItem(EXTCALCH_MENU15,prefMenu,PREFERENCES);
  mainMenu->insertItem(EXTCALCH_MENU16,calcMenu,CALCULATOR);
  mainMenu->insertItem(EXTCALCH_MENU17,graphMenu,GRAPH);
  mainMenu->insertItem(EXTCALCH_MENU46,tableMenu,TABLE);
  mainMenu->insertItem(EXTCALCH_MENU66,scriptMenu,SCRIPTM);
  mainMenu->insertItem(EXTCALCH_MENU74,statisticsMenu,STATISTICSM);
  mainMenu->insertItem(EXTCALCH_MENU18,helpMenu,HELP);

  clientArea=new QTabWidget(this);
  setCentralWidget(clientArea);

  screenshotDialog=new ScreenshotDialog(this);
  addDockWidget(Qt::BottomDockWidgetArea,screenshotDialog,Qt::Horizontal);
  screenshotDialog->setFloating(false);
  screenshotDialog->hide();

  calcButtons=new StandardButtons(this);
  addDockWidget(Qt::BottomDockWidgetArea,calcButtons,Qt::Horizontal);
  calcButtons->setFloating(false);
  calcButtons->show();

  extButtons=new ExtButtons(this);
  addDockWidget(Qt::BottomDockWidgetArea,extButtons,Qt::Horizontal);
  extButtons->setFloating(false);
  extButtons->show();

  toolWidgets.append(calcButtons);
  toolWidgets.append(extButtons);
  toolWidgets.append(screenshotDialog);

  calculator=new CalcWidget(clientArea,pref,vars,threadData,calcButtons,extButtons);
  calculator2=new CalcWidget(clientArea,pref,vars,threadData,calcButtons,extButtons);
  graph = new GraphWidget(clientArea,pref,vars,threadData,screenshotDialog,calcButtons,extButtons);
  table=new TableWidget(clientArea,pref,vars,threadData,calcButtons,extButtons);
  scripting=new ScriptWidget(clientArea,pref,vars,calcButtons,extButtons);
  scriptIO=new ScriptIOWidget(clientArea,pref,vars,graph->getShareContext(),calcButtons,extButtons);
  matrix=new MatrixWidget(clientArea,pref,vars,threadData,calcButtons,extButtons);
  statistics=new StatisticsWidget(clientArea,pref,vars,threadData,calcButtons,extButtons);

  addToolBar(graph->getToolBar());
  addToolBar(calculator->getToolBar());
  addToolBar(calculator2->getToolBar());
  addToolBar(table->getToolBar());
  addToolBar(matrix->getToolBar());
  addToolBar(statistics->getToolBar());
  addToolBar(scripting->getToolBar());
  addToolBar(scriptIO->getToolBar());
  graph->getToolBar()->hide();
  calculator->getToolBar()->hide();
  calculator2->getToolBar()->hide();
  table->getToolBar()->hide();
  matrix->getToolBar()->hide();
  statistics->getToolBar()->hide();
  scripting->getToolBar()->hide();
  scriptIO->getToolBar()->hide();
  
  




    
  QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(helpMenu,SIGNAL(activated(int)),this,SLOT(helpMenuSlot(int)));
  QObject::connect(prefMenu,SIGNAL(activated(int)),this,SLOT(prefMenuSlot(int)));
  QObject::connect(calculator,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(calculator2,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(graph,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(table,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(scripting,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(scriptIO,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(matrix,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
  QObject::connect(statistics,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));

  QObject::connect(clientArea,SIGNAL(currentChanged(int)),this,SLOT(tabChangeSlot(int)));
  QObject::connect(this,SIGNAL(editSignal(int)),calculator,SLOT(editSlot(int)));
  QObject::connect(this,SIGNAL(editSignal(int)),calculator2,SLOT(editSlot(int)));
  QObject::connect(this,SIGNAL(editSignal(int)),graph,SLOT(editSlot(int)));
  QObject::connect(this,SIGNAL(editSignal(int)),table,SLOT(editSlot(int)));
  QObject::connect(this,SIGNAL(editSignal(int)),scripting,SLOT(editSlot(int)));
  QObject::connect(this,SIGNAL(editSignal(int)),scriptIO,SLOT(editSlot(int)));
  QObject::connect(scripting,SIGNAL(runScript(QString*)),this,SLOT(runScriptSlot(QString*)));
  QObject::connect(scripting,SIGNAL(runScript(QString*)),this,SIGNAL(runScript(QString*)));
  QObject::connect(scripting,SIGNAL(controlScriptMenu(int)),this,SLOT(scriptMenuSlot(int)));
  QObject::connect(this,SIGNAL(runScript(QString*)),scriptIO,SLOT(runScript(QString*)));
  QObject::connect(this,SIGNAL(matrixEnterSignal()),matrix,SLOT(enterSlot()));
  QObject::connect(tableMenu,SIGNAL(activated(int)),table,SLOT(tableMenuSlot(int)));
  QObject::connect(statistics,SIGNAL(printSignal()),graph,SLOT(drawSlot()));
  QObject::connect(statistics,SIGNAL(changeTabSignal(int)),this,SLOT(changeTabSlot(int)));
  QObject::connect(statistics,SIGNAL(drawPointsSignal(long double*,int,bool)),graph,SIGNAL(drawPointsSignal(long double*,int,bool)));
  QObject::connect(statistics,SIGNAL(removeLinesSignal()),graph,SIGNAL(removeLinesSignal()));
  QObject::connect(graph,SIGNAL(statisticsRedrawSignal()),statistics,SLOT(redrawGraphSlot()));
  QObject::connect(this,SIGNAL(removeGraphicsLinesSignal()),graph,SIGNAL(removeLinesSignal()));
  QObject::connect(graphSetMenu,SIGNAL(aboutToShow()),this,SLOT(updateGraphSetMenuSlot()));

    
  clientArea->addTab(calculator,tr("Calculator"));
  clientArea->addTab(calculator2,tr("Another Calculator"));
  clientArea->addTab(graph,tr("Graphics"));
  clientArea->addTab(table,tr("Tables"));
  clientArea->addTab(scripting,tr("Script Editor"));
  clientArea->addTab(scriptIO,tr("Script Console"));
  clientArea->addTab(matrix,tr("Matrix/Vector"));
  clientArea->addTab(statistics,tr("Statistics"));

    
    
  int ret=readConfigFile();
  if(ret==-1 || ret==1)
  {
    if(ret == -1)
    {
            //first start
      ret=YesNoBox(EXTCALCH_MENU75);
    }
    else if(ret==1)
    {
      ret=YesNoBox(EXTCALCH_MENU76);
    }
    pref.scriptPath=QString(getenv("HOME"))+QString("/.extcalc/script/");
    pref.scriptDirName="code";
    pref.dataDirName="data";
    if(ret==0)
    {
      if(scriptPref != NULL)
        delete scriptPref;
      scriptPref=new ScriptPreferences(pref,(QWidget*)this);
      QObject::connect(scriptPref,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
    
      scriptPref->show();
    }
    else 
    {
      if(scriptPref != NULL)
        delete scriptPref;
      scriptPref=new ScriptPreferences(pref,(QWidget*)this);
      QObject::connect(scriptPref,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
      scriptPref->saveSlot();
      MessageBox(EXTCALCH_MENU77);
    }
  }
  initConstants();
  readVarFile();
  readUIState();
  readGraphsDir();
  if(pref.currentSet.length()>0)
    readFunctionFile(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+pref.currentSet);
    
}



void MainObject::closeEvent(QCloseEvent*e)
{
	writeConfigFile();
	writeVarFile();
	writeConstants();
	writeUIState();
	statistics->writeListsFile();
	if(pref.currentSet.length()>0)
		writeFunctionFile(pref.currentSet);
	if(scripting->quitProgram())
	{
		e->accept();
		delete[] pref.functions;
	}
}


void MainObject::customEvent(QCustomEvent*ev)
{

	switch(ev->type())
	{
		case SIGPRINT:	
			free(ev->data());
			break;
		case SIGCLEARTEXT:
			break;
		case SIGGETKEY:
		{

			char*strBuf=new char[2];
			strBuf[1]=(char)0;
			strBuf[0]=(char)0;
			threadData->data=strBuf;
			break;
		}
		case SIGKEYSTATE:
		{
			char*strBuf=new char[1];
			strBuf[0]=(char)0;
			threadData->data=strBuf;
			break;
		}
		case SIGGETLINE:
		{
			char*strBuf=new char[2];
			strBuf[1]=(char)0;
			strBuf[0]=(char)0;
			threadData->data=strBuf;
			break;
		}
		case SIGSETTEXTPOS:
			free(ev->data());
			break;
		case SIGFINISHED:		//script stopped
		{
			break;
		}
		case SIGDEBUG:
		{
/*			errorFlag=true;
			if(!t->isActive())
				t->start(30,true);
			
			int*index=(int*)ev->data();
			if(*index >=semicolonLines.GetLen())
				insert("\nEnd of File            ");
			else 
			{
				if((*index>0) && semicolonLines[*index-1]< semicolonLines[*index]-1)
					insert("\nBefore or in line ");
				else insert("\nIn line           ");
	
				QString lineNum=QString::number(semicolonLines[*index]);
				while(lineNum.length()<5)lineNum.insert(0," ");
	
				insert(lineNum);
			}
			char*text=(char*)ev->data()+4;
			insert(": ");
			insert(text);
			*/
			free(ev->data());
			break;
		}
		default:
		{
			break;
		}
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
			QString file("ANGLE=rad\n\
OUTPUTTYPE=variablenum\n\
OUTPUTLENGTH=15\n\
XMIN=-10\n\
XMAX=10\n\
YMIN=-10\n\
YMAX=10\n\
ZMIN=-10\n\
ZMAX=10\n\
RADIUSMAX=10\n\
ANGLEMAX=6.28319\n\
RASTERSIZEX=1\n\
RASTERSIZEY=1\n\
RASTERSIZEZ=1\n\
RASTERSIZEANGLE=0.314159\n\
RASTERSIZERADIUS=1\n\
NYQUISTSTART=-3\n\
NYQUISTEND=3\n\
PARAMETERSTART=-10\n\
PARAMETEREND=10\n\
PARAMETERSTEPS=400\n\
DYNAMICSTART=0\n\
DYNAMICEND=30\n\
DYNAMICSTEPS=15\n\
DYNAMICDELAY=10\n\
TABLESTARTX=0\n\
TABLEENDX=10\n\
TABLESTARTZ=0\n\
TABLEENDZ=10\n\
TABLESTEPSX=11\n\
TABLESTEPSZ=11\n\
GRAPH2DSTEPS=400\n\
GRAPH3DSTEPS=50\n\
NYQUISTSTEPS=400\n\
ANALYSEPRECISION=1\n\
SCRIPTROOT=%1/.extcalc/script\n\
CODEPATH=code\n\
DATAPATH=data\n\
RASTER=true\n\
AXIS=true\n\
LABEL=true\n\
AUTOSIZE=true\n\
DYNAMICMOVEUPDOWN=false\n\
3DGRID=true\n\
LOGNYQUISTSTEPS=true\n\
GRAPHTYPE=std\n\
CALCTYPE=scientific\n\
COMPLEX=true\n\
CLEARSCRIPTMEM=true\n\
STATSHOWLINES=true\n\
STATSHOWPOINTS=true\n\
STATAUTOCLEAR=true\n\
TABLETYPE=normal\n\
BASE=hex\n\
LANGUAGE=en\n\
SHOWWIN1=true\n\
SHOWWIN2=false\n\
SHOWWIN3=true\n\
SHOWWIN4=true\n\
SHOWWIN5=true\n\
SHOWWIN6=true\n\
SHOWWIN7=true\n\
SHOWWIN8=false\n\
CURRENTSET=std\n\
F1=sinX\n\
F2=(X+5)^2-4\n\
F3=if(A<=10) (1-A/5)*x^2; else if(A<=20) -(x+5*(A-10)/10)^2; else -(x+5)^2-4*(A-20)/10;\n\
F4=\n\
F5=X+2\n\
F6=5*sin(4X)\n\
F7=2/(1+0.7cosX)\n\
F8=\n\
F9=T\\T^2\n\
F10=sinT*(exp(cosT)-2*cos(4T)-(sin(T/12))^5)\\cosT*(exp(cosT)-2*cos(4T)-(sin(T/12))^5)\n\
F11=F=.01*T^3+1;U=1-A/15;((1+U)*T+(1-U)*F)/2\\((1-U)*T+(1+U)*F)/2\n\
F12=(1-A/15)*T\\T^3-5*T^2+5*T-2\n\
F13=F=.05*T^3;if(T>0)U=atan(F/T);elseU=0;R=sqrt(T^2+F^2);cos(pi/30*A+U)*R\\sin(pi/30*A+U)*R\n\
F14=\n\
F15=sin(X^2)*cos(Z^2)\n\
F16=L=0.01;U=2;K=1e-3;if(X<U)0;else{if(Z>0 && Z<X-U)K*Z*(X-U-Z/2)*(1+L*Z);else if (Z>0) K/2*(X-U)^2*(1+L*Z); else 0;}\n\
F17=abs(arg(((X+Zi)^2-1)*((X+Zi)^2-2-i)^2/((X+Zi)^2+2+2i)))\n\
F18=\n\
F19=exp(Z*i)\n\
F20=10/(1+Z*i)\n\
COMMENT1=Sine wave, Coordinate system: trigonometric standard size\n\
COMMENT2=Parabola\n\
COMMENT3=Animated parabola\n\
COMMENT4=\n\
COMMENT5=Archimedian spiral\n\
COMMENT6=Polar rose\n\
COMMENT7=Ellipse\n\
COMMENT8=\n\
COMMENT9=Parabola\n\
COMMENT10=Butterfly curve; Coordinate system: polar, max. radius=5; T from 0 to 20\n\
COMMENT11=Inverse function; T from -10 to 10\n\
COMMENT12=Reflection\n\
COMMENT13=Odd function; T from 0 to 10\n\
COMMENT14=\n\
COMMENT15=X, Y and Z from -3 to 3\n\
COMMENT16=MOSFET transistor current; Coordinate system: X and Z from 0 to 10,Y from -0.01 to 0.04\n\
COMMENT17=Complex graph in 3D (X=Re,Z=Im); Coordinate system: X and Z from -2 to 2,Y from 0 to 5; complex enabled (Calculator)\n\
COMMENT18=\n\
COMMENT19=\n\
COMMENT20=\n\
F1ACTIVE=true\n\
F2ACTIVE=false\n\
F3ACTIVE=false\n\
F4ACTIVE=false\n\
F5ACTIVE=false\n\
F6ACTIVE=false\n\
F7ACTIVE=false\n\
F8ACTIVE=false\n\
F9ACTIVE=false\n\
F10ACTIVE=false\n\
F11ACTIVE=false\n\
F12ACTIVE=false\n\
F13ACTIVE=false\n\
F14ACTIVE=false\n\
F15ACTIVE=false\n\
F16ACTIVE=false\n\
F17ACTIVE=false\n\
F18ACTIVE=false\n\
F19ACTIVE=false\n\
F20ACTIVE=false\n\
F1DYNAMIC=false\n\
F2DYNAMIC=false\n\
F3DYNAMIC=true\n\
F4DYNAMIC=false\n\
F5DYNAMIC=false\n\
F6DYNAMIC=false\n\
F7DYNAMIC=false\n\
F8DYNAMIC=false\n\
F9DYNAMIC=false\n\
F10DYNAMIC=false\n\
F11DYNAMIC=true\n\
F12DYNAMIC=true\n\
F13DYNAMIC=true\n\
F14DYNAMIC=false\n\
F15DYNAMIC=false\n\
F16DYNAMIC=false\n\
F17DYNAMIC=false\n\
F18DYNAMIC=true\n\
F19DYNAMIC=false\n\
F20DYNAMIC=false\n\
F1LOGIC=false\n\
F2LOGIC=false\n\
F3LOGIC=true\n\
F4LOGIC=false\n\
F5LOGIC=false\n\
F6LOGIC=false\n\
F7LOGIC=false\n\
F8LOGIC=false\n\
F9LOGIC=false\n\
F10LOGIC=true\n\
F11LOGIC=true\n\
F12LOGIC=false\n\
F13LOGIC=true\n\
F14LOGIC=false\n\
F15LOGIC=false\n\
F16LOGIC=true\n\
F17LOGIC=true\n\
F18LOGIC=false\n\
F19LOGIC=false\n\
F20LOGIC=false\n\
F1COLOR=Qt::red\n\
F2COLOR=Qt::black\n\
F3COLOR=Qt::blue\n\
F4COLOR=Qt::black\n\
F5COLOR=Qt::red\n\
F6COLOR=Qt::green\n\
F7COLOR=Qt::yellow\n\
F8COLOR=Qt::blue\n\
F9COLOR=Qt::green\n\
F10COLOR=Qt::red\n\
F11COLOR=Qt::magenta\n\
F12COLOR=grey\n\
F13COLOR=Qt::cyan\n\
F14COLOR=Qt::green\n\
F15COLOR=colored\n\
F16COLOR=colored\n\
F17COLOR=colored\n\
F18COLOR=Qt::red\n\
F19COLOR=Qt::blue\n\
F20COLOR=Qt::green\n\
F1TYPE=std\n\
F2TYPE=std\n\
F3TYPE=std\n\
F4TYPE=std\n\
F5TYPE=polar\n\
F6TYPE=polar\n\
F7TYPE=polar\n\
F8TYPE=std\n\
F9TYPE=parameter\n\
F10TYPE=parameter\n\
F11TYPE=parameter\n\
F12TYPE=parameter\n\
F13TYPE=parameter\n\
F14TYPE=std\n\
F15TYPE=3d\n\
F16TYPE=3d\n\
F17TYPE=3d\n\
F18TYPE=std\n\
F19TYPE=nyquist3d\n\
F20TYPE=nyquist2d\n");
			file.arg(getenv("HOME"));
			
			
			fwrite(file.latin1(),file.length(),1,configFile);
			fclose(configFile);
			
			if(lstat(CONFIGFILE,&fileStat) != 0)
			{
				ErrorBox(EXTCALCC_MSG3+QString(CONFIGFILE)+"\n\n"+getErrorMessage());
				return -3;
			}

		}
		else {
			ErrorBox(EXTCALCC_MSG1+QString(CONFIGFILE)+"\n\n"+getErrorMessage());
			ret=-2;
		}
	}
	fileLen=fileStat.st_size;



	configFile = fopen(CONFIGFILE,"r");
	if(configFile == NULL)
	{
		MessageBox(EXTCALCC_MSG3+QString(CONFIGFILE)+"\n\n"+getErrorMessage());
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
	QString paraStartStr=getConfigString(&confFile,"PARAMETERSTART");
	if(paraStartStr.length()>0)
	{
		double paraStart=paraStartStr.toDouble();
		if(paraStart == NAN)
			paraStart=0.0;
		pref.parameterStart=paraStart;
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
	QString nyquistStartStr=getConfigString(&confFile,"NYQUISTSTART");
	if(nyquistStartStr.length()>0)
	{
		double tableStartZ=nyquistStartStr.toDouble();
		if(tableStartZ == NAN)
			tableStartZ=0.0;
		pref.nyquistStart=tableStartZ;
	}
	QString nyquistEndStr=getConfigString(&confFile,"NYQUISTEND");
	if(nyquistEndStr.length()>0)
	{
		double tableEndZ=nyquistEndStr.toDouble();
		if(tableEndZ == NAN || tableEndZ<=pref.nyquistStart)
			tableEndZ=pref.nyquistStart+10.0;
		pref.nyquistEnd=tableEndZ;
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
	
	QString solvePrecStr=getConfigString(&confFile,"ANALYSEPRECISION");
	if(solvePrecStr.length()>0)
	{
		int solvePrec=solvePrecStr.toInt();
		if(solvePrec <0 || solvePrec>2)
			solvePrec=1;
		pref.solvePrec=solvePrec;
	}
		
	QString nyquistStepsStr=getConfigString(&confFile,"NYQUISTSTEPS");
	if(nyquistStepsStr.length()>0)
	{
		int nyquistSteps=nyquistStepsStr.toInt();
		if(nyquistSteps <10)
			nyquistSteps=200;
		pref.nyquistSteps=nyquistSteps;
	}
	QString graph2dStepsStr=getConfigString(&confFile,"GRAPH2DSTEPS");
	if(graph2dStepsStr.length()>0)
	{
		int graph2dSteps=graph2dStepsStr.toInt();
		if(graph2dSteps <10)
			graph2dSteps=200;
		pref.prec2dSteps=graph2dSteps;
	}
	QString graph3dStepsStr=getConfigString(&confFile,"GRAPH3DSTEPS");
	if(graph3dStepsStr.length()>0)
	{
		int tableZSteps=graph3dStepsStr.toInt();
		if(tableZSteps <10)
			tableZSteps=50;
		pref.prec3dSteps=tableZSteps;
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
	
	
	QString gridStr=getConfigString(&confFile,"3DGRID");
	if(gridStr.length()>0)
	{
		if(gridStr.lower() == "false")
			pref.show3dGrid=false;
		else pref.show3dGrid=true;
	}
	
	QString compStr=getConfigString(&confFile,"COMPLEX");
	if(compStr.length()>0)
	{
		if(compStr.lower() == "false")
			pref.complex=false;
		else pref.complex=true;
	}
	else ret=1;
	
	QString memStr=getConfigString(&confFile,"CLEARSCRIPTMEM");
	if(memStr.length()>0)
	{
		if(memStr.lower() == "true")
			pref.clearScriptMemory=true;
		else pref.clearScriptMemory=false;
	}
	
	QString logStr=getConfigString(&confFile,"LOGNYQUISTSTEPS");
	if(logStr.length()>0)
	{
		if(logStr.lower() == "false")
			pref.logNyquistSteps=false;
		else pref.logNyquistSteps=true;
	}	
	
	logStr=getConfigString(&confFile,"STATSHOWLINES");
	if(logStr.length()>0)
	{
		if(logStr.lower() == "false")
			pref.showStatLines=false;
		else pref.showStatLines=true;
	}
	logStr=getConfigString(&confFile,"STATSHOWPOINTS");
	if(logStr.length()>0)
	{
		if(logStr.lower() == "false")
			pref.showStatPoints=false;
		else pref.showStatPoints=true;
	}
	logStr=getConfigString(&confFile,"STATAUTOCLEAR");
	if(logStr.length()>0)
	{
		if(logStr.lower() == "false")
			pref.statAutoClear=false;
		else pref.statAutoClear=true;
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
			pref.tableType=TABLEINEQUALITY;
		else if(tableType.lower() == "3d")
			pref.tableType=TABLE3D;
		else if(tableType.lower() == "complex")
			pref.tableType=TABLECOMPLEX;
		
	}
	QString language=getConfigString(&confFile,"LANGUAGE");
	if(language.length()>0)
	{
		if(language.lower() == "de")
			pref.language=LANG_DE;
		else if(language.lower() == "fr")
			pref.language=LANG_FR;
		else pref.language=LANG_EN;
		
	}
	for(int c=0; c<8; c++)
	{
		QString showWinString=getConfigString(&confFile,"SHOWWIN"+QString::number(c+1));
		if(showWinString.lower() =="false")
			pref.showWindows[c]=false;
		else pref.showWindows[c]=true;
	}
	
	QString currentSet=getConfigString(&confFile,"CURRENTSET");
	if(currentSet.length()>0)
		pref.currentSet=currentSet;
	
	QString*functionStrings=new QString[20];
	
	for(int c=0; c<20; c++)
	{
		functionStrings[c]=getConfigString(&confFile,"F"+QString::number(c+1));
		functionStrings[c]=resetConfigString(functionStrings[c]);
		if(functionStrings[c].length()<=0)
			functionStrings[c]="";
	}
	if(pref.functions!=NULL)
		delete[]pref.functions;
	pref.functions=functionStrings;
	
	QString*commentStrings=new QString[20];
	
	for(int c=0; c<20; c++)
	{
		commentStrings[c]=getConfigString(&confFile,"COMMENT"+QString::number(c+1));
		if(commentStrings[c].length()<=0)
			commentStrings[c]="";
	}
	if(pref.functionComments!=NULL)
		delete[]pref.functionComments;
	pref.functionComments=commentStrings;
	
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
	
	bool*logicFunctions=new bool[20];
	for(int c=0; c<20; c++)
	{
		QString logicString=getConfigString(&confFile,"F"+QString::number(c+1)+"LOGIC");
		if(logicString.lower() =="true" &&logicString.length()>0)
			logicFunctions[c]=true;
		else logicFunctions[c]=false;
	}
	if(pref.logicFunctions!=NULL)
		delete[]pref.logicFunctions;
	pref.logicFunctions=logicFunctions;

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
			else if(typeString.lower() == "nyquist2d")
				types[c]=GRAPHCOMPLEX;
			else if(typeString.lower() == "nyquist3d")
				types[c]=GRAPHCOMP3D;
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
		MessageBox(EXTCALCC_MSG1+QString(CONFIGFILE)+"\n\n"+getErrorMessage());
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
	configuration+="\nNYQUISTSTART=";
	configuration+=QString::number(pref.nyquistStart);
	configuration+="\nNYQUISTEND=";
	configuration+=QString::number(pref.nyquistEnd);
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
	configuration+="\nGRAPH2DSTEPS=";
	configuration+=QString::number(pref.prec2dSteps);
	configuration+="\nGRAPH3DSTEPS=";
	configuration+=QString::number(pref.prec3dSteps);
	configuration+="\nNYQUISTSTEPS=";
	configuration+=QString::number(pref.nyquistSteps);
	configuration+="\nANALYSEPRECISION=";
	configuration+=QString::number(pref.solvePrec);
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
	configuration+="\n3DGRID=";
	if(pref.show3dGrid == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nLOGNYQUISTSTEPS=";
	if(pref.logNyquistSteps == true)
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
	configuration+="\nCOMPLEX=";
	if(pref.complex == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nCLEARSCRIPTMEM=";
	if(pref.clearScriptMemory == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nSTATSHOWLINES=";
	if(pref.showStatLines == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nSTATSHOWPOINTS=";
	if(pref.showStatPoints == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nSTATAUTOCLEAR=";
	if(pref.statAutoClear == true)
		configuration+="true";
	else configuration+="false";
	configuration+="\nTABLETYPE=";
	if(pref.tableType==TABLENORMAL)
		configuration+="normal";
	else if(pref.tableType==TABLEPOLAR)
		configuration+="polar";
	else if(pref.tableType==TABLEPARAMETER)
		configuration+="parameter";
	else if(pref.tableType==TABLEINEQUALITY)
		configuration+="inequaity";
	else if(pref.tableType==TABLE3D)
		configuration+="3d";
	else if(pref.tableType==TABLECOMPLEX)
		configuration+="complex";
	configuration+="\nBASE=";
	if(pref.base == HEX)
		configuration+="hex";
	else if(pref.base == OCT)
		configuration+="oct";
	else if(pref.base == BIN)
		configuration+="bin";
	else if(pref.base == DEC)
		configuration+="dec";
	configuration+="\nLANGUAGE=";
	if(pref.language == LANG_DE)
		configuration+="de\n";
	else if(pref.language == LANG_FR)
		configuration+="fr\n";
	else configuration+="en\n";
	configuration+="\nCURRENTSET=";
	configuration+=pref.currentSet;
	configuration+="\n";

	for(int c=0; c<8;c++)
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
		configuration+="COMMENT"+QString::number(c+1)+"="+pref.functionComments[c]+"\n";
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
		configuration+="LOGIC=";
		if(pref.logicFunctions[c])
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
			case GRAPHCOMPLEX:
				configuration+="nyquist2d";
				break;
			case GRAPHCOMP3D:
				configuration+="nyquist3d";
				break;
			default:
				configuration+="std";

		}
		configuration+="\n";
	}
	
	fwrite(configuration,configuration.length(),1,configFile);
	fclose(configFile);
}


void MainObject::readVarFile()
{
	chdir(getenv("HOME"));

	int fileLen;
	struct stat fileStat;

	if(lstat(VARSFILE,&fileStat) != 0)
		return;
	else fileLen=fileStat.st_size;

	
	FILE*varFile = fopen(VARSFILE,"r");
	if(varFile == NULL)
	{
		MessageBox(EXTCALCH_STR21+QString(VARSFILE)+"\n\n"+getErrorMessage());
		return;
	}
	char* cConfFile = new char[fileLen+1];
	fread((void*)cConfFile,fileLen,1,varFile);
	cConfFile[fileLen]=(char)0;
	QString configFile(cConfFile);
	delete[]cConfFile;
	fclose(varFile);
	
	int pos1=0,pos2=0;
	QString num,num2;
	for(int c=0; c<27;c++)
	{
		pos2=configFile.find(" ",pos1);
		if(pos2==-1)
			return;
		num=configFile.mid(pos1,pos2-pos1);
		threadData->numlen[c]=num.toInt();
		if(threadData->numlen[c]<1 || threadData->numlen[c]>400)
		{
			threadData->numlen[c]=1;
			return;
		}
		pos1=pos2+1;
		pos2=configFile.find(" ",pos1);
		if(pos2==-1)
			return;
		num=configFile.mid(pos1,pos2-pos1);
		threadData->dimension[c][0]=num.toInt();
		if(threadData->dimension[c][0]<1)
		{
			threadData->dimension[c][0]=1;
			return;
		}
		pos1=pos2+1;
		pos2=configFile.find("\n",pos1);
		if(pos2==-1)
			return;
		num=configFile.mid(pos1,pos2-pos1);
		threadData->dimension[c][1]=num.toInt();
		if(threadData->dimension[c][1]<1)
		{
			threadData->dimension[c][1]=1;
			return;
		}
		pos1=pos2+1;
	}
	
	bool failure=false;
	for(int c=0; c<27;c++)
	{
		threadData->vars[c]=(Number*) realloc(threadData->vars[c],sizeof(Number)*threadData->numlen[c]);
		
		for(int c1=0; c1<threadData->numlen[c]; c1++)
		{
			
			if(failure)
			{
				threadData->vars[c][c1].cval=NULL;
				threadData->vars[c][c1].type=NNONE;
				continue;
			}
			
			pos2=configFile.find(" ",pos1);
			if(pos2==-1)
			{
				failure=true;
				c1--;
				continue;
			}
			num=configFile.mid(pos1,pos2-pos1);
			pos1=pos2+1;
			
			pos2=configFile.find(" ",pos1);
			if(pos2==-1 && !failure)
			{
				failure=true;
				c1--;
				continue;
			}
			num2=configFile.mid(pos1,pos2-pos1);
			pos1=pos2+1;
			threadData->vars[c][c1].fval=Complex(strtold(num,NULL),strtold(num2,NULL));
			threadData->vars[c][c1].type=NFLOAT;
			threadData->vars[c][c1].cval=NULL;
		}
	}
}

void MainObject::writeVarFile()
{
	FILE*configFile;

	chdir(getenv("HOME"));
	configFile = fopen(VARSFILE,"w");
	if(configFile == NULL)
	{
		ErrorBox(EXTCALCH_STR22+QString(VARSFILE)+"\n\n"+getErrorMessage());
		return;
	}
	QString vars="";
	char*buffer=(char*)malloc(100);
	
	for(int c=0; c<27;c++)
	{
		if(threadData->numlen[c]<=400)
			vars+=QString::number(threadData->numlen[c]);
		else vars+="400";
		vars+=" ";
		vars+=QString::number(threadData->dimension[c][0]);
		vars+=" ";
		vars+=QString::number(threadData->dimension[c][1]);
		vars+="\n";
	}
	for(int c=0; c<27;c++)
	{
		for(int c1=0; c1<threadData->numlen[c] && c1<400; c1++)
		{
			convertToFloat(&threadData->vars[c][c1]);
			sprintf(buffer,"%.*Lg",pref.precision,threadData->vars[c][c1].fval.real());
			vars+=QString(buffer);
			vars+=" ";
			sprintf(buffer,"%.*Lg",pref.precision,threadData->vars[c][c1].fval.imag());
			vars+=QString(buffer);
			vars+=" ";
		}
	}
	free(buffer);
	
	fwrite(vars,vars.length(),1,configFile);
	fclose(configFile);
}



void MainObject::initConstants()
{
	if(pref.constList!=NULL)
	{
		for(int c=0; c<pref.constLen; c++)
		{
			delete pref.constList[c].description;
			delete pref.constList[c].identifier;
			delete pref.constList[c].value;
		}
			
		free(pref.constList);
	}
	pref.constList=(Constant*)malloc(31*sizeof(Constant));
	pref.constLen=31;
	pref.userConstLen=0;

	
	pref.constList[0].identifier=new QString("c_pi");
	pref.constList[0].description=new QString(tr("pi ")+getUnicode(PISTRING));
	pref.constList[0].value=new QString("3.14159265358979323846264338327950288");
	
	pref.constList[1].identifier=new QString("c_eu");
	pref.constList[1].description=new QString(tr("euler number e"));
	pref.constList[1].value=new QString("2.71828182845904523536028747135266249");
	
	pref.constList[2].identifier=new QString("c_C");
	pref.constList[2].description=new QString(tr("euler constant C"));
	pref.constList[2].value=new QString("0.57721566490153286060651209008240243");

	
	pref.constList[3].identifier=new QString("c_c0");
	pref.constList[3].description=new QString(tr("vacuum light speed c0 [m/s]"));
	pref.constList[3].value=new QString("299792458");
		
	pref.constList[4].identifier=new QString("c_g0");
	pref.constList[4].description=new QString(tr("standard acceleration of gravity g [m/s^2]"));
	pref.constList[4].value=new QString("9.80665");
			
	pref.constList[5].identifier=new QString("c_G");
	pref.constList[5].description=new QString(tr("Newtonian constant of gravitation G [m^3/(kg s^2)]"));
	pref.constList[5].value=new QString("6.674 28e-11");	
	
	pref.constList[6].identifier=new QString("c_e0");
	pref.constList[6].description=new QString(tr("electric field constant e0 [F/m]"));
	pref.constList[6].value=new QString("8.854187817e-12");
	
	pref.constList[7].identifier=new QString("c_my0");
	pref.constList[7].description=new QString(tr("magnetic field constant my0 [N/A^2]"));
	pref.constList[7].value=new QString("12.566370614e-7");

	pref.constList[8].identifier=new QString("c_hj");
	pref.constList[8].description=new QString(tr("Planck constant h [Js]"));
	pref.constList[8].value=new QString("6.62606896e-34");
	
	pref.constList[9].identifier=new QString("c_hev");
	pref.constList[9].description=new QString(tr("Planck constant h [eVs]"));
	pref.constList[9].value=new QString("4.13566733e-15");

	pref.constList[10].identifier=new QString("c_Z0");
	pref.constList[10].description=new QString(tr("characteristic impedance of vacuum Z0 [V/A]"));
	pref.constList[10].value=new QString("376.730313461");
	
	pref.constList[11].identifier=new QString("c_F");
	pref.constList[11].description=new QString(tr("Faraday constant F [C/mol]"));
	pref.constList[11].value=new QString("96485.3399");	
	
	pref.constList[12].identifier=new QString("c_e");
	pref.constList[12].description=new QString(tr("atomic unit of charge e [C]"));
	pref.constList[12].value=new QString("1.602176487e-19");
	
	pref.constList[13].identifier=new QString("c_alpha");
	pref.constList[13].description=new QString(tr("fine-structure constant alpha"));
	pref.constList[13].value=new QString("7.2973525376e-3");

	pref.constList[14].identifier=new QString("c_mu");
	pref.constList[14].description=new QString(tr("atomic mass constant mu [kg]"));
	pref.constList[14].value=new QString("1.660 538 782 e-27");	

	pref.constList[15].identifier=new QString("c_me");
	pref.constList[15].description=new QString(tr("electron mass me [kg]"));
	pref.constList[15].value=new QString("9.10938215e-31");

	pref.constList[16].identifier=new QString("c_mn");
	pref.constList[16].description=new QString(tr("neutron mass mn [kg]"));
	pref.constList[16].value=new QString("1.674927211e-27");

	pref.constList[17].identifier=new QString("c_mp");
	pref.constList[17].description=new QString(tr("proton mass mp [kg]"));
	pref.constList[17].value=new QString("1.672621637e-27");
	
	pref.constList[18].identifier=new QString("c_NA");
	pref.constList[18].description=new QString(tr("Avogadro constant [1/mol]"));
	pref.constList[18].value=new QString("6.02214179 e23");	
	
	pref.constList[19].identifier=new QString("c_k0");
	pref.constList[19].description=new QString(tr("Boltzmann constant k [J/K]"));
	pref.constList[19].value=new QString("1.3806504e-23");	
	
	pref.constList[20].identifier=new QString("c_R0");
	pref.constList[20].description=new QString(tr("molar gas constant R0 [J/(mol K)]"));
	pref.constList[20].value=new QString("8.314472");	
	
	pref.constList[21].identifier=new QString("c_sigma");
	pref.constList[21].description=new QString(tr("Stefan-Boltzmann constant sigma [W/(M^2 K^4)]"));
	pref.constList[21].value=new QString("5.670400e-8");	
	
	pref.constList[22].identifier=new QString("c_b");
	pref.constList[22].description=new QString(tr("Wien wavelength displacement law constant b [m K]"));
	pref.constList[22].value=new QString("2.8977685e-3");	


	
	pref.constList[23].identifier=new QString("c_kmmile");
	pref.constList[23].description=new QString(tr("km -> mile"));
	pref.constList[23].value=new QString("0.621371192");
	
	pref.constList[24].identifier=new QString("c_milekm");
	pref.constList[24].description=new QString(tr("mile -> km"));
	pref.constList[24].value=new QString("1.609334");
	
	pref.constList[25].identifier=new QString("c_cminch");
	pref.constList[25].description=new QString(tr("cm -> inch"));
	pref.constList[25].value=new QString("0.393700787");
	
	pref.constList[26].identifier=new QString("c_inchcm");
	pref.constList[26].description=new QString(tr("inch -> cm"));
	pref.constList[26].value=new QString("2.54");
	
	pref.constList[27].identifier=new QString("c_goz");
	pref.constList[27].description=new QString(tr("g -> oz"));
	pref.constList[27].value=new QString("0.035273965");
	
	pref.constList[28].identifier=new QString("c_ozg");
	pref.constList[28].description=new QString(tr("oz -> g"));
	pref.constList[28].value=new QString("28.34962");
		
	pref.constList[29].identifier=new QString("c_Jcal");
	pref.constList[29].description=new QString(tr("J -> calorie"));
	pref.constList[29].value=new QString("0.238902957");
	
	pref.constList[30].identifier=new QString("c_calJ");
	pref.constList[30].description=new QString(tr("calorie -> J"));
	pref.constList[30].value=new QString("4.1858");
	
	
	FILE*configFile;

	chdir(getenv("HOME"));
	
	int fileLen;
	struct stat fileStat;

	if(lstat(CONSTFILE,&fileStat) != 0)
	{
		getPref(pref);
		return;
	}
	else fileLen=fileStat.st_size;
	
	configFile = fopen(CONSTFILE,"r");
	if(configFile == NULL)
	{
		ErrorBox(tr("Can't read constants file %1.\n\n").arg(CONSTFILE)+getErrorMessage());
		getPref(pref);
		return;
	}
	char*buffer=new char[fileLen+1];
	buffer[fileLen]=(char)0;
	fread((void*)buffer,fileLen,1,configFile);
	QString constData(buffer),desc,val;
	int pos1=0,pos2=0;
	
	int c=1;
	while((pos1=constData.find("\n",pos2))!=-1)
	{
		desc=constData.mid(pos2,pos1-pos2);
		pos2=pos1+1;
		pos1=constData.find("\n",pos2);
		if(pos1==-1)
			break;
		val=constData.mid(pos2,pos1-pos2);
		pos2=pos1+1;
		
		pref.constLen++;
		pref.userConstLen++;
		pref.constList=(Constant*)realloc((void*)pref.constList,sizeof(Constant)*pref.constLen);
		pref.constList[pref.constLen-1].description=new QString(desc);
		pref.constList[pref.constLen-1].value=new QString(val);
		pref.constList[pref.constLen-1].identifier=new QString("c_usr"+QString::number(c));
		c++;
	}
	fclose(configFile);
	delete[] buffer;

	getPref(pref);
}

void MainObject::writeConstants()
{
	FILE*configFile;

	chdir(getenv("HOME"));
	configFile = fopen(CONSTFILE,"w");
	if(configFile == NULL)
	{
		ErrorBox(tr("Constants file %1 could not be written.\n\n").arg(CONSTFILE)+getErrorMessage());
		return;
	}
	QString constData("");
	for(int c=pref.constLen-pref.userConstLen; c<pref.constLen; c++)
	{
		constData+=*pref.constList[c].description;
		constData+="\n";
		constData+=*pref.constList[c].value;
		constData+="\n";
	}
	
	fwrite(constData.latin1(),constData.length(),1,configFile);
	fclose(configFile);
}

void MainObject::tabChangeSlot(int index)
{
  QToolBar*tb;
	calculator->dockWindowSlot();
	calculator2->dockWindowSlot();
	graph->dockWindowSlot();
	table->dockWindowSlot();
	matrix->dockWindowSlot();
	statistics->dockWindowSlot();
	scripting->dockWindowSlot();
	scriptIO->dockWindowSlot();

  if(lastTab!=NULL)
  {
    disconnect(calcButtons,SIGNAL(emitText(QString)),lastTab,SLOT(processText(QString)));
    disconnect(extButtons,SIGNAL(emitText(QString)),lastTab,SLOT(processText(QString)));
    qDebug("Widget disconnected! " +((TabWidget*)lastTab)->getDescriptor());
    tb=((TabWidget*)lastTab)->getToolBar();
    if(tb!=NULL)
      tb->hide();
  }
  else qDebug("Disconnect Index failue!");
  lastTab=clientArea->widget(index);

  if(clientArea->widget(index)!=NULL)
  {
    connect(calcButtons,SIGNAL(emitText(QString)),clientArea->widget(index),SLOT(processText(QString)));
    connect(extButtons,SIGNAL(emitText(QString)),clientArea->widget(index),SLOT(processText(QString)));
    qDebug("Widget connected! "+((TabWidget*)(clientArea->widget(index)))->getDescriptor());
    tb=((TabWidget*)clientArea->widget(index))->getToolBar();
    if(tb!=NULL)
      tb->show();
  }
  else qDebug("Connect Index failue! " +QString::number(index));

	if(index==clientArea->indexOf(calculator) || index==clientArea->indexOf(calculator2))
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,false);
		mainMenu->setItemVisible(SCRIPTM,false);
		mainMenu->setItemVisible(STATISTICSM,false);
	}
	else if(index==clientArea->indexOf(graph))
	{
		mainMenu->setItemVisible(GRAPH,true);
		mainMenu->setItemVisible(TABLE,false);
		mainMenu->setItemVisible(SCRIPTM,false);
		mainMenu->setItemVisible(STATISTICSM,false);

	}
	else if(index==clientArea->indexOf(table))
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,true);
		mainMenu->setItemVisible(SCRIPTM,false);
		mainMenu->setItemVisible(STATISTICSM,false);

	}
	else if(index==clientArea->indexOf(matrix))
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,false);
		mainMenu->setItemVisible(SCRIPTM,false);
		mainMenu->setItemVisible(STATISTICSM,false);

		emit matrixEnterSignal();
	}
	else if(index==clientArea->indexOf(scripting) || index==clientArea->indexOf(scriptIO))
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,false);
		mainMenu->setItemVisible(SCRIPTM,true);
		mainMenu->setItemVisible(STATISTICSM,false);
	}
	else if(index==clientArea->indexOf(statistics))
	{
		mainMenu->setItemVisible(GRAPH,false);
		mainMenu->setItemVisible(TABLE,false);
		mainMenu->setItemVisible(SCRIPTM,false);
		mainMenu->setItemVisible(STATISTICSM,true);

	}
	
	if(index!=clientArea->indexOf(calculator) && index!=clientArea->indexOf(calculator2))
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

void MainObject::calcModeMenuSlot(int item)
{
	if(calcFocus || item==SCIENTIFIC)
	{
		pref.calcType=item;
		getPref(pref);
	}
}

void MainObject::calcComplexSlot()
{
	pref.complex=!pref.complex;
	getPref(pref);
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
		if(helpBrowser!=NULL)
			delete helpBrowser;
		helpBrowser=new HelpBrowser(this);
		helpBrowser->setGeometry(50,50,750,550);

		if(pref.language==LANG_DE)
			helpBrowser->setContent(QString(INSTALLDIR)+"/doc/help_de.html");
		else if(pref.language==LANG_FR)
			helpBrowser->setContent(QString(INSTALLDIR)+"/doc/help_fr.html");
		else helpBrowser->setContent(QString(INSTALLDIR)+"/doc/help_en.html");
		helpBrowser->show();
			
		/*
		helpProcess->clearArguments();
		helpProcess->addArgument("konqueror");
		if(pref.language==LANG_DE)
			helpProcess->addArgument(QString(INSTALLDIR)+"/doc/help_de.html");
		else if(pref.language==LANG_FR)
			helpProcess->addArgument(QString(INSTALLDIR)+"/doc/help_fr.html");
		else helpProcess->addArgument(QString(INSTALLDIR)+"/doc/help_en.html");

		helpProcess->start();
		*/
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

void MainObject::graphSetMenuSlot(int item)
{
	writeFunctionFile(pref.currentSet);
	QString currentActionName="";

	for(int c=0; c<graphSetActions->actions().size(); c++)
	{
		if(graphSetActions->actions()[c]->data()==item)
		{
			graphSetActions->actions()[c]->setChecked(true);
			currentActionName=	graphSetActions->actions()[c]->text();
		}
		else graphSetActions->actions()[c]->setChecked(false);
	}

	pref.currentSet=currentActionName;
	readFunctionFile(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)+pref.currentSet);

}

void MainObject::graphMenuSlot(int item)
{
	if(item==GRAPHIMPORT)
	{
		if(functionDialog!=NULL)
		{
			QObject::disconnect(SIGNAL(prefChange(Preferences)),this);
			delete functionDialog;
		}
		functionDialog=new ImportDialog(pref,this,true,true);
		QObject::connect(functionDialog,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		functionDialog->show();
	}
	else if(item==GRAPHEXPORT)
	{
		if(functionDialog!=NULL)
			delete functionDialog;
		functionDialog=new ImportDialog(pref,this,false,true);	
		functionDialog->show();
	}
	else if(item==GRAPHSETMANAGE)
	{
		if(graphSetDialog!=NULL)
			delete graphSetDialog;

		graphSetDialog=new GraphSetDialog(pref,this);
		graphSetDialog->show();
	}
	else if(item==GRAPHCREATESET)
	{
		bool ok;
		QString newString=QInputDialog::getText(tr("Create New Graph Set"),tr("Insert name of new graph set:"),QLineEdit::Normal,QString::null,&ok);
		
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
			 writeFunctionFile(pref.currentSet);
			 for(int c=0; c<20; c++)
			 {
				 pref.functions[c]=QString();
				 pref.functionComments[c]=QString();
				 pref.activeFunctions[c]=false;
				 pref.functionColors[c]=QColor(0,0,0);
				 pref.logicFunctions[c]=false;
				 pref.functionTypes[c]=GRAPHSTD;
				 pref.dynamicFunctions[c]=false;
			 }
			 pref.currentSet=newString;
			 writeFunctionFile(pref.currentSet);
			 getPref(pref);
		}
	}
	else if(item==GRAPHSAVECURR)
	{
		bool ok;
		QString newString=QInputDialog::getText(tr("Save Current Graph Set As"),tr("Insert new name of graph set:"),QLineEdit::Normal,QString(),&ok);
		
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
//			writeFunctionFile(pref.currentSet);
			pref.currentSet=newString;
			writeFunctionFile(pref.currentSet);
			getPref(pref);
		}
	}
}

void MainObject::updateGraphSetMenuSlot()
{
	readGraphsDir();
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

void MainObject::scriptMenuSlot(int item)
{
	switch(item)
	{
		case EXPORTSCRIPT:
			if(exportDialog != NULL)
				delete exportDialog;
			exportDialog=new ImportDialog(pref,(QWidget*)this,false);
			exportDialog->show();			
			break;
		case IMPORTSCRIPT:
			if(importDialog != NULL)
				delete importDialog;
			importDialog=new ImportDialog(pref,(QWidget*)this,true);
			QObject::connect(importDialog,SIGNAL(updateScriptSignal(int)),scripting,SLOT(fileBrowserMenuSlot(int)));
			importDialog->show();
			break;
		case CLEARMEMALWAYS:
			pref.clearScriptMemory=!pref.clearScriptMemory;
			getPref(pref);
			break;
		case CLEARMEMNOW:
			scriptIO->clearMemSlot();
			break;
	}
}

void MainObject::statisticsMenuSlot(int item)
{
	switch(item)
	{
		case STATCLEAR:
			emit removeGraphicsLinesSignal();
			graph->drawSlot();
			break;
		case STATAUTOCLEAR:
			pref.statAutoClear=!pref.statAutoClear;
			getPref(pref);
			break;
		case STATPOINTS:
			pref.showStatPoints=!pref.showStatPoints;
			getPref(pref);
			break;
		case STATLINES:
			pref.showStatLines=!pref.showStatLines;
			getPref(pref);
			break;
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
			grPref=new GraphPreferences(pref,vars,(QWidget*)this);
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

void MainObject::languageMenuSlot(int item)
{
	pref.language=item;
	getPref(pref);
	int ret=YesNoCancelBox(tr("Extcalc must be restarted to apply this changes!\n\nRestart now?"));
	if(ret==0)
	{
		Q3Process extcalcProcess;
		extcalcProcess.addArgument("extcalc");
		extcalcProcess.start();
		qApp->closeAllWindows();
	}
	else {
		for(int c=0; c<languageActions->actions().size(); c++)
			if(languageActions->actions()[c]->data()==pref.language)
				languageActions->actions()[c]->setChecked(true);
	}
}

void MainObject::fileMenuSlot(int item)
{
	
	if(item==QUIT)
		qApp->closeAllWindows();
}

void MainObject::editMenuSlot(int item)
{
	qDebug(QString::number(item));
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
        clientArea->setCurrentWidget(calculator);
			break;
		case VIEWCALC2:
			pref.showWindows[1]=!pref.showWindows[1];
      getPref(pref);
      if(pref.showWindows[1])
        clientArea->setCurrentWidget(calculator2);
			break;
		case VIEWGRAPH:
			pref.showWindows[2]=!pref.showWindows[2];
      getPref(pref);
      if(pref.showWindows[2])
        clientArea->setCurrentWidget(graph);
			break;
		case VIEWTABLE:
			pref.showWindows[3]=!pref.showWindows[3];
      getPref(pref);
      if(pref.showWindows[3])
        clientArea->setCurrentWidget(table);
			break;
		case VIEWMATRIX:
			pref.showWindows[4]=!pref.showWindows[4];
      getPref(pref);
      if(pref.showWindows[4])
        clientArea->setCurrentWidget(matrix);
			break;
		case VIEWSTATISTICS:
			pref.showWindows[5]=!pref.showWindows[5];
      getPref(pref);
      if(pref.showWindows[5])
        clientArea->setCurrentWidget(statistics);
			break;
		case VIEWSCRIPTING:
			pref.showWindows[6]=!pref.showWindows[6];
      getPref(pref);
      if(pref.showWindows[6])
        clientArea->setCurrentWidget(scripting);
			break;
		case VIEWSCRIPTIO:
			pref.showWindows[7]=!pref.showWindows[7];
      getPref(pref);
      if(pref.showWindows[7])
        clientArea->setCurrentWidget(scriptIO);
			break;
	}
}

void MainObject::runScriptSlot(QString*)
{
	if(!pref.showWindows[7])
		viewMenuSlot(VIEWSCRIPTIO);
	else clientArea->setCurrentWidget(scriptIO);
}

void MainObject::changeTabSlot(int num)
{



  switch(num)
	{
		case 0:
			if(!pref.showWindows[0])
				viewMenuSlot(VIEWCALC1);
      clientArea->setCurrentWidget(calculator);

			break;
		case 1:
			if(!pref.showWindows[1])
				viewMenuSlot(VIEWCALC2);
      clientArea->setCurrentWidget(calculator2);

			break;
		case 2:
			if(!pref.showWindows[2])
				viewMenuSlot(VIEWGRAPH);
      clientArea->setCurrentWidget(graph);

			break;
		case 3:
			if(!pref.showWindows[3])
				viewMenuSlot(VIEWTABLE);
      clientArea->setCurrentWidget(table);

			break;
		case 4:
			if(!pref.showWindows[4])
				viewMenuSlot(VIEWMATRIX);
      clientArea->setCurrentWidget(matrix);

			break;
		case 5:
			if(!pref.showWindows[5])
				viewMenuSlot(VIEWSTATISTICS);
      clientArea->setCurrentWidget(statistics);

			break;
		case 6:
			if(!pref.showWindows[6])
				viewMenuSlot(VIEWSCRIPTING);
      clientArea->setCurrentWidget(scripting);

			break;
		case 7:
			if(!pref.showWindows[7])
				viewMenuSlot(VIEWSCRIPTIO);
      clientArea->setCurrentWidget(scriptIO);

			break;
	}
}


void MainObject::getPref(Preferences newPref)
{
  static bool running=false;
  int tabIndexCounter=0;


  if(newPref.graphType==GRAPHPOLAR)
  {
    newPref.xmin=newPref.ymin=-newPref.radiusMax;
    newPref.xmax=newPref.ymax=newPref.radiusMax;
    newPref.rasterSizeX=newPref.rasterSizeY=newPref.rasterSizeRadius;
  }
  else {
    if(fabs(newPref.xmax) > fabs(newPref.xmin))
      newPref.radiusMax=fabs(newPref.xmax);
    else newPref.radiusMax=fabs(newPref.xmin);
    newPref.rasterSizeRadius=newPref.rasterSizeX;
    if(newPref.angle==DEG)
    {
      newPref.rasterSizeAngle=15.0;
      newPref.angleMax=360.0;
    }
    else if(newPref.angle==RAD)
    {
      newPref.rasterSizeAngle=0.1*PI;
      newPref.angleMax=2*PI;
    }
    else if(newPref.angle==GRA)
    {
      newPref.rasterSizeAngle=20.0;
      newPref.angleMax=400.0;
    }
  }

  if(!running)
  {
    running=true;
    if(pref.showWindows[0])
    {
      if(clientArea->indexOf(calculator)==-1)
        clientArea->insertTab(tabIndexCounter,calculator,EXTCALCH_STR6);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(calculator)!=-1)
        clientArea->removeTab(clientArea->indexOf(calculator));
    }
    if(pref.showWindows[1])
    {
      if(clientArea->indexOf(calculator2)==-1)
        clientArea->insertTab(tabIndexCounter,calculator2,EXTCALCH_STR7);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(calculator2)!=-1)
        clientArea->removeTab(clientArea->indexOf(calculator));
    }
    if(pref.showWindows[2])
    {
      if(clientArea->indexOf(graph)==-1)
        clientArea->insertTab(tabIndexCounter,graph,EXTCALCH_STR8);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(graph)!=-1)
        clientArea->removeTab(clientArea->indexOf(graph));
    }
    if(pref.showWindows[3])
    {
      if(clientArea->indexOf(table)==-1)
        clientArea->insertTab(tabIndexCounter,table,EXTCALCH_STR9);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(table)!=-1)
        clientArea->removeTab(clientArea->indexOf(table));
    }
    if(pref.showWindows[4])
    {
      if(clientArea->indexOf(matrix)==-1)
        clientArea->insertTab(tabIndexCounter,matrix,EXTCALCH_MENU73);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(matrix)!=-1)
        clientArea->removeTab(clientArea->indexOf(matrix));
    }
    if(pref.showWindows[5])
    {
      if(clientArea->indexOf(statistics)==-1)
        clientArea->insertTab(tabIndexCounter,statistics,EXTCALCH_MENU74);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(statistics)!=-1)
        clientArea->removeTab(clientArea->indexOf(statistics));
    }
    if(pref.showWindows[6])
    {
      if(clientArea->indexOf(scripting)==-1)
        clientArea->insertTab(tabIndexCounter,scripting,EXTCALCH_STR12);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(scripting)!=-1)
        clientArea->removeTab(clientArea->indexOf(scripting));
    }
    if(pref.showWindows[7])
    {
      if(clientArea->indexOf(scriptIO)==-1)
        clientArea->insertTab(tabIndexCounter,scriptIO,EXTCALCH_STR13);
      tabIndexCounter++;
    }
    else {
      if(clientArea->indexOf(scriptIO)!=-1)
        clientArea->removeTab(clientArea->indexOf(scriptIO));
    }


    running=false;
  }

 /*
  if(((clientArea->indexOf(calculator)!=-1)!=pref.showWindows[0] ||
	   (clientArea->indexOf(calculator2)!=-1)!=pref.showWindows[1] ||
	   (clientArea->indexOf(graph)!=-1)!=pref.showWindows[2] ||
	   (clientArea->indexOf(table)!=-1)!=pref.showWindows[3] ||
	   (clientArea->indexOf(matrix)!=-1)!=pref.showWindows[4] || 
	   (clientArea->indexOf(statistics)!=-1)!=pref.showWindows[5] || 
	   (clientArea->indexOf(scripting)!=-1)!=pref.showWindows[6] ||
	   (clientArea->indexOf(scriptIO)!=-1)!=pref.showWindows[7]
       ) && !running)
  {
  running=true;
  if(clientArea->indexOf(calculator)!=-1)
	  clientArea->removePage(calculator);
  if(clientArea->indexOf(calculator2)!=-1)
	  clientArea->removePage(calculator2);
  if(clientArea->indexOf(graph)!=-1)
	  clientArea->removePage(graph);
  if(clientArea->indexOf(table)!=-1)
	  clientArea->removePage(table);
  if(clientArea->indexOf(matrix)!=-1)
	  clientArea->removePage(matrix);
  if(clientArea->indexOf(statistics)!=-1)
	  clientArea->removePage(statistics);
  if(clientArea->indexOf(scripting)!=-1)
	  clientArea->removePage(scripting);
  if(clientArea->indexOf(scriptIO)!=-1)
	  clientArea->removePage(scriptIO);
  if(pref.showWindows[0])
	  clientArea->addTab(calculator,EXTCALCH_STR6);
  if(pref.showWindows[1])
	  clientArea->addTab(calculator2,EXTCALCH_STR7);
  if(pref.showWindows[2])
	  clientArea->addTab(graph,EXTCALCH_STR8);
  if(pref.showWindows[3])
	  clientArea->addTab(table,EXTCALCH_STR9);
  if(pref.showWindows[4])
	  clientArea->addTab(matrix,EXTCALCH_MENU73);
  if(pref.showWindows[5])
	  clientArea->addTab(statistics,EXTCALCH_MENU74);
  if(pref.showWindows[6])
	  clientArea->addTab(scripting,EXTCALCH_STR12);
  if(pref.showWindows[7])
    clientArea->addTab(scriptIO,EXTCALCH_STR13);
  running=false;
  }
*/

      if(!calcFocus && newPref.calcType==BASE)
      {
        newPref.calcType=SCIENTIFIC;
        calcModeChanged=true;
      }
      if(calcFocus&&calcModeChanged)
      {
        newPref.calcType=BASE;
        calcModeChanged=false;
      }

	for(int c=0; c<graphTypeActions->actions().size(); c++)
		if(graphTypeActions->actions()[c]->data()==newPref.graphType)
			graphTypeActions->actions()[c]->setChecked(true);

	for(int c=0; c<angleActions->actions().size(); c++)
		if(angleActions->actions()[c]->data()==newPref.angle)
			angleActions->actions()[c]->setChecked(true);

	for(int c=0; c<outputActions->actions().size(); c++)
		if(outputActions->actions()[c]->data()==newPref.outputType)
			outputActions->actions()[c]->setChecked(true);
	  
	for(int c=0; c<floatPointActions->actions().size(); c++)
		if(floatPointActions->actions()[c]->data()==newPref.outputLength)
			floatPointActions->actions()[c]->setChecked(true);
	
	for(int c=0; c<calcModeActions->actions().size(); c++)
		if(calcModeActions->actions()[c]->data()==newPref.calcType)
			calcModeActions->actions()[c]->setChecked(true);
	
	for(int c=0; c<baseActions->actions().size(); c++)
		if(baseActions->actions()[c]->data()==newPref.base)
			baseActions->actions()[c]->setChecked(true);
	
	for(int c=0; c<tableTypeActions->actions().size(); c++)
		if(tableTypeActions->actions()[c]->data()==newPref.tableType)
			tableTypeActions->actions()[c]->setChecked(true);
	
	for(int c=0; c<languageActions->actions().size(); c++)
		if(languageActions->actions()[c]->data()==newPref.language)
			languageActions->actions()[c]->setChecked(true);

	
    complexAction->setChecked(pref.complex);


    scriptMenu->setItemChecked(CLEARMEMALWAYS,true);

    pref=newPref;
    calculator->setPref(pref);
    calculator2->setPref(pref);
    graph->setPref(pref);
    table->setPref(pref);
    matrix->setPref(pref);
    statistics->setPref(pref);
    scripting->setPref(pref);
    scriptIO->setPref(pref);
    calcButtons->setPref(pref);
    extButtons->setPref(pref);
    screenshotDialog->setPref(pref);


    scriptMenu->setItemChecked(CLEARMEMALWAYS,pref.clearScriptMemory);
    statisticsMenu->setItemChecked(STATAUTOCLEAR,pref.statAutoClear);
    statisticsMenu->setItemChecked(STATPOINTS,pref.showStatPoints);
    statisticsMenu->setItemChecked(STATLINES,pref.showStatLines);
    coordinateMenu->setItemChecked(SHOWAXES,pref.axis);
    coordinateMenu->setItemChecked(SHOWLABELS,pref.label);
    coordinateMenu->setItemChecked(SHOWRASTER,pref.raster);
    coordinateMenu->setItemChecked(CONSTRATIO,pref.autosize);
    viewMenu->setItemChecked(VIEWCALC1,pref.showWindows[0]);
    viewMenu->setItemChecked(VIEWCALC2,pref.showWindows[1]);
    viewMenu->setItemChecked(VIEWGRAPH,pref.showWindows[2]);
    viewMenu->setItemChecked(VIEWTABLE,pref.showWindows[3]);
    viewMenu->setItemChecked(VIEWMATRIX,pref.showWindows[4]);
    viewMenu->setItemChecked(VIEWSTATISTICS,pref.showWindows[5]);
    viewMenu->setItemChecked(VIEWSCRIPTING,pref.showWindows[6]);
    viewMenu->setItemChecked(VIEWSCRIPTIO,pref.showWindows[7]);
}

void MainObject::writeUIState()
{
	FILE*configFile;
	chdir(getenv("HOME"));
	configFile = fopen(UIFILE,"w");
	if(configFile == NULL)
		return;
	//0             1              2..7
	//window width, window height, function table column 1-6
	int buffer[8];
	buffer[0]=width();
	buffer[1]=height();
	graph->getUIState(&buffer[2]);
	
	fwrite(buffer,8*sizeof(int),1,configFile);

	fclose(configFile);
}

void MainObject::readUIState()
{
	chdir(getenv("HOME"));
	int fileLen;
	struct stat fileStat;

	if(lstat(UIFILE,&fileStat) != 0)
		return;
	else fileLen=fileStat.st_size;
	
	if(fileLen!=8*sizeof(int))
		return;
	
	FILE*configFile = fopen(UIFILE,"r");
	if(configFile == NULL)
		return;
	
	
	int buffer[8];
	fread(buffer,8*sizeof(int),1,configFile);
	
	resize(buffer[0],buffer[1]);
	graph->setUIState(&buffer[2]);

	fclose(configFile);
}

//#config color...
//#config type...
//#config dynamicon/off
//#config logicon/off
//function
void MainObject::readFunctionFile(QString name)
{
	chdir(getenv("HOME"));
	int fileLen;
	struct stat fileStat;

	if(lstat(name,&fileStat) != 0)
	{
		ErrorBox(tr("Unable to read file %1\n\n").arg(name));
		return;
	}
	else fileLen=fileStat.st_size;
	
	
	FILE*configFile = fopen(name,"r");
	if(configFile == NULL)
	{
		ErrorBox(tr("Unable to read graphs file %1\n\n").arg(name));
		return;
	}
	
	int pos1=0,pos2=0,functionCount=0;
	QString config[5],func,comment;
	
	char* buffer=new char[fileLen+1];
	buffer[fileLen]=(char)0;
	fread(buffer,fileLen,1,configFile);

	QString file(buffer);
	delete[] buffer;
	fclose(configFile);
	

	
	if(file.find("#config active")==-1)	//compatibility with v0.9.1 export format
		file.replace("#config color","#config activeoff\n#config color");

	
	if(file.find("#config coordinates")==0)
	{
		int pos1=file.find("#config coordinates");
		pos1+=20;
		int pos2=file.find("\n",pos1);
		
		QString coordinates=file.mid(pos1,pos2-pos1);
		file=file.right(file.length()-pos2-1);
		QStringList coordinatesList=QStringList::split(" ",coordinates);
		if(coordinatesList.count()>22)
		{
			pref.xmin=coordinatesList[0].toDouble();
			pref.xmax=coordinatesList[1].toDouble();
			pref.ymin=coordinatesList[2].toDouble();
			pref.ymax=coordinatesList[3].toDouble();
			pref.zmin=coordinatesList[4].toDouble();
			pref.zmax=coordinatesList[5].toDouble();
			pref.rasterSizeX=coordinatesList[6].toDouble();
			pref.rasterSizeY=coordinatesList[7].toDouble();
			pref.rasterSizeZ=coordinatesList[8].toDouble();
			pref.radiusMax=coordinatesList[9].toDouble();
			pref.angleMax=coordinatesList[10].toDouble();
			pref.rasterSizeRadius=coordinatesList[11].toDouble();
			pref.rasterSizeAngle=coordinatesList[12].toDouble();
			pref.parameterStart=coordinatesList[13].toDouble();
			pref.parameterEnd=coordinatesList[14].toDouble();
			pref.dynamicStart=coordinatesList[15].toDouble();
			pref.dynamicEnd=coordinatesList[16].toDouble();
			pref.nyquistStart=coordinatesList[17].toDouble();
			pref.nyquistEnd=coordinatesList[18].toDouble();
			pref.tableXStart=coordinatesList[19].toDouble();
			pref.tableXEnd=coordinatesList[20].toDouble();
			pref.tableZStart=coordinatesList[21].toDouble();
			pref.tableZEnd=coordinatesList[22].toDouble();
			
			if(pref.xmin>=pref.xmax || pref.ymin>=pref.ymax || pref.zmin>=pref.zmax)
			{
				pref.xmin=pref.ymin=pref.zmin=-10.0;
				pref.xmax=pref.ymax=pref.zmax=10.0;
			}
			if(pref.rasterSizeX <=0 || pref.rasterSizeY<=0 || pref.rasterSizeZ<=0 || pref.rasterSizeAngle<=0 || pref.rasterSizeRadius)
				pref.rasterSizeX=pref.rasterSizeY=pref.rasterSizeZ=pref.rasterSizeAngle=pref.rasterSizeRadius=1.0;
			if(pref.angleMax<=0)
				pref.angleMax=2*PI;
			if(pref.radiusMax<=0)
				pref.radiusMax=10.0;
			if(pref.parameterStart>=pref.parameterEnd || pref.dynamicStart>=pref.dynamicEnd || pref.nyquistStart>=pref.nyquistEnd || pref.tableXStart>=pref.tableXEnd || pref.tableZStart>=pref.tableZEnd)
			{
				pref.parameterStart=pref.dynamicStart=pref.nyquistStart=pref.tableXStart=pref.tableZStart=0.0;
				pref.parameterEnd=pref.dynamicEnd=pref.nyquistEnd=pref.tableXEnd=pref.tableZEnd=10.0;
			}
		}
	}
	if(file.find("#config steps")==0)
	{
		int pos1=file.find("#config steps");
		pos1+=14;
		int pos2=file.find("\n",pos1);
		
		QString coordinates=file.mid(pos1,pos2-pos1);
		file=file.right(file.length()-pos2-1);
		QStringList coordinatesList=QStringList::split(" ",coordinates);
		if(coordinatesList.count()>7)
		{
			pref.parameterSteps=coordinatesList[0].toInt();
			pref.dynamicSteps=coordinatesList[1].toInt();
			pref.dynamicDelay=coordinatesList[2].toInt();
			pref.nyquistSteps=coordinatesList[3].toInt();
			pref.prec2dSteps=coordinatesList[4].toInt();
			pref.prec3dSteps=coordinatesList[5].toInt();
			pref.tableXSteps=coordinatesList[6].toInt();
			pref.tableZSteps=coordinatesList[7].toInt();
			
			if(pref.parameterSteps<=0 || pref.nyquistSteps<=0 || pref.prec2dSteps<=0)
				pref.parameterSteps=pref.nyquistSteps=pref.prec2dSteps=200;
			if(pref.dynamicSteps<=0)
				pref.dynamicSteps=30;
			if(pref.tableXSteps<=0 || pref.tableZSteps <=0 || pref.dynamicDelay<=0)
				pref.tableXSteps=pref.tableZSteps=pref.dynamicDelay=10;
			if(pref.prec3dSteps<=0)
				pref.prec3dSteps=50;
		}
	}
	
	if(file.find("#config flags")==0)
	{
		int pos1=file.find("#config flags");
		pos1+=14;
		int pos2=file.find("\n",pos1);
		
		QString coordinates=file.mid(pos1,pos2-pos1);
		file=file.right(file.length()-pos2-1);
		QStringList coordinatesList=QStringList::split(" ",coordinates);
		if(coordinatesList.count()>2)
		{
			pref.moveUpDown=(bool)coordinatesList[0].toInt();
			pref.show3dGrid=(bool)coordinatesList[1].toInt();
			pref.logNyquistSteps=(bool)coordinatesList[2].toInt();

		}
	}
	if(file.find("#config types")==0)
	{
		int pos1=file.find("#config types");
		pos1+=14;
		int pos2=file.find("\n",pos1);
		
		QString coordinates=file.mid(pos1,pos2-pos1);
		file=file.right(file.length()-pos2-1);
		QStringList coordinatesList=QStringList::split(" ",coordinates);
		if(coordinatesList.count()>1)
		{
			pref.graphType=coordinatesList[0].toInt();
			pref.tableType=coordinatesList[1].toInt();
			
			if(pref.graphType!=GRAPHSTD && pref.graphType !=GRAPHPOLAR && pref.graphType!=GRAPH3D)
				pref.graphType=GRAPHSTD;
			if(pref.tableType!=TABLENORMAL && pref.tableType !=TABLEPOLAR && pref.tableType!=TABLE3D && pref.tableType!=TABLEPARAMETER && pref.tableType !=TABLECOMPLEX && pref.tableType!=TABLEINEQUALITY)
				pref.tableType=TABLENORMAL;

		}
	}

	pos1=pos2=0;
	while(1)
	{
		for(int c=0; c<5; c++)
		{
			pos1=file.find("#config ",pos2);
			if(pos1==-1)
				break;
			pos1+=8;
			pos2=file.find("\n",pos1);
			if(pos2==-1)
				break;
			config[c]=file.mid(pos1,pos2-pos1);
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


		pos1=config[0].find("active");
		if(pos1==-1)
			break;
		config[0]=config[0].right(config[0].length()-6-pos1);
		if(config[0]=="on")
			pref.activeFunctions[functionCount]=true;
		else pref.activeFunctions[functionCount]=false;
		
		pos1=config[1].find("color");
		if(pos1==-1)
			break;
		config[1]=config[1].right(config[1].length()-pos1-5);
		pref.functionColors[functionCount]=getColor(config[1]);
		
		
		pos1=config[2].find("type");
		if(pos1==-1)
			break;
		config[2]=config[2].right(config[2].length()-4-pos1);
		

		if(config[2].lower() == "nyquist3d")
			pref.functionTypes[functionCount]=GRAPHCOMP3D;
		else if(config[2].lower() == "parameter")
			pref.functionTypes[functionCount]=GRAPHPARAMETER;
		else if(config[2].lower() == "polar")
			pref.functionTypes[functionCount]=GRAPHPOLAR;
		else if(config[2].lower() == "3d")
			pref.functionTypes[functionCount]=GRAPH3D;
		else if(config[2].lower() == "iel")
			pref.functionTypes[functionCount]=GRAPHIEL;
		else if(config[2].lower() == "iele")
			pref.functionTypes[functionCount]=GRAPHIELE;
		else if(config[2].lower() == "ieg")
			pref.functionTypes[functionCount]=GRAPHIEG;
		else if(config[2].lower() == "iege")
			pref.functionTypes[functionCount]=GRAPHIEGE;
		else if(config[2].lower() == "nyquist2d")
			pref.functionTypes[functionCount]=GRAPHCOMPLEX;
		else pref.functionTypes[functionCount]=GRAPHSTD;
		
		pos1=config[3].find("dynamic");
		if(pos1==-1)
			break;
		config[3]=config[3].right(config[3].length()-7-pos1);
		if(config[3]=="on")
			pref.dynamicFunctions[functionCount]=true;
		else pref.dynamicFunctions[functionCount]=false;
		
		pos1=config[4].find("logic");
		if(pos1==-1)
			break;
		config[4]=config[4].right(config[4].length()-5-pos1);
		if(config[4]=="on")
			pref.logicFunctions[functionCount]=true;
		else pref.logicFunctions[functionCount]=false;

		pref.functions[functionCount]=resetConfigString(func);
		pref.functionComments[functionCount]=comment;
		functionCount++;
	}
	for(int c=functionCount; c<20; c++)
	{
		pref.functions[c]=QString();
		pref.functionComments[c]=QString();
		pref.activeFunctions[c]=false;
		pref.functionColors[c]=QColor(0,0,0);
		pref.logicFunctions[c]=false;
		pref.functionTypes[c]=GRAPHSTD;
		pref.dynamicFunctions[c]=false;
	}
	getPref(pref);
}


void MainObject::writeFunctionFile(QString name)
{
	FILE*configFile;
	chdir(getenv("HOME"));
	configFile = fopen(GRAPHSDIR+name,"w");
	if(configFile == NULL)
	{
		ErrorBox(tr("Unable to write graphs file %1\n\n").arg(GRAPHSDIR+name));
		return;
	}
	QString expFile("");
	
	//write preferences
	expFile+="#config coordinates ";
	expFile+=QString::number(pref.xmin)+" ";
	expFile+=QString::number(pref.xmax)+" ";
	expFile+=QString::number(pref.ymin)+" ";
	expFile+=QString::number(pref.ymax)+" ";
	expFile+=QString::number(pref.zmin)+" ";
	expFile+=QString::number(pref.zmax)+" ";
	expFile+=QString::number(pref.rasterSizeX)+" ";
	expFile+=QString::number(pref.rasterSizeY)+" ";
	expFile+=QString::number(pref.rasterSizeZ)+" ";
	expFile+=QString::number(pref.radiusMax)+" ";
	expFile+=QString::number(pref.angleMax)+" ";
	expFile+=QString::number(pref.rasterSizeRadius)+" ";
	expFile+=QString::number(pref.rasterSizeAngle)+" ";
	expFile+=QString::number(pref.parameterStart)+" ";
	expFile+=QString::number(pref.parameterEnd)+" ";
	expFile+=QString::number(pref.dynamicStart)+" ";
	expFile+=QString::number(pref.dynamicEnd)+" ";
	expFile+=QString::number(pref.nyquistStart)+" ";
	expFile+=QString::number(pref.nyquistEnd)+" ";
	expFile+=QString::number(pref.tableXStart)+" ";
	expFile+=QString::number(pref.tableXEnd)+" ";
	expFile+=QString::number(pref.tableZStart)+" ";
	expFile+=QString::number(pref.tableZEnd)+"\n";

	expFile+="#config steps ";
	expFile+=QString::number(pref.parameterSteps)+" ";
	expFile+=QString::number(pref.dynamicSteps)+" ";
	expFile+=QString::number(pref.dynamicDelay)+" ";
	expFile+=QString::number(pref.nyquistSteps)+" ";
	expFile+=QString::number(pref.prec2dSteps)+" ";
	expFile+=QString::number(pref.prec3dSteps)+" ";
	expFile+=QString::number(pref.tableXSteps)+" ";
	expFile+=QString::number(pref.tableZSteps)+"\n";

	expFile+="#config flags ";
	expFile+=QString::number(pref.moveUpDown)+" ";
	expFile+=QString::number(pref.show3dGrid)+" ";
	expFile+=QString::number(pref.logNyquistSteps)+"\n";
	
	expFile+="#config types ";
	expFile+=QString::number(pref.graphType)+" ";
	expFile+=QString::number(pref.tableType)+"\n";



	for(int c=0; c<20; c++)
	{
		expFile+="#config active";
		if(pref.activeFunctions[c])
			expFile+="on\n";
		else expFile+="off\n";
		expFile+="#config color"+getColorName(pref.functionColors[c])+"\n";
		expFile+="#config type";
		switch(pref.functionTypes[c])
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
		if(pref.dynamicFunctions[c])
			expFile+="on\n";
		else expFile+="off\n";
		expFile+="#config logic";
		if(pref.logicFunctions[c])
			expFile+="on\n";
		else expFile+="off\n";
		expFile+="//"+pref.functionComments[c]+"\n";
		expFile+=cleanConfigString("",pref.functions[c])+"\n";
		
	}
	fwrite(expFile.latin1(),expFile.length(),1,configFile);

	fclose(configFile);
}

void MainObject::readGraphsDir()
{
	if(graphsDir==NULL)
	{
		graphsDir=new QDir(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR));
		if(!graphsDir->exists())
		{
			graphsDir->mkdir(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR));
			if(!graphsDir->exists())
			{
				ErrorBox(tr("Unable to create graphs directory %1\n\n").arg(QString(getenv("HOME"))+"/"+QString(GRAPHSDIR)));
				return;
			}
		}
	}
	QStringList dirEntries=graphsDir->entryList(QDir::Files);
	if(dirEntries.empty())
	{
		writeFunctionFile("std");
		dirEntries=graphsDir->entryList(QDir::Files);
		pref.currentSet="std";
	}

	graphSetMenu->clear();
	QAction*tmpAction;

	for(int c=0; c<dirEntries.count(); c++)
	{
		//int id=graphSetMenu->insertItem(dirEntries[c]);
		tmpAction=graphSetMenu->addAction(dirEntries[c]);
		tmpAction->setData(QVariant(c));
		tmpAction->setCheckable(true);
		if(dirEntries[c]==pref.currentSet)
			tmpAction->setChecked(true);
		
		connect(tmpAction,SIGNAL(triggered()),graphSetMapper,SLOT(map()));
		graphSetMapper->setMapping(tmpAction,c);
		graphSetActions->addAction(tmpAction);
		//	graphSetMenu->setItemChecked(id,true);
	}
}



HelpBrowser::HelpBrowser(QWidget*parent) :QWidget(parent,"Help Browser",Qt::WType_TopLevel)
{
	currentSource="";
	toolBar=new Q3ToolBar();
	dockArea=new Q3DockArea(Qt::Horizontal,Q3DockArea::Normal,this);
	dockArea->moveDockWindow(toolBar);
	toolBar->setMovingEnabled(false);
	
	forwardIcon=new QPixmap(INSTALLDIR+QString("/data/forward.png"));
	backIcon=new QPixmap(INSTALLDIR+QString("/data/back.png"));
	zoominIcon=new QPixmap(INSTALLDIR+QString("/data/zoomin.png"));
	zoomoutIcon=new QPixmap(INSTALLDIR+QString("/data/zoomout.png"));
	
	browser=new Q3TextBrowser(this);
	
	backButton=new QToolButton(*backIcon,"","",browser,SLOT(backward()),toolBar);	
	forwardButton=new QToolButton(*forwardIcon,"","",browser,SLOT(forward()),toolBar);
	zoominButton=new QToolButton(*zoominIcon,"","",this,SLOT(zoominSlot()),toolBar);
	zoomoutButton=new QToolButton(*zoomoutIcon,"","",this,SLOT(zoomoutSlot()),toolBar);
	
	forwardButton->setOn(false);
	backButton->setOn(false);

	connect(browser,SIGNAL(forwardAvailable(bool)),forwardButton,SLOT(setOn(bool)));
	connect(browser,SIGNAL(backwardAvailable(bool)),backButton,SLOT(setOn(bool)));
	connect(browser,SIGNAL(sourceChanged(const QString&)),this,SLOT(sourceSlot(const QString&)));

	
}
void HelpBrowser::setContent(QString path)
{
	browser->setSource(path);
	currentSource=path;
}

void HelpBrowser::zoominSlot()
{
	browser->zoomIn(2);
	browser->repaint();
}

void HelpBrowser::zoomoutSlot()
{
		browser->zoomOut(2);
		browser->repaint();

}

void HelpBrowser::sourceSlot(const QString &source)
{
	if(currentSource!="" && source.find(currentSource)!=0)
		browser->setSource(currentSource);
}

void HelpBrowser::resizeEvent(QResizeEvent*)
{
	dockArea->setGeometry(0,0,width(),35);
	browser->setGeometry(0,35,width(),height()-35);
}


InfoDialog::InfoDialog(QWidget*parent) : QDialog(parent)
{
	layout=new QGridLayout(this);
	tabWidget=new QTabWidget(this);
	layout->addWidget(tabWidget,0,0);
	licenseWidget=new QTextEdit(tabWidget);
	QString license;
	FILE*licenseFile;
	struct stat fileStat;
	licenseFile = fopen(INSTALLDIR+QString("/data/license.txt"),"r");
	if(licenseFile == NULL)
		license=EXTCALCH_STR1;
	else {
		if(lstat(INSTALLDIR+QString("/data/license.txt"),&fileStat) !=0)
			MessageBox(EXTCALCH_MSG2);
		else
		{
			char*cLicenseText=new char[fileStat.st_size+1];
			cLicenseText[fileStat.st_size]=(char)0;
			fread((void*)cLicenseText,fileStat.st_size,1,licenseFile);
			license=EXTCALCH_STR2;
			license+=QString(cLicenseText);
			delete[]cLicenseText;
		}
		fclose(licenseFile);
	}
	licenseWidget->setText(license);
	licenseWidget->setReadOnly(true);
	authorInfo=new QLabel(INFOSTRING+QString(AUTHORSTRING),tabWidget);
	versionInfo=new QLabel(INFOSTRING+QString(VERSIONSTRING),tabWidget);
	authorInfo->setAlignment(Qt::AlignAuto | Qt::AlignCenter | Qt::ExpandTabs);
	versionInfo->setAlignment(Qt::AlignAuto | Qt::AlignCenter | Qt::ExpandTabs);
	tabWidget->addTab(versionInfo,EXTCALCH_STR3);
	tabWidget->addTab(authorInfo,EXTCALCH_STR4);
	tabWidget->addTab(licenseWidget,EXTCALCH_STR5);
}





