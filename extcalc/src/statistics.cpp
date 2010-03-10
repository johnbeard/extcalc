/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         statistics.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "statistics.h"
//Added by qt3to4:
#include <QResizeEvent>


StatisticsWidget::StatisticsWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td) :TabWidget(parent,p,va,td,false)
{

        functionChanged=false;
        type=STATAPPROX;
        print=false;
        changedRow=-1;

        horzSplit=new QSplitter(Qt::Horizontal,this);
        vertSplit=new QSplitter(Qt::Vertical,horzSplit);
        functionTable=new FunctionTable(vertSplit,pref);
        catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX,this);

        toolFrame=new QFrame(this);
		toolFrame->setFixedHeight(170);
        toolFrameLayout=new QGridLayout(toolFrame);
		toolFrameLayout->setColumnMinimumWidth(0,90);
		toolFrameLayout->setColumnMinimumWidth(1,90);
		toolFrameLayout->setColumnMinimumWidth(2,90);
		toolFrameLayout->setRowMinimumHeight(0,20);
		toolFrameLayout->setRowMinimumHeight(1,20);
		toolFrameLayout->setRowMinimumHeight(2,20);
		toolFrameLayout->setRowMinimumHeight(3,20);
		toolFrameLayout->setRowMinimumHeight(4,20);
		toolFrameLayout->setColumnStretch(0,1);
		toolFrameLayout->setVerticalSpacing(2);
		extButtons->hide();


        minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
        maximizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_remove.png"));
        printIcon=new QPixmap(INSTALLDIR+QString("/data/print.png"));
        catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));

        setMainWidget(horzSplit);
        addSubWidget(calcButtons);
        addSubWidget(toolFrame);
        setDockArea(1);

        toolBar=new Q3ToolBar();
        dockArea->moveDockWindow(toolBar);

        drawButton=new QPushButton(*printIcon,STATISTICSH_STR14,toolBar);
        drawButton->setFixedHeight(25);
        maximizeButton=new QPushButton(*maximizeIcon,"",toolBar);
        lists=new Q3Table(horzSplit);
        lists->setNumRows(1);
        lists->setNumCols(2*LISTCOUNT);
        typeBox=new QComboBox(toolBar);
        functionTypeLabel=new QLabel(STATISTICSH_STR1,toolFrame);
        functionTypeBox=new QComboBox(toolFrame);
        listNumber=new QSpinBox(1,LISTCOUNT,1,toolFrame);
        listNumberLabel=new QLabel(STATISTICSH_STR2,toolFrame);
        resultLabel=new QLabel(STATISTICSH_STR3,toolFrame);
        result=new QLineEdit(toolFrame);
        inputLine=new QLineEdit(vertSplit);
        inputLine->setFixedHeight(25);
        for(int c=0; c<5; c++)
        {
                lists->horizontalHeader()->setLabel(2*c,"X"+QString::number(c+1));
                lists->horizontalHeader()->setLabel(2*c+1,"Y"+QString::number(c+1));
        }

        copyFunctionLabel=new QLabel(STATISTICSH_STR4,toolFrame);
        copyFunction=new QComboBox(toolFrame);
        copyButton=new QPushButton(STATISTICSH_STR5,toolFrame);
        for(int c=0; c<20; c++)
                copyFunction->insertItem("f"+QString::number(c+1)+"(x)");

        listNumberBox=new QComboBox(toolFrame);
        for(int c=0; c<LISTCOUNT; c++)
        {
                listNumberBox->insertItem("X"+QString::number(c+1));
                listNumberBox->insertItem("Y"+QString::number(c+1));
        }

        functionTypeBox->insertItem("const");
        functionTypeBox->insertItem("a*x+b");
        functionTypeBox->insertItem("a*x^2+b*x+c");
        functionTypeBox->insertItem("a*e^(b*x)");
        functionTypeBox->insertItem("a*b^x");

        typeBox->insertItem(STATISTICSH_STR6);
        typeBox->insertItem(STATISTICSH_STR7);
        typeBox->insertItem(STATISTICSH_STR8);
        typeBox->insertItem(STATISTICSH_STR9);
        typeBox->insertItem(STATISTICSH_STR10);

        stepsBox=new QSpinBox(1,100,1,toolFrame);
        stepsBox->setValue(10);
        stepsLabel=new QLabel(STATISTICSH_STR11,toolFrame);


        calculateButton=new QPushButton(STATISTICSH_STR12,toolFrame);
        catalogButton=new QPushButton(*catalogIcon,"",toolBar);
        catalogButton->setFixedWidth(30);
        maximizeButton->setFixedWidth(30);
        typeBox->setFixedWidth(120);

        readListsFile();

        typeBoxSlot(0);
        QObject::connect(functionTable,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
        QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeButtonSlot()));
        QObject::connect(calculateButton,SIGNAL(clicked()),this,SLOT(calculateButtonSlot()));
        QObject::connect(copyButton,SIGNAL(clicked()),this,SLOT(copyButtonSlot()));
        QObject::connect(drawButton,SIGNAL(clicked()),this,SLOT(printButtonSlot()));
        QObject::connect(typeBox,SIGNAL(activated(int)),this,SLOT(typeBoxSlot(int)));
        QObject::connect(lists,SIGNAL(valueChanged(int,int)),this,SLOT(itemChangedSlot(int,int)));
        QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
        QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
        QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(buttonInputSlot(QString)));
        QObject::connect(catalogButton,SIGNAL(clicked()),this,SLOT(catalogSlot()));
        QObject::connect(functionTable,SIGNAL(currentChanged(int,int)),this,SLOT(selectionChangedSlot(int,int)));
        QObject::connect(functionTable,SIGNAL(textEditStarted(QString)),this,SLOT(tableEditSlot(QString)));
        QObject::connect(inputLine,SIGNAL(returnPressed()),this,SLOT(inputTextFinished()));
        QObject::connect(inputLine,SIGNAL(textChanged(const QString&)),this,SLOT(inputTextChanged(const QString&)));
}



