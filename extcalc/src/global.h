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
#include "list.h"
#include "calclocale.h"

using namespace std;


#define CONFIGFILE ".extcalc/extcalc.conf"
#ifdef LANGUAGE_EN
#define VERSIONSTRING "Version: 0.6.6\n2006-01-20\n\n"+QString(DEVVERSION)
#endif
#ifdef LANGUAGE_DE
#define VERSIONSTRING "Version: 0.6.6\n20.1.2006\n\n"+QString(DEVVERSION)
#endif
#define AUTHORSTRING "Autor:\nRainer Strobel  2006\n\nHomepage:\nhttp://extcalc-linux.sourceforge.net"


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

#define MODE				39
#define SCIENTIFIC			32
#define BASE				33

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

#define DRAWNONE			130
#define DRAWFREE			131
#define DRAWLINE			132
#define DRAWRECT			133
#define DRAWCIRCLE			134
#define DRAWFORWARD			135
#define DRAWBACK			136
#define DRAWCLEAR			137
#define DRAWTEXT			138

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
#define SIGFINISHED			50010

#define ROOTSTRING			8730
#define PISTRING			960
#define EULERSTRING			65349
#define INTEGRALSTRING		8747
#define DELTASTRING			916
#define MEGASTRING			65325
#define GIGASTRING			65319
#define TERASTRING			65332
#define DIFFSTRING			8706



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

typedef List<long double> Variable;


struct Preferences
{
	int angle;
	int outputType;
	int outputLength;
	int precision;
	bool shift;
	bool alpha;
	bool hyp;
	bool showWindows[6];
	double xmin,xmax,ymin,ymax,zmin,zmax;
	double rasterSizeX,rasterSizeY,rasterSizeZ;
	double radiusMax,angleMax;
	double rasterSizeRadius,rasterSizeAngle;
	double parameterStart,parameterEnd;
	double dynamicStart,dynamicEnd;
	double nyquistStart,nyquistEnd;
	double tableXStart,tableXEnd,tableZStart,tableZEnd;
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
	int graphType;
	int calcType;
	int tableType;
	int base;
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
	long double fval;
	long double *fvector;		//complex, vector
	int dimension;				//vector size
	complex <long double> cfval;
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
	bool usleep;
	bool exit;
	bool bbreak;
	bool bcontinue;
	bool calcMode;
	int numlen[27];
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
char* checkStringAnsi(char*calcString,Preferences*pref);		//same as checkString in Calc
void MessageBox(QString text);
int YesNoBox(QString text);
 int YesNoCancelBox(QString text);
 void WarningBox(QString text);
 void ErrorBox(QString text);
char* checkString(QString calcString,Preferences*pref);		//Removes Unicode and runs checkStringAnsi
QString getConfigString(QString*,QString);
QString cleanConfigString(QString,QString);
QString getUnicode(int code);
QString formatOutput(long double num,Preferences*pref);
QString formatOutput(Number num,Preferences*pref);
QColor getColor(QString colorName);
QString getColorName(QColor col);
long double runCalc(QString,Preferences*,Variable*);
void printError(const char*,int,QObject*);



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
			delete[]value.cval;
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





