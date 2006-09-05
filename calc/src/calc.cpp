#include <stdio.h>
#include "global.h"
#include <sys/time.h>
#include <float.h>
#include <stdlib.h>
#include "consolecalc.h"

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
	Variable *vars=new Variable[27];

	for(int c=0; c<27;c++)
		vars[c].NewItem(0.0);
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

	struct timeval rndTime;
	gettimeofday(&rndTime,NULL);
	srand(rndTime.tv_usec*rndTime.tv_sec);
	
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
				vars[varCount][0]=strtold(var,NULL);
#else 
				vars[varCount][0]=strtod(var,NULL);
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
			printf("Usage:\ncalc \"input\"\nFor example: calc \"2*(3+7/2)\"\n\nOptions:\n-a, --angle (deg, rad, gra)\n-m, --mode (base, std, script)\n-b, --base (dec, hex, bin, oct) only in base mode\n-o, --output (2-18)\n-h, --help\n-v, --version\n\nPlease use man calc for  further information\n");
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
	}
	char*res=checkString(input,pref,vars);
	char*printString=new char[50];
	if(script)
	{
		fprintf(stderr,"\nProcessing main file ...\n");
		if(res==NULL)
		{
			fprintf(stderr,"Preprocessor Error\n");
			delete[]input;
			delete[]printString;
			delete[]vars;
			delete pref;
			return 0;
		}
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
		scriptData.vars=new Number*[27];
		for(int c=0; c<27;c++)
		{
			scriptData.vars[c]=(Number*)malloc(sizeof(Number));
			scriptData.numlen[c]=1;
			scriptData.vars[c][0].type=NNONE;
		}
		for(int c=0; c<27; c++)
			scriptData.numlen[c]=0;
		

		searchScripts(input,pref,vars,&scriptData);
		scriptData.countDifference=0;
		initDebugging(input,&scriptData);

		
		s=new Script((Script*)NULL,res,pref,vars,&scriptData);
		loadSubScripts(&scriptData,pref,vars,s);
		if(scriptData.error)
		{
			fprintf(stderr,"Script processing failed\n");
			delete[]input;
			delete[]printString;
			delete[]vars;
			delete pref;
			delete s;
			if(tcsetattr(fileno(stdout),TCSANOW,&oldTerminfo)!=0)
				perror("tcsetattr fehler");
			return 0;
		}
		
		
		s->exec();
		
		if(tcsetattr(fileno(stdout),TCSANOW,&oldTerminfo)!=0)
			perror("tcsetattr fehler");
		
		delete[] scriptData.vars;
	}	
	else if(pref->calcType==SCIENTIFIC)
	{
		printf("%.*Lg\n",pref->outputLength,vars[26][0]=calculate(res,pref,vars));
	}
	else {
		
		switch(pref->base)
		{
			case DEC:
				printf("%lli\n",(long long)(vars[26][0]=calculate(res,pref,vars)));
				break;
			case BIN:
			{
				long long result=(long long)(vars[26][0]=calculate(res,pref,vars));
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
				printf("%LX\n",(long long)(vars[26][0]=calculate(res,pref,vars)));
				break;
			case OCT:
				printf("%llo\n",(long long)(vars[26][0]=calculate(res,pref,vars)));
				break;
		}	

	}

	char*newVarString="";

	char*varString=new char[maxLength+20];


	for(int c=0; c<27; c++)
	{
		sprintf(varString,"%.*Lg",maxLength,vars[c][0]);
		newVarString=strins(newVarString,varString,strlen(newVarString));
		newVarString=strins(newVarString,"\n",strlen(newVarString));
	}
	chdir(getenv("HOME"));
	variablesFile=fopen(".calcvariables","w");
	if(variablesFile!=NULL)
	{
		fwrite(newVarString,strlen(newVarString),1,variablesFile);
		fclose(variablesFile);
	}


	delete[]input;
	delete[]res;
		

	delete pref;
	delete[] vars;
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
		for(c=pos1;code[c]!='\n' && c<len+1; c++);
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
	char*cleanString=checkString(code,pref,vars);
	if(cleanString==NULL)
		return;
	char*scriptName;
	int len=strlen(cleanString);
	int pos=0,pos2;
	FILE*subFile;
	while(pos<len)
	{
		if(strncmp(&cleanString[pos],"run(\"",4) == 0) //run("")
		{
			pos2=bracketFind(cleanString,")",pos+4);
			if(pos2-pos<7 || cleanString[pos2-1]!='\"')
			{
				pos++;
				continue;
			}
			scriptName=new char[pos2-pos-5];
			strcopy(scriptName,&cleanString[pos+5],pos2-pos-6);
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
	delete[] cleanString;
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
				cleanSubFileContent=checkString(subFileContent,pref,vars);
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
					subScript->split(cleanSubFileContent);
				}
				delete[]subFileContent;
				scriptData->subprograms.NewItem(subScript);
			}
		}
	}

}









