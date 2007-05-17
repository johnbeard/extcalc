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

		}
		if(type==STATBARGRAPH || type==STATNORMAL)
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
		maximizeButton->setText("Minimize");
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
			}
			c++;
		}
	}
	else {
		listNum=listNumberBox->currentItem();
		while(c<lists->numRows())
		{
			if(lists->text(c,listNum).length()>0)
			{
				lineNum++;
				coordinatesList=(long double*)realloc(coordinatesList,sizeof(long double)*lineNum);
				coordinatesList[lineNum-1]=strtold(lists->text(c,listNum),NULL);
			}
			c++;
		}
	}
	
	switch(type)
	{
		case STATAPPROX:
		{
			int functionType=functionTypeBox->currentItem();
			if(functionType==0)
			{
				long double sum=0.0;
				for(int c=0; c<lineNum; c++)
					sum+=coordinatesList[c*2+1];
				sum/=(long double)lineNum;
				result->setText(QString::number(sum,'g',pref.precision));
			}
			else if(functionType==1)
			{
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
				if(a1!=0.0)
					resultText=QString::number(a1,'g',pref.precision)+"*X";
				if(a0>=0.0)
					resultText+="+";
				if(a0!=0.0)
				resultText+=QString::number(a0,'g',pref.precision);
				result->setText(resultText);
			}
			if(print)
			{
				emit removeLinesSignal();
				emit drawPointsSignal(coordinatesList,lineNum,false);
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
				emit removeLinesSignal();
				emit drawPointsSignal(coordinatesList,lineNum,false);
			}
			break;
		}
		case STATLINEGRAPH:
			if(print)
			{
				emit removeLinesSignal();
				emit drawPointsSignal(coordinatesList,lineNum,true);
			}
			break;
		case STATNORMAL:
		{
			long double my=0.0,sigma=0.0;
			for(int c=0; c<lineNum; c++)
				my+=coordinatesList[c];
			my/=lineNum;
			for(int c=0; c<lineNum; c++)
				sigma+=(coordinatesList[c]-my)*(coordinatesList[c]-my);
			perror(QString::number(lineNum)+" "+QString::number((double)sigma));

			sigma/=(lineNum-1);
			perror(QString::number(lineNum)+" "+QString::number((double)sigma));

			sigma=sqrtl(sigma);
			perror(QString::number(lineNum)+" "+QString::number((double)sigma));
			QString resultString="1/(sqrt(2*pi)*"+QString::number(sigma,'g',pref.precision)+")*eu^-((X-"+
					QString::number(my,'g',pref.precision)+")^2/(2*"+QString::number(sigma,'g',pref.precision)+"^2))";
			
			result->setText(resultString);
			if(print)
			{
				emit removeLinesSignal();
				emit drawPointsSignal(coordinatesList,lineNum,true);
			}
			break;
		}
		case STATBARGRAPH:
			
			
			if(print)
			{
				emit removeLinesSignal();
				emit drawPointsSignal(coordinatesList,lineNum,true);
			}
			break;
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
		int ret=YesNoCancelBox("Really overwrite function f"+QString::number(index+1)+" ?");
		if(ret!=0)
			return;
	}
	
	pref.functions[index]=result->text();
	emit prefChange(pref);
}


void StatisticsWidget::printButtonSlot()
{
	print=true;
	calculateButtonSlot();
	print=false;
	bool *tmpActiveFunctions=new bool[20];
	QString tmpF1=pref.functions[0];
	memcpy(tmpActiveFunctions,pref.activeFunctions,20*sizeof(bool));
	pref.functions[0]=result->text();
	if(type==STATINTERPOL || type==STATAPPROX)
		pref.activeFunctions[0]=true;
	else pref.activeFunctions[0]=false;
	for(int c=1; c<20;c++)
		pref.activeFunctions[c]=false;
	
	emit prefChange(pref);
	emit printSignal();
	emit changeTabSignal(2);

	pref.functions[0]=tmpF1;
	memcpy(pref.activeFunctions,tmpActiveFunctions,20*sizeof(bool));
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

void StatisticsWidget::buttonInputSlot(QString)
{
}


