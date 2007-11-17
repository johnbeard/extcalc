/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         extcalc.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This file contains the main window class of extcalc and a class for the script import/export
dialog, the todo list and the bug list.

////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef EXTCALCH
#define EXTCALCH


#include "graph.h"
#include "calcwidget.h"
#include "graphpref.h"
#include "calcpref.h"
#include "tablepref.h"
#include "scriptpref.h"
#include "table.h"
#include "scriptedit.h"
#include "scriptio.h"
#include "matrixwidget.h"
#include "statistics.h"
#include "global.h"
#include <qtabwidget.h>
#include <qtabbar.h>
#include <qstring.h>
#include <qmenubar.h>
#include <qprocess.h>
#include <qtabdialog.h>
#include <float.h>
#include <qtranslator.h>
#include <locale.h>


//Unicode characters:
//
//Wurzel	8730
//Pi		960
//Euler		65349 (1214)
//Mega		65325 (1052)
//Giga		65319 (1292)
//Terra		65332 (1196)
//Integral	8747




/////////////////////////////////////////////TODO/////////////////////////////////////////////
//                                                                                          //
//  - GUI with tabs                                                                     ok  //
//  - changable button objects                                                          ok  //
//  - input- and output-window for calculations                                         ok  //
//  - output-window for graphs                                                          ok  //
//  - table for graph-functions                                                         ok  //
//  - menus                                                                             ok  //
//  - graphic preferences menu                                                          ok  //
//  - calculator preferences menu                                                       ok  //
//  - calculator preferences dialog                                                     ok  //
//  - graphic preferences dialog                                                        ok  //
//  - info and help dialog                                                              ok  //
//  - fullscreen function for graphics and calculator                                   ok  //
//  - mathematical parser                                                               ok  //
//  - scientific functions for calculator                                               ok  //
//  - make math algorithms compatible with Calc project                                 ok  //
//  - integration differentiation                                                       ok  //
//  - optimized parser for graphics and integration                                     ok  //
//  - make calculator algorithms compatible with standard c++ (no QT)                   ok  //
//  - graph analyzation                                                                 ok  //
//      - x-values                                                                      ok  //
//      - y-values                                                                      ok  //
//      - roots                                                                         ok  //
//      - newtons's method                                                              ok  //
//      - points of intersection                                                        ok  //
//      - extreme values                                                                ok  //
//      - integration                                                                   ok  //
//      - differentiation                                                               ok  //
//  - logical functions (& | ...) for standard-parser           (v0.2)                  ok  //
//  - base-n calcualations in hex, oct, bin                     (v0.2)                  ok  //
//  - different types of 2d-graphs                              (v0.3)                  ok  //
//      - standard 2D-functions                                                         ok  //
//      - Parameter functions (X=T, Y=T)                                                ok  //
//      - polar coordinate functions (r=X)                                              ok  //
//      - inequaity functions (Y>, Y<, Y>=, Y<=)                                        ok  //
//      - dynamc graphs Y=AX                                                            ok  //
//  - 3d-graphs                                                 (v0.3)                  ok  //
//  - tables                                                    (v0.3)                  ok  //
//  - updating graph analysation functions                      (v0.4)                  ok  //
//      - areas of intersection (inequaity functions)                                   ok  //
//      - roots of inequaity functions                                                  ok  //
//      - setting Parameter A for dynamic functions                                     ok  //
//      - integral and differential of 3D-functions (in a later version)                ok  //
//  - script interpretor                                        (v0.5)                  ok  //
//  - script language                                           (v0.5)                  ok  //
//      - standard commands: if, for, while                                             ok  //
//      - compare operations: == != > < >= <=                                           ok  //
//      - jumps: continue, break, exit                                                  ok  //
//      - input functions: getline, getkey, keystate                                    ok  //
//      - text output functions: print, set, clearText                                  ok  //
//      - logic operations and, or, not                                                 ok  //
//      - type converting (int) (float) ...                                             ok  //
//      - Arrays                                                                        ok  //
//      - run other scripts: run                                                        ok  //
//      - 2D-graph output functions: point, line, circle, ... (in a later version)      ok  //
//      - OpenGL 3D-Graphics (in a later version)                                       ok  //
//      - usage of files (in a later version)                                           ok  //
//      - change preferences (in a later version)                                       ok  //
//      - macros (in a later version)                                                   ok  //
//      - script debugging tool                                                         ok  //
//  - load and save scripts                                     (v0.5)                  ok  //
//  - script editor window                                      (v0.5)                  ok  //
//  - manipulating and saving images                            (v0.6)                  ok  //
//  - zooming and moving graphics-window                        (v0.6)                  ok  //
//  - number object for standard-parser                         (v0.7)                  ok  //
//  - support for complex numbers in standard parser            (v0.7)                  ok  //
//  - include matrix- vector- ...-functions to standard-parser  (v0.7)                  ok  //
//  - window for vector calculations                            (v0.8)                  ok  //
//  - window for matrix calculations                            (v0.8)                  ok  //
//  - statistic functions                                       (v0.9 beta)             ok  //
//  - beta-tests, bugfixing, optimizing                         (v1.0 stable)               //
/////////////////////////////////////////////TODO/////////////////////////////////////////////


