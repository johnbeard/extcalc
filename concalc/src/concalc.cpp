/*/////////////////////////////////////////Concalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         concalc.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include <stdio.h>
#include "global.h"
#include <sys/time.h>
#include <float.h>
#include <stdlib.h>
#include "concalc.h"

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
//  - write documentation and manpage                                       ok  //
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
	Variable *vars=new Variable[VARNUM];
	Number value;

	for(int c=0; c<VARNUM;c++)
		vars[c]=0.0;
	Preferences *pref=new Preferences;
	pref->angle=RAD;
	pref->calcType=SCIENTIFIC;
	pref->base=DEC;
	pref->complex=false;
	bool ask=true;
	char*input=NULL;
	bool script=false;
	Script*s;
	ThreadSync scriptData;
	scriptData.vars=new Number*[VARNUM];
	for(int c=0; c<VARNUM;c++)
	{
		scriptData.vars[c]=(Number*)malloc(sizeof(Number));
		scriptData.numlen[c]=1;
		for(int c1=0; c1<VARDIMENSIONS; c1++)
			scriptData.dimension[c][c1]=1;
		scriptData.vars[c][0].type=NNONE;
		scriptData.vars[c][0].cval=NULL;
	}

	
#ifndef NO_LONG_DOUBLE
	pref->outputLength=pref->precision=LDBL_DIG;
	int maxLength=LDBL_DIG;
#else 
	pref->outputLength=pref->precision=DBL_DIG;
	int maxLength=DBL_DIG;
#endif

	char*homedir=getenv("HOME");
	char*path=new char[strlen(homedir)+20];
	memcpy(path,homedir,strlen(homedir));
	memcpy(&path[strlen(homedir)],"/.concalcvariables",19);

	struct timeval rndTime;
	gettimeofday(&rndTime,NULL);
	srand(rndTime.tv_usec*rndTime.tv_sec);
	
	int fileLength;
	struct stat fileStat;
	char*variablesString;

	char*var;

	if(lstat(path,&fileStat) == 0)
	{
		FILE*variablesFile=fopen(path,"r");
		if(variablesFile!=NULL)
		{
			fileLength=fileStat.st_size;
			variablesString=new char[fileLength+1];
			fread(variablesString,fileLength,1,variablesFile);
			
			int varStart=0;
			int varEnd=0;
			int varCount=0;
			bool real=true;
		
		
			for(int c=0; c<fileLength && varCount<27; c++)
			{
				if(variablesString[c]=='\n' || c == fileLength-1)
				{
					varEnd=c;
					var=new char[varEnd-varStart+1];
					memcpy(var,&variablesString[varStart],varEnd-varStart);
					var[varEnd-varStart]=(char)0;
					scriptData.vars[varCount][0].type=NFLOAT;
					if(real)
					{
#ifndef NO_LONG_DOUBLE
					vars[varCount]=strtold(var,NULL);
#else 
					vars[varCount]=strtod(var,NULL);
#endif
					real=false;
					}
					else 
					{
#ifndef NO_LONG_DOUBLE
					scriptData.vars[varCount][0].fval=Complex(vars[varCount],strtold(var,NULL));
#else 
					scriptData.vars[varCount][0].fval=Complex(vars[varCount],strtod(var,NULL));
#endif
						varCount++;
						real=true;
					}
					varStart=varEnd+1;
					delete[] var;
				}
			}
			fclose(variablesFile);
			delete[] variablesString;
		}
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
					printf("Invalid argument for -a!\n\nPossible Arguments:\n-a deg\n-a rad\n-a gra\n\nPlease use man concalc for further information\n");
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
					printf("Invalid argument for -m!\n\nPossible Arguments:\n-m base\n-m std\n\nPlease use man concalc for further information\n");
					delete pref;
					delete[] vars;
					return 0;
				}
				c++;
			}
			else {
				printf("Invalid argument for -m!\n\nPossible Arguments:\n-m base\n-m std\n\nPlease use man concalc for further information\n");
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
					printf("Invalid argument for -m!\n\nPossible Arguments:\n-m base\n-m std\n\nPlease use man concalc for further information\n");
					delete pref;
					delete[] vars;
					return 0;
				}
				c++;
			}
			else {
				printf("Invalid argument for -b!\n\nPossible Arguments:\n-b dec\n-b hex\n-b bin\n-b oct\n\nPlease use man concalc for further information\n");
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
				if(outLen<2 || outLen>pref->precision)
				{
					printf("Invalid argument for -o!\n\nThe argument must be a number between 2 and %i.\nFor example: -o 8\n\nPlease use man concalc for further information\n",pref->precision);
					delete pref;
					delete[] vars;
					return 0;
				}
				pref->outputLength=outLen;
				
				c++;
			}
			else {
				printf("Invalid argument for -o!\n\nThe argument must be a number between 2 and %i.\nFor example: -o 8\n\nPlease use man concalc for further information\n",pref->precision);
				delete pref;
				delete[] vars;
				return 0;
			}
		}
		else if(strcmp(argv[c],"-c")==0 || strcmp(argv[c],"--complex")==0)
		{
			pref->complex=true;
		}
		else if(strcmp(argv[c],"-h")==0 || strcmp(argv[c],"--help")==0)
		{
			printf("Usage:\nconcalc \"input\"\nFor example: calc \"2*(3+7/2)\"\n\nOptions:\n-a, --angle (deg, rad, gra)\n-m, --mode (base, std, script)\n-c, --complex\n-b, --base (dec, hex, bin, oct) only in base mode\n-o, --output (2-18)\n-h, --help\n-v, --version\n\nPlease use man concalc for  further information\n");
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
				input=(char*)malloc(strlen(argv[c])+1);
				memcpy(input,argv[c],strlen(argv[c])+1);
			}
			else {
				char*temp=input;
				input=(char*)malloc(strlen(argv[c])+strlen(temp)+1);
				memcpy(input,temp,strlen(temp));
				memcpy(&input[strlen(temp)],argv[c],strlen(argv[c])+1);
			}
		}
	}
	if(pref->calcType == SCIENTIFIC && pref->base!=DEC)
	{
		printf("Invalid option -b!\nOption -b can only be used when -m is set!\n\nPlease use man concalc for further information\n");
		delete pref;
		delete[] vars;
		return 0;
	}
	if(ask)
	{
		input=(char*)malloc(1026);
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
		input =(char*)malloc(fileinfo.st_size+2);
		if(fread(input,fileinfo.st_size,1,scriptFile)<=0)
		{
			printf("Can't read file %s !\n",path);
			delete[]path;
			return 0;
		}		
		input[fileinfo.st_size]=(char)0;
	}

	char*printString=new char[50];
	char*res=NULL;
		
	scriptData.error=false;
	
	struct termios terminfo,oldTerminfo;
	tcgetattr(fileno(stdout),&terminfo);
	oldTerminfo=terminfo;
	terminfo.c_lflag &=~ECHO;
	terminfo.c_lflag &=~ICANON;
	if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
		perror("tcsetattr fehler");

	scriptData.status=0;
	scriptData.usleep=false;
	scriptData.bbreak=false;
	scriptData.bcontinue=false;
	
	scriptData.exit=false;
	
	if(script)
	{
		
		
		scriptData.countDifference=0;
		initDebugging(input,&scriptData);
		res=preprocessor(input,pref,true);
		
		
		if(res==NULL)
		{
			fprintf(stderr,"Preprocessor Error\n");
			free(input);
			delete[]printString;
			delete[]vars;
			delete pref;
			if(tcsetattr(fileno(stdout),TCSANOW,&oldTerminfo)!=0)
				perror("tcsetattr fehler");
			return 0;
		}
		searchScripts(res,pref,vars,&scriptData);
				

		scriptData.calcMode=false;
		fprintf(stderr,"\nProcessing main file ...\n");

		s=new Script((Script*)NULL,res,pref,vars,&scriptData);
		loadSubScripts(&scriptData,pref,vars,s);
		if(scriptData.error)
		{
			fprintf(stderr,"Script processing failed\n");
			free(input);
			delete[]printString;
			delete[]vars;
			delete pref;
			delete s;
			if(tcsetattr(fileno(stdout),TCSANOW,&oldTerminfo)!=0)
				perror("tcsetattr error");
			return 0;
		}
		value=s->exec();
	}
	else 
	{
		res=preprocessor(input,pref,false);
		scriptData.calcMode=true;
		s=new Script((Script*)NULL,res,pref,vars,&scriptData);
		value=s->exec();
		delete s;
	}
	

	
	if(pref->calcType==SCIENTIFIC)
	{	
		switch(value.type)
		{
			case NFLOAT:
			{
				if(value.fval.imag()==0.0)
				{
					printf("%.*Lg",pref->outputLength,real(value.fval));
				}
				else {
					if(value.fval.imag()>0.0)
						printf("%.*Lg+%.*Lgi",pref->outputLength,real(value.fval),pref->outputLength,imag(value.fval));
					else printf("%.*Lg%.*Lgi",pref->outputLength,real(value.fval),pref->outputLength,imag(value.fval));
				}
	
				break;
			}
			case NINT:
			{
				printf("%lli",value.ival);
				break;
			}
			case NBOOL:
				if(value.bval)
					printf("true");
				else printf("false");
				break;
			case NCHAR:
			{
				printf(value.cval);
				break;
			}
			default:
				printf("none");
				break;
		}
		printf("\n");
		//printf("%.*Lg\n",pref->outputLength,vars[26][0]=;
	}
	else {
		long long ival;
		
		switch(value.type)
		{
			case NFLOAT:
				ival=(long long)value.fval.real();
				break;
			case NINT:
				ival=value.ival;
				break;
			case NBOOL:
				ival=(long long)value.bval;
				break;
			default:
				ival=0;
		}
		
		
		switch(pref->base)
		{
			case DEC:
				printf("%lli\n",ival);
				break;
			case BIN:
			{
				long long result=ival;
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
				printf("%LX\n",ival);
				break;
			case OCT:
				printf("%llo\n",ival);
				break;
		}	

	}

	char*newVarString="";

	char*varString=new char[maxLength+20];

	scriptData.vars[26][0]=value;

	for(int c=0; c<27; c++)
	{
		if(scriptData.vars[c][0].type==NINT)
			scriptData.vars[c][0].fval=Complex((long double)scriptData.vars[c][0].ival,0.0);
		else if(scriptData.vars[c][0].type==NBOOL)
			scriptData.vars[c][0].fval=Complex((long double)scriptData.vars[c][0].bval,0.0);
		else if(scriptData.vars[c][0].type!=NFLOAT)
			scriptData.vars[c][0].fval=Complex(NAN,0.0);
		
		sprintf(varString,"%.*Lg",maxLength,scriptData.vars[c][0].fval.real());
		newVarString=strins(newVarString,varString,strlen(newVarString));
		newVarString=strins(newVarString,"\n",strlen(newVarString));
		
		sprintf(varString,"%.*Lg",maxLength,scriptData.vars[c][0].fval.imag());
		newVarString=strins(newVarString,varString,strlen(newVarString));
		newVarString=strins(newVarString,"\n",strlen(newVarString));
	}
	chdir(getenv("HOME"));
	FILE*variablesFile=fopen(".concalcvariables","w");
	if(variablesFile!=NULL)
	{
		fwrite(newVarString,strlen(newVarString),1,variablesFile);
		fclose(variablesFile);
	}
	delete[] newVarString;

	if(tcsetattr(fileno(stdout),TCSANOW,&oldTerminfo)!=0)
		perror("tcsetattr error");
	
	free(res);
	for(int c=0; c<VARNUM; c++)
	{
		if(scriptData.vars[c]!=NULL)
			free(scriptData.vars[c]);
	}
	delete[] scriptData.vars;
	delete pref;
	delete[] vars;
	delete[] path;
	delete[] varString;
	delete[] printString;
	return 0;
}





void initDebugging(char*code,ThreadSync*scriptData)
{

	int pos1=0,pos2=0;
	bool quote=false;
	char* line;
	int len=strlen(code);
	
	int lineLen;
	int lineCount=0;
	int run=1;
	int c;
	while(run)
	{
		for(c=pos1;code[c]!='\n' && c<=len; c++);
		pos2=c;
		if(c>=len)
			run=false;
		lineCount++;
		line=new char[pos2-pos1+1];
		memcpy(line,&code[pos1],pos2-pos1);
		line[pos2-pos1]=(char)0;
		lineLen=strlen(line);
		for(int c=0; c<lineLen && !(line[c]=='/' && line[c+1]=='/'); c++)
		{
			if(line[c]=='\"')
				quote=!quote;
			else if(!quote && line[c]==';')
			{
				scriptData->semicolonLines.NewItem(lineCount);
			}
		}
		pos1=pos2+1;
		delete[]line;
	}
}


void searchScripts(char*code,Preferences*pref,Variable*vars,ThreadSync*scriptData)
{
//	char*cleanString=preprocessor(code,pref,true);
	char*scriptName;
	int len=strlen(code);
	int pos=0,pos2;
	FILE*subFile;
	while(pos<len)
	{
		if(strncmp(&code[pos],"run(\"",4) == 0) //run("")
		{
			pos2=bracketFind(code,")",pos+4);
			if(pos2-pos<7 || code[pos2-1]!='\"')
			{
				pos++;
				continue;
			}
			scriptName=new char[pos2-pos-5];
			strcopy(scriptName,&code[pos+5],pos2-pos-6);
			bool newScript=true;
			for(int c=0; c<scriptData->subprogramPath.GetLen(); c++)
				if(strcmp(scriptData->subprogramPath[c],scriptName)==0)
				{
					newScript=false;
					break;
				}
			if(newScript)
			{
				struct stat fileStat;
				char*subFileContent;

				if(lstat(scriptName,&fileStat)!=0)
					;
				else {
					subFile=fopen(scriptName,"r");
					if(subFile==NULL || fileStat.st_size<=0)
						;
					else
					{
						subFileContent=new char[fileStat.st_size+1];
						subFileContent[fileStat.st_size]=(char)0;
						fread(subFileContent,fileStat.st_size,1,subFile);
						fclose(subFile);
						scriptData->subprogramPath.NewItem(scriptName);
						searchScripts(subFileContent,pref,vars,scriptData);
						delete[]subFileContent;
					}
				}
			}
			pos=pos2+1;
		}
		else pos++;
	}
}


void loadSubScripts(ThreadSync*scriptData,Preferences*pref,Variable*vars,Script*parent)
{
	struct stat fileStat;
	char*subFileContent;
	char*cleanSubFileContent;
	char*filePath;
	Script*subScript;
	FILE*subFile;
	for(int c=0; c<scriptData->subprogramPath.GetLen(); c++)
	{
		filePath=scriptData->subprogramPath[c];
		if(lstat(filePath,&fileStat)!=0)
			scriptData->subprograms.NewItem((Math*)NULL);
		else {
			subFile=fopen(filePath,"r");
			if(subFile==NULL || fileStat.st_size<=0)
				scriptData->subprograms.NewItem((Math*)NULL);
			else
			{
				subFileContent=new char[fileStat.st_size+1];
				subFileContent[fileStat.st_size]=(char)0;
				fread(subFileContent,fileStat.st_size,1,subFile);
				fclose(subFile);
				scriptData->countDifference+=scriptData->semicolonLines.GetLen();
				initDebugging(subFileContent,scriptData);
				cleanSubFileContent=preprocessor(subFileContent,pref,true);
				fprintf(stderr,"\nProcessing file ");
				fprintf(stderr,scriptData->subprogramPath[c]);
				fprintf(stderr,"\n");
				if(cleanSubFileContent==NULL)
				{
					fprintf(stderr,"Preprocessor Error\n");
					subScript=NULL;
				}
				else 
				{
					subScript=new Script(parent,NULL,pref,vars,scriptData);
					subScript->split(cleanSubFileContent,0,strlen(cleanSubFileContent));
				}
				free(subFileContent);
				scriptData->subprograms.NewItem(subScript);
			}
		}
	}

}

/*
int preferencesPreprocessor(char *code,Preferences*pref)
{
	int pos=0,startPos=0,endPos=0,len;
	bool comment=false,quote=false;
	char*configString=NULL;
	
	
	while(pos<=(len=strlen(code)))
	{
		if(quote)
		{
			if(code[pos]=='\"')
				quote=false;
		}
		else if(comment)
		{
			if(code[pos]=='\n')
				comment=false;
		}
		else if(code[pos]=='/' && code[pos+1]=='/')
			comment=true;
		else if(code[pos]=='\"')
			quote=true;
		else if(code[pos]=='#')
		{
			startPos=pos;
			int configStartPos=startPos;
			endPos=pos;
			
			if(strncmp(&code[startPos],"#config",7)==0)
				configStartPos+=7;
			else return PPINVALIDCOMMAND;
			
			while(code[endPos]!='\n' && endPos<=len) endPos++;
			

			
			while((code[configStartPos]==' ' || code[configStartPos]=='\t') && configStartPos<=len) configStartPos++;
			
			configString=(char*)realloc(configString,endPos-configStartPos+1);
			strcopy(configString,&code[configStartPos],endPos-configStartPos);
		

			if(strncmp(configString,"complexon",9)==0)
				pref->complex=true;
			else if(strncmp(configString,"complexoff",10)==0)
				pref->complex=false;
			else if(strncmp(configString,"angledeg",8)==0)
				pref->angle=DEG;
			else if(strncmp(configString,"anglerad",8)==0)
				pref->angle=RAD;
			else if(strncmp(configString,"anglegra",8)==0)
				pref->angle=GRA;
			else if(strncmp(configString,"modebase",8)==0)
				pref->calcType=BASE;
			else if(strncmp(configString,"modescientific",14)==0)
				pref->calcType=SCIENTIFIC;
			else if(strncmp(configString,"clearmemory",11)==0)
				;//not used in calc
			else if(strncmp(configString,"outputlength",12)==0)
			{				int num=atoi(configString+12);
				if(num>=2 && num<=pref->precision)
					pref->outputLength=num;
				else return PPINVALIDARGUMENT;
			}
			else return PPINVALIDPREF;
			
			memmove(&code[startPos],&code[endPos],len-endPos+1);
			
			if(endPos==len)
				break;
			pos=startPos;
		}
		pos++;
	}
	
	if(strlen(code)<=0)
		return PPEMPTY;
	
	return 0;
}
*/




