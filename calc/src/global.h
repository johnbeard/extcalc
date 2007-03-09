#ifndef GLOBALH
#define GLOBALH

#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <complex>
#include "list.h"

using namespace std;


#define VERSIONSTRING "Version: 0.7.0 2007-03-09\nCalculator algorithm: extcalc v0.7.0 2007-03-09"
#define AUTHORSTRING "Author:\nRainer Strobel\nhttp://extcalc-linux.sourceforge.net\n2007\n"


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


#define NNONE				0x1
#define NFLOAT				0x2
#define NINT				0x4
#define NBOOL				0x8
#define NCHAR				0x10
#define NVECTOR				0x20
#define NMATRIX				0x40
#define NCOMPLEX			0x80

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

#define PPINVALIDCOMMAND	176
#define PPINVALIDARGUMENT	177
#define PPINVALIDPREF		178
#define PPEMPTY				179

#define RAD					6
#define DEG					7
#define GRA					8

#define SCIENTIFIC			32
#define BASE				33

#define BIN					34
#define HEX					35
#define OCT					36
#define DEC					38

#define VARNUM				29
#define VARDIMENSIONS		2

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

#define CONSOLE

typedef List<long double> Variable;
typedef complex <long double> Complex;


class Math;

struct Preferences
{
	int angle;
	int outputType;
	int outputLength;
	int calcType;
	int base;
	int precision;
	bool complex;
};



struct Number
{

	complex <long double> fval;
	long long ival;
	bool bval;
	char*cval;
	int type;
};


struct ThreadSync
{

	int status;
	int sleepTime;
	bool usleep;
	bool exit;
	bool bbreak;
	bool bcontinue;
	bool error;
	bool calcMode;
	int numlen[VARNUM];
	int dimension[VARNUM][VARDIMENSIONS];					//vector, matrix size

	Number**vars;
	List <Math*>subprograms;
	List <char*>subprogramPath;
	List <int>semicolonLines;
	int countDifference;
};



//Standard Calculator functions
long double calculate(char*,Preferences*pref,Variable*vars);
int bracketFind(char* string,char* searchString, int start=0);
int bracketFindRev(char* string,char* searchString, int start=-1);
char*strcut(char*src,int index,int len=1);
char*strins(char*dest,const char*src,int index);
int strcopy(char*dest,char*src,int len);
char* checkString(char*calcString,Preferences*pref);
void printError(const char*,int,ThreadSync*);
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
			delete vertObj;
		if(horzObj!=NULL)
			delete horzObj;
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

	virtual int split(char*line){return 0;}
	virtual char* parse(char*line){return 0;}

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





