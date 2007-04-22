#include "table.h"

void TableWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();


	if(fullscreen)
	{
		outputTable->setGeometry(20,50,width-40,height-100);
		
		calculateButton->setGeometry(20,height-45,90,35);
		typeBox->setGeometry(120,height-45,90,35);
		maximizeButton->setGeometry(220,height-45,90,35);
	}
	else
	{
		functionTable->setGeometry(20,50,width/2-30,height-320);
		outputTable->setGeometry(width/2+10,50,width/2-30,height-290);
		inputLine->setGeometry(20,height-260,width/2-30,20);
	
		standardButtons->setGeometry(20,height-220,280,200);
		extButtons->setGeometry(width/2+10,height-180,300,160);
		
		calculateButton->setGeometry(width/2+15,height-220,90,35);
		typeBox->setGeometry(width/2+115,height-220,90,35);
		maximizeButton->setGeometry(width/2+215,height-220,90,35);
	}
}


void TableWidget::setPref(Preferences p)
{
	pref=p;
	if(pref.tableType==TABLENORMAL)
		typeBox->setCurrentText(TABLEH_STR3);
	else if(pref.tableType==TABLEPOLAR)
		typeBox->setCurrentText(TABLEH_STR4);
	else if(pref.tableType==TABLEPARAMETER)
		typeBox->setCurrentText(TABLEH_STR5);
	else if(pref.tableType==TABLEINEQUAITY)
		typeBox->setCurrentText(TABLEH_STR6);
	else if(pref.tableType==TABLE3D)
		typeBox->setCurrentText(TABLEH_STR7);
	else if(pref.tableType==TABLECOMPLEX)
		typeBox->setCurrentText(TABLEH_STR9);
	
	
	outputTable->setNumRows(pref.tableXSteps);
	double tableXStep=(pref.tableXEnd-pref.tableXStart)/(pref.tableXSteps-1);
	double tableZStep=(pref.tableZEnd-pref.tableZStart)/(pref.tableZSteps-1);

	int oldNum=vertValues.GetLen();
	
	if(oldNum<pref.tableXSteps)
	{
		for(int c=oldNum; c<pref.tableXSteps; c++)
			vertValues.NewItem(c*tableXStep+pref.tableXStart);
	}
	else {
		for(int c=pref.tableXSteps; c<oldNum; c++)
			vertValues.DeleteItem(pref.tableXSteps);
	}
	for(int c=0; c<pref.tableXSteps; c++)
	{
		vertValues[c]=c*tableXStep+pref.tableXStart;
		vertHeader->setLabel(c,QString::number(vertValues[c],'g',5));
	}
	
	oldNum=horzValues.GetLen();
	if(oldNum<pref.tableZSteps)
	{
		for(int c=oldNum; c<pref.tableZSteps; c++)
			horzValues.NewItem(c*tableZStep+pref.tableZStart);
	}
	else {
		for(int c=pref.tableZSteps; c<oldNum; c++)
			horzValues.DeleteItem(pref.tableZSteps);
	}
	for(int c=0; c<pref.tableZSteps; c++)
		horzValues[c]=c*tableZStep+pref.tableZStart;


	standardButtons->setPref(pref);
	extButtons->setPref(pref);
	functionTable->setPref(pref);
}

void TableWidget::getPref(Preferences p)
{
	pref=p;
	emit prefChange(pref);
}

void TableWidget::inputTextChanged()
{
	functionTable->setFunctionText(inputLine->text());
	inputLine->clearFocus();
}

void TableWidget::selectionChangedSlot(int row,int)
{
	if(functionTable->text(row,0).length() > 0)		//10000th code line
		inputLine->setText(functionTable->text(row,0));
	else inputLine->clear();
}

void TableWidget::tableEditSlot(QString string)
{
	if(string.length() > 0)
		inputLine->setText(string);
	else inputLine->clear();
	inputLine->setActiveWindow();
	inputLine->setFocus();
}

