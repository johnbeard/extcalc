/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         global.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "global.h"
//Added by qt3to4:



#ifndef CONSOLE
#include <QCustomEvent>
QString cleanConfigString(QString prefName,QString par)
{
	QString parameter=par;
	QString sign(QChar((unsigned short)ROOTSTRING));
	parameter.replace(sign,"root");
	sign=(QChar((unsigned short)PISTRING));
	parameter.replace(sign,"pi");
	sign=(QChar((unsigned short)EULERSTRING));
	parameter.replace(sign,"euler");
	sign=(QChar((unsigned short)INTEGRALSTRING));
	parameter.replace(sign,"integral");
	sign=(QChar((unsigned short)DELTASTRING));
	parameter.replace(sign,"differential");
	sign=(QChar((unsigned short)MEGASTRING));
	parameter.replace(sign,"mega");
	sign=(QChar((unsigned short)GIGASTRING));
	parameter.replace(sign,"giga");
	sign=(QChar((unsigned short)TERASTRING));
	parameter.replace(sign,"tera");
	if(prefName.length() <=0)
		return parameter;
	else return prefName+"="+parameter+"\n";
}

QString resetConfigString(QString str)
{
	QString retObject=str;
	QString sign(QChar((unsigned short)ROOTSTRING));
	retObject.replace("root",sign);
	sign=(QChar((unsigned short)PISTRING));
	retObject.replace("pi",sign);
	sign=(QChar((unsigned short)EULERSTRING));
	retObject.replace("euler",sign);
	sign=(QChar((unsigned short)INTEGRALSTRING));
	retObject.replace("integral",sign);
	sign=(QChar((unsigned short)DELTASTRING));
	retObject.replace("differential",sign);
	sign=(QChar((unsigned short)MEGASTRING));
	retObject.replace("mega",sign);
	sign=(QChar((unsigned short)GIGASTRING));
	retObject.replace("giga",sign);
	sign=(QChar((unsigned short)TERASTRING));
	retObject.replace("tera",sign);
	
	return retObject;
}

QString getConfigString(QString * configFile,QString objectName)
{
	QString retObject="";
	int pos=0;
	pos=configFile->find(objectName+"=");
	if(pos != -1)
		pos+=objectName.length()+1;
	else return QString("");

	while((*configFile)[pos] != '\n' && (*configFile)[pos] != '\t' && !((*configFile)[pos-1] == '\\' && (*configFile)[pos] == '\\'))
	{
		
		retObject+=(*configFile)[pos];
		pos++;
		if(pos > (int)configFile->length())
			return QString("");
	}
	
	return retObject;
}


QString getUnicode(int code)
{
	QString retString;
	QChar cCode((unsigned short)code);
	retString.setUnicode(&cCode,1);	

	return retString;
}


QString formatOutput(long double num,Preferences*pref)
{
	QString ret;
	char*outString=new char[pref->precision+20];
	
	if(pref->calcType==SCIENTIFIC)
	{
		switch(pref->outputType)
		{
			case FIXEDNUM:
			{
				sprintf(outString,"%.*Le",pref->outputLength,num);
				ret=QString(outString);
				break;
			}
		
			case VARIABLENUM:
			{
				sprintf(outString,"%.*Lg",pref->outputLength,num);
				ret=QString(outString);
				break;
			}
			case EXPSYM:
			{
				if(num < 1e-12 && num > -1e-12)
				{
					num*=1e15;
					ret="f";
				}
				else if(num < 1e-9 && num > -1e-9)
				{
					num*=1e12;
					ret="p";
				}			
				else if(num < 1e-6 && num > -1e-6)
				{
					num*=1e9;
					ret="n";
				}
				else if(num < 1e-3 && num > -1e-3)
				{
					num*=1e6;
					ret="\xb5";
				}
				else if(num < 1 && num > -1)
				{
					num*=1e3;
					ret="m";
				}
				else if(num < 1e3 && num > -1e3)
				{
					ret="";
				}
				else if(num < 1e6 && num > -1e6)
				{
					num/=1e3;
					ret="k";
				}
				else if(num < 1e9 && num > -1e9)
				{
					num/=1e6;
					ret=getUnicode(MEGASTRING);
				}
				else if(num < 1e12 && num > -1e12)
				{
					num/=1e9;
					ret=getUnicode(GIGASTRING);
				}
				else
				{
					num/=1e12;
					ret=getUnicode(TERASTRING);
				}
				sprintf(outString,"%.*Lg",pref->outputLength,num);
				ret=QString(outString)+ret;
				break;
			}
		}
	}
	else {
		long long iNum=(long long)num;
#if QT_VERSION < 0x030200
			char*buffer=new char[66];
			if(pref->base==DEC)
			{
				sprintf(buffer,"%lli",iNum);
				ret=QString(buffer);
			}
			else if(pref->base==HEX)
			{
				sprintf(buffer,"%llX",iNum);
				ret=QString(buffer);
			}
			else if(pref->base==OCT)
			{
				sprintf(buffer,"%llo",iNum);
				ret=QString(buffer);
			}
			else
			{
				unsigned int hipart=(uint)(iNum>>32);
				unsigned int lowpart=(uint)(iNum&0xFFFFFFFF);

				if(hipart>0)
					ret=QString(QString::number(hipart,2));
				else ret="";
				ret+=QString::number(lowpart,2);
			}
#else
		int base;
		if(pref->base==DEC)
			base=10;
		else if(pref->base==HEX)
			base=16;
		else if(pref->base==OCT)
			base=8;
		else base=2;

		ret=QString(QString::number(iNum,base)).upper();
#endif
	}
	delete[] outString;
	return ret;
}

QString formatOutput(Number num,Preferences*pref,ThreadSync*varData)
{
	QString ret;
	switch(num.type)
	{
		case NINT:
			ret=formatOutput((long double)num.ival,pref);
//			ret+="(int)";
			break;
		case NFLOAT:
		case NCOMPLEX:
			ret=formatOutput(num.fval.real(),pref);
			if(num.fval.imag()!=0.0 && pref->complex)
			{
				if(num.fval.imag()>0.0)
					ret+=" +";
				else ret+=" ";
				ret+=formatOutput(imag(num.fval),pref);
				ret+="i";
			}
//			ret+="(float)";
			break;
		case NBOOL:
			ret=formatOutput((long double)num.bval,pref);
//			ret+="(bool)";
			break;
		case NCHAR:
			ret+=QString(num.cval);
//			ret+="(string)";
			break;
		case NVECTOR:
			if(varData==NULL)
				ret=formatOutput((long double)num.ival,pref);
			else {
				if(num.ival<0 || num.ival >=VARNUM)
				{
					ret=QString("invalid");
					break;
				}
				int end=varData->dimension[num.ival][0];
				ret=QString("");
				for(int c=0; c<end;c++)
				{
					if(varData->vars[num.ival][c].type!=NVECTOR && varData->vars[num.ival][c].type!=NMATRIX)
						ret+=formatOutput(varData->vars[num.ival][c],pref);
					ret+=" ";
				}
			}
			break;
		case NMATRIX:
		{
			int effIndex;
			for(int c=0; c<varData->dimension[num.ival][0];c++)
			{
				for(int c1=0; c1<varData->dimension[num.ival][1];c1++)
				{
					effIndex=c1*varData->dimension[num.ival][0]+c;
					if(effIndex<=varData->numlen[num.ival] && varData->vars[num.ival][effIndex].type!=NMATRIX && varData->vars[num.ival][effIndex].type!=NVECTOR)
						ret+=formatOutput(varData->vars[num.ival][effIndex],pref);
					else ret+="invalid";
					ret+=" ";
				}
				ret+="\n";
			}
			break;
	}
		default:
			ret=("invalid");
			break;
	}
	return ret;
}


QColor getColor(QString colorName)
{
	if(colorName == GRAPHH_COL1)
		return QColor(0,0,0);					//red
	else if(colorName == GRAPHH_COL3)
		return QColor(205,135,15);				//brown
	else if(colorName == GRAPHH_COL5)
		return QColor(0,0,255);					//blue
	else if(colorName == GRAPHH_COL4)
		return QColor(0,220,0);					//green
	else if(colorName == GRAPHH_COL6)
		return QColor(255,0,255);				//violet
	else if(colorName == GRAPHH_COL7)
		return QColor(255,192,0);				//orange
	else if(colorName == GRAPHH_COL8)
		return QColor(255,0,0);					//red
	else if(colorName == GRAPHH_COL9)
		return QColor(255,255,0);				//yellow
	else if(colorName == GRAPHH_COL10)
		return QColor(0,220,220);				//magenta
	else if(colorName == GRAPHH_COL2)
		return QColor(150,150,150);				//grey
	else if(colorName == GRAPHH_COL11)
		return QColor(1,1,1);
	else return QColor(0,0,0);
}


QString getColorName(QColor col)
{
	if(col == QColor(0,0,0))
		return QString(GRAPHH_COL1);					//red
	else if(col == QColor(205,135,15))
		return QString(GRAPHH_COL3);				//brown
	else if(col == QColor(0,0,255))
		return QString(GRAPHH_COL5);					//blue
	else if(col == QColor(0,220,0))
		return QString(GRAPHH_COL4);					//green
	else if(col == QColor(255,0,255))
		return QString(GRAPHH_COL6);				//violet
	else if(col == QColor(255,192,0))
		return QString(GRAPHH_COL7);				//orange
	else if(col == QColor(255,0,0))
		return QString(GRAPHH_COL8);					//red
	else if(col == QColor(255,255,0))
		return QString(GRAPHH_COL9);				//yellow
	else if(col == QColor(0,220,220))
		return QString(GRAPHH_COL10);				//magenta
	else if(col == QColor(150,150,150))
		return QString(GRAPHH_COL2);				//grey
	else if(col == QColor(1,1,1))
		return QString(GRAPHH_COL11);
	else return QString(GRAPHH_COL1);
	
}


long double runCalc(QString line,Preferences*pref,Variable*vars)
{

	char*cleanString=preprocessor(&line,pref,false);
	if(cleanString==NULL)
		return NAN;
	else 
	{
		Calculate ca(NULL,cleanString,0,strlen(cleanString),pref,vars);
		double result= ca.calc();
		free(cleanString);
		return (long double)result;
	}
}

QString getErrorMessage()
{
	int er=errno;
	switch(er)
	{
		case EACCES:
			return(QString("Permission denied"));
		case EBADF:
			return(QString("Bad file descriptor"));
		case EBUSY:
			return(QString("Device or resource busy"));
		case ECANCELED:
			return(QString("Operation canceled"));
		case EEXIST:
			return(QString("File exists"));
		case EFAULT:
			return(QString("Bad address"));
		case EFBIG:
			return(QString("File too large"));
		case EINVAL:
			return(QString("Invalid argument"));
		case EIO:
			return(QString("Input/output error"));
		case EISDIR:
			return(QString("Is a directory"));
		case EMFILE:
			return(QString("Too many open files"));
		case ENAMETOOLONG:
			return(QString("Filename too long"));
		case ENOENT:
			return(QString("No such file or directory"));
		case ENOMEM:
			return(QString("Not enough space"));
		case ENOTDIR:
			return(QString("Not a directory"));
		case ENOTEMPTY:
			return(QString("Directory not empty"));
		case EPERM:
			return(QString("Operation not permitted"));
		case EROFS:
			return(QString("Read-only file system"));
		case EUSERS:
			return(QString("Too many users"));
		default:
			return(QString("Unknown error"));
	}
}

void MessageBox(QString text)
{
	QMessageBox mb("Extcalc",text,
				   QMessageBox::Information,QMessageBox::Ok ,QMessageBox::NoButton,QMessageBox::NoButton);
	mb.exec();
} 


int YesNoBox(QString text)
{
	QMessageBox mb("Extcalc",text,
				   QMessageBox::Information ,QMessageBox::Yes ,QMessageBox::No,QMessageBox::NoButton);
	switch(mb.exec())
	{
		case QMessageBox::Yes:
			return 0;
		default:
		{
			return 1;
		}
	}
}

 int YesNoCancelBox(QString text)
{
	QMessageBox mb("Develop",text,
				   QMessageBox::Information ,QMessageBox::Yes ,QMessageBox::No,QMessageBox::Cancel);
	switch(mb.exec())
	{
		case QMessageBox::Yes:
			return 0;
		case QMessageBox::No:
			return 1;
		default:
		{
			return -1;
		}
	}
}

 void WarningBox(QString text)
{
	QMessageBox mb("Develop",text,
				   QMessageBox::Warning,QMessageBox::Ok ,QMessageBox::NoButton,QMessageBox::NoButton);
	mb.exec();

}

 void ErrorBox(QString text)
{
	QMessageBox mb("Develop",text,
				   QMessageBox::Critical,QMessageBox::Ok ,QMessageBox::NoButton,QMessageBox::NoButton);
	mb.exec();

}
#endif
/*
char*checkString(QString input,Preferences*pref)
{

	if(input.length()<=0)
		return NULL;
	
	QString qstr=input;
	qstr.replace("\xb2"+getUnicode(ROOTSTRING),"sqrt");
	qstr.replace("2"+getUnicode(ROOTSTRING),"sqrt");
	qstr.replace("\xb3"+getUnicode(ROOTSTRING),"curt");
	qstr.replace("3"+getUnicode(ROOTSTRING),"curt");
	qstr.replace(getUnicode(ROOTSTRING),"root");
	qstr.replace(getUnicode(DEGREESTRING),"sprod");

	qstr.replace(getUnicode(PISTRING),"pi");
	qstr.replace(getUnicode(EULERSTRING),"eu");
	qstr.replace(getUnicode(INTEGRALSTRING),"integ");
	qstr.replace("\xb2","^(2)");
	qstr.replace("\xb3","^(3)");

	qstr.replace(getUnicode(MEGASTRING),"e6");
	qstr.replace(getUnicode(GIGASTRING),"e9");
	qstr.replace(getUnicode(TERASTRING),"e12");


	char*output=new char[qstr.length()+1];
	output[qstr.length()]=(char)0;
	for(int c=0; c<(signed)qstr.length();c++)
	{
		output[c]=qstr[c].latin1();
		//make all changes here
	}
	char*ret=checkStringAnsi(output,pref);
	delete[]output;
	return ret;
}
*/
char* preprocessor(char*input,Preferences*pref,bool script)
{
	char*ret=removeComments(input);
	if(ret==NULL)
		return NULL;

	if(script)
	{
		ret=preferencesPreprocessor(ret,pref);
		if(ret==NULL)
			return NULL;

		ret=macroPreprocessor(ret);
		if(ret==NULL)
			return NULL;
	}
	ret=cleanString(ret,pref);
	if(ret==NULL)
		return NULL;
		
	return ret;	
}

#ifndef CONSOLE
char* preprocessor(QString *input,Preferences*pref,bool script)
{
	if(!script)
		replaceConstants(input,pref);
	char*ret=removeUnicode(input);
	if(ret==NULL)
		return NULL;
	ret=preprocessor(ret,pref,script);
	return ret;
}
char* removeUnicode(QString*input)
{
	if(input->length()<=0)
		return NULL;

	QString qstr=*input;
	qstr.replace("\xb2"+getUnicode(ROOTSTRING),"sqrt");
	qstr.replace("2"+getUnicode(ROOTSTRING),"sqrt");
	qstr.replace("\xb3"+getUnicode(ROOTSTRING),"curt");
	qstr.replace("3"+getUnicode(ROOTSTRING),"curt");
	qstr.replace(getUnicode(ROOTSTRING),"root");
	qstr.replace(getUnicode(DEGREESTRING),"sprod");

	qstr.replace(getUnicode(PISTRING),"pi");
	qstr.replace(getUnicode(EULERSTRING),"eu");
	qstr.replace(getUnicode(INTEGRALSTRING),"integ");
	qstr.replace("\xb2","^(2)");
	qstr.replace("\xb3","^(3)");

	qstr.replace(getUnicode(MEGASTRING),"e6");
	qstr.replace(getUnicode(GIGASTRING),"e9");
	qstr.replace(getUnicode(TERASTRING),"e12");

	const char*tmp=qstr.ascii();
	char*output=(char*)malloc(strlen(tmp)+1);
	memcpy(output,tmp,strlen(tmp)+1);

	return output;
}


void replaceConstants(QString *input,Preferences*pref)
{
	for(int c=0; c<pref->constLen; c++)
		input->replace(*(pref->constList[c].identifier),"("+*(pref->constList[c].value)+")");
}
#endif

char* removeComments(char*input)
{
	unsigned int len=strlen(input);
	int end=0;
	bool str=false;
	for(unsigned int c=0; c<len; c++)
	{
		if(input[c]=='/' &&!str)
		{
			end=-1;
			if(input[c+1]=='/')
			{
				for(unsigned int c1=c+2; c1<len; c1++)
				{
					if(input[c1]=='\n')
					{
						end=c1-1;
						break;
					}
				}
			}
			else if(input[c+1]=='*')
			{
				for(unsigned int c1=c+2; c1<len; c1++)
				{
					if(input[c1]=='*' && input[c1+1]=='/')
					{
						end=c1+1;
						break;
					}
				}
			}
			else continue;
			if(end==-1)
				end=len-1;
			memmove(&input[c],&input[end+1],len-end);
			len=strlen(input);
		}
		else if(input[c]=='\"')
			str=!str;
	}
	
	
	return input;
}
char* preferencesPreprocessor(char*code,Preferences*pref)
{
	int pos=0,startPos=0,endPos=0,len=strlen(code);
	bool quote=false;
	char*configString=NULL;
	
	
	while(pos<len)
	{
		if(quote)
		{
			if(code[pos]=='\"')
				quote=false;
		}
		else if(code[pos]=='\"')
			quote=true;
		else if(code[pos]=='#')
		{
			startPos=pos;
			int configStartPos=startPos;
			endPos=pos;
			
			if(strncmp(&code[startPos],"#config",7)==0)
				configStartPos+=7;
			else {
				pos++;
				continue;
			}
			
			while(code[endPos]!='\n' && endPos<=len)
				endPos++;
			
			while((code[configStartPos]==' ' || code[configStartPos]=='\t') && configStartPos<=len)
				configStartPos++;
			
			configString=(char*)malloc(endPos-configStartPos+1);
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
#ifndef CONSOLE
			else if(strncmp(configString,"clearmemory",11)==0)
				pref->clearScriptMemory=true;
#endif
			else if(strncmp(configString,"outputlength",12)==0)
			{
				int num=atoi(configString+12);
				if(num>=2 && num<=pref->precision)
					pref->outputLength=num;
				else return NULL;
			}
#ifndef CONSOLE
			else if(strncmp(configString,"gl",2)==0)
				pref->scriptGraphicsMode=SCRIPT3D;
			else if(strncmp(configString,"graphics",8)==0)
				pref->scriptGraphicsMode=SCRIPT2D;
			else if(strncmp(configString,"rasteron",8)==0)
				pref->raster=true;
			else if(strncmp(configString,"rasteroff",9)==0)
				pref->raster=false;
			else if(strncmp(configString,"labelson",8)==0)
				pref->label=true;
			else if(strncmp(configString,"labelsoff",9)==0)
				pref->label=false;
			else if(strncmp(configString,"axeson",6)==0)
				pref->axis=true;
			else if(strncmp(configString,"axesoff",7)==0)
				pref->axis=false;
			else if(strncmp(configString,"autoscaleon",11)==0)
				pref->autosize=true;
			else if(strncmp(configString,"autoscaleoff",12)==0)
				pref->autosize=false;
#endif
			else return NULL;
			
			memmove(&code[startPos],&code[endPos],len-endPos+1);
			len=strlen(code);
			free(configString);
			pos=startPos;
		}
		pos++;
	}
	
	if(strlen(code)<=0)
		return NULL;
	
	return code;
}

char* macroPreprocessor(char*code)
{
	int pos=0,startPos=0,endPos=0,len=strlen(code),macroLen=0,replacementLen=0;
	bool quote=false,mQuote=false;
	char*configString=NULL,*macro,*replacement;
	
	
	while(pos<len)
	{
		if(quote)
		{
			if(code[pos]=='\"')
				quote=false;
		}
		else if(code[pos]=='\"')
			quote=true;
		else if(code[pos]=='#')
		{
			startPos=pos;
			int configStartPos=startPos;
			endPos=pos;
			
			if(strncmp(&code[startPos],"#define",7)==0)
				configStartPos+=7;
			else return NULL;
			
			while(code[endPos]!='\n' && endPos<=len)
				endPos++;
			
			while((code[configStartPos]==' ' || code[configStartPos]=='\t') && configStartPos<=len)
				configStartPos++;
			
			configString=(char*)malloc(endPos-configStartPos+1);
			strcopy(configString,&code[configStartPos],endPos-configStartPos);
			

			memmove(&code[startPos],&code[endPos],len-endPos+1);
			len=strlen(code);
			pos=startPos;
			
			startPos=endPos=0;
			while(configString[endPos]!=' ' && configString[endPos]!='\t' && endPos<=(signed)strlen(configString))
				endPos++;
			
			macro=(char*)malloc(endPos-startPos+1);
			memcpy(macro,configString,endPos-startPos);
			macro[endPos-startPos]=(char)0;
			macroLen=strlen(macro);
			
			startPos=endPos;
			while((configString[startPos]==' ' || configString[startPos]=='\t') && startPos<=(signed)strlen(configString))
				startPos++;
			endPos=strlen(configString);
			
			if(endPos<=startPos)
				return NULL;
			
			replacement=(char*)malloc(endPos-startPos+1);
			memcpy(replacement,&configString[startPos],endPos-startPos);
			replacement[endPos-startPos]=(char)0;
			replacementLen=strlen(replacement);
			
			
			if(!((macro[0]>='a' && macro[0]<='z') ||
						  (macro[0]>='A' && macro[0]<='Z') ||
						  macro[0]=='_'))
				return NULL;
			for(int c=1; c<macroLen; c++)
			{
				if(!((macro[c]>='a' && macro[c]<='z') ||
								 (macro[c]>='A' && macro[c]<='Z') ||
								 (macro[c]>='0' && macro[c]<='9') ||
								 macro[c]=='_'))
					return NULL;
			}
			
			if(strlen(macro)>0 && strlen(replacement)>0)
			{
				mQuote=false;
				for(int c=0; c<len; c++)
				{

					if(code[c]=='\"')
						mQuote=!mQuote;
					
					else if(!mQuote && strncmp(&code[c],macro,macroLen)==0)
					{
						if(c>0 && !((code[c-1]>='a' && code[c-1]<='z') ||
						            (code[c-1]>='A' && code[c-1]<='Z') ||
									code[c-1]=='_')
							   && !((code[c+macroLen]>='a' && code[c+macroLen]<='z') ||
									(code[c+macroLen]>='A' && code[c+macroLen]<='Z') ||
									(code[c+macroLen]>='0' && code[c+macroLen]<='9') ||
									code[c+macroLen]=='_')
						  )
						{
							//code=(char*)realloc(code,len+replacementLen-macroLen);
							//memmove(&code[c+replacementLen],&code[c+macroLen],len-c-macroLen+1);
							//memcpy(&code[c],replacement,replacementLen);
							code=strreplace(code,c,macroLen,replacement);
							len=strlen(code);
						}
					}
				}
			}
			free(configString);
			free(macro);
			free(replacement);
		}
		pos++;
	}
	
	if(strlen(code)<=0)
		return NULL;
	
	return code;
	
}

