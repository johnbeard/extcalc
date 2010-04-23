/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         buttons.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "buttons.h"
//Added by qt3to4:
#include <QResizeEvent>

/// StandardButtons constructor to initialize buttons and set dock widget settings
StandardButtons::StandardButtons(QWidget *parent) :ToolWidget(parent)
{
  cols=5;
  rows=4;

  QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
              "4",	"5",	"6",	"*",	"/",
              "1",	"2",	"3",	"+",	"-",
              "0",	".",	"EXP",	"ANS",	"=",
  };

  buttons=new QButtonGroup(this);


  for(int c=0; c<20; c++)
    buttons->addButton(new QPushButton(buttonName[c],this),c);


  setMinimumWidth(280);
  setMaximumWidth(280);
  setMinimumHeight(220);
  setMaximumHeight(220);

  setFocusPolicy(Qt::StrongFocus);
  setFloating(false);
  setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
  setAllowedAreas(Qt::BottomDockWidgetArea);


  QObject::connect(buttons,SIGNAL(buttonClicked(int)),this,SLOT(buttonSlot(int)));
}

/// updates the local copy of the preferences struct and sets the correct button set
void StandardButtons::setPref(Preferences newPref)
{
    pref=newPref;
    if(pref.alpha)
      setAlphaSet();
    else if(pref.shift)
      setShiftSet();
    else setStandardSet();
}

/// change the button text to the standard set
void StandardButtons::setStandardSet()
{
  QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
              "4",	"5",	"6",	"*",	"/",
              "1",	"2",	"3",	"+",	"-",
              "0",	".",	"EXP",	"ANS",	"=",
  };
  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }
}

/// change the button text to the alpha set
void StandardButtons::setAlphaSet()
{
  QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
              "4",	"5",	"6",	"W",	"X",
              "1",	"2",	"3",	"Y",	"Z",
              "0",	".",	"EXP",	"ANS",	"=",
  };
  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }
}

/// change the button set to the shift set
void StandardButtons::setShiftSet()
{
  QString buttonName[] ={	"M",	"G",	"T",	"DEL",	"AC",
              "\xb5",	"m",	"k",	"*",	"/",
              "f",	"p",	"n",	"+",	"-",
              "0",	".",	"EXP",	"ANS",	"=",
  };
  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }
}

/// Check the pressed button end emit a text signal. Default text is the button text.
void StandardButtons::buttonSlot(int num)
{
//	MessageBox("stdButton: "+QString::number(num));
	switch(num)
	{
		case 0:
			if(pref.shift) 
				emit emitText(getUnicode(MEGASTRING));
      else emit emitText(buttons->button(num)->text());
			break;
		case 1:
			if(pref.shift) 
				emit emitText(getUnicode(GIGASTRING));
      else emit emitText(buttons->button(num)->text());
			break;
		case 2:
			if(pref.shift) 
				emit emitText(getUnicode(TERASTRING));
      else emit emitText(buttons->button(num)->text());
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
      emit emitText(buttons->button(num)->text());
			break;
	}
	
	if(pref.hyp || pref.shift || pref.alpha)
	{
		pref.hyp=pref.shift=pref.alpha=false;
    ((QPushButton*)buttons->button(0))->setOn(false);
    ((QPushButton*)buttons->button(0))->setOn(false);
    ((QPushButton*)buttons->button(0))->setOn(false);
		emit prefChange(pref);
	}
}

/// ExtButton constructor with button initialization and dock widget settings
ExtButtons::ExtButtons(QWidget *parent) :ToolWidget(parent)
{
  cols=6;
  rows=4;

  buttons=new QButtonGroup(this);

  for(int c=0; c<24; c++)
    buttons->addButton(new QPushButton(this),c);

  setFocusPolicy(Qt::StrongFocus);
  setFloating(false);
  setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
  setAllowedAreas(Qt::BottomDockWidgetArea);

  setStandardSet();

  ((QPushButton*)buttons->button(0))->setToggleButton(true);
  ((QPushButton*)buttons->button(6))->setToggleButton(true);
  ((QPushButton*)buttons->button(14))->setToggleButton(true);

  setMinimumWidth(300);
  setMaximumWidth(300);
  setMinimumHeight(180);
  setMaximumHeight(180);

  QObject::connect(buttons,SIGNAL(buttonClicked(int)),this,SLOT(buttonSlot(int)));
}

/// update local preferences struct, load neccesary button set and set shift/alpha/hyp button state
 void ExtButtons::setPref(Preferences newPref)
{
  pref=newPref;
//	buttons[0].setOn(pref.shift);
//	buttons[6].setOn(pref.alpha);
//	buttons[14].setOn(pref.hyp);
  ((QPushButton*)buttons->button(0))->setOn(pref.shift);
  ((QPushButton*)buttons->button(6))->setOn(pref.alpha);
  ((QPushButton*)buttons->button(14))->setOn(pref.hyp);

  if(pref.calcType == BASE)
  {
    if(pref.shift)
      setBaseShiftSet();
    else if(pref.alpha)
      setAlphaSet();
    else setBaseStandardSet();
  }
  else
  {
    if(pref.shift)
      setShiftSet();
    else if(pref.alpha)
      setAlphaSet();
    else if(pref.hyp)
      setHypSet();
    else setStandardSet();
  }
}

