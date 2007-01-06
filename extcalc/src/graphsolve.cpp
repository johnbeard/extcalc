#include "graphsolve.h"




void GraphSolveWidget::setState(int newSolveType)
{
	solveType=newSolveType;
	resetDialog();
}


void GraphSolveWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right() - geometry().left();
	int height=geometry().bottom() - geometry().top();
	
	switch(solveType)
	{
		case CALCYVAL:
		{
			if(functionType==GRAPHPARAMETER || functionType==GRAPHCOMPLEX)
			{
				xLabel->setGeometry(20,0,width/2-20,20);
				yLabel->setGeometry(width/2+5,0,width/2-20,20);
				outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
				functionBox->setGeometry(20,30,width/2-25,30);
				solveButton->setGeometry(width/2-105,height-30,100,30);
				x2Label->setGeometry(20,70,width/2-25,20);
				xLine->setGeometry(20,100,width/2-25,20);
			}
			else if(functionType==GRAPH3D)
			{
				xLabel->setGeometry(20,0,width/2-20,20);
				yLabel->setGeometry(width/2+5,0,width/2-20,20);
				outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
				functionBox->setGeometry(20,30,width/2-25,30);	
				x2Label->setGeometry(20,70,width/2-80,20);
				xLine->setGeometry(width/2-100,70,90,20);	
				x3Label->setGeometry(20,100,width/2-80,20);
				x2Line->setGeometry(width/2-100,100,90,20);
				solveButton->setGeometry(width/2-105,height-30,100,30);
			}
			else
			{
				xLabel->setGeometry(20,0,width/2-20,20);
				yLabel->setGeometry(width/2+5,0,width/2-20,20);
				xLine->setGeometry(20,30,width/2-25,20);
				outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
				solveButton->setGeometry(width/2-105,height-40,100,30);
			}
			break;
		}
		case CALCZEROS:
		case CALCEXTRVAL:
		{
			xLabel->setGeometry(20,0,width/2-20,20);
			yLabel->setGeometry(width/2+5,0,width/2-20,20);
			outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
			functionBox->setGeometry(20,30,width/2-25,30);
			solveButton->setGeometry(width/2-105,height-40,100,30);
			break;
		}
		case CALCNEWTON:
		{
			
			xLabel->setGeometry(20,0,width/2-20,20);
			yLabel->setGeometry(width/2+5,0,width/2-20,20);
			outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
			functionBox->setGeometry(20,30,width/2-25,30);
			solveButton->setGeometry(width/2-105,height-30,100,30);
			x2Label->setGeometry(20,70,width/2-80,20);
			xLine->setGeometry(width/2-100,70,60,20);
			x3Label->setGeometry(20,100,width/2-80,20);
			spinBox->setGeometry(width/2-100,100,60,20);
			
			break;
		}
		case CALCXVAL:
		{
			if(functionType==GRAPH3D)
			{
				xLabel->setGeometry(20,0,width/2-20,20);
				yLabel->setGeometry(width/2+5,0,width/2-20,20);
				outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
				functionBox->setGeometry(20,30,width/2-25,30);	
				x2Label->setGeometry(20,70,width/2-80,20);
				xLine->setGeometry(width/2-100,70,90,20);	
				x3Label->setGeometry(20,100,width/2-80,20);
				x2Line->setGeometry(width/2-100,100,90,20);
				solveButton->setGeometry(width/2-105,height-30,100,30);
			}
			else {
				xLabel->setGeometry(20,0,width/2-20,20);
				yLabel->setGeometry(width/2+5,0,width/2-20,20);
				outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
				functionBox->setGeometry(20,30,width/2-25,30);
				solveButton->setGeometry(width/2-105,height-30,100,30);
				x2Label->setGeometry(20,70,width/2-25,20);
				xLine->setGeometry(20,100,width/2-25,20);
			}
			
			break;
		}
		case CALCCROSSP:
		{
			
			xLabel->setGeometry(20,0,width/2-20,20);
			yLabel->setGeometry(width/2+5,0,width/2-20,20);
			outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
			functionBox->setGeometry(20,25,width/2-25,30);
			solveButton->setGeometry(width/2-105,height-30,100,30);
			x2Label->setGeometry(20,65,width/2-25,20);
			functionBox2->setGeometry(20,90,width/2-25,30);

			
			break;
		}
		case CALCINTEGRAL:
		{
			xLabel->setGeometry(20,0,width/2-20,20);
			outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
			functionBox->setGeometry(20,30,width/2-25,30);	
			solveButton->setGeometry(width/2-105,height-30,100,30);
			if(functionType==GRAPH3D)
			{
				x2Label->setGeometry(30,70,50,20);
				xLine->setGeometry(90,70,(width/2-160)/2,20);
				x3Label->setGeometry((width/2-120)/2+90,70,50,20);
				x2Line->setGeometry((width/2-120)/2+130,70,(width/2-160)/2,20);
				
				x4Label->setGeometry(30,100,50,20);
				x3Line->setGeometry(90,100,(width/2-160)/2,20);
				yLabel->setGeometry((width/2-120)/2+90,100,50,20);
				x4Line->setGeometry((width/2-120)/2+130,100,(width/2-160)/2,20);


			}
			else
			{
				x2Label->setGeometry(20,70,width/2-80,20);
				xLine->setGeometry(width/2-100,70,90,20);	
				x3Label->setGeometry(20,100,width/2-80,20);
				x2Line->setGeometry(width/2-100,100,90,20);
			}
			break;
		}
		case CALCDIFF:
		{
			xLabel->setGeometry(20,0,width/2-20,20);
			yLabel->setGeometry(width/2+5,0,width/2-20,20);
			outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
			functionBox->setGeometry(20,30,width/2-25,30);
			solveButton->setGeometry(width/2-105,height-30,100,30);
			
			if(functionType==GRAPH3D)
			{
				x2Label->setGeometry(20,70,width/2-80,20);
				xLine->setGeometry(width/2-100,70,90,20);	
				x3Label->setGeometry(20,100,width/2-80,20);
				x2Line->setGeometry(width/2-100,100,90,20);
				
			}
			else {
				x2Label->setGeometry(20,70,width/2-25,20);
				xLine->setGeometry(20,100,width/2-25,20);
			}
			break;
		}
		case CALCZVAL:
		{
			xLabel->setGeometry(20,0,width/2-20,20);
			yLabel->setGeometry(width/2+5,0,width/2-20,20);
			outputTable->setGeometry(width/2+5,30,width/2-25,height-40);
			functionBox->setGeometry(20,30,width/2-25,30);	
			x2Label->setGeometry(20,70,width/2-80,20);
			xLine->setGeometry(width/2-100,70,90,20);	
			x3Label->setGeometry(20,100,width/2-80,20);
			x2Line->setGeometry(width/2-100,100,90,20);
			solveButton->setGeometry(width/2-105,height-30,100,30);
			break;
		}
		case GETSCREENSHOT:
		{
			x2Label->setGeometry(20,0,width/2-20,20);
			x3Label->setGeometry(30,30,20,20);
			spinBox->setGeometry(50,30,(width/2-120)/2,20);
			yLabel->setGeometry((width/2-120)/2+90,30,30,20);
			spinBox2->setGeometry((width/2-120)/2+110,30,(width/2-120)/2,20);
			formatLabel->setGeometry(20,60,100,30);
			formatBox->setGeometry(120,60,width/2-130,30);
			xLabel->setGeometry(20,100,60,20);
			xLine->setGeometry(80,100,width/2-115,20);
			openButton->setGeometry(width/2-30,100,20,20);
			saveButton->setGeometry(width/2-105,height-30,100,30);
			
			penLabel->setGeometry(width/2+10,20,60,30);
			spinBox3->setGeometry(width/2+70,20,100,30);
			colorButton->setGeometry(width/2+190,20,105,30);
			freeButton->setGeometry(width/2+10,75,30,30);
			lineButton->setGeometry(width/2+50,75,30,30);
			rectButton->setGeometry(width/2+90,75,30,30);
			circleButton->setGeometry(width/2+130,75,30,30);
			textButton->setGeometry(width/2+170,75,30,30);
			rubberButton->setGeometry(width/2+210,75,30,30);
			backButton->setGeometry(width/2+10,130,90,30);
			forwardButton->setGeometry(width/2+110,130,90,30);
			clearButton->setGeometry(width/2+210,130,85,30);
		}
	}
	if(aVisible && solveType!=GETSCREENSHOT)
	{
		aLabel->setGeometry(20,height-35,100,20);
		aLine->setGeometry(width/2-175,height-35,60,20);
	}
}



