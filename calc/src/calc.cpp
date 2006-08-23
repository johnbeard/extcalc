#include <stdio.h>
#include "global.h"
#include <sys/time.h>
#include <float.h>
#include <stdlib.h>

///////////////////////////////////////Calc///////////////////////////////////////
//  Calc is a scientific calculator for the text console.                       //
//  It is a sub-project of Extcalc and it uses the calculaton algorithms of     //
//  Extcalc.                                                                    //
//  Calc is very simple to use. Just start the program with your calculaton     //
//  and it will return the result.                                              //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////TODO///////////////////////////////////////
//                                                                              //
//  - write all needed subroutines for calculator                           ok  //
//  - make all needed changes that the calc algorithms run standalone       ok  //
//  - port accerelated calcualtion algorithm form extcalc to calc           ok  //
//  - make all algorithms compatible with extcalc                           ok  //
//  - enable command line parameters for setting output format              ok  //
//  - enable command line parameters for different angle formats            ok  //
//  - enable base-n calculatons                                             ok  //
//  - enable logic functions                                                ok  //
//  - make usage of variables possible                                      ok  //
//  - write documentation and manpage                                           //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////Bugs///////////////////////////////////////
//
//	- Base mode doesn't work												fixed
//
//
//
//////////////////////////////////////////////////////////////////////////////////




