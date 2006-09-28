#include "graph.h"



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////GraphOutput/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////GraphWidget/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


void GraphWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();
	

	if(pref.autosize)
	{
		int maxWidth,maxHeight;
		if(maximized)
		{
			maxWidth=width-20;
			maxHeight=height-100;
		}
		else {
			maxWidth=width/2-30;
			maxHeight=height-290;
		}
			
		double graphWidth=pref.xmax-pref.xmin,graphHeight=pref.ymax-pref.ymin;
		if(graphWidth/(double)maxWidth>graphHeight/(double)maxHeight)
		{
			double pixelPerLength=(double)maxWidth/graphWidth;
			int pixelHeight=(int)(pixelPerLength*graphHeight);
			if(pixelHeight<10)
				pixelHeight=10;
			if(maximized)
				graph->setGeometry(10,40+(maxHeight-pixelHeight)/2,width-20,pixelHeight);
			else graph->setGeometry(width/2+10,50+(maxHeight-pixelHeight)/2,width/2-30,pixelHeight);
		}
		else
		{
			double pixelPerLength=(double)maxHeight/graphHeight;
			int pixelWidth=(int)(pixelPerLength*graphWidth);
			if(pixelWidth<10)
				pixelWidth=10;
			if(maximized)
				graph->setGeometry(10+(maxWidth-pixelWidth)/2,50,pixelWidth,height-100);
			else graph->setGeometry(width/2+10+(maxWidth-pixelWidth)/2,50,pixelWidth,height-290);
		}
		
	}
	else{
		if(maximized)
			graph->setGeometry(10,40,width-20,height-100);
		else graph->setGeometry(width/2+10,50,width/2-30,height-290);
	}
	functionTable->setGeometry(20,50,width/2-30,height-320);
	inputLine->setGeometry(20,height-260,width/2-30,20);
	if(solveMode && !maximized)
	{
		solveType->setGeometry(20,height-220,width/4-20,30);
		functionType->setGeometry(width/4+10,height-220,width/4-20,30);
		solveWidget->setGeometry(20,height-180,width-40,160);
	}
	standardButtons->setGeometry(20,height-220,280,200);
	extButtons->setGeometry(width/2+10,height-180,300,160);
	drawButton->setGeometry(width/2+15,height-220,90,35);
	modeBox->setGeometry(width/2+115,height-220,90,35);
	if(maximized)
		maximizeButton->setGeometry(10,height-45,90,35);
	else maximizeButton->setGeometry(width/2+215,height-220,90,35);

}



void GraphWidget::selectionChangedSlot(int row,int)
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

void GraphWidget::tableEditSlot(QString string)
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
	perror("tableEditSlot");
}




void GraphWidget::drawSlot()
{
	if(functionChanged)
		inputTextFinished();
	graph->clearGL();
	for(int c=0; c<20; c++)
	{
		if(pref.activeFunctions[c])
			graph->processFunction(c);
	}
	graph->repaint(true);
}


void GraphWidget::maximizeSlot()
{
	if(maximized)
	{
		maximized=false;
		functionTable->show();
		drawButton->show();
		modeBox->show();
		inputLine->show();
		maximizeButton->setText(GRAPHC_STR1);
		if(solveMode)
		{
			solveMode=false;
			modeSlot(0);
		}
		else {
			standardButtons->show();
			extButtons->show();
		}
		resizeEvent(NULL);
	}
	else {
		maximized=true;

		standardButtons->hide();
		extButtons->hide();
		functionTable->hide();
		drawButton->hide();
		modeBox->hide();
		inputLine->hide();
		solveType->hide();
		functionType->hide();
		solveWidget->hide();
		maximizeButton->setText(GRAPHC_STR2);
		resizeEvent(NULL);
	 }
}

void GraphWidget::modeSlot(int)
{
	switch(modeBox->currentItem())
	{
		case 0:
			solveMode=false;
			standardButtons->show();
			extButtons->show();
			solveType->hide();
			functionType->hide();
			solveWidget->hide();
			break;
	
		case 1:
			solveMode=true;
			standardButtons->hide();
			extButtons->hide();
			solveType->show();
			functionType->show();
			solveWidget->show();
			solveType->setCurrentItem(0);
			emit solveTypeSignal(0);
			break;
			
		case 2:
			solveMode=true;
			standardButtons->hide();
			extButtons->hide();
			solveType->hide();
			functionType->hide();
			solveWidget->show();
			emit solveTypeSignal(9);
			break;
	}
	resizeEvent(NULL);

}


