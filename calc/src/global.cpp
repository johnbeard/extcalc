#include "global.h"




int bracketFind(char* string,char* searchString, int start)
{
	//special search options:
	//searchString= "a-z"
	//searchString= "A-Z"
	//searchString= "0-9"
	
	if(searchString == "a-z")
	{
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c<(int)strlen(string); c++)
		{
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(string[c] == '(')
					bracket++;
				else if(string[c] == '{')
					brace++;
				else if(string[c] == '\"')
					quote=true;
				else if(string[c] >= 'a' && string[c] <= 'z')
					return c;
			}
			else {
				if(!quote)
				{
					if(string[c] == '(')
						bracket++;
					else if(string[c] == ')')
						bracket--;
					else if(string[c] == '{')
						brace++;
					else if(string[c] == '}')
						brace--;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
		}
	}
	else if(searchString == "A-Z")
	{
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c<(int)strlen(string); c++)
		{
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(string[c] == '(')
					bracket++;
				else if(string[c] == '{')
					brace++;
				else if(string[c] == '\"')
					quote=true;
				else if(string[c] >= 'A' && string[c] <= 'Z')
					return c;
			}
			else {
				if(!quote)
				{
					if(string[c] == '(')
						bracket++;
					else if(string[c] == ')')
						bracket--;
					else if(string[c] == '{')
						brace++;
					else if(string[c] == '}')
						brace--;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
		}
	}
	else if(searchString == "0-9")
	{
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c<(int)strlen(string); c++)
		{
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(string[c] == '(')
					bracket++;
				else if(string[c] == '{')
					brace++;
				else if(string[c] == '\"')
					quote=true;
				else if(string[c] >= '0' && string[c] <= '9')
					return c;
			}
			else {
				if(!quote)
				{
					if(string[c] == '(')
						bracket++;
					else if(string[c] == ')')
						bracket--;
					else if(string[c] == '{')
						brace++;
					else if(string[c] == '}')
						brace--;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
		}
	}
	else{
		int searchLen=strlen(searchString);
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c<(int)strlen(string); c++)
		{
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(strncmp(&string[c],searchString,searchLen) == 0)
					return c;
				else if(string[c] == '(')
					bracket++;
				else if(string[c] == '{')
					brace++;
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
						if(bracket == 0 && brace == 0)
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
						if(bracket == 0 && brace == 0)
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
	}
	return -1;
}


