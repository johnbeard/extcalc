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
					ret="";
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
	char*cleanString=checkString(line,pref,vars);
	if(cleanString==NULL)
		return NAN;
	else 
	{
		long double ret= calculate(cleanString,pref,vars);
		delete[]cleanString;
		return ret;
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

char*checkString(QString input,Preferences*pref,Variable*vars)
{

	if(input.length()<=0)
		return NULL;
	
	QString qstr=input;
	qstr.replace("\xb2"+getUnicode(ROOTSTRING),"sqrt");
	qstr.replace("2"+getUnicode(ROOTSTRING),"sqrt");
	qstr.replace("\xb3"+getUnicode(ROOTSTRING),"curt");
	qstr.replace("3"+getUnicode(ROOTSTRING),"curt");
	qstr.replace(getUnicode(ROOTSTRING),"root");
	
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
	char*ret=checkStringAnsi(output,pref,vars);
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
					bracket--;
				else if(string[c] == '[')
					sqbracket--;
				if(string[c] == ']')
					sqbracket++;
				else if(string[c] == '{')
					brace--;
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


char* checkStringAnsi(char* str,Preferences*pref,Variable*vars)
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
			tmp=calcString;
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
				 (calcString[c] >= 'a' && calcString[c]<='z' &&(calcString[c]!='e' ||calcString[c+1]=='u') && calcString[c]!='x'))
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
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z'))
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




long double calculate(char* line,Preferences*pref,Variable*vars)
{
//	perror(line);
	if(line == NULL)
		return (NAN);
	int len=strlen(line);
	if(len <=0)
		return (NAN);
	long double complete=(long double)0.0;
	char*recString1,*recString2;

	if(bracketFind(line,"->") != -1)
	{
		int pos1=bracketFindRev(line,"->");
		if(len<pos1+1)
			return NAN;
			
		int var=((int)line[pos1+1])-65;
		if(var<0 || var>25)
			return NAN;

		recString1=new char[pos1];
		strcopy(recString1,line,pos1-1);
		vars[var][0]=calculate(recString1,pref,vars);
		delete[]recString1;
		return vars[var][0];
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
			if( pos2>0 &&(line[pos2-1] >='A' && line[pos2-1]<='Z'					//binary - operator
			   || line[pos2-1]>='0' && line[pos2-1]<='9'
			   || line[pos2-1]=='.' || line[pos2-1]==')'))
			{
				pos=pos2;

					recString1=new char[pos+1];
					strcopy(recString1,line,pos);
					recString2=new char[len-pos];
					strcopy(recString2,&line[pos+1],len-pos-1);
					complete=calculate(recString1,pref,vars)-calculate(recString2,pref,vars);
					delete[]recString1;
					delete[]recString2;
					return complete;
			}
			else if(pos2==0)								//unary - operator
				return (long double)-1.0*calculate(&line[1],pref,vars);
			
		}
		else if(pos1>pos2)
		{
			if(pos1>0 && (line[pos1-1] >='A' && line[pos1-1]<='Z'		//binary + operator
						 || line[pos1-1]>='0' && line[pos1-1]<='9'
						 || line[pos1-1]=='.' || line[pos1-1]==')'))
			{
				pos=pos1;

					recString1=new char[pos+1];
					strcopy(recString1,line,pos);
					recString2=new char[len-pos];
					strcopy(recString2,&line[pos+1],len-pos-1);
					complete=calculate(recString1,pref,vars)+calculate(recString2,pref,vars);
					delete[]recString1;
					delete[]recString2;
					return complete;

			}
			else if(pos1==0)								//unary + operator
				return calculate(&line[1],pref,vars);
		}
	}
	
	if(bracketFind(line,"*") != -1 || bracketFind(line,"/") != -1)
	{
		int pos1=bracketFindRev(line,"*");
		int pos2=bracketFindRev(line,"/");
		if(pos1==-1 && pos2==-1)
			return NAN;
		int pos;
		if((pos2>pos1 && pos2 != -1) || pos1==-1)
		{
			pos=pos2;
			
			recString1=new char[pos+1];
			strcopy(recString1,line,pos);
			recString2=new char[len-pos];
			strcopy(recString2,&line[pos+1],len-pos-1);
			complete=calculate(recString1,pref,vars)/calculate(recString2,pref,vars);
			delete[]recString1;
			delete[]recString2;
			return complete;
		}
		else
		{
			pos=pos1;
			recString1=new char[pos+1];
			strcopy(recString1,line,pos);
			recString2=new char[len-pos];
			strcopy(recString2,&line[pos+1],len-pos-1);
			complete=calculate(recString1,pref,vars)*calculate(recString2,pref,vars);
			delete[]recString1;
			delete[]recString2;
			return complete;
		}
	}
	else if(bracketFind(line,"%") != -1)
	{
		int pos=bracketFind(line,"%");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos];
		strcopy(recString2,&line[pos+1],len-pos-1);
		complete=fmodl(calculate(recString1,pref,vars),calculate(recString2,pref,vars));
		delete[]recString1;
		delete[]recString2;
		return complete;
		
		
	}
	else if(bracketFind(line,"||") != -1)
	{
		int pos=bracketFind(line,"||");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos-1];
		strcopy(recString2,&line[pos+2],len-pos-2);
		int num1=(int)calculate(recString1,pref,vars);
		int num2=(int)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		if(num1==0 && num2==0)
			return 0.0;
		else return 1.0;
	}
	else if(bracketFind(line,"&&") != -1)
	{
		int pos=bracketFind(line,"&&");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos-1];
		strcopy(recString2,&line[pos+2],len-pos-2);
		int num1=(int)calculate(recString1,pref,vars);
		int num2=(int)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		if(num1==0 || num2==0)
			return 0.0;
		else return 1.0;
	}
	else if(bracketFind(line,">>") != -1)
	{
		int pos=bracketFind(line,">>");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos-1];
		strcopy(recString2,&line[pos+2],len-pos-2);
		long long num1=(long long)calculate(recString1,pref,vars);
		long long num2=(long long)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return (long double)(num1>>num2);
	}
	else if(bracketFind(line,"<<") != -1)
	{
		int pos=bracketFind(line,"<<");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos-1];
		strcopy(recString2,&line[pos+2],len-pos-2);
		long long num1=(long long)calculate(recString1,pref,vars);
		long long num2=(long long)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return (long double)(num1<<num2);
	}
	else if(bracketFind(line,"x") != -1)
	{
		int pos=bracketFind(line,"x");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos];
		strcopy(recString2,&line[pos+1],len-pos-1);
		long long num1=(long long)calculate(recString1,pref,vars);
		long long num2=(long long)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return(long double)(num1^num2);
	}
	else if(bracketFind(line,"|") != -1)
	{
		int pos=bracketFind(line,"|");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos];
		strcopy(recString2,&line[pos+1],len-pos-1);
		long long num1=(long long)calculate(recString1,pref,vars);
		long long num2=(long long)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return(long double)(num1|num2);
	}
	else if(bracketFind(line,"&") != -1)
	{
		int pos=bracketFind(line,"&");
		recString1=new char[pos+1];
		strcopy(recString1,line,pos);
		recString2=new char[len-pos];
		strcopy(recString2,&line[pos+1],len-pos-1);
		long long num1=(long long)calculate(recString1,pref,vars);
		long long num2=(long long)calculate(recString2,pref,vars);
		delete[]recString1;
		delete[]recString2;
		return(long double)(num1&num2);
	}
	else if(bracketFind(line,"^") != -1)
	{
		int pos1;
		pos1=bracketFindRev(line,"^");
		if(pos1==-1)
			return NAN;
		recString1=new char[pos1+1];
		strcopy(recString1,line,pos1);
		recString2=new char[len-pos1];
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		complete=powl(calculate(recString1,pref,vars),calculate(recString2,pref,vars));
		delete[] recString1;
		delete[] recString2;
	}
	else if(bracketFind(line,"$r") != -1)	//	root operation for extcalc (binary operator)
	{

		int pos=bracketFind(line,"$r");
		recString1=new char[pos+1];
		recString2=new char[len-pos-1];
		strcopy(recString1,line,pos);
		strcopy(recString2,&line[pos+2],len-pos-2);
		
		complete=powl(calculate(recString2,pref,vars),1.0/calculate(recString1,pref,vars));
		delete[]recString1;
		delete[]recString2;
		return complete;
	}
	else if(line[0]>='a' && line[0]<='z') 
	{
		long double mult=1.0;
		if(pref->angle==DEG)
			mult=(long double)PI/180.0;
		else if(pref->angle==GRA)
			mult=(long double)PI/200.0;

		if(strncmp(line,"asinh",5) == 0)
		{
			complete=asinhl(calculate(&line[5],pref,vars));
		}
		else if(strncmp(line,"acosh",5) == 0)
		{
			complete=acoshl(calculate(&line[5],pref,vars));
		}
		else  if(strncmp(line,"atanh",5) == 0)
		{
			complete=atanhl(calculate(&line[5],pref,vars));
		}
		else  if(strncmp(line,"asin",4) == 0)
		{
			complete=asinl(calculate(&line[4],pref,vars))/mult;
		}
		else if(strncmp(line,"acos",4) == 0)
		{
			complete=acosl(calculate(&line[4],pref,vars))/mult;
		}
		else if(strncmp(line,"atan",4) == 0)
		{
			complete=atanl(calculate(&line[4],pref,vars))/mult;
		}
		else if(strncmp(line,"sinh",4) == 0)
		{
			complete=sinhl(calculate(&line[4],pref,vars));
		}
		else if(strncmp(line,"cosh",4) == 0)
		{
			complete=coshl(calculate(&line[4],pref,vars));
		}
		else if(strncmp(line,"tanh",4) == 0)
		{
			complete=tanhl(calculate(&line[4],pref,vars));
		}
		else if(strncmp(line,"sin",3) == 0)
		{
			complete=sinl(calculate(&line[3],pref,vars)*mult);
		}
		else if(strncmp(line,"cos",3) == 0)
		{
			complete=cosl(calculate(&line[3],pref,vars)*mult);
		}
		else if(strncmp(line,"tan",3) == 0)
		{
			complete=tanl(calculate(&line[3],pref,vars)*mult);
		}
		else if(strncmp(line,"log",3) == 0)
		{
			complete=logl(calculate(&line[3],pref,vars))/log(10);
		}
		else if(strncmp(line,"ln",2) == 0)
		{
			complete=logl(calculate(&line[2],pref,vars));
		}
		else if(strncmp(line,"rnd",3) == 0)
		{
#if RAND_MAX < 1000000000
			complete=(((rand()*(1000000000/RAND_MAX))%1000000000)*calculate(&line[3],pref,vars))/1000000000;
#else
			complete=((rand()%1000000000)*calculate(&line[3],pref,vars))/1000000000;
#endif
		}
		else if(strncmp(line,"sqrt",4) == 0)
		{
			complete=sqrtl(calculate(&line[4],pref,vars));
		}
		else if(strncmp(line,"curt",4) == 0)
		{
			complete=powl(calculate(&line[4],pref,vars),(long double)(1.0/3.0));
		}
		else if(line[0]=='n')
		{
			int num=(int)calculate(&line[1],pref,vars);
			if(num==0)
				return(1.0);
			else return(0.0);
		}
		else{
			return (NAN);
		}
		if(complete < pow(10.0,-pref->precision+1) && complete > -1.0*pow(10.0,-pref->precision+1))
		{
			complete=0.0;
		}
	}
	else if(line[0]=='~')
	{
		long long num=(long long)calculate(&line[1],pref,vars);
		num=~num;
		return (long double)num;
	}
	else if(bracketFind(line,"!") != -1)
	{
		recString1=new char[len];
		strcopy(recString1,line,len-1);
		long double end=calculate(recString1,pref,vars);
		delete[]recString1;
		if(end<0.0)
			return NAN;
		complete=1.0;
		for(int c=2; c<=(int)end; c++)
			complete*=c;
	}
