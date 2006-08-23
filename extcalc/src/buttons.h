
#ifndef BUTTONSH
#define BUTTONSH

#include "global.h"
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qstring.h>
#include <qfont.h>
#include <stdio.h>


class StandardButtons :public QButtonGroup
{
//	QPushButton * buttons;
	int cols,rows;
	Preferences pref;
	QFont stdFont;

	Q_OBJECT
	
public:

	StandardButtons(QWidget *parent) :QButtonGroup(parent)
	{
		cols=5;
		rows=4;


		QString buttonName[] ={	"7",	"8",	"9",	"DEL",	"AC",
								"4",	"5",	"6",	"*",	"/",
								"1",	"2",	"3",	"+",	"-",
								"0",	".",	"EXP",	"ANS",	"=",
		};

//		buttons = new QPushButton[20](this);
		for(int c=0; c<20; c++)
			insert(new QPushButton(buttonName[c],this));
		
/*		for(int c=0; c<cols*rows; c++)
		{
			buttons[c].setText(buttonName[c]);
		}
*/		QObject::connect(this,SIGNAL(clicked(int)),this,SLOT(buttonSlot(int)));
	//	stdFont=font();
	//	stdFont.setPixelSize(15);
	//	setFont(stdFont);

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
								"µ",	"m",	"k",	"*",	"/",
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


class ExtButtons :public QButtonGroup
{
//	QPushButton * buttons;
	int cols,rows;
	Preferences pref;

	Q_OBJECT
	
public:

	ExtButtons(QWidget *parent) :QButtonGroup(parent)
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
	//	buttons[0].setToggleButton(true);
	//	buttons[6].setToggleButton(true);
	//	buttons[14].setToggleButton(true);
		
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
		QString buttonName[] ={	"Shift","Rand",	"!",	"",		"i",	"",
								"Alpha","x²",	"²",	"^",	"x",	"^-1",
								"log",	"ln",	"hyp",	"sin",	"cos",	"tan",
								"a/b",	"X",	"(",	")",	",",	"->",
		};
		buttonName[3].insert(1,getUnicode(INTEGRALSTRING));
		buttonName[8].insert(1,getUnicode(ROOTSTRING));
		buttonName[10].insert(1,getUnicode(ROOTSTRING));
		buttonName[5].insert(0,getUnicode(PISTRING));
	//	buttons[14].setToggleButton(true);
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
		QString buttonName[] ={	"Shift","Rand",	"!",	"d/dx",	"i",	"",
								"Alpha","x³",	"³",	"^",	"x",	"^-1",
								"10^",	"^",	"hyp",	"asin",	"acos",	"atan",
								"a/b",	"X",	"(",	")",	",",	"->",
		};

		buttonName[8].insert(1,getUnicode(ROOTSTRING));
		buttonName[10].insert(1,getUnicode(ROOTSTRING));
		buttonName[5].insert(0,getUnicode(EULERSTRING));
		buttonName[9].insert(0,getUnicode(EULERSTRING));
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
								"a/b",	"X",	"(",	")",	",",	"->",
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
		QString buttonName[] ={	"Shift","Rand",	"!",	"%",	"x",	"^",
								"Alpha","x³",	"&&&&",	"||",	"n",	"xor",
								"dec",	"bin",	"hex",	"oct",	"<<",	">>",
								"a/b",	"X",	"(",	")",	",",	"->",
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

