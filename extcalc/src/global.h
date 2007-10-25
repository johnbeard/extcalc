/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         global.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This file contains the two classes needed to process calculations.
The Calculate class for function graphs and the Script class for the normal calculator
and the script interpreter.
The help functions for string processing and mathematic help functions are also defined in this
file.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef GLOBALH
#define GLOBALH

#include <qstring.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qmutex.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <complex>
#include <errno.h>
#include "list.h"
#include "calclocale.h"

using namespace std;


#define CONFIGFILE ".extcalc/extcalc.conf"
#define VARSFILE ".extcalc/vars.conf"
#define LISTSFILE ".extcalc/lists.conf"
#ifdef LANGUAGE_EN
#define VERSIONSTRING "Version: 0.9.1\n2007-10-25\n\n"+QString(DEVVERSION)
#endif
#ifdef LANGUAGE_FR
#define VERSIONSTRING "Version: 0.9.1\n2007-10-25\n\n"+QString(DEVVERSION)
#endif
#ifdef LANGUAGE_DE
#define VERSIONSTRING "Version: 0.9.1\n25.10.2007\n\n"+QString(DEVVERSION)
#endif

#define AUTHORSTRING "Homepage:\nhttp://extcalc-linux.sourceforge.net\n\n"+QString(GLOBALH_STR1)


#define FILEM				1
#define PREFERENCES			2
#define CALCULATOR			3
#define GRAPH				4
#define HELP				5
#define EXTHELP				10
#define INFO				11
#define CPREF				17
#define GPREF				18
#define TPREF				55
#define TABLE				58
#define EDITUNDO			59
#define EDITREDO			60
#define EDITCUT				61
#define EDITCOPY			62
#define EDITPASTE			63
#define VIEWCALC1			64
#define VIEWCALC2			65
#define VIEWGRAPH			66
#define VIEWTABLE			67
#define VIEWSCRIPTING		68
#define VIEW				69
#define EDIT				70
#define QUIT				71
#define SPREF				72
#define VIEWSCRIPTIO		83
#define EDITSELECTALL		175
#define EDITORRUN			176
#define EDITORMINIMIZE		177
#define EDITORIMPORT		178
#define EDITOREXPORT		179
#define VIEWMATRIX			180
#define VIEWSTATISTICS		181

#define FILENEWSCRIPT		73
#define FILENEWDIR			74
#define FILEDELETE			75
#define FILERENAME			76
#define FILECUT				77
#define FILECOPY			78
#define FILEUPDATE			79
#define FILESAVE			80
#define FILESAVEALL			81
#define FILEPASTE			82


#define ANGLE				9
#define OUTPUT				12

#define RAD					6
#define DEG					7
#define GRA					8

#define FIXEDNUM			13
#define VARIABLENUM			14
#define EXPSYM				15
#define FLOATPOINT			16

#define STANDARDCOORDS 		24
#define TRIGONOMETRICCOORDS	25
#define COORDINATE			26
#define SHOWAXES			27
#define SHOWLABELS			28
#define SHOWRASTER			29
#define CONSTRATIO			30
#define GRAPHTYPE			31
#define TABLETYPE			56
#define STANDARDTABLE		57
#define RESETTABLE			184

#define EXPORTSCRIPT		171
#define IMPORTSCRIPT		172
#define CLEARMEMALWAYS		173
#define CLEARMEMNOW			174
#define SCRIPTM				175
#define STATISTICSM			207

#define MODE				39
#define SCIENTIFIC			32
#define BASE				33
#define COMPLEXMENU			165

#define BASEMENU			40
#define BIN					34
#define HEX					35
#define OCT					36
#define DEC					38

#define NONE				 1
#define PLUS				 2
#define MINUS				 3
#define MULT				 4
#define DIVIDE				 5
#define POW					 6
#define ROOT				 7
#define SIN					 8
#define COS					 9
#define TAN					10
#define ASIN				11
#define ACOS				12
#define ATAN				13
#define ASINH				14
#define ACOSH				15
#define ATANH				16
#define SINH				17
#define COSH				18
#define TANH				19
#define LG					20
#define LN					21
#define DIFF				22
#define INTEGRAL			23
#define MODULO				116
#define ARRAY				129
#define RSHIFT				139
#define LSHIFT				140
#define XOR					141
#define CPOW				153
#define CROOT				154
#define CSIN				155
#define CCOS				156
#define CTAN				157
#define CSINH				158
#define CCOSH				159
#define CTANH				160
#define CLN					161
#define CLG					162
#define CABS				163
#define CDIVIDE				164
#define SQRT				166
#define CSQRT				167
#define CURT				168
#define SCALARPROD			170
#define DETERMINANT			182
#define INVERT				183