////////////////////////////////////////beta releases/////////////////////////////////////////
//                                                                                          //
//  - reorganisation of the checkString and script preprocessor functions               ok  //
//  - optimization of the split and parse methods                                           //
//  - change structure of exec and calc methods                                             //
//  - standardized user interface design for all tabs                                   ok  //
//  - open help file in default browser                                                     //
//  - integrate constants list                                                              //
//  - precise error messages                                                            ok  //
//  - RPN                                                                                   //
//  - Port to QT 4                                                                          //
//  - use QTranslator for internationalization                                          ok  //
//  - symbolic calculation for systems of linear equations                                  //
//                                                                                          //
////////////////////////////////////////beta releases/////////////////////////////////////////


/////////////////////////////////////////////bugs/////////////////////////////////////////////
//																							//
//	- Menu for number of output-Digits doesn't work										ok	//
//	- Colors in gaphic analysation window are not resetted								ok	//
//	- some buttons of calculator don't move if window switches to fullscreen mode		ok	//
//	- buffer overflow at some functions													ok	//
//	- wrong text at some graph analysation options										ok	//
//	- calculation of roots doesn't work													ok	//
//	- Newton's method doesn't work														ok	//
//	- function box in graph solve window is sometimes empty								ok	//
//	- script editor saves unicode wrong													ok	//
//	- calculaton repeating doesn't work with second line								ok	//
//	- integral calculation doesn't work on periodic functions							ok	//
//	- graph analyse window doesn't view result of integral correctly					ok	//
//	- graph analyse window does not allways process mouse events						ok	//
//	- preferences dialogs can't process mathematical expressions						ok  //
//	- Script editor has no Menu bar														ok	//
//	- converting floating point values does not work for all locale settings			ok	//
//	- asymptotes are not alsways shown correctly										ok	//
//	- calculator keys must be sorted													ok	//
//	- Size of output-table in GraphSolveWidget is not resized							ok	//
//	- text copying does not work in script console										ok	//
//	- changing angle type does not work													ok	//
//	- changing analyse precision does not work											ok	//
//	- some script commands may cause problems in calculator mode						ok	//
//	- recalculaton of 3d-graphs and parameter graphs is not needed						ok	//
//	- automatic ans inserting does not work corectly									ok	//
//	- dynamic graphs are not shown correctly when coordinate system is moved			ok	//
//	- debug messages in graph calculation												ok	//
//	- CPU-load is 100% when waiting for keyboart input									ok	//
//	- 3rd, 5th ... root of  N returns only complex results								ok	//
//	- result lines in polar cs were drawn wrong when angle type isn't rad				ok	//
//	- array memory can't be deleted														ok	//
//	- script load balancing doesn't work on fast (dual-core) CPUs						ok	//
//	- inserting text into a running script doesn't work									ok	//
//	- gl script programming does not work on every system								ok	//
//	- import script dialog path check is wrong											ok	//
//	- bug in script console at selection												ok	//
//	- file dialog in script preferences window is always in background					ok	//
//	- view error when maximizing statistics tab											ok	//
//	- directory creation at first start does not work									ok	//
//	- command priority in script interpreter wrong										ok	//
//	- autosize setting leads to wrong screenshot size									ok	//
//	- abs does not exist in standard calculator class										//


