#include "statistics.h"




void StatisticsWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();
	if(fullscreen)
	{
		splitter->setGeometry(20,50,width-40,height-100);
		drawButton->setGeometry(20,height-45,90,35);
		typeBox->setGeometry(120,height-45,90,35);
		maximizeButton->setGeometry(220,height-45,90,35);
	}
	else
	{
		splitter->setGeometry(20,50,width-40,height-290);

		drawButton->setGeometry(width/2+15,height-220,90,35);
		typeBox->setGeometry(width/2+115,height-220,90,35);
		maximizeButton->setGeometry(width/2+215,height-220,90,35);
		
		standardButtons->setGeometry(20,height-220,280,200);
		

		if(type==STATAPPROX)
		{
			functionTypeLabel->setGeometry(width/2+15,height-180,170,25);
			functionTypeBox->setGeometry(width/2+195,height-180,110,25);

			listNumberLabel->setGeometry(width/2+15,height-150,190,20);
			listNumber->setGeometry(width/2+205,height-150,100,20);
			
			calculateButton->setGeometry(width/2+215,height-120,90,25);
			
			resultLabel->setGeometry(width/2+15,height-90,290,20);
			result->setGeometry(width/2+15,height-65,290,20);
		
			copyFunctionLabel->setGeometry(width/2+15,height-40,130,20);
			copyFunction->setGeometry(width/2+155,height-40,80,20);
			copyButton->setGeometry(width/2+245,height-40,60,20);	
		}
		if(type==STATINTERPOL)
		{
			listNumberLabel->setGeometry(width/2+15,height-180,190,20);
			listNumber->setGeometry(width/2+205,height-180,100,20);
			
			calculateButton->setGeometry(width/2+215,height-155,90,25);
			
			resultLabel->setGeometry(width/2+15,height-115,290,20);
			result->setGeometry(width/2+15,height-90,290,20);
		
			copyFunctionLabel->setGeometry(width/2+15,height-65,65,20);
			copyFunction->setGeometry(width/2+155,height-65,80,20);
			copyButton->setGeometry(width/2+245,height-65,60,20);
		}
		if(type==STATLINEGRAPH)
		{

			listNumberLabel->setGeometry(width/2+15,height-180,190,20);
			listNumber->setGeometry(width/2+205,height-180,100,20);
			
			stepsLabel->setGeometry(width/2+15,height-150,220,20);
			stepsBox->setGeometry(width/2+235,height-150,70,20);
		}
		if(type==STATBARGRAPH)
		{
			listNumberLabel->setGeometry(width/2+15,height-180,190,20);
			listNumberBox->setGeometry(width/2+205,height-180,100,20);
			
			stepsLabel->setGeometry(width/2+15,height-150,220,20);
			stepsBox->setGeometry(width/2+235,height-150,70,20);			
			
		}
		if(type==STATNORMAL)
		{

			listNumberLabel->setGeometry(width/2+15,height-180,190,20);
			listNumberBox->setGeometry(width/2+205,height-180,100,20);
			
			calculateButton->setGeometry(width/2+215,height-155,90,25);
			
			resultLabel->setGeometry(width/2+15,height-115,290,20);
			result->setGeometry(width/2+15,height-90,290,20);
		
			copyFunctionLabel->setGeometry(width/2+15,height-65,65,20);
			copyFunction->setGeometry(width/2+155,height-65,80,20);
			copyButton->setGeometry(width/2+245,height-65,60,20);
		}
	}
}


void StatisticsWidget::setPref(Preferences p)
{
	pref=p;
	standardButtons->setPref(pref);
//	calcWidget->setPref(pref);
	functionTable->setPref(pref);
}

void StatisticsWidget::getPref(Preferences p)
{
	pref=p;
	emit prefChange(pref);
}


void StatisticsWidget::maximizeButtonSlot()
{
	fullscreen=!fullscreen;

	if(fullscreen)
	{
		maximizeButton->setText(STATISTICSC_STR1);
		standardButtons->hide();
		typeBoxSlot(-1);
	}
	else 
	{
		maximizeButton->setText("Maximize");
		typeBoxSlot(typeBox->currentItem());
		standardButtons->show();
	}
	resizeEvent(NULL);
}

