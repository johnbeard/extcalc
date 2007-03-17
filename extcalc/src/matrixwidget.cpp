#include "matrixwidget.h"


void MatrixWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();

	
	varTable->setGeometry(20,50,width/4-30,height-290);
	outputTable->setGeometry(width/4+10,50,3*width/4-30,height-290);

	standardButtons->setGeometry(20,height-220,280,200);
	calcWidget->setGeometry(320,height-180,width-340,160);
	
	operationBox->setGeometry(320,height-220,95,35);
	sprodButton->setGeometry(425,height-220,30,35);
	invertButton->setGeometry(465,height-220,30,35);
	detButton->setGeometry(505,height-220,30,35);
	braceOpenButton->setGeometry(545,height-220,30,35);
	braceCloseButton->setGeometry(585,height-220,30,35);
}

void MatrixWidget::setVarTable()
{
	for(int c=0; c<27; c++)
	{
		if(threadData->dimension[c][0]==1 && threadData->dimension[c][1]==1)
			varTable->setText(c,0,"s");
		else if(threadData->dimension[c][1]==1)
			varTable->setText(c,0,"v");
		else varTable->setText(c,0,"m");
		
		varTable->setText(c,1,QString::number(threadData->dimension[c][0]));
		varTable->setText(c,2,QString::number(threadData->dimension[c][1]));
	}
	varTable->horizontalHeader()->setLabel(0,"");
	varTable->horizontalHeader()->setLabel(1,"");
	varTable->horizontalHeader()->setLabel(2,"");
	varTable->adjustColumn(0);
	varTable->adjustColumn(1);
	varTable->adjustColumn(2);
	varTable->horizontalHeader()->setLabel(0,"Type");
	varTable->horizontalHeader()->setLabel(1,"Rows");
	varTable->horizontalHeader()->setLabel(2,"Columns");
}


void MatrixWidget::setOutputTable(int num)
{
	outputTable->setNumRows(threadData->dimension[num][0]);
	outputTable->setNumCols(threadData->dimension[num][1]);
	int effIndex;
	for(int c1=0; c1<threadData->dimension[num][0]; c1++)
	{
		for(int c2=0; c2<threadData->dimension[num][1]; c2++)
		{
			effIndex=c2*threadData->dimension[num][0]+c1;
			if(effIndex<threadData->numlen[num])
				outputTable->setText(c1,c2,formatOutput(threadData->vars[num][effIndex],&pref));
			else outputTable->setText(c1,c2,"invalid");
			if(c1==threadData->dimension[num][0]-1)
				outputTable->adjustColumn(c2);
		}
	}
}

void MatrixWidget::resizeVar(int var,int rows,int cols)
{
	int newlen=rows*cols;
	int oldDimension1=threadData->dimension[var][0],oldDimension2=threadData->dimension[var][1];

	if(oldDimension1==rows)
	{
		threadData->vars[var]=(Number*)realloc((void*)threadData->vars[var],sizeof(Number)*newlen);
		for(int c=threadData->numlen[var]; c<newlen; c++)
		{
			threadData->vars[var][c].type=NNONE;
			threadData->vars[var][c].cval=NULL;
		}
	}
	
	
	
	threadData->numlen[var]=newlen;
	threadData->dimension[var][0]=rows;
	threadData->dimension[var][1]=cols;


	int oldEffIndex,newEffIndex;


	if(threadData->dimension[var][0]>oldDimension1)
	{
		threadData->vars[var]=(Number*)realloc((void*)threadData->vars[var],sizeof(Number)*newlen);
		for(int c=threadData->numlen[var]; c<newlen; c++)
		{
			threadData->vars[var][c].type=NNONE;
			threadData->vars[var][c].cval=NULL;
		}
		for(int c=oldDimension2-1; c>=1; c--)
		{
			for(int c1=oldDimension1-1; c1>=0; c1--)
			{
							
				oldEffIndex=c1+c*oldDimension1;
				newEffIndex=c1+c*threadData->dimension[var][0];
				memcpy(&threadData->vars[var][newEffIndex],&threadData->vars[var][oldEffIndex],sizeof(Number));
			}
		}
	}
	else if(threadData->dimension[var][0]<oldDimension1)
	{
		for(int c=1; c<oldDimension2; c++)
		{
			for(int c1=0; c1<oldDimension1; c1++)
			{
							
				oldEffIndex=c1+c*oldDimension1;
				newEffIndex=c1+c*threadData->dimension[var][0];
				memcpy(&threadData->vars[var][newEffIndex],&threadData->vars[var][oldEffIndex],sizeof(Number));
			}
		}
		threadData->vars[var]=(Number*)realloc((void*)threadData->vars[var],sizeof(Number)*newlen);
	}
	
}



void MatrixWidget::setPref(Preferences p)
{
	pref=p;
	standardButtons->setPref(pref);
	calcWidget->setPref(pref);
}

void MatrixWidget::getPref(Preferences p)
{
	pref=p;
	emit prefChange(pref);
}


void MatrixWidget::sprodButtonSlot()
{
	calcWidget->setBold(false);
	calcWidget->textInput(getUnicode(DEGREESTRING));
}

void MatrixWidget::invertButtonSlot()
{
	calcWidget->setBold(false);
	calcWidget->textInput("^-1");
}

void MatrixWidget::detButtonSlot()
{
	calcWidget->setBold(false);
	calcWidget->textInput("det");
}

void MatrixWidget::braceOpenButtonSlot()
{
	calcWidget->setBold(false);
	calcWidget->textInput("[");
}

void MatrixWidget::braceCloseButtonSlot()
{
	calcWidget->setBold(false);
	calcWidget->textInput("]");
}

void MatrixWidget::operationBoxSlot(const QString&)
{
	
}

void MatrixWidget::buttonInputSlot(QString text)
{
	if(text == "calculate")
	{
		calcWidget->calculateKey();
		setOutputTable(currentVar);
		setVarTable();
	}
	else if(text == "backkey")
		calcWidget->backKey();
	else if(text == "clearall")
		calcWidget->clearAll();
	else {
		calcWidget->setBold(false);
		calcWidget->textInput(text);
	}
}


void MatrixWidget::enterSlot()
{
	setVarTable();
	setOutputTable(currentVar);
}

void MatrixWidget::varSelectionSlot(int row ,int)
{
	if(row!=currentVar)
	{
		currentVar=row;
		setOutputTable(currentVar);
		varTable->clearSelection();
		varTable->selectRow(currentVar);
	}
}

void MatrixWidget::varChangedSlot(int row,int col)
{
	int newsize=0;
	if(col==1)
	{
		newsize=varTable->text(row,col).toInt();
		if(newsize>0)
			resizeVar(row,newsize,threadData->dimension[row][1]);
	}
	else
	{
		newsize=varTable->text(row,col).toInt();
		if(newsize>0)
			resizeVar(row,threadData->dimension[row][0],newsize);
	}

	setVarTable();
	setOutputTable(currentVar);
}

void MatrixWidget::outputChangedSlot(int row,int col)
{
	int effIndex=threadData->dimension[currentVar][0]*col+row;
	if(threadData->numlen[currentVar]<effIndex)
		resizeVar(currentVar,threadData->dimension[currentVar][0],threadData->dimension[currentVar][1]);
	
	threadData->vars[currentVar][effIndex].type=NFLOAT;
	threadData->vars[currentVar][effIndex].fval=Complex(runCalc(outputTable->text(row,col),&pref,vars),0.0);
	
	setOutputTable(currentVar);
}




