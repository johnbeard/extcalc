#include "matrixwidget.h"


void MatrixWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();

	
	varTable->setGeometry(20,50,width/4-30,height-290);
	outputTable->setGeometry(width/4+10,50,3*width/4-30,height-290);

	standardButtons->setGeometry(20,height-220,280,200);
	calcWidget->setGeometry(width/2+10,height-180,300,160);
	
	operationBox->setGeometry(width/2+15,height-220,90,35);
	sprodButton->setGeometry(width/2+115,height-220,35,35);
	invertButton->setGeometry(width/2+160,height-220,35,35);
	detButton->setGeometry(width/2+205,height-220,35,35);
	
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

	for(int c1=0; c1<threadData->dimension[num][0]; c1++)
	{
		for(int c2=0; c2<threadData->dimension[num][1]; c2++)
			outputTable->setText(c1,c2,formatOutput(threadData->vars[num][c2*threadData->dimension[num][1]+c1],&pref));
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
	
}

void MatrixWidget::invertButtonSlot()
{
	
}

void MatrixWidget::detButtonSlot()
{
	
}

void MatrixWidget::operationBoxSlot(const QString&)
{
	
}

void MatrixWidget::buttonInputSlot(QString text)
{
	if(text == "calculate")
		calcWidget->calculateKey();
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