int bracketFindRev(char* string,char* searchString, int start)
{
	if(start==-1)
		start=strlen(string)-1;
	if(searchString == "a-z")
	{
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c>=0; c--)
		{
	
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(string[c] == ')')
					bracket++;
				else if(string[c] == '}')
					brace++;
				else if(string[c] == '\"')
					quote=true;
				else if(string[c] >= 'a' && string[c] <= 'z')
					return c;
			}
			else {
				if(!quote)
				{
					if(string[c] == ')')
						bracket++;
					else if(string[c] == '(')
						bracket--;
					else if(string[c] == '{')
						brace--;
					else if(string[c] == '}')
						brace++;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
		}
	}
	else if(searchString == "A-Z")
	{
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c>=0; c--)
		{
	
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(string[c] == ')')
					bracket++;
				else if(string[c] == '}')
					brace++;
				else if(string[c] == '\"')
					quote=true;
				else if(string[c] >= 'A' && string[c] <= 'Z')
					return c;
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
					else if(string[c] == '{')
						brace--;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
		}
	}
	else if(searchString == "0-9")
	{
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c>=0; c--)
		{
	
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(string[c] == ')')
					bracket++;
				else if(string[c] == '}')
					brace++;
				else if(string[c] == '\"')
					quote=true;
				else if(string[c] >= '0' && string[c] <= '9')
					return c;
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
					else if(string[c] == '{')
						brace--;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
		}
	}
	else {
		int searchLen=strlen(searchString);
		int bracket=0,brace=0;
		bool quote=false;
		for(int c=start; c>=0; c--)
		{
	
			if(bracket == 0 && brace == 0 && !quote)
			{
				if(strncmp(&string[c-searchLen+1],searchString,searchLen) == 0)
					return c;
				else if(string[c] == ')')
					bracket++;
				else if(string[c] == '}')
					brace++;
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
					else if(string[c] == '{')
						brace--;
					else if(string[c] == '\"')
						quote=!quote;
				}
				else if(string[c] == '\"')
					quote=!quote;
			}
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



char* checkString(char* str,Preferences*pref,long double*vars)
{
	char* calcString=new char[strlen(str)+1];
	char*temp;
	memcpy(calcString,str,strlen(str)+1);
	int calcLen=strlen(calcString);
	bool quote=false;

	for(unsigned int c=0; c<calcLen; c++)	//Step 1: remove whitespace, correct strings
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
				
				if(strlen(calcString)>c+1)
					calcString=strcut(calcString,c+1);
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
			else calcString=strcut(calcString,c,pos-c);
		}
		if(calcString[c] == ' ' || calcString[c] == '\t' || calcString[c] == '\n')
		{
			calcString=strcut(calcString,c);
			c--;
		}
		if(calcString[c] == '\\')//reserved sign
		{
			return NULL;
		}
		calcLen=strlen(calcString);
	}
	quote=false;
	for(unsigned int c=0; c<calcLen; c++)	//Step 2: replace special functions
	{
		if(calcLen <= 0)
			return NULL;
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(strncmp(&calcString[c],"root",4) == 0)
		{
			calcString=strcut(calcString,c,4);
			calcString=strins(calcString,"$r",c);
		}
		if(strncmp(&calcString[c],"d/dx",4) == 0)
		{
			calcString=strcut(calcString,c,4);
			calcString=strins(calcString,"\\d",c);
		}
		if(strncmp(&calcString[c],"integ",5) == 0)
		{
			calcString=strcut(calcString,c,5);
			calcString=strins(calcString,"\\i",c);
		}
		if(strncmp(&calcString[c],"bin",3) == 0)
		{
			calcString=strcut(calcString,c,3);
			calcString=strins(calcString,"\\b",c);
		}
		if(strncmp(&calcString[c],"oct",3) == 0)
		{
			calcString=strcut(calcString,c,3);
			calcString=strins(calcString,"\\o",c);
		}
		if(strncmp(&calcString[c],"dec",3) == 0)
		{
			calcString=strcut(calcString,c,3);
			calcString=strins(calcString,"\\c",c);
		}
		if(strncmp(&calcString[c],"hex",3) == 0)
		{
			calcString=strcut(calcString,c,3);
			calcString=strins(calcString,"\\h",c);
		}
		
		if(calcString[c] == 'x' && pref->calcType!=BASE)
			calcString[c]='X';
		
		if(calcString[c] == 'z' && pref->calcType!=BASE)
			calcString[c]='Z';

		if(calcString[c] == '-' && calcString[c+1] == '-' )
		{
			calcString[c]='+';
			calcString=strcut(calcString,c+1);
		}
		if(calcString[c] == (char)0xb2)	// second power
		{
			calcString=strcut(calcString,c,1);
			if(c>0)
				if(calcString[c-1] == (char)0xc2)
				{
					calcString=strcut(calcString,c-1,1);
					c--;
				}
			calcString=strins(calcString,"^2",c);

		}
		if(calcString[c] == (char)0xb3)	// third power
		{
			calcString=strcut(calcString,c,1);
			if(c>0)
				if(calcString[c-1] == (char)0xc2)
				{
					calcString=strcut(calcString,c-1,1);
					c--;
				}
			calcString=strins(calcString,"^3",c);
		}
		if(c>0 && !(calcString[c+1]>='a' && calcString[c+1]<='z'))
		{
			if(calcString[c-1]>='0' && calcString[c-1]<='9')
			{
				if(calcString[c] == 'f')
				{
					calcString=strcut(calcString,c);
					calcString=strins(calcString,"e-15",c);
				}
				if(calcString[c+1] == 'n')
				{
					calcString=strcut(calcString,c+1);
					calcString=strins(calcString,"e-9",c+1);
				}
				if(calcString[c] == 'p')
				{
					calcString=strcut(calcString,c);
					calcString=strins(calcString,"e-12",c);
				}
				if(calcString[c] == (char)0xb5)	//micro
				{
					calcString=strcut(calcString,c);
					if(c>0)
						if(calcString[c-1] == (char)0xc2)
					{
						calcString=strcut(calcString,c-1,1);
						c--;
					}
					calcString=strins(calcString,"e-6",c);
				}		
				if(calcString[c] == 'm')
				{
					calcString=strcut(calcString,c);
					calcString=strins(calcString,"e-3",c);
				}
				if(calcString[c] == 'k')
				{
					calcString=strcut(calcString,c);
					calcString=strins(calcString,"e3",c);
				}
			}
		}
		if((calcString[c] == '+' || calcString[c] == '-' || 
				  calcString[c] == '*' || calcString[c] == '/' || 
				  calcString[c] == '^'
		   ) && calcString[c+1] == '+')
		{
			calcString=strcut(calcString,c+1);
		}
		else if((calcString[c+1] == '+' || calcString[c+1] == '-') && calcString[c] == '+')
		{
			calcString=strcut(calcString,c);
		}
		calcLen=strlen(calcString);
	}
	
	quote=false;
	for(unsigned int c=1; c<calcLen; c++)		//Step 3: insert not written *-signs
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
			calcString=strins(calcString,"*",c);


		if(
				 (calcString[c] == '.' ||
				 (calcString[c] >= '0' && calcString[c] <= '9'))
				 &&
				 (//calcString[c-1] == '!' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z'))
		  )
			calcString=strins(calcString,"*",c);
		
		calcLen=strlen(calcString);
	}
	quote=false;
	for(unsigned int c=0; c<calcLen-1; c++)		//Step 4: replace constants
	{
		if(calcLen <= 0)
			return NULL;
		if(calcString[c]=='\"')
			quote=!quote;
		if(quote)
			continue;
		if(strncmp(&calcString[c],"ans",3) == 0)
		{
			calcString=strcut(calcString,c,3);
			char*lastRes=new char[60];
			if(pref->calcType == SCIENTIFIC)
			{
				sprintf(lastRes,"%'.40Lg",vars[26]);
				calcString=strins(calcString,"()",c);
				calcString=strins(calcString,lastRes,c+1);
			}
			else {
				sprintf(lastRes,"\\c%lli",(long long)vars[26]);
				calcString=strins(calcString,"()",c);
				calcString=strins(calcString,lastRes,c+1);
			}
			
			delete[]lastRes;
		}
		if(strncmp(&calcString[c],"pi",2) == 0)
		{
			calcString=strcut(calcString,c,2);
//			char*pi=new char[60];
//			sprintf(pi,"%'.40Lg",(long double)PI);
			calcString=strins(calcString,"()",c);
			calcString=strins(calcString,SPI,c+1);
			c+=strlen(SPI)-2;
		}
		if(strncmp(&calcString[c],"eu",2) == 0)
		{
			calcString=strcut(calcString,c,2);
//			char*euler=new char[60];
//			sprintf(euler,"%'.40Lg",(long double)EULER);
			calcString=strins(calcString,"()",c);
			calcString=strins(calcString,SEULER,c+1);
			c+=strlen(SEULER)-2;
		}
		calcLen=strlen(calcString);
	}
	quote=false;
	for(unsigned int c=1; c<calcLen; c++)		//Step 5: insert not written *-signs
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
			calcString=strins(calcString,"*",c);


		if(
				 (calcString[c] == '.' ||
				 (calcString[c] >= '0' && calcString[c] <= '9'))
				 &&
				 (//calcString[c-1] == '!' ||
				 ((pref->calcType==SCIENTIFIC && calcString[c-1] >= 'A' || calcString[c-1]>='G') && calcString[c-1]<='Z'))
		  )
			calcString=strins(calcString,"*",c);
		
		calcLen=strlen(calcString);
	}
	

	return calcString;
	
}