char* cleanString(char*code,Preferences*pref)
{
	unsigned int len=strlen(code);
	bool quote=false;

	for(unsigned int c=0; c<len; c++)
	{
		if(len<=0)
			return NULL;
		
		if(quote)
		{
			if(code[c]=='\"')
				quote=false;
			else
			{
				if(code[c]=='\\')
				{
					switch(code[c+1])
					{
						case 'n':
							code[c]='\n';
							break;
						case 't':
							code[c]='\t';
							break;
						case 'a':
							code[c]='\a';
							break;
						case 'b':
							code[c]='\b';
							break;
						case 'v':
							code[c]='\v';
							break;
						case 'f':
							code[c]='\f';
							break;
						case 'r':
							code[c]='\r';
							break;
						case '\\':
							code[c]='\\';
							break;
						default:
							return NULL;
					}
					memmove(&code[c+1],&code[c+2],len-c-1);
					c--;
				}
			}
		}
		else
		{
			if(code[c]=='\"')
				quote=true;
			else
			{
				if(code[c]==' ' || code[c]=='\t' || code[c]=='\n' || code[c]=='\a' ||
				  code[c]=='\r' || code[c]=='\f' || code[c]=='\v' || code[c]=='\b')
				{
					memmove(&code[c],&code[c+1],len-c);
					c--;
				}
				else if(code[c]=='\\')
				{
					if(code[c+1]=='\n')
						memmove(&code[c],&code[c+2],len-c-1);
					else return NULL;
					c--;
				}
			}
		}
		len=strlen(code);
	}
	
	quote=false;
	for(unsigned int c=0; c<len; c++)
	{
		if(len <= 0)
			return NULL;
		if(code[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(strncmp(&code[c],"root",4) == 0)
			code=strreplace(code,c,4,"$r");
		else if(strncmp(&code[c],"sprod",5) == 0)
			code=strreplace(code,c,5,"$s");
		else if(strncmp(&code[c],"ans",3) == 0)
			code=strreplace(code,c,3,"$A");
		else if(strncmp(&code[c],"pi",2) == 0)
		{
			code=strreplace(code,c,2,"()");
			code=strinsert(code,c+1,SPI);
		}
		else if(strncmp(&code[c],"eu",2) == 0)
		{
			code=strreplace(code,c,2,"()");
			code=strinsert(code,c+1,SEULER);
		}
		else if(strncmp(&code[c],"exp",3) == 0)
		{
			code=strreplace(code,c,3,"()^");
			code=strinsert(code,c+1,SEULER);
		}
		else if(strncmp(&code[c],"d/dx",4) == 0)
			code=strreplace(code,c,4,"\\d");
		else if(strncmp(&code[c],"integ",5) == 0)
			code=strreplace(code,c,5,"\\i");
		else if(strncmp(&code[c],"bin",3) == 0)
			code=strreplace(code,c,3,"\\b");
		else if(strncmp(&code[c],"oct",3) == 0)
			code=strreplace(code,c,3,"\\o");
		else if(strncmp(&code[c],"dec",3) == 0)
			code=strreplace(code,c,3,"\\c");
		else if(strncmp(&code[c],"hex",3) == 0)
			code=strreplace(code,c,3,"\\h");
		else if(strncmp(&code[c],"--",2) == 0 || strncmp(&code[c],"++",2) == 0)
		{
			code=strreplace(code,c,2,"+");
			c--;
		}
		else if(strncmp(&code[c],"+-",2) == 0 || strncmp(&code[c],"-+",2) == 0)
		{
			code=strreplace(code,c,2,"-");
			c--;
		}
		else if(code[c] == 'x' && pref->calcType!=BASE)
			code[c]='X';
		else if(code[c] == 'z' && pref->calcType!=BASE)
			code[c]='Z';

		else if(code[c] == (char)0xb2 && c>0 && code[c-1] == (char)0xc2)	// second power
			code=strreplace(code,c-1,2,"^2");
		else if(code[c] == (char)0xb3 && c>0 && code[c-1] == (char)0xc2)	// second power
			code=strreplace(code,c-1,2,"^3");

		else if(!(code[c+1]>='a' && code[c+1]<='z') && c>0 && code[c-1]>='0' && code[c-1]<='9')
		{
			if(code[c] == 'f')
				code=strreplace(code,c,1,"e-15");
			else if(code[c] == 'n')
				code=strreplace(code,c,1,"e-9");
			else if(code[c] == 'p')
				code=strreplace(code,c,1,"e-12");
			else if(code[c] == (char)0xb5 && c>0 && code[c-1] == (char)0xc2)	//micro
				code=strreplace(code,c-1,2,"e-6");
			else if(code[c] == 'm')
				code=strreplace(code,c,1,"e-3");
			else if(code[c] == 'k')
				code=strreplace(code,c,1,"e3");
		}
		len=strlen(code);
	}
	
	quote=false;
	for(unsigned int c=0; c<len-1; c++)
	{
		if(len<=0)
			return NULL;
		
		if(quote)
		{
			if(code[c]=='\"')
				quote=false;
		}
		else 
		{
			if(code[c]=='\"')
				quote=true;
//left side
// variable:
// (code[c]>='A' && code[c]<='F' && pref->calcType!=BASE) || code[c]>='G' && code[c]<='Z' || code[c]==']'
// bracket:
// code[c]==')'
// number:
//(code[c]>='0' && code[c]<='9' || code[c]=='.' || code[c]==')')
			
//right side
// variable:
// code[c+1]>='A' && code[c+1]<='F' && pref->calcType!=BASE || code[c+1]>='G' && code[c+1]<='Z' || (code[c+1]=='$' && code[c+2]=='A')
// bracket:
// code[c+1]=='('
// number:
//code[c+1]>='0' && code[c+1] <='9' || code[c+1]=='.'
// unary operator
// code[c+1]>='a' && code[c+1] <='z' && code[c+1]!='e' || (code[c+1]=='$' && code[c+1]=='A') || code[c+1]=='\\'
			
			else if(
					((code[c]>='A' && code[c]<='F' && pref->calcType!=BASE) || code[c]>='G' && code[c]<='Z' || code[c]==']' ||
					(code[c]>='0' && code[c]<='9') || code[c]=='.') &&
					(code[c+1]>='A' && code[c+1]<='F' && pref->calcType!=BASE || code[c+1]>='G' && code[c+1]<='Z'||
					(code[c+1]=='$' && code[c+2]=='A') ||
					code[c+1]=='(' ||
					code[c+1]>='a' && code[c+1] <='z' && code[c+1]!='e' || code[c+1]=='\\')
					||
					((code[c]>='A' && code[c]<='F' && pref->calcType!=BASE) || code[c]>='G' && code[c]<='Z' || code[c]==']') &&
					(code[c+1]>='0' && code[c+1] <='9' || code[c+1]=='.' ||
					code[c+1]>='A' && code[c+1]<='F' && pref->calcType!=BASE || code[c+1]>='G' && code[c+1]<='Z'||
					(code[c+1]=='$' && code[c+2]=='A') ||
					code[c+1]=='(')
				   )
			{
				code=strinsert(code,c+1,"*");
			}
		}
		len=strlen(code);

	}

	return code;
}

int bracketFind(char* string,char* searchString, int start,int end)
{

	int searchLen=strlen(searchString);
	int bracket=0,brace=0,sqbracket=0;
	bool quote=false;
	if(end==-1)
		end=(int)strlen(string);
	for(int c=start; c<end; c++)
	{
		if(bracket == 0 && brace == 0  && sqbracket==0 && !quote)
		{
			if(strncmp(&string[c],searchString,searchLen) == 0)
				return c;
			else if(string[c] == '(')
				bracket++;
			else if(string[c] == '{')
				brace++;
			else if(string[c] == '[')
				sqbracket++;
			else if(string[c] == '\"')
				quote=true;
		}
		else {
			if(!quote)
			{
				if(string[c] == '(')
					bracket++;
				else if(string[c] == ')')
				{
					bracket--;
					if(bracket == 0 && brace == 0 && sqbracket==0)
					{
						if(strncmp(&string[c],searchString,searchLen) == 0)
							return c;
					}
				}
				else if(string[c] == '{')
					brace++;
				else if(string[c] == '}')
				{
					brace--;
					if(bracket == 0 && brace == 0 && sqbracket==0)
					{
						if(strncmp(&string[c],searchString,searchLen) == 0)
							return c;
					}
				}
				if(string[c] == '[')
					sqbracket++;
				else if(string[c] == ']')
				{
					sqbracket--;
					if(bracket == 0 && brace == 0 && sqbracket==0)
					{
						if(strncmp(&string[c],searchString,searchLen) == 0)
							return c;
					}
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
			else if(string[c] == '\"')
				quote=!quote;
		}
	}
	
	return -1;
}


int bracketFindRev(char* string,char* searchString, int start, int end)
{
	if(start==-1)
		start=strlen(string)-1;

	int searchLen=strlen(searchString);
	int bracket=0,brace=0,sqbracket=0;
	bool quote=false;
	end+=searchLen-1;
	for(int c=start; c>=end; c--)
	{

		if(bracket == 0 && brace == 0 && sqbracket==0 && !quote)
		{
			if(strncmp(&string[c-searchLen+1],searchString,searchLen) == 0)
				return c;
			else if(string[c] == ')')
				bracket++;
			else if(string[c] == '}')
				brace++;
			else if(string[c] == ']')
				sqbracket++;
			else if(string[c] == '\"')
				quote=true;
		}
		else {
			if(!quote)
			{
				if(string[c] == ')')
					bracket++;
				else if(string[c] == '}')
					brace++;
				else if(string[c] == '(')
				{
					bracket--;
					if(bracket == 0 && brace == 0 && sqbracket==0 && !quote)
						if(strncmp(&string[c-searchLen+1],searchString,searchLen) == 0)
							return c;
				}
				else if(string[c] == '[')
				{
					sqbracket--;
					if(bracket == 0 && brace == 0 && sqbracket==0 && !quote)
						if(strncmp(&string[c-searchLen+1],searchString,searchLen) == 0)
							return c;
				}
				if(string[c] == ']')
					sqbracket++;
				else if(string[c] == '{')
				{
					brace--;
					if(bracket == 0 && brace == 0 && sqbracket==0 && !quote)
						if(strncmp(&string[c-searchLen+1],searchString,searchLen) == 0)
							return c;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
			else if(string[c] == '\"')
				quote=!quote;
		}
	}
	
	return -1;
}



char*strcut(char*src,int index,int len)
{
	int srclen=strlen(src);
	char*ret=new char[srclen-len+1];
	if(index>0)
		memcpy(ret,src,index);
	memcpy(&ret[index],&src[index+len],srclen-len-index+1);
	return ret;
}

char*strins(char*dest,const char*src,int index)
{
	int destlen=strlen(dest);
	int srclen=strlen(src);
	char*ret=new char[srclen+destlen+1];
	if(index>0)
		memcpy(ret,dest,index);
	memcpy(&ret[index],src,srclen);
	memcpy(&ret[index+srclen],&dest[index],destlen-index+1);
	return ret;
}

int strcopy(char*dest,char*src,int len)
{
	memcpy(dest,src,len);
	dest[len]=(char)0;
	return 0;
}

char* strreplace(char*st,int index,int len,char*rep)
{
	
	int replen=strlen(rep),stlen=strlen(st);

	if(len<replen)
	{
		char*tmp=(char*)malloc(stlen-index-len+1);
		memcpy(tmp,&st[index+len],stlen-index-len+1);
		st=(char*)realloc(st,stlen+replen-len+1);
		memcpy(&st[index+replen],tmp,stlen-index-len+1);
		free(tmp);
	}
	else
	{
		memmove(&st[index+replen],&st[index+len],stlen-index-len+1);
	}
	
	memcpy(&st[index],rep,replen);

	return st;
}
char* strinsert(char*st,int index,char*ins)
{
	
	unsigned int inslen=strlen(ins),stlen=strlen(st);
	char*tmp=(char*)malloc(stlen-index+1);
	memcpy(tmp,&st[index],stlen-index+1);
	st=(char*)realloc(st,stlen+inslen+1);
	memcpy(&st[index+inslen],tmp,stlen-index+1);
	memcpy(&st[index],ins,inslen);
	free(tmp);
	return st;
}


char* checkStringAnsi(char* str,Preferences*pref)
{
	char* calcString=new char[strlen(str)+1];
	char*tmp;
	memcpy(calcString,str,strlen(str)+1);
	int calcLen=strlen(calcString);
	bool quote=false;

	for(int c=0; c<calcLen; c++)	//Step 1: remove whitespace, correct strings
	{
		if(calcLen <= 0)
			return NULL;
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
		{
			if(calcString[c]=='\\')
			{
				if(calcString[c+1]=='n')
					calcString[c]='\n';
				else if(calcString[c+1]=='t')
					calcString[c]='\t';
				else if(calcString[c+1]=='a')
					calcString[c]='\a';
				else if(calcString[c+1]=='b')
					calcString[c]='\b';
				else if(calcString[c+1]=='v')
					calcString[c]='\v';
				else if(calcString[c+1]=='f')
					calcString[c]='\f';
				else if(calcString[c+1]=='r')
					calcString[c]='\r';
				else if(calcString[c+1]=='\\')
					calcString[c]='\\';
				
				if((signed)strlen(calcString)>c+1)
				{
					tmp=calcString;
					calcString=strcut(calcString,c+1);
					delete[]tmp;
				}
			}
			continue;
		}
		if(calcString[c]=='/' && calcString[c+1]=='/')
		{
			int pos=-1;
			for(int c1=c+1; c1<calcLen; c1++)
				if(calcString[c1]=='\n')
				{
					pos=c1;
					break;
				}
			if(pos==-1)
				return NULL;
			else {
				tmp=calcString;
				calcString=strcut(calcString,c,pos-c);
				delete[]tmp;
			}
		}
		if(calcString[c] == ' ' || calcString[c] == '\t' || calcString[c] == '\n')
		{
			tmp=calcString;
			calcString=strcut(calcString,c);
			delete[]tmp;
			c--;
		}
		if(calcString[c] == '\\')//reserved character
		{
			return NULL;
		}
		calcLen=strlen(calcString);
	}
	quote=false;
	for(int c=0; c<calcLen; c++)	//Step 2: replace special functions
	{
		if(calcLen <= 0)
			return NULL;
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(strncmp(&calcString[c],"root",4) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,4);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"$r",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"sprod",5) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,5);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"$s",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"d/dx",4) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,4);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"\\d",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"integ",5) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,5);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"\\i",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"bin",3) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,3);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"\\b",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"oct",3) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,3);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"\\o",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"dec",3) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,3);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"\\c",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"hex",3) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,3);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"\\h",c);
			delete[]tmp;
		}
		
		if(calcString[c] == 'x' && pref->calcType!=BASE)
			calcString[c]='X';
		
		if(calcString[c] == 'z' && pref->calcType!=BASE)
			calcString[c]='Z';

		if(calcString[c] == '-' && calcString[c+1] == '-' )
		{
			calcString[c]='+';
			tmp=calcString;
			calcString=strcut(calcString,c+1);
			c--;
			delete[]tmp;
			continue;
		}
		if(calcString[c] == (char)0xb2)	// second power
		{
			tmp=calcString;
			calcString=strcut(calcString,c,1);
			delete[]tmp;
			if(c>0)
				if(calcString[c-1] == (char)0xc2)
				{
					tmp=calcString;
					calcString=strcut(calcString,c-1,1);
					delete[]tmp;
					c--;
				}
			tmp=calcString;
			calcString=strins(calcString,"^2",c);
			delete[]tmp;

		}
		if(calcString[c] == (char)0xb3)	// third power
		{
			tmp=calcString;
			calcString=strcut(calcString,c,1);
			delete[]tmp;
			if(c>0)
				if(calcString[c-1] == (char)0xc2)
				{
					tmp=calcString;
					calcString=strcut(calcString,c-1,1);
					delete[]tmp;
					c--;
				}
			tmp=calcString;
			calcString=strins(calcString,"^3",c);
			delete[]tmp;
		}
		if(c>0 && !(calcString[c+1]>='a' && calcString[c+1]<='z'))
		{
			if(calcString[c-1]>='0' && calcString[c-1]<='9')
			{
				if(calcString[c] == 'f')
				{
					tmp=calcString;
					calcString=strcut(calcString,c);
					delete[]tmp;
					tmp=calcString;
					calcString=strins(calcString,"e-15",c);
					delete[]tmp;
				}
				if(calcString[c+1] == 'n')
				{
					tmp=calcString;
					calcString=strcut(calcString,c+1);
					delete[]tmp;
					tmp=calcString;
					calcString=strins(calcString,"e-9",c+1);
					delete[]tmp;
				}
				if(calcString[c] == 'p')
				{
					tmp=calcString;
					calcString=strcut(calcString,c);
					delete[]tmp;
					tmp=calcString;
					calcString=strins(calcString,"e-12",c);
					delete[]tmp;
				}
				if(calcString[c] == (char)0xb5)	//micro
				{
					tmp=calcString;
					calcString=strcut(calcString,c);
					delete[]tmp;
					if(c>0)
						if(calcString[c-1] == (char)0xc2)
					{
						tmp=calcString;
						calcString=strcut(calcString,c-1,1);
						delete[]tmp;
						c--;
					}
					tmp=calcString;
					calcString=strins(calcString,"e-6",c);
					delete[]tmp;
				}
				if(calcString[c] == 'm')
				{
					tmp=calcString;
					calcString=strcut(calcString,c);
					delete[]tmp;
					tmp=calcString;
					calcString=strins(calcString,"e-3",c);
					delete[]tmp;
				}
				if(calcString[c] == 'k')
				{
					tmp=calcString;
					calcString=strcut(calcString,c);
					delete[]tmp;
					tmp=calcString;
					calcString=strins(calcString,"e3",c);
					delete[]tmp;
				}
			}
		}
		if((calcString[c] == '+' || calcString[c] == '-' || 
				  calcString[c] == '*' || calcString[c] == '/' || 
				  calcString[c] == '^'
		   ) && calcString[c+1] == '+')
		{
			tmp=calcString;
			calcString=strcut(calcString,c+1);
			delete[]tmp;
			c--;
			continue;
		}
		else if((calcString[c+1] == '+' || calcString[c+1] == '-') && calcString[c] == '+')
		{
			tmp=calcString;
			calcString=strcut(calcString,c);
			delete[]tmp;
			c--;
			continue;
		}
		calcLen=strlen(calcString);
	}
	
	quote=false;
	for(int c=1; c<calcLen; c++)		//Step 3: insert not written *-signs
	{
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(
				 ( calcString[c]=='\\' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c] >= 'A' || calcString[c]>='G') && calcString[c]<='Z') ||
				 (calcString[c] >= 'a' && calcString[c]<='z' &&(calcString[c]!='e' ||calcString[c+1]=='u') && calcString[c]!='x'))
				 && 
				 ( //calcString[c-1] == '!' ||
				 calcString[c-1] == '.' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z') || 
				 (calcString[c-1] >= '0' && calcString[c-1]<='9'))
		  )
		{
			tmp=calcString;
			calcString=strins(calcString,"*",c);
			delete[]tmp;
		}


		if(
				 (calcString[c] == '.' ||
				 (calcString[c] >= '0' && calcString[c] <= '9'))
				 &&
				 (//calcString[c-1] == '!' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z'))
		  )
		{
			tmp=calcString;
			calcString=strins(calcString,"*",c);
			delete[]tmp;
		}
		
		calcLen=strlen(calcString);
	}
	quote=false;
	for(int c=0; c<calcLen-1; c++)		//Step 4: replace constants
	{
		if(calcLen <= 0)
			return NULL;
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(strncmp(&calcString[c],"ans",3) == 0)
		{
/*			tmp=calcString;
			calcString=strcut(calcString,c,3);
			delete[]tmp;
			char*lastRes=new char[60];
			if(pref->calcType == SCIENTIFIC)
			{
				sprintf(lastRes,"%'.40Lg",vars[26][0]);
				tmp=calcString;
				calcString=strins(calcString,"()",c);
				delete[]tmp;
				tmp=calcString;
				calcString=strins(calcString,lastRes,c+1);
				delete[]tmp;
			}
			else {
				sprintf(lastRes,"\\c%lli",(long long)vars[26][0]);
				tmp=calcString;
				calcString=strins(calcString,"()",c);
				delete[]tmp;
				tmp=calcString;
				calcString=strins(calcString,lastRes,c+1);
				delete[]tmp;
			}
			
			delete[]lastRes;
			*/
			tmp=calcString;
			calcString=strcut(calcString,c,3);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"$A",c);
			delete[]tmp;
		}
		if(strncmp(&calcString[c],"pi",2) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,2);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"()",c);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,SPI,c+1);
			delete[]tmp;
			c+=strlen(SPI)-2;
		}
		if(strncmp(&calcString[c],"eu",2) == 0)
		{
			tmp=calcString;
			calcString=strcut(calcString,c,2);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,"()",c);
			delete[]tmp;
			tmp=calcString;
			calcString=strins(calcString,SEULER,c+1);
			delete[]tmp;
			c+=strlen(SEULER)-2;
		}
		calcLen=strlen(calcString);
	}
	quote=false;
	for(int c=1; c<calcLen; c++)		//Step 5: insert not written *-signs
	{
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(
				 (calcString[c]=='\\' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c] >= 'A' || calcString[c]>='G') && calcString[c]<='Z') ||
				 (calcString[c] >= 'a' && calcString[c]<='z' && calcString[c]!='e' && calcString[c]!='x'))
				 && 
				 (//calcString[c-1] == '!' ||
				 calcString[c-1] == '.' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z') || 
				 (calcString[c-1] >= '0' && calcString[c-1]<='9'))
		  )
		{
			tmp=calcString;
			calcString=strins(calcString,"*",c);
			delete[]tmp;
		}


		if(
				 (calcString[c] == '.' ||
				 (calcString[c] >= '0' && calcString[c] <= '9'))
				 &&
				 (//calcString[c-1] == '!' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z') || calcString[c-1]=='i')
		  )
		{
			tmp=calcString;
			calcString=strins(calcString,"*",c);
			delete[]tmp;
		}
		
		calcLen=strlen(calcString);
	}
	return calcString;
}



