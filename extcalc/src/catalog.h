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
#include "global.h"


class Catalog :public QPopupMenu
{
	QPopupMenu *mathStandard,*mathTrigonometric,*mathExtended,*matrix,*scriptStandard,*scriptText,*scriptGraphics,*scriptGL;
	Q_OBJECT


	public:
	
	Catalog(int state, QWidget*parent) :QPopupMenu(parent)
	{
		mathStandard=new QPopupMenu(this);
		mathTrigonometric=new QPopupMenu(this);
		mathExtended=new QPopupMenu(this);
		matrix=new QPopupMenu(this);
		scriptStandard=new QPopupMenu(this);
		scriptText=new QPopupMenu(this);
		scriptGraphics=new QPopupMenu(this);
		scriptGL=new QPopupMenu(this);

		if(state&CATMATHSTD)
		{
			mathStandard->insertItem("+",1);
			mathStandard->insertItem("-",2);
			mathStandard->insertItem("*",3);
			mathStandard->insertItem("/",4);
			
			mathTrigonometric->insertItem("sin",1);
			mathTrigonometric->insertItem("cos",2);
			mathTrigonometric->insertItem("tan",3);
			
			mathExtended->insertItem("abs",1);
			
			insertItem("Math Standard",mathStandard);
			insertItem("Math Trigonometric",mathTrigonometric);
			insertItem("Math Extended",mathExtended);
		}
		if(state&CATMATHCOMPLEX)
		{
			
			mathExtended->insertItem("arg",2);
			mathExtended->insertItem("conj",3);
		}
		if(state&CATMATRIX)
		{
			matrix->insertItem("[]",1);
			
			insertItem("Matrix/Vector",matrix);

		}
		if(state&CATSCRIPT)
		{
			scriptStandard->insertItem("if",1);
			scriptStandard->insertItem("for",2);
			scriptStandard->insertItem("while",3);
			
			scriptText->insertItem("print",1);
			
			scriptGraphics->insertItem("drawpoint",1);
			
			scriptGL->insertItem("glbegin",1);
			
			insertItem("Script Standard",scriptStandard);
			insertItem("Script Text",scriptText);
			insertItem("Script Graphics",scriptGraphics);
			insertItem("Script GL",scriptGL);
			
		}

		QObject::connect(mathStandard,SIGNAL(activated(int)),this,SLOT(mathStandardSlot(int)));
		QObject::connect(mathTrigonometric,SIGNAL(activated(int)),this,SLOT(mathTrigonometricSlot(int)));
		QObject::connect(mathExtended,SIGNAL(activated(int)),this,SLOT(mathExtendedSlot(int)));
		QObject::connect(matrix,SIGNAL(activated(int)),this,SLOT(matrixSlot(int)));
		QObject::connect(scriptStandard,SIGNAL(activated(int)),this,SLOT(scriptStandardSlot(int)));
		QObject::connect(scriptText,SIGNAL(activated(int)),this,SLOT(scriptTextSlot(int)));
		QObject::connect(scriptGraphics,SIGNAL(activated(int)),this,SLOT(scriptGraphicsSlot(int)));
		QObject::connect(scriptGL,SIGNAL(activated(int)),this,SLOT(scriptGLSlot(int)));
	}
	
	public slots:
		
	void mathStandardSlot(int);
	void mathTrigonometricSlot(int);
	void mathExtendedSlot(int);
	
	void matrixSlot(int);
	
	void scriptStandardSlot(int);
	void scriptTextSlot(int);
	void scriptGraphicsSlot(int);
	void scriptGLSlot(int);
	
	signals:
	
	void menuSignal(QString);
	
	
};




#endif