long double calculate(char* line,Preferences*pref,long double*vars)
{
//	perror(line);
	if(line == NULL)
		return (NAN);
	int len=strlen(line);
	if(len <=0)
		return (NAN);
	long double complete=(long double)0.0;
	char*recString1,*recString2,*recString3;

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
		vars[var]=calculate(recString1,pref,vars);
		delete[]recString1;
		return vars[var];
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
			   || line[pos2-1]=='.' || line[pos2-1]==')') && pos2>0)
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
			if((line[pos1-1] >='A' && line[pos1-1]<='Z'		//binary + operator
						 || line[pos1-1]>='0' && line[pos1-1]<='9'
						 || line[pos1-1]=='.' || line[pos1-1]==')') && pos1>0)
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
/*	else if(bracketFind(line,"$r") != -1)	//	root operation for extcalc (binary operator)
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
*/	else if(line[0]>='a' && line[0]<='z') 
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
			struct timeval rndTime;
			gettimeofday(&rndTime,NULL);
			srand(rndTime.tv_usec*rndTime.tv_sec);
			complete=((rand()%1000000000)*calculate(&line[3],pref,vars))/1000000000;
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
			int num=calculate(&line[1],pref,vars);
			if(num==0)
				return(1.0);
			else return(0.0);
		}
		else{
			return (NAN);
		}
		if(complete < pow(10.0,-pref->precisision+1) && complete > -1.0*pow(10.0,-pref->precisision+1))
		{
			complete=0.0;
		}
	}
	else if(line[0]=='~')
	{
		long long num=calculate(&line[1],pref,vars);
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
	else if(bracketFind(line,"\\r(") != -1)		//root operation for calc (operator with arguments)
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
	else if(bracketFind(line,"\\i(") != -1)
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
		double step;
		vars[23]=start;
		oldy=integ.calc();
		vars[23]=end;
		y=integ.calc();
		line1[0]=(y+oldy)*(end-start)/2.0;
		double fail=(1.0/0.0),oldfail=0.0;
		
		int num=1;
		int steps;
		while(true)
		{
			delete[]line2;
			line2=line1;
			line1=new double[num+1];
			line1[0]=0.0;
			
			steps=pow(2,(num-1));
			
			for(int c=1; c<=steps; c++)
			{
				vars[23]=start+((2*c-1)*(end-start))/pow(2,num);
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
				break;
			if(fail>oldfail)
			{
				line1[num-1]=NAN;
				break;
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
		vars[23]=pos-step;
		double w1=diff.calc();
		vars[23]=pos+step;
		double w2=diff.calc();
		complete=(w2-w1)/((double)2.0*step);
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

	}
	else if((pref->calcType == SCIENTIFIC && line[0]>='A' || line[0]>='G') && line[0]<='Z')
	{

		complete=vars[(int)line[0]-65];

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
			   || line[pos2-1]=='.' || line[pos2-1]==')') && pos2>0)
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
						 || line[pos1-1]=='.' || line[pos1-1]==')') && pos1>0)
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
/*	else if(bracketFind(line,"$r") != -1)	//	root operation for extcalc (binary operator)
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
*/	else if(line[0]>='a' && line[0]<='z') 
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
			return -1;
		}

		return 0;
	}
	else if(bracketFind(line,"$r(") != -1)		//root operation for calc (operator with arguments)
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
	}
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
		bool inv=false;
		double start,end;
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
		operation=NONE;
		var=((int)line[0])-65;
		horzObj=NULL;
		vertObj=NULL;

		
	}
	else{
		operation=NONE;
		number=strtod(line,NULL);
		var=-1;
		horzObj=NULL;
		vertObj=NULL;
		return 0;
//		 line.toDouble();
	}
	return -1;
}