/*
void StatisticsWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();
	if(fullscreen)
	{
		horzSplit->setGeometry(20,menuBottom+40,width-40,height-90);
	//	drawButton->setGeometry(20,height-45,90,35);
	//	typeBox->setGeometry(120,height-45,90,35);
	//	maximizeButton->setGeometry(220,height-45,90,35);
		dockArea->setGeometry(0,menuBottom,width,35);
	}
	else
	{
		horzSplit->setGeometry(20,50,width-40,height-290);

	//	drawButton->setGeometry(width/2+15,height-220,90,35);
	//	typeBox->setGeometry(width/2+115,height-220,90,35);
	//	maximizeButton->setGeometry(width/2+215,height-220,90,35);
		dockArea->setGeometry(width/2+15,height-220,width/2-35,35);
		
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
*/

void StatisticsWidget::setPref(Preferences p)
{
	pref=p;
        calcButtons->setPref(pref);
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
	if(!isMaximized())
	{
		maximizeButton->setIconSet(*minimizeIcon);
		calcButtons->hide();
		typeBox->hide();
		typeBoxSlot(-1);
		maximizeSlot(true);
	}
	else 
	{
		maximizeButton->setIconSet(*maximizeIcon);
		typeBoxSlot(typeBox->currentItem());
		calcButtons->show();
		typeBox->show();
		maximizeSlot(false);
	}
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
			if(lists->text(c,2*listNum).length()>0 && lists->text(c,2*listNum+1).length()>0 &&
					!((functionTypeBox->currentItem()==3 || functionTypeBox->currentItem()==4)
					&& type==STATAPPROX && strtold(lists->text(c,2*listNum+1),NULL)<=0.0))
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

				}
				
				for(int c=0; c<5; c++)
				{
					sum2[c]=0.0;
					for(int c1=0; c1<lineNum; c1++)
						sum2[c]+=powl(coordinatesList[c1*2],c);
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
	toolFrameLayout->removeWidget(functionTypeBox);
	toolFrameLayout->removeWidget(functionTypeLabel);
	toolFrameLayout->removeWidget(listNumberBox);
	toolFrameLayout->removeWidget(copyFunction);
	toolFrameLayout->removeWidget(listNumber);
	toolFrameLayout->removeWidget(resultLabel);
	toolFrameLayout->removeWidget(copyFunctionLabel);
	toolFrameLayout->removeWidget(result);
	toolFrameLayout->removeWidget(listNumberLabel);
	toolFrameLayout->removeWidget(copyButton);
	toolFrameLayout->removeWidget(stepsBox);
	toolFrameLayout->removeWidget(copyButton);
	toolFrameLayout->removeWidget(stepsLabel);
	toolFrameLayout->removeWidget(calculateButton);


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

			toolFrameLayout->addWidget(functionTypeLabel,0,0,1,2);
			toolFrameLayout->addWidget(functionTypeBox,0,2,1,1);
			toolFrameLayout->addWidget(listNumberLabel,1,0,1,2);
			toolFrameLayout->addWidget(listNumber,1,2,1,1);
			toolFrameLayout->addWidget(calculateButton,2,2,1,1);
			toolFrameLayout->addWidget(resultLabel,3,0,1,3);
			toolFrameLayout->addWidget(result,4,0,1,3);
			toolFrameLayout->addWidget(copyFunctionLabel,5,0,1,1);
			toolFrameLayout->addWidget(copyFunction,5,1,1,1);
			toolFrameLayout->addWidget(copyButton,5,2,1,1);

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

			toolFrameLayout->addWidget(listNumberLabel,0,0,1,2);
			toolFrameLayout->addWidget(listNumber,0,2,1,1);
			toolFrameLayout->addWidget(calculateButton,1,2,1,1);
			toolFrameLayout->addWidget(resultLabel,2,0,1,3);
			toolFrameLayout->addWidget(result,3,0,1,3);
			toolFrameLayout->addWidget(copyFunctionLabel,4,0,1,1);
			toolFrameLayout->addWidget(copyFunction,4,1,1,1);
			toolFrameLayout->addWidget(copyButton,4,2,1,1);
			break;
		case 2:
			type=STATLINEGRAPH;
			listNumber->show();
			listNumberLabel->show();

			toolFrameLayout->addWidget(listNumberLabel,0,0,1,2);
			toolFrameLayout->addWidget(listNumber,0,2,1,1);
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

			toolFrameLayout->addWidget(listNumberLabel,0,0,1,2);
			toolFrameLayout->addWidget(listNumberBox,0,2,1,1);
			toolFrameLayout->addWidget(calculateButton,1,2,1,1);
			toolFrameLayout->addWidget(resultLabel,2,0,1,3);
			toolFrameLayout->addWidget(result,3,0,1,3);
			toolFrameLayout->addWidget(copyFunctionLabel,4,0,1,1);
			toolFrameLayout->addWidget(copyFunction,4,1,1,1);
			toolFrameLayout->addWidget(copyButton,4,2,1,1);

			break;
		case 4:
			type=STATBARGRAPH;
			listNumberBox->show();
			listNumberLabel->show();
			stepsBox->show();
			stepsLabel->show();


			toolFrameLayout->addWidget(listNumberLabel,0,0,1,2);
			toolFrameLayout->addWidget(listNumberBox,0,2,1,1);
			toolFrameLayout->addWidget(stepsLabel,1,0,1,2);
			toolFrameLayout->addWidget(stepsBox,1,2,1,1);
			break;
		default:
			break;
	}
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