/*	else if(bracketFind(line,"\\r(") != -1)		//root operation for calc (operator with arguments)
	{
		// syntax: fourth root of nine: root(4,9)
		int pos1=bracketFind(line,"\\r(");
		pos1+=3;
		int pos2=bracketFind(line,",",pos1);
		if(pos1==-1 || pos2 == -1 || line[len-1]!=')')
			return (NAN);
		
		recString1=new char[pos2-pos1+1];
		recString2=new char[len-pos2-1];
		strcopy(recString1,&line[pos1],pos2-pos1);
		strcopy(recString2,&line[pos2+1],len-pos2-2);
		
		complete=powl(calculate(recString2,pref,vars),1/calculate(recString1,pref,vars));
		delete[]recString1;
		delete[]recString2;
	}
*/	else if(bracketFind(line,"\\i(") != -1)
	{
		// syntax: integration of sin X between 2 and 3: integ(sinx,2,3)
		bool inv=false;
		double start,end;
		int pos1=bracketFind(line,",",3);
		if(pos1==-1)
			return NAN;
		int pos2=bracketFind(line,",",pos1+1);
		if(pos2==-1)
			return NAN;
		char *function=new char[pos1-2];
		char *startStr=new char[pos2-pos1+1];
		char *endStr=new char[len-pos2];

		strcopy(function,&line[3],pos1-3);
		strcopy(startStr,&line[pos1+1],pos2-pos1-1);
		strcopy(endStr,&line[pos2+1],len-pos2-2);
		
		start=calculate(startStr,pref,vars);
		end=calculate(endStr,pref,vars);
		Calculate integ(NULL,function,pref,vars);
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
		vars[23][0]=start;
		oldy=integ.calc();
		vars[23][0]=end;
		y=integ.calc();
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
			
			steps=(int)pow(2,(num-1));
			
			for(int c=1; c<=steps; c++)
			{
				vars[23][0]=start+((2*c-1)*(end-start))/pow(2,num);
				line1[0]+=integ.calc();
			}
			line1[0]=0.5*(line1[0]*(end-start)/pow(2,num-1)+line2[0]);
			
			for(int c=2; c<=num+1; c++)
				line1[c-1]=(pow(4,c-1)*line1[c-2]-line2[c-2])/(pow(4,c-1)-1);

		
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
		complete=line1[num-1];
		if(inv)
			complete*=-1.0;
		delete[]function;
		delete[]startStr;
		delete[]endStr;

	}
	else if(bracketFind(line,"\\d(") !=-1)
	{
		double pos;
		int pos1=bracketFind(line,",",3);
		if(pos1<0 || pos1>len-2)
			return NAN;
		char* function=new char[pos1-2];
		char* startStr=new char[len-pos1-1];
		strcopy(function,&line[3],pos1-3);
		strcopy(startStr,&line[pos1+1],len-pos1-2);
//	startStr=checkString(startStr);
		pos=calculate(startStr,pref,vars);
		Calculate diff(NULL,function,pref,vars);
		double step=(pos*(double)1e-6);
		if(step<1e-6)
			step=1e-6;
		vars[23][0]=pos-step;
		double w1=diff.calc();
		vars[23][0]=pos+step;
		double w2=diff.calc();
		complete=(w2-w1)/((double)2.0*step);
		delete[]function;
		delete[]startStr;
	}
	else if(line[0]=='(')
	{
		if(line[len-1] == ')')
		{
		recString1=new char[len-1];
		strcopy(recString1,&line[1],len-2);
		}
		else 
		{
			recString1=new char[len];
			strcopy(recString1,&line[1],len-1);
		}
		complete=calculate(recString1,pref,vars);
		delete[] recString1;
	}
	else if((pref->calcType == SCIENTIFIC && line[0]>='A' || line[0]>='G') && line[0]<='Z')
	{

		complete=vars[(int)line[0]-65][0];

	}
	else if(line[0] == '\\')
	{
		if(len<3)
			return NAN;
		if(line[1] == 'b')
			return (long double)strtoll(&line[2],NULL,2);
		else if(line[1] == 'o')
			return (long double)strtoll(&line[2],NULL,8);
		else if(line[1] == 'c')
			return (long double)strtoll(&line[2],NULL,10);
		else if(line[1] == 'h')
			return (long double)strtoll(&line[2],NULL,16);
		else return NAN;
	}
	else {
		if(pref->calcType == BASE)
		{
			if(pref->base == BIN)
				return (long double)strtoll(line,NULL,2);
			else if(pref->base == OCT)
				return (long double)strtoll(line,NULL,8);
			else if(pref->base == HEX)
				return (long double)strtoll(line,NULL,16);
			else if(pref->base == DEC)
				return (long double)strtoll(line,NULL,10);
			
			
		}
		else return(strtold(line,NULL));
	} 
	
	return complete;
}









