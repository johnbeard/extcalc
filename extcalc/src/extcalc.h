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
#include "importdialog.h"
#include "graphsetdialog.h"
#include "screenshotdialog.h"
#include <qtabwidget.h>
#include <qtabbar.h>
#include <qstring.h>
#include <qmenubar.h>
#include <q3process.h>
#include <q3tabdialog.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QLabel>
#include <QPixmap>
#include <QCloseEvent>
#include <QCustomEvent>
#include <Q3PopupMenu>
#include <QTabWidget>
#include <float.h>
#include <qtranslator.h>
#include <qinputdialog.h>
#include <locale.h>
#include <q3textbrowser.h>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <qicon.h>
#include <qtoolbutton.h>
#include <qdir.h>
#include <QActionGroup>
#include <QGridLayout>


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
//  - optimization of the split and parse methods                                       ok  //
//  - change structure of exec and calc methods                                             //
//  - standardized user interface design for all tabs                                   ok  //
//  - open help file in default browser                                                 ok  //
//  - mathematic constants list                                                         ok  //
//  - precise error messages                                                            ok  //
//  - RPN                                                                                   //
//  - Port to QT 4                                                                      ok  //
//                use QMainWindow as main widget                                        ok  //
//                replace Q3PopupMenu                                                       //
//                replace Q3ToolBar                                                         //
//  - use QTranslator for internationalization                                          ok  //
//  - symbolic calculation for systems of linear equations                                  //
//  - logic operations for graph drawing                                                ok  //
//  - graph analysis for functions with logic operations                                ok  //
//  - multi-line edit for functions in graphics window                                      //
//  - usage of multithreading for graph calculation                                     ok  //
//  - import/export function for graphs                                                 ok  //
//  - organize graphs in graph sets with equal settings                                 ok  //
//  - return error message in calculator mode                                               //
//  - scripting language compatbile with octave                                             //
//  - change structure of user interface to more flexible model                             //
//  - switch to doxygen code documentation                                                  //
//  - provide script commands for efficient 2D-graphics                                     //
//                                                                                          //
////////////////////////////////////////beta releases/////////////////////////////////////////


/////////////////////////////////////////////bugs/////////////////////////////////////////////
//                                                                                          //
//	- Menu for number of output-Digits doesn't work                                     ok  //
//	- Colors in gaphic analysation window are not resetted                              ok  //
//	- some buttons of calculator don't move if window switches to fullscreen mode       ok  //
//	- buffer overflow at some functions													                        ok	//
//	- wrong text at some graph analysation options                                      ok	//
//	- calculation of roots doesn't work                                                 ok	//
//	- Newton's method doesn't work                                                      ok	//
//	- function box in graph solve window is sometimes empty                             ok	//
//	- script editor saves unicode wrong                                                 ok	//
//	- calculaton repeating doesn't work with second line                                ok	//
//	- integral calculation doesn't work on periodic functions                           ok	//
//	- graph analyse window doesn't view result of integral correctly                    ok	//
//	- graph analyse window does not allways process mouse events                        ok	//
//	- preferences dialogs can't process mathematical expressions                        ok  //
//	- Script editor has no Menu bar                                                     ok	//
//	- converting floating point values does not work for all locale settings            ok	//
//	- asymptotes are not alsways shown correctly                                        ok	//
//	- calculator keys must be sorted                                                    ok	//
//	- Size of output-table in GraphSolveWidget is not resized                           ok	//
//	- text copying does not work in script console                                      ok	//
//	- changing angle type does not work                                                 ok	//
//	- changing analyse precision does not work                                          ok	//
//	- some script commands may cause problems in calculator mode                        ok	//
//	- recalculaton of 3d-graphs and parameter graphs is not needed                      ok	//
//	- automatic ans inserting does not work corectly                                    ok	//
//	- dynamic graphs are not shown correctly when coordinate system is moved            ok	//
//	- debug messages in graph calculation                                               ok	//
//	- CPU-load is 100% when waiting for keyboart input                                  ok	//
//	- 3rd, 5th ... root of  N returns only complex results                              ok	//
//	- result lines in polar cs were drawn wrong when angle type isn't rad               ok	//
//	- array memory can't be deleted                                                     ok	//
//	- script load balancing doesn't work on fast (dual-core) CPUs                       ok	//
//	- inserting text into a running script doesn't work                                 ok	//
//	- gl script programming does not work on every system	                              ok	//
//	- import script dialog path check is wrong                                          ok	//
//	- bug in script console at selection                                                ok	//
//	- file dialog in script preferences window is always in background                  ok	//
//	- view error when maximizing statistics tab                                         ok	//
//	- directory creation at first start does not work                                   ok	//
//	- command priority in script interpreter wrong                                      ok	//
//	- autosize setting leads to wrong screenshot size                                   ok	//
//	- abs does not exist in standard calculator class                                   ok	//
//	- timer for animated graphs does not work                                           ok	//
//	- automatic insertion of * operator is not always correct                           ok	//
//	- different fonts in different windows                                              ok	//
//	- segfault when drawing animated graphs                                             ok	//
//	- screenshot export does not work                                                   ok	//
//	- complex operator cant't be used as prefix                                         ok	//
//	- faculty of 1 and negative values is wrong                                         ok	//
//	- communication between script and console does not work                            ok	//
//	- automatic switching to script console window does not work                        ok	//
//  - context menu in script editor disabled                                                //
//  - 3D-graphics in scripting is disabled                                                  //
//  - matrix and vector calculation features are invisible                                  //
//  - graph analysis functions were disabled                                                //
//  - segfault at x%2                                                                   ok  //
//  - segfault at x**2                                                                  ok  //
//  - conversation kmmmile and goz have no value                                        ok  //
//  - calculator button shows Lokigmodus instaed of Logikmodus                          ok  //



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
//process multiplications:  /  \         |  \                     //
//                         5    6        |   \                    //
//process sums:           OK    OK       |    \                   //
//                                      6*4    3                  //
//                                     MULT    OK                 //
//process multiplications:             /  \                       //
//                                    6   4                       //
//                                   OK   OK                      //
//                                                                //
////////////////////////////////////////////////////////////////////