//////////////////////////used variables//////////////////////////
//
//      Type: double
//      sign         exponent            mantisse
//      |+/-      |  +/-308     |          1.7*10^15             |
//      63       62             52                               0
//
//      Type: long double (12 Byte at 32bit CPU; 10 Bytes were used)
//      sign         exponent            mantisse
//      |+/-      |  +/-4932     |        1.2*10^18               |
//      79        78             63            5                   0
//
//
//		precision: 
//		18 digits in normal mode
//		17 digits in trigonometric functions
//		ca. 9 digits at integrations
//		ca. 8 digits at differentiations


//////////////////////////////Operations/////////////////////////////
//
//  binary operators:
// + -
// * /
// ^ root %
// && || 
// & | xor
//
// unary operators with argument right
// sin cos tan
// asin acos atan
// sinh cosh tanh
// asinh acosh atanh
// log ln exp
// sqrt curt
// not ~
//
// unary operatos with argument left
// !
//
// operators with argument list
// d/dx integral
//
// special operations
// Variables A-Z
// numbers 10 0.34 -34e-6 .456 34.e+43 hex4FA7C bin100010111 


//////////////////////////////Parser:///////////////////////////////
//                                                                //
//                      2 - 5*6 + (6*4+3)                         //
//process sums:        /      |        \                          //
//                  2        5*6        6*4+3                     //
//                 OK       MULT         SUM                      //
//process multiblications:  /  \         |  \                     //
//                         5    6        |   \                    //
//process sums:           OK    OK       |    \                   //
//                                      6*4    3                  //
//                                     MULT    OK                 //
//process multiblications:             /  \                       //
//                                    6   4                       //
//                                   OK   OK                      //
//                                                                //
////////////////////////////////////////////////////////////////////

class ImportDialog;

