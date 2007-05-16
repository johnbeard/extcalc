#include "matrixwidget.h"


void MatrixWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();

	
	varTable->setGeometry(20,50,width/4-30,height-290);
	outputTable->setGeometry(width/4+10,50,3*width/4-30,height-290);

	operationBox->setGeometry(320,height-220,145,35);
	sprodButton->setGeometry(490,height-220,35,35);
	invertButton->setGeometry(535,height-220,35,35);
	detButton->setGeometry(580,height-220,35,35);

	switch(state)
	{
		case MATCALC:
			standardButtons->setGeometry(20,height-220,280,200);
			calcWidget->setGeometry(320,height-180,width-340,160);
			break;
		case MATLSE:
			matrixLabel->setGeometry(20,height-220,140,20);
			vectorLabel->setGeometry(160,height-220,140,20);
			matrixBox->setGeometry(20,height-190,120,25);
			vectorBox->setGeometry(160,height-190,120,25);
			size1Label->setGeometry(20,height-155,100,20);
			size1Box->setGeometry(140,height-155,85,20);
			sizeButton->setGeometry(230,height-155,50,20);
			size2Label->setGeometry(20,height-135,280,80);
			calcButton->setGeometry(180,height-45,100,25);
			resultTable->setGeometry(320,height-180,width-340,160);
			break;
		case MATGENERATE:
			calcWidget->setGeometry(320,height-180,width-340,160);
			vectorLabel->setGeometry(20,height-220,140,20);
			matrixLabel->setGeometry(160,height-220,140,20);
			typeBox->setGeometry(20,height-190,120,25);
			matrixBox->setGeometry(160,height-190,120,25);
			size1Label->setGeometry(20,height-155,100,20);
			size1Box->setGeometry(140,height-155,85,20);
			sizeButton->setGeometry(230,height-155,50,20);
			label1->setGeometry(20,height-130,140,20);
			input1->setGeometry(160,height-130,120,20);
			label2->setGeometry(20,height-105,140,20);
			input2->setGeometry(160,height-105,120,20);
			label3->setGeometry(20,height-80,140,20);
			input3->setGeometry(160,height-80,120,20);
			calcButton->setGeometry(180,height-45,100,25);
			break;
		case MATANALYSE:
			matrixLabel->setGeometry(20,height-220,120,25);
			matrixBox->setGeometry(160,height-220,120,25);
			size2Label->setGeometry(20,height-190,240,25);
			label1->setGeometry(20,height-160,140,20);
			input1->setGeometry(160,height-160,120,20);
			label2->setGeometry(20,height-135,140,20);
			input2->setGeometry(160,height-135,120,20);
			label3->setGeometry(20,height-110,140,20);
			input3->setGeometry(160,height-110,120,20);
			vectorLabel->setGeometry(320,height-180,width-340,20);
			resultTable->setGeometry(320,height-155,width-340,135);
			calcButton->setGeometry(180,height-45,100,25);
			break;
		case MATINV:
			matrixLabel->setGeometry(20,height-220,120,25);
			matrixBox->setGeometry(140,height-220,140,25);
			size1Label->setGeometry(20,height-180,100,20);
			size1Box->setGeometry(140,height-180,85,20);
			sizeButton->setGeometry(230,height-180,50,20);
			size2Label->setGeometry(20,height-150,280,80);
			calcButton->setGeometry(180,height-45,100,25);
			resultTable->setGeometry(320,height-180,width-340,160);
			break;
	}
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
	varTable->horizontalHeader()->setLabel(0,MATRIXWIDGETH_STR1);
	varTable->horizontalHeader()->setLabel(1,MATRIXWIDGETH_STR2);
	varTable->horizontalHeader()->setLabel(2,MATRIXWIDGETH_STR3);
	
	setOutputTable(currentVar);
	varTable->clearSelection();
	varTable->selectRow(currentVar);
}