void StatisticsWidget::calculateButtonSlot()
{
	long double *coordinatesList=NULL;
	int listNum,c=0,lineNum=0,c1=0;
	long double x,y;

	
	if(type==STATAPPROX || type==STATINTERPOL || type==STATLINEGRAPH)
	{
		xmin=xmax=ymin=ymax=0.0;
		listNum=listNumber->value()-1;
		while(c<lists->numRows())
		{
			if(lists->text(c,2*listNum).length()>0 && lists->text(c,2*listNum+1).length()>0)
			{
				lineNum++;
				coordinatesList=(long double*)realloc(coordinatesList,sizeof(long double)*lineNum*2);
				c1=lineNum-2;
				x=strtold(lists->text(c,2*listNum),NULL);
				y=strtold(lists->text(c,2*listNum+1),NULL);
				while(c1>=0 && coordinatesList[c1*2]>x)
				{
					coordinatesList[c1*2+2]=coordinatesList[c1*2];
					coordinatesList[c1*2+3]=coordinatesList[c1*2+1];
					c1--;
				}
				coordinatesList[c1*2+2]=x;
				coordinatesList[c1*2+3]=y;
				if(x>xmax)
					xmax=x;
				else if(x<xmin)
					xmin=x;
				if(y>ymax)
					ymax=y;
				else if(y<ymin)
					ymin=y;
			}
			c++;
		}
	}
	else {
		xmin=xmax=ymin=0.0;
		ymax=1.0;
		listNum=listNumberBox->currentItem();
		while(c<lists->numRows())
		{
			if(lists->text(c,listNum).length()>0)
			{
				lineNum++;
				coordinatesList=(long double*)realloc(coordinatesList,sizeof(long double)*lineNum);
				coordinatesList[lineNum-1]=strtold(lists->text(c,listNum),NULL);
				if(coordinatesList[lineNum-1]>xmax)
					xmax=coordinatesList[lineNum-1];
			}
			c++;
		}
	}
	
	switch(type)
	{
		case STATAPPROX:
		{
			result->setText("");
			int functionType=functionTypeBox->currentItem();
			if(functionType==0)
			{
				if(lineNum<1)
					MessageBox(STATISTICSC_STR6);
				long double sum=0.0;
				for(int c=0; c<lineNum; c++)
					sum+=coordinatesList[c*2+1];
				sum/=(long double)lineNum;
				result->setText(QString::number(sum,'g',pref.precision));
			}
			
			else if(functionType==1 || functionType==3 ||functionType==4)
			{
				if(lineNum<2)
					MessageBox(STATISTICSC_STR7);
				if(functionType==3 || functionType==4)
				{
					for(int c=0; c<lineNum; c++)
						coordinatesList[c*2+1]=logl(coordinatesList[c*2+1]);
				}
				long double xSum=0.0,ySum=0.0,xySum=0.0,x2Sum=0.0,a0,a1;
				QString resultText;
				for(int c=0; c<lineNum; c++)
				{
					xSum+=coordinatesList[c*2];
					ySum+=coordinatesList[c*2+1];
					xySum+=coordinatesList[c*2]*coordinatesList[c*2+1];
					x2Sum+=coordinatesList[c*2]*coordinatesList[c*2];
				}
				a0=(ySum*x2Sum-xSum*xySum)/(lineNum*x2Sum-xSum*xSum);
				a1=(lineNum*xySum-xSum*ySum)/(lineNum*x2Sum-xSum*xSum);
				if(functionType==1)
				{
					if(a1!=0.0)
						resultText=QString::number(a1,'g',pref.precision)+"*X";
					if(a0>0.0)
						resultText+="+";
					if(a0!=0.0)
					resultText+=QString::number(a0,'g',pref.precision);
				}
				else if(functionType==3 || functionType==4)
				{
					for(int c=0; c<lineNum; c++)
						coordinatesList[c*2+1]=expl(coordinatesList[c*2+1]);
					a0=expl(a0);
					if(functionType==4)
					{
						a1=expl(a1);
						resultText=QString::number(a0,'g',pref.precision)+"*"+QString::number(a1,'g',pref.precision)+"^X";
					}
					else 
					{
						resultText=QString::number(a0,'g',pref.precision)+"*eu^("+QString::number(a1,'g',pref.precision)+"*X)";
					}
				}
				result->setText(resultText);
			}
			else if(functionType==2)
			{
				if(lineNum<3)
					MessageBox(STATISTICSC_STR8);
				
				long double*sum1=new long double[3];
				long double*sum2=new long double[5];
				long double*mat=new long double[9];
				long double*coeff=new long double[3];
				QString resultText="";
				
				for(int c=0; c<3; c++)
				{
					sum1[c]=0.0;
					for(int c1=0; c1<lineNum; c1++)
					{
						if(c==0)
							sum1[c]+=coordinatesList[c1*2+1];
						else sum1[c]+=coordinatesList[c1*2+1]*powl(coordinatesList[c1*2],c);
					}
					perror("sum1: "+QString::number(c)+": "+QString::number((double)sum1[c]));

				}
				
				for(int c=0; c<5; c++)
				{
					sum2[c]=0.0;
					for(int c1=0; c1<lineNum; c1++)
						sum2[c]+=powl(coordinatesList[c1*2],c);
					perror("sum2: "+QString::number(c)+": "+QString::number((double)sum2[c]));
				}
				for(int c=0; c<3; c++) 
				{
					for(int c1=0; c1<3; c1++)
					{
						mat[c1*3+c]=sum2[c+c1];
					}
				}
				
				invertMatrix(3,mat);
				
				for(int c=0; c<3; c++)
				{
					coeff[c]=0.0;
					for(int c1=0; c1<3; c1++)
						coeff[c]+=mat[c1*3+c]*sum1[c1];
				}
				
				if(coeff[2]!=0.0)
					resultText+=QString::number(coeff[2],'g',pref.precision)+"*X^2";
				if(coeff[1]>0.0)
					resultText+="+";
				if(coeff[1]!=0.0)
					resultText+=QString::number(coeff[1],'g',pref.precision)+"*X";
				if(coeff[0]>0.0)
					resultText+="+";
				if(coeff[0]!=0.0)
					resultText+=QString::number(coeff[0],'g',pref.precision);

				delete[]sum1;
				delete[]sum2;
				delete[]mat;
				delete[]coeff;
				
				result->setText(resultText);
			}

			if(print)
			{
				setCoordinateSystem();
				if(pref.statAutoClear)
					emit removeLinesSignal();
				if(pref.showStatPoints || pref.showStatLines)
				emit drawPointsSignal(coordinatesList,lineNum,pref.showStatLines);
			}
			break;
		}
		case STATINTERPOL:
		{
			long double *coef=(long double*)malloc(lineNum*sizeof(long double));
			for(int c=0; c<lineNum; c++)
				coef[c]=coordinatesList[c*2+1];
			for(int c1=1; c1<lineNum; c1++)
			{
				for(int c2=lineNum-1; c2>=c1; c2--)
					coef[c2]=(coef[c2]-coef[c2-1])/(coordinatesList[c2*2]-coordinatesList[(c2-c1)*2]);
			}
			
			QString resultString="";
			for(int c1=0; c1<lineNum; c1++)
			{
				if(c1!=0 && coef[c1]>=0.0)
					resultString+="+";
				resultString+=QString::number(coef[c1],'g',pref.precision);
				for(int c2=0; c2<c1; c2++)
				{
					resultString+="*(X";
					if(coordinatesList[c2*2]<=0)
						resultString+="+";
					resultString+=QString::number(-1.0*coordinatesList[c2*2],'g',pref.precision);
					resultString+=")";
				}
			}
			result->setText(resultString);
			free(coef);
			if(print)
			{
				setCoordinateSystem();
				if(pref.statAutoClear)
					emit removeLinesSignal();
				if(pref.showStatPoints || pref.showStatLines)
					emit drawPointsSignal(coordinatesList,lineNum,pref.showStatLines);
			}
			break;
		}
		case STATLINEGRAPH:
			if(print)
			{
				setCoordinateSystem();
				if(pref.statAutoClear)
					emit removeLinesSignal();
				emit drawPointsSignal(coordinatesList,lineNum,true);
			}
			break;
		case STATBARGRAPH:
		case STATNORMAL:
		{
			int stepCount=stepsBox->value();
			long double *graphData=new long double[2*stepCount],start,end,step;

			
			start=end=coordinatesList[0];
			for(int c=1; c<lineNum; c++)
			{
				if(coordinatesList[c]>end)
					end=coordinatesList[c];
				if(coordinatesList[c]<start)
					start=coordinatesList[c];
			}
			step=(end-start)/(stepCount-1);
			
			for(int c=0; c<stepCount; c++)
			{
				graphData[c*2+1]=0.0;
				graphData[c*2]=start+step*c;
			}
			
			
			for(int c1=0; c1<lineNum; c1++)
			{
				for(int c2=1; c2<=stepCount; c2++)
				{
					
					if(coordinatesList[c1]<start+c2*step-step/2)
					{
						graphData[2*c2-1]+=1.0;
						if(graphData[2*c2-1]>ymax)
							ymax=graphData[2*c2-1];
						break;
					}
				}
			}
			if(type==STATNORMAL)
			{
				long double sum=0.0;
				for(int c=0; c<stepCount; c++)
					sum+=graphData[2*c+1];
				for(int c=0; c<stepCount; c++)
					graphData[2*c+1]=graphData[2*c+1]/sum;
				ymax=ymax/sum;
			}
			
			if(print)
			{
				setCoordinateSystem();
				if(pref.statAutoClear)
					emit removeLinesSignal();
				if(type==STATBARGRAPH || pref.showStatLines)
					emit drawPointsSignal(graphData,stepCount,true);
				else if(type==STATNORMAL && pref.showStatPoints)
					emit drawPointsSignal(graphData,stepCount,false);
			}
			
			delete[] graphData;
			
			if(type==STATNORMAL)
			{
	
				long double my=0.0,sigma=0.0,coeff1,coeff2;
				for(int c=0; c<lineNum; c++)
					my+=coordinatesList[c];
				my/=lineNum;
				for(int c=0; c<lineNum; c++)
					sigma+=(coordinatesList[c]-my)*(coordinatesList[c]-my);
				sigma/=(lineNum-1);
				sigma=sqrtl(sigma);
				
				coeff1=1.0/(sqrtl(2.0*PI)*sigma);
				coeff2=1.0/(2.0*sigma*sigma);
	
				QString resultString=QString::number(coeff1,'g',pref.precision);
				resultString+="*eu^(-"+QString::number(coeff2,'g',pref.precision);
				resultString+="*(X-"+QString::number(my,'g',pref.precision)+")^2)";
				
				result->setText(resultString);
			}
			break;
		}
	}
	free(coordinatesList);
}

	
void StatisticsWidget::typeBoxSlot(int index)
{
	functionTypeBox->hide();
	functionTypeLabel->hide();
	listNumberBox->hide();
	copyFunction->hide();
	listNumber->hide();
	calculateButton->hide();
	resultLabel->hide();
	copyFunctionLabel->hide();
	result->hide();
	listNumberLabel->hide();
	copyButton->hide();
	stepsBox->hide();
	stepsLabel->hide();
	
	switch(index)
	{
		case 0:
			type=STATAPPROX;
			functionTypeBox->show();
			functionTypeLabel->show();
			copyFunction->show();
			listNumber->show();
			calculateButton->show();
			resultLabel->show();
			copyFunctionLabel->show();
			listNumberLabel->show();
			result->show();
			copyButton->show();
			break;
		case 1:
			type=STATINTERPOL;
			copyFunction->show();
			listNumber->show();
			calculateButton->show();
			resultLabel->show();
			copyFunctionLabel->show();
			listNumberLabel->show();
			result->show();
			copyButton->show();
			break;
		case 2:
			type=STATLINEGRAPH;
			listNumber->show();
			listNumberLabel->show();
			break;
		case 3:
			type=STATNORMAL;
			listNumberBox->show();
			listNumberLabel->show();
			result->show();
			resultLabel->show();
			copyButton->show();
			copyFunctionLabel->show();
			copyFunction->show();
			calculateButton->show();
			break;
		case 4:
			type=STATBARGRAPH;
			listNumberBox->show();
			listNumberLabel->show();
			stepsBox->show();
			stepsLabel->show();
			break;
	}
	resizeEvent(NULL);
}