void GraphSolveWidget::resetDialog()
{
	xLine->setText("");
	x2Line->setText("");
	x3Line->setText("");
	x4Line->setText("");
	aLine->setText("");	
	xLine->hide();
	x2Line->hide();
	x3Line->hide();
	x4Line->hide();
	xLabel->hide();
	x2Label->hide();
	x3Label->hide();
	x4Label->hide();
	yLabel->hide();	
	outputTable->hide();
	solveButton->hide();
	functionBox->hide();
	functionBox2->hide();
	spinBox->hide();
	spinBox2->hide();
	spinBox3->hide();
	aLabel->hide();
	aLine->hide();
	formatBox->hide();
	formatLabel->hide();
	saveButton->hide();
	openButton->hide();
	backButton->hide();
	forwardButton->hide();
	clearButton->hide();
	freeButton->hide();
	rectButton->hide();
	lineButton->hide();
	circleButton->hide();
	rubberButton->hide();
	textButton->hide();
	colorButton->hide();
	penLabel->hide();
	emit drawSignal(DRAWNONE,paintColor,1);
	
	if(aVisible && solveType!=GETSCREENSHOT)
	{
		aLabel->show();
		aLine->show();
	}
	switch(solveType)
	{
		case CALCYVAL:
		{

			yLabel->setText(GRAPHSOLVEC_STR2);
			xLine->show();
			xLabel->show();
			yLabel->show();
			solveButton->show();
			outputTable->setNumRows(20);
			outputTable->show();
			if(functionType==GRAPHPARAMETER || functionType==GRAPHCOMPLEX)
			{
				outputTable->setNumCols(2);
				QStringList colLabels;
				
				functionBox->show();
				setFunctionBox(functionBox);
				xLabel->setText(GRAPHSOLVEC_STR3);

				if(functionType==GRAPHPARAMETER)
				{
					x2Label->setText(GRAPHSOLVEC_STR1);
					colLabels+="y";
					colLabels+="T";
				}
				else 
				{
					x2Label->setText(GRAPHSOLVEC_STR39);
					yLabel->setText(GRAPHSOLVEC_STR40);
					colLabels+="Im(Y)";
					colLabels+="Z";	
				}
				outputTable->setColumnLabels(colLabels);
				x2Label->show();
			}
			else if (functionType==GRAPHSTD || functionType==GRAPHPOLAR || functionType==GRAPHIEL)
			{
				outputTable->setNumCols(1);
				xLabel->setText(GRAPHSOLVEC_STR1);
				outputTable->setColumnLabels(QStringList("f(x)"));
			}
			else {
				outputTable->setNumCols(1);
				x2Label->show();
				functionBox->show();
				setFunctionBox(functionBox);
				x3Label->show();
				x2Line->show();
				xLabel->setText(GRAPHSOLVEC_STR3);
				x2Label->setText(GRAPHSOLVEC_STR20);
				x3Label->setText(GRAPHSOLVEC_STR22);
				outputTable->setColumnLabels(QStringList("y(x;z)"));
			}
			break;
		}
		case CALCEXTRVAL:
		{
			if(functionType==GRAPH3D)
			{
			}
			else {
				setFunctionBox(functionBox);
				xLabel->setText(GRAPHSOLVEC_STR3);
				yLabel->setText(GRAPHSOLVEC_STR18);
				xLabel->show();
				yLabel->show();
				functionBox->show();
				solveButton->show();
				outputTable->setNumCols(1);
				outputTable->setColumnLabels(QStringList("x"));
				outputTable->show();
			}
			break;
		}
		case CALCZEROS:
		{
			setFunctionBox(functionBox);
			xLabel->setText(GRAPHSOLVEC_STR3);
			yLabel->setText(GRAPHSOLVEC_STR4);
			xLabel->show();
			yLabel->show();
			functionBox->show();
			solveButton->show();
			outputTable->setNumCols(1);
			if(functionType==GRAPHPARAMETER|| functionType==GRAPHCOMPLEX)
			{
				outputTable->setNumCols(2);
				QStringList colLabels;
				if(functionType==GRAPHPARAMETER)
				{
					colLabels+="x";
					colLabels+="T";
				}
				else 
				{
					colLabels+="Re(Y)";
					colLabels+="Z";
				}
				outputTable->setColumnLabels(colLabels);
			}
			else outputTable->setColumnLabels(QStringList("x"));
			outputTable->show();
			break;
		}
		case CALCNEWTON:
		{
			setFunctionBox(functionBox);
			xLabel->setText(GRAPHSOLVEC_STR3);
			x2Label->setText(GRAPHSOLVEC_STR5);
			x3Label->setText(GRAPHSOLVEC_STR6);
			yLabel->setText(GRAPHSOLVEC_STR19);
			xLabel->show();
			x2Label->show();
			x3Label->show();
			yLabel->show();
			xLine->show();
			spinBox->setValue(5);
			spinBox->show();
			functionBox->show();
			solveButton->show();
			outputTable->setNumRows(spinBox->value());
			outputTable->setNumCols(3);
			QStringList labels("x1");
			labels+="f(x1)";
			labels+="f'(x1)";
			outputTable->setColumnLabels(labels);
//			outputTable->setColumnReadOnly(0,true);
//			outputTable->setColumnReadOnly(1,true);
//			outputTable->setColumnReadOnly(2,true);
			outputTable->show();
			break;
		}
		case CALCXVAL:
		{
			setFunctionBox(functionBox);
			xLabel->setText(GRAPHSOLVEC_STR3);
			xLabel->show();
			yLabel->show();
			yLabel->setText(GRAPHSOLVEC_STR7);
			x2Label->setText(GRAPHSOLVEC_STR8);
			x2Label->show();
			xLine->show();
			functionBox->show();
			solveButton->show();
			outputTable->setNumCols(1);
			if(functionType==GRAPHPARAMETER)
			{
				outputTable->setNumCols(2);
				QStringList colLabels;
				colLabels+="x";
				colLabels+="T";
				outputTable->setColumnLabels(colLabels);
			}
			else if(functionType==GRAPHCOMPLEX)
			{
			
				yLabel->setText(GRAPHSOLVEC_STR41);
				x2Label->setText(GRAPHSOLVEC_STR42);
				outputTable->setNumCols(2);
				QStringList colLabels;
				colLabels+="Re(Y)";
				colLabels+="Z";
				outputTable->setColumnLabels(colLabels);
			}				
			else if (functionType==GRAPH3D)
			{

				x3Label->show();
				x2Line->show();
				x2Label->setText(GRAPHSOLVEC_STR21);
				x3Label->setText(GRAPHSOLVEC_STR22);
				outputTable->setColumnLabels(QStringList("x"));

			}
			else outputTable->setColumnLabels(QStringList("x"));
			outputTable->show();
			
			break;
		}
		case CALCCROSSP:
		{
			setFunctionBox(functionBox);
			setFunctionBox(functionBox2);
			functionBox->show();
			functionBox2->show();
			solveButton->show();
			outputTable->setNumCols(1);
			outputTable->setNumRows(0);
			
//			outputTable->setColumnReadOnly(0,true);
			outputTable->setColumnLabels(QStringList("x"));
			outputTable->show();
			yLabel->setText(GRAPHSOLVEC_STR9);
			xLabel->setText(GRAPHSOLVEC_STR10);
			x2Label->setText(GRAPHSOLVEC_STR11);
			yLabel->show();
			xLabel->show();
			x2Label->show();
			break;
		}
		case CALCINTEGRAL:
		{
			
			setFunctionBox(functionBox);
			xLabel->setText(GRAPHSOLVEC_STR3);
			x2Label->setText(GRAPHSOLVEC_STR12);
			x3Label->setText(GRAPHSOLVEC_STR13);
			xLabel->show();
			x2Label->show();
			x3Label->show();
			xLine->show();
			x2Line->show();
			solveButton->show();
			functionBox->show();
			outputTable->setNumCols(1);
			outputTable->setNumRows(1);
			outputTable->setColumnLabels(QStringList("F(x)"));
			outputTable->show();
			if(functionType==GRAPH3D)
			{
				x3Line->show();
				x4Line->show();
				x4Label->setText(GRAPHSOLVEC_STR24);
				yLabel->setText(GRAPHSOLVEC_STR25);
				x2Label->setText(GRAPHSOLVEC_STR26);
				x3Label->setText(GRAPHSOLVEC_STR27);
				x4Label->show();
				yLabel->show();
				outputTable->setColumnLabels(QStringList("F(x,z)"));
			}
			
			break;
		}
		case CALCDIFF:
		{
			setFunctionBox(functionBox);
			xLabel->setText(GRAPHSOLVEC_STR3);
			xLabel->show();
			x2Label->show();
			xLine->show();
			functionBox->show();
			solveButton->show();
			outputTable->show();
			if(functionType==GRAPH3D)
			{
				QString delta(QChar((unsigned short)DIFFSTRING));
				outputTable->setNumCols(2);
				outputTable->setNumRows(1);
				QStringList colLabels;
				colLabels+=delta+"y/"+delta+"x";
				colLabels+=delta+"y/"+delta+"z";
				outputTable->setColumnLabels(colLabels);
				x3Label->show();
				x2Line->show();
				x2Label->setText(GRAPHSOLVEC_STR14);
				x3Label->setText(GRAPHSOLVEC_STR22);
			}
			else {
				if(functionType==GRAPHPARAMETER)
					x2Label->setText(GRAPHSOLVEC_STR23);
				else x2Label->setText(GRAPHSOLVEC_STR14);
				outputTable->setNumCols(1);
				outputTable->setNumRows(1);
				outputTable->setColumnLabels(QStringList("dy/dx"));
			}
			break;
		}
		case CALCZVAL:
		{
			
			setFunctionBox(functionBox);
			xLabel->setText(GRAPHSOLVEC_STR3);
			x2Label->setText(GRAPHSOLVEC_STR20);
			x3Label->setText(GRAPHSOLVEC_STR21);
			xLabel->show();
			x2Label->show();
			x3Label->show();
			xLine->show();
			x2Line->show();
			solveButton->show();
			functionBox->show();
			outputTable->setNumCols(1);
			outputTable->setNumRows(0);
			outputTable->setColumnLabels(QStringList("z"));
			outputTable->show();
			break;
		}
		case GETSCREENSHOT:
		{
			xLabel->setText(GRAPHSOLVEC_STR28);
			xLabel->show();
			xLine->setText(getenv("HOME")+QString("/screenshot.png"));
			xLine->show();
			x2Label->setText(GRAPHSOLVEC_STR29);
			x2Label->show();
			x3Label->setText("x");
			yLabel->setText("y");
			x3Label->show();
			yLabel->show();
			openButton->show();
			spinBox->setValue(TEXTURESIZE);
			spinBox->show();
			if(pref.autosize)
				spinBox2->setValue((int)((double)TEXTURESIZE*(pref.ymax-pref.ymin)/(pref.xmax-pref.xmin)));
			else spinBox2->setValue(TEXTURESIZE);
			spinBox2->show();
			spinBox3->show();
			formatLabel->setText(GRAPHSOLVEC_STR30);
			formatBox->clear();
			formatBox->insertItem(GRAPHSOLVEC_STR43);
			formatBox->insertItem("PNG");
			formatBox->insertItem("JPEG");
			formatBox->insertItem("BMP");
			formatBox->insertItem("XPM");
//			formatBox->insertItem("GIF");
			formatBox->show();
			formatLabel->show();
			saveButton->show();
			
			penLabel->show();
			backButton->show();
			forwardButton->show();
			clearButton->show();
			freeButton->show();
			rectButton->show();
			lineButton->show();
			circleButton->show();
			rubberButton->show();
			colorButton->show();
			textButton->show();
			
			freeButtonSlot();
			
			
			
			break;
		}
	}
	resizeEvent(NULL);
}