void GraphWidget::buttonInputSlot(QString text)
{
	if(text == "calculate")
	{
		drawSlot();
	}
	else if(text == "backkey")
	{
		if(inputLine->cursorPosition() > 0)
			inputLine->backspace();
		else inputLine->del();
		functionTable->setText(functionTable->currentRow(),0,inputLine->text());
		if((inputLine->text().length())<=0)
		{
			QCheckTableItem *checkItem=(QCheckTableItem*)functionTable->item(functionTable->currentRow(),2);
			checkItem->setChecked(false);
		}
	}
	else if(text == "clearall")
	{
//		functionTable->clearCell(functionTable->currentRow(),0);
//		inputLine->clear();
//		QCheckTableItem *checkItem=(QCheckTableItem*)functionTable->item(functionTable->currentRow(),2);
//		checkItem->setChecked(false);
		functionTable->setFunctionText("");
	}
	else {
		QString fullText=inputLine->text();
		int cursorPos=inputLine->cursorPosition();
		fullText.insert(cursorPos,text);
		inputLine->setText(fullText);
		inputLine->setCursorPosition(cursorPos+text.length());
		functionTable->setText(functionTable->currentRow(),0,inputLine->text());
		QCheckTableItem *checkItem=(QCheckTableItem*)functionTable->item(functionTable->currentRow(),2);
		checkItem->setChecked(true);
	
		
	}
	
}
void GraphWidget::solveTypeSlot(int type)
{
	switch(functionType->currentItem())
	{
		case 0:	//normal
		case 1:	//polar
		case 3:	//inequaity
			if(type==8)
				emit solveTypeSignal(9);
			else emit solveTypeSignal(type);
			break;
		case 2:	//parameter
			if(type==0 || type==1)
				emit solveTypeSignal(type);
			else if(type==2)
				emit solveTypeSignal(3);
			else if(type==3)
				emit solveTypeSignal(7);
			else if(type==4)
				emit solveTypeSignal(9);
			break;
		case 4:	//3D
			if(type==0)
				emit solveTypeSignal(0);
			else if(type==1)
				emit solveTypeSignal(3);
			else if(type==2)
				emit solveTypeSignal(6);
			else if(type==3)
				emit solveTypeSignal(7);
			else if(type==4)
				emit solveTypeSignal(8);
			else if(type==5)
				emit solveTypeSignal(9);
			break;
	}
}

void GraphWidget::functionTypeSlot(int fType)
{
	//		y-value						normal	polar	parameter	inequaity	3D
	//		extreme values				normal	polar				inequaity	3D
	//		integral					normal	polar				inequaity	3D
	//		differential				normal	polar	parameter	inequaity	3D
	//		roots						normal	polar	parameter	inequaity
	//		x-value						normal	polar	parameter	inequaity
	//		newton's method				normal	polar				inequaity
	//		points of intersection		normal	polar				inequaity


//	functionType->setCurrentItem(fType);
	if(fType==0 || fType == 2 || fType == 3 && pref.graphType!=GRAPHSTD)
	{
		pref.graphType=GRAPHSTD;
		emit prefChange(pref);
		graph->repaint();
	}
	else if(fType == 1 && pref.graphType!=GRAPHPOLAR)
	{
		pref.graphType=GRAPHPOLAR;
		emit prefChange(pref);
		graph->repaint();
	}
	else if(fType == 4 && pref.graphType!=GRAPH3D)
	{
		pref.graphType=GRAPH3D;
		emit prefChange(pref);
		graph->repaint();
	}
	switch(fType)
	{
		case 0:	//normal
		case 1:	//polar
		case 3:	//inequaity
			solveType->clear();
			solveType->insertItem(GRAPHH_STR4,-2);
			solveType->insertItem(GRAPHH_STR5,-3);
			solveType->insertItem(GRAPHH_STR6,-3);
			solveType->insertItem(GRAPHH_STR7,-4);
			solveType->insertItem(GRAPHH_STR8,-5);
			solveType->insertItem(GRAPHH_STR9,-6);
			solveType->insertItem(GRAPHH_STR10,-7);
			solveType->insertItem(GRAPHH_STR11,-8);
			solveType->insertItem("Save and modify",-9);
			break;
		case 2:	//parameter
			solveType->clear();
			solveType->insertItem(GRAPHH_STR4,-2);
			solveType->insertItem(GRAPHH_STR5,-3);
			solveType->insertItem(GRAPHH_STR7,-4);
			solveType->insertItem(GRAPHH_STR11,-7);
			solveType->insertItem("Save and modify",-9);
			break;
		case 4:	//3D
			solveType->clear();
			solveType->insertItem(GRAPHH_STR4,-2);
			solveType->insertItem(GRAPHH_STR7,-4);
			solveType->insertItem(GRAPHH_STR10,-7);
			solveType->insertItem(GRAPHH_STR11,-8);
			solveType->insertItem(GRAPHH_STR25,-9);
			solveType->insertItem("Save and modify",-9);
			break;
	}
	solveTypeSlot(solveType->currentItem());
}

void GraphWidget::inputTextFinished()
{
	if(functionChanged)
	{
		functionTable->setFunctionText(inputLine->text(),changedRow);
		functionChanged=false;
	}
	inputLine->clearFocus();
}

void GraphWidget::inputTextChanged(const QString&)
{
	functionChanged=true;
}


void GraphWidget::editSlot(int type)
{
	if(inputLine->hasFocus())
	{
		switch(type)
		{
			case EDITUNDO:
				inputLine->undo();
				break;
			case EDITREDO:
				inputLine->redo();
				break;
			case EDITCUT:
				inputLine->cut();
				break;
			case EDITCOPY:
				inputLine->copy();
				break;
			case EDITPASTE:
				inputLine->paste();
				break;
		}
	}
	else if(type==EDITCOPY && functionTable->hasFocus())
	{
				if(functionTable->currentColumn()==0)
					(qApp->clipboard())->setText(functionTable->text(functionTable->currentRow(),0),QClipboard::Clipboard);
	}
}