int Calculate::split(char* line)
{

	if(line==NULL)
		return -1;
	int len=strlen(line);
	if(len <=0)
		return -1;
//	perror("split: "+QString(line));

	if(bracketFind(line," ") != -1)	//Leeroperation
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
			if(pos1==-1)
				break;
			if(line[pos1-1]=='e')
				pos=pos1-1;
			else break;
		}
		pos=-1;
		while(true)
		{
			pos2=bracketFindRev(line,"-",pos);
			if(pos2==-1)
				break;
			if(line[pos2-1]=='e')
				pos=pos2-1;
			else break;
		}
		
		if(pos2>pos1)
		{
			if((line[pos2-1] >='A' && line[pos2-1]<='Z'					//binary - operator
			   || line[pos2-1]>='0' && line[pos2-1]<='9'
			   || line[pos2-1]=='.' || line[pos2-1]==')'|| line[pos2-1]==']') && pos2>0)
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
			if((line[pos1-1] >='A' && line[pos1-1]<='Z'					//binary + operator
						 || line[pos1-1]>='0' && line[pos1-1]<='9'
						 || line[pos1-1]=='.' || line[pos1-1]==')' || line[pos1-1]==']') && pos1>0)
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
			operation=ROOT;
			horzObj=new Calculate(this,&line[4],pref,vars);
			vertObj=new Calculate(this,"2",pref,vars);
		}
		else if(strncmp(line,"curt",4) == 0)
		{
			operation=ROOT;
			horzObj=new Calculate(this,&line[4],pref,vars);
			vertObj=new Calculate(this,"3",pref,vars);
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
		if(line[len-1] == ')')
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
		{
			if(line[1]=='[' && line[len-1]==']')
			{
				operation=ARRAY;
				char*recString1=new char[len-2];
				strcopy(recString1,&line[2],len-3);
				horzObj=new Calculate(this,recString1,pref,vars);
			}
			else var=-1;
		}
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
				return vars[var][0];
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
		case ARRAY:
		{
			double dIndex=horzObj->calc();
			int index=(int)dIndex;
			if(index>=0 && index<vars[var].GetLen())
				return vars[var][index];
			else return NAN;
		}
		case POW:
			return pow(vertObj->calc(),horzObj->calc());
		case ROOT:
			return pow(horzObj->calc(),1/vertObj->calc());
		case SIN:
			return sin(vertObj->calc()/number);
		case COS:
			return cos(vertObj->calc()/number);
		case TAN:
			return tan(vertObj->calc()/number);
		case LG:
			return log(vertObj->calc())/log(10);
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
			double savedX=vars[23][0];
			double point;
			if(vertObj!= NULL)
				point=vertObj->calc();
			else return NAN;
			if(horzObj == NULL)
				return NAN;
			double step=(point*1e-6);
			if(step<1e-6)
				step=1e-6;
			vars[23][0]=point-step;
			double w1=horzObj->calc();
			vars[23][0]=point+step;
			double w2=horzObj->calc();
			vars[23][0]=savedX;
			return((w2-w1)/(2*step));
		}
		case MODULO:
			return fmod(vertObj->calc(),horzObj->calc());
		case INTEGRAL:
		{
			double savedX=vars[23][0];
//     Verzweigung:
			//    
//         end
//          |
//         NONE - start
//           |
//        INTEGRAL - function
			//
//        integral(function,start,end);

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
			vars[23][0]=start;
			oldy=horzObj->calc();
			vars[23][0]=end;
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
				steps=(int)pow(2,(num-1));
				for(int c=1; c<=steps; c++)
				{
					vars[23][0]=start+((2*c-1)*(end-start))/pow(2,num);
					line1[0]+=horzObj->calc();
				}
				line1[0]=0.5*(line1[0]*(end-start)/pow(2,num-1)+line2[0]);
			
				for(int c=2; c<=num+1; c++)
					line1[c-1]=(pow(4,c-1)*line1[c-2]-line2[c-2])/(pow(4,c-1)-1);

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

			vars[23][0]=savedX;
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
	int pos1;
	int len=strlen(line);
//	perror("parse: "+QString(line));
	
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
			if(line[pos1+3]=='[' && line[len-1]==']')
			{
				if((pos2=bracketFind(line,"[",pos1+4))!=-1)
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
		eventReciver->numlen[var]=1;
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
	else if(bracketFind(line,">") != -1)
	{
		pos1=bracketFindRev(line,">");
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
	else if(bracketFind(line,"<") != -1)
	{
		pos1=bracketFindRev(line,"<");
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
				if((pos2=bracketFindRev(line,"]",pos1-2)) !=-1)
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
		eventReciver->numlen[var]=1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"+")) != -1)
	{
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
	else if((pos1=bracketFind(line,"-")) != -1)
	{
		operation=MINUS;
		char*recString1=new char[pos1+1];
		char*recString2=new char[len-pos1];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+1],len-pos1-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=new Script(this,recString2,pref,vars,eventReciver);
		delete[]recString1;
		delete[]recString2;
		if(vertObj->getOperation()==NONE)
		{
			operation=NONE;
			delete vertObj;
			delete vertObj2;
			vertObj=vertObj2=NULL;
		}
		else return NULL;
	}
	if(bracketFind(line,"!") ==0)
	{
		if(len<2)
		{
			operation=SFAIL;
			printError("No argument for ! set",semicolonCount,eventReciver->eventReciver);
		}
		else operation=SNOT;
		char*recString1=new char[len];
		strcopy(recString1,&line[1],len-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=vertObj3=horzObj=nextObj=NULL;
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

	else if((pos1=bracketFind(line,"run(")) == 0)
	{
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
	else if(line[0]>='A' && line[0]<='Z' &&len==1)
	{
		operation=SVAR;
		var=line[0]-65;
		eventReciver->numlen[var]=1;
		return NULL;
	}
	else if(line[0]>='A' && line[0]<='Z' && line[len-1]==']')
	{

		if((pos1=bracketFind(line,"[",2))!=-1)
		{
			if(line[pos1-1] !=']')
			{
				printError("Closing brace for variable not found",semicolonCount,eventReciver->eventReciver);
				operation=SFAIL;
				return NULL;
			}
			char*recString1=new char[pos1-2];
			char*recString2=new char[len-pos1-1];
			strcopy(recString1,&line[2],pos1-3);
			strcopy(recString2,&line[pos1+1],len-pos1-2);
			vertObj=new Script(this,recString1,pref,vars,eventReciver);
			vertObj2=new Script(this,recString2,pref,vars,eventReciver);
	//		perror(QString("index: ")+recString1);
			delete[]recString1;
			delete[]recString2;
			operation=SMATRIX;
		}
		else {
			char*recString1=new char[len-2];
			strcopy(recString1,&line[2],len-3);
			vertObj=new Script(this,recString1,pref,vars,eventReciver);
			vertObj2=vertObj3=horzObj=nextObj=NULL;
	//		perror(QString("index: ")+recString1);
			delete[]recString1;
			operation=SARRAY;
		}
		var=line[0]-65;
		if(var>25 || var < 0)
		{
			printError("Invalid variable",semicolonCount,eventReciver->eventReciver);
			operation=SFAIL;
			return NULL;
		}
		eventReciver->numlen[var]=1;
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
		value.fval=NAN;
		value.type=NCHAR;
		value.cval=new char[len-1];
		strcopy(value.cval,&line[1],len-2);
		return NULL;
	}
	else {
		char*end;
		long long ret=strtoll(line,&end,10);
		if(end[0]==(char)0)
		{
//			perror("integer: "+QString(line));
			operation=SVALUE;
			value.fval=NAN;
			value.type=NINT;
			value.ival=ret;
			value.fval=(long double)ret;
			return NULL;
		}
		else
		{
			operation=NONE;									//No script operation; use Calculate
			horzObj=new Calculate((Math*)this,line,pref,vars);

			if(horzObj->getOperation()==NONE)
				if(isnan(horzObj->calc()))
					printError("Unknown command",semicolonCount,eventReciver->eventReciver);
			

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
		
		if(eventReciver->exit)
		{
			eventReciver->exit=false;
			eventReciver->status=0;
			pthread_exit(0);
		}
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
		case NONE:
			value.type=NFLOAT;
			value.fval=horzObj->calc();
			return value;
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
				index=(int)value.fval;
			if(index<0)
				index=0;
			if(index>=eventReciver->numlen[var])
			{
				eventReciver->vars[var]=(Number*)realloc((void*)eventReciver->vars[var],sizeof(Number)*(index+1));
				eventReciver->numlen[var]=index+1;
			}
			return eventReciver->vars[var][index];
		}
		case SMATRIX:
		{
			value=vertObj->exec();
			int index=0,index2=0;
			if(value.type==NBOOL)
				index=(int)value.bval;
			else if(value.type==NINT)
				index=value.ival;
			else if(value.type==NFLOAT)
				index=(int)value.fval;
			if(index<0)
				index=0;
			
			value=vertObj2->exec();
			if(value.type==NBOOL)
				index2=(int)value.bval;
			else if(value.type==NINT)
				index2=value.ival;
			else if(value.type==NFLOAT)
				index2=(int)value.fval;
			if(index2<0)
				index2=0;
			if(index>=eventReciver->numlen[var])
			{
				eventReciver->vars[var]=(Number*)realloc((void*)eventReciver->vars[var],sizeof(Number)*(index+1));
				eventReciver->numlen[var]=index+1;
				eventReciver->vars[var][index].type=NNONE;
			}
			else if(eventReciver->vars[var][index].type==NCHAR)
			{
				value.type=NINT;
				if((signed)strlen(eventReciver->vars[var][index].cval)>index2)
					value.ival=(long long)eventReciver->vars[var][index].cval[index2];
				else value.ival=0;
				return value;
			}
			return eventReciver->vars[var][index];
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
					value.bval=(n1.fval==(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval==(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval==(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval==(long double)n1.ival);
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
			value.fval=(long double)value.bval;
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
				if(value.fval!=0.0)
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
				if(value.fval!=0.0)
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
					if(!value.bval)
						break;
				else if(value.type==NINT)
					if(value.ival==0)
						break;
				else if(value.type==NFLOAT)
					if(value.fval==0.0)
						break;
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
						if(value.fval==0.0)
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
						if(value.fval==0.0)
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
		case SSET:
		{
			int index=0,index2=-1;
			value=vertObj->exec();

			if(value.type==NINT)
				value.fval=(long double)value.ival;
			else if(value.type==NFLOAT);
			else if(value.type==NCHAR)
				value.fval=(long double)value.cval[0];
			else if(value.type==NBOOL)
				value.fval=(long double)value.bval;
			if(vertObj2!=NULL)
			{
				Number nIndex=vertObj2->exec();
				if(nIndex.type==NBOOL)
					index=(int)nIndex.bval;
				else if(nIndex.type==NINT)
					index=nIndex.ival;
				else if(nIndex.type==NFLOAT)
					index=(int)nIndex.fval;
				if(index<0)
					index=0;
			}
			if(index>=vars[var].GetLen())
			{
				int addlen=index-vars[var].GetLen()+1;
				//long double*diffItems=new long double[addlen];
				//vars[var].NewItems(addlen,diffItems);
				for(int c=0; c<addlen; c++)
					vars[var].NewItem(0.0);
			//	delete[]diffItems;
			}
			if(index>=eventReciver->numlen[var])
			{
				eventReciver->vars[var]=(Number*)realloc((void*)eventReciver->vars[var],sizeof(Number)*(index+1));
				for(int c=eventReciver->numlen[var]; c<index+1; c++)
					eventReciver->vars[var][c].type=NNONE;
				eventReciver->numlen[var]=index+1;
			}
			if(vertObj3!=NULL && eventReciver->vars[var][index].type==NCHAR)
			{
				Number nIndex=vertObj3->exec();
				if(nIndex.type==NBOOL)
					index2=(int)nIndex.bval;
				else if(nIndex.type==NINT)
					index2=nIndex.ival;
				else if(nIndex.type==NFLOAT)
					index2=(int)nIndex.fval;
				if(index2<0)
					index2=0;
				if(index2<(signed)strlen(eventReciver->vars[var][index].cval))
				{
					if(value.type==NINT)
						eventReciver->vars[var][index].cval[index2]=(char)value.ival;
					else if(value.type==NCHAR)
					{
						int slen=strlen(eventReciver->vars[var][index].cval);
						int slen2=strlen(value.cval);
						if(slen2+index2>slen)
						{
							char*newchar=new char[slen2+index2+1];
							memcpy(newchar,eventReciver->vars[var][index].cval,slen);
							memcpy(&newchar[index2],value.cval,slen2+1);
							delete[] eventReciver->vars[var][index].cval;
							eventReciver->vars[var][index].cval=newchar;
						}
						else memcpy(&(eventReciver->vars[var][index].cval[index2]),value.cval,slen2);;
					}
					else if(value.type==NFLOAT)
						eventReciver->vars[var][index].cval[index2]=(char)value.fval;
				}
				else {
					int slen=strlen(eventReciver->vars[var][index].cval);
					int newlen;
					if(value.type==NCHAR)
						newlen=index2+strlen(value.cval)+2;
					else newlen=index2+2;

					char*newchar=new char[newlen];
					memcpy(newchar,eventReciver->vars[var][index].cval,slen);
					for(int c=slen; c<index2; c++)
						newchar[c]=' ';
					newchar[newlen-1]=(char)0;
					if(value.type==NINT)
						newchar[index2]=(char)value.ival;
					else if(value.type==NFLOAT)
						newchar[index2]=(char)value.fval;
					else if(value.type==NBOOL)
						newchar[index2]=(char)value.bval;
					else if(value.type==NCHAR)
						memcpy(&newchar[index2],value.cval,strlen(value.cval));
					delete[] (eventReciver->vars[var][index].cval);
					eventReciver->vars[var][index].cval=newchar;
				}
			}
			else 
			{
				vars[var][index]=value.fval;
				if(eventReciver->vars[var][index].type==NCHAR)
				{
					delete[] eventReciver->vars[var][index].cval;
					eventReciver->vars[var][index].cval=NULL;
				}
				if(value.type==NCHAR)
				{
					eventReciver->vars[var][index].type=NCHAR;
					int slen=strlen(value.cval);
					eventReciver->vars[var][index].cval=new char[slen+1];
					memcpy(eventReciver->vars[var][index].cval,value.cval,slen+1);
				}
				else eventReciver->vars[var][index]=value;
			}
			return value;
		}
		case SPRINT:
		{
			char*eventContent;
			value=vertObj->exec();
			switch(value.type)
			{
				case NFLOAT:
				{
					eventContent=(char*)malloc(42);
					char*printString=new char[12];
					sprintf(printString,"%%.%iLg",pref->outputLength);
					sprintf(eventContent,printString,value.fval);
					delete[]printString;
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
				default:
					eventContent=(char*)malloc(5);
					strcopy(eventContent,"none",4);
					break;
			}

			QCustomEvent *ev=new QCustomEvent(SIGPRINT);
			ev->setData(eventContent);

			QApplication::postEvent(eventReciver->eventReciver,ev);

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
					value.bval=(n1.fval!=(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval!=(long double)n2.ival);
				else value.bval=true;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval!=(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval!=(long double)n1.ival);
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
			value.fval=(long double)value.bval;
			return value;
		}
		case SNOT:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			if(n1.type==NBOOL)
				value.bval=!n1.bval;
			else if(n1.type==NINT)
				value.bval=!n1.ival;
			else if(n1.type==NFLOAT)
			{
				if(n1.fval==0)
					value.bval=true;
				else value.bval=false;
			}
			else value.bval=false;
			
			return value;
		}
		case SAND:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NBOOL)
				;
			else if(n1.type==NINT)
			{
				n1.bval=!(!n1.ival);
				n1.type=NBOOL;
			}
			else if(n1.type==NFLOAT)
			{
				if(n1.fval==0)
					n1.bval=false;
				else n1.bval=true;
				n1.type=NBOOL;
			}
			else {
				n1.bval=false;
				n1.type=NBOOL;
			}
			if(n2.type==NBOOL)
				;
			else if(n2.type==NINT)
			{
				n2.bval=!(!n1.ival);
				n2.type=NBOOL;
			}
			else if(n2.type==NFLOAT)
			{
				if(n2.fval==0)
					n2.bval=false;
				else n2.bval=true;
				n2.type=NBOOL;
			}
			else {
				n2.bval=false;
				n2.type=NBOOL;
			}
			value.bval=(n1.bval&&n2.bval);
			
			return value;
		}
		case SOR:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NBOOL)
				;
			else if(n1.type==NINT)
			{
				n1.bval=!(!n1.ival);
				n1.type=NBOOL;
			}
			else if(n1.type==NFLOAT)
			{
				if(n1.fval==0)
					n1.bval=false;
				else n1.bval=true;
				n1.type=NBOOL;
			}
			else {
				n1.bval=false;
				n1.type=NBOOL;
			}
			if(n2.type==NBOOL)
				;
			else if(n2.type==NINT)
			{
				n2.bval=!(!n1.ival);
				n2.type=NBOOL;
			}
			else if(n2.type==NFLOAT)
			{
				if(n2.fval==0)
					n2.bval=false;
				else n2.bval=true;
				n2.type=NBOOL;
			}
			else {
				n2.bval=false;
				n2.type=NBOOL;
			}
			value.bval=(n1.bval||n2.bval);
			
			return value;
		}
		case PLUS:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			if(value.type==NINT)
			{
				if(n.type==NINT)
					value.ival+=n.ival;
				else if(n.type==NFLOAT)
				{
					value.fval=(long double)value.ival+n.fval;
					value.type=NFLOAT;
				}
				else if(n.type==NCHAR)
					value.ival+=(long long)n.cval[0];
				else if(n.type==NBOOL)
					value.ival+=(long long)n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
			}
			else if(value.type==NFLOAT)
			{
				if(n.type==NINT)
					value.fval+=(long double)n.ival;
				else if(n.type==NFLOAT)
					value.fval+=n.fval;
				else if(n.type==NCHAR)
					value.fval+=(long double)n.cval[0];
				else if(n.type==NBOOL)
					value.fval+=(long double)n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
			}
			else if(value.type==NCHAR)
			{
				if(n.type==NINT)
					value.cval[0]+=(char)n.ival;
				else if(n.type==NFLOAT)
					value.cval[0]+=(char)n.fval;
				else if(n.type==NCHAR)
				{
					int strlen1=strlen(value.cval);
					int strlen2=strlen(n.cval);
					char*newstring=new char[strlen1+strlen2+1];
					memcpy(newstring,value.cval,strlen1);
					memcpy(&newstring[strlen1],n.cval,strlen2+1);
					delete[] value.cval;
					value.cval=newstring;
				}
				else if(n.type==NBOOL)
					value.cval[0]+=(char)n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
			}
			else if(value.type==NBOOL)
			{
				if(n.type==NINT)
				{
					value.type=NINT;
					value.ival=(long long)value.bval+n.ival;
				}
				else if(n.type==NFLOAT)
				{
					value.fval=(long double)value.bval+n.fval;
					value.type=NFLOAT;
				}
				else if(n.type==NCHAR)
					value.bval+=(bool)n.cval[0];
				else if(n.type==NBOOL)
					value.bval+=n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
				value.bval=!(!value.bval);
			}
			else {
				value.fval=NAN;
				value.type=NNONE;
			}
			switch(value.type)
			{
				case NINT:
					value.fval=(long double)value.ival; break;
				case NBOOL:
					value.fval=(long double)value.bval; break;
				case NCHAR:
					value.fval=(long double)value.cval[0]; break;
				case NNONE:
					value.fval=NAN; break;
			}
			return value;
		}
		case MINUS:
		{
			value=vertObj->exec();
			Number n=vertObj2->exec();
			if(value.type==NINT)
			{
				if(n.type==NINT)
					value.ival-=n.ival;
				else if(n.type==NFLOAT)
				{
					value.fval=(long double)value.ival-n.fval;
					value.type=NFLOAT;
				}
				else if(n.type==NCHAR)
					value.ival-=(long long)n.cval[0];
				else if(n.type==NBOOL)
					value.ival-=(long long)n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
			}
			else if(value.type==NFLOAT)
			{
				if(n.type==NINT)
					value.fval-=(long double)n.ival;
				else if(n.type==NFLOAT)
					value.fval-=n.fval;
				else if(n.type==NCHAR)
					value.fval-=(long double)n.cval[0];
				else if(n.type==NBOOL)
					value.fval-=(long double)n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
			}
			else if(value.type==NCHAR)
			{
				if(n.type==NINT)
					value.cval[0]-=(char)n.ival;
				else if(n.type==NFLOAT)
					value.cval[0]-=(char)n.fval;
				else if(n.type==NCHAR)
					value.cval[0]-=n.cval[0];
				else if(n.type==NBOOL)
					value.cval[0]-=(char)n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
			}
			else if(value.type==NBOOL)
			{
				if(n.type==NINT)
				{
					value.type=NINT;
					value.ival=(long long)value.bval-n.ival;
				}
				else if(n.type==NFLOAT)
				{
					value.type=NFLOAT;
					value.fval=(float)value.bval-n.fval;
				}
				else if(n.type==NCHAR)
					value.bval-=(bool)n.cval[0];
				else if(n.type==NBOOL)
					value.bval-=n.bval;
				else {
					value.fval=NAN;
					value.type=NNONE;
				}
				value.bval=!(!value.bval);
			}
			else {
				value.fval=NAN;
				value.type=NNONE;
			}
			switch(value.type)
			{
				case NINT:
					value.fval=(long double)value.ival; break;
				case NBOOL:
					value.fval=(long double)value.bval; break;
				case NCHAR:
					value.fval=(long double)value.cval[0]; break;
				case NNONE:
					value.fval=NAN; break;
			}
			return value;
		}
		case SLESS:
		{
			value.type=NBOOL;
			Number n1=vertObj->exec();
			Number n2=vertObj2->exec();
			if(n1.type==NFLOAT)
			{
				if(n2.type==NFLOAT)
					value.bval=(n1.fval<n2.fval);
				else if(n2.type==NBOOL)
					value.bval=(n1.fval<(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval<(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval>(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval>(long double)n1.ival);
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
			value.fval=(long double)value.bval;
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
					value.bval=(n1.fval>n2.fval);
				else if(n2.type==NBOOL)
					value.bval=(n1.fval>(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval>(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval<(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval<(long double)n1.ival);
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
			value.fval=(long double)value.bval;
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
					value.bval=(n1.fval<=n2.fval);
				else if(n2.type==NBOOL)
					value.bval=(n1.fval<=(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval<=(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval>=(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval>=(long double)n1.ival);
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
			value.fval=(long double)value.bval;
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
					value.bval=(n1.fval>=n2.fval);
				else if(n2.type==NBOOL)
					value.bval=(n1.fval>=(long double)n2.bval);
				else if(n2.type==NINT)
					value.bval=(n1.fval>=(long double)n2.ival);
				else value.bval=false;
			}
			else if(n2.type==NFLOAT)
			{
				if(n1.type==NBOOL)
					value.bval=(n2.fval<=(long double)n1.bval);
				else if(n1.type==NINT)
					value.bval=(n2.fval<=(long double)n1.ival);
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
			value.fval=(long double)value.bval;
			return value;
		}
		case SRUN:
		{
			if(eventReciver->subprograms[var]!=NULL)
				return ((Script*)eventReciver->subprograms[var])->exec();
			else 
			{
				value.type=NNONE;
				value.fval=NAN;
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
	//		perror("stop");
			QCustomEvent*killEvent=new QCustomEvent(SIGFINISHED);
			QApplication::postEvent(eventReciver->eventReciver,killEvent);
			pthread_exit(0);
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
							value.ival=(long long)n.fval;
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
					value.fval=(long double)value.ival;
					return value;
				case NFLOAT:
					switch(n.type)
					{
						case NINT:
							value.fval=(long double)n.ival;
							break;
						case NFLOAT:
							value.fval=n.fval;
							break;
						case NCHAR:
							value.fval=strtold(n.cval,NULL);
							break;
						case NBOOL:
							value.fval=n.bval;
							break;
						default:
							value.fval=NAN;
					}
					return value;
				case NBOOL:
					switch(n.type)
					{
						case NINT:
							value.bval=!(!(bool)n.ival);
							break;
						case NFLOAT:
							if(n.fval==0.0)
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
					value.fval=(long double)value.bval;
					return value;
				case NCHAR:
					value.cval=new char[42];
					switch(n.type)
					{
						case NINT:
							sprintf(value.cval,"%lli",n.ival);
							break;
						case NFLOAT:
							sprintf(value.cval,"%Lg",n.fval);
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
					value.fval=NAN;
					return value;
				default:
					value.type=NNONE;
					value.fval=NAN;
					return value;
			}
		}
		case SRAND:
		{
			
			value=vertObj->exec();
			value.type=NFLOAT;
#if RAND_MAX < 1000000000
			value.fval=(((rand()*(1000000000/RAND_MAX))%1000000000)*value.fval)/1000000000;
#else
			value.fval=((rand()%1000000000)*value.fval)/1000000000;
#endif
			return value;
		}
		case SSLEEP:
		{
			value=vertObj->exec();
			int sleeptime;
			if(value.type ==NINT)
				sleeptime=value.ival;
			else sleeptime=(int)value.fval;
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
	//		perror("SETCURSOR in exec: "+QString::number(pthread_self()));
			int*coords=(int*)malloc(sizeof(int)*2);
			value=vertObj->exec();
			if(value.type==NINT)
				coords[0]=value.ival;
			else coords[0]=(int)value.fval;
			value=vertObj2->exec();
			if(value.type==NINT)
				coords[1]=value.ival;
			else coords[1]=(int)value.fval;
			QCustomEvent *ev=new QCustomEvent(SIGSETTEXTPOS);
			ev->setData(coords);
//			qApp->lock();
			QApplication::postEvent(eventReciver->eventReciver,ev);
//			QApplication::sendPostedEvents();
//			qApp->unlock();
//			free(coords);
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SCLEARTEXT:
		{

			QCustomEvent*clearEvent=new QCustomEvent(SIGCLEARTEXT);
			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
//			QApplication::sendPostedEvents();

			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SGETKEY:
		{
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGGETKEY);
			qApp->lock();
			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
			QApplication::sendPostedEvents();
			qApp->unlock();
			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
				else usleep(500);
			}
			value.cval[0]=*((char*)(eventReciver->data));
			value.fval=(long double)value.cval[0];
			free(eventReciver->data);
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SKEYSTATE:
		{
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGKEYSTATE);
			qApp->lock();
			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
			QApplication::sendPostedEvents();
			qApp->unlock();
			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
				else usleep(500);
			}
			value.cval[0]=*((char*)(eventReciver->data));
			value.fval=(long double)value.cval[0];
			free(eventReciver->data);
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SGETLINE:
		{
			eventReciver->data=NULL;
			QCustomEvent*clearEvent=new QCustomEvent(SIGGETLINE);
			qApp->lock();
			QApplication::postEvent(eventReciver->eventReciver,clearEvent);
			QApplication::sendPostedEvents();
			qApp->unlock();
			while(eventReciver->data==NULL)
			{
				if(eventReciver->status)
					if(eventReciver->exit)
					{
						eventReciver->exit=false;
						pthread_exit(0);
					}
				else usleep(500);
			}
			int dataLen=strlen((char*)eventReciver->data);
			value.cval=new char[dataLen+1];
			memcpy(value.cval,eventReciver->data,dataLen+1);
			free(eventReciver->data);
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SINIT:
		{
			value=nextObj->exec();
			QCustomEvent*killEvent=new QCustomEvent(SIGFINISHED);
			QApplication::postEvent(eventReciver->eventReciver,killEvent);
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

void printError(const char*text,int num,QObject*eventReciver)
{
		QCustomEvent*debugEvent=new QCustomEvent(SIGDEBUG);
		char*debugData=(char*)malloc(strlen(text)+5);
		memcpy(debugData,&num,4);
		memcpy(&debugData[4],text,strlen(text)+1);
		debugEvent->setData(debugData);
		QApplication::postEvent(eventReciver,debugEvent);
}