class ImportDialog;
class HelpBrowser;
class InfoDialog;

class MainObject :public QMainWindow
{
	QMenuBar*mainMenu;
	Q3PopupMenu *calcMenu,*helpMenu,*prefMenu,*graphMenu;
	Q3PopupMenu *coordinateMenu,*tableMenu;
	Q3PopupMenu *viewMenu,*fileMenu,*scriptMenu,*statisticsMenu;
	QMenu *editMenu,*angleMenu,*floatPointMenu,*outputMenu;
	QSignalMapper *editMapper,*angleMapper,*floatPointMapper,*outputMapper;
	QActionGroup*floatPointActions,*angleActions,*outputActions;
	//new
	QActionGroup *calcModeActions,*languageActions,*baseActions,*graphTypeActions,*graphSetActions,*tableTypeActions;
	QSignalMapper *calcModeMapper,*languageMapper,*baseMapper,*graphTypeMapper,*graphSetMapper,*tableTypeMapper;
	QMenu *calcModeMenu,*languageMenu,*baseMenu,*graphTypeMenu,*graphSetMenu,*tableTypeMenu;
	QAction *complexAction;

  ScreenshotDialog *screenshotDialog;

	QTabBar*tabBar;
	CalcWidget *calculator,*calculator2;
	GraphWidget * graph;
	GraphPreferences*grPref;
	CalcPreferences*calcPref;
	TablePreferences*tablePref;
	ScriptPreferences*scriptPref;
	ImportDialog*importDialog;
	ImportDialog*exportDialog;
	ImportDialog*functionDialog;
	GraphSetDialog*graphSetDialog;
	TableWidget*table;
	ScriptWidget*scripting;
	ScriptIOWidget*scriptIO;
	MatrixWidget*matrix;
	StatisticsWidget*statistics;
	Preferences pref;
	Q3Process*helpProcess;
	InfoDialog*infoDialog;
	Q3TextEdit*licenseWidget;
	QLabel*authorInfo;
	QLabel*versionInfo;
	QPixmap*appIcon;
	QDir*graphsDir;
	HelpBrowser *helpBrowser;
	Variable *vars;
	Vector *vecs;
	bool calcFocus;
	bool calcModeChanged;
	ThreadSync*threadData;
    QTabWidget *clientArea;
	QToolBar *toolBar;


Q_OBJECT
public:
MainObject();

~MainObject()
{
	delete[]vars;
}
int readConfigFile();
void readVarFile();
void writeConfigFile();
void writeVarFile();
void initConstants();
void writeConstants();
void writeUIState();
void readUIState();
void readGraphsDir();
void readFunctionFile(QString);
void writeFunctionFile(QString);


protected:

virtual void closeEvent(QCloseEvent*);
virtual void customEvent(QCustomEvent*);

public slots:
void fileMenuSlot(int item);
  //void quitSlot()
void editMenuSlot(int item);
  //void undoSlot()
  //void redoSlot()
  //void cutSlot()
  //void copySlot()
  //void pasteSlot()
void viewMenuSlot(int item);
  //void viewCalc1Slot()
  //void viewCalc2Slot()
  //void viewGraphSlot()
  //void viewTableSlot()
  //void viewMatrixSlot()
  //void viewStatisticsSlot()
  //void viewScriptingSlot()
  //void viewScriptIOSlot()
void angleMenuSlot(int type);
  //void degSlot()
  //void radSlot()
  //void graSlot()
void outputMenuSlot(int item);
  //void fixedNumSlot()
  //void variableNumSlot()
  //void expSymSlot()
void coordinateMenuSlot(int item);
  //void standardCoordinateSlot()
  //void trigonimectricCoordinateSlot()
  //void showAxesSlot()
  //void showLabelsSlot()
  //void showRasterSlot()
  //void constRationSlot()
void graphTypeMenuSlot(int item);
  //void graphStdSlot()
  //void graphPolarSlot()
  //void graph3DSlot();
void graphMenuSlot(int item);
  //void graphsetManageSlot()
  //void graphsetSaveSlot()
  //void graphsetCreateSlot()
  //void graphsetImportSlot()
  //void graphsetExportSlot()
void calcModeMenuSlot(int item);
void calcComplexSlot();
  //void calcScientificSlot()
  //void calcBaseSlot()
  //void calcComplexSlot()
void baseMenuSlot(int item);
  //void baseBinSlot()
  //void baseOctSlot()
  //void baseDecSlot()
  //void baseHexSlot()
void helpMenuSlot(int item);
  //void helpSlot()
  //void infoSlot()
void prefMenuSlot(int item);
  //void prefCalculatorSlot()
  //void prefGraphicsSlot()
  //void prefTableSlot()
  //void prefScriptSlot()  
void languageMenuSlot(int item);
  //void langEnSlot()
  //void langFrSlot()
  //void langDeSlot()
void tableMenuSlot(int item);
  //void tableStandardSlot()
  //void tableResetSlot()
void scriptMenuSlot(int item);
  //void scriptExportSlot()
  //void scriptImportSlot()
  //void scriptMemAutoSlot()
  //void scripMemClearSlot()
void statisticsMenuSlot(int item);
  //void statClearSlot()
  //void statAutoclearSlot()
  //void statPointsSlot()
  //void statLinesSlot()
void tableTypeMenuSlot(int item);
  //void tableNormalSlot()
  //void tablePolarSlot()
  //void tableParameterSlot()
  //void tableInequalitySlot()
  //void table3dSlot()
  //void tableComplexSlot()

void graphSetMenuSlot(int item);
void floatPointMenuSlot(int item);
void updateGraphSetMenuSlot();

void runScriptSlot(QString*);
void changeTabSlot(int);
void tabChangeSlot(int index);


void getPref(Preferences newPref);

signals:
	void editSignal(int);
	void runScript(QString*);
	void matrixEnterSignal();
	void removeGraphicsLinesSignal();

};




class HelpBrowser :public QWidget
{
	Q3ToolBar*toolBar;
	Q3DockArea*dockArea;
	QPixmap *forwardIcon,*backIcon,*zoominIcon,*zoomoutIcon;
	QToolButton *forwardButton,*backButton,*zoominButton,*zoomoutButton;
	Q3TextBrowser *browser;
	QString currentSource;
	Q_OBJECT
	
	public:
	HelpBrowser(QWidget*parent);
	void setContent(QString);
	
	public slots:
	void zoominSlot();
	void zoomoutSlot();
	void sourceSlot(const QString&);
	
	protected:
	void resizeEvent(QResizeEvent*);
};


class InfoDialog :public QDialog
{
	Q_OBJECT
	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;
	QTextEdit *licenseWidget;
	QLabel *authorInfo,*versionInfo;
	QGridLayout*layout;

	public:
		InfoDialog(QWidget*parent);
};





#endif