void convertToFloat(Number*num)
{
	switch(num->type)
	{
		case NINT:
			num->fval=Complex((long double)num->ival); break;
		case NFLOAT:
			break;
		case NBOOL:
			num->fval=Complex((long double)num->bval); break;
		default:
			num->fval=Complex(NAN);
	}
	num->type=NFLOAT;
	
}

void convertToInt(Number*num)
{
	switch(num->type)
	{
		case NINT:
			break;
		case NFLOAT:
			num->ival=(long long)num->fval.real();break;
		case NBOOL:
			num->ival=(long long)num->bval; break;
		case NCHAR:
			if(num->cval==NULL) 
				num->ival=0;
			else num->ival=(long long)num->cval[0]; break;
		default:
			num->ival=0;
	}
	num->type=NINT;
}

void convertToBool(Number*num)
{
	switch(num->type)
	{
		case NBOOL:
			break;
		case NINT:
			num->bval=num->ival!=0; break;
			break;
		case NFLOAT:
			num->bval=num->fval.real()!=0.0; break;
		case NCHAR:
			if(num->cval==NULL) 
				num->bval=false;
			else num->bval=(long long)num->cval[0]!=0; break;
		default:
			num->bval=false;
	}
	num->type=NBOOL;
	
}



int Calculate::split(char* line, int start, int end)
{
	int pos;
	operation=NONE;
	number=NAN;
	var=-1;
	horzObj=NULL;
	vertObj=NULL;
	
	if(line==NULL)
		return -1;

	int len=strlen(line);
	if(len <=0 || start>=end)
		return -1;


	if((pos=bracketFind(line," ",start,end)) != -1)	//none operation
	{
		horzObj=new Calculate(this,line,0,pos,pref,vars);
		vertObj=new Calculate(this,line,pos+1,end,pref,vars);
		return 0;
	}
	else if(bracketFindRev(line,"+",end-1,start) != -1 || bracketFindRev(line,"-",end-1,start) != -1)
	{
		int pos1,pos2,pos=end-1;
		while(true)
		{
			pos1=bracketFindRev(line,"+",pos,start);
			if(pos1<=start)
				break;
			if(line[pos1-1]=='e')
				pos=pos1-1;
			else break;
		}
		pos=end-1;
		while(true)
		{
			pos2=bracketFindRev(line,"-",pos,start);
			if(pos2<=start)
				break;
			if(line[pos2-1]=='e')
				pos=pos2-1;
			else break;
		}
		
		if(pos2>pos1)
		{
			if(pos2>start && (line[pos2-1] >='A' && line[pos2-1]<='Z'					//binary - operator
			   || line[pos2-1]>='0' && line[pos2-1]<='9'
			   || line[pos2-1]=='.' || line[pos2-1]==')'|| line[pos2-1]==']'))
			{
				pos=pos2;
				operation=MINUS;
				horzObj=new Calculate(this,line,pos+1,end,pref,vars);
				vertObj=new Calculate(this,line,start,pos,pref,vars);
				return 0;
			}
			else if(pos2==start)										//unary - operator
			{
				operation=MINUS;
				horzObj=new Calculate(this,line,start+1,end,pref,vars);
				return 0;
			}
		}
		else if(pos1>pos2)
		{
			if(pos1>start && (line[pos1-1] >='A' && line[pos1-1]<='Z'					//binary + operator
						 || line[pos1-1]>='0' && line[pos1-1]<='9'
						 || line[pos1-1]=='.' || line[pos1-1]==')' || line[pos1-1]==']'))
			{
				pos=pos1;
				operation=PLUS;
				horzObj=new Calculate(this,line,pos+1,end,pref,vars);
				vertObj=new Calculate(this,line,start,pos,pref,vars);
				return 0;
			}
			else if(pos1==start)										//unary + operator
			{
				operation=PLUS;
				horzObj=new Calculate(this,line,start+1,end,pref,vars);
				return 0;
			}
		}
	}
	if(bracketFind(line,"*",start,end) != -1 || bracketFind(line,"/",start,end) != -1)
	{
		int pos1=bracketFindRev(line,"*",end-1,start);
		int pos2=bracketFindRev(line,"/",end-1,start);
		if((pos2>pos1 && pos2 != -1) || pos1==-1)
		{
			pos=pos2;
			operation=DIVIDE;
			horzObj=new Calculate(this,line,pos+1,end,pref,vars);
			vertObj=new Calculate(this,line,start,pos,pref,vars);
			return 0;
		}
		else
		{
			pos=pos1;
			operation=MULT;
			horzObj=new Calculate(this,line,pos+1,end,pref,vars);
			vertObj=new Calculate(this,line,start,pos,pref,vars);
			return 0;
		}
	}
  else if((pos=bracketFind(line,"%",start,end)) != -1)
	{
		operation=MODULO;
		vertObj=new Calculate(this,line,start,pos,pref,vars);
		horzObj=new Calculate(this,line,pos+1,end,pref,vars);
		return 0;
		
		
	}
	else if((pos=bracketFindRev(line,"^",end-1,start)) != -1)
	{
		operation=POW;
		vertObj=new Calculate(this,line,start,pos,pref,vars);
		horzObj=new Calculate(this,line,pos+1,end,pref,vars);
		return 0;
	}
	else if((pos=bracketFind(line,"$r",end-1,start)) != -1)	//	root operation for extcalc (binary operator)
	{
		operation=ROOT;
		vertObj=new Calculate(this,line,start,pos,pref,vars);
		horzObj=new Calculate(this,line,pos+2,end,pref,vars);
		return 0;
	}
	else if(line[start]>='a' && line[start]<='z') 
	{
		if(pref->angle==DEG)
			number=180.0/(long double)PI;
		else if(pref->angle==RAD)
			number=1.0;
		else number=200.0/(long double)PI;
		if(strncmp("asinh",line+start,5) == 0)
		{
			operation=ASINH;
			vertObj=new Calculate(this,line,start+5,end,pref,vars);
		}
		else if(strncmp("acosh",line+start,5) == 0)
		{
			operation=ACOSH;
			vertObj=new Calculate(this,line,start+5,end,pref,vars);
		}
			else if(strncmp("atanh",line+start,5) == 0)
		{
			operation=ATANH;
			vertObj=new Calculate(this,line,start+5,end,pref,vars);
		}
		else if(strncmp("asin",line+start,4) == 0)
		{
			operation=ASIN;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp("acos",line+start,4) == 0)
		{
			operation=ACOS;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp("atan",line+start,4) == 0)
		{
			operation=ATAN;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp("sinh",line+start,4) == 0)
		{
			operation=SINH;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp("cosh",line+start,4) == 0)
		{
			operation=COSH;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp("tanh",line+start,4) == 0)
		{
			operation=TANH;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp("sin",line+start,3) == 0)
		{
			operation=SIN;
			vertObj=new Calculate(this,line,start+3,end,pref,vars);
		}
		else if(strncmp("cos",line+start,3) == 0)
		{
			operation=COS;
			vertObj=new Calculate(this,line,start+3,end,pref,vars);
		}
		else if(strncmp("tan",line+start,3) == 0)
		{
			operation=TAN;
			vertObj=new Calculate(this,line,start+3,end,pref,vars);
		}
		else if(strncmp("log",line+start,3) == 0)
		{
			operation=LG;
			vertObj=new Calculate(this,line,start+3,end,pref,vars);
		}
		else if(strncmp(line+start,"ln",2) == 0)
		{
			operation=LN;
			vertObj=new Calculate(this,line,start+2,end,pref,vars);
		}
		else if(strncmp(line+start,"sqrt",4) == 0)
		{
			operation=SQRT;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp(line+start,"curt",4) == 0)
		{
			operation=CURT;
			vertObj=new Calculate(this,line,start+4,end,pref,vars);
		}
		else if(strncmp(line+start,"abs",3) == 0)
		{
			operation=SABS;
			vertObj=new Calculate(this,line,start+3,end,pref,vars);
		}
		else{
			number=NAN;
			return -1;
		}
		return 0;
	}
	else if(strncmp(line+start,"\\d(",3) == 0)
	{
		pos=bracketFind(line,",",start+3,end);
		if(pos<0 || pos>len-2)
			return -1;
		operation=DIFF;

		horzObj=new Calculate(this,line,start+3,pos,pref,vars);
		vertObj=new Calculate(this,line,pos+1,end-1,pref,vars);
		return 0;
	}
	else if(strncmp(line+start,"\\i(",3) == 0)
	{
		int pos1=bracketFind(line,",",3,end);
		if(pos1==-1)
			return-1;
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos2==-1)
			return -1;
		operation=INTEGRAL;
		
		char *parStr=new char[len-pos1+2];
		strcopy(parStr,&line[pos1+1],pos2-pos1-1);
		parStr[pos2-pos1-1]=' ';
		strcopy(&parStr[pos2-pos1],&line[pos2+1],len-pos2-2);
		horzObj=new Calculate(this,line,start+3,pos1,pref,vars);
		vertObj=new Calculate(this,parStr,0,strlen(parStr),pref,vars);
		delete[]parStr;
		return 0;
	}
	else if(line[start]=='(')
	{
		if(end-start && line[end-1] == ')')
			horzObj=new Calculate(this,line,start+1,end-1,pref,vars);
		else horzObj=new Calculate(this,line,start+1,end,pref,vars);

		return 0;
	}
	else if(line[start]>='A' && line[start]<='Z')
	{
		var=((int)line[start])-65;
		if(end-start>1)
			var=-1;
		return 0;
	}
	else{
		char*tmp=new char[end-start+1];
		tmp[end-start]=(char)0;
		memcpy(tmp,&line[start],end-start);
		number=strtod(tmp,NULL);
		delete[] tmp;
		
		if(number==NAN)
			return -1;
		else return 0;
	}
	return -1;
}




double Calculate::calc()
{
//	perror("calc: "+QString::number(operation));
	switch(operation)
	{
		case NONE:
		{
			if(horzObj != NULL)
			{
				return horzObj->calc();
			}
			else if(vertObj != NULL)
			{
				return vertObj->calc();
			}
			else if(var!=-1)
			{
				return vars[var];
			}
			else 
			{
				return number;
			}
		}
		case PLUS:
		{
			if(vertObj != NULL && horzObj != NULL)
			{
				return vertObj->calc()+horzObj->calc();
			}
			else if(horzObj != NULL)
			{
				return horzObj->calc();
			}
			else {
				return NAN;
			}
		}
		case MINUS:
		{
			if(vertObj != NULL && horzObj != NULL)
			{
				return vertObj->calc()-horzObj->calc();
			}
			else if(horzObj != NULL)
			{
				return (double)-1.0*horzObj->calc();
			}
			else {
				return NAN;
			}
		}
		case MULT:
			return vertObj->calc()*horzObj->calc();
		case DIVIDE:
			return vertObj->calc()/horzObj->calc();
		case POW:
			return pow(vertObj->calc(),horzObj->calc());
		case SQRT:
			return sqrt(vertObj->calc());
		case CURT:
			return cbrt(vertObj->calc());
		case ROOT:
			return pow(horzObj->calc(),1/vertObj->calc());
		case SIN:
			return sin(vertObj->calc()/number);
		case COS:
			return cos(vertObj->calc()/number);
		case TAN:
			return tan(vertObj->calc()/number);
		case LG:
			return log10(vertObj->calc());
		case LN:
			return log(vertObj->calc());
		case SABS:
			return fabsl(vertObj->calc());
		case ASIN:
			return asin(vertObj->calc())*number;
		case ACOS:
			return acos(vertObj->calc())*number;
		case ATAN:
			return atan(vertObj->calc())*number;
		case SINH:
			return sinh(vertObj->calc());
		case COSH:
			return cosh(vertObj->calc());
		case TANH:
			return tanh(vertObj->calc());
		case ASINH:
			return asinh(vertObj->calc());
		case ACOSH:
			return acosh(vertObj->calc());
		case ATANH:
			return atanh(vertObj->calc());
		case DIFF:
		{
			double savedX=vars[23];
			double point;
			if(vertObj!= NULL)
				point=vertObj->calc();
			else return NAN;
			if(horzObj == NULL)
				return NAN;
			double step=(point*1e-6);
			if(step<1e-6)
				step=1e-6;
			vars[23]=point-step;
			double w1=horzObj->calc();
			vars[23]=point+step;
			double w2=horzObj->calc();
			vars[23]=savedX;
			return((w2-w1)/(2*step));
		}
		case MODULO:
			return fmod(vertObj->calc(),horzObj->calc());
		case INTEGRAL:
		{
			double savedX=vars[23];
			double complete=(double)0.0;
			if(vertObj == NULL || horzObj == NULL)
				return NAN;
			double start=vertObj->calcHorzObj();
			double end=vertObj->calcVertObj();
			bool inverse=false;

			if(start > end)
			{
				double zw=end;
				end=start;
				start=zw;
				inverse=true;
			}

			double * line1=new double;
			double *line2=new double[3];
			double y,oldy;
			vars[23]=start;
			oldy=horzObj->calc();
			vars[23]=end;
			y=horzObj->calc();
			line1[0]=(y+oldy)*(end-start)/2.0;
			double fail=1e+308,oldfail=0.0;

			int num=1;
			int steps;
			while(true)
			{
				delete[]line2;
				line2=line1;
				line1=new double[num+1];
				line1[0]=0.0;
				steps=(int)pow(2.0,(double)(num-1));
				for(int c=1; c<=steps; c++)
				{
					vars[23]=start+((2*c-1)*(end-start))/pow(2.0,(double)num);
					line1[0]+=horzObj->calc();
				}
				line1[0]=0.5*(line1[0]*(end-start)/pow(2.0,(double)(num-1))+line2[0]);
			
				for(int c=2; c<=num+1; c++)
					line1[c-1]=(pow(4.0,(double)(c-1))*line1[c-2]-line2[c-2])/(pow(4.0,(double)(c-1))-1);

				num++;
				oldfail=fail;
				fail=line1[num-1]-line2[num-2];
				if(fail < 0.0)
					fail*=-1.0;
				
				if(num>13 || (fail < 1e-7))
				{
					if(num>3)
						break;
				}
				if(fail>oldfail)
				{
					if(num>5)
					{
						line1[num-1]=NAN;
						break;
					}
				}
			}
			complete=line1[num-1];

			vars[23]=savedX;
			if(inverse)
				return -complete;
			else return complete;
		}
	}
	return NAN;
}



double Calculate::calcVertObj()
{
	if(vertObj != NULL)
		return vertObj->calc();
	else return NAN;
}

double Calculate::calcHorzObj()
{
	if(horzObj != NULL)
		return horzObj->calc();
	else return NAN;
}


int Script::split(char*line,int start,int end)
{
	bool init=false;
	int rest;
	if(parent==NULL)
	{
		value.type=NNONE;
		rest=start;
		init=true;
		parse(NULL,0,0);
		operation=SINIT;
	}
	else rest=parse(line,start,end);

	if(rest!=-1)
	{
		horzObj=new Script(this,NULL,0,0,pref,vars,eventReciver);
		horzObj->split(line,rest,end);
	}
	return 0;
}