void GraphSolveWidget::calculateYVal(QString text)
{

	if(pref.functions == NULL || pref.activeFunctions == NULL)
		return;
	outputTable->setNumRows(0);
//	MessageBox("remove");
	double num=runCalc(text,&pref,vars);
	if(num != NAN && text.length()>0)
	{
		double oldX=vars[23][0];
		int count=0;
		for(int c=0; c<20; c++)
		{
			if(pref.functions[c].length() > 0 && pref.activeFunctions[c] &&
			(pref.functionTypes[c]==functionType || 
						(pref.functionTypes[c]==GRAPHIEG ||pref.functionTypes[c]==GRAPHIEL || pref.functionTypes[c]==GRAPHIEGE ||pref.functionTypes[c]==GRAPHIELE)&&functionType==GRAPHIEL))
			{
				char* checkedFunction=checkString(pref.functions[c],&pref);
				if(checkedFunction == NULL)
					return;
				if(strlen(checkedFunction)<=0)
					return;
				Calculate cal(NULL,checkedFunction,&pref,vars);
				delete[]checkedFunction;
				vars[23][0]=num;

				double y=cal.calc();
				QString result;
				outputTable->setNumRows(count+1);
				result=formatOutput(y,&pref);
				outputTable->verticalHeader()->setLabel(count,"y"+QString::number(c+1));
				outputTable->setText(count,0,result);
				outputTable->changeColor(count,pref.functionColors[c]);
				count++;
			}


		}
		vars[23][0]=oldX;
	}
	outputTable->adjustColumn(0);
}






