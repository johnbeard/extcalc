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
		
		resultLabel->setGeometry(width/2+15,height-180,290,20);
		result->setGeometry(width/2+15,height-155,290,20);
		
		copyFunctionLabel->setGeometry(width/2+15,height-130,130,20);
		copyFunction->setGeometry(width/2+155,height-130,80,20);
		copyButton->setGeometry(width/2+245,height-130,60,20);

		if(type==STATAPPROX)
		{
			functionTypeLabel->setGeometry(20,height-220,170,25);
			functionTypeBox->setGeometry(200,height-220,105,25);

			listNumberLabel->setGeometry(20,height-190,190,20);
			listNumber->setGeometry(210,height-190,95,20);
		}
		else
		{
			listNumberLabel->setGeometry(20,height-220,190,20);
			listNumber->setGeometry(210,height-220,95,20);
		}
		calculateButton->setGeometry(width/2-102,height-45,90,25);
	}
}


void StatisticsWidget::setPref(Preferences p)
{
	pref=p;
//	standardButtons->setPref(pref);
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
		maximizeButton->setText("Minimize");
	else maximizeButton->setText("Maximize");
	resizeEvent(NULL);
}

void StatisticsWidget::calculateButtonSlot()
{
	long double *coordinatesList=NULL;
	int listNum=listNumber->value()-1,c=0,lineNum=0,c1=0;
	long double x,y;
	
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
			emit drawPointsSignal(coordinatesList,lineNum,true);
			break;
		}
		case STATINTERPOL:
			break;
	}
	free(coordinatesList);
}


void StatisticsWidget::typeBoxSlot(int index)
{
	switch(index)
	{
		case 0:
			type=STATAPPROX;
			functionTypeBox->show();
			functionTypeLabel->show();
			break;
		case 1:
			type=STATINTERPOL;
			
			functionTypeBox->hide();
			functionTypeLabel->hide();
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
	emit printSignal();
	emit changeTabSignal(2); 
	
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