void MatrixWidget::setOutputTable(int num)
{
	outputTable->setNumRows(threadData->dimension[num][0]);
	outputTable->setNumCols(threadData->dimension[num][1]);
	setHeader(outputTable);
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
		threadData->numlen[var]=newlen;
		for(int c=threadData->numlen[var]; c<newlen; c++)
		{
			threadData->vars[var][c].type=NNONE;
			threadData->vars[var][c].cval=NULL;
		}
	}

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
		threadData->numlen[var]=newlen;
		for(int c=oldDimension2-1; c>=1; c--)
		{
			for(int c1=oldDimension1-1; c1>=0; c1--)
			{
							
				oldEffIndex=c1+c*oldDimension1;
				newEffIndex=c1+c*threadData->dimension[var][0];
				if(oldEffIndex<threadData->numlen[var] &&newEffIndex<threadData->numlen[var])
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
				if(oldEffIndex<threadData->numlen[var] && newEffIndex<threadData->numlen[var])
					memcpy(&threadData->vars[var][newEffIndex],&threadData->vars[var][oldEffIndex],sizeof(Number));
			}
		}
		threadData->vars[var]=(Number*)realloc((void*)threadData->vars[var],sizeof(Number)*newlen);
		threadData->numlen[var]=newlen;
	}
}

void MatrixWidget::resetInterface()
{
	size1Box->hide();
	size2Box->hide();
	matrixBox->hide();
	vectorBox->hide();
	matrixLabel->hide();
	vectorLabel->hide();
	size1Label->hide();
	size2Label->hide();
	calcButton->hide();
	calcWidget->hide();
	standardButtons->hide();
	resultTable->hide();
	sizeButton->hide();
	label1->hide();
	label2->hide();
	label3->hide();
	input1->hide();
	input2->hide();
	input3->hide();
	typeBox->hide();
	calcButton->setEnabled(true);
	
	switch(state)
	{
		case MATCALC:
			calcWidget->show();
			standardButtons->show();
			break;
		case MATLSE:
			size1Box->setMinValue(1);
			size1Box->setMaxValue(20);
			vectorLabel->setText(MATRIXWIDGETC_STR1);
			size1Box->show();
			matrixBox->show();
			vectorBox->show();
			matrixLabel->show();
			vectorLabel->show();
			size1Label->show();
			size2Label->show();
			calcButton->setText(MATRIXWIDGETH_STR9);
			calcButton->show();
			resultTable->show();
			resultTable->setNumRows(1);
			resultTable->setNumCols(1);
			setHeader(resultTable);
			matrixBox->setCurrentItem(currentVar);
			matrixBoxSlot(currentVar);
			sizeButton->show();
			size1Label->setText(MATRIXWIDGETC_STR2);
			matrixLabel->setText(MATRIXWIDGETC_STR3);
			vectorLabel->setText(MATRIXWIDGETC_STR1);
			size2Label->setText(MATRIXWIDGETC_STR4);
			break;
		case MATGENERATE:
			calcWidget->show();
			vectorLabel->setText(MATRIXWIDGETH_STR1);
			vectorLabel->show();
			typeBox->show();
			matrixLabel->setText(MATRIXWIDGETC_STR5);
			matrixLabel->show();
			matrixBox->show();
			size1Box->show();
			size1Label->show();
			sizeButton->show();
			calcButton->setText(MATRIXWIDGETC_STR6);
			calcButton->show();
			input1->setReadOnly(false);
			input2->setReadOnly(false);
			input2->setReadOnly(false);
			break;
		case MATANALYSE:
			resultTable->show();
			resultTable->setNumRows(1);
			resultTable->setNumCols(1);
			setHeader(resultTable);
			matrixLabel->setText(MATRIXWIDGETC_STR5);
			matrixLabel->show();
			matrixBox->show();
			matrixBox->setCurrentItem(currentVar);
			label1->show();
			label2->show();
			label3->show();
			input1->show();
			input2->show();
			input3->show();
			input1->setReadOnly(true);
			input2->setReadOnly(true);
			input3->setReadOnly(true);
			vectorLabel->setText(MATRIXWIDGETC_STR7);
			vectorLabel->show();
			size2Label->setText("");
			size2Label->show();
			calcButton->setText(MATRIXWIDGETH_STR9);
			calcButton->show();
			matrixBoxSlot(currentVar);
			break;
		case MATINV:
			resultTable->show();
			resultTable->setNumRows(1);
			resultTable->setNumCols(1);
			setHeader(resultTable);
			matrixLabel->setText(MATRIXWIDGETC_STR3);
			matrixLabel->show();
			matrixBox->show();
			matrixBox->setCurrentItem(currentVar);
			size1Box->setMinValue(1);
			size1Box->setMaxValue(20);
			size1Box->show();
			size1Label->show();
			size2Label->setText("");
			size2Label->show();
			sizeButton->show();
			calcButton->setText(MATRIXWIDGETH_STR9);
			calcButton->show();
			matrixBoxSlot(currentVar);
			break;
	}
	resizeEvent(NULL);
}