void TableWidget::calculateButtonSlot()
{
	outputTable->setNumCols(0);
	
	if(pref.tableType==TABLENORMAL)
	{
		vars[0]=pref.tableAValue;
		for(int c=0; c<20;c++)
		{
			if(pref.functionTypes[c]==GRAPHSTD &&pref.activeFunctions[c])
			{
				outputTable->setNumCols(outputTable->numCols()+1);
				horzHeader->setLabel(outputTable->numCols()-1,"y"+QString::number(c+1)+"(x)");
				char*cleanString=checkString(pref.functions[c],&pref);
				Calculate ca(NULL,cleanString,&pref,vars);
				
				for(int c=0; c<pref.tableXSteps;c++)
				{
					vars[23]=vertValues[c];
					outputTable->setText(c,outputTable->numCols()-1,formatOutput(ca.calc(),&pref));
				}
			}
		}
	}
	else if(pref.tableType==TABLEPOLAR)
	{
		vars[0]=pref.tableAValue;
		for(int c=0; c<20;c++)
		{
			if(pref.functionTypes[c]==GRAPHPOLAR &&pref.activeFunctions[c])
			{
				outputTable->setNumCols(outputTable->numCols()+1);
				outputTable->horizontalHeader()->setLabel(outputTable->numCols()-1,"r"+QString::number(c+1)+"(x)");
				char*cleanString=checkString(pref.functions[c],&pref);
				Calculate ca(NULL,cleanString,&pref,vars);
				for(int c=0; c<pref.tableXSteps;c++)
				{
					vars[23]=vertValues[c];
					outputTable->setText(c,outputTable->numCols()-1,formatOutput(ca.calc(),&pref));
				}
			}
		}
	}
	else if(pref.tableType==TABLEPARAMETER)
	{
		vars[0]=pref.tableAValue;
		for(int c=0; c<20;c++)
		{
			if(pref.functionTypes[c]==GRAPHPARAMETER &&pref.activeFunctions[c])
			{
				outputTable->setNumCols(outputTable->numCols()+2);
				outputTable->horizontalHeader()->setLabel(outputTable->numCols()-2,"X"+QString::number(c+1)+"(T)");
				outputTable->horizontalHeader()->setLabel(outputTable->numCols()-1,"Y"+QString::number(c+1)+"(T)");
				char*cleanStringX=checkString(pref.functions[c].left(pref.functions[c].find("\\")),&pref);
				char*cleanStringY=checkString(pref.functions[c].right(pref.functions[c].length()-1-pref.functions[c].find("\\")),&pref);
				Calculate caX(NULL,cleanStringX,&pref,vars);
				Calculate caY(NULL,cleanStringY,&pref,vars);
				for(int c=0; c<pref.tableXSteps;c++)
				{
					vars[19]=vertValues[c];
					outputTable->setText(c,outputTable->numCols()-2,formatOutput(caX.calc(),&pref));
					outputTable->setText(c,outputTable->numCols()-1,formatOutput(caY.calc(),&pref));
				}
			}
		}
	}
	else if(pref.tableType==TABLEINEQUAITY)
	{
		vars[0]=pref.tableAValue;
		for(int c=0; c<20;c++)
		{
			if((pref.functionTypes[c]==GRAPHIEGE || 
						 pref.functionTypes[c]==GRAPHIEG || 
						 pref.functionTypes[c]==GRAPHIELE || 
						 pref.functionTypes[c]==GRAPHIEG )&&pref.activeFunctions[c])
			{
				outputTable->setNumCols(outputTable->numCols()+1);
				outputTable->horizontalHeader()->setLabel(outputTable->numCols()-1,"y"+QString::number(c+1)+"(x)");
				char*cleanString=checkString(pref.functions[c],&pref);
				Calculate ca(NULL,cleanString,&pref,vars);
				for(int c=0; c<pref.tableXSteps;c++)
				{
					vars[23]=vertValues[c];
					outputTable->setText(c,outputTable->numCols()-1,formatOutput(ca.calc(),&pref));
				}
			}
		}
	}
	else if(pref.tableType==TABLE3D)  
	{
		vars[0]=pref.tableAValue;
		for(int c=0; c<20;c++)
		{
			if(pref.functionTypes[c]==GRAPH3D &&pref.activeFunctions[c])
			{
				outputTable->setNumCols(outputTable->numCols()+pref.tableZSteps);
				for(int c1=0; c1<pref.tableZSteps;c1++)
					outputTable->horizontalHeader()->setLabel(outputTable->numCols()-pref.tableZSteps+c1,"y"+QString::number(c+1)+"(x"+QString::number(horzValues[c1],'g',5)+")");
				char*cleanString=checkString(pref.functions[c],&pref);
				Calculate ca(NULL,cleanString,&pref,vars);
				for(int c2=0; c2<pref.tableXSteps;c2++)
				{
					for(int c1=0; c1<pref.tableZSteps;c1++)
					{
						vars[23]=vertValues[c2];
						vars[25]=horzValues[c1];
						outputTable->setText(c2,outputTable->numCols()-pref.tableZSteps+c1,formatOutput(ca.calc(),&pref));
					}
				}
			}
		}
	}
	else if(pref.tableType==TABLECOMPLEX)
	{
		threadData->vars[0][0].fval=Complex(pref.tableAValue);
		bool complexPref=pref.complex;
		pref.complex=true;
		for(int c=0; c<20;c++)
		{
			if((pref.functionTypes[c]==GRAPHCOMPLEX || pref.functionTypes[c]==GRAPHCOMP3D) &&pref.activeFunctions[c])
			{
				outputTable->setNumCols(outputTable->numCols()+1);
				horzHeader->setLabel(outputTable->numCols()-1,"F"+QString::number(c+1)+"(z)");
				char*cleanString=checkString(pref.functions[c],&pref);
				if(cleanString==NULL || strlen(cleanString)<=0)
				{
					for(int c=0; c<pref.tableXSteps; c++)
						outputTable->setText(c,outputTable->numCols()-1,"nan");
					continue;
				}
				Script ca(NULL,cleanString,&pref,vars,threadData);
				threadData->vars[25][0].type=NFLOAT;
				for(int c=0; c<pref.tableXSteps;c++)
				{
					threadData->vars[25][0].fval=Complex(vertValues[c]);
					outputTable->setText(c,outputTable->numCols()-1,formatOutput(ca.exec(),&pref));
				}
			}
		}
		pref.complex=complexPref;
	}
}


