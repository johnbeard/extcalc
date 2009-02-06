/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         graph.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "graph.h"
//Added by qt3to4:
#include <QResizeEvent>
#include <Q3ValueList>



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
	

	if(maximized)
	{
//		graph->setGeometry(10,menuBottom+40,width-20,height-90);
		horzSplit->setGeometry(20,menuBottom+40,width-40,height-90);
		dockArea->setGeometry(0,menuBottom,width,35);
	}
	else
	{
		horzSplit->setGeometry(20,50,width-40,height-290);

		if(solveMode)
		{
			solveType->setGeometry(20,height-220,width/4-20,30);
			functionType->setGeometry(width/4+10,height-220,width/4-20,30);
			solveWidget->setGeometry(20,height-180,width-40,160);
		}
		standardButtons->setGeometry(20,height-220,280,200);
		extButtons->setGeometry(width/2+10,height-180,300,160);

		dockArea->setGeometry(width/2+15,height-220,width/2-30,35);
	}
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
}




void GraphWidget::drawSlot()
{
	if(dynamicStart)
	{
		if(pref.dynamicDelay==0)
		{
			graph->timerSlot();
			drawButton->setText(GRAPHH_STR1);
		}
		else
		{
			dynamicStart=false;
			graph->timerStartSlot(false);
			drawButton->setText(GRAPHH_STR1);
			return;
		}
	}

	if(processStarted)
		return;
	drawButton->setEnabled(false);
	processStarted=true;
	
	if(functionChanged)
		inputTextFinished();
	graph->clearGL();
	dynamicStart=false;
	int type;
	qDebug("create data structures");
	for(int c=0; c<20; c++)
	{
		if(pref.activeFunctions[c])
		{
			type=pref.functionTypes[c];
			if(type==GRAPHIEGE)
				type=GRAPHIEG;
			else if(type==GRAPHIELE)
				type=GRAPHIEL;

			graph->processFunction(pref.functions[c],"",type,pref.functionColors[c],pref.logicFunctions[c],pref.dynamicFunctions[c]);
			if(type==GRAPHIEL || type==GRAPHIEG)
				graph->processFunction(pref.functions[c],"",GRAPHSTD,QColor(0,0,0),pref.logicFunctions[c],pref.dynamicFunctions[c]);

			if(pref.dynamicFunctions[c])
				dynamicStart=true;
		}
	}
	
	if(dynamicStart && pref.dynamicDelay!=0)
		drawButton->setText(GRAPHC_STR5);
	else drawButton->setText(GRAPHH_STR1);
	qDebug("data structure creation finished; start processing");
	
	graph->calculateGraphData();

}

void GraphWidget::graphProcessingFinishedSlot()
{
	qDebug("processing finished; initialize gl lists");
	graph->createGLLists();
	qDebug("gl initialization finished");
	graph->repaint(true);
	processStarted=false;
	drawButton->setEnabled(true);
}


void GraphWidget::maximizeSlot()
{
	if(maximized)
	{
		maximized=false;
		modeBox->show();
		maximizeButton->setIconSet(*maximizeIcon);
		Q3ValueList<int> s = horzSplit->sizes();
		s[1]=(s[0]+s[1])/2;
		s[0]=s[1];
		horzSplit->setSizes(s);
		if(solveMode)
		{
			solveMode=false;
			modeSlot(0);
		}
		else
		{
			standardButtons->show();
			extButtons->show();
		}
		resizeEvent(NULL);
	}
	else
	{
		maximized=true;

		standardButtons->hide();
		extButtons->hide();
		Q3ValueList<int> s = horzSplit->sizes();
		s[1]=s[0]+s[1];
		s[0]=0;
		horzSplit->setSizes(s);
		modeBox->hide();
		solveType->hide();
		functionType->hide();
		solveWidget->hide();
		maximizeButton->setIconSet(*minimizeIcon);
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
			Q3CheckTableItem *checkItem=(Q3CheckTableItem*)functionTable->item(functionTable->currentRow(),2);
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
		Q3CheckTableItem *checkItem=(Q3CheckTableItem*)functionTable->item(functionTable->currentRow(),2);
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
		case 5: //nyquist
			if(type==0 || type==1)
				emit solveTypeSignal(type);
			else if(type==2)
				emit solveTypeSignal(3);
			else if(type==3)
				emit solveTypeSignal(9);
			break;
	}
}