int main(int argc,char**argv)
{
	long double *vars=new long double[27];
	Preferences *pref=new Preferences;
	pref->angle=RAD;
	pref->calcType=SCIENTIFIC;
	pref->base=DEC;
	bool ask=true;
	char*input=NULL;
	bool script=false;
	Script*s;
	ThreadSync scriptData;

#ifdef HAVE_LONG_DOUBLE
	pref->outputLength=pref->precisision=LDBL_DIG;
	int maxLength=LDBL_DIG;
#else 
	pref->outputLength=pref->precisision=DBL_DIG;
	int maxLength=DBL_DIG;
#endif	

	char*homedir=getenv("HOME");
	char*path=new char[strlen(homedir)+16];
	memcpy(path,homedir,strlen(homedir));
	memcpy(&path[strlen(homedir)],"/.calcvariables",16);
	
	int fileLength;
	struct stat fileStat;
	char*variablesString;
	FILE*variablesFile=fopen(path,"r");
	char*var;
	if(lstat(path,&fileStat) == 0 && variablesFile!=NULL)
	{
		fileLength=fileStat.st_size;
		variablesString=new char[fileLength+1];
		fread(variablesString,fileLength,1,variablesFile);
		
		int varStart=0;
		int varEnd=0;
		int varCount=0;
	
	
		for(int c=0; c<fileLength && varCount<27; c++)
		{
			if(variablesString[c]=='\n' || c == fileLength-1)
			{
				varEnd=c;
				var=new char[varEnd-varStart+1];
				memcpy(var,&variablesString[varStart],varEnd-varStart);
				var[varEnd-varStart]=(char)0;
#ifdef HAVE_LONG_DOUBLE
				vars[varCount]=strtold(var,NULL);
#else 
				vars[varCount]=strtod(var,NULL);
#endif
				varStart=varEnd+1;
				varCount++;	
				delete[] var;
			}
		}
		fclose(variablesFile);
	}







	for(int c=1; c<argc; c++)
	{
		if(strcmp(argv[c],"-a")==0 || strcmp(argv[c],"--angle")==0)
		{
			if(argc>c)
			{
				if(strncmp(argv[c+1],"deg",3)==0)
					pref->angle=DEG;
				else if(strncmp(argv[c+1],"rad",3)==0)
					pref->angle=RAD;
				else if(strncmp(argv[c+1],"gra",3)==0)
					pref->angle=GRA;
				else {
					printf("Invalid argument for -a!\n\nPossible Arguments:\n-a deg\n-a rad\n-a gra\n\nPlease use man calc for further information\n");
					delete pref;
					delete[] vars;
					return 0;
				}
				c++;
			}
			else {
				printf("Invalid argument for -a!\n\nPossible Arguments:\n-a deg\n-a rad\n-a gra\n\nPlease use man calc for further information\n");
				delete pref;
				delete[] vars;
				return 0;
			}
		}
		else if(strcmp(argv[c],"-m")==0 || strcmp(argv[c],"--mode")==0)
		{
			if(argc>c)
			{
				if(strncmp(argv[c+1],"base",3)==0)
					pref->calcType=BASE;
				else if(strncmp(argv[c+1],"std",3)==0)
					pref->calcType=SCIENTIFIC;
				else if(strncmp(argv[c+1],"script",3)==0)
				{
					pref->calcType=SCIENTIFIC;
					script=true;
				}
				else {
					printf("Invalid argument for -m!\n\nPossible Arguments:\n-m base\n-m std\n\nPlease use man calc for further information\n");
					delete pref;
					delete[] vars;
					return 0;
				}
				c++;
			}
			else {
				printf("Invalid argument for -m!\n\nPossible Arguments:\n-m base\n-m std\n\nPlease use man calc for further information\n");
				delete pref;
				delete[] vars;
				return 0;
			}
		}
		else if(strcmp(argv[c],"-b")==0 || strcmp(argv[c],"--base")==0)
		{
			if(argc>c)
			{
				if(strncmp(argv[c+1],"bin",3)==0)
					pref->base=BIN;
				else if(strncmp(argv[c+1],"hex",3)==0)
					pref->base=HEX;
				else if(strncmp(argv[c+1],"oct",3)==0)
					pref->base=OCT;
				else if(strncmp(argv[c+1],"dec",3)==0)
					pref->base=DEC;
				else {
					printf("Invalid argument for -m!\n\nPossible Arguments:\n-m base\n-m std\n\nPlease use man calc for further information\n");
					delete pref;
					delete[] vars;
					return 0;
				}
				c++;
			}
			else {
				printf("Invalid argument for -b!\n\nPossible Arguments:\n-b dec\n-b hex\n-b bin\n-b oct\n\nPlease use man calc for further information\n");
				delete pref;
				delete[] vars;
				return 0;
			}
		}
		else if(strcmp(argv[c],"-o")==0 || strcmp(argv[c],"--output")==0)
		{
			if(argc>c)
			{
				int outLen=atoi(argv[c+1]);
				if(outLen<2 || outLen>pref->precisision)
				{
					printf("Invalid argument for -o!\n\nThe argument must be a number between 2 and %i.\nFor example: -o 8\n\nPlease use man calc for further information\n",pref->precisision);
					delete pref;
					delete[] vars;
					return 0;
				}
				pref->outputLength=outLen;
				
				c++;
			}
			else {
				printf("Invalid argument for -o!\n\nThe argument must be a number between 2 and %i.\nFor example: -o 8\n\nPlease use man calc for further information\n",pref->precisision);
				delete pref;
				delete[] vars;
				return 0;
			}
		}
		else if(strcmp(argv[c],"-h")==0 || strcmp(argv[c],"--help")==0)
		{
			printf("Usage:\ncalc \"input\"\nFor example: calc \"2*(3+7/2)\"\n\nOptions:\n-a, --angle (deg, rad, gra)\n-m, --mode (base, std)\n-b, --base (dec, hex, bin, oct) only in base mode\n-o, --output (2-18)\n-h, --help\n-v, --version\n\nPlease use man calc for  further information\n");
			delete pref;
			delete[] vars;
			return 0;		
		}
		else if(strcmp(argv[c],"-v")==0 || strcmp(argv[c],"--version")==0)
		{
			printf("\n%s\n\n%s",VERSIONSTRING,AUTHORSTRING);
			delete pref;
			delete[] vars;
			return 0;		
		}
		else {
			ask=false;
			if(input==NULL)
			{
				input=new char[strlen(argv[c])+1];
				memcpy(input,argv[c],strlen(argv[c])+1);
			}
			else {
				char*temp=input;
				input=new char[strlen(argv[c])+strlen(temp)+1];
				memcpy(input,temp,strlen(temp));
				memcpy(&input[strlen(temp)],argv[c],strlen(argv[c])+1);
			}
		}
	}
	if(pref->calcType == SCIENTIFIC && pref->base!=DEC)
	{
		printf("Invalid option -b!\nOption -b can only be used when -m is set!\n\nPlease use man calc for further information\n");
		delete pref;
		delete[] vars;
		return 0;
	}
	if(ask)
	{
		input=new char[1026];
		scanf("%1024s",input);
	}
	if(script)
	{
		char*path=input;
		struct stat fileinfo;
		FILE*scriptFile;
		if(lstat(path,&fileinfo)!=0)
		{
			printf("Opening script file %s failed!\n",path);
			delete[]path;
			return 0;
		}
		if(fileinfo.st_size<=0)
		{
			printf("Invalid file %s !\n",path);
			delete[]path;
			return 0;
		}
		scriptFile=fopen(path,"r");
		if(scriptFile==NULL)
		{
			printf("Opening script file %s failed!\n",path);
			delete[]path;
			return 0;
		}
		input = new char[fileinfo.st_size+1];
		if(fread(input,fileinfo.st_size,1,scriptFile)<=0)
		{
			printf("Can't read file %s !\n",path);
			delete[]path;
			return 0;
		}		
		input[fileinfo.st_size]=(char)0;
		printf("program: %s\n",input);
	}
	char*res=checkString(input,pref,vars);
	char*printString=new char[50];
	if(script)
	{
		struct termios terminfo,oldTerminfo;
		tcgetattr(fileno(stdout),&terminfo);
		oldTerminfo=terminfo;
		terminfo.c_lflag &=~ECHO;
		terminfo.c_lflag &=~ICANON;
		if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
			perror("tcsetattr fehler");
		
		scriptData.exit=false;
		scriptData.vars=new Number[27];
		s=new Script((Script*)NULL,res,pref,vars,&scriptData);
		s->exec();
		
		if(tcsetattr(fileno(stdout),TCSANOW,&oldTerminfo)!=0)
			perror("tcsetattr fehler");
		
		delete[] scriptData.vars;
	}	
	else if(pref->calcType==SCIENTIFIC)
	{
		sprintf(printString,"%%.%iLg\n",pref->outputLength);
		printf(printString,vars[26]=calculate(res,pref,vars));
	}
	else {
		
		switch(pref->base)
		{
			case DEC:
				printf("%lli\n",(long long)(vars[26]=calculate(res,pref,vars)));
				break;
			case BIN:
			{
				long long result=(long long)(vars[26]=calculate(res,pref,vars));
				char*cRes=new char[65];
				cRes[64]=(char)0;
				for(long long c=0; c<64;c++)
				{
					unsigned long long match=1;
					match=match<<c;
					unsigned long long bin=match&result;
					if(bin==0)
						cRes[63-c]='0';
					else cRes[63-c]='1';
				}
				int c=0;
				while(cRes[c]=='0' && c<63)
					c++;
				printf("%s\n",&cRes[c]);
				break;
				}
			case HEX:
				printf("%LX\n",(long long)(vars[26]=calculate(res,pref,vars)));
				break;
			case OCT:
				printf("%llo\n",(long long)(vars[26]=calculate(res,pref,vars)));
				break;
		}	

	}

	char*newVarString="";
	sprintf(printString,"%%.%iLg",maxLength);
	char*varString=new char[maxLength+20];


	for(int c=0; c<27; c++)
	{
		sprintf(varString,printString,vars[c]);
		newVarString=strins(newVarString,varString,strlen(newVarString));
		newVarString=strins(newVarString,"\n",strlen(newVarString));
	}
	variablesFile=fopen(".calcvariables","w");
	if(variablesFile!=NULL)
	{
		fwrite(newVarString,strlen(newVarString),1,variablesFile);
		fclose(variablesFile);
	}


	delete[]input;
	delete[]res;
		
	//printf("Usage:\ncalc \"input\"\nFor example: calc \"2*(3+7/2)\"\nPlease use man calc for  further information\n");
	delete pref;
	delete[] vars;
	return 0;
}
