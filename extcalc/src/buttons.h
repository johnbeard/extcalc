/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         buttons.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This file includes the classes for the two button fields of the calculator.
StandardButtons class for numbers and basic functions
ExtButtons for scientific functions

////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef BUTTONSH
#define BUTTONSH

#include "global.h"
#include <qpushbutton.h>
#include <q3buttongroup.h>
#include <qstring.h>
#include <qfont.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <stdio.h>


class StandardButtons :public Q3ButtonGroup
{
//	QPushButton * buttons;
	int cols,rows;
	Preferences pref;
	QFont stdFont;

	Q_OBJECT
	
public:

	StandardButtons(QWidget *parent) :Q3ButtonGroup(parent)
	{
		cols=5;
		rows=4;


		QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
								"4",	"5",	"6",	"*",	"/",
								"1",	"2",	"3",	"+",	"-",
								"0",	".",	"EXP",	"ANS",	"=",
		};


		for(int c=0; c<20; c++)
			insert(new QPushButton(buttonName[c],this));
	
		setMinimumWidth(280);
		setMaximumWidth(280);
		setMinimumHeight(200);
		setMaximumHeight(200);

		
		QObject::connect(this,SIGNAL(clicked(int)),this,SLOT(buttonSlot(int)));


	}
	
	void setPref(Preferences newPref)
	{
		pref=newPref;
		if(pref.alpha)
			setAlphaSet();
		else if(pref.shift)
			setShiftSet();
		else setStandardSet();
	}

	void setStandardSet()
	{
		QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
								"4",	"5",	"6",	"*",	"/",
								"1",	"2",	"3",	"+",	"-",
								"0",	".",	"EXP",	"ANS",	"=",
		};
		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
	}

	void setAlphaSet()
	{
		QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
								"4",	"5",	"6",	"W",	"X",
								"1",	"2",	"3",	"Y",	"Z",
								"0",	".",	"EXP",	"ANS",	"=",
		};
		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
	}
	
	void setShiftSet()
	{
		QString buttonName[] ={	"M",	"G",	"T",	"DEL",	"AC",
								"\xb5",	"m",	"k",	"*",	"/",
								"f",	"p",	"n",	"+",	"-",
								"0",	".",	"EXP",	"ANS",	"=",
		};
		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
	}
	



protected:
		
	virtual void resizeEvent( QResizeEvent * );

public slots:
	
	void buttonSlot(int);
	
	signals:
	void emitText(QString);
	void prefChange(Preferences);
	
};


class ExtButtons :public Q3ButtonGroup
{
//	QPushButton * buttons;
	int cols,rows;
	Preferences pref;

	Q_OBJECT
	
public:

	ExtButtons(QWidget *parent) :Q3ButtonGroup(parent)
	{
		cols=6;
		rows=4;


//		buttons = new QPushButton[24](this);
		for(int c=0; c<24; c++)
			insert(new QPushButton(this));
		

		setStandardSet();

		((QPushButton*)find(0))->setToggleButton(true);
		((QPushButton*)find(6))->setToggleButton(true);
		((QPushButton*)find(14))->setToggleButton(true);

		setMinimumWidth(300);
		setMaximumWidth(300);
		setMinimumHeight(160);
		setMaximumHeight(160);
		
		QObject::connect(this,SIGNAL(clicked(int)),this,SLOT(buttonSlot(int)));


	}
	