int GraphSolveWidget::calculateRoots(QString function,long double startValue, long double endValue,long double**dResults,int varIndex=23,bool forceScript=false)
{
	if(endValue <= startValue || endValue==NAN || startValue==NAN)
		return -1;
	if(varIndex<0 || varIndex>25)
		return -1;
	if(pref.solvePrec>1)
		forceScript=true;
	
	
	long double scanPos=startValue;
	long double step=(endValue-startValue)/ANALYSESTEPS;
	long double exactStep=step/EXACTANALYSESTEPS;
	if(step<= 1e-15)
		step=1e-15;
	if(exactStep<= 1e-15)
		exactStep=1e-15;
	char*cf=checkString(function,&pref);
	QString cleanFunction(cf);
	delete[]cf;
	if(varIndex!=23)
	{
		cleanFunction.replace('X',"("+QString::number((double)vars[23][0],'g',pref.precision)+")");
		cleanFunction.replace((char)(varIndex+65),"X");
	}
	
	if(cleanFunction.length()<=0)
		return -1;
	char*modifiedFunction=(char*)cleanFunction.ascii();
	Calculate *cfx=NULL;
	Script*sfx=NULL;
	if(forceScript)
		sfx=new Script(NULL,modifiedFunction,&pref,vars,threadData);
	else cfx=new Calculate(NULL,modifiedFunction,&pref,vars);
	
	QString strdfx("d/dx("+function+"");
	cf=checkString(strdfx,&pref);
	cleanFunction=QString(cf);
	delete[]cf;
	if(varIndex!=23)
	{
		cleanFunction.replace('X',"("+QString::number((double)vars[23][0],'g',pref.precision)+")");
		cleanFunction.replace((char)(varIndex+65),"X");
	}
	cleanFunction+=",X)";
	if(cleanFunction.length()<=0)
		return -1;
	modifiedFunction=(char*)cleanFunction.ascii();
	
	Calculate *cdfx=NULL;
	Script*sdfx=NULL;
	if(forceScript)
		sdfx=new Script(NULL,modifiedFunction,&pref,vars,threadData);
	else cdfx=new Calculate(NULL,modifiedFunction,&pref,vars);
	List <long double> results;


	long double fx1,dfx1;
	if(forceScript)
	{
		threadData->vars[23][0].type=NFLOAT;
		threadData->vars[23][0].cfval=Complex(scanPos,0.0);
		fx1=sfx->exec().cfval.real();
		dfx1=sdfx->exec().cfval.real();
	}
	else
	{
		vars[23][0]=scanPos;
		fx1=cfx->calc();
		dfx1=cdfx->calc();
	}
	
	long double oldfx1=0,olddfx1=0;
	long double x1=0,nfx1=0,ndfx1=0;
	long double startPos=0,endPos=0;
	bool fail=false;
	
	while(scanPos<endValue)
	{
		if(x1==NAN)
			x1=scanPos;
		oldfx1=fx1;
		olddfx1=dfx1;
		scanPos+=step;
		if(forceScript)
		{
			
			threadData->vars[23][0].cfval=Complex(scanPos,0.0);
			fx1=sfx->exec().cfval.real();
			dfx1=sdfx->exec().cfval.real();
		}
		else {
			
			vars[23][0]=scanPos;
			fx1=cfx->calc();
			dfx1=cdfx->calc();
		}
		
		if(oldfx1*fx1 <= (double)0.0 || olddfx1*dfx1<= (double)0.0)
		{

			endPos=scanPos+exactStep;
			scanPos-=(step+exactStep);
			startPos=scanPos;
			if(forceScript)
			{
				threadData->vars[23][0].cfval=Complex(scanPos,0.0);
				fx1=sfx->exec().cfval.real();
				dfx1=sdfx->exec().cfval.real();
			}
			else {
				vars[23][0]=scanPos;
				fx1=cfx->calc();
				dfx1=cdfx->calc();
			}
			while(scanPos<endPos)
			{
				//perror("scanPos: "+QString::number((double)scanPos));
				oldfx1=fx1;
				olddfx1=dfx1;
				scanPos+=exactStep;
				if(forceScript)
				{
					threadData->vars[23][0].cfval=Complex(scanPos,0.0);
					fx1=sfx->exec().cfval.real();
					dfx1=sdfx->exec().cfval.real();
				}
				else {
					vars[23][0]=scanPos;
					fx1=cfx->calc();
					dfx1=cdfx->calc();
				}
				if(olddfx1*dfx1<= (double)0.0)			//Newton; for double-roots
				{
					fail=false;
					x1=scanPos;
					for(int c=0; c<EXACTANALYSESTEPS; c++)
					{
						if(forceScript)
						{
							threadData->vars[23][0].cfval=Complex(x1,0.0);
							nfx1=sfx->exec().cfval.real();
							ndfx1=sdfx->exec().cfval.real();
						}
						else {
							vars[23][0]=x1;
							nfx1=cfx->calc();
							ndfx1=cdfx->calc();
						}
						//perror("x1 "+QString::number((double)x1)+" nfx1 "+QString::number((double)nfx1)+" ndfx1 "+QString::number((double)ndfx1));
						if(nfx1<1e-30 && nfx1>-1e-30)
							break;
						if(ndfx1<1e-50 && ndfx1>-1e-50)
						{
							fail=true;
							break;
						}
						x1=x1-(nfx1/(ndfx1));
					}
					if(!fail)
					{
						if(x1>=scanPos-exactStep &&x1<=scanPos)
						{
							results.NewItem(x1);
							if(results.GetLen() > 50)
							{
								scanPos=endValue+1.0;
								break;
							}
						}
					}
				}
				else if(oldfx1*fx1 <= 0.0)			//Regula falsi; for normal roots
				{
					endPos=scanPos+exactStep;
					scanPos-=(step+exactStep);
					startPos=scanPos;
					long double rfXEnd=endPos,rfXStart=startPos;
					long double rfYEnd,rfYStart;
					int c=0;
					while(true)
					{
						c++;
						if(forceScript)
						{
							threadData->vars[23][0].cfval=Complex(rfXStart,0.0);
							rfYStart=sfx->exec().cfval.real();
							threadData->vars[23][0].cfval=Complex(rfXEnd,0.0);
							rfYEnd=sfx->exec().cfval.real();
						}
						else {
							vars[23][0]=rfXStart;
							rfYStart=cfx->calc();
							vars[23][0]=rfXEnd;
							rfYEnd=cfx->calc();
						}
						x1=rfXEnd-rfYEnd*(rfXEnd-rfXStart)/(rfYEnd-rfYStart);
						
						if(forceScript)
						{
							threadData->vars[23][0].cfval=Complex(x1,0.0);
							fx1=sfx->exec().cfval.real();
						}
						else {
							vars[23][0]=x1;
							fx1=cfx->calc();
						}
						
						if(fx1*rfYEnd < (double)0.0)
							rfXStart=x1;
						else if(fx1*rfYStart < (double)0.0)
							rfXEnd=x1;
						
						if((fx1>-1e-14 && fx1<1e-14) || c>EXACTANALYSESTEPS)
						{
							results.NewItem(x1);
							scanPos=endPos;
							if(results.GetLen() > 50)
							{
								scanPos=endValue+1.0;
								break;
							}
							
							if(forceScript)
							{
								threadData->vars[23][0].cfval=Complex(scanPos,0.0);
								fx1=sfx->exec().cfval.real();
								dfx1=sdfx->exec().cfval.real();
							}
							else {
								vars[23][0]=scanPos;
								fx1=cfx->calc();
								dfx1=cdfx->calc();
							}
							break;
						}
					}
				}
			}
		}
	}
	if(results.GetLen()<=0)
		return 0;
	(*dResults)=new long double[results.GetLen()];
	for(int c=0; c<results.GetLen(); c++)
		(*dResults)[c]=results[c];
	
	return results.GetLen();
}

void GraphSolveWidget::showRoots(QString function,QColor color)
{
	emit removeLines();
	
	long double*results;
	int numResults;
	if(functionType==GRAPHPOLAR)
		numResults=calculateRoots(function,0.0, pref.angleMax,&results);
	else numResults=calculateRoots(function,pref.xmin, pref.xmax,&results);
	
	if(numResults <=0)
		return;
	
	outputTable->setNumRows(numResults);

	for(int c=0; c<numResults; c++)
	{
		QString result;
		if(pref.outputType==FIXEDNUM)
			result=QString::number(results[c],'e',pref.outputLength);
		else result=QString::number(results[c],'g',pref.outputLength);
		if(pref.graphType==GRAPHPOLAR)
			emit addPolarLine(results[c]);
		else emit addVerticalLine(results[c]);

		outputTable->setText(c,0,result);
		outputTable->changeColor(c,color);
	}
	delete[]results;

	outputTable->adjustColumn(0);
	
	//Error message for too many results (for example f(x): y=0)
	if(numResults>50)
		MessageBox(GRAPHPREFC_STR6);
}