void MatrixWidget::setHeader(CalcTable*table)
{
	QHeader*tableHeader=table->horizontalHeader();
	for(int c=0; c<tableHeader->count(); c++)
		tableHeader->setLabel(c,QString::number(c));
	tableHeader->adjustHeaderSize();
	tableHeader=table->verticalHeader();
	for(int c=0; c<tableHeader->count(); c++)
		tableHeader->setLabel(c,QString::number(c));
	tableHeader->adjustHeaderSize();
		
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


void MatrixWidget::operationBoxSlot(int index)
{
	state=index;
	resetInterface();
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
	long double num;
	char*end;
	num=strtold(outputTable->text(row,col),&end);
	if(end[0]!=(char)0)
		num=runCalc(outputTable->text(row,col),&pref,vars);

	threadData->vars[currentVar][effIndex].fval=Complex(num);
	
	setOutputTable(currentVar);
}

void MatrixWidget::matrixBoxSlot(int)
{
	if(state==MATLSE || state==MATGENERATE || state==MATINV)
	{
		int size=threadData->dimension[matrixBox->currentItem()][0];
		if(threadData->dimension[matrixBox->currentItem()][1]>size)
		{
			if(vectorBox->currentItem()==0)
				size=threadData->dimension[matrixBox->currentItem()][1]-1;
			else size=threadData->dimension[matrixBox->currentItem()][1];
		}	
		size1Box->setValue(size);
		size1BoxSlot(size);

		if(currentVar!=matrixBox->currentItem())
		{
			currentVar=matrixBox->currentItem();
			setVarTable();
			setOutputTable(currentVar);
		}
		if(state==MATINV)
			size2Label->setText("");

	}
	else if(state==MATANALYSE)
	{
		int var=matrixBox->currentItem();
		long double det,num;
		int rank=0;
		if(threadData->dimension[var][1]!=1)
		{
			size2Label->setText(MATRIXWIDGETC_STR8);
			int effIndex;
			long double*matrix=(long double*)malloc(sizeof(long double)*threadData->dimension[var][0]*threadData->dimension[var][1]);
			for(int c1=0; c1<threadData->dimension[var][1]; c1++)
			{
				for(int c2=0; c2<threadData->dimension[var][0]; c2++)
				{
					effIndex=c2+c1*threadData->dimension[var][0];
					if(effIndex<threadData->numlen[var])
						matrix[effIndex]=threadData->vars[var][effIndex].fval.real();
					else matrix[effIndex]=NAN;
				}
			}
			det=gauss(threadData->dimension[var][1],threadData->dimension[var][0],matrix);
			rank=threadData->dimension[var][0];
			for(int c=threadData->dimension[var][0]-1; c>=0; c--)
			{
				perror(formatOutput(matrix[c+threadData->dimension[var][0]*(threadData->dimension[var][1]-1)],&pref));
				if(matrix[c+threadData->dimension[var][0]*(threadData->dimension[var][1]-1)]==0.0)
					rank=c;
				else break;
			}
			label1->setText(MATRIXWIDGETC_STR9);
			input1->setText(QString::number(threadData->dimension[var][0])+"x"+QString::number(threadData->dimension[var][1]));
			label2->setText(MATRIXWIDGETC_STR10);
			if(threadData->dimension[var][0]==threadData->dimension[var][0])
				input2->setText(formatOutput(det,&pref));
			else input2->setText(MATRIXWIDGETC_STR11);
			label3->setText(MATRIXWIDGETC_STR12);
			input3->setText(QString::number(rank));
			resultTable->setNumRows(threadData->dimension[var][0]);
			resultTable->setNumCols(threadData->dimension[var][1]);
			setHeader(resultTable);
			for(int c1=0; c1<threadData->dimension[var][1]; c1++)
			{
				for(int c2=0; c2<threadData->dimension[var][0]; c2++)
				{
					effIndex=c2+c1*threadData->dimension[var][0];
					resultTable->setText(c2,c1,formatOutput(matrix[effIndex],&pref));
				}
			}
			free(matrix);
		}
		else if(threadData->dimension[var][0]!=1)
		{
			size2Label->setText(MATRIXWIDGETC_STR13);
			label1->setText(MATRIXWIDGETC_STR14);
			input1->setText(QString::number(threadData->dimension[var][0]));
			label2->setText(MATRIXWIDGETC_STR15);
			num=0.0;
			for(int c=0; c<threadData->dimension[var][0] && c<threadData->numlen[var]; c++)
				num+=threadData->vars[var][c].fval.real()*threadData->vars[var][c].fval.real();
			input2->setText(formatOutput(sqrtl(num),&pref));
			label3->setText("");
			input3->setText("");
			resultTable->setNumRows(0);
			resultTable->setNumCols(0);
		}
		else {
			size2Label->setText(MATRIXWIDGETC_STR16);
			label1->setText(MATRIXWIDGETC_STR15);
			input1->setText(formatOutput(fabsl(threadData->vars[var][0].fval.real()),&pref));
			label2->setText("");
			input2->setText("");
			label3->setText("");
			input3->setText("");
			resultTable->setNumRows(0);
			resultTable->setNumCols(0);
		}
		currentVar=matrixBox->currentItem();
		setVarTable();
		setOutputTable(currentVar);
	}
	
}

void MatrixWidget::vectorBoxSlot(int)
{
	if(state==MATLSE && vectorBox->currentItem()!=0)
	{
		if(vectorBox->currentItem()-1==matrixBox->currentItem())
		{
			vectorBox->setCurrentItem(0);
			WarningBox(MATRIXWIDGETC_STR17);
		}

		if(vectorBox->currentItem()!=0)
		{
			currentVar=vectorBox->currentItem()-1;
			setVarTable();
			setOutputTable(currentVar);
			size1BoxSlot(threadData->dimension[currentVar][0]);
		}
	}
}

void MatrixWidget::size1BoxSlot(int newsize)
{
	if(state==MATLSE)
	{
		if(vectorBox->currentItem()==0)
		{
			if(threadData->dimension[matrixBox->currentItem()][0]==newsize &&threadData->dimension[matrixBox->currentItem()][1]==newsize+1)
			{
				calcButton->setEnabled(true);
				size2Label->setText( MATRIXWIDGETC_STR18);
			}
			else {
				calcButton->setEnabled(false);
				size2Label->setText(MATRIXWIDGETC_STR19);
			}
		}
		else
		{
			if(threadData->dimension[matrixBox->currentItem()][0]==newsize &&
				threadData->dimension[matrixBox->currentItem()][1]==newsize &&
				threadData->dimension[vectorBox->currentItem()-1][0]==newsize &&
				threadData->dimension[vectorBox->currentItem()-1][1]==1)
			{
				calcButton->setEnabled(true);
				size2Label->setText(MATRIXWIDGETC_STR20);
			}
			else {
				calcButton->setEnabled(false);
				size2Label->setText(MATRIXWIDGETC_STR21);
			}
		}
	}
}

void MatrixWidget::sizeButtonSlot()
{
	if(state==MATLSE)
	{
		int newsize=size1Box->value();
		if(vectorBox->currentItem()==0)
		{
			resizeVar(matrixBox->currentItem(),newsize,newsize+1);
			if(currentVar!=matrixBox->currentItem())
				currentVar=matrixBox->currentItem();
		}
		else
		{
			resizeVar(matrixBox->currentItem(),newsize,newsize);
			resizeVar(vectorBox->currentItem()-1,newsize,1);
		}
		setVarTable();
		setOutputTable(currentVar);
		calcButton->setEnabled(true);
	}
	else if(state==MATGENERATE || state==MATINV)
	{
		int newsize=size1Box->value();
		resizeVar(matrixBox->currentItem(),newsize,newsize);
		setVarTable();
		setOutputTable(currentVar);
	}
}


void MatrixWidget::typeBoxSlot(int index)
{
	if(state==MATGENERATE)
	{
		switch(index)
		{
			case 3:				//rotate x
				size1Box->setMinValue(2);
				size1Box->setMaxValue(3);
				label1->setText(MATRIXWIDGETC_STR22);
				label1->show();
				label2->hide();
				label3->hide();
				input1->show();
				input2->hide();
				input3->hide();
				break;
			case 4:				//rotate y
				size1Box->setMinValue(3);
				size1Box->setMaxValue(3);
				label1->setText(MATRIXWIDGETC_STR23);
				label1->show();
				label2->hide();
				label3->hide();
				input1->show();
				input2->hide();
				input3->hide();
				break;
			case 5:				//rotate z
				size1Box->setMinValue(3);
				size1Box->setMaxValue(3);
				label1->setText(MATRIXWIDGETC_STR24);
				label1->show();
				label2->hide();
				label3->hide();
				input1->show();
				input2->hide();
				input3->hide();
				break;
			case 6:				//scale
				size1Box->setMinValue(2);
				size1Box->setMaxValue(3);
				label1->setText(MATRIXWIDGETC_STR25);
				label2->setText(MATRIXWIDGETC_STR26);
				label3->setText(MATRIXWIDGETC_STR27);
				label1->show();
				label2->show();
				label3->show();
				input1->show();
				input2->show();
				input3->show();
				break;	
			default:
				size1Box->setMinValue(1);
				size1Box->setMaxValue(20);
				label1->hide();
				label2->hide();
				label3->hide();
				input1->hide();
				input2->hide();
				input3->hide();
		}
	}
}






void MatrixWidget::calcButtonSlot()
{
	switch(state)
	{
		case MATLSE:
		{
			int size=size1Box->value(),effSrcIndex,effDestIndex;
			int matVar=matrixBox->currentItem(),vecVar=vectorBox->currentItem()-1;
			long double *matrix=(long double*)malloc(sizeof(long double)*size*(size+1));
			for(int c1=0; c1<size; c1++)
			{
				for(int c2=0; c2<size; c2++)
				{
					effSrcIndex=c2+c1*threadData->dimension[matVar][0];
					effDestIndex=c2+c1*size;
					if(effSrcIndex<threadData->numlen[matVar])
						matrix[effDestIndex]=threadData->vars[matVar][effSrcIndex].fval.real();
					else matrix[effDestIndex]=NAN;
				}
				if(vecVar==-1)
				{
					if(c1+size*size<threadData->numlen[matVar])
						matrix[c1+size*size]=threadData->vars[matVar][c1+size*size].fval.real();
					else matrix[c1+size*size]=NAN;
				}
				else {
					if(c1<threadData->numlen[vecVar])
						matrix[c1+size*size]=threadData->vars[vecVar][c1].fval.real();
					else matrix[c1+size*size]=NAN;
				}
			}
			gauss(size+1,size,matrix);
			resultTable->setNumRows(size);
			resultTable->setNumCols(1);
			setHeader(resultTable);

			if(matrix[(size-1)*size+size-1]==0.0)
			{
				resultTable->setNumCols(size+1);
				for(int c2=0; c2<size; c2++)
				{
					for(int c3=0; c3<size+1; c3++)
						resultTable->setText(c2,c3,formatOutput(matrix[c3*size+c2],&pref));
				}
				if(matrix[size*size+size-1]==0.0)
					size2Label->setText(MATRIXWIDGETC_STR28);
				else size2Label->setText(MATRIXWIDGETC_STR29);
			}
			else {
				long double *results=(long double*)malloc(sizeof(long double)*size);
				for(int c=size-1; c>=0; c--)
				{
					results[c]=matrix[size*size+c];
					for(int c1=c; c1<size; c1++)
					{
						if(c1!=c)
							results[c]-=results[c1]*matrix[c+c1*size];
					}
					results[c]/=matrix[c+c*size];
					resultTable->setText(c,0,formatOutput(results[c],&pref));
				}
				free(results);
				size2Label->setText(MATRIXWIDGETC_STR30);
			}
			
			for(int c=0; c<resultTable->numCols(); c++)
				resultTable->adjustColumn(c);

			
			
			free(matrix);
			break;
		}
		case MATGENERATE:
		{
			int var=matrixBox->currentItem();
			int size=size1Box->value();
			long double num;
			switch(typeBox->currentItem())
			{
				case 0:							//identity matrix
					resizeVar(var,size,size);
					for(int c1=0; c1<size; c1++)
						for(int c2=0; c2<size; c2++)
					{
						threadData->vars[var][size*c1+c2].type=NFLOAT;
						if(c1==c2)
							threadData->vars[var][size*c1+c2].fval=Complex(1.0,0.0);
						else threadData->vars[var][size*c1+c2].fval=Complex(0.0,0.0);
					}
					break;
				case 1:							//zero matrix
					resizeVar(var,size,size);
					for(int c1=0; c1<size; c1++)
						for(int c2=0; c2<size; c2++)
					{
						threadData->vars[var][size*c1+c2].type=NFLOAT;
						threadData->vars[var][size*c1+c2].fval=Complex(0.0,0.0);
					}
					break;
				case 2:						//zero vector
					resizeVar(var,size,1);
					for(int c=0; c<size; c++)
					{
						threadData->vars[var][c].type=NFLOAT;
						threadData->vars[var][c].fval=Complex(0.0,0.0);
					}	
					break;
				case 3:					//x-rotate mtrix
					resizeVar(var,size,size);
					
					num=runCalc(input1->text(),&pref,vars);
					if(pref.angle==DEG)
						num*=PI/180.0;
					else if(pref.angle==GRA)
						num*=PI/200.0;
					for(int c=0; c<threadData->numlen[var]; c++)
						threadData->vars[var][c].type=NFLOAT;
					if(size==2)
					{
						threadData->vars[var][0].fval=Complex(cosl(num));
						threadData->vars[var][1].fval=Complex(sinl(num));
						threadData->vars[var][2].fval=Complex(-1.0*sinl(num));
						threadData->vars[var][3].fval=Complex(cosl(num));
					}
					else 
					{
						threadData->vars[var][0].fval=Complex(1.0);
						threadData->vars[var][1].fval=Complex(0.0);
						threadData->vars[var][2].fval=Complex(0.0);
						threadData->vars[var][3].fval=Complex(0.0);
						threadData->vars[var][4].fval=Complex(cosl(num));
						threadData->vars[var][5].fval=Complex(sinl(num));
						threadData->vars[var][6].fval=Complex(0.0);
						threadData->vars[var][7].fval=Complex(-1.0*sinl(num));
						threadData->vars[var][8].fval=Complex(cosl(num));
					}
					break;
				case 4:					//y-rotate matrix
					resizeVar(var,size,size);
					num=runCalc(input1->text(),&pref,vars);
					if(pref.angle==DEG)
						num*=PI/180.0;
					else if(pref.angle==GRA)
						num*=PI/200.0;
					for(int c=0; c<threadData->numlen[var]; c++)
						threadData->vars[var][c].type=NFLOAT;
					
					threadData->vars[var][0].fval=Complex(cosl(num));
					threadData->vars[var][1].fval=Complex(0.0);
					threadData->vars[var][2].fval=Complex(-1.0*sinl(num));
					threadData->vars[var][3].fval=Complex(0.0);
					threadData->vars[var][4].fval=Complex(1.0);
					threadData->vars[var][5].fval=Complex(0.0);
					threadData->vars[var][6].fval=Complex(sinl(num));
					threadData->vars[var][7].fval=Complex(0.0);
					threadData->vars[var][8].fval=Complex(cosl(num));
					break;
				case 5:					//z-rotate matrix
					resizeVar(var,size,size);
					num=runCalc(input1->text(),&pref,vars);
					if(pref.angle==DEG)
						num*=PI/180.0;
					else if(pref.angle==GRA)
						num*=PI/200.0;
					for(int c=0; c<threadData->numlen[var]; c++)
						threadData->vars[var][c].type=NFLOAT;
					
					threadData->vars[var][0].fval=Complex(cosl(num));
					threadData->vars[var][1].fval=Complex(sinl(num));
					threadData->vars[var][2].fval=Complex(0.0);
					threadData->vars[var][3].fval=Complex(-1.0*sinl(num));
					threadData->vars[var][4].fval=Complex(cosl(num));
					threadData->vars[var][5].fval=Complex(0.0);
					threadData->vars[var][6].fval=Complex(0.0);
					threadData->vars[var][7].fval=Complex(0.0);
					threadData->vars[var][8].fval=Complex(1.0);
					break;
				case 6:					//scale matrix
					resizeVar(var,size,size);
					for(int c=0; c<threadData->numlen[var]; c++)
					{
						threadData->vars[var][c].type=NFLOAT;
						threadData->vars[var][c].fval=Complex(0.0);
					}
					
					if(size==2)
					{
						num=runCalc(input1->text(),&pref,vars);
						threadData->vars[var][0].fval=Complex(num);
						num=runCalc(input2->text(),&pref,vars);
						threadData->vars[var][2].fval=Complex(num);
					}
					else if(size==3)
					{
						num=runCalc(input1->text(),&pref,vars);
						threadData->vars[var][9].fval=Complex(num);
						num=runCalc(input2->text(),&pref,vars);
						threadData->vars[var][4].fval=Complex(num);
						num=runCalc(input3->text(),&pref,vars);
						threadData->vars[var][8].fval=Complex(num);
					}
					break;
			}
			currentVar=var;
			setVarTable();
			setOutputTable(currentVar);
			break;
		}
		case MATANALYSE:
		{
			matrixBox->setCurrentItem(currentVar);
			matrixBoxSlot(currentVar);
			break;
		}
		case MATINV:
		{
			long double*matrix;
			long double mainDet;
			int size=size1Box->value(),effIndex;
			int var=matrixBox->currentItem();
			
			if(threadData->dimension[var][0]!=threadData->dimension[var][1])
			{
				size2Label->setText(MATRIXWIDGETC_STR31);
				resultTable->setNumRows(1);
				resultTable->setNumCols(1);
				setHeader(resultTable);
				break;
			}
			else size2Label->setText("");
			
			resultTable->setNumRows(size);
			resultTable->setNumCols(size);
			setHeader(resultTable);

			matrix=(long double*)malloc(size*size*sizeof(long double));
			for(int c1=0; c1<size; c1++)
				for(int c2=0; c2<size; c2++)
			{
				effIndex=c1+c2*threadData->dimension[var][0];
				if(effIndex<threadData->numlen[var])
				{
					convertToFloat(&threadData->vars[var][effIndex]);
					matrix[c1+size*c2]=threadData->vars[var][effIndex].fval.real();
				}
			}
			mainDet=gauss(size,size,matrix);
			if(mainDet==0.0)
			{
				size2Label->setText(MATRIXWIDGETC_STR32);
				resultTable->setNumRows(1);
				resultTable->setNumCols(1);
				setHeader(resultTable);
				break;
			}
			mainDet=1.0/mainDet;
			
			resizeVar(27,size,size);
			threadData->dimension[27][0]=threadData->dimension[27][1]=size;
			
			int pos1,pos2,effSrcIndex,effDestIndex,vz;
			for(int c3=0; c3<size; c3++)
			{
				for(int c4=0; c4<size; c4++)
				{
					effIndex=c3+c4*threadData->dimension[var][0];
					pos1=0;
					for(int c1=0; c1<size; c1++)
					{
						if(c1!=c3)
						{
							pos2=0;
							for(int c2=0; c2<size; c2++)
							{
								effDestIndex=pos1+(size-1)*pos2;
								effSrcIndex=c1+c2*threadData->dimension[var][0];
								if(c2!=c4)
								{
									if(effSrcIndex<threadData->numlen[var])
										matrix[effDestIndex]=threadData->vars[var][effSrcIndex].fval.real();
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
					threadData->vars[27][effDestIndex].fval=Complex(mainDet*(long double)vz*subDet);
					threadData->vars[27][effDestIndex].type=NFLOAT;
					resultTable->setText(c4,c3,formatOutput(threadData->vars[27][effDestIndex].fval.real(),&pref));
					if(c4==size-1)
						resultTable->adjustColumn(c3);
				}
				
			}
			free(matrix);
			break;
		}
	}
}