int Script::parse(char* line,int start,int end)
{

	static int semicolonCount=0;
	if(line==NULL)
	{
		semicolonCount=0;
		return -1;
	}
	if(end<=start)
	{
//		printError("Empty operation",semicolonCount,eventReciver);
		operation=SFAIL;
		return -1;
	}
	

//        QString outLine(line);
//        outLine=outLine.mid(start,end-start);
//        qDebug(outLine);
	
	int pos1;
//	perror(line);

	
	if(line[start]== '{' && bracketFind(line,"}",start,end)==end-1 || line[start]== '(' && bracketFind(line,")",start,end)==end-1)
	{
		split(line,start+1,end-1);
		return -1;
	}
//	static int commands=0;
//	perror("Commands: "+QString::number(commands++));
//	perror("line after bracket: "+QString(line));
	
	//programming language structures
	if(strncmp("if(",line+start,3) == 0)
	{
		int pos2=bracketFind(line,")",start,end);
		if(pos2<start+3)
		{
			printError("No closing bracket for if found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+3,pos2,pref,vars,eventReciver);

		vertObj2=new Script(this,NULL,0,0,pref,vars,eventReciver);
		int rest=vertObj2->parse(line,pos2+1,end);
		if(rest==-1)
		{
			operation=SIF;
			return -1;
		}

		if(strncmp(line+rest,"else",4)==0)
		{
			operation=SIFELSE;
			vertObj3=new Script(this,NULL,pref,vars,eventReciver);
			rest=vertObj3->parse(line,rest+4,end);
		}
		else operation=SIF;

		return rest;
	}
	else if(strncmp(line+start,"while(",6) == 0)
	{
		operation=SWHILE;
		int pos2=bracketFind(line,")",start,end);
		if(pos2<start+7)
		{
			printError("No closing bracket for while found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}

		vertObj=new Script(this,line,start+6,pos2,pref,vars,eventReciver);
		vertObj2=new Script(this,NULL,0,0,pref,vars,eventReciver);
		int rest=vertObj2->parse(line,pos2+1,end);

		return rest;
	}
	else if(strncmp(line+start,"for(",4) == 0)
	{
		operation=SFOR;
		int pos2=bracketFind(line,";",start+4,end);
		int pos3=bracketFind(line,";",pos2+1,end);
		int pos4=bracketFind(line,")",start,end);
		if(pos2<start+4 || pos3<start+5 || pos4<start+6)
		{
			printError("Invalid usage of for",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}

		vertObj=new Script(this,line,start+4,pos2,pref,vars,eventReciver);

		semicolonCount++;
		if(pos3-pos2>1)
			vertObj2=new Script(this,line,pos2+1,pos3,pref,vars,eventReciver);
		else vertObj2=NULL;
		semicolonCount++;


		vertObj3=new Script(this,line,pos3+1,pos4,pref,vars,eventReciver);

		
		if(end-pos4<2)
		{
			printError("For-loop has no body",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}

		vertObj4=new Script(this,NULL,pref,vars,eventReciver);
		return vertObj4->parse(line,pos4+1,end);
	}
	else if(line[start] == '{')
	{
		operation=SBRACKET;
		pos1=bracketFind(line,"}",start,end);
		if(pos1<1)
		{
			printError("No closing bracket for { found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,NULL,pref,vars,eventReciver);
		vertObj->split(line,start+1,pos1);
		if(pos1==end)
			return -1;
		else return pos1+1;
	}
	//operators
	else if((pos1=bracketFind(line,";",start,end)) != -1)
	{
		operation=SSEMICOLON;

		if(pos1>start)
			vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		else vertObj=NULL;
		semicolonCount++;

		if(pos1<end-1)
			return pos1+1;
		else return -1;
	}
	else if((pos1=bracketFind(line,"&&",start,end)) != -1)
	{
		operation=SAND;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+2,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"||",start,end)) != -1)
	{
		operation=SOR;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+2,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"->",start,end)) != -1)
	{
		operation=SSET;
		int pos2=0;
		if(pos1!=end-3)
		{
			if(line[pos1+3]=='[' && line[end-1]==']')
			{
				if((pos2=bracketFindRev(line,"["))!=-1)
				{
					if(line[pos2-1]!=']')
					{
						printError("No closing brace for set operation found",semicolonCount,eventReciver);
						operation=SFAIL;
						return -1;
					}
					vertObj2=new Script(this,line,pos1+4,pos2-1,pref,vars,eventReciver);
					vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
				}
				else vertObj2=new Script(this,line,pos1+4,end-1,pref,vars,eventReciver);
			}
			else {
				printError("Right operand of set operation invalid",semicolonCount,eventReciver);
				operation=SFAIL;
				return -1;
			}
		}

		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);

		var=line[pos1+2]-65;
		if(var<0 || var>25)
		{
			printError("Invalid variable for set operation",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		return -1;
	}
	else if((pos1=bracketFindRev(line,"==",end-1,start)) != -1)
	{
		operation=SCOMPARE;
		vertObj=new Script(this,line,start,pos1-1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,"!=",end-1,start)) != -1)
	{
		operation=SUNEQUAL;
		vertObj=new Script(this,line,start,pos1-1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,">=",end-1,start)) != -1)
	{
		operation=SGREQ;
		vertObj=new Script(this,line,start,pos1-1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,"<=",end-1,start)) != -1)
	{
		operation=SLESSEQ;
		vertObj=new Script(this,line,start,pos1-1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,">",end-1,start)) != -1 && line[pos1+1]!='>')
	{
		operation=SGREATHER;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,"<",end-1,start)) != -1 && line[pos1+1]!='<')
	{
		operation=SLESS;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"=",start,end)) != -1)
	{
		operation=SSET;

		vertObj=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		int pos2=0;
		if(pos1!=start+1)
		{
			if(line[start+1]=='[' && line[pos1-1]==']')
			{
				if((pos2=bracketFind(line,"]",start,end)) !=pos1-1)
				{
					if(line[pos2+1]!='[')
					{
						printError("Closing brace for set operation not found",semicolonCount,eventReciver);
						operation=SFAIL;
						return -1;
					}

					vertObj2=new Script(this,line,start+2,pos2,pref,vars,eventReciver);
					vertObj3=new Script(this,line,pos2+2,pos1-1,pref,vars,eventReciver);
				}
				else vertObj2=new Script(this,line,start+2,pos1-1,pref,vars,eventReciver);
			}
			else {
				printError("Left operand of set operation invalid",semicolonCount,eventReciver);
				operation=SFAIL;
				return -1;
			}
			
		}
		var=line[start]-65;
		if(var<0 || var>25)
		{
			printError("Invalid variable for set operation",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		return -1;
	}
	pos1=start;
	while((pos1=bracketFind(line,"+",pos1,end)) != -1)
	{
		if(pos1>start && line[pos1-1]=='e')
		{
			pos1++;
			continue;
		}
		operation=SFAIL;
		if(pos1<start+1)
		{
			operation=PLUS;
			vertObj=NULL;
		}
		else if(end-pos1<2)
			printError("Second operand of + invalid",semicolonCount,eventReciver);
		else {
			operation=PLUS;
			vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		}
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);

		return -1;
	}
	pos1=end-1;
	while((pos1=bracketFindRev(line,"-",pos1,start)) !=-1)
	{
		if(pos1>start && !(line[pos1-1]>='A' && line[pos1-1]<='Z' || line[pos1-1]>='0' && line[pos1-1]<='9' || line[pos1-1]=='i' || line[pos1-1]==')'||line[pos1-1]==']'|| line[pos1-1]=='!') )
		{
			pos1--;
			continue;
		}
		operation=SFAIL;
		if(pos1<start+1)
		{
			operation=MINUS;
			vertObj=NULL;
		}
		else if(end-pos1<2)
			printError("Second operand of - invalid",semicolonCount,eventReciver);
		else {
			operation=MINUS;
			vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		}
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	if((pos1=bracketFindRev(line,"*",end-1,start)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of * invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of * invalid",semicolonCount,eventReciver);
		else operation=MULT;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,"/",end-1,start)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of / invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of / invalid",semicolonCount,eventReciver);
		else {
			if(pref->complex)
				operation=CDIVIDE;
			else operation=DIVIDE;
		}
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFindRev(line,"$s",end-1,start)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+2)
			printError("First operand of root invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of root invalid",semicolonCount,eventReciver);
		else {
			operation=SCALARPROD;
		}
		vertObj=new Script(this,line,start,pos1-1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}	
	else if((pos1=bracketFind(line,"%",start,end)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of % invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of % invalid",semicolonCount,eventReciver);
		else operation=MODULO;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,">>",start,end)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of >> invalid",semicolonCount,eventReciver);
		else if(end-pos1<3)
			printError("Second operand of >> invalid",semicolonCount,eventReciver);
		else operation=RSHIFT;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+2,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"<<",start,end)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of << invalid",semicolonCount,eventReciver);
		else if(end-pos1<3)
			printError("Second operand of << invalid",semicolonCount,eventReciver);
		else operation=LSHIFT;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+2,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"x",start,end)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of x invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of x invalid",semicolonCount,eventReciver);
		else operation=XOR;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"&",start,end)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of & invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of & invalid",semicolonCount,eventReciver);
		else operation=SBAND;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"|",start,end)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of | invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of | invalid",semicolonCount,eventReciver);
		else operation=SBOR;
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if((pos1=bracketFind(line,"!",start,end))!=-1)
	{
		if(pos1==end-1)
		{
				operation=SFAK;
				vertObj=new Script(this,line,start,end-1,pref,vars,eventReciver);
		}
		else if(pos1==start)
		{
			operation=SNOT;
			vertObj=new Script(this,line,start+1,end,pref,vars,eventReciver);
		}
		else {
				operation=SFAIL;
				printError("Invalid use of !",semicolonCount,eventReciver);
		}
		return -1;
	}
	else if((pos1=bracketFindRev(line,"^",end-1,start)) != -1)
	{
		operation=SFAIL;
		if(pos1<start+1)
			printError("First operand of ^ invalid",semicolonCount,eventReciver);
		else if(end-pos1<2)
			printError("Second operand of ^ invalid",semicolonCount,eventReciver);
		else 
		{
			if(pref->complex)
				operation=CPOW;
			else operation=POW;
		}
		vertObj=new Script(this,line,start,pos1,pref,vars,eventReciver);
		if(strncmp(line+pos1+1,"-1",2)!=0)
			vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		else operation=INVERT;
		return -1;
	}
	else if((pos1=bracketFindRev(line,"$r",end-1,start)) != -1)
	{
		operation=SFAIL;
		if(pos1<1)
			printError("First operand of root invalid",semicolonCount,eventReciver);
		else if(end-pos1<3)
			printError("Second operand of root invalid",semicolonCount,eventReciver);
		else {
			if(pref->complex)
				operation=CROOT;
			else operation=ROOT;
		}
		vertObj=new Script(this,line,start,pos1-1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end,pref,vars,eventReciver);
		return -1;
	}

	else if(strncmp(line+start,"print(",6) == 0)
	{
		operation=SPRINT;
		if(bracketFind(line,")",start,end)!=end-1)
		{
			printError("Closing bracket for print not found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+6,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"clear",5) == 0)
	{
		operation=SCLEARTEXT;
		return -1;
	}
	else if(strncmp(line+start,"setcursor(",10) == 0)
	{
		operation=SSETCURSOR;
		pos1=bracketFind(line,",",start+10,end-1);
		int pos2=bracketFind(line,")",start,end);
		if(pos2!=end-1 || pos1<start+10)
		{
			printError("Invalid use of setcursor",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+10,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"sleep(",6) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SSLEEP;
		if(bracketFind(line,")",start,end)!=end-1)
		{
			printError("No closing bracket for sleep found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+6,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"rnd(",4) == 0)
	{
		operation=SRAND;
		value.type=NFLOAT;
		if(bracketFind(line,")",start,end)!=end-1)
		{
			printError("No closing bracket for rnd found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+4,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"readfile(",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SFREAD;
		if(bracketFind(line,")",start,end)!=end-1)
		{
			printError("Closing bracket for readfile not found",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else vertObj=new Script(this,line,start+9,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"writefile(",10) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SFWRITE;
		pos1=bracketFind(line,",",start+10,end);
		if(pos1<start+10)
		{
			printError("Invalid use of writefile",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+10,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"removefile(",11) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SFREMOVE;
		if(bracketFind(line,")",start,end)<start+11)
		{
			printError("Closing bracket for removefile not found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+11,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"appendfile(",11) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SFAPPEND;
		pos1=bracketFind(line,",",start+11,end);
		if(pos1<start+12)
		{
			printError("Invalid use of appendfile",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+11,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glbegin(",8) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHPAINT;
		if(bracketFind(line,")",start+8,end)<start+8)
		{
			printError("Closing bracket for glbegin not found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		if(strncmp(line+start+8,"points",6)==0)
			value.ival=0;
		else if(strncmp(line+start+8,"linestrip",9)==0)
			value.ival=2;
		else if(strncmp(line+start+8,"lineloop",8)==0)
			value.ival=3;
		else if(strncmp(line+start+8,"lines",5)==0)
			value.ival=1;
		else if(strncmp(line+start+8,"trianglestrip",13)==0)
			value.ival=5;
		else if(strncmp(line+start+8,"trianglefan",11)==0)
			value.ival=6;
		else if(strncmp(line+start+8,"triangles",9)==0)
			value.ival=4;
		else if(strncmp(line+start+8,"quadstrip",9)==0)
			value.ival=8;
		else if(strncmp(line+start+8,"quads",5)==0)
			value.ival=7;
		else if(strncmp(line+start+8,"polygon",7)==0)
			value.ival=9;
		else{
			printError("Invalid argument in glbegin",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		return -1;
	}
	else if(strncmp(line+start,"glendlist",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHLIST;
		var=2;
		return -1;
	}
	else if(strncmp(line+start,"glend",5) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHCONTROL;
		var=2;
		return -1;
	}
	else if(strncmp(line+start,"glshow",6) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHCONTROL;
		var=0;
		return -1;
	}
	else if(strncmp(line+start,"glclear",7) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHCONTROL;
		var=1;
		return -1;
	}
	else if(strncmp(line+start,"glloadidentity",14) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHCONTROL;
		var=3;
		return -1;
	}
	else if(strncmp(line+start,"glstartlist",11) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHLIST;
		var=1;
		return -1;
	}
	else if(strncmp(line+start,"glcalllist(",11) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHLIST;
		var=0;
		if(bracketFind(line,")",start,end)<start+12)
		{
			printError("Closing bracket for glcalllist not found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+11,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glpoint(",8) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHVERTEX;
		pos1=bracketFind(line,",",start+8,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+8 || pos2<start+8)
		{
			printError("Invalid use of glpoint",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+8,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glscale(",8) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHTRANSFORM;
		var=0;
		pos1=bracketFind(line,",",start+8,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+8 || pos2<start+8)
		{
			printError("Invalid use of glscale",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+8,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glmove(",7) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHTRANSFORM;
		var=1;
		pos1=bracketFind(line,",",start+7,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+7 || pos2<start+7)
		{
			printError("Invalid use of glmove",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+7,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glrotate(",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHTRANSFORM;
		var=2;
		pos1=bracketFind(line,",",start+9,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		int pos3=bracketFind(line,",",pos2+1,end);
		if(pos1<start+9 || pos2==start+9 || pos3==start+9)
		{
			printError("Invalid use if glrotate",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj4=new Script(this,line,start+9,pos1,pref,vars,eventReciver);
		vertObj=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos2+1,pos3,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos3+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glcolor(",8) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHCOLOR;
		pos1=bracketFind(line,",",start+8,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+8 || pos2<start+8)
		{
			printError("Invalid use of glcolor",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+8,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"glstring(",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SGRAPHTEXT;
		var=2;
		pos1=bracketFind(line,",",start+9,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+9 || pos2<start+9)
		{
			printError("Invalid use of glstring",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+9,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj4=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"drawclear",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=0;
		return -1;
	}
	else if(strncmp(line+start,"drawpoint(",10) ==0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=1;
		pos1=bracketFind(line,",",start+10,end);
		if(pos1<start+10)
		{
			printError("Invalid use of drawpoint",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+10,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"drawcolor(",10) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=2;
		pos1=bracketFind(line,",",start+10,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+10 || pos2<start+10)
		{
			printError("Invalid use of drawcolor",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+10,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"drawstring(",11) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=3;
		pos1=bracketFind(line,",",start+11,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+11 || pos2<start+11)
		{
			printError("Invalid use of drawstring",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj=new Script(this,line,start+11,pos1,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"drawline(",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=4;
		int pos1=bracketFind(line,",",start+9,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		int pos3=bracketFind(line,",",pos2+1,end);
		if(pos1<start+9 || pos2<start+9 || pos3<start+9)
		{
			printError("Invalid use of drawline",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj4=new Script(this,line,start+9,pos1,pref,vars,eventReciver);
		vertObj=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos2+1,pos3,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos3+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"drawrect(",9) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=5;
		int pos1=bracketFind(line,",",start+9,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		int pos3=bracketFind(line,",",pos2+1,end);
		if(pos1<start+9 || pos2<start+9 || pos3<start+9)
		{
			printError("Invalid use of drawrect",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj4=new Script(this,line,start+9,pos1,pref,vars,eventReciver);
		vertObj=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos2+1,pos3,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos3+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"drawcircle(",11) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SDRAW;
		var=6;
		pos1=bracketFind(line,",",start+11,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		int pos3=bracketFind(line,",",pos2+1,end);
		if(pos1<start+11 || pos2<start+11 || pos3<start+11)
		{
			printError("Invalid use of drawline",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj4=new Script(this,line,start+11,pos1,pref,vars,eventReciver);
		vertObj=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos2+1,pos3,pref,vars,eventReciver);
		vertObj3=new Script(this,line,pos3+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"run(",4) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SRUN;
		
		if(bracketFind(line,")",start,end)!=end-1)
		{
			printError("No closing bracket for run found",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		if(line[end-2]!='\"' || line[start+4]!='\"')
		{
			printError("Filename in run must be quoted",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		var=-1;
		for(int c=0; c<eventReciver->subprogramPath.GetLen(); c++)
			if(strncmp(eventReciver->subprogramPath[c],line+start+5,end-start-7)==0 && (signed)strlen(eventReciver->subprogramPath[c])==end-start-7)
			{
				var=c;
				break;
			}
		if(var==-1)
		{
			printError("File for run does not exist",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		return -1;
	}
	else if(strncmp(line+start,"\\d(",3) == 0)
	{
		operation=DIFF;
		pos1=bracketFind(line,",",start+3,end);
		if(pos1<start+3 || bracketFind(line,")",start,end)!=end-1)
		{
			printError("Invalid use if d/dx",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
                vertObj4=new Script(this,line,start+3,pos1,pref,vars,eventReciver);
		vertObj=new Script(this,line,pos1+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"\\i(",3) == 0)
	{
		operation=INTEGRAL;
		pos1=bracketFind(line,",",start+3,end);
		int pos2=bracketFind(line,",",pos1+1,end);
		if(pos1<start+3 || pos2<start+3)
		{
			printError("Invalid use of integ",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		vertObj4=new Calculate(this,line,start+3,pos1,pref,vars);
		vertObj=new Script(this,line,pos1+1,pos2,pref,vars,eventReciver);
		vertObj2=new Script(this,line,pos2+1,end-1,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(line+start,"getline",7) ==0)
	{
		if(end-start>7)
		{
			printError("Invalid operation after getline",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else operation=SGETLINE;
		value.type=NCHAR;
		return -1;
	}
	else if(strncmp(line+start,"getkey",6) ==0)
	{
		if(end-start>6)
		{
			printError("Invalid operation after getkey",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else operation=SGETKEY;
		value.type=NCHAR;
		value.cval=new char[2];
		value.cval[1]=(char)0;
		return -1;
	}
	else if(strncmp(line+start,"keystate",8) ==0)
	{
		if(end-start>8)
		{
			printError("Invalid operation after keystate",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else operation=SKEYSTATE;
		value.type=NCHAR;
		value.cval=new char[2];
		value.cval[1]=(char)0;
		return -1;
	}
	else if(strncmp(line+start,"break",5) ==0)
	{
		if(end-start>5)
		{
			printError("Invalid operation after break",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else operation=SBREAK;
		return -1;
	}
	else if(strncmp(line+start,"continue",8) == 0)
	{
		if(end-start>8)
		{
			printError("Invalid operation after getkey",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else operation=SCONTINUE;
		return -1;
	}
	else if(strncmp(line+start,"stop",4) ==0)
	{
		if(end-start>4)
		{
			printError("Invalid operation after stop",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		else operation=SSTOP;
		return -1;
	}
	else if(line[start]>='a' && line[start]<='z') 
	{
		if(pref->angle==DEG)
			number=180.0/(long double)PI;
		else if(pref->angle==RAD)
			number=1.0;
		else number=200.0/(long double)PI;
		if(strncmp("asinh",line+start,5) == 0)
		{
			operation=ASINH;
			vertObj=new Script(this,line,start+5,end,pref,vars,eventReciver);
		}
		else if(strncmp("acosh",line+start,5) == 0)
		{
			operation=ACOSH;
			vertObj=new Script(this,line,start+5,end,pref,vars,eventReciver);
		}
		else if(strncmp("atanh",line+start,5) == 0)
		{
			operation=ATANH;
			vertObj=new Script(this,line,start+5,end,pref,vars,eventReciver);
		}
		else if(strncmp("asin",line+start,4) == 0)
		{
			operation=ASIN;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp("acos",line+start,4) == 0)
		{
			operation=ACOS;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp("atan",line+start,4) == 0)
		{
			operation=ATAN;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp("sinh",line+start,4) == 0)
		{
			if(pref->complex)
				operation=CSINH;
			else operation=SINH;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp("cosh",line+start,4) == 0)
		{
			if(pref->complex)
				operation=CCOSH;
			else operation=COSH;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp("tanh",line+start,4) == 0)
		{
			if(pref->complex)
				operation=CTANH;
			else operation=TANH;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp("sin",line+start,3) == 0)
		{
			if(pref->complex)
				operation=CSIN;
			else operation=SIN;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp("cos",line+start,3) == 0)
		{
			if(pref->complex)
				operation=CCOS;
			else operation=COS;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp("tan",line+start,3) == 0)
		{
			if(pref->complex)
				operation=CTAN;
			else operation=TAN;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp("log",line+start,3) == 0)
		{
			if(pref->complex)
				operation=CLG;
			else operation=LG;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp("ln",line+start,2) == 0)
		{
			if(pref->complex)
				operation=CLN;
			else operation=LN;
			vertObj=new Script(this,line,start+2,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"sqrt",4) == 0)
		{
			if(pref->complex)
				operation=CSQRT;
			else operation=SQRT;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"curt",4) == 0)
		{
			if(pref->complex)
			{
				operation=CROOT;
				vertObj=new Script(this,"3",0,1,pref,vars,eventReciver);
				vertObj2=new Script(this,line,start+4,end,pref,vars,eventReciver);
			}
			else 
			{
				operation=CURT;
				vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
			}
		}
		else if(strncmp(line+start,"real",4) == 0)
		{
			operation=SREAL;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"imag",4) == 0)
		{
			operation=SIMAG;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"abs",3) == 0)
		{
			if(pref->complex)
				operation=CABS;
			else operation=SABS;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"arg",3) == 0 && pref->complex)
		{
			operation=SARG;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"conj",4) == 0 && pref->complex)
		{
			operation=SCONJ;
			vertObj=new Script(this,line,start+4,end,pref,vars,eventReciver);
		}
		else if(strncmp(line,"det",3) == 0)
		{
			operation=DETERMINANT;
			vertObj=new Script(this,line,start+3,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"i",1) == 0 && pref->complex)
		{
			operation=SVALUE; 
			value.type=NFLOAT;
			
			if((end-start)==1)
			{
				value.fval=Complex(0.0,1.0);
			}
			else
			{
				char*err,*tmpval;
				tmpval=new char[end-start];
				strcopy(tmpval,&line[start+1],end-start-1);
		
				value.fval=Complex(0.0,strtold(tmpval,&err));
					
				if(*err!=(char)0)
				{
					printError("Invalid number",semicolonCount,eventReciver);
					operation=SFAIL;
				}
				delete[] tmpval;
			}
			return -1;
		}
		else{
			printError("Unknown command",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		return -1;
	}
	else if(bracketFind(line,"~",start,end)==0)
	{
		if(end-start<2)
		{
				operation=SFAIL;
				printError("No argument for ~ set",semicolonCount,eventReciver);
		}
		else operation=SBNOT;
		vertObj=new Script(this,line,start+1,end,pref,vars,eventReciver);
		return -1;
	}
	else if(strncmp(&line[start],"(float)",7)==0 || strncmp(&line[start],"(int)",5)==0 || strncmp(&line[start],"(bool)",6)==0 || strncmp(&line[start],"(string)",8)==0)
	{

		operation=SCAST;
		if(strncmp(line+start,"(int)",5)==0)
		{
			value.type=NINT;
			vertObj=new Script(this,line,start+5,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"(float)",7)==0)
		{
			value.type=NFLOAT;
			vertObj=new Script(this,line,start+7,end,pref,vars,eventReciver);;
		}
		else if(strncmp(line+start,"(bool)",6)==0)
		{
			value.type=NBOOL;
			vertObj=new Script(this,line,start+6,end,pref,vars,eventReciver);
		}
		else if(strncmp(line+start,"(string)",8)==0)
		{
			value.type=NCHAR;
			vertObj=new Script(this,line,start+8,end,pref,vars,eventReciver);
		}
		else operation=SFAIL;
		return -1;
	}
	
	else if((pref->calcType == SCIENTIFIC && line[start]>='A' || line[start]>='G') && line[start]<='Z'&& end-start==1 || (strncmp(line+start,"$A",2)==0 &&end-start==2))
	{
		operation=SVAR;
		if(strncmp(line+start,"$A",2)==0)
			var=26;
		else var=line[start]-65;
		return -1;
	}
	else if((line[start]>='A' && line[start]<='Z' || strncmp(line+start,"$A",2)==0) && line[end-1]==']')
	{
		if(strncmp(line+start,"$A",2)==0)
		{
			var=26;
			start++;
		}
		else var=line[start]-65;
		
		if((pos1=bracketFindRev(line,"[",end-1,start))>start+1)
		{
			if(line[pos1-1] !=']')
			{
				printError("Closing brace for variable not found",semicolonCount,eventReciver);
				operation=SFAIL;
				return -1;
			}
			if(pos1-3<=start && end-pos1-2<=0)
			{
				vertObj=vertObj2=NULL;
			}
			else {
				vertObj=new Script(this,line,start+2,pos1-1,pref,vars,eventReciver);
				vertObj2=new Script(this,line,pos1+1,end-1,pref,vars,eventReciver);
			}
			operation=SMATRIX;
		}
		else {

			if(end-start<=3)
				operation=SVECTOR;
			else {
				vertObj=new Script(this,line,start+2,end-1,pref,vars,eventReciver);
				operation=SARRAY;
			}
		}
		if(var>26 || var < 0)
		{
			printError("Invalid variable",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		return -1;
	}
	else if(line[start] == '\"')
	{
		if(line[end-1]!='\"' || end-start <=1)
		{
			printError("Invalid String",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SVALUE;
		value.type=NCHAR;
		value.cval=(char*)malloc(end-start-1);
		strcopy(value.cval,&line[start+1],end-start-2);
		return -1;
	}
	else if(line[start] == '\\')
	{
		char*err,*tmpval;
		if(end-start<3)
		{
			printError("Invalid number",semicolonCount,eventReciver);
			operation=SFAIL;
			return -1;
		}
		operation=SVALUE;
		value.type=NINT;
		
		tmpval=new char[end-start-1];
		strcopy(tmpval,&line[start+2],end-start-2);

		if(line[start+1] == 'b')
			value.ival=strtoll(tmpval,&err,2);
		else if(line[start+1] == 'o')
			value.ival=strtoll(tmpval,&err,8);
		else if(line[start+1] == 'c')
			value.ival=strtoll(tmpval,&err,10);
		else if(line[start+1] == 'h')
			value.ival=strtoll(tmpval,&err,16);
		else {
			printError("Invalid number",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		if(*err!=(char)0)
		{
			printError("Invalid number",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		
		delete[] tmpval;
		return -1;
	}
	else {
		operation=SVALUE;
		char*err,*tmpval;
		tmpval=new char[end-start+1];
		strcopy(tmpval,&line[start],end-start);
		
		if(pref->calcType == BASE)
		{
			value.type=NINT;
			if(pref->base == BIN)
				value.ival=strtoll(tmpval,&err,2);
			else if(pref->base == OCT)
				value.ival=strtoll(tmpval,&err,8);
			else if(pref->base == HEX)
				value.ival=strtoll(tmpval,&err,16);
			else if(pref->base == DEC)
				value.ival=strtoll(tmpval,&err,10);
		}
		else
		{
			value.ival=strtoll(tmpval,&err,10);
			if(*err!=(char)0)
			{
				value.fval=Complex(strtold(tmpval,&err),0.0);
				value.type=NFLOAT;
			}
			else value.type=NINT;
		}
		if(*err!=(char)0)
		{
			printError("Invalid number",semicolonCount,eventReciver);
			operation=SFAIL;
		}
		delete[] tmpval;
	}
	
	return -1;
}



double Script::calc()
{
	switch(operation)
	{
		case NONE:
			return ((Calculate*)horzObj)->calc();
	}
	return 0.0;
}



double Script::calcVertObj()
{
	if(vertObj != NULL)
		return vertObj->calc();
	else return NAN;
}
double Script::calcHorzObj()
{
	if(horzObj != NULL)
		return horzObj->calc();
	else return NAN;
}

Number Script::exec()
{

//	perror("exec: "+QString::number(operation));
	if(eventReciver->status)
	{
#ifndef CONSOLE
		if(eventReciver->exit)
		{
			eventReciver->exit=false;
			eventReciver->status=0;
			pthread_exit(0);
		}
		if(eventReciver->eventCount>200)
		{
//			perror("events: "+QString::number(eventReciver->eventCount));
			usleep(1000);
			if(eventReciver->eventCount>210)
				usleep(100000);
		}
#endif
		if(eventReciver->usleep)
		{
			eventReciver->usleep=false;
			usleep(eventReciver->sleepTime);
		}
		if(eventReciver->bbreak || eventReciver->bcontinue)
			return value;
		else eventReciver->status=0;
	}
	
	switch(operation)
	{
		case SSEMICOLON:
		{
			if(vertObj!=NULL)
				value=vertObj->exec();
			if(horzObj!=NULL)
			{
				return value=horzObj->exec();
			}
			else return value;
		}
		case SBRACKET:
			return vertObj->exec();
		case SVALUE:
			return value;

		case SVAR:
		{
			return eventReciver->vars[var][0];
		}
		case SARRAY:
		{
			value=vertObj->exec();
			int index=0;
			if(value.type==NBOOL)
				index=(int)value.bval;
			else if(value.type==NINT)
				index=value.ival;
			else if(value.type==NFLOAT)
				index=(int)value.fval.real();
			if(index<0)
				index=0;
			
			if(eventReciver->vars[var][0].type==NCHAR && eventReciver->numlen[var]==1)
			{
				value.type=NINT;
				if(eventReciver->vars[var][0].cval!=NULL && (signed)strlen(eventReciver->vars[var][0].cval)>index)
					value.ival=(long long)eventReciver->vars[var][0].cval[index];
				else value.ival=0;
				return value;
			}
			else if(index>=eventReciver->numlen[var])
			{
				value.type=NNONE;
				return value;
			}
			return eventReciver->vars[var][index];
		}
		case SVECTOR:
		{
			value.type=NVECTOR;
			value.ival=var;
			return value;
		}
		case SMATRIX:
		{
			if(vertObj==NULL && vertObj2==NULL)
			{
				value.type=NMATRIX;
				value.ival=var;
				return value;
			}
			int index=0,index2=0;
			
			value=vertObj->exec();
			convertToInt(&value);
			index=value.ival;
			if(index<0)
				index=0;
			
			value=vertObj2->exec();
			index2=value.ival;
			convertToInt(&value);
			if(index2<0)
				index2=0;
			int effIndex=index+index2*eventReciver->dimension[var][0];
//			perror("matrix effIndex: "+QString::number(effIndex));
			
			if(index<eventReciver->numlen[var] && eventReciver->vars[var][index].type==NCHAR)
			{
				value.type=NINT;
				if(eventReciver->vars[var][index].cval!=NULL && (signed)strlen(eventReciver->vars[var][index].cval)>index2)
					value.ival=(long long)eventReciver->vars[var][index].cval[index2];
				else value.ival=0;
				return value;
			}
			else if(effIndex>=eventReciver->numlen[var])
			{
				value.type=NNONE;
				return value;
			}
			return eventReciver->vars[var][effIndex];
		}
		case PLUS:
		{
			if(vertObj!=NULL)
				value=vertObj->exec();
			else {
				value.type=NFLOAT;
				value.fval=Complex(0.0);
			}
			Number n;

			if((value.type==NVECTOR || value.type==NMATRIX) &&value.ival==27)
			{
				Number*tmpMem=eventReciver->vars[27];
				int tmpMemLen=eventReciver->numlen[27],tmpDimension1=eventReciver->dimension[27][0],tmpDimension2=eventReciver->dimension[27][1];
				
				eventReciver->vars[27]= (Number*)malloc(sizeof(Number));
				eventReciver->vars[27][0].type=NNONE;
				eventReciver->vars[27][0].cval=NULL;
				eventReciver->dimension[27][0]=eventReciver->dimension[27][1]=eventReciver->numlen[27]=1;
				n=vertObj2->exec();
				
				free(eventReciver->vars[28]);
				eventReciver->vars[28]=tmpMem;
				eventReciver->numlen[28]=tmpMemLen;
				eventReciver->dimension[28][0]=tmpDimension1;
				eventReciver->dimension[28][1]=tmpDimension2;
				value.ival=28;
			}
			else n =vertObj2->exec();

			if(value.type==NCHAR && n.type==NCHAR)
			{
				int strlen1=strlen(value.cval);
				int strlen2=strlen(n.cval);
				char*newstring=(char*)malloc(strlen1+strlen2+1);
				memcpy(newstring,value.cval,strlen1);
				memcpy(&newstring[strlen1],n.cval,strlen2+1);
				free(value.cval);
				value.cval=newstring;

				return value;
			}
			
			switch(value.type)
			{
				case NBOOL:
					value.ival=(long long)value.bval; value.type=NINT; break;
				case NNONE:
				case NCHAR:
					value.fval=Complex(NAN,0.0); value.type=NFLOAT; break;
			}
			switch(n.type)
			{
				case NBOOL:
					n.ival=(long long)n.bval; n.type=NINT; break;
				case NNONE:
				case NCHAR:
					n.fval=Complex(NAN,0.0); n.type=NFLOAT; break;
				case NVECTOR:
					if(value.type!=NVECTOR)
					{
						Number tmp=value;
						value=n;
						n=tmp;
					}
					break;
				case NMATRIX:
					if(value.type!=NMATRIX)
					{
						Number tmp=value;
						value=n;
						n=tmp;
					}
					break;
			}

			switch(value.type)
			{
				case NINT:
					switch(n.type)
					{
						case NINT:
							value.ival+=n.ival;	break;
							break;
						case NFLOAT:
							value.fval=Complex((long double)value.ival,0.0)+n.fval; value.type=NFLOAT; break;
					}
					break;
				case NFLOAT:
					switch(n.type)
					{
						case NINT:
							value.fval+=Complex((long double)n.ival,0.0);	break;

						case NFLOAT:
							value.fval+=n.fval; break;
					}
					break;
				case NVECTOR:
				{
					int minlen=eventReciver->numlen[value.ival];
					if(n.type==NVECTOR)
					{
						if(eventReciver->numlen[n.ival]<minlen)
							minlen=eventReciver->numlen[n.ival];
						eventReciver->vars[27]=(Number*)realloc(eventReciver->vars[27],sizeof(Number)*minlen);
						for(int c=0; c<minlen; c++)
						{
							convertToFloat(&eventReciver->vars[value.ival][c]);
							convertToFloat(&eventReciver->vars[n.ival][c]);
							eventReciver->vars[27][c].type=NFLOAT;
							eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval+eventReciver->vars[n.ival][c].fval;
						}
					}
					else
					{
						convertToFloat(&n);
						eventReciver->vars[27]=(Number*)realloc(eventReciver->vars[27],sizeof(Number)*minlen);
						for(int c=0; c<minlen; c++)
						{
							convertToFloat(&eventReciver->vars[value.ival][c]);
							eventReciver->vars[27][c].type=NFLOAT;
							eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval+n.fval;
						}
					}
					eventReciver->numlen[27]=minlen;
					eventReciver->dimension[27][0]=minlen;
					eventReciver->dimension[27][1]=1;
					value.ival=27;
					break;
				}
				case NMATRIX:
				{
					int min1=eventReciver->dimension[value.ival][0];
					int min2=eventReciver->dimension[value.ival][1];
					int effIndex1=0,effIndex2=0,effIndexD=0;
					if(n.type==NMATRIX)
					{
						if(eventReciver->dimension[n.ival][0]<min1)
							min1=eventReciver->dimension[n.ival][0];
						if(eventReciver->dimension[n.ival][1]<min2)
							min2=eventReciver->dimension[n.ival][1];
	
						resizeVar(27,min1*min2);
						for(int c=0; c<min1; c++)
						{
							for(int c1=0; c1<min2; c1++)
							{
								effIndex1=c+c1*eventReciver->dimension[value.ival][0];
								effIndex2=c+c1*eventReciver->dimension[n.ival][0];
								effIndexD=c+c1*min1;
								convertToFloat(&eventReciver->vars[value.ival][effIndex1]);
								convertToFloat(&eventReciver->vars[n.ival][effIndex2]);
								eventReciver->vars[27][effIndexD].type=NFLOAT;
								eventReciver->vars[27][effIndexD].fval=eventReciver->vars[value.ival][effIndex1].fval+eventReciver->vars[n.ival][effIndex2].fval;
							}
						}
						eventReciver->dimension[27][0]=min1;
						eventReciver->dimension[27][1]=min2;
					}
					else
					{
						convertToFloat(&n);
						resizeVar(27,eventReciver->numlen[value.ival]);
						for(int c=0; c<eventReciver->numlen[value.ival]; c++)
						{
							convertToFloat(&eventReciver->vars[value.ival][c]);
							eventReciver->vars[27][c].type=NFLOAT;
							eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval+n.fval;
						}
						eventReciver->numlen[27]=eventReciver->numlen[value.ival];
						eventReciver->dimension[27][0]=eventReciver->dimension[value.ival][0];
						eventReciver->dimension[27][1]=eventReciver->dimension[value.ival][1];
					}
					value.ival=27;
				}
			}

			return value;
		}
		case MINUS:
		{
			Number n;
			if(vertObj!=NULL)
				value=vertObj->exec();
			else
			{
				value.type=NFLOAT;
				value.fval=Complex(0.0);
			}
			if((value.type==NVECTOR || value.type==NMATRIX) &&value.ival==27)
			{
				Number*tmpMem=eventReciver->vars[27];
				int tmpMemLen=eventReciver->numlen[27],tmpDimension1=eventReciver->dimension[27][0],tmpDimension2=eventReciver->dimension[27][1];
				
				eventReciver->vars[27]= (Number*)malloc(sizeof(Number));
				eventReciver->vars[27][0].type=NNONE;
				eventReciver->vars[27][0].cval=NULL;
				eventReciver->dimension[27][0]=eventReciver->dimension[27][1]=eventReciver->numlen[27]=1;
				n=vertObj2->exec();
				
				free(eventReciver->vars[28]);
				eventReciver->vars[28]=tmpMem;
				eventReciver->numlen[28]=tmpMemLen;
				eventReciver->dimension[28][0]=tmpDimension1;
				eventReciver->dimension[28][1]=tmpDimension2;
				value.ival=28;
			}
			else n =vertObj2->exec();
			
			switch(value.type)
			{
				case NBOOL:
					value.ival=(long long)value.bval; value.type=NINT; break;
				case NNONE:
				case NCHAR:
					value.type=NFLOAT; break;
			}
			int fakt=1;
			
			switch(n.type)
			{
				
				case NBOOL:
					n.ival=(long long)n.bval; n.type=NINT; break;
				case NNONE:
				case NCHAR:
					n.type=NFLOAT; break;
				case NVECTOR:
					if(value.type!=NVECTOR)
					{
						Number tmp=value;
						value=n;
						n=tmp;
						convertToFloat(&n);
						n.fval*=Complex(-1.0);
						fakt=-1;
					}
					break;
				case NMATRIX:
					if(value.type!=NMATRIX)
					{
						Number tmp=value;
						value=n;
						n=tmp;
						convertToFloat(&n);
						n.fval*=Complex(-1.0);
						fakt=-1;
					}
					break;
			}
			
			switch(value.type)
			{
				case NINT:
					switch(n.type)
					{
						case NINT:
							value.ival-=n.ival;	break;
							break;
						case NFLOAT:
							value.fval=Complex((long double)value.ival,0.0)-n.fval; value.type=NFLOAT; break;
					}
					break;
				case NFLOAT:
					switch(n.type)
					{
						case NINT:
							value.fval-=Complex((long double)n.ival,0.0);	break;

						case NFLOAT:
							value.fval-=n.fval; break;
					}
					break;
				case NVECTOR:
				{
					int minlen=eventReciver->numlen[value.ival];
					if(n.type==NVECTOR)
					{
						if(eventReciver->numlen[n.ival]<minlen)
							minlen=eventReciver->numlen[n.ival];
						eventReciver->vars[27]=(Number*)realloc(eventReciver->vars[27],sizeof(Number)*minlen);
						for(int c=0; c<minlen; c++)
						{
							convertToFloat(&eventReciver->vars[value.ival][c]);
							convertToFloat(&eventReciver->vars[n.ival][c]);
							eventReciver->vars[27][c].type=NFLOAT;
							eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval-eventReciver->vars[n.ival][c].fval;
						}
					}
					else
					{
						convertToFloat(&n);
						eventReciver->vars[27]=(Number*)realloc(eventReciver->vars[27],sizeof(Number)*minlen);
						for(int c=0; c<minlen; c++)
						{
							convertToFloat(&eventReciver->vars[value.ival][c]);
							eventReciver->vars[27][c].type=NFLOAT;
							eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval*Complex(fakt)-n.fval;
						}
					}
					eventReciver->numlen[27]=minlen;
					eventReciver->dimension[27][0]=minlen;
					eventReciver->dimension[27][1]=1;
					value.ival=27;
					break;
				}
				case NMATRIX:
				{
					int min1=eventReciver->dimension[value.ival][0];
					int min2=eventReciver->dimension[value.ival][1];
					int effIndex1=0,effIndex2=0,effIndexD=0;
					if(n.type==NMATRIX)
					{
						if(eventReciver->dimension[n.ival][0]<min1)
							min1=eventReciver->dimension[n.ival][0];
						if(eventReciver->dimension[n.ival][1]<min2)
							min2=eventReciver->dimension[n.ival][1];
	
						resizeVar(27,min1*min2);
						for(int c=0; c<min1; c++)
						{
							for(int c1=0; c1<min2; c1++)
							{
								effIndex1=c+c1*eventReciver->dimension[value.ival][0];
								effIndex2=c+c1*eventReciver->dimension[n.ival][0];
								effIndexD=c+c1*min1;
								convertToFloat(&eventReciver->vars[value.ival][effIndex1]);
								convertToFloat(&eventReciver->vars[n.ival][effIndex2]);
								eventReciver->vars[27][effIndexD].type=NFLOAT;
								eventReciver->vars[27][effIndexD].fval=eventReciver->vars[value.ival][effIndex1].fval-eventReciver->vars[n.ival][effIndex2].fval;
							}
						}
						eventReciver->dimension[27][0]=min1;
						eventReciver->dimension[27][1]=min2;
					}
					else
					{
						convertToFloat(&n);
						resizeVar(27,eventReciver->numlen[value.ival]);
						for(int c=0; c<eventReciver->numlen[value.ival]; c++)
						{
							convertToFloat(&eventReciver->vars[value.ival][c]);
							eventReciver->vars[27][c].type=NFLOAT;
							eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval*Complex(fakt)-n.fval;
						}
						eventReciver->numlen[27]=eventReciver->numlen[value.ival];
						eventReciver->dimension[27][0]=eventReciver->dimension[value.ival][0];
						eventReciver->dimension[27][1]=eventReciver->dimension[value.ival][1];
					}
					value.ival=27;
				}
			}
			return value;
		}
		case SCOMPARE:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
					value.bval=(n1.fval==n2.fval);
				else if(n2.type==NBOOL)
					value.bval=(n1.fval.real()==(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval.real()==(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval.real()==(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval.real()==(long double)n1.ival);
				else value.bval=false;
			}
			else if(n1.type==NINT)
			{
				if(n2.type==NINT)
					value.bval=(n1.ival==n2.ival);
				else if(n2.type==NBOOL)
						value.bval=(n1.ival==(long long)n2.bval);
				else value.bval=false;
			}
			else if(n2.type==NINT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.ival==(long long)n1.bval);
				else value.bval=false;
			}
			else if(n1.type==NCHAR)
			{
				if(n2.type==NCHAR)
				{
					if(n1.cval!=NULL && n2.cval!=NULL)
						value.bval=(strcmp(n1.cval,n2.cval)==0);
					else value.bval=false;
				}
				else value.bval=false;
			}
			else if(n1.type==n2.type)
				value.bval=true;
			else value.bval=false;
			return value;
		}
		case SSET:
		{
			int index=0,index2=0,effIndex=0,oldDimension1=eventReciver->dimension[var][0],oldDimension2=eventReciver->dimension[var][1];
			int newlen=1;
			bool charOperation=false;
			value=vertObj->exec();


			if(vertObj2!=NULL)
			{
				Number nIndex=vertObj2->exec();
				if(nIndex.type==NBOOL)
					index=(int)nIndex.bval;
				else if(nIndex.type==NINT)
					index=nIndex.ival;
				else if(nIndex.type==NFLOAT)
					index=(int)nIndex.fval.real();
				if(index<0)
					index=0;
				
				if(vertObj3==NULL && eventReciver->vars[var][0].type==NCHAR && value.type!=NCHAR && eventReciver->numlen[var]==1)
				{
					charOperation=true;
					newlen=1;
					index2=index;
					index=0;
				}
				else {
					if(eventReciver->dimension[var][0]<index+1)
						eventReciver->dimension[var][0]=index+1;
					newlen=index+1;
				}
			}
			if(vertObj3!=NULL)
			{
				Number nIndex=vertObj3->exec();
				if(nIndex.type==NBOOL)
					index2=(int)nIndex.bval;
				else if(nIndex.type==NINT)
					index2=nIndex.ival;
				else if(nIndex.type==NFLOAT)
					index2=(int)nIndex.fval.real();
				if(index2<0)
					index2=0;
				
				if(eventReciver->numlen[var]>index && eventReciver->vars[var][index].type==NCHAR && value.type!=NCHAR)
				{
					charOperation=true;
					newlen=index+1;
				}
				else {
					if(eventReciver->dimension[var][1]<index2+1)
						eventReciver->dimension[var][1]=index2+1;
					newlen=index2*eventReciver->dimension[var][0]+index+1;
				}
			}
			
			if(value.type==NVECTOR)
			{
				newlen=eventReciver->dimension[value.ival][0];
				eventReciver->dimension[var][0]=eventReciver->dimension[value.ival][0];
			}
			else if(value.type==NMATRIX)
			{
				newlen=eventReciver->dimension[value.ival][0]*eventReciver->dimension[value.ival][1];
				eventReciver->dimension[var][0]=eventReciver->dimension[value.ival][0];
				eventReciver->dimension[var][1]=eventReciver->dimension[value.ival][1];
			}

			
			if(oldDimension1<eventReciver->dimension[var][0])
			{
				newlen=eventReciver->dimension[var][1]*eventReciver->dimension[var][0];
				if(newlen>eventReciver->numlen[var])
					resizeVar(var,newlen);
				int oldEffIndex,newEffIndex;
				Number nullNum;
				nullNum.type=NONE;
				nullNum.cval=NULL;
				
				for(int c=oldDimension2-1; c>=1; c--)
				{
					for(int c1=oldDimension1-1; c1>=0; c1--)
					{
						
						oldEffIndex=c1+c*oldDimension1;
						newEffIndex=c1+c*eventReciver->dimension[var][0];
						memcpy(&eventReciver->vars[var][newEffIndex],&eventReciver->vars[var][oldEffIndex],sizeof(Number));
						memcpy(&eventReciver->vars[var][oldEffIndex],&nullNum,sizeof(Number));
					}
				}
			}
			else if(newlen>eventReciver->numlen[var])
				resizeVar(var,newlen);
			
			if(charOperation)
			{
				if(eventReciver->dimension[var][0]<index+1)
					eventReciver->dimension[var][0]=index+1;
				
				convertToInt(&value);
				
				if(eventReciver->vars[var][index].cval==NULL)
					eventReciver->vars[var][index].cval=(char*)calloc(index2+2,1);
				else if((signed)strlen(eventReciver->vars[var][index].cval)<index2+1)
				{
					eventReciver->vars[var][index].cval=(char*)realloc(eventReciver->vars[var][index].cval,index2+2);
					eventReciver->vars[var][index].cval[index2+1]=(char)0;
				}
				eventReciver->vars[var][index].cval[index2]=(char)value.ival;
					
				return value;
			}
			effIndex=index+index2*eventReciver->dimension[var][0];
//			perror("newlen "+QString::number(eventReciver->numlen[var])+ " var: " + QString::number(var));
//			perror("index "+QString::number(index)+ " index2: " + QString::number(index2));
//			perror("dimesion[0] "+QString::number(eventReciver->dimension[var][0])+ " dimension[1]: " + QString::number(eventReciver->dimension[var][1]));
			switch(value.type)
			{
				case NINT:
					eventReciver->vars[var][effIndex].ival=value.ival; eventReciver->vars[var][effIndex].type=NINT; break;
				case NFLOAT:
					eventReciver->vars[var][effIndex].fval=value.fval; eventReciver->vars[var][effIndex].type=NFLOAT; break;
				case NBOOL:
					eventReciver->vars[var][effIndex].cval=value.cval; eventReciver->vars[var][effIndex].type=NBOOL; break;
				case NCHAR:
//					perror("effIndex: "+QString::number(effIndex)+" source text: "+QString(value.cval));
					if(value.cval==NULL)
						eventReciver->vars[var][effIndex].cval=NULL;
					else {
						if(eventReciver->vars[var][effIndex].cval==NULL)
							eventReciver->vars[var][effIndex].cval=(char*)malloc(strlen(value.cval)+1);
						else eventReciver->vars[var][effIndex].cval=(char*)realloc(eventReciver->vars[var][effIndex].cval,strlen(value.cval)+1);
						strcpy(eventReciver->vars[var][effIndex].cval,value.cval);
					}
					eventReciver->vars[var][effIndex].type=NCHAR;
					break;
				case NVECTOR:
				case NMATRIX:
					for(int c=0; c<eventReciver->numlen[value.ival]; c++)
					{
						convertToFloat(&eventReciver->vars[value.ival][c]);
						eventReciver->vars[var][c].fval=eventReciver->vars[value.ival][c].fval;
						eventReciver->vars[var][c].type=NFLOAT;
					}
					break;
				default:
					eventReciver->vars[var][effIndex].type=NNONE;
			}
			return value;
		}
		case SIF:
		{
			value=vertObj->exec();
			if(value.type==NBOOL)
				if(value.bval)
					value=vertObj2->exec();
			else if(value.type==NINT)
				if(value.ival)
					value=vertObj2->exec();
			else if(value.type==NFLOAT)
				if(value.fval.real()!=0.0)
					value=vertObj2->exec();
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SIFELSE:
		{
			value=vertObj->exec();
			if(value.type==NBOOL)
				if(value.bval)
					value=vertObj2->exec();
				else value=vertObj3->exec();
			else if(value.type==NINT)
				if(value.ival)
					value=vertObj2->exec();
				else value=vertObj3->exec();
			else if(value.type==NFLOAT)
				if(value.fval.real()!=0.0)
					value=vertObj2->exec();
				else value=vertObj3->exec();
			else value=vertObj3->exec();
			
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SWHILE:
		{
			while(true)
			{
				value=vertObj->exec();
				if(value.type==NBOOL)
				{
					if(!value.bval)
						break;
				}
				else if(value.type==NINT)
				{
					if(value.ival==0)
						break;
				}
				else if(value.type==NFLOAT)
				{
					if(value.fval.real()==0.0)
						break;
				}
				else break;
				vertObj2->exec();
				if(eventReciver->status)
				{
					if(eventReciver->bbreak)
					{
						eventReciver->status=0;
						eventReciver->bbreak=false;
						break;
					}
					if(eventReciver->bcontinue)
					{
						eventReciver->status=0;
						eventReciver->bcontinue=false;
					}
				}
			}
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SFOR:
		{
			if(vertObj3!=NULL)
			{
				for(vertObj->exec();;vertObj3->exec())
				{
					if(vertObj2!=NULL)
					{
						value=vertObj2->exec();
						if(value.type==NBOOL)
							if(!value.bval)
								break;
						else if(value.type==NINT)
							if(value.ival==0)
								break;
						else if(value.type==NFLOAT)
							if(value.fval.real()==0.0)
								break;
						else break;
					}
					vertObj4->exec();
					if(eventReciver->status)
					{
						if(eventReciver->bbreak)
						{
							eventReciver->status=0;
							eventReciver->bbreak=false;
							break;
						}
						else if(eventReciver->bcontinue)
						{
							eventReciver->status=0;
							eventReciver->bcontinue=false;
						}
					}
				}
			}
			else {
				for(vertObj->exec();;)
				{
					if(vertObj2!=NULL)
					{
						value=vertObj2->exec();
						if(value.type==NBOOL)
							if(!value.bval)
								break;
						else if(value.type==NINT)
							if(value.ival==0)
								break;
						else if(value.type==NFLOAT)
							if(value.fval.real()==0.0)
								break;
						else break;
					}
					vertObj4->exec();
					if(eventReciver->status)
					{
						if(eventReciver->bbreak)
						{
							eventReciver->status=0;
							eventReciver->bbreak=false;
							break;
						}
						else if(eventReciver->bcontinue)
						{
							eventReciver->status=0;
							eventReciver->bcontinue=false;
						}
					}
				}
			}
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}

		case SUNEQUAL:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
					value.bval=(n1.fval!=n2.fval);
				else if(n2.type==NBOOL)
					value.bval=(n1.fval.real()!=(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval.real()!=(long double)n2.ival);
				else value.bval=true;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval.real()!=(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval.real()!=(long double)n1.ival);
				else value.bval=true;
			}
			else if(n1.type==NINT)
			{
				if(n2.type==NINT)
					value.bval=(n1.ival!=n2.ival);
				else if(n2.type==NBOOL)
					value.bval=(n1.ival!=(long long)n2.bval);
				else value.bval=true;
			}
			else if(n2.type==NINT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.ival!=(long long)n1.bval);
				else value.bval=true;
			}
			else if(n1.type==NCHAR)
			{
				if(n2.type==NCHAR)
				{
					if(n1.cval!=NULL && n2.cval!=NULL)
						value.bval=(strcmp(n1.cval,n2.cval)!=0);
					else value.bval=true;
				}
				else value.bval=true;
			}
			else if(n1.type==n2.type)
				value.bval=false;
			else value.bval=true;

			return value;
		}
		case SNOT:
		{
			value=vertObj->exec();
			convertToBool(&value);
			value.bval=!value.bval;
			return value;
		}
		case SAND:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToBool(&value);
			convertToBool(&n);
			
			value.bval=(value.bval&&n.bval);
			return value;
		}
		case SOR:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToBool(&value);
			convertToBool(&n);
			
			value.bval=(value.bval||n.bval);
			return value;
		}

		case MULT:
		{
			value=vertObj->exec();
			Number n;
			if((value.type==NVECTOR || value.type==NMATRIX) &&value.ival==27)
			{
				Number*tmpMem=eventReciver->vars[27];
				int tmpMemLen=eventReciver->numlen[27],tmpDimension1=eventReciver->dimension[27][0],tmpDimension2=eventReciver->dimension[27][1];
				
				eventReciver->vars[27]= (Number*)malloc(sizeof(Number));
				eventReciver->vars[27][0].type=NNONE;
				eventReciver->vars[27][0].cval=NULL;
				eventReciver->dimension[27][0]=eventReciver->dimension[27][1]=eventReciver->numlen[27]=1;
				n=vertObj2->exec();
				
				free(eventReciver->vars[28]);
				eventReciver->vars[28]=tmpMem;
				eventReciver->numlen[28]=tmpMemLen;
				eventReciver->dimension[28][0]=tmpDimension1;
				eventReciver->dimension[28][1]=tmpDimension2;
				value.ival=28;
			}
			else n =vertObj2->exec();
			
			switch(value.type)
			{
				case NBOOL:
					value.ival=(long long)value.bval; value.type=NINT; break;
				case NNONE:
				case NCHAR:
					value.type=NFLOAT; break;
			}
			switch(n.type)
			{
				case NBOOL:
					n.ival=(long long)n.bval; n.type=NINT; break;
				case NNONE:
				case NCHAR:
					n.type=NFLOAT; break;
				case NVECTOR:
					if(value.type!=NVECTOR && value.type!=NMATRIX)
					{
						Number tmp=value;
						value=n;
						n=tmp;
					}
					break;
				case NMATRIX:
					if(value.type!=NMATRIX && value.type!=NVECTOR)
					{
						Number tmp=value;
						value=n;
						n=tmp;
					}
					break;
			}
			if(value.type==NINT && n.type==NINT)
				value.ival*=n.ival;
			else if(value.type==NFLOAT && n.type==NFLOAT)
				value.fval*=n.fval;
			else if(value.type==NFLOAT && n.type==NINT)
				value.fval*=Complex((long double)n.ival,0.0);
			else if(value.type==NINT && n.type==NFLOAT)
			{
				value.fval=Complex((long double)value.ival,0.0)*n.fval;
				value.type=NFLOAT;
			}
			else if(value.type==NVECTOR && n.type==NVECTOR)					//cross product
			{
				if(eventReciver->dimension[n.ival][0]==3 && eventReciver->dimension[value.ival][0]==3)
				{
					int index1=value.ival;
					int index2=n.ival;
//					perror(QString::number(index1)+" "+QString::number(index2));

					eventReciver->vars[27]=(Number*)realloc(eventReciver->vars[27],sizeof(Number)*3);
					
					if(eventReciver->numlen[n.ival]<3)
						resizeVar(n.ival,3);
					if(eventReciver->numlen[value.ival]<3)
						resizeVar(value.ival,3);
					
					for(int c=0; c<3;c++)
					{
						eventReciver->vars[27][c].type=NFLOAT;
						eventReciver->vars[27][c].cval=NULL;
						convertToFloat(&eventReciver->vars[index1][c]);
						convertToFloat(&eventReciver->vars[index2][c]);
					}

					eventReciver->vars[27][0].fval=eventReciver->vars[index1][1].fval*eventReciver->vars[index2][2].fval-eventReciver->vars[index1][2].fval*eventReciver->vars[index2][1].fval;
					eventReciver->vars[27][1].fval=eventReciver->vars[index1][2].fval*eventReciver->vars[index2][0].fval-eventReciver->vars[index1][0].fval*eventReciver->vars[index2][2].fval;
					eventReciver->vars[27][2].fval=eventReciver->vars[index1][0].fval*eventReciver->vars[index2][1].fval-eventReciver->vars[index1][1].fval*eventReciver->vars[index2][0].fval;

					eventReciver->numlen[27]=3;
					eventReciver->dimension[27][0]=3;
					value.ival=27;
					value.type=NVECTOR;

				}
				else {
					value.type=NNONE;
					value.fval=Complex(NAN,0.0);
				}
				
			}
			else if((value.type==NMATRIX || value.type==NVECTOR) && (n.type==NMATRIX || n.type==NVECTOR))					//matrix product
			{
			//	perror("Dimension value: "+QString::number(eventReciver->dimension[value.ival][0])+" "+QString::number(eventReciver->dimension[value.ival][1])+
			//			" Dimension n: "+QString::number(eventReciver->dimension[n.ival][0])+" "+QString::number(eventReciver->dimension[n.ival][1]));
				int min1=eventReciver->dimension[value.ival][0];
				int min2=eventReciver->dimension[n.ival][1];
				int minstep=eventReciver->dimension[value.ival][1];
				int effIndex1=0,effIndex2=0,effIndexD=0;
				
				if(eventReciver->dimension[n.ival][0]!=minstep)
				{
					value.type=NNONE;
					return value;
				}

				resizeVar(27,min1*min2);
				for(int c=0; c<min1; c++)								//row
				{
					for(int c1=0; c1<min2; c1++)						//column
					{
						effIndexD=c+c1*min1;
						eventReciver->vars[27][effIndexD].type=NFLOAT;
						eventReciver->vars[27][effIndexD].fval=Complex(0.0);
						for(int c2=0; c2<minstep; c2++)
						{
							effIndex1=c+c2*eventReciver->dimension[value.ival][0];
							effIndex2=c2+c1*eventReciver->dimension[n.ival][0];
						
							if(effIndex1<eventReciver->numlen[value.ival] && effIndex2<eventReciver->numlen[n.ival])
							{
								convertToFloat(&eventReciver->vars[value.ival][effIndex1]);
								convertToFloat(&eventReciver->vars[n.ival][effIndex2]);
								eventReciver->vars[27][effIndexD].fval+=eventReciver->vars[value.ival][effIndex1].fval*eventReciver->vars[n.ival][effIndex2].fval;
							}
						}
					}
				}
				eventReciver->dimension[27][0]=min1;
				eventReciver->dimension[27][1]=min2;
				value.ival=27;
				if(n.type==NVECTOR)
					value.type=NVECTOR;
				else value.type=NMATRIX;
			}
			else if((value.type==NMATRIX || value.type==NVECTOR) && !(n.type==NMATRIX || n.type==NVECTOR))
			{
				convertToFloat(&n);
				resizeVar(27,eventReciver->numlen[value.ival]);
				for(int c=0; c<eventReciver->numlen[value.ival]; c++)
				{
					convertToFloat(&eventReciver->vars[value.ival][c]);
					eventReciver->vars[27][c].type=NFLOAT;
					eventReciver->vars[27][c].fval=eventReciver->vars[value.ival][c].fval*n.fval;
				}
				eventReciver->numlen[27]=eventReciver->numlen[value.ival];
				eventReciver->dimension[27][0]=eventReciver->dimension[value.ival][0];
				eventReciver->dimension[27][1]=eventReciver->dimension[value.ival][1];
				value.ival=27;
			}
			else value.type=NNONE;

			return value;
		}
		case DIVIDE:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			switch(value.type)
			{
				case NBOOL:
					value.ival=(long long)value.bval; value.type=NINT; break;
				case NNONE:
				case NCHAR:
					value.type=NFLOAT; break;
			}
			switch(n.type)
			{
				case NBOOL:
					n.ival=(long long)n.bval; n.type=NINT; break;
				case NNONE:
				case NCHAR:
					n.type=NFLOAT; break;
			}
			if(value.type==NINT && n.type==NINT)
			{
				if(n.ival==0)
				{
					value.fval=Complex((long double)value.ival/(long double)n.ival,0.0);
					value.type=NFLOAT;
				}
				else {
					value.fval=Complex((long double)value.ival / (long double)n.ival);
					value.ival=(long long)value.fval.real();
					if((long double)value.ival != value.fval.real())
					{
						value.type=NFLOAT;
					}
				}
			}
			else if(value.type==NFLOAT && n.type==NFLOAT)
				value.fval=Complex(value.fval.real()/n.fval.real());
			else if(value.type==NFLOAT && n.type==NINT)
				value.fval=Complex(value.fval.real()/(long double)n.ival,0.0);
			else if(value.type==NINT && n.type==NFLOAT)
			{
				value.fval=Complex((long double)value.ival/n.fval.real(),0.0);
				value.type=NFLOAT;
			}

			return value;
		}
		case CDIVIDE:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			switch(value.type)
			{
				case NBOOL:
					value.ival=(long long)value.bval; value.type=NINT; break;
				case NNONE:
				case NCHAR:
					value.type=NFLOAT; break;
			}
			switch(n.type)
			{
				case NBOOL:
					n.ival=(long long)n.bval; n.type=NINT; break;
				case NNONE:
				case NCHAR:
					n.type=NFLOAT; break;
			}
			if(value.type==NINT && n.type==NINT)
			{
				if(n.ival==0)
				{
					value.fval=Complex((long double)value.ival/(long double)n.ival,0.0);
					value.type=NFLOAT;
				}
				else {
					value.fval=Complex((long double)value.ival / (long double)n.ival);
					value.ival=(long long)value.fval.real();
					if((long double)value.ival != value.fval.real())
						value.type=NFLOAT;
				}
			}
			else if(value.type==NFLOAT && n.type==NFLOAT)
				value.fval/=n.fval;
			else if(value.type==NFLOAT && n.type==NINT)
				value.fval/=Complex((long double)n.ival,0.0);
			else if(value.type==NINT && n.type==NFLOAT)
			{
				value.fval=Complex((long double)value.ival,0.0)/n.fval;
				value.type=NFLOAT;
			}

			return value;
		}
		case SPRINT:
		{
			char*eventContent=NULL;
			value=vertObj->exec();
			switch(value.type)
			{
				case NFLOAT:
				{
					if(value.fval.imag()==0.0)
					{
						eventContent=(char*)malloc(42);
						sprintf(eventContent,"%.*Lg",pref->outputLength,real(value.fval));
					}
					else {
						eventContent=(char*)malloc(84);
						if(value.fval.imag()<0.0)
							sprintf(eventContent,"%.*Lg%.*Lgi",pref->outputLength,real(value.fval),pref->outputLength,imag(value.fval));
						else sprintf(eventContent,"%.*Lg+%.*Lgi",pref->outputLength,real(value.fval),pref->outputLength,imag(value.fval));
					}

					break;
				}
				case NINT:
				{
					eventContent=(char*)malloc(30);
					sprintf(eventContent,"%lli",value.ival);
					break;
				}
				case NBOOL:
					if(value.bval)
					{
						eventContent=(char*)malloc(5);
						strcopy(eventContent,"true",4);
					}
					else {
						eventContent=(char*)malloc(6);
						strcopy(eventContent,"false",5);
					}
					break;
				case NCHAR:
				{
					int slen=strlen(value.cval);
					eventContent=(char*)malloc(slen+1);
					strcopy(eventContent,value.cval,slen);
					break;
				}
				case NVECTOR:
				{
					eventContent=(char*)calloc(1,1);
					for(int c=0; c<eventReciver->dimension[value.ival][0];c++)
					{
						convertToFloat(&eventReciver->vars[value.ival][c]);
						if(eventReciver->vars[value.ival][c].fval.imag()==0.0)
						{
							eventContent=(char*)realloc(eventContent,strlen(eventContent)+44);
							sprintf(&eventContent[strlen(eventContent)]," %.*Lg",pref->outputLength,real(eventReciver->vars[value.ival][c].fval));
						}
						else {
							eventContent=(char*)realloc(eventContent,strlen(eventContent)+86);
							if(eventReciver->vars[value.ival][c].fval.imag()<0.0)
								sprintf(&eventContent[strlen(eventContent)]," %.*Lg%.*Lgi",pref->outputLength,real(eventReciver->vars[value.ival][c].fval),pref->outputLength,imag(eventReciver->vars[value.ival][c].fval));
							else sprintf(&eventContent[strlen(eventContent)]," %.*Lg+%.*Lgi",pref->outputLength,real(eventReciver->vars[value.ival][c].fval),pref->outputLength,imag(eventReciver->vars[value.ival][c].fval));
						}
					}
					break;
				}
				case NMATRIX:
				{
					eventContent=(char*)calloc(1,1);
					int effIndex;
					for(int c=0; c<eventReciver->dimension[value.ival][0];c++)
					{
						for(int c1=0; c1<eventReciver->dimension[value.ival][1];c1++)
						{
							effIndex=c1*eventReciver->dimension[value.ival][0]+c;
							convertToFloat(&eventReciver->vars[value.ival][effIndex]);
							if(eventReciver->vars[value.ival][effIndex].fval.imag()==0.0)
							{
								eventContent=(char*)realloc(eventContent,strlen(eventContent)+45);
								sprintf(&eventContent[strlen(eventContent)]," %.*Lg",pref->outputLength,real(eventReciver->vars[value.ival][effIndex].fval));
							}
							else {
								eventContent=(char*)realloc(eventContent,strlen(eventContent)+87);
								if(eventReciver->vars[value.ival][effIndex].fval.imag()<0.0)
									sprintf(&eventContent[strlen(eventContent)]," %.*Lg%.*Lgi",pref->outputLength,real(eventReciver->vars[value.ival][effIndex].fval),pref->outputLength,imag(eventReciver->vars[value.ival][effIndex].fval));
								else sprintf(&eventContent[strlen(eventContent)]," %.*Lg+%.*Lgi",pref->outputLength,real(eventReciver->vars[value.ival][effIndex].fval),pref->outputLength,imag(eventReciver->vars[value.ival][effIndex].fval));
							}
						}
						sprintf(&eventContent[strlen(eventContent)],"\n");

					}
					break;
				}
				default:
					eventContent=(char*)malloc(5);
					strcopy(eventContent,"none",4);
					break;
			}

#ifndef CONSOLE
			QCustomEvent *ev=new QCustomEvent(SIGPRINT);
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else 
			fprintf(stderr,"%s",eventContent);
			free(eventContent);
#endif

			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
#ifndef CONSOLE
		case SDRAW:
		{
			QCustomEvent *ev=new QCustomEvent(SIGDRAW);
			char*eventContent=NULL;
			int arg;
			switch(var)
			{
				case 0:
					eventContent=(char*)malloc(1);
					eventContent[0]=var;
					break;
				case 1:
					eventContent=(char*)malloc(9);
					eventContent[0]=var;
					value=vertObj->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[1],&arg,4);
					value=vertObj2->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[5],&arg,4);
					break;
				case 2:
					eventContent=(char*)malloc(13);
					eventContent[0]=var;
					value=vertObj->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[1],&arg,4);
					value=vertObj2->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[5],&arg,4);
					value=vertObj3->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[9],&arg,4);
					break;
				case 3:
					value=vertObj3->exec();
					if(value.type!=NCHAR)
					{
						convertToFloat(&value);
						eventContent=(char*)malloc(101+2*sizeof(int));
						sprintf(&eventContent[2*sizeof(int)+1],"%.*Lg",pref->outputLength,value.fval.real());
					}
					else {
						eventContent=(char*)malloc(strlen(value.cval)+2*sizeof(int)+2);
						strcpy(&eventContent[2*sizeof(int)+1],value.cval);
					}
					eventContent[0]=var;
					value=vertObj->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[1],&arg,4);
					value=vertObj2->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[5],&arg,4);
					break;
				case 4:
				case 5:
				case 6:
					eventContent=(char*)malloc(17);
					eventContent[0]=var;
					value=vertObj4->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[1],&arg,4);
					value=vertObj->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[5],&arg,4);
					value=vertObj2->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[9],&arg,4);
					value=vertObj3->exec();
					convertToInt(&value);
					arg=(int)value.ival;
					memcpy(&eventContent[13],&arg,4);
					break;
					
			}
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			return value;
		}
		case SGRAPHLIST:
		{
			if(var==0)
			{
				QCustomEvent *ev=new QCustomEvent(SIGCALLLIST);
				value=vertObj->exec();
				convertToInt(&value);
				int num=value.ival;
				int*eventContent=(int*)malloc(sizeof(int));
				memcpy(eventContent,&num,sizeof(int));
				ev->setData(eventContent);
				QCoreApplication::postEvent(eventReciver->eventReciver,ev);
				eventReciver->eventCount++;
				if(eventReciver->eventCount>200)
					eventReciver->status=1;
			}
			else if(var==1)
			{
				QCustomEvent *ev=new QCustomEvent(SIGSTARTLIST);
				QCoreApplication::postEvent(eventReciver->eventReciver,ev);
				eventReciver->eventCount++;
				if(eventReciver->eventCount>200)
					eventReciver->status=1;
			}
			else if(var==2)
			{
				eventReciver->data=NULL;
				QCustomEvent*ev=new QCustomEvent(SIGENDLIST);
				qApp->lock();
				QCoreApplication::postEvent(eventReciver->eventReciver,ev);
				eventReciver->eventCount++;
				if(eventReciver->eventCount>200)
					eventReciver->status=1;
				qApp->unlock();
				while(eventReciver->data==NULL)
				{
					if(eventReciver->status)
						if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
					usleep(500);
				}
				int retval;
				memcpy(&retval,eventReciver->data,sizeof(int));
				value.ival=retval;
				value.type=NINT;
				free(eventReciver->data);
			}

			return value;
		}
		case SGRAPHCONTROL:
		{
			QCustomEvent *ev;
			if(var==0)
				ev=new QCustomEvent(SIGGRAPHSHOW);
			else if(var==1)
				ev=new QCustomEvent(SIGGRAPHCLEAR);
			else if(var==2)
				ev=new QCustomEvent(SIGGRAPHEND);
			else ev=new QCustomEvent(SIGIDENTITY);
			
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			
			return value;
		}
		case SGRAPHPAINT:
		{
			QCustomEvent *ev=new QCustomEvent(SIGGRAPHBEGIN);
			int*eventContent=(int*)malloc(sizeof(int));
			*eventContent=(int)value.ival;
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;

			return value;
		}
		case SGRAPHVERTEX:
		{
			QCustomEvent *ev=new QCustomEvent(SIGGRAPHVERTEX);
			double*eventContent=(double*)malloc(sizeof(double)*3);
			value=vertObj->exec();
			convertToFloat(&value);
			eventContent[0]=(double)value.fval.real();
			value=vertObj2->exec();
			convertToFloat(&value);
			eventContent[1]=(double)value.fval.real();
			value=vertObj3->exec();
			convertToFloat(&value);
			eventContent[2]=(double)value.fval.real();

			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			return value;
		}
		case SGRAPHTRANSFORM:
		{
			QCustomEvent *ev;
			double*eventContent=(double*)malloc(sizeof(double)*4);
			value=vertObj->exec();
			convertToFloat(&value);
			eventContent[0]=(double)value.fval.real();
			value=vertObj2->exec();
			convertToFloat(&value);
			eventContent[1]=(double)value.fval.real();
			value=vertObj3->exec();
			convertToFloat(&value);
			eventContent[2]=(double)value.fval.real();
			if(var==2)
			{
				value=vertObj4->exec();
				convertToFloat(&value);
				eventContent[3]=(double)value.fval.real();
				ev=new QCustomEvent(SIGGRAPHROTATE);
			}
			else if(var==1)
				ev=new QCustomEvent(SIGGRAPHTRANSLATE);
			else ev=new QCustomEvent(SIGGRAPHSCALE);

			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			return value;
		}
		case SGRAPHCOLOR:
		{
			QCustomEvent *ev=new QCustomEvent(SIGGRAPHCOLOR);
			int*eventContent=(int*)malloc(sizeof(int)*3);
			value=vertObj->exec();
			convertToInt(&value);
			if(value.ival<0)
				value.ival=0;
			if(value.ival>255)
				value.ival=255;
			eventContent[0]=(int)value.ival;
			value=vertObj2->exec();
			convertToInt(&value);
			if(value.ival<0)
				value.ival=0;
			if(value.ival>255)
				value.ival=255;
			eventContent[1]=(int)value.ival;
			value=vertObj3->exec();
			convertToInt(&value);
			if(value.ival<0)
				value.ival=0;
			if(value.ival>255)
				value.ival=255;
			eventContent[2]=(int)value.ival;

			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			return value;
		}
		case SGRAPHTEXT:
		{
			QCustomEvent *ev=new QCustomEvent(SIGGRAPHTEXT);
			char*eventContent;
			
			value=vertObj4->exec();
			if(value.type!=NCHAR)
			{
				convertToFloat(&value);
				eventContent=(char*)malloc(100+2*sizeof(int));
				sprintf(&eventContent[2*sizeof(int)],"%.*Lg",pref->outputLength,value.fval.real());
			}
			else {
				eventContent=(char*)malloc(strlen(value.cval)+2*sizeof(int)+1);
				strcpy(&eventContent[2*sizeof(int)],value.cval);
			}
			value=vertObj->exec();
			convertToInt(&value);
			((int*)eventContent)[0]=(int)value.ival;
			value=vertObj2->exec();
			convertToInt(&value);
			((int*)eventContent)[1]=(int)value.ival;
			
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			
			return value;
		}
#endif
		case SLESS:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
				{
					if(n1.fval.imag()==0.0 && n2.fval.imag()==0.0)
						value.bval=(n1.fval.real()<n2.fval.real());
					else value.bval=(abs(n1.fval)<abs(n2.fval));
				}
				else if(n2.type==NBOOL)
					value.bval=(n1.fval.real()<(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval.real()<(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval.real()>(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval.real()>(long double)n1.ival);
				else value.bval=false;
			}
			else if(n1.type==NINT)
			{
				if(n2.type==NINT)
					value.bval=(n1.ival<n2.ival);
				else if(n2.type==NBOOL)
					value.bval=(n1.ival<(long long)n2.bval);
				else value.bval=false;
			}
			else if(n2.type==NINT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.ival>(long long)n1.bval);
				else value.bval=false;
			}
			else if(n1.type==NCHAR)
			{
				if(n2.type==NCHAR)
				{
					if(n1.cval!=NULL && n2.cval!=NULL)
						value.bval=(strcmp(n1.cval,n2.cval)<0);
					else value.bval=false;
				}
				else value.bval=false;
			}
			else value.bval=false;
			return value;
		}
		case SGREATHER:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
				{
					if(n1.fval.imag()==0.0 && n2.fval.imag()==0.0)
						value.bval=(n1.fval.real()>n2.fval.real());
					else value.bval=(abs(n1.fval)>abs(n2.fval));
				}
				else if(n2.type==NBOOL)
					value.bval=(n1.fval.real()>(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval.real()>(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval.real()<(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval.real()<(long double)n1.ival);
				else value.bval=false;
			}
			else if(n1.type==NINT)
			{
				if(n2.type==NINT)
					value.bval=(n1.ival>n2.ival);
				else if(n2.type==NBOOL)
					value.bval=(n1.ival>(long long)n2.bval);
				else value.bval=false;
			}
			else if(n2.type==NINT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.ival<(long long)n1.bval);
				else value.bval=false;
			}
			else if(n1.type==NCHAR)
			{
				if(n2.type==NCHAR)
				{
					if(n1.cval!=NULL && n2.cval!=NULL)
						value.bval=(strcmp(n1.cval,n2.cval)>0);
					else value.bval=false;
				}
				else value.bval=false;
			}
			else value.bval=false;

			return value;
		}
		case SLESSEQ:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
				{
					if(n1.fval.imag()==0.0 && n2.fval.imag()==0.0)
						value.bval=(n1.fval.real()<=n2.fval.real());
					else value.bval=(abs(n1.fval)<=abs(n2.fval));
				}
				else if(n2.type==NBOOL)
					value.bval=(n1.fval.real()<=(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval.real()<=(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval.real()>=(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval.real()>=(long double)n1.ival);
				else value.bval=false;
			}
			else if(n1.type==NINT)
			{
				if(n2.type==NINT)
					value.bval=(n1.ival<=n2.ival);
				else if(n2.type==NBOOL)
					value.bval=(n1.ival<=(long long)n2.bval);
				else value.bval=false;
			}
			else if(n2.type==NINT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.ival>=(long long)n1.bval);
				else value.bval=false;
			}
			else if(n1.type==NCHAR)
			{
				if(n2.type==NCHAR)
				{
					if(n1.cval!=NULL && n2.cval!=NULL)
						value.bval=(strcmp(n1.cval,n2.cval)<=0);
					else value.bval=false;
				}
				else value.bval=false;
			}
			else value.bval=false;

			return value;
		}
		case SGREQ:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
				{
					if(n1.fval.imag()==0.0 && n2.fval.imag()==0.0)
						value.bval=(n1.fval.real()>=n2.fval.real());
					else value.bval=(abs(n1.fval)>=abs(n2.fval));
				}
				else if(n2.type==NBOOL)
					value.bval=(n1.fval.real()>=(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval.real()>=(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval.real()<=(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval.real()<=(long double)n1.ival);
				else value.bval=false;
			}
			else if(n1.type==NINT)
			{
				if(n2.type==NINT)
					value.bval=(n1.ival>=n2.ival);
				else if(n2.type==NBOOL)
					value.bval=(n1.ival>=(long long)n2.bval);
				else value.bval=false;
			}
			else if(n2.type==NINT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.ival<=(long long)n1.bval);
				else value.bval=false;
			}
			else if(n1.type==NCHAR)
			{
				if(n2.type==NCHAR)
				{
					if(n1.cval!=NULL && n2.cval!=NULL)
						value.bval=(strcmp(n1.cval,n2.cval)>=0);
					else value.bval=false;
				}
				else value.bval=false;
			}
			else value.bval=false;

			return value;
		}
		case POW:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToFloat(&value);
			convertToFloat(&n);

			value.fval=Complex(powl(value.fval.real(),n.fval.real()));
			return value;
		}
		case CPOW:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToFloat(&value);
			convertToFloat(&n);


			if(value.fval.imag()==0.0 && n.fval.imag()==0.0)
				value.fval=Complex(powl(value.fval.real(),n.fval.real()));
			else value.fval=pow(value.fval,n.fval);
			return value;
		}
		case INVERT:
		{
			value=vertObj->exec();
			switch(value.type)
			{
				case NFLOAT:
					value.fval=Complex(1.0)/value.fval;
					return value;
				case NMATRIX:
					
					long double*matrix;
					long double mainDet;
					int size,effIndex;
					if(eventReciver->dimension[value.ival][0]==eventReciver->dimension[value.ival][1])
						size=eventReciver->dimension[value.ival][1];
					else{
						value.type=NNONE;
						return value;
					}
					
					matrix=(long double*)malloc(size*size*sizeof(long double));
					for(int c1=0; c1<size; c1++)
						for(int c2=0; c2<size; c2++)
					{
						effIndex=c1+c2*eventReciver->dimension[value.ival][0];
						if(effIndex<eventReciver->numlen[value.ival])
						{
							convertToFloat(&eventReciver->vars[value.ival][effIndex]);
							matrix[c1+size*c2]=eventReciver->vars[value.ival][effIndex].fval.real();
						}
					}
					mainDet=gauss(size,size,matrix);
					mainDet=1.0/mainDet;
					
					resizeVar(27,size*size);
					eventReciver->dimension[27][0]=eventReciver->dimension[27][1]=size;
					
					int pos1,pos2,effSrcIndex,effDestIndex,vz;
					for(int c3=0; c3<size; c3++)
					{
						for(int c4=0; c4<size; c4++)
						{
							effIndex=c3+c4*eventReciver->dimension[value.ival][0];
							pos1=0;
							for(int c1=0; c1<size; c1++)
							{
								if(c1!=c3)
								{
									pos2=0;
									for(int c2=0; c2<size; c2++)
									{
										effDestIndex=pos1+(size-1)*pos2;
										effSrcIndex=c1+c2*eventReciver->dimension[value.ival][0];
										if(c2!=c4)
										{
											if(effSrcIndex<eventReciver->numlen[value.ival])
												matrix[effDestIndex]=eventReciver->vars[value.ival][effSrcIndex].fval.real();
											else matrix[effDestIndex]=NAN;
											pos2++;
										}
									}
									pos1++;
								}
							}
							vz=(c3+c4)%2;
							if(vz==0)
								vz=1;
							else vz=-1;
							effDestIndex=c4+c3*size;
							long double subDet=gauss(size-1,size-1,matrix);
							eventReciver->vars[27][effDestIndex].fval=Complex(mainDet*(long double)vz*subDet);
							
							eventReciver->vars[27][effDestIndex].type=NFLOAT;
						}
					}
					free(matrix);
					value.ival=27;
					return value;
				default:
					convertToFloat(&value);
					value.fval=Complex(1.0)/value.fval;
					return value;
			}
		}
		case SQRT:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(sqrtl(value.fval.real()));
			return value;
		}
		case CURT:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(cbrtl(value.fval.real()));
			return value;
		}
		case CSQRT:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=sqrt(value.fval);
			return value;
		}
		case ROOT:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToFloat(&value);
			convertToFloat(&n);

			value.fval=Complex(powl(n.fval.real(),1.0/value.fval.real()));
			return value;
		}
		case CROOT:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToFloat(&value);
			convertToFloat(&n);

			value.fval=pow(n.fval,Complex(1.0)/value.fval);
			return value;
		}
		case SIN:
		{
			value=vertObj->exec();
			convertToFloat(&value);
			value.fval=Complex(value.fval.real()/number);

			value.fval=Complex(sinl(value.fval.real()));
			return value;
		}
		case COS:
		{
			value=vertObj->exec();
			convertToFloat(&value);
			value.fval=Complex(value.fval.real()/number);
			value.fval=Complex(cosl(value.fval.real()));
			return value;
			
		}
		case TAN:
		{
			value=vertObj->exec();
			convertToFloat(&value);
			value.fval=Complex(value.fval.real()/number);
			value.fval=Complex(tanl(value.fval.real()));
			return value;
			
		}
		case CSIN:
		{
			value=vertObj->exec();
			convertToFloat(&value);
			value.fval=Complex(value.fval.real()/number,value.fval.imag());
			

			value.fval=sin(value.fval);
			return value;
		}
		case CCOS:
		{
			value=vertObj->exec();
			convertToFloat(&value);
			value.fval=Complex(value.fval.real()/number,value.fval.imag());
			value.fval=cos(value.fval);
			return value;
			
		}
		case CTAN:
		{
			value=vertObj->exec();
			convertToFloat(&value);
			value.fval=Complex(value.fval.real()/number,value.fval.imag());
			value.fval=tan(value.fval);
			return value;
			
		}
		case ASIN:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(asinl(value.fval.real())*number,imag(value.fval));
			return value;
		}
		case ACOS:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(acosl(value.fval.real())*number,imag(value.fval));
			return value;
		}
		case ATAN:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(atanl(value.fval.real())*number,imag(value.fval));
			return value;
		}
		case ASINH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(asinhl(value.fval.real()),imag(value.fval));
			return value;
			
		}
		case ACOSH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(acoshl(value.fval.real()),imag(value.fval));
			return value;
			
		}
		case ATANH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(atanhl(value.fval.real()),imag(value.fval));
			return value;
		}
		case SINH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(sinhl(value.fval.real()));
			return value;
			
		}
		case COSH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(cosh(value.fval.real()));
			return value;
			
		}
		case TANH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(tanh(value.fval.real()));
			return value;
			
		}
		case CSINH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=sinh(value.fval);
			return value;
			
		}
		case CCOSH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=cosh(value.fval);
			return value;
			
		}
		case CTANH:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=tanh(value.fval);
			return value;
			
		}
		case LN:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(log(value.fval.real()));
			return value;
			
		}
		case LG:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(log10(value.fval.real()));
			return value;
		}
		case CLN:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=log(value.fval);
			return value;
			
		}
		case CLG:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=log10(value.fval);
			return value;
		}
		case SREAL:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(value.fval.real(),0.0);
			return value;
		}
		case SIMAG:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(value.fval.imag(),0.0);
			return value;
		}
		case SABS:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(fabsl(value.fval.real()));
			return value;
		}
		case CABS:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(abs(value.fval),0.0);
			return value;
		}
		case SARG:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=Complex(arg(value.fval),0.0);
			return value;
		}
		case SCONJ:
		{
			value=vertObj->exec();
			convertToFloat(&value);

			value.fval=conj(value.fval);
			return value;
		}
		case SFAK:
		{
			value=vertObj->exec();
			convertToInt(&value);
			value.type=NFLOAT;

			if(value.ival<0)
				value.fval=Complex(NAN);
			else if(value.ival<2)
				value.fval=Complex(1.0);
			else {
				int end=value.ival;
				long double res=1.0;
				for(int c=2; c<=end; c++)
					res*=(long double)c;
				value.fval=Complex(res,0.0);
			}
			return value;
		}
		case SCAST:
		{
			Number n=vertObj->exec();
			switch(value.type)
			{
				case NINT:
					switch(n.type)
					{
						case NINT:
							value.ival=n.ival;
							break;
						case NFLOAT:
							value.ival=(long long)n.fval.real();
							break;
						case NCHAR:
							char*end;
							value.ival=strtoll(n.cval,&end,10);
							if(end[0]!=(char)0)
								value.ival=(long long)n.cval[0];
							break;
						case NBOOL:
							value.ival=n.bval;
							break;
						default:
							value.ival=0;
					}
					return value;
				case NFLOAT:
					switch(n.type)
					{
						case NINT:
							value.fval=Complex((long double)n.ival,0.0);
							break;
						case NCHAR:
							if(n.cval==NULL || strlen(n.cval)<=0)
								value.fval=Complex(NAN,0.0);
							else value.fval=Complex(strtold(n.cval,NULL),0.0);
							break;
						case NBOOL:
							value.fval=Complex(n.bval,0.0);
							break;
						default:
							value.fval=Complex(NAN,0.0);
					}
					return value;
				case NBOOL:
					switch(n.type)
					{
						case NINT:
							value.bval=!(!(bool)n.ival);
							break;
						case NFLOAT:
							if(n.fval.real()==0.0)
								value.bval=false;
							else value.bval=true;
							break;
						case NCHAR:
							if(strcmp(n.cval,"true")==0)
								value.bval=true;
							else if(strcmp(n.cval,"false")==0)
								value.bval=false;
							else value.bval=!(!((bool)strtoll(n.cval,NULL,10)));
							break;
						case NBOOL:
							value.bval=n.bval;
							break;
						default:
							value.bval=false;
					}
					return value;
				case NCHAR:
					switch(n.type)
					{
						case NINT:
							value.cval=(char*)malloc(25);
							sprintf(value.cval,"%lli",n.ival);
							break;
						case NFLOAT:
							value.cval=(char*)malloc(90);
							sprintf(value.cval,"%Lg",n.fval.real());
							if(value.fval.imag()!=0.0)
							{
								if(value.fval.imag()>0.0)
									strcpy(value.cval,"+");
								sprintf(&value.cval[strlen(value.cval)],"%Lg",n.fval.imag());
								strcpy(value.cval,"i");
							}
								
							break;
						case NCHAR:
							break;
						case NBOOL:
							if(n.bval)
								strcpy(value.cval,"true");
							else strcpy(value.cval,"false");
							break;
						default:
							value.cval[0]=(char)0;
					}
					return value;
				default:
					value.type=NNONE;
					return value;
			}
		}
		case RSHIFT:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToInt(&value);
			convertToInt(&n);

			value.ival=value.ival >> n.ival;
			return value;
		}
		case LSHIFT:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToInt(&value);
			convertToInt(&n);

			value.ival=value.ival << n.ival;
			return value;
		}
		case XOR:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToInt(&value);
			convertToInt(&n);

			value.ival=value.ival ^ n.ival;
			return value;
		}
		case SBAND:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToInt(&value);
			convertToInt(&n);

			value.ival=value.ival & n.ival;
			return value;
		}
		case SBOR:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			convertToInt(&value);
			convertToInt(&n);

			value.ival=value.ival | n.ival;
			return value;
		}
		case SBNOT:
		{
			value=vertObj->exec();
			switch(value.type)
			{
				case NBOOL:
					value.ival=(long long)value.bval; value.type=NINT; break;
				case NFLOAT:
					value.ival=(long long)value.fval.real(); value.type=NINT; break;
				case NCHAR:
				case NNONE:
					value.type=NNONE;
					return value;
			}

			value.ival=~value.ival;
			return value;
		}
		case MODULO:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			if(value.type!=NINT)
				convertToFloat(&value);
			if(n.type!=NINT)
				convertToFloat(&n);
			
			if(value.type==NINT && n.type==NINT)
				value.ival%=n.ival;
			else if(value.type==NFLOAT && n.type==NFLOAT)
				value.fval=Complex(fmodl(value.fval.real(),n.fval.real()),value.fval.imag());
			else if(value.type==NFLOAT && n.type==NINT)
				value.fval=Complex(fmodl(value.fval.real(),(long double)n.ival),value.fval.imag());
			else if(value.type==NINT && n.type==NFLOAT)
			{
				value.fval=Complex(fmodl((long double)value.ival,n.fval.real()),n.fval.imag());
				value.type=NFLOAT;
			}
			
			return value;
		}
		case DIFF:
		{
			Number value=vertObj->exec();
			double pos;

			convertToFloat(&value);
			pos=value.fval.real();

			double step=(pos*(double)1e-8);
			if(step<1e-8)
				step=1e-8;
			eventReciver->vars[23][0].type=NFLOAT;
			eventReciver->vars[23][0].fval=Complex(pos-step,0.0);
			Number w1=vertObj4->exec();
			convertToFloat(&w1);
			eventReciver->vars[23][0].fval=Complex(pos+step,0.0);
			Number w2=vertObj4->exec();
			convertToFloat(&w2);
			value.fval=Complex((w2.fval.real()-w1.fval.real())/(2.0*step),0.0);
		
			return value;
		}
		case INTEGRAL:
		{
			bool inv=false;
			Number nstart=vertObj->exec();
			Number nend=vertObj2->exec();
			double start,end;

			convertToFloat(&nstart);
			convertToFloat(&nend);
			start=nstart.fval.real();
			end=nend.fval.real();
			
			if(start>end)
			{
				double temp=start;
				start=end;
				end=temp;
				inv=true;
			}

		double * line1=new double;						//	Romberg's Method
		double *line2=new double[3];
		double y,oldy;
		vars[23]=start;
		oldy=vertObj4->calc();
		vars[23]=end;
		y=vertObj4->calc();
		line1[0]=(y+oldy)*(end-start)/2.0;
		double fail=HUGE_VAL,oldfail=0.0;
		
		int num=1;
		int steps;

		while(true)
		{
			delete[]line2;
			line2=line1;
			line1=new double[num+1];
			line1[0]=0.0;
			
			steps=(int)pow(2.0,(double)(num-1));
			
			for(int c=1; c<=steps; c++)
			{
				vars[23]=start+((2*c-1)*(end-start))/pow(2.0,(double)num);
				line1[0]+=vertObj4->calc();
			}
			line1[0]=0.5*(line1[0]*(end-start)/pow(2.0,(double)(num-1))+line2[0]);
			
			for(int c=2; c<=num+1; c++)
				line1[c-1]=(pow(4.0,(double)(c-1))*line1[c-2]-line2[c-2])/(pow(4.0,(double)(c-1))-1);

			num++;
			oldfail=fail;
			fail=line1[num-1]-line2[num-2];
			if(fail < 0.0)
				fail*=-1.0;
			if(num>16 || (fail < 1e-9))
			{
				if(num>3)					//precision check may not work before that
					break;
			}
			if(fail>oldfail)
			{
				if(num>5)					//error check may not work before that
				{
					line1[num-1]=NAN;
					break;
				}
			}
		}
		value.type=NFLOAT;
		value.fval=Complex((long double)line1[num-1],0.0);
		if(inv)
			value.fval*=Complex(-1.0);
		
		return value;
		}
		case DETERMINANT:
		{
			value=vertObj->exec();
			if(value.type!=NMATRIX)
			{
				convertToFloat(&value);
				return value;
			}
			long double*matrix;
			int size,effIndex;
			if(eventReciver->dimension[value.ival][0]==eventReciver->dimension[value.ival][1])
				size=eventReciver->dimension[value.ival][1];
			else
			{
				value.type=NNONE;
				return value;
			}
			
			matrix=(long double*)malloc(size*size*sizeof(long double));
			
			for(int c1=0; c1<size; c1++)
				for(int c2=0; c2<size; c2++)
			{
				effIndex=c1+c2*eventReciver->dimension[value.ival][0];
				if(effIndex<eventReciver->numlen[value.ival])
				{
					convertToFloat(&eventReciver->vars[value.ival][effIndex]);
					matrix[c1+size*c2]=eventReciver->vars[value.ival][effIndex].fval.real();
				}
			}
			value.type=NFLOAT;
			value.fval=Complex(gauss(size,size,matrix));
			free(matrix);
			return value;
		}
		case SRUN:
		{
			if(eventReciver->subprograms[var]!=NULL)
				return ((Script*)eventReciver->subprograms[var])->exec();
			else 
			{
				value.type=NNONE;
				return value;
			}
		}
		case SBREAK:
		{
			eventReciver->status=1;
			eventReciver->bbreak=true;
			return value;
		}
		case SCONTINUE:
		{
	//		perror("continue");
			eventReciver->status=1;
			eventReciver->bcontinue=true;
			return value;
		}
		case SSTOP:
		{
#ifndef CONSOLE
			QCustomEvent*killEvent=new QCustomEvent(SIGFINISHED);
			QCoreApplication::postEvent(eventReciver->eventReciver,killEvent);
			pthread_exit(0);
#else 
			exit(0);
#endif

			return value;
		}
		case SRAND:
		{
			
			value=vertObj->exec();
			convertToFloat(&value);
			value.type=NFLOAT;
#if RAND_MAX < 1000000000
			value.fval=Complex((((rand()*(1000000000/RAND_MAX))%1000000000)*value.fval.real())/1000000000.0,0.0);
#else
			value.fval=Complex(((rand()%1000000000)*value.fval.real())/1000000000.0,0.0);
#endif
			return value;
		}
		case SCALARPROD:
		{
			value=vertObj->exec();
			Number n;
			if((value.type==NVECTOR || value.type==NMATRIX) &&value.ival==27)
			{
				Number*tmpMem=eventReciver->vars[27];
				int tmpMemLen=eventReciver->numlen[27],tmpDimension1=eventReciver->dimension[27][0],tmpDimension2=eventReciver->dimension[27][1];
				
				eventReciver->vars[27]= (Number*)malloc(sizeof(Number));
				eventReciver->vars[27][0].type=NNONE;
				eventReciver->vars[27][0].cval=NULL;
				eventReciver->dimension[27][0]=eventReciver->dimension[27][1]=eventReciver->numlen[27]=1;
				n=vertObj2->exec();
				
				free(eventReciver->vars[28]);
				eventReciver->vars[28]=tmpMem;
				eventReciver->numlen[28]=tmpMemLen;
				eventReciver->dimension[28][0]=tmpDimension1;
				eventReciver->dimension[28][1]=tmpDimension2;
				value.ival=28;
			}
			else n =vertObj2->exec();
			if(value.type==NVECTOR && n.type==NVECTOR)
			{
				int minlen=eventReciver->dimension[value.ival][0];
				if(eventReciver->dimension[n.ival][0]<minlen)
					minlen=eventReciver->dimension[n.ival][0];

				value.fval=Complex(0.0,0.0);
				for(int c=0; c<minlen;c++)
				{
					convertToFloat(&eventReciver->vars[value.ival][c]);
					convertToFloat(&eventReciver->vars[n.ival][c]);
					value.fval+=eventReciver->vars[value.ival][c].fval*eventReciver->vars[n.ival][c].fval;
				}
				value.type=NFLOAT;
			}
			else {
				value.type=NNONE;
				value.fval=Complex(NAN,0.0);
			}
			
			return value;
		}
		case SFREAD:
		{
			value=vertObj->exec();
			if(value.type!=NCHAR || value.cval==NULL || value.cval[0]==(char)0)
			{
				value.type=NNONE;
				return value;
			}
			int pathlen=strlen(value.cval);
#ifndef CONSOLE
			char*eventContent=(char*)malloc(pathlen+1);
			memcpy(eventContent,value.cval,pathlen+1);
			eventReciver->data=NULL;
			QCustomEvent*fileEvent=new QCustomEvent(SIGFILEREAD);
			fileEvent->setData(eventContent);

			QCoreApplication::postEvent(eventReciver->eventReciver,fileEvent);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;

			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
				{
					eventReciver->exit=false;
					pthread_exit(0);
				}
				usleep(5000);
			}
			int dataLen=strlen((char*)eventReciver->data);
			value.cval=(char*)malloc(dataLen+1);
			memcpy(value.cval,eventReciver->data,dataLen+1);
			free(eventReciver->data);
#else

			char*fileData;
			struct stat fileStat;
			FILE*f;
			if(strlen(value.cval)>0 && lstat(value.cval,&fileStat)==0)
			{
				f=fopen(value.cval,"r");
				if(f!=NULL && fileStat.st_size>0 && S_ISREG(fileStat.st_mode))
				{
					fileData=new char[fileStat.st_size+1];
					fileData[fileStat.st_size]=(char)0;
					fread(fileData,fileStat.st_size,1,f);
					fclose(f);
				}
				else fileData=NULL;
			}
			else fileData=NULL;
				
			if(fileData==NULL)
				value.cval[0]=(char)0;
			else {
				free(value.cval);
				value.cval=fileData;
			}
#endif
			
			
			return value;
		}
		case SFAPPEND:
		{
			value=vertObj->exec();
			if(value.type!=NCHAR || value.cval==NULL)
			{
				value.type=NNONE;
				return value;
			}
			Number n=vertObj2->exec();
			char*eventContent;
			int pathlen=strlen(value.cval);
			if(n.type!=NCHAR)
			{
				convertToFloat(&n);
				eventContent=(char*)malloc(100+pathlen);
				strcpy(eventContent,value.cval);
				sprintf(&eventContent[pathlen+1],"%.*Lg",pref->outputLength,n.fval.real());
			}
			else {
				eventContent=(char*)malloc(strlen(n.cval)+pathlen+2);
				strcpy(eventContent,value.cval);
				strcpy(&eventContent[pathlen+1],n.cval);
			}
#ifndef CONSOLE
			QCustomEvent *ev=new QCustomEvent(SIGFILEAPPEND);
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else

				
			FILE*f;
			if(strlen(value.cval)>0)
			{
				f=fopen(value.cval,"a");
				if(f!=NULL)
				{
					int dataLen=strlen(&((char*)eventContent)[pathlen+1]);
					fwrite(&((char*)eventContent)[pathlen+1],dataLen,1,f);
					fclose(f);
				}
			}
			free(eventContent);
#endif
			
			return value;
		}
		case SFWRITE:
		{
			value=vertObj->exec();
			if(value.type!=NCHAR)
			{
				value.type=NNONE;
				return value;
			}
			Number n=vertObj2->exec();
			char*eventContent;
			int pathlen=strlen(value.cval);
			if(n.type!=NCHAR)
			{
				convertToFloat(&n);
				eventContent=(char*)malloc(100+pathlen);
				strcpy(eventContent,value.cval);
				sprintf(&eventContent[pathlen+1],"%.*Lg",pref->outputLength,n.fval.real());
			}
			else {
				eventContent=(char*)malloc(strlen(n.cval)+pathlen+2);
				strcpy(eventContent,value.cval);
				strcpy(&eventContent[pathlen+1],n.cval);
			}
			
#ifndef CONSOLE
			QCustomEvent *ev=new QCustomEvent(SIGFILEWRITE);
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else

				
			FILE*f;
			if(strlen(value.cval)>0)
			{
				f=fopen(value.cval,"w");
				if(f!=NULL)
				{
					int dataLen=strlen(&((char*)eventContent)[pathlen+1]);
					fwrite(&((char*)eventContent)[pathlen+1],dataLen,1,f);
					fclose(f);
				}
			}
			free(eventContent);
#endif
			
			
			return value;
		}
		case SFREMOVE:
		{
			value=vertObj->exec();
			if(value.type!=NCHAR || value.cval==NULL)
			{
				value.type=NNONE;
				return value;
			}
#ifndef CONSOLE
			char*eventContent=(char*)malloc(strlen(value.cval)+1);
			strcpy(eventContent,value.cval);
			QCustomEvent *ev=new QCustomEvent(SIGFILEREMOVE);
			ev->setData(eventContent);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else
			remove(value.cval);
#endif
			
			return value;
		}
		case SSLEEP:
		{
			value=vertObj->exec();
			int sleeptime;
			if(value.type ==NINT)
				sleeptime=value.ival;
			else sleeptime=(int)value.fval.real();
			if(sleeptime>0)
			{
				usleep(sleeptime);
			}
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SSETCURSOR:
		{
			int*coords=(int*)malloc(sizeof(int)*2);
			value=vertObj->exec();
			if(value.type==NINT)
				coords[0]=value.ival;
			else coords[0]=(int)value.fval.real();
			value=vertObj2->exec();
			if(value.type==NINT)
				coords[1]=value.ival;
			else coords[1]=(int)value.fval.real();
			
			
#ifndef CONSOLE
			QCustomEvent *ev=new QCustomEvent(SIGSETTEXTPOS);
			ev->setData(coords);
			QCoreApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else 
			fprintf(stderr,"\033[%i;%iH",coords[1]+1,coords[0]+1);
#endif

			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SCLEARTEXT:
		{
#ifndef CONSOLE
			QCustomEvent*clearEvent=new QCustomEvent(SIGCLEARTEXT);
			QCoreApplication::postEvent(eventReciver->eventReciver,clearEvent);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else 
			fprintf(stderr,"\033[2J");
			fprintf(stderr,"\033[1;1H");
#endif

			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SGETKEY:
		{
#ifndef CONSOLE
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGGETKEY);

			QCoreApplication::postEvent(eventReciver->eventReciver,clearEvent);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;

			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
				usleep(2000);
			}
			value.cval[0]=*((char*)(eventReciver->data));
			value.fval=Complex((long double)value.cval[0],0.0);
			free(eventReciver->data);
#else 
			value.cval[0]=(char)getchar();
#endif
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SKEYSTATE:
		{
#ifndef CONSOLE
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGKEYSTATE);

			QCoreApplication::postEvent(eventReciver->eventReciver,clearEvent);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;

			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
				usleep(1000);
			}
			value.cval[0]=*((char*)(eventReciver->data));
			value.fval=Complex((long double)value.cval[0],0.0);
			free(eventReciver->data);
#else 
			struct termios terminfo;
			int time,min;
			tcgetattr(fileno(stdout),&terminfo);
			time=terminfo.c_cc[VTIME];
			min=terminfo.c_cc[VMIN];
			terminfo.c_cc[VTIME]=0;
			terminfo.c_cc[VMIN]=0;

			if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
				perror("tcsetattr fehler");
			int key=getchar();
			if(key<=0)
			{
				key=0;
				clearerr(stdin);
			}
			value.cval[0]=(char)key;

			value.fval=(long double)value.cval[0];
			
			terminfo.c_cc[VTIME]=time;
			terminfo.c_cc[VTIME]=min;
			if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
				perror("tcsetattr fehler");
#endif
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SGETLINE:
		{
#ifndef CONSOLE
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGGETLINE);

			QCoreApplication::postEvent(eventReciver->eventReciver,clearEvent);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;

			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
				usleep(5000);
			}
			int dataLen=strlen((char*)eventReciver->data);
			value.cval=(char*)realloc(value.cval,dataLen+1);
			memcpy(value.cval,eventReciver->data,dataLen+1);
			free(eventReciver->data);
#else
			struct termios terminfo;
			tcgetattr(fileno(stdout),&terminfo);
			terminfo.c_lflag |=ECHO;
			terminfo.c_lflag |=ICANON;
			if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
				perror("tcsetattr fehler");
			
			
			char*input=(char*)malloc(1001);
			fgets(input,1000,stdin);

			terminfo.c_lflag &=~ICANON;
			terminfo.c_lflag &=~ECHO;
			if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
				perror("tcsetattr fehler");

			value.cval=(char*)realloc(value.cval,strlen(input));
			memcpy(value.cval,input,strlen(input)-1);
			value.cval[strlen(input)-1]=(char)0;

			free(input);			
			
#endif
			if(horzObj==NULL)
				return value;
			else return horzObj->exec();
		}
		case SINIT:
		{

			if(horzObj!=NULL)
				value=horzObj->exec();
#ifndef CONSOLE
			QCustomEvent*killEvent=new QCustomEvent(SIGFINISHED);
			QCoreApplication::postEvent(eventReciver->eventReciver,killEvent);
#endif
			return value;
		}
		case SFAIL:
		{
			value.type=NNONE;
			value.fval=Complex(NAN);
			return value;
		}
	}
	return value;
}

Number Script::execVertObj()
{
	if(vertObj != NULL)
		return vertObj->exec();
	else return value;
}

Number Script::execHorzObj()
{
	if(horzObj != NULL)
		return horzObj->exec();
	else return value;
}

bool Script::resizeVar(int var,int newlen)
{
	eventReciver->vars[var]=(Number*)realloc(eventReciver->vars[var],sizeof(Number)*(newlen));
	for(int c=eventReciver->numlen[var]; c<newlen; c++)
	{
		eventReciver->vars[var][c].type=NNONE;
		eventReciver->vars[var][c].cval=NULL;
	}
				
	eventReciver->numlen[var]=newlen;
	return true;
}

long double determinant(int size,long double*matrix)
{
	if(size>2)
	{
		long double ret=0.0;
		long double*nextMatrix=(long double*)malloc(sizeof(long double)*(size-1)*(size-1));
		int pos=0;
		for(int c=0; c<size; c++)
		{
			pos=0;
			for(int c2=1; c2<size; c2++)
				for(int c1=0; c1<size; c1++)
			{
				if(c!=c1)
				{
					nextMatrix[pos]=matrix[c1+size*c2];
					pos++;
				}
			}
			if(c%2==0)
				ret+=matrix[c]*determinant(size-1,nextMatrix);
			else ret-=matrix[c]*determinant(size-1,nextMatrix);
		}
		free(nextMatrix);
		return ret;
	}
	else if(size==2)
		return matrix[0]*matrix[3]-matrix[1]*matrix[2];
	else return matrix[0];
}

long double gauss(int sizex,int sizey,long double*matrix)
{
	long double fakt,ret=1.0;
	int offset=0;
	int size=sizex;
	if(size>sizey)
		size=sizey;
	
	for(int c1=0; c1<size; c1++)
	{
		if(matrix[c1*sizey+c1]==0.0)
		{
			int swapIndex=0;
			for(int c2=c1+1; c2<sizey; c2++)
				if(matrix[c1*sizey+c2]!=0.0)
				{
					swapIndex=c2;
					break;
				}
			if(swapIndex==0)
			{
				offset++;
				continue;
			}
			else
			{
				long double tmp;
				for(int c2=0; c2<sizex; c2++)
				{
					tmp=matrix[swapIndex+c2*sizey];
					matrix[swapIndex+c2*sizey]=matrix[c1+c2*sizey];
					matrix[c1+c2*sizey]=tmp;
				}
				ret=-ret;
			}
		}
		for(int c2=c1+1-offset; c2<sizey; c2++)
		{
			fakt=matrix[c1*sizey+c2]/matrix[c1*sizey+c1-offset];
			for(int c3=c1; c3<sizex; c3++)
				matrix[c3*sizey+c2]-=matrix[c3*sizey+c1-offset]*fakt;
		}

	}
	for(int c=0; c<size; c++)
		ret*=matrix[c*size+c];
	return ret;
}

bool invertMatrix(int size,long double*matrix)
{
	long double mainDet;
	long double *result=(long double*)malloc(size*size*sizeof(long double));
	long double *subMatrix=(long double*)malloc((size-1)*(size-1)*sizeof(long double));

	memcpy(result,matrix,size*size*sizeof(long double));

	mainDet=gauss(size,size,result);
	if(mainDet==0.0)
		return false;
	mainDet=1.0/mainDet;
			
			
	int pos1,pos2,effSrcIndex,effDestIndex,vz,effIndex;
	for(int c3=0; c3<size; c3++)
	{
		for(int c4=0; c4<size; c4++)
		{
			effIndex=c3+c4*size;
			pos1=0;
			for(int c1=0; c1<size; c1++)
			{
				if(c1!=c3)
				{
					pos2=0;
					for(int c2=0; c2<size; c2++)
					{
						effDestIndex=pos1+(size-1)*pos2;
						effSrcIndex=c1+c2*size;
						if(c2!=c4)
						{

								subMatrix[effDestIndex]=matrix[effSrcIndex];

							pos2++;
						}
					}
					pos1++;
				}
			}
			vz=(c3+c4)%2;
			if(vz==0)
				vz=1;
			else vz=-1;
			effDestIndex=c4+c3*size;
			long double subDet=gauss(size-1,size-1,subMatrix);
			result[effDestIndex]=mainDet*(long double)vz*subDet;
		}
	}
	memcpy(matrix,result,size*size*sizeof(long double));
	free(result);
	free(subMatrix);

	return true;
}


#ifdef CONSOLE
void printError(const char*string,int semicolonCount,ThreadSync*data)
{
	data->error=true;
	if(data->calcMode)
		return;
	
	int index=semicolonCount-data->countDifference;
	if(index>=data->semicolonLines.GetLen())
		fprintf(stderr,"End of File            : ");
	else 
	{
		if((index>0) && data->semicolonLines[index-1]< data->semicolonLines[index]-1)
			fprintf(stderr,"Before or in line ");
		else fprintf(stderr,"In line           ");
	
		fprintf(stderr,"%5i: ",(data->semicolonLines)[index]);


	}
	
	
	fprintf(stderr,string);
	fprintf(stderr,"\n");
}
#else
void printError(const char*text,int num,ThreadSync*eventReciver)
{
		QCustomEvent*debugEvent=new QCustomEvent(SIGDEBUG);
		char*debugData=(char*)malloc(strlen(text)+5);
		memcpy(debugData,&num,4);
		memcpy(&debugData[4],text,strlen(text)+1);
		debugEvent->setData(debugData);
		QCoreApplication::postEvent(eventReciver->eventReciver,debugEvent);
}
#endif