void GraphSolveWidget::calculateNewton(QString function)
{

	emit removeLines();
	outputTable->setNumRows(spinBox->value());
	double x1=runCalc(xLine->text(),&pref,vars),fx1=0,dfx1=0;
	if(x1==NAN)
		x1=0.0;
	char* cleanFunction=checkString(function,&pref);
	if(cleanFunction == NULL)
		return;
	if(strlen(cleanFunction)<=0)
		return;
	Calculate cfx(NULL,cleanFunction,&pref,vars);
	QString strdfx("d/dx("+QString(cleanFunction)+",X)");
	cleanFunction=checkString(strdfx,&pref);
	if(cleanFunction == NULL)
		return;
	if(strlen(cleanFunction)<=0)
		return;
	Calculate cdfx(NULL,cleanFunction,&pref,vars);

	for(int c=0; c<spinBox->value(); c++)
	{
		outputTable->setText(c,0,formatOutput(x1,&pref));
		vars[23][0]=x1;
		fx1=cfx.calc();
		outputTable->setText(c,1,formatOutput(fx1,&pref));
		dfx1=cdfx.calc();
		outputTable->setText(c,2,formatOutput(dfx1,&pref));
		x1=x1-(fx1/dfx1);
		outputTable->changeColor(c,QColor(0,0,0));
	}
	if(pref.graphType==GRAPHPOLAR)
		emit addPolarLine(x1);
	else emit addVerticalLine(x1);
	outputTable->adjustColumn(0);
	delete[]cleanFunction;
}

void GraphSolveWidget::setFunctionBox(QComboBox*fBox)
{

	QString actualFunction=fBox->currentText();
	fBox->clear();
	
	
	if(pref.functions != NULL && pref.activeFunctions != NULL)
	{
		int functionCount=0;
		for(int c=0; c<20; c++)
		{
			if(pref.activeFunctions[c] && (pref.functionTypes[c] == functionType || pref.functionTypes[c]==GRAPHCOMP3D && functionType==GRAPHCOMPLEX ||
			functionType==GRAPHIEL && (pref.functionTypes[c] == GRAPHIEG ||
						pref.functionTypes[c] == GRAPHIEGE ||
						pref.functionTypes[c] == GRAPHIELE)))
			{
				functionIndices[functionCount]=c;
				functionCount++;
				fBox->insertItem("f"+QString::number(c+1)+": "+pref.functions[c],-1);
			}
		}
	}
	if(actualFunction.length() >0)
	{
		for(int c=0; c<fBox->count(); c++)
		{
			if(fBox->text(c) == actualFunction)
			{
				fBox->setCurrentItem(c);
				break;
			}
		}
	}
}