/// set standard button set
void ExtButtons::setStandardSet()
{
//	QString buttonName[] ={	"Shift","Rand",	"!",	"",		"i",	"",
//							"Alpha","x^","^2",	"^",	"x",	"^-1",
//							"log",	"ln",	"hyp",	"sin",	"cos",	"tan",
//							"a/b",	"X",	"(",	")",	",",	"->",
//	};
  QString buttonName[] ={	"Shift","","d/dx",	"i",	"",		"",
              "Alpha","x^2","^x",	"^-1",	"\xb2",	"x",
              "log",	"ln",	"hyp",	"sin",	"cos",	"tan",
              ";",	"X",	"(",	")",	",",	"->"
  };

  buttonName[1].insert(0,getUnicode(INTEGRALSTRING));
  buttonName[10].insert(1,getUnicode(ROOTSTRING));
  buttonName[11].insert(1,getUnicode(ROOTSTRING));
  buttonName[4].insert(0,getUnicode(PISTRING));
  buttonName[5].insert(0,getUnicode(EULERSTRING));

  ((QPushButton*)buttons->button(14))->setToggleButton(true);

  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }
}

/// set shift button set
 void ExtButtons::setShiftSet()
  {
    QString buttonName[] ={	"Shift","Rand",	"!",	"i",	"",		"",
                "Alpha","x^3","^3",	"abs",	"arg",	"conj",
                "10^",	"^",	"hyp",	"asin",	"acos",	"atan",
                "==",	"[",	"{",	"}",	"]",	"",
    };

    buttonName[8].insert(1,getUnicode(ROOTSTRING));
    buttonName[13].insert(0,getUnicode(EULERSTRING));
    buttonName[4].insert(0,getUnicode(PISTRING));
    buttonName[5].insert(0,getUnicode(EULERSTRING));
    buttonName[23].insert(0,getUnicode(DEGREESTRING));
  //	buttons[14].setToggleButton(true);
    ((QPushButton*)buttons->button(14))->setToggleButton(true);

    QPushButton *currentButton;
    for(int c=0; c<cols*rows; c++)
    {
      currentButton=(QPushButton*)buttons->button(c);
      currentButton->setText(buttonName[c]);
    }
    if(pref.hyp)
      setHypSet();
  }

/// set alpha button set
void ExtButtons::setAlphaSet()
{
  QString buttonName[] ={	"Shift","A",	"B",	"C",	"D",	"E",
              "Alpha","F",	"G",	"H",	"I",	"J",
              "K",	"L",	"M",	"N",	"O",	"P",
              "Q",	"R",	"S",	"T",	"U",	"V",
  };
//	buttons[14].setToggleButton(false);
  ((QPushButton*)buttons->button(14))->setToggleButton(false);


  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }
}

/// set hyp button set
void ExtButtons::setHypSet()
{
  if(pref.shift)
  {
  //	buttons[15].setText("asinh");
  //	buttons[16].setText("acosh");
  //	buttons[17].setText("atanh");
    ((QPushButton*)buttons->button(15))->setText("asinh");
    ((QPushButton*)buttons->button(16))->setText("acosh");
    ((QPushButton*)buttons->button(17))->setText("atanh");
  }
  else {
  //	buttons[15].setText("sinh");
  //	buttons[16].setText("cosh");
  //	buttons[17].setText("tanh");
    ((QPushButton*)buttons->button(15))->setText("sinh");
    ((QPushButton*)buttons->button(16))->setText("cosh");
    ((QPushButton*)buttons->button(17))->setText("tanh");
  }
}

/// set standard button set for calculator logic mode
 void ExtButtons::setBaseStandardSet()
{
  QString buttonName[] ={	"Shift","Rand",	"!",	"%",	"x",	"^",
              "Alpha","x^2",	"&&",	"|",	"~",	"xor",
              "A",	"B",	"C",	"D",	"E",	"F",
              "==",	"X",	"(",	")",	",",	"->",
  };

  buttonName[4].insert(1,getUnicode(ROOTSTRING));
  ((QPushButton*)buttons->button(14))->setToggleButton(false);

  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }
}

/// set shift button set for calculator logic mode
void ExtButtons::setBaseShiftSet()
{
  QString buttonName[] ={	"Shift","Rand",	">",	"%",	"x",	"^",
              "Alpha","x\xb3","&&&&",	"||",	"<",	"xor",
              "dec",	"bin",	"hex",	"oct",	"<<",	">>",
              "!=",	"X",	"(",	")",	",",	"->",
  };

  buttonName[4].insert(1,getUnicode(ROOTSTRING));
  ((QPushButton*)buttons->button(14))->setToggleButton(false);

  QPushButton *currentButton;
  for(int c=0; c<cols*rows; c++)
  {
    currentButton=(QPushButton*)buttons->button(c);
    currentButton->setText(buttonName[c]);
  }

}