#define SSEMICOLON			83
#define SCOMPARE			84
#define SIF					85
#define SFOR				86
#define SWHILE				87
#define SPRINT				88
#define SSET				89
#define SBRACKET			99
#define SFAIL				100
#define SIFELSE				101
#define SSPLIT				102
#define SGREATHER			103
#define SLESS				104
#define SGREQ				105
#define SLESSEQ				106
#define SUNEQUAL			107
#define SVALUE				108
#define SINIT				109
#define SSETCURSOR			110
#define SCLEARTEXT			111
#define SSLEEP				112
#define SGETLINE			113
#define SGETKEY				114
#define SVAR				115
#define SAND				117
#define SOR					118
#define SNOT				119
#define SCAST				120
#define SKEYSTATE			121
#define SARRAY				122
#define SRAND				123
#define SMATRIX				124
#define SBREAK				125
#define SCONTINUE			126
#define SSTOP				127
#define SRUN				128
#define SBAND				142
#define SBOR				143
#define SFAK				144
#define SBNOT				145
#define SABS				148
#define SCONJ				149
#define SREAL				150
#define SIMAG				151
#define SARG				152
#define SVECTOR				169
#define SFREAD				186
#define SFWRITE				187
#define SFAPPEND			188
#define SFREMOVE			189
#define SGRAPHLIST			190
#define SGRAPHCONTROL		191
#define SGRAPHPAINT			192
#define SGRAPHVERTEX		193
#define SGRAPHTEXT			194
#define SGRAPHCOLOR			195
#define SGRAPHTRANSFORM		196
#define SGRAPHIDENTITY		197
#define SDRAW				211

#define CALCYVAL			0
#define CALCZEROS			1
#define CALCNEWTON			2
#define CALCXVAL			3
#define CALCCROSSP			4
#define CALCEXTRVAL			5
#define CALCINTEGRAL		6
#define CALCDIFF			7
#define CALCZVAL			8
#define GETSCREENSHOT		9

#define MATCALC				0
#define MATLSE				1
#define MATGENERATE			2
#define MATANALYSE			3
#define MATINV				4

#define GRAPHSTD			41
#define GRAPHPOLAR			42
#define GRAPHPARAMETER		43
#define GRAPHDYNAMIC		44
#define GRAPHIEL			45
#define GRAPHIELE			46
#define GRAPHIEG			47
#define GRAPHIEGE			48
#define GRAPH3D				49
#define GRAPHCOMPLEX		146
#define GRAPHCOMP3D			147

#define TABLENORMAL			50
#define TABLEPOLAR			51
#define TABLEPARAMETER		52
#define TABLEINEQUAITY		53
#define TABLE3D				54
#define TABLECOMPLEX		185

#define STATCLEAR			203
#define STATAUTOCLEAR		204
#define STATPOINTS			205
#define STATLINES			206

#define STATAPPROX			198
#define STATINTERPOL		199
#define STATNORMAL			200
#define STATBARGRAPH		201
#define STATLINEGRAPH		202

#define SCRIPTTEXT			208
#define SCRIPT2D			209
#define SCRIPT3D			210

#define DRAWNONE			130
#define DRAWFREE			131
#define DRAWLINE			132
#define DRAWRECT			133
#define DRAWCIRCLE			134
#define DRAWFORWARD			135
#define DRAWBACK			136
#define DRAWCLEAR			137
#define DRAWTEXT			138

#define PINVALIDCOMMAND		176
#define PPINVALIDARGUMENT	177
#define PPINVALIDPREF		178
#define PPEMPTY				179
#define MPEMPTY				212
#define MPINVALIDMACRO		213

#define CATMATHSTD			0x1
#define CATMATHCOMPLEX		0x2
#define CATMATRIX			0x4
#define CATSCRIPT			0x8
#define CATMATHLOGIC		0x10


#define NNONE				0x1
#define NFLOAT				0x2
#define NINT				0x4
#define NBOOL				0x8
#define NCHAR				0x10
#define NVECTOR				0x20
#define NMATRIX				0x40
#define NCOMPLEX			0x80

#define SIGPRINT			50000
#define SIGSETTEXTPOS		50001
#define SIGCLEARTEXT		50002
#define SIGGETLINE			50003
#define SIGGETKEY			50004
#define SIGKEYSTATE			50005
#define SIGDEBUG			50006
#define SIGFILEREAD			50007
#define SIGFILEWRITE		50008
#define SIGFILEAPPEND		50009
#define SIGFILEREMOVE		50010
#define SIGCALLLIST			50011
#define SIGSTARTLIST		50012
#define SIGENDLIST			50013
#define SIGGRAPHSHOW		50014
#define SIGGRAPHCLEAR		50015
#define SIGGRAPHEND			50016
#define SIGGRAPHBEGIN		50017
#define SIGGRAPHVERTEX		50018
#define SIGGRAPHTEXT		50019
#define SIGGRAPHCOLOR		50020
#define SIGGRAPHROTATE		50021
#define SIGGRAPHSCALE		50022
#define SIGGRAPHTRANSLATE	50023
#define SIGIDENTITY			50024
#define SIGDRAW				50025
#define SIGFINISHED			50030