void StatisticsWidget::copyButtonSlot()
{
	int index=copyFunction->currentItem();
	if(pref.functions==NULL || result->text().length()<=0)
		return;
	if(pref.functions[index].length()>0)
	{
		int ret=YesNoCancelBox(STATISTICSC_STR2+QString::number(index+1)+STATISTICSC_STR3);
		if(ret!=0)
			return;
	}
	
	pref.functions[index]=result->text();
	pref.functionTypes[index]=GRAPHSTD;
	emit prefChange(pref);
}


void StatisticsWidget::printButtonSlot()
{
	print=true;
	calculateButtonSlot();
	print=false;
	bool *tmpActiveFunctions=new bool[20];
	QString tmpF1=pref.functions[0];
	int tmpFunctionType=pref.functionTypes[0];
	
	memcpy(tmpActiveFunctions,pref.activeFunctions,20*sizeof(bool));
	pref.functions[0]=result->text();
	if(type==STATINTERPOL || type==STATAPPROX || type==STATNORMAL)
		pref.activeFunctions[0]=true;
	else pref.activeFunctions[0]=false;
	for(int c=1; c<20;c++)
		pref.activeFunctions[c]=false;
	pref.graphType=GRAPHSTD;
	pref.functionTypes[0]=GRAPHSTD;
	
	emit prefChange(pref);
	emit printSignal();
	emit changeTabSignal(2);

	pref.functions[0]=tmpF1;
	memcpy(pref.activeFunctions,tmpActiveFunctions,20*sizeof(bool));
	pref.functionTypes[0]=tmpFunctionType;
	emit prefChange(pref);
	delete[] tmpActiveFunctions;
}