	void setPref(Preferences newPref)
	{
		pref=newPref;
	//	buttons[0].setOn(pref.shift);	
	//	buttons[6].setOn(pref.alpha);
	//	buttons[14].setOn(pref.hyp);
		((QPushButton*)find(0))->setOn(pref.shift);
		((QPushButton*)find(6))->setOn(pref.alpha);
		((QPushButton*)find(14))->setOn(pref.hyp);

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


	void setStandardSet()
	{
	//	QString buttonName[] ={	"Shift","Rand",	"!",	"",		"i",	"",
	//							"Alpha","x\xb2","\xb2",	"^",	"x",	"^-1",
	//							"log",	"ln",	"hyp",	"sin",	"cos",	"tan",
	//							"a/b",	"X",	"(",	")",	",",	"->",
	//	};
		QString buttonName[] ={	"Shift","","d/dx",	"i",	"",		"",
								"Alpha","x\xb2","^x",	"^-1",	"\xb2",	"x",
								"log",	"ln",	"hyp",	"sin",	"cos",	"tan",
								";",	"X",	"(",	")",	",",	"->"
		};
		
		buttonName[1].insert(0,getUnicode(INTEGRALSTRING));
		buttonName[10].insert(1,getUnicode(ROOTSTRING));
		buttonName[11].insert(1,getUnicode(ROOTSTRING));
		buttonName[4].insert(0,getUnicode(PISTRING));
		buttonName[5].insert(0,getUnicode(EULERSTRING));

		((QPushButton*)find(14))->setToggleButton(true);

		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
	}
	void setShiftSet()
	{
		QString buttonName[] ={	"Shift","Rand",	"!",	"i",	"",		"",
								"Alpha","x\xb3","\xb3",	"abs",	"arg",	"conj",
								"10^",	"^",	"hyp",	"asin",	"acos",	"atan",
								"==",	"[",	"{",	"}",	"]",	"",
		};

		buttonName[8].insert(1,getUnicode(ROOTSTRING));
		buttonName[13].insert(0,getUnicode(EULERSTRING));
		buttonName[4].insert(0,getUnicode(PISTRING));
		buttonName[5].insert(0,getUnicode(EULERSTRING));
		buttonName[23].insert(0,getUnicode(DEGREESTRING));
	//	buttons[14].setToggleButton(true);
		((QPushButton*)find(14))->setToggleButton(true);

		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
		if(pref.hyp)
			setHypSet();
	}
	void setAlphaSet()
	{
		QString buttonName[] ={	"Shift","A",	"B",	"C",	"D",	"E",
								"Alpha","F",	"G",	"H",	"I",	"J",
								"K",	"L",	"M",	"N",	"O",	"P",
								"Q",	"R",	"S",	"T",	"U",	"V",
		};
	//	buttons[14].setToggleButton(false);
		((QPushButton*)find(14))->setToggleButton(false);


		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
	}
	void setHypSet()
	{
		if(pref.shift)
		{
		//	buttons[15].setText("asinh");
		//	buttons[16].setText("acosh");
		//	buttons[17].setText("atanh");
			((QPushButton*)find(15))->setText("asinh");
			((QPushButton*)find(16))->setText("acosh");
			((QPushButton*)find(17))->setText("atanh");
		}
		else {
		//	buttons[15].setText("sinh");
		//	buttons[16].setText("cosh");
		//	buttons[17].setText("tanh");
			((QPushButton*)find(15))->setText("sinh");
			((QPushButton*)find(16))->setText("cosh");
			((QPushButton*)find(17))->setText("tanh");
		}
	}
	void setBaseStandardSet()
	{
		QString buttonName[] ={	"Shift","Rand",	"!",	"%",	"x",	"^",
								"Alpha","x²",	"&&",	"|",	"~",	"xor",
								"A",	"B",	"C",	"D",	"E",	"F",
								"==",	"X",	"(",	")",	",",	"->",
		};

		buttonName[4].insert(1,getUnicode(ROOTSTRING));
		((QPushButton*)find(14))->setToggleButton(false);

		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}
	}
	void setBaseShiftSet()
	{
		QString buttonName[] ={	"Shift","Rand",	">",	"%",	"x",	"^",
								"Alpha","x\xb3","&&&&",	"||",	"<",	"xor",
								"dec",	"bin",	"hex",	"oct",	"<<",	">>",
								"!=",	"X",	"(",	")",	",",	"->",
		};

		buttonName[4].insert(1,getUnicode(ROOTSTRING));
		((QPushButton*)find(14))->setToggleButton(false);

		QPushButton *currentButton;
		for(int c=0; c<cols*rows; c++)
		{
			currentButton=(QPushButton*)find(c);
			currentButton->setText(buttonName[c]);
		}

	}

	protected:

	virtual void resizeEvent( QResizeEvent * );

	public slots:
		
	void buttonSlot(int);

	signals:
	void emitText(QString);
	void prefChange(Preferences);
	
};


#endif