class MainObject :public QTabWidget
{
	QMenuBar*mainMenu;
	QPopupMenu *calcMenu,*angleMenu,*helpMenu,*outputMenu,*floatPointMenu,*prefMenu,*graphMenu;
	QPopupMenu *coordinateMenu,*graphTypeMenu,*calcTypeMenu,*baseMenu,*tableMenu,*tableTypeMenu;
	QPopupMenu *editMenu,*viewMenu,*fileMenu,*scriptMenu,*statisticsMenu,*languageMenu;
	QTabBar*tabBar;
	CalcWidget *calculator,*calculator2;
	GraphWidget * graph;
	GraphPreferences*grPref;
	CalcPreferences*calcPref;
	TablePreferences*tablePref;
	ScriptPreferences*scriptPref;
	ImportDialog*importDialog;
	ImportDialog*exportDialog;
	TableWidget*table;
	ScriptWidget*scripting;
	ScriptIOWidget*scriptIO;
	MatrixWidget*matrix;
	StatisticsWidget*statistics;
	Preferences pref;
	QProcess*helpProcess;
	QTabDialog*infoDialog;
	QTextEdit*licenseWidget;
	QLabel*authorInfo;
	QLabel*versionInfo;
	QPixmap*appIcon;
	Variable *vars;
	Vector *vecs;
	bool calcFocus;
	bool calcModeChanged;
	ThreadSync*threadData;

Q_OBJECT
public:
MainObject() :QTabWidget()
{

	vars=new Variable [27];
	for(int c=0; c<27;c++)
		vars[c]=0.0;
	Number n0;
	n0.type=NFLOAT;
	vecs=new Vector [VARNUM];
	for(int c=0; c<VARNUM;c++)
		vecs[c].NewItem(n0);
	
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
	helpProcess=new QProcess(this);
	
	infoDialog=new QTabDialog(this,0,true);
	licenseWidget=new QTextEdit(infoDialog);
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
	authorInfo=new QLabel(INFOSTRING+QString(AUTHORSTRING),infoDialog);
	versionInfo=new QLabel(INFOSTRING+QString(VERSIONSTRING),infoDialog);
	authorInfo->setAlignment(Qt::AlignAuto | Qt::AlignCenter | Qt::ExpandTabs);
	versionInfo->setAlignment(Qt::AlignAuto | Qt::AlignCenter | Qt::ExpandTabs);
	infoDialog->addTab(versionInfo,EXTCALCH_STR3);
	infoDialog->addTab(authorInfo,EXTCALCH_STR4);
	infoDialog->addTab(licenseWidget,EXTCALCH_STR5);

		
	
	
	grPref=NULL;
	calcPref=NULL;
	tablePref=NULL;
	scriptPref=NULL;
	importDialog=NULL;
	exportDialog=NULL;
	
	tabBar = new QTabBar(this);
	
	setTabBar(tabBar);
		
	
	mainMenu=new QMenuBar(this);

	
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


	threadData=new ThreadSync;
	threadData->mutex=NULL;
	threadData->eventReciver=this;
	threadData->status=0;
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


	angleMenu=new QPopupMenu;
	angleMenu->insertItem(EXTCALCH_MENU1,DEG);
	angleMenu->insertItem(EXTCALCH_MENU2,RAD);
	angleMenu->insertItem(EXTCALCH_MENU3,GRA);
	QObject::connect(angleMenu,SIGNAL(activated(int)),this,SLOT(angleMenuSlot(int)));
	
	floatPointMenu=new QPopupMenu;
	for(int c=2;c<=pref.precision; c++)
		floatPointMenu->insertItem(QString::number(c),c);

	QObject::connect(floatPointMenu,SIGNAL(activated(int)),this,SLOT(floatPointMenuSlot(int)));

	outputMenu=new QPopupMenu;
	outputMenu->insertItem(EXTCALCH_MENU4,FIXEDNUM);
	outputMenu->insertItem(EXTCALCH_MENU5,VARIABLENUM);
	outputMenu->insertItem(EXTCALCH_MENU6,EXPSYM);
	outputMenu->insertItem(EXTCALCH_MENU7,floatPointMenu,FLOATPOINT);
	QObject::connect(outputMenu,SIGNAL(activated(int)),this,SLOT(outputMenuSlot(int)));
	floatPointMenu->setItemChecked(pref.outputLength,true);
	
	baseMenu=new QPopupMenu;
	baseMenu->insertItem(EXTCALCH_MENU27,BIN);
	baseMenu->insertItem(EXTCALCH_MENU28,OCT);
	baseMenu->insertItem(EXTCALCH_MENU29,DEC);
	baseMenu->insertItem(EXTCALCH_MENU30,HEX);
	QObject::connect(baseMenu,SIGNAL(activated(int)),this,SLOT(baseMenuSlot(int)));
	
	calcTypeMenu=new QPopupMenu;
	calcTypeMenu->insertItem(EXTCALCH_MENU31,SCIENTIFIC);
	calcTypeMenu->insertItem(EXTCALCH_MENU32,BASE);
	calcTypeMenu->insertItem(EXTCALCH_MENU67,COMPLEXMENU);
	calcTypeMenu->insertItem(EXTCALCH_MENU33,baseMenu,BASEMENU);
	QObject::connect(calcTypeMenu,SIGNAL(activated(int)),this,SLOT(calcTypeMenuSlot(int)));
	baseMenu->setItemChecked(pref.base,true);
	
	calcMenu=new QPopupMenu;
	calcMenu->insertItem(EXTCALCH_MENU8,angleMenu,ANGLE);
	calcMenu->insertItem(EXTCALCH_MENU9,outputMenu,OUTPUT);
	calcMenu->insertItem(EXTCALCH_MENU34,calcTypeMenu,MODE);
	angleMenu->setItemChecked(pref.angle,true);
	outputMenu->setItemChecked(pref.outputType,true);
	calcTypeMenu->setItemChecked(pref.calcType,true);
	
	coordinateMenu=new QPopupMenu;
	coordinateMenu->insertItem(EXTCALCH_MENU19,STANDARDCOORDS);
	coordinateMenu->insertItem(EXTCALCH_MENU20,TRIGONOMETRICCOORDS);
	coordinateMenu->insertItem(EXTCALCH_MENU21,SHOWAXES);
	coordinateMenu->insertItem(EXTCALCH_MENU22,SHOWLABELS);
	coordinateMenu->insertItem(EXTCALCH_MENU23,SHOWRASTER);
	coordinateMenu->insertItem(EXTCALCH_MENU24,CONSTRATIO);
	QObject::connect(coordinateMenu,SIGNAL(activated(int)),this,SLOT(coordinateMenuSlot(int)));
	
	graphTypeMenu=new QPopupMenu;
	graphTypeMenu->insertItem(EXTCALCH_MENU35,GRAPHSTD);
	graphTypeMenu->insertItem(EXTCALCH_MENU36,GRAPHPOLAR);
	graphTypeMenu->insertItem(EXTCALCH_MENU37,GRAPH3D);
	QObject::connect(graphTypeMenu,SIGNAL(activated(int)),this,SLOT(graphTypeMenuSlot(int)));
	
	graphMenu=new QPopupMenu;
	graphMenu->insertItem(EXTCALCH_MENU25,coordinateMenu,COORDINATE);
	graphMenu->insertItem(EXTCALCH_MENU26,graphTypeMenu,GRAPHTYPE);
	
	tableTypeMenu=new QPopupMenu;
	tableTypeMenu->insertItem(EXTCALCH_MENU38,TABLENORMAL);
	tableTypeMenu->insertItem(EXTCALCH_MENU39,TABLEPOLAR);
	tableTypeMenu->insertItem(EXTCALCH_MENU40,TABLEPARAMETER);
	tableTypeMenu->insertItem(EXTCALCH_MENU41,TABLEINEQUAITY);
	tableTypeMenu->insertItem(EXTCALCH_MENU42,TABLE3D);
	tableTypeMenu->insertItem(EXTCALCH_MENU78,TABLECOMPLEX);
	QObject::connect(tableTypeMenu,SIGNAL(activated(int)),this,SLOT(tableTypeMenuSlot(int)));
	
	tableMenu=new QPopupMenu;
	tableMenu->insertItem(EXTCALCH_MENU43,STANDARDTABLE);
	tableMenu->insertItem(EXTCALCH_MENU68,RESETTABLE);
	tableMenu->insertItem(EXTCALCH_MENU44,tableTypeMenu,TABLETYPE);
	QObject::connect(tableMenu,SIGNAL(activated(int)),this,SLOT(tableMenuSlot(int)));


	scriptMenu=new QPopupMenu;
	scriptMenu->insertItem(EXTCALCH_MENU62,EXPORTSCRIPT);
	scriptMenu->insertItem(EXTCALCH_MENU63,IMPORTSCRIPT);
	scriptMenu->insertSeparator();
	scriptMenu->insertItem(EXTCALCH_MENU64,CLEARMEMALWAYS);
	scriptMenu->insertItem(EXTCALCH_MENU65,CLEARMEMNOW);
	QObject::connect(scriptMenu,SIGNAL(activated(int)),this,SLOT(scriptMenuSlot(int)));
	
	statisticsMenu=new QPopupMenu;
	statisticsMenu->insertItem(EXTCALCH_MENU69,STATCLEAR);
	statisticsMenu->insertItem(EXTCALCH_MENU70,STATAUTOCLEAR);
	statisticsMenu->insertSeparator();
	statisticsMenu->insertItem(EXTCALCH_MENU71,STATPOINTS);
	statisticsMenu->insertItem(EXTCALCH_MENU72,STATLINES);
	QObject::connect(statisticsMenu,SIGNAL(activated(int)),this,SLOT(statisticsMenuSlot(int)));
	
	languageMenu=new QPopupMenu;
	languageMenu->insertItem(tr("English"),LANG_EN);
	languageMenu->insertItem(tr("French"),LANG_FR);
	languageMenu->insertItem(tr("German"),LANG_DE);
	QObject::connect(languageMenu,SIGNAL(activated(int)),this,SLOT(languageMenuSlot(int)));

	
	prefMenu=new QPopupMenu;
	prefMenu->insertItem(EXTCALCH_MENU10,CPREF);
	prefMenu->insertItem(EXTCALCH_MENU11,GPREF);
	prefMenu->insertItem(EXTCALCH_MENU45,TPREF);
	prefMenu->insertItem(EXTCALCH_MENU60,SPREF);
	prefMenu->insertSeparator();
	prefMenu->insertItem(tr("Language"),languageMenu,LPREF);
	
	helpMenu=new QPopupMenu;
	helpMenu->insertItem(EXTCALCH_MENU12,EXTHELP);
	helpMenu->insertItem(EXTCALCH_MENU13,INFO);
	
	editMenu=new QPopupMenu;
	editMenu->insertItem(EXTCALCH_MENU47,EDITUNDO);
	editMenu->insertItem(EXTCALCH_MENU48,EDITREDO);
	editMenu->insertItem(EXTCALCH_MENU49,EDITCUT);
	editMenu->insertItem(EXTCALCH_MENU50,EDITCOPY);
	editMenu->insertItem(EXTCALCH_MENU51,EDITPASTE);
	QObject::connect(editMenu,SIGNAL(activated(int)),this,SLOT(editMenuSlot(int)));
	
	viewMenu=new QPopupMenu;
	viewMenu->insertItem(EXTCALCH_MENU52,VIEWCALC1);
	viewMenu->insertItem(EXTCALCH_MENU53,VIEWCALC2);
	viewMenu->insertItem(EXTCALCH_MENU54,VIEWGRAPH);
	viewMenu->insertItem(EXTCALCH_MENU55,VIEWTABLE);
	viewMenu->insertItem(EXTCALCH_MENU73,VIEWMATRIX);
	viewMenu->insertItem(EXTCALCH_MENU74,VIEWSTATISTICS);
	viewMenu->insertItem(EXTCALCH_MENU56,VIEWSCRIPTING);
	viewMenu->insertItem(EXTCALCH_MENU61,VIEWSCRIPTIO);
	QObject::connect(viewMenu,SIGNAL(activated(int)),this,SLOT(viewMenuSlot(int)));
	
	fileMenu=new QPopupMenu;
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
	
	
	QRect tabbarSize=tabBar->geometry();
	
	mainMenu->setGeometry(tabbarSize.left(),tabbarSize.bottom(),
	tabbarSize.right()-tabbarSize.left(),20);

	

	calculator=new CalcWidget(this,pref,vars,threadData,tabbarSize.bottom());
	calculator2=new CalcWidget(this,pref,vars,threadData,tabbarSize.bottom());
	graph = new GraphWidget(this,pref,vars,threadData,tabbarSize.bottom());
	table=new TableWidget(this,pref,vars,threadData,tabbarSize.bottom());
	scripting=new ScriptWidget(this,pref,vars,tabbarSize.bottom());
	scriptIO=new ScriptIOWidget(this,pref,vars,graph->getShareContext(),tabbarSize.bottom());
	matrix=new MatrixWidget(this,pref,vars,threadData);
	statistics=new StatisticsWidget(this,pref,vars,threadData,tabbarSize.bottom());
//	addTab(calculator,EXTCALCH_STR6);
//	addTab(calculator2,EXTCALCH_STR7);
//	addTab(graph,EXTCALCH_STR8);
//	addTab(table,EXTCALCH_STR9);
//	addTab(scripting,"Scripting");
	calculator->hide();
	calculator2->hide();
	graph->hide();
	table->hide();
	scripting->hide();
	scriptIO->hide();
	matrix->hide();
	statistics->hide();

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
//	QObject::connect(statistics,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
	QObject::connect(this,SIGNAL(currentChanged(QWidget*)),this,SLOT(tabChangeSlot(QWidget*)));
	QObject::connect(this,SIGNAL(editSignal(int)),calculator,SLOT(editSlot(int)));
	QObject::connect(this,SIGNAL(editSignal(int)),calculator2,SLOT(editSlot(int)));
	QObject::connect(this,SIGNAL(editSignal(int)),graph,SLOT(editSlot(int)));
	QObject::connect(this,SIGNAL(editSignal(int)),table,SLOT(editSlot(int)));
	QObject::connect(this,SIGNAL(editSignal(int)),scripting,SLOT(editSlot(int)));
	QObject::connect(this,SIGNAL(editSignal(int)),scriptIO,SLOT(editSlot(int)));
//	QObject::connect(this,SIGNAL(editSignal(int)),matrix,SLOT(editSlot(int)));
//	QObject::connect(this,SIGNAL(editSignal(int)),statistics,SLOT(editSlot(int)));
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
		pref.scriptPath=getenv("HOME")+QString("/.extcalc/script/");
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
	readVarFile();


}

~MainObject()
{
	delete[]vars;
}
int readConfigFile();
void readVarFile();
void writeConfigFile();
void writeVarFile();



protected:

virtual void closeEvent(QCloseEvent*);
virtual void customEvent(QCustomEvent*);

public slots:
void fileMenuSlot(int item);
void editMenuSlot(int item);
void viewMenuSlot(int item);
void angleMenuSlot(int type);
void tabChangeSlot(QWidget*);
void outputMenuSlot(int item);
void coordinateMenuSlot(int item);
void graphTypeMenuSlot(int item);
void floatPointMenuSlot(int item);
void calcTypeMenuSlot(int item);
void baseMenuSlot(int item);
void helpMenuSlot(int item);
void prefMenuSlot(int item);
void languageMenuSlot(int item);
void tableMenuSlot(int item);
void scriptMenuSlot(int item);
void statisticsMenuSlot(int item);
void tableTypeMenuSlot(int item);
void runScriptSlot(QString*);
void changeTabSlot(int);
void getPref(Preferences newPref)
{
	static bool running=false;
	for(int c=2;c<=pref.precision;c++)
		if(floatPointMenu->isItemChecked(c))
			floatPointMenu->setItemChecked(c,false);
	
	

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
	if(((indexOf(calculator)!=-1)!=pref.showWindows[0] ||
		   (indexOf(calculator2)!=-1)!=pref.showWindows[1] ||
		   (indexOf(graph)!=-1)!=pref.showWindows[2] ||
		   (indexOf(table)!=-1)!=pref.showWindows[3] ||
		   (indexOf(matrix)!=-1)!=pref.showWindows[4] || 
			(indexOf(statistics)!=-1)!=pref.showWindows[5] || 
			(indexOf(scripting)!=-1)!=pref.showWindows[6] ||
			(indexOf(scriptIO)!=-1)!=pref.showWindows[7]
	   ) && !running)
	{
		running=true;
		if(indexOf(calculator)!=-1)
			removePage(calculator);
		if(indexOf(calculator2)!=-1)
			removePage(calculator2);
		if(indexOf(graph)!=-1)
			removePage(graph);
		if(indexOf(table)!=-1)
			removePage(table);
		if(indexOf(matrix)!=-1)
			removePage(matrix);
		if(indexOf(statistics)!=-1)
			removePage(statistics);
		if(indexOf(scripting)!=-1)
			removePage(scripting);
		if(indexOf(scriptIO)!=-1)
			removePage(scriptIO);
		if(pref.showWindows[0])
			addTab(calculator,EXTCALCH_STR6);
		if(pref.showWindows[1])
			addTab(calculator2,EXTCALCH_STR7);
		if(pref.showWindows[2])
			addTab(graph,EXTCALCH_STR8);
		if(pref.showWindows[3])
			addTab(table,EXTCALCH_STR9);
		if(pref.showWindows[4])
			addTab(matrix,EXTCALCH_MENU73);
		if(pref.showWindows[5])
			addTab(statistics,EXTCALCH_MENU74);
		if(pref.showWindows[6])
			addTab(scripting,EXTCALCH_STR12);
		if(pref.showWindows[7])
			addTab(scriptIO,EXTCALCH_STR13);
	}
	running=false;

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

	graphTypeMenu->setItemChecked(GRAPHSTD,false);
	graphTypeMenu->setItemChecked(GRAPHPOLAR,false);
	graphTypeMenu->setItemChecked(GRAPH3D,false);

	angleMenu->setItemChecked(DEG,false);
	angleMenu->setItemChecked(RAD,false);
	angleMenu->setItemChecked(GRA,false);

	outputMenu->setItemChecked(FIXEDNUM,false);
	outputMenu->setItemChecked(VARIABLENUM,false);
	outputMenu->setItemChecked(EXPSYM,false);

	calcTypeMenu->setItemChecked(SCIENTIFIC,false);
	calcTypeMenu->setItemChecked(BASE,false);
	calcTypeMenu->setItemChecked(COMPLEXMENU,false);

	baseMenu->setItemChecked(BIN,false);
	baseMenu->setItemChecked(OCT,false);
	baseMenu->setItemChecked(DEC,false);
	baseMenu->setItemChecked(HEX,false);
	
	languageMenu->setItemChecked(LANG_DE,false);
	languageMenu->setItemChecked(LANG_EN,false);
	languageMenu->setItemChecked(LANG_FR,false);

	tableTypeMenu->setItemChecked(TABLENORMAL,false);
	tableTypeMenu->setItemChecked(TABLEPARAMETER,false);
	tableTypeMenu->setItemChecked(TABLEPOLAR,false);
	tableTypeMenu->setItemChecked(TABLEINEQUAITY,false);
	tableTypeMenu->setItemChecked(TABLE3D,false);
	tableTypeMenu->setItemChecked(TABLECOMPLEX,false);

	
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
//	savePref(&pref);

	angleMenu->setItemChecked(pref.angle,true);
	outputMenu->setItemChecked(pref.outputType,true);
	floatPointMenu->setItemChecked(pref.outputLength,true);
	baseMenu->setItemChecked(pref.base,true);
	calcTypeMenu->setItemChecked(pref.calcType,true);
	calcTypeMenu->setItemChecked(COMPLEXMENU,pref.complex);
	calcTypeMenu->setItemEnabled(BASEMENU,calcTypeMenu->isItemChecked(BASE));
	graphTypeMenu->setItemChecked(pref.graphType,true);
	tableTypeMenu->setItemChecked(pref.tableType,true);
	scriptMenu->setItemChecked(CLEARMEMALWAYS,pref.clearScriptMemory);
	statisticsMenu->setItemChecked(STATAUTOCLEAR,pref.statAutoClear);
	statisticsMenu->setItemChecked(STATPOINTS,pref.showStatPoints);
	statisticsMenu->setItemChecked(STATLINES,pref.showStatLines);
	coordinateMenu->setItemChecked(SHOWAXES,pref.axis);
	coordinateMenu->setItemChecked(SHOWLABELS,pref.label);
	coordinateMenu->setItemChecked(SHOWRASTER,pref.raster);
	coordinateMenu->setItemChecked(CONSTRATIO,pref.autosize);
	languageMenu->setItemChecked(pref.language,true);
	viewMenu->setItemChecked(VIEWCALC1,pref.showWindows[0]);
	viewMenu->setItemChecked(VIEWCALC2,pref.showWindows[1]);
	viewMenu->setItemChecked(VIEWGRAPH,pref.showWindows[2]);
	viewMenu->setItemChecked(VIEWTABLE,pref.showWindows[3]);
	viewMenu->setItemChecked(VIEWMATRIX,pref.showWindows[4]);
	viewMenu->setItemChecked(VIEWSTATISTICS,pref.showWindows[5]);
	viewMenu->setItemChecked(VIEWSCRIPTING,pref.showWindows[6]);
	viewMenu->setItemChecked(VIEWSCRIPTIO,pref.showWindows[7]);
}

signals:
	void editSignal(int);
	void runScript(QString*);
	void matrixEnterSignal();
	void removeGraphicsLinesSignal();

};