void GraphSolveWidget::solveButtonSlot()
{
	if(aVisible)
	{
		long double A=runCalc(aLine->text(),&pref,vars);
		if(A==NAN)
			A=0;
		vars[0][0]=A;
	}
	switch(solveType)
	{
		case CALCYVAL:
		{
			emit removeLines();
			switch(functionType)
			{
				case GRAPHSTD:
				case GRAPHPOLAR:
				case GRAPHIEL:
				{
					calculateYVal(xLine->text());
					double xVal=runCalc(xLine->text(),&pref,vars);
					if(xVal != NAN)
					{
						if(functionType==GRAPHPOLAR)
							emit addPolarLine(xVal);
						else emit addVerticalLine(xVal);
					}
					break;
				}
				case GRAPHPARAMETER:
				case GRAPHCOMPLEX:
				{
					double xVal=runCalc(xLine->text(),&pref,vars);
					if(xVal!=NAN)
					{
						
						
						if(functionBox->currentItem()<0)
							break;
						int funcIndex=functionIndices[functionBox->currentItem()];
						QString xFunction;
						if(solveType==GRAPHPARAMETER)
						{
							xFunction=pref.functions[funcIndex].left(pref.functions[funcIndex].find("\\"));
							xFunction.replace('T',"X");
							xFunction+="-";
							xFunction+=QString::number(xVal,'g',pref.precision);
						}
						else {
							xFunction="real("+pref.functions[funcIndex]+")-";
							xFunction+=QString::number(xVal,'g',pref.precision);
						}
						long double*tValues;
						int numTValues;
						if(solveType==GRAPHPARAMETER)
						{
							numTValues=calculateRoots(xFunction,pref.parameterStart,pref.parameterEnd,&tValues);
							emit addVerticalLine(xVal);
						}
						else 
						{
							if(pref.functionTypes[funcIndex]==GRAPHCOMP3D)
								numTValues=calculateRoots(xFunction,pref.zmin,pref.zmax,&tValues,25,true);
							else {
								emit addVerticalLine(xVal);
								if(pref.logNyquistSteps)
									numTValues=calculateRoots(xFunction,pow(10,pref.nyquistStart),pow(10,pref.nyquistEnd),&tValues,25,true);
								else numTValues=calculateRoots(xFunction,pref.nyquistStart,pref.nyquistEnd,&tValues,25,true);
							}
						}
						long double*yValues;
						if(numTValues>0)
							yValues=new long double[numTValues];
						else {
							outputTable->setNumRows(0);
							break;
						}
						
						outputTable->setNumCols(2);
						outputTable->setNumRows(numTValues);
												
						QString yFunction;
						Calculate*cyf=NULL;
						Script*syf=NULL;
						if(solveType == GRAPHPARAMETER)
						{
							yFunction=pref.functions[funcIndex].right(pref.functions[funcIndex].length()-1-pref.functions[funcIndex].find("\\"));
							char*cleanFunc=checkString(yFunction,&pref);
							cyf=new Calculate(NULL,cleanFunc,&pref,vars);
						}
						else {
							yFunction="imag("+pref.functions[funcIndex]+")";
							char*cleanFunc=checkString(yFunction,&pref);
							syf=new Script(NULL,cleanFunc,&pref,vars,threadData);
							threadData->vars[25][0].type=NFLOAT;
						}
						
						
						
						for(int c=0; c<numTValues; c++)
						{
							if(solveType==GRAPHPARAMETER)
							{
								vars[19][0]=tValues[c];
								yValues[c]=cyf->calc();
								emit addHorizontalLine(yValues[c]);
							}
							else {
								threadData->vars[25][0].cfval=Complex(tValues[c]);
								yValues[c]=syf->exec().cfval.real();
								if(pref.functionTypes[funcIndex]==GRAPHCOMP3D)
								{
									emit add3dXLine(yValues[c],tValues[c]);
									emit add3dYLine(xVal,tValues[c]);
									emit add3dZLine(xVal,yValues[c]);
								}
								else emit addHorizontalLine(yValues[c]);
							}
							
							
							QString yString,tString;
							yString=formatOutput(yValues[c],&pref);
							tString=formatOutput(tValues[c],&pref);
							
							outputTable->setText(c,0,yString);
							outputTable->setText(c,1,tString);
							outputTable->changeColor(c,pref.functionColors[funcIndex]);
						}
						outputTable->adjustColumn(0);
						outputTable->adjustColumn(1);
						delete[]tValues;
						delete[]yValues;
					}
					break;
				}
				case GRAPH3D:
				{
					emit removeLines();
					if(functionBox->currentItem()<0)
						break;
					int funcIndex=functionIndices[functionBox->currentItem()];
					double xVal=runCalc(xLine->text(),&pref,vars);
					double zVal=runCalc(x2Line->text(),&pref,vars);
					
					vars[23][0]=xVal;
					vars[25][0]=zVal;
					double result=runCalc(pref.functions[funcIndex],&pref,vars);
					QString yString;
					if(pref.outputType==FIXEDNUM)
						yString=QString::number(result,'e',pref.outputLength);
					else yString=QString::number(result,'g',pref.outputLength);

					outputTable->setText(0,0,yString);
					outputTable->changeColor(0,pref.functionColors[funcIndex]);
					emit add3dXLine(result,zVal);
					emit add3dYLine(xVal,zVal);
					emit add3dZLine(xVal,result);
					outputTable->adjustColumn(0);
					break;
				}
			}
			break;
		}
		case CALCNEWTON:
		{
			if(functionBox->currentItem()<0)
				break;
			QString functionString=pref.functions[functionIndices[functionBox->currentItem()]];
			calculateNewton(functionString);
			break;
		}
		case CALCZEROS:
		case CALCXVAL:
		{
			outputTable->setNumRows(0);
			emit removeLines();
			double yval;
			if(solveType==CALCXVAL)
			{
				yval=runCalc(xLine->text(),&pref,vars);
				if(yval == NAN)
					yval=0.0f;
			}
			else yval=0;
			switch(functionType)
			{
				case GRAPHSTD:
				case GRAPHPOLAR:
				case GRAPHIEL:
				{
			
					if(functionBox->currentItem()<0)
						break;
					int funcIndex=functionIndices[functionBox->currentItem()];
					QString functionString=pref.functions[funcIndex];
					functionString+="-";
					functionString+=QString::number(yval,'g',pref.precision);
					if(funcIndex>=0 && funcIndex<20)
						showRoots(functionString,pref.functionColors[funcIndex]);
					else showRoots(functionString,QColor(0,0,0));
					if(functionType==GRAPHPOLAR)
						emit addCircle(yval);
					else emit addHorizontalLine(yval);
					break;
				}
				case GRAPHPARAMETER:
				case GRAPHCOMPLEX:
				{
					if(yval!=NAN)
					{
					
						if(functionBox->currentItem()<0)
							break;
						int funcIndex=functionIndices[functionBox->currentItem()];
						QString yFunction=pref.functions[funcIndex].right(pref.functions[funcIndex].length()-1-pref.functions[funcIndex].find("\\"));
						
						long double*tValues;
						int numTValues;
						if(solveType==GRAPHPARAMETER)
						{
							yFunction.replace('T',"X");
							yFunction+="-";
							yFunction+=QString::number(yval,'g',pref.precision);
							numTValues=calculateRoots(yFunction,pref.parameterStart,pref.parameterEnd,&tValues);
							emit addHorizontalLine(yval);
						}
						else {
							yFunction="imag("+pref.functions[funcIndex]+")-";
							yFunction+=QString::number(yval,'g',pref.precision);
							
							if(pref.functionTypes[funcIndex]==GRAPHCOMP3D)
								numTValues=calculateRoots(yFunction,pref.zmin,pref.zmax,&tValues,25,true);
							else {
								emit addHorizontalLine(yval);
								if(pref.logNyquistSteps)
									numTValues=calculateRoots(yFunction,pow(10,pref.nyquistStart),pow(10,pref.nyquistEnd),&tValues,25,true);
								else numTValues=calculateRoots(yFunction,pref.nyquistStart,pref.nyquistEnd,&tValues,25,true);
							}
						}
						
						long double*xValues;
						if(numTValues>0)
							xValues=new long double[numTValues];
						else {
							outputTable->setNumRows(0);
							break;
						}
						
						Calculate *cxf=NULL;
						Script* sxf=NULL;
						if(solveType==GRAPHPARAMETER)
						{
							QString xFunction=pref.functions[funcIndex].left(pref.functions[funcIndex].find("\\"));
							char*cleanFunc=checkString(xFunction,&pref);
							cxf=new Calculate(NULL,cleanFunc,&pref,vars);
						}
						else {
							yFunction="real("+pref.functions[funcIndex]+")";
							char*cleanFunc=checkString(yFunction,&pref);
							sxf=new Script(NULL,cleanFunc,&pref,vars,threadData);
							threadData->vars[25][0].type=NFLOAT;
						}

						outputTable->setNumCols(2);
						outputTable->setNumRows(numTValues);


						for(int c=0; c<numTValues; c++)
						{
							if(solveType==GRAPHPARAMETER)
							{
								vars[19][0]=tValues[c];
								xValues[c]=cxf->calc();
								emit addVerticalLine(xValues[c]);
							}
							else {
								threadData->vars[25][0].cfval=Complex(tValues[c]);
								xValues[c]=sxf->exec().cfval.real();
								
								if(pref.functionTypes[funcIndex]==GRAPHCOMP3D)
								{
									emit add3dXLine(yval,tValues[c]);
									emit add3dYLine(xValues[c],tValues[c]);
									emit add3dZLine(xValues[c],yval);
								}
								else emit addVerticalLine(xValues[c]);
							}

							QString xString,tString;
							xString=formatOutput(xValues[c],&pref);
							tString=formatOutput(tValues[c],&pref);

							
							outputTable->setText(c,0,xString);
							outputTable->setText(c,1,tString);
							outputTable->changeColor(c,pref.functionColors[funcIndex]);
						}
						outputTable->adjustColumn(0);
						outputTable->adjustColumn(1);
						delete[]tValues;
						delete[]xValues;
					}
					break;
				}
				case GRAPH3D:
				{
					if(functionBox->currentItem()<0)
						break;
					int funcIndex=functionIndices[functionBox->currentItem()];
	
					double zVal=runCalc(x2Line->text(),&pref,vars);
					emit add3dXLine(yval,zVal);
			
					QString function=pref.functions[funcIndex];
					function+="-("+QString::number(yval,'g',pref.precision)+")";
					vars[25][0]=zVal;
			
					long double*xValues;
					int num=calculateRoots(function,pref.xmin,pref.xmax,&xValues);
					if(num<=0)
						break;
					QString xString;
					outputTable->setNumRows(num);
					for(int c=0; c<num; c++)
					{
						if(pref.outputType==FIXEDNUM)
							xString=QString::number(xValues[c],'e',pref.outputLength);
						else xString=QString::number(xValues[c],'g',pref.outputLength);
						outputTable->setText(c,0,xString);
						emit add3dYLine(xValues[c],zVal);
						emit add3dZLine(xValues[c],yval);
					}
					outputTable->adjustColumn(0);
					delete[]xValues;
					break;
				}
				
			}
			break;
		}
		case CALCCROSSP:
		{
			if(functionBox->currentText() == functionBox2->currentText())
			{
				MessageBox(GRAPHPREFC_STR5);
				break;
			}
			if(functionType!=GRAPHIEL)
			{
				if(functionBox->currentItem()<0 || functionBox2->currentItem()<0)
					break;
				QString functionString=pref.functions[functionIndices[functionBox->currentItem()]];
				functionString+="-(";
				functionString+=pref.functions[functionIndices[functionBox2->currentItem()]];
				functionString+=")";
				showRoots(functionString,QColor(0,0,0));
			}
			else {
				emit drawInequaityIntersection(functionIndices[functionBox->currentItem()],functionIndices[functionBox2->currentItem()]);
				emit redrawGraphs();
			}
			break;
		}
		case CALCINTEGRAL:
		{
			if(functionBox->currentItem()<0)
				break;
			QString functionString=getUnicode(INTEGRALSTRING);
			functionString+="(";
			functionString+=pref.functions[functionIndices[functionBox->currentItem()]];
			functionString+=",";
			double start=runCalc(xLine->text(),&pref,vars);
			if(start == NAN)
			{
				MessageBox(GRAPHSOLVEC_STR15);
				break;
			}
			double end=runCalc(x2Line->text(),&pref,vars);
			if(end == NAN)
			{
				MessageBox(GRAPHSOLVEC_STR16);
				break;
			}
			functionString+=QString::number(start,'g',pref.precision);
			functionString+=",";
			functionString+=QString::number(end,'g',pref.precision);
			functionString+=")";
			char*cleanFunc=checkString(functionString,&pref);
			if(cleanFunc == NULL)
				return;
			emit removeLines();
			
			double result=0.0;
			if(functionType==GRAPH3D)
			{
				double zStart=runCalc(x3Line->text(),&pref,vars);
				double zEnd=runCalc(x4Line->text(),&pref,vars);
				if(zStart==NAN || zEnd==NAN)
					break;
				double zStep=(zEnd-zStart)/INTEGRAL3DSTEPS;
				zStart+=zStep/2.0;
				Calculate ca(NULL,cleanFunc,&pref,vars);
				for(int c=0; c<INTEGRAL3DSTEPS; c++)
				{
					vars[25][0]=zStart+c*zStep;
					result+=ca.calc()*zStep;
				}
				emit add3dYLine(start,zStart);
				emit add3dYLine(start,zEnd);
				emit add3dYLine(end,zStart);
				emit add3dYLine(end,zEnd);
				
			}
			else 
			{
				result=runCalc(functionString,&pref,vars);
			}
			delete[]cleanFunc;
			
			if(functionType==GRAPHPOLAR)
			{
				emit addPolarLine(start);
				emit addPolarLine(end);
				
			}
			else if(functionType!=GRAPH3D)
			{
				emit addVerticalLine(start);
				emit addVerticalLine(end);
				
			}
			
			
			outputTable->setText(0,0,formatOutput(result,&pref));
			if(functionIndices[functionBox->currentItem()]>=0 && functionIndices[functionBox->currentItem()]<20)
				outputTable->changeColor(0,pref.functionColors[functionIndices[functionBox->currentItem()]]);
			outputTable->adjustColumn(0);
			break;
		}
		case CALCDIFF:
		{
			if(functionBox->currentItem()<0)
				break;
			int funcIndex=functionIndices[functionBox->currentItem()];
			double pos=runCalc(xLine->text(),&pref,vars);
			if(pos == NAN)
			{
				MessageBox(GRAPHSOLVEC_STR17);
				break;
			}
			if(functionType==GRAPHPARAMETER)
			{
				QString xFunction,yFunction;
				xFunction=pref.functions[funcIndex].left(pref.functions[funcIndex].find("\\"));
				yFunction=pref.functions[funcIndex].right(pref.functions[funcIndex].length()-1-pref.functions[funcIndex].find("\\"));
				xFunction.replace('T',"X");
				yFunction.replace('T',"X");
				vars[23][0]=pos;
				double xPos=runCalc(xFunction,&pref,vars);
				double yPos=runCalc(yFunction,&pref,vars);
				xFunction="d/dx("+xFunction+","+QString::number(pos,'g',pref.precision)+")";
				yFunction="d/dx("+yFunction+","+QString::number(pos,'g',pref.precision)+")";
				double xDiff=runCalc(xFunction,&pref,vars);
				double yDiff=runCalc(yFunction,&pref,vars);
				emit removeLines();
				emit addVerticalLine(xPos);
				emit addHorizontalLine(yPos);
				if(funcIndex>=0 && funcIndex<20)
					outputTable->changeColor(0,pref.functionColors[funcIndex]);
				outputTable->setText(0,0,formatOutput(yDiff/xDiff,&pref));
			}
			else if(functionType==GRAPH3D)
			{
				double zVal=runCalc(x2Line->text(),&pref,vars);
				if(zVal==NAN)
					break;
				emit removeLines();
				emit add3dYLine(pos,zVal);
				
				vars[25][0]=zVal;
				QString functionString="d/dx("+pref.functions[funcIndex]+","+QString::number(pos,'g',pref.precision)+")";
				double result=runCalc(functionString,&pref,vars);
				outputTable->setText(0,0,formatOutput(result,&pref));
				functionString=pref.functions[funcIndex];
				for(int c=0; c<(signed)functionString.length(); c++)
					if(functionString[c]=='x')
						if(!(c>2 && functionString.mid(c-3,4)=="d/dx"))
							functionString[c]='X';
				functionString.replace("X","("+QString::number(pos,'g',pref.precision)+")");
				functionString.replace("z","X");
				functionString.replace("Z","X");
				functionString="d/dx("+functionString+","+QString::number(zVal,'g',pref.precision)+")";
				result=runCalc(functionString,&pref,vars);
				outputTable->setText(0,1,formatOutput(result,&pref));
			}
			else {
				QString functionString="d/dx("+pref.functions[funcIndex]+","+QString::number(pos,'g',pref.precision)+")";
				double result=runCalc(functionString,&pref,vars);
				emit removeLines();
				if(functionType==GRAPHPOLAR)
					emit addPolarLine(pos);
				else emit addVerticalLine(pos);
				outputTable->setText(0,0,formatOutput(result,&pref));
			}
			if(funcIndex>=0 && funcIndex<20)
				outputTable->changeColor(0,pref.functionColors[funcIndex]);
			outputTable->adjustColumn(0);
			break;
		}
		case CALCEXTRVAL:
		{
			if(functionBox->currentItem()<0)
				break;
			int funcIndex=functionIndices[functionBox->currentItem()];
			QString functionString=pref.functions[funcIndex];
			if(funcIndex>=0 && funcIndex<20)
				showRoots("d/dx("+functionString+",X)",pref.functionColors[funcIndex]);
			else showRoots("d/dx("+functionString+",X)",QColor(0,0,0));
			outputTable->adjustColumn(0);
			break;
		}
		case CALCZVAL:
		{
			outputTable->setNumRows(0);
			emit removeLines();
			if(functionBox->currentItem()<0)
				break;
			int funcIndex=functionIndices[functionBox->currentItem()];
			
			double xVal=runCalc(xLine->text(),&pref,vars);
			double yVal=runCalc(x2Line->text(),&pref,vars);
			emit add3dZLine(xVal,yVal);
			
			QString function=pref.functions[funcIndex];
			vars[23][0]=xVal;
			function+="-("+QString::number(yVal,'g',pref.precision)+")";
			
			
			long double*zValues;
			int num=calculateRoots(function,pref.zmin,pref.zmax,&zValues,25);
			if(num<=0)
				break;
			QString zString;
			outputTable->setNumRows(num);
			for(int c=0; c<num; c++)
			{
				if(pref.outputType==FIXEDNUM)
					zString=QString::number(zValues[c],'e',pref.outputLength);
				else zString=QString::number(zValues[c],'g',pref.outputLength);
				outputTable->setText(c,0,zString);
				emit add3dXLine(yVal,zValues[c]);
				emit add3dYLine(xVal,zValues[c]);
			}
			outputTable->adjustColumn(0);
			delete[]zValues;
			break;
		}
		case GETSCREENSHOT:
		{
			emit getScreenshotSignal(spinBox->value(),spinBox2->value());
		}
	}
}