#define ROOTSTRING			8730
#define PISTRING			960
#define EULERSTRING			65349
#define INTEGRALSTRING		8747
#define DELTASTRING			916
#define MEGASTRING			65325
#define GIGASTRING			65319
#define TERASTRING			65332
#define DIFFSTRING			8706
#define DEGREESTRING		176

#define VARNUM				29
#define VARDIMENSIONS		2



//String constants (with 40 digits precisision) and system constants (128-bit) for Pi and e
#ifdef M_PIl
#define PI					M_PIl
#else
#define PI					3.141592653589793238462643383279502884197
#endif

#ifdef M_El
#define EULER				M_El
#else 
#define EULER				2.718281828459045235360287471352662497757
#endif

#define SPI					"3.141592653589793238462643383279502884197"
#define SEULER				"2.718281828459045235360287471352662497757"

#ifndef NAN
#define NAN (HUGE_VAL/HUGE_VAL)
#endif

class Math;

typedef long double Variable;


struct Preferences
{
	int angle;
	int outputType;
	int outputLength;
	int precision;
	bool shift;
	bool alpha;
	bool hyp;
	bool showWindows[8];
	double xmin,xmax,ymin,ymax,zmin,zmax;
	double rasterSizeX,rasterSizeY,rasterSizeZ;
	double radiusMax,angleMax;
	double rasterSizeRadius,rasterSizeAngle;
	double parameterStart,parameterEnd;
	double dynamicStart,dynamicEnd;
	double nyquistStart,nyquistEnd;
	double tableXStart,tableXEnd,tableZStart,tableZEnd;
	double tableAValue;
	int parameterSteps;
	int dynamicSteps;
	int dynamicDelay;
	int nyquistSteps;
	int prec2dSteps;
	int prec3dSteps;
	int solvePrec;
	int tableXSteps,tableZSteps;
	bool raster;
	bool axis;
	bool label;
	bool autosize;
	bool moveUpDown;
	bool show3dGrid;
	bool logNyquistSteps;
	bool complex;
	bool clearScriptMemory;
	bool showStatLines;
	bool showStatPoints;
	bool statAutoClear;
	int graphType;
	int calcType;
	int tableType;
	int base;
	int scriptGraphicsMode;
	QString scriptPath;
	QString scriptDirName;
	QString dataDirName;
	QString*functions;
	bool*activeFunctions;
	int*functionTypes;
	bool*dynamicFunctions;
	QColor*functionColors;
	QString drawText;
};

struct Number
{

	complex <long double> fval;
	long long ival;
	bool bval;
	char*cval;
	int type;
};

typedef List<Number> Vector;
typedef complex <long double> Complex;

struct ThreadSync
{
	QMutex*mutex;
	QObject*eventReciver;
	void*data;
	int type;
	int sleepTime;
	int status;
	int eventCount;
	bool usleep;
	bool exit;
	bool bbreak;
	bool bcontinue;
	bool calcMode;
	int numlen[VARNUM];	
	int dimension[VARNUM][VARDIMENSIONS];					//vector, matrix size
	Number**vars;
	List <Math*>subprograms;
	List <char*>subprogramPath;
};




//Standard Calculator functions
int bracketFind(char* string,char* searchString, int start=0);
int bracketFindRev(char* string,char* searchString, int start=-1);
char*strcut(char*src,int index,int len=1);
char*strins(char*dest,const char*src,int index);
int strcopy(char*dest,char*src,int len);
char* strreplace(char*st,int index,int len,char*rep);
char* strinsert(char*st,int index,char*ins);
char* checkStringAnsi(char*calcString,Preferences*pref);		//same as checkString in Calc
void MessageBox(QString text);
int YesNoBox(QString text);
 int YesNoCancelBox(QString text);
 void WarningBox(QString text);
 void ErrorBox(QString text);
//char* checkString(QString calcString,Preferences*pref);		//Removes Unicode and runs checkStringAnsi
char* preprocessor(char*,Preferences*,bool);
char* preprocessor(QString*,Preferences*,bool);
char* preferencesPreprocessor(char*,Preferences*);
char* macroPreprocessor(char*);
char* cleanString(char*,Preferences*);
char* removeUnicode(QString*);
char* removeComments(char*);
QString getConfigString(QString*,QString);
QString cleanConfigString(QString,QString);
QString getUnicode(int code);
QString formatOutput(long double num,Preferences*pref);
QString formatOutput(Number num,Preferences*pref,ThreadSync*varData=NULL);
QColor getColor(QString colorName);
QString getColorName(QColor col);
QString getErrorMessage();
long double runCalc(QString,Preferences*,Variable*);
long double determinant(int,long double*);
long double gauss(int sizex,int sizey,long double*matrix);
bool invertMatrix(int size,long double*matrix);
void printError(const char*,int,QObject*);
void convertToFloat(Number*num);
inline void convertToInt(Number*num);
inline void convertToBool(Number*num);