/// Receive the button signals and emit text message. Default is the button text.
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
			if(pref.calcType==SCIENTIFIC && !pref.shift && !pref.alpha)
				emit emitText(getUnicode(INTEGRALSTRING)+"(");
			else if(pref.calcType==SCIENTIFIC && pref.shift && !pref.alpha ||pref.calcType==BASE && !pref.alpha)
				emit emitText("rnd(");
      else emit emitText(buttons->button(num)->text());
			break;
		}
		case 2:
		{
			if(pref.calcType==SCIENTIFIC && !pref.shift && !pref.alpha)
				emit emitText("d/dx(");
      else emit emitText(buttons->button(num)->text());
			break;
		}
		case 4:
		{
			if(pref.calcType==BASE && !pref.alpha)
				emit emitText(getUnicode(ROOTSTRING));
      else emit emitText(buttons->button(num)->text());
			break;
		}
	/*	case 3:
			if(pref.calcType==SCIENTIFIC)
			{
				if(pref.alpha)
          emit emitText(buttons->button(num)->text());
				else if(pref.shift)
					emit emitText("d/dx(");
				else emit emitText(getUnicode(INTEGRALSTRING)+"(");
			}
      else emit emitText(buttons->button(num)->text());
			break;
		case 4:
			if(pref.calcType==SCIENTIFIC)
			{
				if(pref.alpha)
          emit emitText(buttons->button(num)->text());
				else emit emitText(find(num)->text());; // i button
			}
			else {
				if(pref.alpha)
					emit emitText(find(num)->text());
				else emit emitText(getUnicode(ROOTSTRING));
			}
			break;
	*/	case 6:
			pref.alpha=!pref.alpha;
			emit prefChange(pref);
			break;
		case 7:
			if(pref.shift)
				emit emitText("\xb3");
			else if(pref.alpha)
        emit emitText(buttons->button(num)->text());
			else emit emitText("\xb2");
			break;
		case 8:

			if(pref.calcType==SCIENTIFIC)
			{
				if(pref.shift)
          emit emitText(buttons->button(num)->text());
				else if(pref.alpha)
          emit emitText(buttons->button(num)->text());
				else emit emitText("^");
			}
			else {
				if(pref.shift)
					emit emitText("&&");
				else if(pref.alpha)
          emit emitText(buttons->button(num)->text());
				else emit emitText("&");
				}
			break;
		case 11:
			if(pref.calcType==BASE &&!pref.alpha)
				emit emitText("x");
			else if(pref.calcType==SCIENTIFIC && !pref.alpha && !pref.shift)
				emit emitText(getUnicode(ROOTSTRING));
      else emit emitText(buttons->button(num)->text());
				
			break;
		case 14:
			
			if(pref.alpha || pref.calcType==BASE)
        emit emitText(buttons->button(num)->text());
			else {
				pref.hyp=!pref.hyp;
				emit prefChange(pref);
			}
			break;

		default:
      emit emitText(buttons->button(num)->text());
			break;
	}

	if((num!=14 && num !=0 && num!=6 && (pref.hyp || pref.shift)) ||
	    (num!=0 && num!=6 && (pref.alpha || pref.calcType==BASE)))
	{
		pref.hyp=pref.shift=pref.alpha=false;
		emit prefChange(pref);
	}
}


/// Resize event handler to place the singe buttons correctly
void StandardButtons::resizeEvent( QResizeEvent*)
{


	int width=geometry().right() -geometry().left()-2;
  int height=geometry().bottom()-geometry().top()-22;
	
	if(width <=0 || height <=0)
		return;

	

	for(int c1=0; c1<rows; c1++)
		for(int c2=0; c2<cols; c2++)
		{
      if(buttons->button(c1*cols+c2)!=NULL)
        buttons->button(c1*cols+c2)->setGeometry(c2*(width/cols)+2,c1*(height/rows)+22,width/cols,height/rows);
		}
	

}



/// Resize event handler to place the singe buttons correctly
void ExtButtons::resizeEvent( QResizeEvent*)
{


	int width=geometry().right() -geometry().left()-2;
  int height=geometry().bottom()-geometry().top()-22;
	
	if(width <=0 || height <=0)
		return;
	
	for(int c1=0; c1<rows; c1++)
		for(int c2=0; c2<cols; c2++)
		{
    if(buttons->button(c1*cols+c2)!=NULL)
      buttons->button(c1*cols+c2)->setGeometry(c2*(width/cols)+2,c1*(height/rows)+22,width/cols,height/rows);
		}

	
}

