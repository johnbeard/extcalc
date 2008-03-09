/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         catalog.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This is a overloaded popup menu that serves a complete function catalog.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef CATALOGH
#define CATALOGH

#include <qpopupmenu.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qdialog.h>
#include "global.h"


/*
math
pi											3,14159 26535 89793 23846 26433 83279 50288
euler										2,71828 18284 59045 23536 02874 71352 66249
(C)gamma (Euler-Mascheroni-Konstante)			0,57721 56649 01532 86060 65120 90082 40243

physics
c0	vacuum light speed						299 792 458						m/s
my0 magnetic field							12.566 370 614...x10^7			N/A^2
epsilon0 electric field						8.854 187 817...x10^12			F/m
Z0	Wellenwiderstand						376.730 313 461					Ohm
G (Gravitation)								6.6742x10^11					m^3/(kg s^2)
h (plancksches Wirkungsquantum				6.626 069 3x10^-34

e (Elementraladung)							1.602 176 53x10^-19				C
alpha (Feinstrukturkonstante)				7.297 352 568x10^-3

m_e Elektronenmasse							9.109 381 88(72)x10^-31			kg
m_p Protonenmasse							1.672 621 58(13)x10^-27			kg
m_n Neutronenmasse							1.674 927 16(13)x10^-27			kg

conversation
*/

class ConstantDialog :public QDialog
{
	QLabel *constLabel,*descriptionLabel,*valueLabel,*identifierLabel;
	QLineEdit *descriptionLine,*valueLine,*identifierLine;
	QPushButton *okButton,*cancelButton,*addButton,*removeButton;
	QListBox *variablesBox;
	Preferences pref;
	Q_OBJECT
	
	
	public:
	ConstantDialog(QWidget*parent,QString name,Preferences p);
	
	public slots:
		
	void boxSlot();
	void applySlot();
	void removeSlot();
	void setPref(Preferences newPref);
	
	signals:
		void prefChange(Preferences);
	
};


class Catalog :public QPopupMenu
{
	QPopupMenu *mathStandard,*mathTrigonometric,*mathExtended,*mathLogic,*matrix,*scriptStandard,*scriptText,*scriptGraphics,*scriptGL,*scriptFile,
 	*constantsMath,*constantsPhysics,*constantsConv,*constantsUser;
	Preferences pref;
	int mathConstLen,physicsConstLen,convConstLen;
	int state;
	ConstantDialog*cDialog;
	Q_OBJECT


	public:
	
