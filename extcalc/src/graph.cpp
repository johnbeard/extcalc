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



  GraphWidget::GraphWidget(QWidget*parent,Preferences pr,Variable*va,ThreadSync*td,ScreenshotDialog *sd,StandardButtons*cB,ExtButtons*eB) :TabWidget(parent,pr,va,td,"graph",false)
  {

    solveMode=false;
    functionChanged=false;
    changedRow=-1;
    dynamicStart=false;
    processStarted=false;


    horzSplit=new QSplitter(Qt::Horizontal,this);
    vertSplit=new QSplitter(Qt::Vertical,horzSplit);
    functionTable=new FunctionTable((QWidget*)vertSplit,pref);
    graphArea=new GraphArea(horzSplit);
    graph=new GraphOutput(graphArea,vars,threadData);
    catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX,this);
    screenshotDialog=sd;
    calcButtons=cB;
    extButtons=eB;

    setMainWidget(horzSplit);

/*		minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
    maximizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_remove.png"));
    printIcon=new QPixmap(INSTALLDIR+QString("/data/print.png"));
    catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));*/

    toolBar=new QToolBar("graphics",parent);

    maximizeAction=new QAction(QIcon(":/view_top_bottom.png"),"",toolBar);
    maximizeAction->setCheckable(true);
    maximizeAction->setChecked(true);
    drawAction=new QAction(QIcon(":/print.png"),"Draw",toolBar);
    catalogAction=new QAction(QIcon(":/catalog.png"),"",toolBar);
    catalogAction->setMenu(catalog);
    toolBar->addAction(maximizeAction);
    toolBar->addAction(drawAction);
    toolBar->addAction(catalogAction);


//		drawButton=new QPushButton(*printIcon,GRAPHH_STR1,toolBar);
//		maximizeButton=new QPushButton(*maximizeIcon,"",toolBar);
    modeBox=new QComboBox(toolBar);
    toolBar->addWidget(modeBox);
//    modeBox->hide();
//		catalogButton=new QPushButton(*catalogIcon,"",toolBar);
//		catalogButton->setFixedWidth(30);
//		maximizeButton->setFixedWidth(30);


//		drawButton->setFixedHeight(25);

    solveType=new QComboBox(toolBar);
//		functionType=new QComboBox(this);
//		solveWidget=new GraphSolveWidget(this,pref,vars,threadData);
//    screenshotDialog=new ScreenshotDialog(parent);
//    screenshotDialog->hide();

    solveType->hide();
//		functionType->hide();
//		solveWidget->hide();
    inputLine=new QLineEdit(vertSplit);
    inputLine->setFixedHeight(25);
    Q3ValueList<int> s = horzSplit->sizes();
    s[1]=300;
    s[0]=300;
    horzSplit->setSizes(s);




    solveType->insertItem(GRAPHH_STR4,-2);
    solveType->insertItem(GRAPHH_STR5,-3);
    solveType->insertItem(GRAPHH_STR6,-3);
    solveType->insertItem(GRAPHH_STR7,-4);
    solveType->insertItem(GRAPHH_STR8,-5);
    solveType->insertItem(GRAPHH_STR9,-6);
    solveType->insertItem(GRAPHH_STR10,-7);
    solveType->insertItem(GRAPHH_STR11,-8);
    solveType->insertItem(GRAPHH_STR26,-9);

//		functionType->insertItem(TABLEH_STR3);
//		functionType->insertItem(TABLEH_STR4);
//		functionType->insertItem(TABLEH_STR5);
//		functionType->insertItem(TABLEH_STR6);
//		functionType->insertItem(TABLEH_STR7);
//		functionType->insertItem(GRAPHH_STR30);
    modeBox->insertItem(tr("Edit"));
    modeBox->insertItem(tr("Screenshot"));
    modeBox->setCurrentItem(0);


    QObject::connect(functionTable,SIGNAL(currentChanged(int,int)),this,SLOT(selectionChangedSlot(int,int)));
    QObject::connect(functionTable,SIGNAL(textEditStarted(QString)),this,SLOT(tableEditSlot(QString)));
    QObject::connect(drawAction,SIGNAL(triggered()),graph,SLOT(resetRotation()));
    QObject::connect(drawAction,SIGNAL(triggered()),graph,SLOT(removeLines()));
    QObject::connect(drawAction,SIGNAL(triggered()),this,SLOT(drawSlot()));
    QObject::connect(modeBox,SIGNAL(activated(int)),this,SLOT(modeSlot(int)));
