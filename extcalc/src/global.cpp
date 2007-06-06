#include "global.h"


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
	return prefName+"="+parameter+"\n";
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

	char*cleanString=checkString(line,pref);
	if(cleanString==NULL)
		return NAN;
	else 
	{
		Calculate ca(NULL,cleanString,pref,vars);
		double result= ca.calc();
		delete[]cleanString;
		return (long double)result;
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



int bracketFind(char* string,char* searchString, int start)
{

	int searchLen=strlen(searchString);
	int bracket=0,brace=0,sqbracket=0;
	bool quote=false;
	for(int c=start; c<(int)strlen(string); c++)
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


int bracketFindRev(char* string,char* searchString, int start)
{
	if(start==-1)
		start=strlen(string)-1;

	int searchLen=strlen(searchString);
	int bracket=0,brace=0,sqbracket=0;
	bool quote=false;
	for(int c=start; c>=0; c--)
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



int Calculate::split(char* line)
{

	if(line==NULL)
		return -1;
	int len=strlen(line);
	if(len <=0)
		return -1;
//	perror("split: "+QString(line));

	if(bracketFind(line," ") != -1)	//none operation
	{
		operation=NONE;
		var=-1;
		number=NAN;
		int pos=bracketFind(line," ");
		char* recString1=new char[pos+1];
		char* recString2=new char[len-pos];
		strcopy(recString1,line,pos);
		strcopy(recString2,&line[pos+1],len-pos-1);
		horzObj=new Calculate(this,recString1,pref,vars);
		vertObj=new Calculate(this,recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return 0;
	}
	else if(bracketFind(line,"+") != -1 || bracketFind(line,"-") != -1)
	{
		int pos1,pos2,pos=-1;
		while(true)
		{
			pos1=bracketFindRev(line,"+",pos);
			if(pos1<=0)
				break;
			if(line[pos1-1]=='e')
				pos=pos1-1;
			else break;
		}
		pos=-1;
		while(true)
		{
			pos2=bracketFindRev(line,"-",pos);
			if(pos2<=0)
				break;
			if(line[pos2-1]=='e')
				pos=pos2-1;
			else break;
		}
		
		if(pos2>pos1)
		{
			if(pos2>0 && (line[pos2-1] >='A' && line[pos2-1]<='Z'					//binary - operator
			   || line[pos2-1]>='0' && line[pos2-1]<='9'
			   || line[pos2-1]=='.' || line[pos2-1]==')'|| line[pos2-1]==']'))
			{
				pos=pos2;
				number=NAN;
				var=-1;
				operation=MINUS;
				char*recString2=new char[len-pos];
				strcopy(recString2,&line[pos+1],len-pos-1);
				horzObj=new Calculate(this,recString2,pref,vars);
				delete[]recString2;
				char*recString1=new char[pos+1];
				strcopy(recString1,line,pos);
				vertObj=new Calculate(this,recString1,pref,vars);
				delete[]recString1;
				return 0;
			}
			else if(pos2==0)										//unary - operator
			{
				operation=MINUS;
				var=-1;
				number=NAN;
				vertObj=NULL;
				horzObj=new Calculate(this,&line[1],pref,vars);
				return 0;
			}
		}
		else if(pos1>pos2)
		{
			if(pos1>0 && (line[pos1-1] >='A' && line[pos1-1]<='Z'					//binary + operator
						 || line[pos1-1]>='0' && line[pos1-1]<='9'
						 || line[pos1-1]=='.' || line[pos1-1]==')' || line[pos1-1]==']'))
			{
				pos=pos1;
				number=NAN;
				var=-1;
				operation=PLUS;
				char*recString2=new char[len-pos];
				strcopy(recString2,&line[pos+1],len-pos-1);
				horzObj=new Calculate(this,recString2,pref,vars);
				delete[]recString2;
				char*recString1=new char[pos+1];
				strcopy(recString1,line,pos);
				vertObj=new Calculate(this,recString1,pref,vars);
				delete[]recString1;
				return 0;
			}
			else if(pos1==0)										//unary + operator
			{
				operation=PLUS;
				var=-1;
				number=NAN;
				vertObj=NULL;
				horzObj=new Calculate(this,&line[1],pref,vars);
				return 0;
			}

		}
	}
	if(bracketFind(line,"*") != -1 || bracketFind(line,"/") != -1)
	{
		int pos1=bracketFindRev(line,"*");
		int pos2=bracketFindRev(line,"/");
		if(pos1==-1 && pos2==-1)
			return -1;
		int pos;
		if((pos2>pos1 && pos2 != -1) || pos1==-1)
		{
			pos=pos2;
			var=-1;
			operation=DIVIDE;
			char*recString1=new char[pos+1];
			char*recString2=new char[len-pos];
			strcopy(recString1,line,pos);
			strcopy(recString2,&line[pos+1],len-pos-1);
			horzObj=new Calculate(this,recString2,pref,vars);
			vertObj=new Calculate(this,recString1,pref,vars);
			delete[]recString1;
			delete[]recString2;
			return 0;
		}
		else
		{
			pos=pos1;
			var=-1;
			operation=MULT;
			char*recString1=new char[pos+1];
			char*recString2=new char[len-pos];
			strcopy(recString1,line,pos);
			strcopy(recString2,&line[pos+1],len-pos-1);
			horzObj=new Calculate(this,recString2,pref,vars);
			vertObj=new Calculate(this,recString1,pref,vars);
			delete[]recString1;
			delete[]recString2;
			return 0;
		}
	}
	else if(bracketFind(line,"%") != -1)
	{
		number=NAN;
		operation=MODULO;
		var=-1;
		int pos=bracketFind(line,"%");
		char*recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		char*recString2=new char[len-pos];
		strcopy(recString2,&line[pos+1],len-pos-1);
		vertObj=new Calculate(this,recString1,pref,vars);
		horzObj=new Calculate(this,recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return 0;
		
		
	}
	else if(bracketFind(line,"^") != -1)
	{
		int pos1=bracketFindRev(line,"^");
		number=NAN;
		operation=POW;
		var=-1;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Calculate(this,recString1,pref,vars);
		horzObj=new Calculate(this,recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return 0;
	}
	else if(bracketFind(line,"$r") != -1)	//	root operation for extcalc (binary operator)
	{
		operation=ROOT;
		var=-1;
		number=NAN;
		int pos=bracketFind(line,"$r");
		char* recString1=new char[pos+1];
		char* recString2=new char[len-pos-1];
		strcopy(recString1,line,pos);
		strcopy(recString2,&line[pos+2],len-pos-2);
		vertObj=new Calculate(this,recString1,pref,vars);
		horzObj=new Calculate(this,recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return 0;
	}
	else if(line[0]>='a' && line[0]<='z') 
	{
		horzObj=NULL;
		var=-1;
		if(pref->angle==DEG)
			number=180.0/(long double)PI;
		else if(pref->angle==RAD)
			number=1.0;
		else number=200.0/(long double)PI;
		if(strncmp("asinh",line,5) == 0)
		{
			operation=ASINH;
			vertObj=new Calculate(this,&line[5],pref,vars);
		}
		else if(strncmp("acosh",line,5) == 0)
		{
			operation=ACOSH;
			vertObj=new Calculate(this,&line[5],pref,vars);
		}
			else if(strncmp("atanh",line,5) == 0)
		{
			operation=ATANH;
			vertObj=new Calculate(this,&line[5],pref,vars);
		}
		else if(strncmp("asin",line,4) == 0)
		{
			operation=ASIN;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp("acos",line,4) == 0)
		{
			operation=ACOS;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp("atan",line,4) == 0)
		{
			operation=ATAN;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp("sinh",line,4) == 0)
		{
			operation=SINH;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp("cosh",line,4) == 0)
		{
			operation=COSH;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp("tanh",line,4) == 0)
		{
			operation=TANH;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp("sin",line,3) == 0)
		{
			operation=SIN;
			vertObj=new Calculate(this,&line[3],pref,vars);
		}
		else if(strncmp("cos",line,3) == 0)
		{
			operation=COS;
			vertObj=new Calculate(this,&line[3],pref,vars);
		}
		else if(strncmp("tan",line,3) == 0)
		{
			operation=TAN;
			vertObj=new Calculate(this,&line[3],pref,vars);
		}
		else if(strncmp("log",line,3) == 0)
		{
			operation=LG;
			vertObj=new Calculate(this,&line[3],pref,vars);
		}
		else if(strncmp("ln",line,2) == 0)
		{
			operation=LN;
			vertObj=new Calculate(this,&line[2],pref,vars);
		}
		else if(strncmp(line,"sqrt",4) == 0)
		{
			operation=SQRT;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else if(strncmp(line,"curt",4) == 0)
		{
			operation=CURT;
			vertObj=new Calculate(this,&line[4],pref,vars);
		}
		else{
			operation=NONE;
			number=NAN;
			return -1;
		}

		return 0;
	}
	/*	else if(bracketFind(line,"$r(") != -1)		//root operation for calc (operator with arguments)
	{
		// syntax: fourth root of nine: root(4,9)
		operation=ROOT;
		var=-1;
		number=NAN;
		int pos1=bracketFind(line,"$r(");
		pos1+=3;
		int pos2=bracketFind(line,",",pos1);
		if(pos1==-1 || pos2 == -1 || line[len-1]!=')')
		return (NAN);
			
		char* recString1=new char[pos2-pos1+1];
		char* recString2=new char[len-pos2-1];
		strcopy(recString1,&line[pos1],pos2-pos1);
		strcopy(recString2,&line[pos2+1],len-pos2-2);
			
		vertObj=new Calculate(this,recString1,pref,vars);
		horzObj=new Calculate(this,recString2,pref,vars);
		
		delete[]recString1;
		delete[]recString2;
		return 0;
	}*/
	else if(bracketFind(line,"\\d(") != -1)
	{
		operation=DIFF;
		number=NAN;
		var=-1;
		int pos1=bracketFind(line,",",3);
		if(pos1<0 || pos1>len-2)
			return -1;
		char* function=new char[pos1-2];
		char* startStr=new char[len-pos1-1];
		strcopy(function,&line[3],pos1-3);
		strcopy(startStr,&line[pos1+1],len-pos1-2);


		horzObj=new Calculate(this,function,pref,vars);
		vertObj=new Calculate(this,startStr,pref,vars);
		delete[]function;
		delete[]startStr;
		return 0;
	}
	else if(bracketFind(line,"\\i(") != -1)
	{
		operation=INTEGRAL;
		number=NAN;
		var=-1;
		int pos1=bracketFind(line,",",3);
		if(pos1==-1)
			return-1;
		int pos2=bracketFind(line,",",pos1+1);
		if(pos2==-1)
			return -1;
		char *function=new char[pos1-2];
		char *parStr=new char[len-pos1+2];

		strcopy(function,&line[3],pos1-3);
		strcopy(parStr,&line[pos1+1],pos2-pos1-1);
		parStr[pos2-pos1-1]=' ';
		strcopy(&parStr[pos2-pos1],&line[pos2+1],len-pos2-2);
		horzObj=new Calculate(this,function,pref,vars);
		vertObj=new Calculate(this,parStr,pref,vars);
		delete[]function;
		delete[]parStr;
		return 0;
	}
	else if(line[0]=='(')
	{
		number=NAN;
		operation=NONE;
		var=-1;
		char*recString1;
		if(len>0 && line[len-1] == ')')
		{
			recString1=new char[len-1];
			strcopy(recString1,&line[1],len-2);
		}
		else 
		{
			recString1=new char[len];
			strcopy(recString1,&line[1],len-1);
		}
		horzObj=new Calculate(this,recString1,pref,vars);
		delete[]recString1;
		vertObj=NULL;
		
		return 0;
	}
	else if(line[0]>='A' && line[0]<='Z')
	{
		
		number=NAN;
		vertObj=NULL;
		var=((int)line[0])-65;
		
		if(len>1)
			var=-1;
		else 
		{
			operation=NONE;
			horzObj=NULL;
		}
	}
	else{
		operation=NONE;
		number=strtod(line,NULL);
		var=-1;
		horzObj=NULL;
		vertObj=NULL;
		if(number==NAN)
			return -1;
		else return 0;
//		 line.toDouble();
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
			else if(number!=NAN)
			{
				return number;
			}
			else 
			{
				return NAN;
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


int Script::split(char*line)
{
	bool init=false;
	char*rest;
	if(parent==NULL)
	{
		value.type=NNONE;
		operation=SINIT;
		rest=line;
		init=true;
		parse(NULL);
	}
	else rest=parse(line);

	if(rest!=NULL)
	{
		nextObj=new Script(this,NULL,pref,vars,eventReciver);
		nextObj->split(rest);
		if(parent!=NULL)
			delete[]rest;
	}
	return 0;
}


char* Script::parse(char* line)
{
	static int semicolonCount=0;
	if(line==NULL)
	{
		semicolonCount=0;
		return NULL;
	}
	
//	perror(line);
	int pos1;
	int len=strlen(line);

	
	if(line[0]== '{' && bracketFind(line,"}")==len-1 || line[0]== '(' && bracketFind(line,")")==len-1)
	{
		line[len-1]=(char)0;
		line++;
		len-=2;
		split(line);
		return NULL;
	}
//	static int commands=0;
//	perror("Commands: "+QString::number(commands++));
//	perror("line after bracket: "+QString(line));
	
	//programming language structures
	if((pos1=bracketFind(line,"if(")) == 0)
	{
		int pos2=bracketFind(line,")");
		if(pos2<3 || len<pos2+2)
		{
			printError("No closing bracket for if found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-2];
		strcopy(recString1,&line[3],pos2-3);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[] recString1;
		
		char*recString2=new char[len-pos2];
		strcopy(recString2,&line[pos2+1],len-pos2-1);
		vertObj2=new Script(this,NULL,pref,vars,eventReciver);
		char*rest=vertObj2->parse(recString2);
		delete[]recString2;
		if(rest==NULL)
		{
			operation=SIF;
			return NULL;
		}

		if(strncmp(rest,"else",4)==0)
		{
			operation=SIFELSE;
			char*recString3=new char[strlen(rest)-3];
			strcopy(recString3,&rest[4],strlen(rest)-4);
			delete[]rest;
			vertObj3=new Script(this,NULL,pref,vars,eventReciver);
			rest=vertObj3->parse(recString3);
			delete[]recString3;
		}
		else operation=SIF;
		
		return rest;
	}
	else if((pos1=bracketFind(line,"while(")) == 0)
	{
		operation=SWHILE;
		int pos2=bracketFind(line,")");
		if(pos2<7)
		{
			printError("No closing bracket for while found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		char*recString1=new char[pos2-5];
		strcopy(recString1,&line[6],pos2-6);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		char*recString2=new char[len-pos2];
		strcopy(recString2,&line[pos2+1],len-pos2-1);

		vertObj2=new Script(this,NULL,pref,vars,eventReciver);
		char*rest=vertObj2->parse(recString2);
		delete[]recString2;
		
		return rest;
	}
	else if((pos1=bracketFind(line,"for(")) == 0)
	{
		
		operation=SFOR;
		int pos2=bracketFind(line,";",4);
		int pos3=bracketFind(line,";",pos2+1);
		int pos4=bracketFind(line,")",3);
		if(pos2<4 || pos3<5 || pos4<6)
		{
			printError("Invalid usage of for",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		
		char*recString1=new char[pos2-2];
		strcopy(recString1,&line[4],pos2-3);
		char*recString2=new char[pos3-pos2+1];
		strcopy(recString2,&line[pos2+1],pos3-pos2);
		
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		
		delete[]recString1;
		delete[]recString2;
		if(pos4-pos3>1)
		{
			char*recString3=new char[pos4-pos3];
			strcopy(recString3,&line[pos3+1],pos4-pos3-1);
			vertObj3=new Script(this,recString3,pref,vars,eventReciver);
			delete[]recString3;
		}
		else vertObj3=NULL;
		
		if(len-pos4<2)
		{
			printError("For-loop has no body",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString4=new char[len-pos4];
		strcopy(recString4,&line[pos4+1],len-pos4-1);
		horzObj=new Script(this,NULL,pref,vars,eventReciver);
		char*rest=horzObj->parse(recString4);
//		perror("for rest: "+QString(rest));
		delete[]recString4;
		
		return rest;
	}
	else if(line[0] == '{')
	{
//		perror("another bracket");
		operation=SBRACKET;
		int pos1=bracketFind(line,"}");
		if(pos1<1)
		{
			printError("No closing bracket for { found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos1];
		strcopy(recString1,&line[1],pos1-1);
		vertObj=new Script(this,NULL,pref,vars,eventReciver);
		vertObj->split(recString1);
		delete[]recString1;
		if(pos1==len-1)
		{
//			perror("bracket returns 0");
			return NULL;
		}
		else {
			char*recString2=new char[len-pos1];
			strcopy(recString2,&line[pos1+1],len-pos1-1);
//			perror("bracket return: "+QString(recString2));
			return recString2;
		}
	}
	//operators
	else if((pos1=bracketFind(line,";")) != -1)
	{
//		perror("semicolon");
		operation=SSEMICOLON;
		char*recString1=new char[pos1+1];
		strcopy(recString1,line,pos1);
		if(pos1>0)
			vertObj=new Script(this,recString1,pref,vars,eventReciver);
		else vertObj=NULL;
		delete[]recString1;
	//	printError("Strichpunkt gefunden",semicolonCount,eventReciver->eventReciver);
		semicolonCount++;
		
		
		if(len-pos1>1)
		{
			char*recString2=new char[len-pos1];
			strcopy(recString2,&line[pos1+1],len-pos1-1);
			return recString2;
		}
		else return NULL;

	}
	else if((pos1=bracketFind(line,"&&")) != -1)
	{

		operation=SAND;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"||")) != -1)
	{

		operation=SOR;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"->")) != -1)
	{
		operation=SSET;
		char*recString2;
		vertObj2=vertObj3=NULL;
		int pos2=0;
		if(pos1!=len-3)
		{
			if(line[pos1+3]=='[' && line[len-1]==']' && len-pos1!=4)
			{
				if((pos2=bracketFindRev(line,"["))!=-1)
				{
					if(line[pos2-1]!=']')
					{
						printError("No closing brace for set operation found",semicolonCount,eventReciver->eventReciver);
						operation=SFAIL;
						return NULL;
					}
					recString2=new char[pos2-pos1-4];
					char*recString3=new char[len-pos2-1];
					strcopy(recString2,&line[pos1+4],pos2-pos1-5);
					strcopy(recString3,&line[pos2+1],len-pos2-2);
					vertObj2=new Script(this,recString2,pref,vars,eventReciver);
					vertObj3=new Script(this,recString3,pref,vars,eventReciver);
				//	perror(QString("arrow index: ")+recString2);
					delete[]recString2;
					delete[]recString3;
					
				}
				else {
					recString2=new char[len-pos1-4];
					strcopy(recString2,&line[pos1+4],len-pos1-5);
					vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			//		perror(QString("arrow index: ")+recString2);
					delete[]recString2;
				}
			}
			else {
				printError("Right operand of set operation invalid",semicolonCount,eventReciver->eventReciver);
				operation=SFAIL;
				return NULL;
			}
		}
		char*recString1=new char[pos1+1];
		strcopy(recString1,line,pos1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);

			
		var=line[pos1+2]-65;
		if(var<0 || var>25)
		{
			printError("Invalid variable for set operation",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			delete[]recString1;
			return NULL;
		}
		//eventReciver->numlen[var]=1;
		delete[]recString1;
		return NULL;
	}
	else if(bracketFind(line,"==") != -1)
	{
		pos1=bracketFindRev(line,"==")-1;
		operation=SCOMPARE;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,"!=") != -1)
	{
		pos1=bracketFindRev(line,"!=")-1;
		operation=SUNEQUAL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,">=") != -1)
	{
		pos1=bracketFindRev(line,">=")-1;
		operation=SGREQ;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,"<=") != -1)
	{
		pos1=bracketFindRev(line,"<=")-1;
		operation=SLESSEQ;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,">")) != -1 && line[pos1+1]!='>')
	{
		operation=SGREATHER;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"<")) != -1 && line[pos1+1]!='<')
	{
		operation=SLESS;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"=")) != -1)
	{
		operation=SSET;
		char*recString1=new char[len-pos1];
		strcopy(recString1,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		vertObj2=vertObj3=NULL;
		int pos2=0;
		if(pos1!=1)
		{
			if(line[1]=='[' && line[pos1-1]==']')
			{
				if((pos2=bracketFind(line,"]")) !=pos1-1)
				{
					if(line[pos2+1]!='[')
					{
						printError("Closing brace for set operation not found",semicolonCount,eventReciver->eventReciver);
						operation=SFAIL;
						return NULL;
					}
					char*recString2=new char[pos2-1];
					char*recString3=new char[pos1-pos2-2];
					strcopy(recString2,&line[2],pos2-2);
					strcopy(recString3,&line[pos2+2],pos1-pos2-3);
					vertObj2=new Script(this,recString2,pref,vars,eventReciver);
					vertObj3=new Script(this,recString3,pref,vars,eventReciver);
	//				perror(QString("set index: ")+recString2);
					delete[]recString2;
					delete[]recString3;
				}
				else {
					char*recString2=new char[pos1-2];
					strcopy(recString2,&line[2],pos1-3);
					vertObj2=new Script(this,recString2,pref,vars,eventReciver);
	//				perror(QString("set index: ")+recString2);
					delete[]recString2;
				}
			}
			else {
				printError("Left operand of set operation invalid",semicolonCount,eventReciver->eventReciver);
				operation=SFAIL;
				return NULL;
			}
			
		}
		var=line[0]-65;
		if(var<0 || var>25)
		{
			printError("Invalid variable for set operation",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
//		eventReciver->numlen[var]=1;
		return NULL;
	}
	pos1=0;
	while((pos1=bracketFind(line,"+",pos1)) != -1)
	{
		if(pos1>1 && line[pos1-1]=='e')
		{
			pos1++;
			continue;
		}
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of + invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of + invalid",semicolonCount,eventReciver->eventReciver);
		else operation=PLUS;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	pos1=-1;
	while((pos1=bracketFindRev(line,"-",pos1)) != -1)
	{		
		if(pos1>1 && !(line[pos1-1]>='A' && line[pos1-1]<='Z' || line[pos1-1]>='0' && line[pos1-1]<='9' || line[pos1-1]=='i' || line[pos1-1]==')'||line[pos1-1]==']'|| line[pos1-1]=='!') )
		{
			pos1--;
			continue;
		}
		operation=MINUS;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	if((pos1=bracketFindRev(line,"*")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of * invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of * invalid",semicolonCount,eventReciver->eventReciver);
		else operation=MULT;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFindRev(line,"/")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of / invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of / invalid",semicolonCount,eventReciver->eventReciver);
		else {
			if(pref->complex)
				operation=CDIVIDE;
			else operation=DIVIDE;
		}
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,"$s") != -1)
	{
		pos1=bracketFindRev(line,"$s")-1;
		operation=SFAIL;
		if(pos1<1)
			printError("First operand of root invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<3)
			printError("Second operand of root invalid",semicolonCount,eventReciver->eventReciver);
		else {
			operation=SCALARPROD;
		}
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];

		
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}	
	else if((pos1=bracketFind(line,"%")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of % invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of % invalid",semicolonCount,eventReciver->eventReciver);
		else operation=MODULO;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,">>") != -1)
	{
		pos1=bracketFind(line,">>");
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		if(pos1<1)
			printError("First operand of >> invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<3)
			printError("Second operand of >> invalid",semicolonCount,eventReciver->eventReciver);
		else operation=RSHIFT;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,"<<") != -1)
	{
		pos1=bracketFind(line,"<<");
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];
		if(pos1<1)
			printError("First operand of << invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<3)
			printError("Second operand of << invalid",semicolonCount,eventReciver->eventReciver);
		else operation=LSHIFT;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"x")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of x invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of x invalid",semicolonCount,eventReciver->eventReciver);
		else operation=XOR;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"&")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of & invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of & invalid",semicolonCount,eventReciver->eventReciver);
		else operation=SBAND;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"|")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of | invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of | invalid",semicolonCount,eventReciver->eventReciver);
		else operation=SBOR;
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"!"))!=-1)
	{
		vertObj2=vertObj3=horzObj=nextObj=NULL;
		char*recString1=new char[len];
		if(pos1<=0)
		{
			if(len>1)
			{
				operation=SNOT;
				strcopy(recString1,&line[1],len-1);
			}
			else {
				operation=SFAIL;
				printError("No argument for ! set",semicolonCount,eventReciver->eventReciver);
			}
		}
		else {
				operation=SFAK;
				strcopy(recString1,line,len-1);
				
		}
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"print(")) == 0)
	{
//		perror("print");
		operation=SPRINT;
		int pos2=bracketFind(line,")");
		if(pos2<7)
		{
			printError("Closing bracket for print not found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-5];
		strcopy(recString1,&line[6],pos2-6);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;

		return NULL;
	}
	else if((pos1=bracketFind(line,"clear")) == 0)
	{
//		perror("clear");
		operation=SCLEARTEXT;
		return NULL;
	}
	else if((pos1=bracketFind(line,"setcursor(")) == 0)
	{
//		perror("setcursor");
		operation=SSETCURSOR;
		int pos2=bracketFind(line,",",10);
		int pos3=bracketFindRev(line,")");
		if(pos2<11 || pos3<12 || pos3<pos2)
		{
			printError("Invalid use of setcursor",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-9];
		strcopy(recString1,&line[10],pos2-10);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		char*recString2=new char[pos3-pos2];
		strcopy(recString2,&line[pos2+1],pos3-pos2-1);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;

		return NULL;
	}
	else if((pos1=bracketFind(line,"sleep(")) == 0)
	{
//		perror("sleep");
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SSLEEP;
		int pos2=bracketFind(line,")");
		if(pos2<7)
		{
			printError("No closing bracket for sleep found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-5];
		strcopy(recString1,&line[6],pos2-6);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"rnd(")) == 0)
	{
		operation=SRAND;
		value.type=NFLOAT;
		if(line[len-1]!=')')
		{
			printError("No closing bracket for rnd found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[len-pos1-4];
		strcopy(recString1,&line[4],len-pos1-5);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"readfile(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SFREAD;
		int pos2=bracketFind(line,")");
		if(pos2<10)
		{
			printError("Closing bracket for readfile not found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-8];
		strcopy(recString1,&line[9],pos2-9);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;

		return NULL;
	}
	else if((pos1=bracketFind(line,"writefile(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SFWRITE;
		var=-1;
		int pos1=bracketFind(line,",",10);
		if(pos1<11 || pos1>len-2)
		{
			printError("Invalid use of writefile",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char* filename=new char[pos1-9];
		char* input=new char[len-pos1-1];
		strcopy(filename,&line[10],pos1-10);
		strcopy(input,&line[pos1+1],len-pos1-2);


		vertObj=new Script(this,filename,pref,vars,eventReciver);
		vertObj2=new Script(this,input,pref,vars,eventReciver);
		delete[]input;
		delete[]filename;
		return NULL;
	}
	else if((pos1=bracketFind(line,"removefile(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SFREMOVE;
		int pos2=bracketFind(line,")");
		if(pos2<12)
		{
			printError("Closing bracket for removefile not found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-10];
		strcopy(recString1,&line[11],pos2-11);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;

		return NULL;
	}
	else if((pos1=bracketFind(line,"appendfile(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SFAPPEND;
		var=-1;
		int pos1=bracketFind(line,",",11);
		if(pos1<12 || pos1>len-2)
		{
			printError("Invalid use of appendfile",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char* filename=new char[pos1-10];
		char* input=new char[len-pos1-1];
		strcopy(filename,&line[11],pos1-11);
		strcopy(input,&line[pos1+1],len-pos1-2);

		vertObj=new Script(this,filename,pref,vars,eventReciver);
		vertObj2=new Script(this,input,pref,vars,eventReciver);
		delete[]input;
		delete[]filename;
		return NULL;
	}
	else if((pos1=bracketFind(line,"glbegin(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHPAINT;
		int pos2=bracketFind(line,")");
		if(pos2<9)
		{
			printError("Closing bracket for glbegin not found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-7];
		strcopy(recString1,&line[8],pos2-8);
		if(strcmp(recString1,"points")==0)
			value.ival=0;
		else if(strcmp(recString1,"lines")==0)
			value.ival=1;
		else if(strcmp(recString1,"linestrip")==0)
			value.ival=2;
		else if(strcmp(recString1,"lineloop")==0)
			value.ival=3;
		else if(strcmp(recString1,"triangles")==0)
			value.ival=4;
		else if(strcmp(recString1,"trianglestrip")==0)
			value.ival=5;
		else if(strcmp(recString1,"trianglefan")==0)
			value.ival=6;
		else if(strcmp(recString1,"quads")==0)
			value.ival=7;
		else if(strcmp(recString1,"quadstrip")==0)
			value.ival=8;
		else if(strcmp(recString1,"polygon")==0)
			value.ival=9;
		else{
			printError("Invalid argument in glbegin",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		delete[]recString1;
		
		return NULL;
	}
	else if((pos1=bracketFind(line,"glendlist")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHLIST;
		var=2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"glend")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHCONTROL;
			var=2;
		return NULL;
	}
	else if((pos1=bracketFind(line,"glshow")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHCONTROL;
		var=0;
		return NULL;
	}
	else if((pos1=bracketFind(line,"glclear")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHCONTROL;
		var=1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"glloadidentity")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHCONTROL;
		var=3;
		return NULL;
	}
	else if((pos1=bracketFind(line,"glstartlist")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHLIST;
		var=1;
		return NULL;
	}

	else if((pos1=bracketFind(line,"glcalllist(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHLIST;
		var=0;
		int pos2=bracketFind(line,")");
		if(pos2<12)
		{
			printError("Closing bracket for glcalllist not found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-10];
		strcopy(recString1,&line[11],pos2-11);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;

		return NULL;
	}
	else if(bracketFind(line,"glpoint(") == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHVERTEX;
		int pos1=bracketFind(line,",",8);

		int pos2=bracketFind(line,",",pos1+1);
		if(pos1==-1 || pos2==-1)
		{
			printError("Invalid use of glpoint",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}

		char *xval=new char[pos1-7];
		char *yval=new char[pos2-pos1];
		char *zval=new char[len-pos2-1];

		strcopy(xval,&line[8],pos1-8);
		strcopy(yval,&line[pos1+1],pos2-pos1-1);
		strcopy(zval,&line[pos2+1],len-pos2-2);
		vertObj=new Script(this,xval,pref,vars,eventReciver);
		vertObj2=new Script(this,yval,pref,vars,eventReciver);
		vertObj3=new Script(this,zval,pref,vars,eventReciver);
		delete[]xval;
		delete[]yval;
		delete[]zval;
		return NULL;
	}
	else if(bracketFind(line,"glscale(") == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHTRANSFORM;
		var=0;
		int pos1=bracketFind(line,",",8);

		int pos2=bracketFind(line,",",pos1+1);
		if(pos1==-1 || pos2==-1)
		{
			printError("Invalid use of glscale",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}

		char *xval=new char[pos1-7];
		char *yval=new char[pos2-pos1];
		char *zval=new char[len-pos2-1];

		strcopy(xval,&line[8],pos1-8);
		strcopy(yval,&line[pos1+1],pos2-pos1-1);
		strcopy(zval,&line[pos2+1],len-pos2-2);
		vertObj=new Script(this,xval,pref,vars,eventReciver);
		vertObj2=new Script(this,yval,pref,vars,eventReciver);
		vertObj3=new Script(this,zval,pref,vars,eventReciver);
		delete[]xval;
		delete[]yval;
		delete[]zval;
		return NULL;
	}
	else if(bracketFind(line,"glmove(") == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHTRANSFORM;
		var=1;
		int pos1=bracketFind(line,",",7);

		int pos2=bracketFind(line,",",pos1+1);
		if(pos1==-1 || pos2==-1)
		{
			printError("Invalid use of glmove",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}

		char *xval=new char[pos1-6];
		char *yval=new char[pos2-pos1];
		char *zval=new char[len-pos2-1];

		strcopy(xval,&line[7],pos1-7);
		strcopy(yval,&line[pos1+1],pos2-pos1-1);
		strcopy(zval,&line[pos2+1],len-pos2-2);
		vertObj=new Script(this,xval,pref,vars,eventReciver);
		vertObj2=new Script(this,yval,pref,vars,eventReciver);
		vertObj3=new Script(this,zval,pref,vars,eventReciver);
		delete[]xval;
		delete[]yval;
		delete[]zval;
		return NULL;
	}
	else if(bracketFind(line,"glrotate(") == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHTRANSFORM;
		var=2;
		int pos1=bracketFind(line,",",9);

		int pos2=bracketFind(line,",",pos1+1);
		int pos3=bracketFind(line,",",pos2+1);
		if(pos1==-1 || pos2==-1 || pos3==-1)
		{
			printError("Invalid use if glrotate",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char *angle=new char[pos1-8];
		char *xval=new char[pos2-pos1];
		char *yval=new char[pos3-pos2];
		char *zval=new char[len-pos3-1];
		
		strcopy(angle,&line[9],pos1-9);
		strcopy(xval,&line[pos1+1],pos2-pos1-1);
		strcopy(yval,&line[pos2+1],pos3-pos2-1);
		strcopy(zval,&line[pos3+1],len-pos3-2);
		
		horzObj=new Script(this,angle,pref,vars,eventReciver);
		vertObj=new Script(this,xval,pref,vars,eventReciver);
		vertObj2=new Script(this,yval,pref,vars,eventReciver);
		vertObj3=new Script(this,zval,pref,vars,eventReciver);
		delete[]angle;
		delete[]xval;
		delete[]yval;
		delete[]zval;
		return NULL;
	}
	else if(bracketFind(line,"glcolor(") == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHCOLOR;
		int pos1=bracketFind(line,",",8);

		int pos2=bracketFind(line,",",pos1+1);
		if(pos1==-1 || pos2==-1)
		{
			printError("Invalid use of glcolor",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}

		char *xval=new char[pos1-7];
		char *yval=new char[pos2-pos1];
		char *zval=new char[len-pos2-1];

		strcopy(xval,&line[8],pos1-8);
		strcopy(yval,&line[pos1+1],pos2-pos1-1);
		strcopy(zval,&line[pos2+1],len-pos2-2);
		vertObj=new Script(this,xval,pref,vars,eventReciver);
		vertObj2=new Script(this,yval,pref,vars,eventReciver);
		vertObj3=new Script(this,zval,pref,vars,eventReciver);
		delete[]xval;
		delete[]yval;
		delete[]zval;
		return NULL;
	}
	else if(bracketFind(line,"glstring(") == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SGRAPHTEXT;
		var=2;
		int pos1=bracketFind(line,",",9);

		int pos2=bracketFind(line,",",pos1+1);
		if(pos1==-1 || pos2==-1)
		{
			printError("Invalid use of glstring",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char *xval=new char[pos1-8];
		char *yval=new char[pos2-pos1];
		char *text=new char[len-pos2-1];
		
		strcopy(xval,&line[9],pos1-9);
		strcopy(yval,&line[pos1+1],pos2-pos1-1);
		strcopy(text,&line[pos2+1],len-pos2-2);
		
		horzObj=new Script(this,text,pref,vars,eventReciver);
		vertObj=new Script(this,xval,pref,vars,eventReciver);
		vertObj2=new Script(this,yval,pref,vars,eventReciver);
		delete[]text;
		delete[]xval;
		delete[]yval;
		return NULL;
	}
	else if((pos1=bracketFind(line,"run(")) == 0)
	{
		if(eventReciver->calcMode)
		{
			printError("Operation not allowed in calculator mode",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		operation=SRUN;
		
		if(line[len-1]!=')')
		{
			printError("No closing bracket for run found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		if(line[len-2]!='\"' || line[4]!='\"')
		{
			printError("Filename in run must be quoted",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[len-pos1-6];
		strcopy(recString1,&line[5],len-pos1-7);
		var=-1;
		for(int c=0; c<eventReciver->subprogramPath.GetLen(); c++)
			if(strcmp(eventReciver->subprogramPath[c],recString1)==0)
			{
				var=c;
				break;
			}
		if(var==-1)
		{
			printError("File for run does not exist",semicolonCount,eventReciver->eventReciver);
			delete[]recString1;
			operation=SFAIL;
			return NULL;
		}
		delete[]recString1;
		return NULL;
	}
	else if(bracketFind(line,"\\d(") != -1)
	{
		operation=DIFF;
		var=-1;
		int pos1=bracketFind(line,",",3);
		if(pos1<0 || pos1>len-2)
		{
			printError("Invalid use if d/dx",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		char* function=new char[pos1-2];
		char* startStr=new char[len-pos1-1];
		strcopy(function,&line[3],pos1-3);
		strcopy(startStr,&line[pos1+1],len-pos1-2);


		horzObj=new Script(this,function,pref,vars,eventReciver);
		vertObj=new Script(this,startStr,pref,vars,eventReciver);
		delete[]function;
		delete[]startStr;
		return NULL;
	}
	else if(bracketFind(line,"\\i(") != -1)
	{
		operation=INTEGRAL;
		var=-1;
		int pos1=bracketFind(line,",",3);

		int pos2=bracketFind(line,",",pos1+1);
		if(pos1==-1 || pos2==-1)
		{
			printError("Invalid use if integ",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}

		char *function=new char[pos1-2];
		char *startStr=new char[pos2-pos1];
		char *endStr=new char[len-pos2-1];

		strcopy(function,&line[3],pos1-3);
		strcopy(startStr,&line[pos1+1],pos2-pos1-1);
		strcopy(endStr,&line[pos2+1],len-pos2-2);
		horzObj=new Calculate(this,function,pref,vars);
		vertObj=new Script(this,startStr,pref,vars,eventReciver);
		vertObj2=new Script(this,endStr,pref,vars,eventReciver);
		delete[]function;
		delete[]startStr;
		delete[]endStr;
		return NULL;
	}
	else if(bracketFind(line,"getline") ==0)
	{
		if(len>7)
		{
			printError("Invalid operation after getline",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
		}
		else operation=SGETLINE;
		value.type=NCHAR;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"getkey") ==0)
	{
		if(len>6)
		{
			printError("Invalid operation after getkey",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
		}
		else operation=SGETKEY;
		value.type=NCHAR;
		value.cval=new char[2];
		value.cval[1]=(char)0;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"keystate") ==0)
	{
		if(len>8)
		{
			printError("Invalid operation after keystate",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
		}
		else operation=SKEYSTATE;
		value.type=NCHAR;
		value.cval=new char[2];
		value.cval[1]=(char)0;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"break") ==0)
	{
		if(len>5)
		{
			printError("Invalid operation after break",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
		}
		else operation=SBREAK;
		value.type=NNONE;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"continue") ==0)
	{
		if(len>8)
		{
			printError("Invalid operation after getkey",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
		}
		else operation=SCONTINUE;
		value.type=NNONE;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"stop") ==0)
	{
		if(len>4)
		{
			printError("Invalid operation after stop",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
		}
		else operation=SSTOP;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(line[0]>='a' && line[0]<='z') 
	{
		horzObj=vertObj2=vertObj3=nextObj=NULL;
		if(pref->angle==DEG)
			number=180.0/(long double)PI;
		else if(pref->angle==RAD)
			number=1.0;
		else number=200.0/(long double)PI;
		if(strncmp("asinh",line,5) == 0)
		{
			operation=ASINH;
			vertObj=new Script(this,&line[5],pref,vars,eventReciver);
		}
		else if(strncmp("acosh",line,5) == 0)
		{
			operation=ACOSH;
			vertObj=new Script(this,&line[5],pref,vars,eventReciver);
		}
		else if(strncmp("atanh",line,5) == 0)
		{
			operation=ATANH;
			vertObj=new Script(this,&line[5],pref,vars,eventReciver);
		}
		else if(strncmp("asin",line,4) == 0)
		{
			operation=ASIN;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp("acos",line,4) == 0)
		{
			operation=ACOS;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp("atan",line,4) == 0)
		{
			operation=ATAN;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp("sinh",line,4) == 0)
		{
			if(pref->complex)
				operation=CSINH;
			else operation=SINH;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp("cosh",line,4) == 0)
		{
			if(pref->complex)
				operation=CCOSH;
			else operation=COSH;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp("tanh",line,4) == 0)
		{
			if(pref->complex)
				operation=CTANH;
			else operation=TANH;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp("sin",line,3) == 0)
		{
			if(pref->complex)
				operation=CSIN;
			else operation=SIN;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp("cos",line,3) == 0)
		{
			if(pref->complex)
				operation=CCOS;
			else operation=COS;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp("tan",line,3) == 0)
		{
			if(pref->complex)
				operation=CTAN;
			else operation=TAN;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp("log",line,3) == 0)
		{
			if(pref->complex)
				operation=CLG;
			else operation=LG;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp("ln",line,2) == 0)
		{
			if(pref->complex)
				operation=CLN;
			else operation=LN;
			vertObj=new Script(this,&line[2],pref,vars,eventReciver);
		}
		else if(strncmp(line,"sqrt",4) == 0)
		{
			if(pref->complex)
				operation=CSQRT;
			else operation=SQRT;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp(line,"curt",4) == 0)
		{
			if(pref->complex)
			{
				operation=CROOT;
				vertObj=new Script(this,"3",pref,vars,eventReciver);
				vertObj2=new Script(this,&line[4],pref,vars,eventReciver);
			}
			else 
			{
				operation=CURT;
				vertObj=new Script(this,&line[4],pref,vars,eventReciver);
			}
		}
		else if(strncmp(line,"real",4) == 0)
		{
			operation=SREAL;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
			vertObj2=new Script(this,"3",pref,vars,eventReciver);
		}
		else if(strncmp(line,"imag",4) == 0)
		{
			operation=SIMAG;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp(line,"abs",3) == 0)
		{
			if(pref->complex)
				operation=CABS;
			else operation=SABS;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp(line,"arg",3) == 0 && pref->complex)
		{
			operation=SARG;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp(line,"conj",4) == 0 && pref->complex)
		{
			operation=SCONJ;
			vertObj=new Script(this,&line[4],pref,vars,eventReciver);
		}
		else if(strncmp(line,"det",3) == 0)
		{
			operation=DETERMINANT;
			vertObj=new Script(this,&line[3],pref,vars,eventReciver);
		}
		else if(strncmp(line,"i",1) == 0  && pref->complex)
		{
			operation=SVALUE;
			value.type=NFLOAT;
			value.fval=Complex(0.0,1.0);
			return NULL;
		}
		else{
			printError("Unknown command",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		return NULL;
	}
	else if(bracketFind(line,"~")==0)
	{
		vertObj2=vertObj3=horzObj=nextObj=NULL;
		char*recString1=new char[len];
		if(len<2)
		{
				operation=SFAIL;
				printError("No argument for ~ set",semicolonCount,eventReciver->eventReciver);
		}
		else operation=SBNOT;
		
		strcopy(recString1,&line[1],len-1);
		
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		return NULL;
	}
	else if((pos1=bracketFindRev(line,"^")) != -1)
	{
		operation=SFAIL;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		if(pos1<1)
			printError("First operand of ^ invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<2)
			printError("Second operand of ^ invalid",semicolonCount,eventReciver->eventReciver);
		else 
		{
			if(pref->complex)
				operation=CPOW;
			else operation=POW;
		}
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		if(strcmp(recString2,"-1")!=0)
			vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		else {
			operation=INVERT;
			vertObj2=NULL;
		}
			
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}
	else if(bracketFind(line,"$r") != -1)
	{
		pos1=bracketFindRev(line,"$r")-1;
		operation=SFAIL;
		if(pos1<1)
			printError("First operand of root invalid",semicolonCount,eventReciver->eventReciver);
		else if(len-pos1<3)
			printError("Second operand of root invalid",semicolonCount,eventReciver->eventReciver);
		else {
			if(pref->complex)
				operation=CROOT;
			else operation=ROOT;
		}
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1-1];

		
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],len-pos1-2);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		return NULL;
	}	
	
	else if(line[0] == '(' && (line[len-1]==')' || strncmp(&line[1],"float",5)==0 || strncmp(&line[1],"int",3)==0 || strncmp(&line[1],"bool",4)==0 || strncmp(&line[1],"string",6)==0))
	{
//		perror("bracket");
		int pos1=bracketFind(line,")");
		if(pos1<1)
		{
			printError("Closing bracket for ( not found",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		else if(pos1!=len-1)
		{
			char*castType=new char[pos1];
			strcopy(castType,&line[1],pos1-1);
			if(strcmp(castType,"int")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NINT;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				delete[]castType;
				delete[]recString1;
				return NULL;
			}
			else if(strcmp(castType,"float")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NFLOAT;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				delete[]castType;
				delete[]recString1;
				return NULL;
			}
			else if(strcmp(castType,"bool")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NBOOL;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				delete[]castType;
				delete[]recString1;
				return NULL;
			}
			else if(strcmp(castType,"string")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NCHAR;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				delete[]castType;
				delete[]recString1;
				return NULL;
			}
		}
		operation=SBRACKET;
		char*recString1=new char[pos1];
		strcopy(recString1,&line[1],pos1-1);
		vertObj=new Script(this,NULL,pref,vars,eventReciver);
		vertObj->split(recString1);
		delete[]recString1;
		if(pos1==len-1)
			return NULL;
		else {
			char*recString2=new char[len-pos1];
			strcopy(recString2,&line[pos1+1],len-pos1-1);
			return recString2;
		}
	}
	else if((pref->calcType == SCIENTIFIC && line[0]>='A' || line[0]>='G') && line[0]<='Z'&& len==1 || strncmp(line,"$A",2)==0 &&len==2)
	{
		operation=SVAR;
		if(strncmp(line,"$A",2)==0)
			var=26;
		else var=line[0]-65;
//		eventReciver->numlen[var]=1;
		return NULL;
	}
	else if((line[0]>='A' && line[0]<='Z' || strncmp(line,"$A",2)==0) && line[len-1]==']')
	{
		if(strncmp(line,"$A",2)==0)
		{
			var=26;
			line++;
			len--;
		}
		else var=line[0]-65;
		
		if((pos1=bracketFindRev(line,"["))>1)
		{
			if(line[pos1-1] !=']')
			{
				printError("Closing brace for variable not found",semicolonCount,eventReciver->eventReciver);
				operation=SFAIL;
				return NULL;
			}
			if(pos1-3<=0 && len-pos1-2<=0)
			{
				vertObj=vertObj2=NULL;
			}
			else {
				char*recString1=new char[pos1-2];
				char*recString2=new char[len-pos1-1];
				strcopy(recString1,&line[2],pos1-3);
				strcopy(recString2,&line[pos1+1],len-pos1-2);
				
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		//		perror(QString("index: ")+recString1);
				delete[]recString1;
				delete[]recString2;
			}
			operation=SMATRIX;
		}
		else {

			if(len-3<=0)
				operation=SVECTOR;
			else {
				char*recString1=new char[len-2];
				strcopy(recString1,&line[2],len-3);
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				vertObj2=vertObj3=horzObj=nextObj=NULL;
	//			perror(QString("index: ")+recString1);
				delete[]recString1;
				operation=SARRAY;
			}
		}

		if(var>26 || var < 0)
		{
			printError("Invalid variable",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
//		eventReciver->numlen[var]=1;
		return NULL;
	}
	else if(line[0] == '\"')
	{
		if(line[len-1]!='\"' || len <=1)
		{
			printError("Invalid String",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		operation=SVALUE;
		value.type=NCHAR;
		value.cval=(char*)malloc(len-1);
		strcopy(value.cval,&line[1],len-2);
		return NULL;
	}
	else if(line[0] == '\\')
	{
		char*err;
		if(len<3)
		{
			printError("Invalid number",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}

		operation=SVALUE;
		value.type=NINT;

		if(line[1] == 'b')
			value.ival=strtoll(&line[2],&err,2);
		else if(line[1] == 'o')
			value.ival=strtoll(&line[2],&err,8);
		else if(line[1] == 'c')
			value.ival=strtoll(&line[2],&err,10);
		else if(line[1] == 'h')
			value.ival=strtoll(&line[2],&err,16);
		else {
			printError("Invalid number",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		if(*err!=(char)0)
		{
			printError("Invalid number",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}


		return NULL;
	}
	else {
		
		operation=SVALUE;
		char*err;
		
		if(pref->calcType == BASE)
		{
			value.type=NINT;
			if(pref->base == BIN)
				value.ival=strtoll(line,&err,2);
			else if(pref->base == OCT)
				value.ival=strtoll(line,&err,8);
			else if(pref->base == HEX)
				value.ival=strtoll(line,&err,16);
			else if(pref->base == DEC)
				value.ival=strtoll(line,&err,10);

		}
		else
		{
			value.ival=strtoll(line,&err,10);
			if(*err!=(char)0)
			{
				value.fval=Complex(strtold(line,&err),0.0);
				value.type=NFLOAT;
			}
			else value.type=NINT;
		}
		if(*err!=(char)0)
		{
			printError("Invalid number",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
	}
	return NULL;
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
			if(nextObj!=NULL)
			{
				return value=nextObj->exec();
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
			value=vertObj->exec();
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
					vertObj2->exec();
			else if(value.type==NINT)
				if(value.ival)
					vertObj2->exec();
			else if(value.type==NFLOAT)
				if(value.fval.real()!=0.0)
					vertObj2->exec();
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SIFELSE:
		{
			value=vertObj->exec();
			if(value.type==NBOOL)
				if(value.bval)
					vertObj2->exec();
				else vertObj3->exec();
			else if(value.type==NINT)
				if(value.ival)
					vertObj2->exec();
				else vertObj3->exec();
			else if(value.type==NFLOAT)
				if(value.fval.real()!=0.0)
					vertObj2->exec();
				else vertObj3->exec();
			else vertObj3->exec();
			
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
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
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SFOR:
		{
			if(vertObj3!=NULL)
			{
				for(vertObj->exec();;vertObj3->exec())
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
					horzObj->exec();
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
					horzObj->exec();
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
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else 
			fprintf(stderr,"%s",eventContent);
			free(eventContent);
#endif

			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
#ifndef CONSOLE
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
				QApplication::postEvent(eventReciver->eventReciver,ev);
				eventReciver->eventCount++;
				if(eventReciver->eventCount>200)
					eventReciver->status=1;
			}
			else if(var==1)
			{
				QCustomEvent *ev=new QCustomEvent(SIGSTARTLIST);
				QApplication::postEvent(eventReciver->eventReciver,ev);
				eventReciver->eventCount++;
				if(eventReciver->eventCount>200)
					eventReciver->status=1;
			}
			else if(var==2)
			{
				eventReciver->data=NULL;
				QCustomEvent*ev=new QCustomEvent(SIGENDLIST);
				qApp->lock();
				QApplication::postEvent(eventReciver->eventReciver,ev);
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
			
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
				value=horzObj->exec();
				convertToFloat(&value);
				eventContent[3]=(double)value.fval.real();
				ev=new QCustomEvent(SIGGRAPHROTATE);
			}
			else if(var==1)
				ev=new QCustomEvent(SIGGRAPHTRANSLATE);
			else ev=new QCustomEvent(SIGGRAPHSCALE);

			ev->setData(eventContent);
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
			return value;
		}
		case SGRAPHTEXT:
		{
			QCustomEvent *ev=new QCustomEvent(SIGGRAPHTEXT);
			char*eventContent;
			
			value=horzObj->exec();
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
				value.fval=Complex(res,value.fval.imag());
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
			Number w1=horzObj->exec();
			convertToFloat(&w1);
			eventReciver->vars[23][0].fval=Complex(pos+step,0.0);
			Number w2=horzObj->exec();
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
		oldy=horzObj->calc();
		vars[23]=end;
		y=horzObj->calc();
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
			QApplication::postEvent(eventReciver->eventReciver,killEvent);
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
			memcpy(eventContent,value.cval,pathlen);
			eventReciver->data=NULL;
			QCustomEvent*fileEvent=new QCustomEvent(SIGFILEREAD);
			fileEvent->setData(eventContent);

			QApplication::postEvent(eventReciver->eventReciver,fileEvent);
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
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
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
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
			QApplication::postEvent(eventReciver->eventReciver,ev);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else 
			fprintf(stderr,"\033[%i;%iH",coords[1]+1,coords[0]+1);
#endif

			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SCLEARTEXT:
		{
#ifndef CONSOLE
			QCustomEvent*clearEvent=new QCustomEvent(SIGCLEARTEXT);
			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
			eventReciver->eventCount++;
			if(eventReciver->eventCount>200)
				eventReciver->status=1;
#else 
			fprintf(stderr,"\033[2J");
			fprintf(stderr,"\033[1;1H");
#endif

			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SGETKEY:
		{
#ifndef CONSOLE
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGGETKEY);

			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
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
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SKEYSTATE:
		{
#ifndef CONSOLE
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGKEYSTATE);

			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
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
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SGETLINE:
		{
#ifndef CONSOLE
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGGETLINE);

			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
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
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SINIT:
		{

			if(nextObj!=NULL)
				value=nextObj->exec();
#ifndef CONSOLE
			QCustomEvent*killEvent=new QCustomEvent(SIGFINISHED);
			QApplication::postEvent(eventReciver->eventReciver,killEvent);
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
			fprintf(stderr,QString::number((double)result[effDestIndex])+" ");
		}
		fprintf(stderr,"\n");
	}
	memcpy(matrix,result,size*size*sizeof(long double));
	free(result);
	free(subMatrix);
	
	return true;
}


void printError(const char*text,int num,QObject*eventReciver)
{
		QCustomEvent*debugEvent=new QCustomEvent(SIGDEBUG);
		char*debugData=(char*)malloc(strlen(text)+5);
		memcpy(debugData,&num,4);
		memcpy(&debugData[4],text,strlen(text)+1);
		debugEvent->setData(debugData);
		QApplication::postEvent(eventReciver,debugEvent);
}