	Catalog(int st, QWidget*parent,Preferences *p=NULL) :QPopupMenu(parent)
	{
		state=st;
		if(p==NULL)
		{
			if(state&CATCONSTANTS)
				state&=~CATCONSTANTS;
			pref.constList=NULL;
		}
		else pref=*p;
		mathStandard=new QPopupMenu(this);
		mathTrigonometric=new QPopupMenu(this);
		mathExtended=new QPopupMenu(this);
		mathLogic=new QPopupMenu(this);
		matrix=new QPopupMenu(this);
		scriptStandard=new QPopupMenu(this);
		scriptText=new QPopupMenu(this);
		scriptGraphics=new QPopupMenu(this);
		scriptGL=new QPopupMenu(this);
		scriptFile=new QPopupMenu(this);

		constantsMath=new QPopupMenu(this);
		constantsPhysics=new QPopupMenu(this);
		constantsConv=new QPopupMenu(this);
		constantsUser=new QPopupMenu(this);
		
		cDialog=new ConstantDialog(parent,"Mofify Constants",pref);

		if(state&CATCONSTANTS)
		{
			insertItem(tr("Mathematics Constants"),constantsMath);
			insertItem(tr("Physics Constants"),constantsPhysics);
			insertItem(tr("Conversation Constants"),constantsConv);
			insertItem(tr("Userdefined Constants"),constantsUser);
		}
		if(state&CATMATHSTD)
		{
			mathStandard->insertItem("+",1);
			mathStandard->insertItem("-",2);
			mathStandard->insertItem("*",3);
			mathStandard->insertItem("/",4);
			
			mathStandard->insertItem("^2",5);
			mathStandard->insertItem("^3",6);
			mathStandard->insertItem("^-1",7);
			mathStandard->insertItem("^",8);
			mathStandard->insertItem("sqrt",9);
			mathStandard->insertItem("curt",10);
			mathStandard->insertItem("root",11);

			mathStandard->insertItem("log",12);
			mathStandard->insertItem("ln",13);
			
			mathStandard->insertItem("set ->",14);
			mathStandard->insertItem("set =",15);

			
			mathTrigonometric->insertItem("sin",1);
			mathTrigonometric->insertItem("cos",2);
			mathTrigonometric->insertItem("tan",3);
			mathTrigonometric->insertItem("asin",4);
			mathTrigonometric->insertItem("acos",5);
			mathTrigonometric->insertItem("atan",6);
			mathTrigonometric->insertItem("sinh",7);
			mathTrigonometric->insertItem("cosh",8);
			mathTrigonometric->insertItem("tanh",9);
			mathTrigonometric->insertItem("asinh",10);
			mathTrigonometric->insertItem("acosh",11);
			mathTrigonometric->insertItem("atanh",12);
			
			mathExtended->insertItem("abs",1);
			mathExtended->insertItem("faculty !",6);
			mathExtended->insertItem("modulo %",7);
			mathExtended->insertItem("rnd",8);
			mathExtended->insertItem("d/dx",9);
			mathExtended->insertItem("integral",10);


			
			insertItem(tr("Math Standard"),mathStandard);
			insertItem(tr("Math Trigonometric"),mathTrigonometric);
			insertItem(tr("Math Extended"),mathExtended);
		}
		if(state&CATMATHLOGIC)
		{
			mathLogic->insertItem("logic and &&&&",1);
			mathLogic->insertItem("logic or ||",2);
			mathLogic->insertItem("logic not !",3);
			mathLogic->insertItem("==",4);
			mathLogic->insertItem(">=",5);
			mathLogic->insertItem("<=",6);
			mathLogic->insertItem("!=",7);
			mathLogic->insertItem("<",8);
			mathLogic->insertItem(">",9);
			mathLogic->insertItem("binary and &&",10);
			mathLogic->insertItem("binary or |",11);
			mathLogic->insertItem("binary not ~",12);
			mathLogic->insertItem("left shift <<",13);
			mathLogic->insertItem("right shift >>",14);

			insertItem(tr("Math Logic"),mathLogic);
		}
		if(state&CATMATHCOMPLEX)
		{
			
			mathExtended->insertItem("arg",2);
			mathExtended->insertItem("conj",3);
			mathExtended->insertItem("real",4);
			mathExtended->insertItem("imag",5);

		}
		if(state&CATMATRIX)
		{
			matrix->insertItem("[]",1);
			matrix->insertItem("sprod",2);
			matrix->insertItem("^-1",3);

			insertItem(tr("Matrix/Vector"),matrix);
		}
		if(state&CATSCRIPT)
		{
			scriptStandard->insertItem("if",1);
			scriptStandard->insertItem("for",2);
			scriptStandard->insertItem("while",3);
			scriptStandard->insertItem("break",4);
			scriptStandard->insertItem("continue",5);
			scriptStandard->insertItem("stop",6);
			scriptStandard->insertItem("sleep",7);
			scriptStandard->insertItem("run",8);
			scriptStandard->insertItem("(bool)",9);
			scriptStandard->insertItem("(int)",10);
			scriptStandard->insertItem("(float)",11);
			scriptStandard->insertItem("(string)",12);
			scriptStandard->insertItem(";",13);
			scriptStandard->insertItem("{",14);
			scriptStandard->insertItem("}",15);
			
			scriptText->insertItem("print",1);
			scriptText->insertItem("clear",2);
			scriptText->insertItem("setcursor",3);
			scriptText->insertItem("getline",4);
			scriptText->insertItem("getkey",5);
			scriptText->insertItem("keystate",6);

			
			scriptGraphics->insertItem("drawpoint",1);
			scriptGraphics->insertItem("drawline",2);
			scriptGraphics->insertItem("drawrect",3);
			scriptGraphics->insertItem("drawcircle",4);
			scriptGraphics->insertItem("drawstring",5);
			scriptGraphics->insertItem("drawcolor",6);
			scriptGraphics->insertItem("drawclear",7);
			
			
			scriptGL->insertItem("glbegin",1);
			scriptGL->insertItem("glendlist",2);
			scriptGL->insertItem("glend",3);
			scriptGL->insertItem("glshow",4);
			scriptGL->insertItem("glclear",5);
			scriptGL->insertItem("glloadidentity",6);
			scriptGL->insertItem("glstartlist",7);
			scriptGL->insertItem("glcalllist",8);
			scriptGL->insertItem("glpoint",9);
			scriptGL->insertItem("glscale",10);
			scriptGL->insertItem("glmove",11);
			scriptGL->insertItem("glrotate",12);
			scriptGL->insertItem("glcolor",13);
			scriptGL->insertItem("glstring",14);
			
			scriptFile->insertItem("readfile",1);
			scriptFile->insertItem("writefile",2);
			scriptFile->insertItem("removefile",3);
			scriptFile->insertItem("appendfile",4);

			
			insertItem(tr("Script Standard"),scriptStandard);
			insertItem(tr("Script Text"),scriptText);
			insertItem(tr("Script Graphics"),scriptGraphics);
			insertItem(tr("Script GL"),scriptGL);
			insertItem(tr("Script File"),scriptFile);
			
		}

		QObject::connect(mathStandard,SIGNAL(activated(int)),this,SLOT(mathStandardSlot(int)));
		QObject::connect(mathTrigonometric,SIGNAL(activated(int)),this,SLOT(mathTrigonometricSlot(int)));
		QObject::connect(mathExtended,SIGNAL(activated(int)),this,SLOT(mathExtendedSlot(int)));
		QObject::connect(mathLogic,SIGNAL(activated(int)),this,SLOT(mathLogicSlot(int)));
		QObject::connect(matrix,SIGNAL(activated(int)),this,SLOT(matrixSlot(int)));
		QObject::connect(scriptStandard,SIGNAL(activated(int)),this,SLOT(scriptStandardSlot(int)));
		QObject::connect(scriptText,SIGNAL(activated(int)),this,SLOT(scriptTextSlot(int)));
		QObject::connect(scriptGraphics,SIGNAL(activated(int)),this,SLOT(scriptGraphicsSlot(int)));
		QObject::connect(scriptGL,SIGNAL(activated(int)),this,SLOT(scriptGLSlot(int)));
		QObject::connect(scriptFile,SIGNAL(activated(int)),this,SLOT(scriptFileSlot(int)));
		QObject::connect(constantsPhysics,SIGNAL(activated(int)),this,SLOT(constantsSlot(int)));
		QObject::connect(constantsMath,SIGNAL(activated(int)),this,SLOT(constantsSlot(int)));
		QObject::connect(constantsConv,SIGNAL(activated(int)),this,SLOT(constantsSlot(int)));
		QObject::connect(constantsUser,SIGNAL(activated(int)),this,SLOT(constantsSlot(int)));
		QObject::connect(cDialog,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		

	}
	
	void setPref(Preferences newPref);
	


	
	public slots:
		
	void mathStandardSlot(int);
	void mathTrigonometricSlot(int);
	void mathExtendedSlot(int);
	void mathLogicSlot(int);
	
	void matrixSlot(int);
	
	void scriptStandardSlot(int);
	void scriptTextSlot(int);
	void scriptGraphicsSlot(int);
	void scriptGLSlot(int);
	void scriptFileSlot(int);
	
	void constantsSlot(int);
	
	void getPref(Preferences pref)
	{emit prefChange(pref);}

	
	signals:
	
	void menuSignal(QString);
	void prefChange(Preferences);
	
	
};




#endif