//		QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
//		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
//    QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
//		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
    QObject::connect(graph,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
    QObject::connect(functionTable,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
//		QObject::connect(solveWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
    QObject::connect(inputLine,SIGNAL(returnPressed()),this,SLOT(inputTextFinished()));
    QObject::connect(inputLine,SIGNAL(textChanged(const QString&)),this,SLOT(inputTextChanged(const QString&)));
//		QObject::connect(graph,SIGNAL(leftMButtonPressed(double,double)),solveWidget,SLOT(graphLMButtonPressed(double,double)));
//		QObject::connect(solveWidget,SIGNAL(addHorizontalLine(double)),graph,SLOT(drawHorizontalLine(double)));
//		QObject::connect(solveWidget,SIGNAL(addVerticalLine(double)),graph,SLOT(drawVerticalLine(double)));
//		QObject::connect(solveWidget,SIGNAL(addPolarLine(double)),graph,SLOT(drawPolarLine(double)));
//		QObject::connect(solveWidget,SIGNAL(addCircle(double)),graph,SLOT(drawCircle(double)));
//		QObject::connect(solveWidget,SIGNAL(add3dXLine(double,double)),graph,SLOT(draw3dXLine(double,double)));
//		QObject::connect(solveWidget,SIGNAL(add3dYLine(double,double)),graph,SLOT(draw3dYLine(double,double)));
//		QObject::connect(solveWidget,SIGNAL(add3dZLine(double,double)),graph,SLOT(draw3dZLine(double,double)));
//		QObject::connect(solveWidget,SIGNAL(removeLines()),graph,SLOT(removeLines()));
    QObject::connect(solveType,SIGNAL(activated(int)),this,SLOT(solveTypeSlot(int)));
//		QObject::connect(this,SIGNAL(solveTypeSignal(int)),solveWidget,SLOT(setState(int)));
//		QObject::connect(functionType,SIGNAL(activated(int)),solveWidget,SLOT(setFunctionType(int)));
//		QObject::connect(functionType,SIGNAL(activated(int)),this,SLOT(functionTypeSlot(int)));
//		QObject::connect(solveWidget,SIGNAL(drawInequalityIntersection(int, int)),this,SLOT(inequalitySlot(int,int)));
    QObject::connect(screenshotDialog,SIGNAL(redrawGraphs()),this,SLOT(drawSlot()));
    QObject::connect(graph,SIGNAL(redrawSignal()),this,SLOT(drawSlot()));
    QObject::connect(graph,SIGNAL(screenshotSignal(QPixmap*)),screenshotDialog,SLOT(screenshotSlot(QPixmap*)));
    QObject::connect(screenshotDialog,SIGNAL(getScreenshotSignal(int,int)),graph,SLOT(screenshotSlot(int,int)));
    QObject::connect(screenshotDialog,SIGNAL(drawSignal(int,QColor,int)),graph,SLOT(drawSlot(int,QColor,int)));
    QObject::connect(this,SIGNAL(drawPointsSignal(long double*,int,bool)),graph,SLOT(drawPoints(long double*,int,bool)));
    QObject::connect(this,SIGNAL(removeLinesSignal()),graph,SLOT(removeLines()));
    QObject::connect(graph,SIGNAL(statisticsRedrawSignal()),this,SIGNAL(statisticsRedrawSignal()));
    QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(processText(QString)));
    QObject::connect(catalogAction,SIGNAL(triggered()),this,SLOT(catalogSlot()));
    QObject::connect(graphArea,SIGNAL(sizeChanged()),this,SLOT(graphSizeSlot()));
    QObject::connect(graph,SIGNAL(processingFinished()),this,SLOT(graphProcessingFinishedSlot()));
    QObject::connect(maximizeAction,SIGNAL(toggled(bool)),this,SLOT(viewSlot(bool)));
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
  qDebug("start drawing");
	if(dynamicStart)
	{
		if(pref.dynamicDelay==0)
		{
			graph->timerSlot();
      drawAction->setText(GRAPHH_STR1);
		}
		else
		{
			dynamicStart=false;
			graph->timerStartSlot(false);
      drawAction->setText(GRAPHH_STR1);
			return;
		}
	}
  qDebug("timer for dynamic graphs initialized");

	if(processStarted)
		return;
  drawAction->setEnabled(false);
	processStarted=true;
  qDebug("processStarted flag checked");
	
	if(functionChanged)
		inputTextFinished();
  qDebug("before clearGL");
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
    drawAction->setText(GRAPHC_STR5);
  else drawAction->setText(GRAPHH_STR1);
	qDebug("data structure creation finished; start processing");
	
	graph->calculateGraphData();

}

void GraphWidget::graphProcessingFinishedSlot()
{
	qDebug("processing finished; initialize gl lists");
	graph->createGLLists();
	qDebug("gl initialization finished");
	graph->repaint(true);
  qDebug("initial repaint successful");
	processStarted=false;
  drawAction->setEnabled(true);
}



void GraphWidget::modeSlot(int)
{
	switch(modeBox->currentItem())
	{
		case 0:
			solveMode=false;
      updateUIState();
			break;
	
		case 1:
      solveMode=true;
      updateUIState();
			break;
			
		case 2:
			solveMode=true;
			solveType->hide();
//			functionType->hide();
//			setDockArea(0);
			removeSubWidget(1);
			emit solveTypeSignal(9);
			break;
	}

}


void GraphWidget::processText(QString text)
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

void GraphWidget::updateUIState()
{
  if(isVisible() && !isMaximized())
  {

    if(solveMode)
    {
      screenshotDialog->show();
      screenshotDialog->setActive(true);
      calcButtons->setActive(false);
      extButtons->setActive(false);
      calcButtons->hide();
      extButtons->hide();
    }
    else {
      calcButtons->setActive(true);
      extButtons->setActive(true);
      calcButtons->show();
      extButtons->show();

    }
  }
  else if(isVisible() && isMaximized())
  {
    calcButtons->setActive(false);
    extButtons->setActive(false);
    screenshotDialog->setActive(false);
    calcButtons->hide();
    extButtons->hide();
    screenshotDialog->hide();
  }
  repaint();
}

void GraphWidget::viewSlot(bool min)
{
  if(min)
  {
    maximizeSlot(false);
  }
  else
  {
    maximizeSlot(true);
  }

  updateUIState();

}


void GraphWidget::solveTypeSlot(int type)
{
/*	switch(functionType->currentItem())
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
  }*/
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
//	catalog->exec(toolBar->mapToGlobal(QPoint(catalogButton->x(),catalogButton->y()+catalogButton->height())));
}

void GraphWidget::dockWindowSlot()
{
  updateUIState();
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