double Calculate::calc()
{
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
//     Verzweigung:
			//    
//         end
//          |
//         NONE - start
//           |
//        INTEGRAL - function
			//
//        integral(function,start,end);

			double result,complete=(double)0.0;
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

			double * line1=new double;						// Romberg-Verfahren
			double *line2=new double[3];
			double y,oldy;
			double step;
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
				steps=pow(2,(num-1));
				for(int c=1; c<=steps; c++)
				{
					vars[23]=start+((2*c-1)*(end-start))/pow(2,num);
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
					break;
				if(fail>oldfail)
				{
					line1[num-1]=NAN;
					break;
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
//	perror("split: "+QString(line));
	bool init=false;
	char*rest;
	if(parent==NULL)
	{
		operation=SINIT;
		rest=line;
		init =true;
	}
	else rest=parse(line);
//	perror("split rest: "+QString(rest));
	if(rest!=NULL)
	{
		nextObj=new Script(this,NULL,pref,vars,eventReciver);
		nextObj->split(rest);
		if(parent!=NULL)
			delete[]rest;
//		else perror("complete finish");
	}
//	else perror("finished");
	return 0;
}


char* Script::parse(char* line)
{
	int pos1;
	int len=strlen(line);
//	perror("parse: "+QString(line));
	if((pos1=bracketFind(line,"if(")) == 0)
	{
		int pos2=bracketFind(line,")");
		if(pos2<3 || len<pos2+2)
		{
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
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			return NULL;
		}
		char*recString1=new char[pos2-5];
		strcopy(recString1,&line[6],pos2-6);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		int pos3;
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
	else if((pos1=bracketFind(line,";")) != -1)
	{
//		perror("semicolon");
		operation=SSEMICOLON;
		char*recString1=new char[pos1+1];
		strcopy(recString1,line,pos1);
		if(pos1>0)
			vertObj=new Script(this,recString1,pref,vars,eventReciver);
		else vertObj=NULL;
		if(len-pos1>1)
		{
			char*recString2=new char[len-pos1];
			strcopy(recString2,&line[pos1+1],len-pos1-1);
			return recString2;
		}
		else return NULL;

	}
	else if((pos1=bracketFind(line,"print(")) == 0)
	{
//		perror("print");
		operation=SPRINT;
		int pos2=bracketFind(line,")");
		if(pos2<7)
		{
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
		int pos3=bracketFind(line,")",10);
		if(pos2<11 || pos3<12 || pos3<pos2)
		{
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
			operation=SFAIL;
			return NULL;
		}
		char*recString1=new char[pos2-5];
		strcopy(recString1,&line[6],pos2-6);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		delete[]recString1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"->")) != -1)
	{
		operation=SSET;
		char*recString1=new char[pos1+1];
		char*recString2=new char[2];
		strcopy(recString1,line,pos1);
		strcopy(recString2,&line[pos1+2],1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		var=recString2[0]-65;
		if(var<0 || var>25)
		{
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			delete[]recString1;
			delete[]recString2;
			return NULL;
		}
		delete[]recString1;
		delete[]recString2;
		return NULL;
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
	else if(pos1=bracketFind(line,"||") != -1)
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
		var=line[0]-65;
		if(var<0 || var>25)
		{
			operation=SFAIL;
			horzObj=vertObj=NULL;
			number=NAN;
			delete[]recString1;
			return NULL;
		}
		delete[]recString1;
		return NULL;
	}
	else if((pos1=bracketFind(line,"+")) != -1)
	{
		operation=PLUS;
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
		return NULL;
	}
	else if(bracketFind(line,"getline") !=-1)
	{
		if(len>7)
			operation=SFAIL;
		else operation=SGETLINE;
		value.type=NCHAR;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"getkey") !=-1)
	{
		if(len>6)
			operation=SFAIL;
		else operation=SGETKEY;
		value.type=NCHAR;
		value.cval=new char[2];
		value.cval[1]=(char)0;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"keystate") !=-1)
	{
		if(len>8)
			operation=SFAIL;
		else operation=SKEYSTATE;
		value.type=NCHAR;
		value.cval=new char[2];
		value.cval[1]=(char)0;
		vertObj=vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"!") ==0)
	{
		if(len<2)
			operation=SFAIL;
		else operation=SNOT;
		char*recString1=new char[len];
		strcopy(recString1,&line[1],len-1);
		vertObj=new Script(this,recString1,pref,vars,eventReciver);
		vertObj2=vertObj3=horzObj=nextObj=NULL;
		return NULL;
	}
	else if(bracketFind(line,"A-Z")==0 && len==1)
	{
		operation=SVAR;
		var=line[0]-65;
		return NULL;
	}
	else if(line[0] == '(')
	{
//		perror("bracket");
		int pos1=bracketFind(line,")");
		if(pos1<1)
		{
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
				return NULL;
			}
			else if(strcmp(castType,"float")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NFLOAT;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				return NULL;
			}
			else if(strcmp(castType,"bool")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NBOOL;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
				return NULL;
			}
			else if(strcmp(castType,"string")==0)
			{
				char*recString1=new char[len-pos1];
				strcopy(recString1,&line[pos1+1],len-pos1-1);
				operation=SCAST;
				value.type=NCHAR;
				vertObj=new Script(this,recString1,pref,vars,eventReciver);
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
	else if((line[0] == '\"' && line[len-1]=='\"'))
	{
		operation=SVALUE;
		value.fval=NAN;
		value.type=NCHAR;
		value.cval=new char[len-1];
		strcopy(value.cval,&line[1],len-2);
		return NULL;
	}
	else if((line[0] == '\"' && line[len-1]=='\"'))
	{
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
//	perror("Running script command: "+QString::number(operation));
	
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
			return eventReciver->vars[var];
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

				}
			}
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SSET:
		{
			value=vertObj->exec();
			if(value.type==NINT)
				value.fval=(long double)value.ival;
			else if(value.type==NFLOAT);
			else if(value.type==NCHAR)
				value.fval=(long double)value.cval[0];
			else if(value.type==NBOOL)
				value.fval=(long double)value.bval;
			
			vars[var]=value.fval;
			eventReciver->vars[var]=value;
			return value;
		}
		case SPRINT:
		{
			value=vertObj->exec();
			switch(value.type)
			{
				case NFLOAT:
				{
					char*printString=new char[12];
					sprintf(printString,"%%.%iLg",pref->outputLength);
					fprintf(stderr,printString,value.fval);
					delete[]printString;
					break;
				}
				case NINT:
				{
					fprintf(stderr,"%lli",value.ival);
					break;
				}
				case NBOOL:
					if(value.bval)
						fprintf(stderr,"true");
					else fprintf(stderr,"false");
					break;
				case NCHAR:
				{
					//printf(value.cval);
					fprintf(stderr,value.cval);
					break;
				}
				default:
					fprintf(stderr,"none");
					break;
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
				n1.type==NBOOL;
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
					value.ival+=(long long)n.fval;
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
					value.cval[0]+=n.cval[0];
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
					value.bval+=(bool)n.ival;
				else if(n.type==NFLOAT)
					value.bval+=(bool)n.fval;
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
					value.ival-=(long long)n.fval;
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
					value.bval-=(bool)n.ival;
				else if(n.type==NFLOAT)
					value.bval-=(bool)n.fval;
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
		case SCAST:
		{
			Number n=vertObj->exec();
			switch(value.type)
			{
				case NINT:
					switch(n.type)
					{
						case NINT:
							break;
						case NFLOAT:
							value.ival=(int)n.fval;
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
							value.fval=(float)n.ival;
							break;
						case NFLOAT:
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
			int x,y;
			value=vertObj->exec();
			if(value.type==NINT)
				x=value.ival;
			else x=(int)value.fval;
			value=vertObj2->exec();
			if(value.type==NINT)
				y=value.ival;
			else y=(int)value.fval;
			
			//printf("\033[%i;%iH",y+1,x+1);
			fprintf(stderr,"\033[%i;%iH",y+1,x+1);

			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SCLEARTEXT:
		{

			fprintf(stderr,"\033[2J");
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SGETKEY:
		{

			value.cval[0]=(char)getchar();
			value.fval=(long double)value.cval[0];
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SKEYSTATE:
		{
			struct termios terminfo;
			int time,min;
			tcgetattr(fileno(stdout),&terminfo);
			time=terminfo.c_cc[VTIME];
			min=terminfo.c_cc[VMIN];
			terminfo.c_cc[VTIME]=0;
			terminfo.c_cc[VMIN]=0;

			if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
				perror("tcsetattr fehler");
			value.cval[0]=(char)getchar();
			value.fval=(long double)value.cval[0];
			
			terminfo.c_cc[VTIME]=time;
			terminfo.c_cc[VTIME]=min;
			if(tcsetattr(fileno(stdout),TCSANOW,&terminfo)!=0)
				perror("tcsetattr fehler");
						
			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SGETLINE:
		{
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

			value.cval=new char[strlen(input)+1];
			memcpy(value.cval,input,strlen(input)+1);

			free(input);

			if(nextObj==NULL)
				return value;
			else return nextObj->exec();
		}
		case SINIT:
		{
			value=nextObj->exec();
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



