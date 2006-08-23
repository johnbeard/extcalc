#include "buttons.h"




void StandardButtons::buttonSlot(int num)
{
//	MessageBox("stdButton: "+QString::number(num));
	switch(num)
	{
		case 0:
			if(pref.shift) 
				emit emitText(getUnicode(MEGASTRING));
			else emit emitText(find(num)->text());
			break;
		case 1:
			if(pref.shift) 
				emit emitText(getUnicode(GIGASTRING));
			else emit emitText(find(num)->text());
			break;
		case 2:
			if(pref.shift) 
				emit emitText(getUnicode(TERASTRING));
			else emit emitText(find(num)->text());
			break;
		case 3:
			 emit emitText("backkey");
			break;
		case 4:
			emit emitText("clearall");
			break;
		case 17:
			emit emitText("e");
			break;
		case 18:
			emit emitText("ans");
			break;
		case 19:
			emit emitText("calculate");
			break;
		default:
			emit emitText(find(num)->text());
			break;
	}
	
	if(pref.hyp || pref.shift || pref.alpha)
	{
		pref.hyp=pref.shift=pref.alpha=false;
		((QPushButton*)find(0))->setOn(false);
		((QPushButton*)find(0))->setOn(false);
		((QPushButton*)find(0))->setOn(false);
		emit prefChange(pref);
	}
}



void ExtButtons::buttonSlot(int num)
{
//	MessageBox("extButton: "+QString::number(num));
	switch(num)
	{
		case 0:
			pref.shift=!pref.shift;
			emit prefChange(pref);
			break;
		case 1:
		{
			if(pref.alpha)
				emit emitText(find(num)->text());
			else emit emitText("rnd");
			break;
		}
		case 3:
			if(pref.calcType==SCIENTIFIC)
			{
				if(pref.alpha)
					emit emitText(find(num)->text());
				else if(pref.shift)
					emit emitText("d/dx(");
				else emit emitText(getUnicode(INTEGRALSTRING)+"(");
			}
			else emit emitText(find(num)->text());
			break;
		case 4:
			if(pref.calcType==SCIENTIFIC)
			{
				if(pref.alpha)
					emit emitText(find(num)->text());
				else ; // i button
			}
			else {
				if(pref.alpha)
					emit emitText(find(num)->text());
				else emit emitText(getUnicode(ROOTSTRING));
			}
			break;
		case 6:
			pref.alpha=!pref.alpha;
			emit prefChange(pref);
			break;
		case 7:
			if(pref.shift)
				emit emitText("³");
			else if(pref.alpha)
				emit emitText(find(num)->text());
			else emit emitText("²");
			break;
		case 8:

			if(pref.calcType==SCIENTIFIC)
				emit emitText(find(num)->text());
			else {
				if(pref.shift)
					emit emitText("&&");
				else if(pref.alpha)
					emit emitText(find(num)->text());
				else emit emitText("&");
				}
			break;
		case 10:
			if(pref.calcType==SCIENTIFIC)
			{
				if(pref.alpha)
					emit emitText(find(num)->text());
				else emit emitText(getUnicode(ROOTSTRING));
			}
			else emit emitText(find(num)->text());
			break;
		case 11:
			if(pref.calcType==BASE &&!pref.alpha)
				emit emitText("x");
			else emit emitText(find(num)->text());
			break;
		case 14:
			
			if(pref.alpha || pref.calcType==BASE)
				emit emitText(find(num)->text());
			else {
				pref.hyp=!pref.hyp;
				emit prefChange(pref);
			}
			break;
		case 18:
			if(pref.alpha)
				emit emitText(find(num)->text());
			else ; // a/b button
			break;
		default:
			emit emitText(find(num)->text());
			break;
	}

	if((num!=14 && num !=0 && num!=6 && (pref.hyp || pref.shift)) ||
	    (num!=0 && num!=6 && (pref.alpha || pref.calcType==BASE)))
	{
		pref.hyp=pref.shift=pref.alpha=false;
		emit prefChange(pref);
	}
}
 
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////StandardButtons////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



void StandardButtons::resizeEvent( QResizeEvent*)
{


	int width=geometry().right() -geometry().left()-2;
	int height=geometry().bottom()-geometry().top()-2;
	
	if(width <=0 || height <=0)
		return;

	

	for(int c1=0; c1<rows; c1++)
		for(int c2=0; c2<cols; c2++)
		{
			find(c1*cols+c2)->setGeometry(c2*(width/cols)+2,c1*(height/rows)+2,width/cols,height/rows);
		}
	

}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////ExtButtons//////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


void ExtButtons::resizeEvent( QResizeEvent*)
{


	int width=geometry().right() -geometry().left()-2;
	int height=geometry().bottom()-geometry().top()-2;
	
	if(width <=0 || height <=0)
		return;
	
	for(int c1=0; c1<rows; c1++)
		for(int c2=0; c2<cols; c2++)
		{
			find(c1*cols+c2)->setGeometry(c2*(width/cols)+2,c1*(height/rows)+2,width/cols,height/rows);
		}

	
}