void StatisticsWidget::buttonInputSlot(QString text)
{
	if(text == "calculate")
	{
//		drawSlot();
	}
	else if(text == "backkey")
	{
		if(inputLine->cursorPosition() > 0)
			inputLine->backspace();
		else inputLine->del();
		functionTable->setText(functionTable->currentRow(),0,inputLine->text());
		if((inputLine->text().length())<=0)
		{
			Q3CheckTableItem *checkItem=(Q3CheckTableItem*)functionTable->item(functionTable->currentRow(),2);
			checkItem->setChecked(false);
		}
	}
	else if(text == "clearall")
	{
		functionTable->setFunctionText("");
	}
	else {
		QString fullText=inputLine->text();
		int cursorPos=inputLine->cursorPosition();
		fullText.insert(cursorPos,text);
		inputLine->setText(fullText);
		inputLine->setCursorPosition(cursorPos+text.length());
		functionTable->setText(functionTable->currentRow(),0,inputLine->text());
		Q3CheckTableItem *checkItem=(Q3CheckTableItem*)functionTable->item(functionTable->currentRow(),2);
		checkItem->setChecked(true);
	}
}

void StatisticsWidget::selectionChangedSlot(int row,int)
{
	if(functionChanged)
	{
		inputTextFinished();
	}
	if(functionTable->text(row,0).length() > 0)
		inputLine->setText(functionTable->text(row,0));
	else inputLine->clear();
	changedRow=row;
	functionChanged=false;
}

void StatisticsWidget::tableEditSlot(QString string)
{
	if(functionChanged)
	{
		inputTextFinished();
	}
	changedRow=functionTable->currentRow();
	if(string.length() > 0)
		inputLine->setText(string);
	else inputLine->clear();
	inputLine->setActiveWindow();
	inputLine->setFocus();
	functionChanged=false;
}

void StatisticsWidget::inputTextChanged(const QString&)
{
	functionChanged=true;
}

void StatisticsWidget::inputTextFinished()
{
	if(functionChanged)
	{
		functionTable->setFunctionText(inputLine->text(),changedRow);
		functionChanged=false;
	}
	inputLine->clearFocus();
}

void StatisticsWidget::dockWindowSlot()
{
	dockArea->moveDockWindow(toolBar);
}

void StatisticsWidget::catalogSlot()
{
	catalog->exec(toolBar->mapToGlobal(QPoint(catalogButton->x(),catalogButton->y()+catalogButton->height())));
}