void GraphSolveWidget::screenshotSlot(QPixmap*scr)
{
	struct stat fileInfo;
	if(xLine->text().length() <=0)
	{
		ErrorBox(GRAPHSOLVEC_STR31);
		return;
	}
	if(lstat(xLine->text(),&fileInfo) == 0)
	{
		if(S_ISREG(fileInfo.st_mode))
		{
			if(YesNoCancelBox(GRAPHSOLVEC_STR32+xLine->text()+" ?")!=0)
				return;
		}
		else 
		{
			ErrorBox(xLine->text()+GRAPHSOLVEC_STR33);
			return;
		}
	}
	QString format;
	if(formatBox->currentText() == GRAPHSOLVEC_STR43)
	{
		format= xLine->text().right(3).upper();
		if(format=="JPG" ||  xLine->text().right(4).upper()=="JPEG")
			format=QString("JPEG");
		else if(format!="PNG" && format!="BMP" && format!="XPM")
		{
			WarningBox(GRAPHSOLVEC_STR44);
			format=QString("PNG");
		}
	}
	else format=formatBox->currentText();
	if(scr->save(xLine->text(),format))
		MessageBox(GRAPHSOLVEC_STR34);
	else ErrorBox(GRAPHSOLVEC_STR35);
}

void GraphSolveWidget::openButtonSlot()
{
	QString path=QFileDialog::getSaveFileName(".",GRAPHSOLVEC_STR36,this,
											  "save dialog",GRAPHSOLVEC_STR37);
	xLine->setText(path);
}