// for compatibility with systems without math functions for long double
#ifdef NO_LONG_DOUBLE

#define sinl(var) sin(var)
#define cosl(var) cos(var)
#define tanl(var) tan(var)

#define asinl(var) asin(var)
#define acosl(var) acos(var)
#define atanl(var) atan(var)

#define sinhl(var) sinh(var)
#define coshl(var) cosh(var)
#define tanhl(var) tanh(var)

#define asinhl(var) asinh(var)
#define acoshl(var) acosh(var)
#define atanhl(var) atanh(var)

#define logl(var) log(var)
#define sqrtl(var) sqrt(var)
#define powl(va,vb) pow(va,vb)
#define fmodl(va,vb) fmod(va,vb)
#define strtold(va,vb) strtod(va,vb)
#define cbrtl(var) cbrt(var)
#define fabsl(var) fabs(var)
#define expl(var) exp(var)

#endif

class Math
{
	protected:
	Variable*vars;
	Preferences*pref;
	Math*parent;
	Math *vertObj,*horzObj;
	double number;
	int var;
	int operation;
	
	
public:
		
	Math(Math*par,Preferences*pr,Variable*va)
	{
		parent=par;
		pref=pr;
		vars=va;
	}
	virtual ~Math()
	{
		if(vertObj!=NULL)
		{
			delete vertObj;
			vertObj=NULL;
		}
		if(horzObj!=NULL)
		{
			delete horzObj;
			horzObj=NULL;
		}
	}
	
	int getOperation()
	{
		return operation;
	}
	
	virtual double calc() {return 0.0;}
	virtual double calcVertObj() {return 0.0;}
	virtual double calcHorzObj() {return 0.0;}
	
	virtual Number exec() {Number r;r.type=NNONE;return r;}
	virtual Number execVertObj() {Number r;r.type=NNONE;return r;}
	virtual Number execHorzObj() {Number r;r.type=NNONE;return r;}

	virtual int split(char*){return 0;}
	virtual char* parse(char*){return 0;}
	
};


class Calculate :public Math
{
	
	virtual int split(char* line);

public:
	
	Calculate(Math *par,char* line,Preferences*pr,Variable*va) :Math((Math*)par,pr,va)
	{
		horzObj=vertObj=NULL;
		split(line);
	}
	~Calculate()
	{
		if(horzObj!=NULL)
		{
			delete horzObj;
			horzObj=NULL;
		}
		if(vertObj!=NULL)
		{
			delete vertObj;
			vertObj=NULL;
		}
	}


	virtual double calc();
	virtual double calcVertObj();
	virtual double calcHorzObj();
};

class Script :public Math
{
	Number value;
	Math*nextObj,*vertObj2,*vertObj3;
	ThreadSync*eventReciver;
		
private:
	
	inline bool resizeVar(int var,int newlen);

public:

	Script(Script*par,char*line,Preferences*pr,Variable*va,ThreadSync*evrec) :Math((Math*)par,pr,va)
	{
		horzObj=vertObj=vertObj2=vertObj3=nextObj=NULL;
		value.type=NNONE;
		eventReciver=evrec;
		value.cval=NULL;
		if(par==NULL)
			split(line);
		else if(line!=NULL)
		{
			char*rest=parse(line);
			if(rest!=NULL)
			{
				operation=SFAIL;
				delete[]rest;
			}
		}
	}
	~Script()
	{
		if(value.type==SVALUE && value.type==NCHAR && value.cval!=NULL)
		{
			free(value.cval);
			value.cval=NULL;
		}
		if(horzObj!=NULL)
		{
			delete horzObj;
			horzObj=NULL;
		}
		if(vertObj!=NULL)
		{
			delete vertObj;
			vertObj=NULL;
		}
		if(vertObj2!=NULL)
		{
			delete vertObj2;
			vertObj2=NULL;
		}
		if(vertObj3!=NULL)
		{
			delete vertObj3;
			vertObj3=NULL;
		}
		if(nextObj!=NULL)
		{
			delete nextObj;
			nextObj=NULL;
		}
	}
	char*parse(char*line);
	virtual int split(char* line);


	virtual double calc();
	virtual double calcVertObj();
	virtual double calcHorzObj();

	virtual Number exec();
	virtual Number execVertObj();
	virtual Number execHorzObj();

};

#endif