void TableWidget::maximizeButtonSlot()
{
	if(fullscreen)
	{
		maximizeButton->setText(TABLEH_STR2);
		standardButtons->show();
		extButtons->show();
		functionTable->show();
		inputLine->show();
	}
	else 
	{
		maximizeButton->setText(TABLEH_STR8);
		standardButtons->hide();
		extButtons->hide();
		functionTable->hide();
		inputLine->hide();
	}
	fullscreen=!fullscreen;
	resizeEvent(NULL);
	
}

void TableWidget::typeBoxSlot(const QString&str)
{

	if(str==TABLEH_STR3)
		pref.tableType=TABLENORMAL;
	else if(str==TABLEH_STR4)
		pref.tableType=TABLEPOLAR;
	else if(str==TABLEH_STR5)
		pref.tableType=TABLEPARAMETER;
	else if(str==TABLEH_STR6)
		pref.tableType=TABLEINEQUAITY;
	else if(str==TABLEH_STR7)
		pref.tableType=TABLE3D;
	else if(str==TABLEH_STR9)
		pref.tableType=TABLECOMPLEX;
	emit prefChange(pref);
}


void TableWidget::buttonInputSlot(QString text)
{
	
	if(text == "calculate")
	{
		calculateButtonSlot();
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
	//	functionTable->clearCell(functionTable->currentRow(),0);
	//	inputLine->clear();
	//	QCheckTableItem *checkItem=(QCheckTableItem*)functionTable->item(functionTable->currentRow(),2);
	//	checkItem->setChecked(false);
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

void TableWidget::editSlot(int type)
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
	else {
		if(type==EDITCOPY)
		{
			
			if(functionTable->hasFocus())
			{
				if(functionTable->currentColumn()==0)
					(qApp->clipboard())->setText(functionTable->text(functionTable->currentRow(),0),QClipboard::Clipboard);
			}
			else if(outputTable->hasFocus())
			{
				(qApp->clipboard())->setText(outputTable->text(outputTable->currentRow(),outputTable->currentColumn()),QClipboard::Clipboard);
			}
		}
	}
}

void TableWidget::horzHeaderSlot(int index)
{
	bool ok;

	if(pref.tableType!=TABLE3D)
		return;
	index=index%pref.tableZSteps;
	QString input = QInputDialog::getText(
			TABLEH_STR10, TABLEH_STR11+QString::number(index+1)+":", QLineEdit::Normal,
	QString::null, &ok, this );
	if ( ok && input.length()>0 )
	{
		horzValues[index]=runCalc(input,&pref,vars);
		calculateButtonSlot();
	}
	
}

void TableWidget::vertHeaderSlot(int index)
{
	bool ok;
	QString input = QInputDialog::getText(
			TABLEH_STR10, TABLEH_STR12+QString::number(index+1)+":", QLineEdit::Normal,
	QString::null, &ok, this );
	if ( ok && input.length()>0 )
	{
		vertValues[index]=runCalc(input,&pref,vars);
		vertHeader->setLabel(index,QString::number(vertValues[index],'g',5));
		calculateButtonSlot();
	}
}

void TableWidget::tableMenuSlot(int item)
{
	if(item==RESETTABLE)
	{
		double tableXStep=(pref.tableXEnd-pref.tableXStart)/(pref.tableXSteps-1);
		double tableZStep=(pref.tableZEnd-pref.tableZStart)/(pref.tableZSteps-1);
		
		for(int c=0; c<vertValues.GetLen(); c++)
		{
			vertValues[c]=pref.tableXStart+c*tableXStep;
			vertHeader->setLabel(c,QString::number(vertValues[c],'g',5));
		}
		for(int c=0; c<horzValues.GetLen(); c++)
			horzValues[c]=pref.tableZStart+c*tableZStep;
		calculateButtonSlot();
	}
}