void StatisticsWidget::itemChangedSlot(int row,int col)
{
	QString item=lists->text(row,col);
	if(item.length()<=0)
	{
		if((row==lists->numRows()-1 || row==lists->numRows()-2))
		{
			bool clear=true;
			while(clear && lists->numRows()>1)
			{
				for(int c=0; c<lists->numCols(); c++)
					if(lists->text(lists->numRows()-1,c).length()>0 || lists->text(lists->numRows()-2,c).length()>0)
				{
					clear=false;
					break;
				}
				if(clear)
					lists->setNumRows(lists->numRows()-1);
			}
		}
		return;
	}
	
	long double value=runCalc(item,&pref,vars);
	lists->setText(row,col,formatOutput(value,&pref));
	
	if(row>=lists->numRows()-1)
		lists->setNumRows(row+2);
}


void StatisticsWidget::writeListsFile()
{
	FILE*configFile;

	chdir(getenv("HOME"));
	configFile = fopen(LISTSFILE,"w");
	if(configFile == NULL)
	{
		ErrorBox(STATISTICSC_STR4+QString(LISTSFILE));
		return;
	}
	QString vars="";
	char*buffer=(char*)malloc(100);
    vars+=QString::number(lists->numRows()-1);
	vars+="\n";
	
	for(int c=0; c<LISTCOUNT*2;c++)
	{
		for(int c1=0; c1<lists->numRows()-1; c1++)
		{
			if(lists->text(c1,c).length()>0)
				vars+=lists->text(c1,c);
			else vars+="X";
			vars+=" ";
		}
	}
	free(buffer);
	
	fwrite(vars,vars.length(),1,configFile);
	fclose(configFile);
}