void GraphSolveWidget::colorButtonSlot()
{
	if(paintColor.red()==4 &&paintColor.green()==4 &&paintColor.blue()==4)
		paintColor.setRgb(0,0,0);
	QColor col=QColorDialog::getColor(paintColor,this,GRAPHSOLVEC_STR38);
	paintColor=col;
	colorIcon->fill(paintColor);
	colorButton->setIconSet(*colorIcon);
	if(paintColor.red()<4 &&paintColor.green()<4 &&paintColor.blue()<4)
		paintColor.setRgb(4,4,4);
	if(drawState==DRAWTEXT)
		return;
	emit drawSignal(drawState,paintColor,spinBox3->value());
}

void GraphSolveWidget::penValueSlot(int value)
{
	if(drawState==DRAWTEXT)
		return;
	if(rubberButton->isOn())
		emit drawSignal(drawState,QColor(0,0,0),value);
	else emit drawSignal(drawState,paintColor,value);
}

void GraphSolveWidget::forwardButtonSlot()
{
//	drawState=DRAWFORWARD;
	emit drawSignal(DRAWFORWARD,paintColor,spinBox3->value());
}
void GraphSolveWidget::backButtonSlot()
{
//	drawState=DRAWBACK;
	emit drawSignal(DRAWBACK,paintColor,spinBox3->value());
}
void GraphSolveWidget::clearButtonSlot()
{
//	drawState=DRAWCLEAR;
	emit drawSignal(DRAWCLEAR,paintColor,spinBox3->value());
}
void GraphSolveWidget::freeButtonSlot()
{
	drawState=DRAWFREE;
	freeButton->setOn(true);
	lineButton->setOn(false);
	rectButton->setOn(false);
	circleButton->setOn(false);
	rubberButton->setOn(false);
	colorButton->setEnabled(true);
	textButton->setOn(false);
	emit drawSignal(DRAWFREE,paintColor,spinBox3->value());
}
void GraphSolveWidget::lineButtonSlot()
{
	drawState=DRAWLINE;
	freeButton->setOn(false);
	lineButton->setOn(true);
	rectButton->setOn(false);
	circleButton->setOn(false);
	rubberButton->setOn(false);
	colorButton->setEnabled(true);
	textButton->setOn(false);
	emit drawSignal(DRAWLINE,paintColor,spinBox3->value());
}
void GraphSolveWidget::rectButtonSlot()
{
	drawState=DRAWRECT;
	freeButton->setOn(false);
	lineButton->setOn(false);
	rectButton->setOn(true);
	circleButton->setOn(false);
	rubberButton->setOn(false);
	colorButton->setEnabled(true);
	textButton->setOn(false);
	emit drawSignal(DRAWRECT,paintColor,spinBox3->value());
}
void GraphSolveWidget::circleButtonSlot()
{
	drawState=DRAWCIRCLE;
	freeButton->setOn(false);
	lineButton->setOn(false);
	rectButton->setOn(false);
	circleButton->setOn(true);
	rubberButton->setOn(false);
	colorButton->setEnabled(true);
	textButton->setOn(false);
	emit drawSignal(DRAWCIRCLE,paintColor,spinBox3->value());
}
void GraphSolveWidget::rubberButtonSlot()
{
	drawState=DRAWFREE;
	freeButton->setOn(false);
	lineButton->setOn(false);
	rectButton->setOn(false);
	circleButton->setOn(false);
	rubberButton->setOn(true);
	colorButton->setEnabled(false);
	textButton->setOn(false);
	emit drawSignal(DRAWFREE,QColor(0,0,0),8);
}

void GraphSolveWidget::textButtonSlot()
{
	drawState=DRAWTEXT;
	freeButton->setOn(false);
	lineButton->setOn(false);
	rectButton->setOn(false);
	circleButton->setOn(false);
	rubberButton->setOn(false);
	colorButton->setEnabled(true);
	textButton->setOn(true);
	emit drawSignal(DRAWTEXT,paintColor,spinBox3->value());
}

void GraphSolveWidget::setPref(Preferences newPref)
{
	pref=newPref;


//	setFunctionBox(functionBox);
//	setFunctionBox(functionBox2);
	
	aVisible=false;
	
	for(int c=0; c<20; c++)
	{
		if(pref.activeFunctions!=NULL && pref.functionTypes!=NULL && pref.dynamicFunctions!=NULL)
		{	 
			if(pref.activeFunctions[c] && 
					(functionType == pref.functionTypes[c] ||
					functionType==GRAPHIEL && (pref.functionTypes[c]==GRAPHIEG ||pref.functionTypes[c]==GRAPHIELE ||pref.functionTypes[c]==GRAPHIEGE))
					&& pref.dynamicFunctions[c])
			{
				aVisible=true;
				aLine->show();
				aLabel->show();
				resizeEvent(NULL);
				break;
			}
		}
	}
	if(!aVisible)
	{
		aLine->hide();
		aLabel->hide();
		resizeEvent(NULL);
	}
//	if(isShown())
//		resetDialog();
	if(functionBox->isShown())
		setFunctionBox(functionBox);
	if(functionBox2->isShown())
		setFunctionBox(functionBox2);
//	solveButtonSlot();
	
}


void GraphSolveWidget::graphLMButtonPressed(double x,double y)
{
	switch(solveType)
	{
		case CALCDIFF:
			if(functionType==GRAPHPARAMETER)
			{
				emit removeLines();
				break;
			}
		case CALCYVAL:
		case CALCNEWTON:
		{
			emit removeLines();
			xLine->setText(QString::number(x,'g',10));
			if(functionType==GRAPHPOLAR)
				emit addPolarLine(x);
			else emit addVerticalLine(x);
			break;
		}
		case CALCINTEGRAL:
		{
			emit removeLines();
			static bool firstLine=true;
			if(firstLine)
			{
				xLine->setText(QString::number(x,'g',10));
				if(functionType==GRAPHPOLAR)
					emit addPolarLine(x);
				else emit addVerticalLine(x);
				double x2Val=runCalc(x2Line->text(),&pref,vars);
				if(x2Val != NAN)
				{
					if(functionType==GRAPHPOLAR)
						emit addPolarLine(x2Val);
					else emit addVerticalLine(x2Val);
				}
			}
			else {
				x2Line->setText(QString::number(x,'g',10));
				if(functionType==GRAPHPOLAR)
					emit addPolarLine(x);
				else emit addVerticalLine(x);
				
				double xVal=runCalc(xLine->text(),&pref,vars);
				if(xVal != NAN)
				{
					if(functionType==GRAPHPOLAR)
						emit addPolarLine(xVal);
					else emit addVerticalLine(xVal);
				}
			}
			firstLine=!firstLine;
			break;
		}
		case CALCXVAL:
		{
			emit removeLines();
			xLine->setText(QString::number(y,'g',10));

			if(functionType==GRAPHPOLAR)
				emit addCircle(y);
			else emit addHorizontalLine(y);
			break;
		}

	}
}

void GraphSolveWidget::setFunctionType(int fType)
{
//	MessageBox("functionType, currentItem: "+QString::number(fType));
	switch(fType)
	{
		case 0:
			functionType=GRAPHSTD;
			break;
		case 1:
			functionType=GRAPHPOLAR;
			break;
		case 2:
			functionType=GRAPHPARAMETER;
			break;
		case 3:
			functionType=GRAPHIEL;
			break;
		case 4:
			functionType=GRAPH3D;
			break;
		case 5:
			functionType=GRAPHCOMPLEX;
			break;
	}
	setPref(pref);

}