class ImportDialog :public QWidget
{
	QPushButton*saveButton,*cancelButton,*openDialogButton,*saveDialogButton;
	QLabel *mainLabel,*openPathLabel,*savePathLabel;
	QLineEdit *openPathLine,*savePathLine;
	Preferences pref;
	bool dialog;
	bool importFile;
	
	
	Q_OBJECT
	public:
		ImportDialog(Preferences p,QWidget*parent,bool importF) 
	:QWidget(parent,EXTCALCH_STR14,Qt::WStyle_Dialog | Qt::WType_Dialog)
		{
			pref=p;
			dialog=false;
			importFile=importF;
			
			if(importFile)
			{
				mainLabel=new QLabel(EXTCALCH_STR15,this);
				openPathLabel=new QLabel(EXTCALCH_STR16,this);
				savePathLabel=new QLabel(EXTCALCH_STR17,this);
			}
			else {
				mainLabel=new QLabel(EXTCALCH_STR18,this);
				openPathLabel=new QLabel(EXTCALCH_STR19,this);
				savePathLabel=new QLabel(EXTCALCH_STR17,this);
			}
			openPathLine=new QLineEdit(this);
			savePathLine=new QLineEdit(this);

			saveButton=new QPushButton(SCRIPTPREFH_STR5,this);
			cancelButton=new QPushButton(SCRIPTPREFH_STR6,this);
			openDialogButton=new QPushButton(SCRIPTPREFH_STR7,this);
			saveDialogButton=new QPushButton(SCRIPTPREFH_STR7,this);

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
	
	protected:
		virtual void windowActivationChange(bool);

	public slots:

		void saveSlot();
		void openDialogSlot();
		void saveDialogSlot();
		
	signals:
		void updateScriptSignal(int);
};










#endif