void StatisticsWidget::readListsFile()
{
	chdir(getenv("HOME"));

	int fileLen;
	struct stat fileStat;

	if(lstat(LISTSFILE,&fileStat) != 0)
		return;
	else fileLen=fileStat.st_size;

	
	FILE*varFile = fopen(LISTSFILE,"r");
	if(varFile == NULL)
	{
		MessageBox(STATISTICSC_STR5+QString(LISTSFILE));
		return;
	}
	char* cConfFile = new char[fileLen+1];
	fread((void*)cConfFile,fileLen,1,varFile);
	cConfFile[fileLen]=(char)0;
	QString configFile(cConfFile);
	delete[]cConfFile;
	fclose(varFile);
	
	int pos1=0,pos2=0;
	QString num;
	int rowNum;
	pos2=configFile.find("\n");
	num=configFile.mid(pos1,pos2-pos1);
	rowNum=num.toInt();
	if(rowNum<1)
		return;
	pos1=pos2+1;
	lists->setNumRows(rowNum+1);
	
	for(int c=0; c<2*LISTCOUNT;c++)
	{
		for(int c1=0; c1<rowNum; c1++)
		{
			pos2=configFile.find(" ",pos1);
			num=configFile.mid(pos1,pos2-pos1);
			pos1=pos2+1;
			if(pos2==-1)
				return;
			if(num!="X")
				lists->setText(c1,c,num);
		}
	}
}

void StatisticsWidget::setCoordinateSystem()
{
	double xSize=xmax-xmin,ySize=ymax-ymin;
	xSize*=0.1;
	ySize*=0.1;
	pref.xmin=xmin-xSize;
	pref.xmax=xmax+xSize*2.0;
	pref.ymin=ymin-ySize;
	pref.ymax=ymax+ySize;
	if(pref.xmax-pref.xmin<0.1 || pref.ymax-pref.ymin<0.1)
	{
		pref.xmax=pref.ymax=10.0;
		pref.xmin=pref.ymin=-10.0;
	}
	
	emit prefChange(pref);
}

void StatisticsWidget::redrawGraphSlot()
{
	print=true;
	calculateButtonSlot();
	print=false;
}

void StatisticsWidget::buttonInputSlot(QString)
{
}