void GraphWidget::functionTypeSlot(int fType)
{
	//		y-value						normal	polar	parameter	inequaity	3D	nyquist
	//		extreme values				normal	polar				inequaity	3D
	//		integral					normal	polar				inequaity	3D
	//		differential				normal	polar	parameter	inequaity	3D
	//		roots						normal	polar	parameter	inequaity		nyquist
	//		x-value						normal	polar	parameter	inequaity		nyquist
	//		newton's method				normal	polar				inequaity
	//		points of intersection		normal	polar				inequaity


//	functionType->setCurrentItem(fType);
	if(fType==0 || fType == 2 || fType == 3 || (fType==5 &&pref.graphType!=GRAPHPOLAR && pref.graphType!=GRAPH3D) && pref.graphType!=GRAPHSTD)
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
			solveType->insertItem(GRAPHH_STR26,-9);
			break;
		case 2:	//parameter
			solveType->clear();
			solveType->insertItem(GRAPHH_STR4,-2);
			solveType->insertItem(GRAPHH_STR5,-3);
			solveType->insertItem(GRAPHH_STR7,-4);
			solveType->insertItem(GRAPHH_STR11,-7);
			solveType->insertItem(GRAPHH_STR26,-9);
			break;
		case 4:	//3D
			solveType->clear();
			solveType->insertItem(GRAPHH_STR4,-2);
			solveType->insertItem(GRAPHH_STR7,-4);
			solveType->insertItem(GRAPHH_STR10,-7);
			solveType->insertItem(GRAPHH_STR11,-8);
			solveType->insertItem(GRAPHH_STR25,-9);
			solveType->insertItem(GRAPHH_STR26,-9);
			break;
		case 5: // nyquist
			solveType->clear();
			solveType->insertItem(GRAPHH_STR4,-2);
			solveType->insertItem(GRAPHH_STR5,-3);
			solveType->insertItem(GRAPHH_STR7,-4);
			solveType->insertItem(GRAPHH_STR26,-9);
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

void GraphWidget::catalogSlot()
{
	catalog->exec(toolBar->mapToGlobal(QPoint(catalogButton->x(),catalogButton->y()+catalogButton->height())));
}

void GraphWidget::dockWindowSlot()
{
	dockArea->moveDockWindow(toolBar);
}


void GraphWidget::graphSizeSlot()
{
	int width=graphArea->width(),height=graphArea->height();
	int newWidth,newHeight;
	float wtohWin,wtohCs;
	if(pref.autosize)
	{
		wtohWin=(float)width/(float)height;
		if(pref.graphType==GRAPHSTD)
			wtohCs=((pref.xmax-pref.xmin)/pref.rasterSizeX)/((pref.ymax-pref.ymin)/pref.rasterSizeY);
		else wtohCs=1.0;
		
		if(wtohCs<wtohWin)
		{
			newHeight=height;
			newWidth=(int)((float)height*wtohCs);
		}
		else 
		{
			newWidth=width;
			newHeight=(int)((float)width/wtohCs);
		}
	}
	else 
	{
		newWidth=width;
		newHeight=height;
	}
	graph->setGeometry((width-newWidth)/2,(height-newHeight)/2,newWidth,newHeight);
}

void GraphWidget::inequalitySlot(int i1,int i2)
{
	pref.activeFunctions[i1]=pref.activeFunctions[i2]=false;
	drawSlot();
	pref.activeFunctions[i1]=pref.activeFunctions[i2]=true;	
	if((pref.functionTypes[i1]==GRAPHIEG || pref.functionTypes[i1]==GRAPHIEGE) && 
		   (pref.functionTypes[i2]==GRAPHIEG || pref.functionTypes[i2]==GRAPHIEGE))
		graph->processFunction(pref.functions[i1],pref.functions[i2],GRAPHIEG,QColor(123,121,255),pref.logicFunctions[i1]|pref.logicFunctions[i2],false);
	else if((pref.functionTypes[i1]==GRAPHIEL || pref.functionTypes[i1]==GRAPHIELE) && 
				(pref.functionTypes[i2]==GRAPHIEL || pref.functionTypes[i2]==GRAPHIELE))
		graph->processFunction(pref.functions[i1],pref.functions[i2],GRAPHIEL,QColor(123,121,255),pref.logicFunctions[i1]|pref.logicFunctions[i2],false);
	else if((pref.functionTypes[i1]==GRAPHIEG || pref.functionTypes[i1]==GRAPHIEGE) && 
		   (pref.functionTypes[i2]==GRAPHIEL || pref.functionTypes[i2]==GRAPHIELE))
		graph->processFunction(pref.functions[i1],pref.functions[i2],GRAPHIEGE,QColor(123,121,255),pref.logicFunctions[i1]|pref.logicFunctions[i2],false);
	else if((pref.functionTypes[i1]==GRAPHIEL || pref.functionTypes[i1]==GRAPHIELE) && 
		   (pref.functionTypes[i2]==GRAPHIEG || pref.functionTypes[i2]==GRAPHIEGE))
		graph->processFunction(pref.functions[i1],pref.functions[i2],GRAPHIELE,QColor(123,121,255),pref.logicFunctions[i1]|pref.logicFunctions[i2],false);

	graph->processFunction(pref.functions[i1],"",GRAPHSTD,pref.functionColors[i1],pref.logicFunctions[i1],false);
	graph->processFunction(pref.functions[i2],"",GRAPHSTD,pref.functionColors[i2],pref.logicFunctions[i2],false);


	graph->calculateGraphData();
	graph->createGLLists();


	graph->repaint(true);
}






