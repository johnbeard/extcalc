/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         catalog.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "catalog.h"
//Added by qt3to4:
#include <QLabel>

  Catalog::Catalog(int st, QWidget*parent,Preferences *p) :QMenu(parent)
  {
    QAction*tmpAction;
    state=st;
    if(p==NULL)
    {
      if(state&CATCONSTANTS)
        state&=~CATCONSTANTS;
      pref.constList=NULL;
    }
    else pref=*p;
    mathStandard=new QMenu(this);
    mathTrigonometric=new QMenu(this);
    mathExtended=new QMenu(this);
    mathLogic=new QMenu(this);
    matrix=new QMenu(this);
    scriptStandard=new QMenu(this);
    scriptText=new QMenu(this);
    scriptGraphics=new QMenu(this);
    scriptGL=new QMenu(this);
    scriptFile=new QMenu(this);

    constantsMath=new QMenu(this);
    constantsPhysics=new QMenu(this);
    constantsConv=new QMenu(this);
    constantsUser=new QMenu(this);

    mathStandardMapper=new QSignalMapper(this);
    mathTrigonometricMapper=new QSignalMapper(this);
    mathExtendedMapper=new QSignalMapper(this);
    mathLogicMapper=new QSignalMapper(this);
    matrixMapper=new QSignalMapper(this);
    scriptStandardMapper=new QSignalMapper(this);
    scriptTextMapper=new QSignalMapper(this);
    scriptGraphicsMapper=new QSignalMapper(this);
    scriptGLMapper=new QSignalMapper(this);
    scriptFileMapper=new QSignalMapper(this);

    constantsMapper=new QSignalMapper(this);


    cDialog=new ConstantDialog(parent,"Mofify Constants",pref);

    if(state&CATCONSTANTS)
    {

      constantsMath->setTitle(tr("Mathematics Constants"));
      constantsPhysics->setTitle(tr("Physics Constants"));
      constantsConv->setTitle(tr("Conversation Constants"));
      constantsUser->setTitle(tr("Userdefined Constants"));

      addMenu(constantsMath);
      addMenu(constantsPhysics);
      addMenu(constantsConv);
      addMenu(constantsUser);
    }
    if(state&CATMATHSTD)
    {
      tmpAction=mathStandard->addAction("+");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,1);
      tmpAction=mathStandard->addAction("-");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,2);
      tmpAction=mathStandard->addAction("*");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,3);
      tmpAction=mathStandard->addAction("/");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,4);

      tmpAction=mathStandard->addAction("^2");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,5);
      tmpAction=mathStandard->addAction("^3");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,6);
      tmpAction=mathStandard->addAction("^-1");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,7);
      tmpAction=mathStandard->addAction("^");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,8);


      tmpAction=mathStandard->addAction("sqrt");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,9);
      tmpAction=mathStandard->addAction("curt");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,10);
      tmpAction=mathStandard->addAction("root");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,11);

      tmpAction=mathStandard->addAction("log");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,12);
      tmpAction=mathStandard->addAction("ln");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,13);
      tmpAction=mathStandard->addAction("set ->");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,14);
      tmpAction=mathStandard->addAction("set =");
      connect(tmpAction,SIGNAL(triggered()),mathStandardMapper,SLOT(map()));
      mathStandardMapper->setMapping(tmpAction,15);

      tmpAction=mathTrigonometric->addAction("sin");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,1);
      tmpAction=mathTrigonometric->addAction("cos");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,2);
      tmpAction=mathTrigonometric->addAction("tan");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,3);
      tmpAction=mathTrigonometric->addAction("asin");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,4);

      tmpAction=mathTrigonometric->addAction("acos");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,5);
      tmpAction=mathTrigonometric->addAction("atan");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,6);
      tmpAction=mathTrigonometric->addAction("sinh");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,7);
      tmpAction=mathTrigonometric->addAction("cosh");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,8);

      tmpAction=mathTrigonometric->addAction("tanh");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,9);
      tmpAction=mathTrigonometric->addAction("asinh");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,10);
      tmpAction=mathTrigonometric->addAction("acosh");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,11);
      tmpAction=mathTrigonometric->addAction("atanh");
      connect(tmpAction,SIGNAL(triggered()),mathTrigonometricMapper,SLOT(map()));
      mathTrigonometricMapper->setMapping(tmpAction,12);

      tmpAction=mathExtended->addAction("abs");
      connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
      mathExtendedMapper->setMapping(tmpAction,1);

      if(state&CATMATHCOMPLEX)
      {
        tmpAction=mathExtended->addAction("arg");
        connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
        mathExtendedMapper->setMapping(tmpAction,2);
        tmpAction=mathExtended->addAction("conj");
        connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
        mathExtendedMapper->setMapping(tmpAction,3);
        tmpAction=mathExtended->addAction("real");
        connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
        mathExtendedMapper->setMapping(tmpAction,4);
        tmpAction=mathExtended->addAction("imag");
        connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
        mathExtendedMapper->setMapping(tmpAction,5);
      }
      tmpAction=mathExtended->addAction("faculty !");
      connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
      mathExtendedMapper->setMapping(tmpAction,6);
      tmpAction=mathExtended->addAction("modulo %");
      connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
      mathExtendedMapper->setMapping(tmpAction,7);
      tmpAction=mathExtended->addAction("rnd");
      connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
      mathExtendedMapper->setMapping(tmpAction,8);

      tmpAction=mathExtended->addAction("d/dx");
      connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
      mathExtendedMapper->setMapping(tmpAction,9);
      tmpAction=mathExtended->addAction("integral");
      connect(tmpAction,SIGNAL(triggered()),mathExtendedMapper,SLOT(map()));
      mathExtendedMapper->setMapping(tmpAction,10);

      mathStandard->setTitle(tr("Math Standard"));
      mathTrigonometric->setTitle(tr("Math Trigonometric"));
      mathExtended->setTitle(tr("Math Extended"));

      addMenu(mathStandard);
      addMenu(mathTrigonometric);
      addMenu(mathExtended);
    }
    if(state&CATMATHLOGIC)
    {
      tmpAction=mathLogic->addAction("logic and &&&&");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,1);
      tmpAction=mathLogic->addAction("logic or ||");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,2);
      tmpAction=mathLogic->addAction("logic not !");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,3);
      tmpAction=mathLogic->addAction("==");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,4);

      tmpAction=mathLogic->addAction(">=");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,5);
      tmpAction=mathLogic->addAction("<=");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,6);
      tmpAction=mathLogic->addAction("!=");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,7);
      tmpAction=mathLogic->addAction("<");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,8);

      tmpAction=mathLogic->addAction(">");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,9);
      tmpAction=mathLogic->addAction("binary and &&");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,10);
      tmpAction=mathLogic->addAction("binary or |");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,11);
      tmpAction=mathLogic->addAction("binary not ~");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,12);
      tmpAction=mathLogic->addAction("left shift <<");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,13);
      tmpAction=mathLogic->addAction("right shift >>");
      connect(tmpAction,SIGNAL(triggered()),mathLogicMapper,SLOT(map()));
      mathLogicMapper->setMapping(tmpAction,14);

      mathLogic->setTitle(tr("Math Logic"));
      addMenu(mathLogic);
    }
    if(state&CATMATRIX)
    {
      tmpAction=matrix->addAction("[]");
      connect(tmpAction,SIGNAL(triggered()),matrixMapper,SLOT(map()));
      matrixMapper->setMapping(tmpAction,1);
      tmpAction=matrix->addAction("sprod");
      connect(tmpAction,SIGNAL(triggered()),matrixMapper,SLOT(map()));
      matrixMapper->setMapping(tmpAction,2);
      tmpAction=matrix->addAction("^-1");
      connect(tmpAction,SIGNAL(triggered()),matrixMapper,SLOT(map()));
      matrixMapper->setMapping(tmpAction,3);

      matrix->setTitle(tr("Matrix/Vector"));
      addMenu(matrix);
    }
    if(state&CATSCRIPT)
    {
      tmpAction=scriptStandard->addAction("if");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,1);
      tmpAction=scriptStandard->addAction("for");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,2);
      tmpAction=scriptStandard->addAction("while");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,3);
      tmpAction=scriptStandard->addAction("break");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,4);

      tmpAction=scriptStandard->addAction("continue");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,5);
      tmpAction=scriptStandard->addAction("stop");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,6);
      tmpAction=scriptStandard->addAction("sleep");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,7);
      tmpAction=scriptStandard->addAction("run");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,8);

      tmpAction=scriptStandard->addAction("(bool)");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,9);
      tmpAction=scriptStandard->addAction("(int)");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,10);
      tmpAction=scriptStandard->addAction("(float)");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,11);
      tmpAction=scriptStandard->addAction("(string)");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,12);

      tmpAction=scriptStandard->addAction(";");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,13);
      tmpAction=scriptStandard->addAction("{");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,14);
      tmpAction=scriptStandard->addAction("}");
      connect(tmpAction,SIGNAL(triggered()),scriptStandardMapper,SLOT(map()));
      scriptStandardMapper->setMapping(tmpAction,15);

      tmpAction=scriptText->addAction("print");
      connect(tmpAction,SIGNAL(triggered()),scriptTextMapper,SLOT(map()));
      scriptTextMapper->setMapping(tmpAction,1);
      tmpAction=scriptText->addAction("clear");
      connect(tmpAction,SIGNAL(triggered()),scriptTextMapper,SLOT(map()));
      scriptTextMapper->setMapping(tmpAction,2);
      tmpAction=scriptText->addAction("setcursor");
      connect(tmpAction,SIGNAL(triggered()),scriptTextMapper,SLOT(map()));
      scriptTextMapper->setMapping(tmpAction,3);

      tmpAction=scriptText->addAction("getline");
      connect(tmpAction,SIGNAL(triggered()),scriptTextMapper,SLOT(map()));
      scriptTextMapper->setMapping(tmpAction,4);
      tmpAction=scriptText->addAction("getkey");
      connect(tmpAction,SIGNAL(triggered()),scriptTextMapper,SLOT(map()));
      scriptTextMapper->setMapping(tmpAction,5);
      tmpAction=scriptText->addAction("keystate");
      connect(tmpAction,SIGNAL(triggered()),scriptTextMapper,SLOT(map()));
      scriptTextMapper->setMapping(tmpAction,6);

      tmpAction=scriptGraphics->addAction("drawpoint");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,1);
      tmpAction=scriptGraphics->addAction("drawline");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,2);
      tmpAction=scriptGraphics->addAction("drawrect");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,3);
      tmpAction=scriptGraphics->addAction("drawcircle");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,4);
      tmpAction=scriptGraphics->addAction("drawstring");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,5);
      tmpAction=scriptGraphics->addAction("drawcolor");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,6);
      tmpAction=scriptGraphics->addAction("drawclear");
      connect(tmpAction,SIGNAL(triggered()),scriptGraphicsMapper,SLOT(map()));
      scriptGraphicsMapper->setMapping(tmpAction,7);

      tmpAction=scriptGL->addAction("glbegin");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,1);
      tmpAction=scriptGL->addAction("glendlist");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,2);
      tmpAction=scriptGL->addAction("glend");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,3);
      tmpAction=scriptGL->addAction("glshow");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,4);
      tmpAction=scriptGL->addAction("glclear");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,5);

      tmpAction=scriptGL->addAction("glloadidentity");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,6);
      tmpAction=scriptGL->addAction("glstartlist");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,7);
      tmpAction=scriptGL->addAction("glcalllist");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,8);
      tmpAction=scriptGL->addAction("glpoint");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,9);
      tmpAction=scriptGL->addAction("glscale");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,10);

      scriptGL->insertItem("glmove",11);
      scriptGL->insertItem("glrotate",12);
      scriptGL->insertItem("glcolor",13);
      scriptGL->insertItem("glstring",14);

      tmpAction=scriptGL->addAction("glmove");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,11);
      tmpAction=scriptGL->addAction("glrotate");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,12);
      tmpAction=scriptGL->addAction("glcolor");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,13);
      tmpAction=scriptGL->addAction("glstring");
      connect(tmpAction,SIGNAL(triggered()),scriptGLMapper,SLOT(map()));
      scriptGLMapper->setMapping(tmpAction,14);


      tmpAction=scriptFile->addAction("readfile");
      connect(tmpAction,SIGNAL(triggered()),scriptFileMapper,SLOT(map()));
      scriptFileMapper->setMapping(tmpAction,1);
      tmpAction=scriptFile->addAction("writefile");
      connect(tmpAction,SIGNAL(triggered()),scriptFileMapper,SLOT(map()));
      scriptFileMapper->setMapping(tmpAction,2);
      tmpAction=scriptFile->addAction("removefile");
      connect(tmpAction,SIGNAL(triggered()),scriptFileMapper,SLOT(map()));
      scriptFileMapper->setMapping(tmpAction,3);
      tmpAction=scriptFile->addAction("appendfile");
      connect(tmpAction,SIGNAL(triggered()),scriptFileMapper,SLOT(map()));
      scriptFileMapper->setMapping(tmpAction,4);

      scriptStandard->setTitle(tr("Script Standard"));
      addMenu(scriptStandard);
      scriptText->setTitle(tr("Script Text"));
      addMenu(scriptText);
      scriptGraphics->setTitle(tr("Script Graphics"));
      addMenu(scriptGraphics);
      scriptGL->setTitle(tr("Script GL"));
      addMenu(scriptGL);
      scriptFile->setTitle(tr("Script File"));
      addMenu(scriptFile);

    }

    QObject::connect(mathStandardMapper,SIGNAL(mapped(int)),this,SLOT(mathStandardSlot(int)));
    QObject::connect(mathTrigonometricMapper,SIGNAL(mapped(int)),this,SLOT(mathTrigonometricSlot(int)));
    QObject::connect(mathExtendedMapper,SIGNAL(mapped(int)),this,SLOT(mathExtendedSlot(int)));
    QObject::connect(mathLogicMapper,SIGNAL(mapped(int)),this,SLOT(mathLogicSlot(int)));
    QObject::connect(matrixMapper,SIGNAL(mapped(int)),this,SLOT(matrixSlot(int)));
    QObject::connect(scriptStandardMapper,SIGNAL(mapped(int)),this,SLOT(scriptStandardSlot(int)));
    QObject::connect(scriptTextMapper,SIGNAL(mapped(int)),this,SLOT(scriptTextSlot(int)));
    QObject::connect(scriptGraphicsMapper,SIGNAL(mapped(int)),this,SLOT(scriptGraphicsSlot(int)));
    QObject::connect(scriptGLMapper,SIGNAL(mapped(int)),this,SLOT(scriptGLSlot(int)));
    QObject::connect(scriptFileMapper,SIGNAL(mapped(int)),this,SLOT(scriptFileSlot(int)));
    QObject::connect(constantsMapper,SIGNAL(mapped(int)),this,SLOT(constantsSlot(int)));

    QObject::connect(cDialog,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));


  }


void Catalog::mathStandardSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("+");
			break;
		case 2:
			emit menuSignal("-");
			break;
		case 3:
			emit menuSignal("*");
			break;
		case 4:
			emit menuSignal("/");
			break;
		case 5:
			emit menuSignal("^2");
			break;
		case 6:
			emit menuSignal("^3");
			break;
		case 7:
			emit menuSignal("^-1");
			break;
		case 8:
			emit menuSignal("^");
			break;
		case 9:
			emit menuSignal("sqrt");
			break;
		case 10:
			emit menuSignal("curt");
			break;
		case 11:
			emit menuSignal("root");
			break;
		case 12:
			emit menuSignal("log");
			break;
		case 13:
			emit menuSignal("ln");
			break;
		case 14:
			emit menuSignal("->");
			break;
		case 15:
			emit menuSignal("=");
			break;
	}
}

void Catalog::mathTrigonometricSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("sin");
			break;
		case 2:
			emit menuSignal("cos");
			break;
		case 3:
			emit menuSignal("tan");
			break;
		case 4:
			emit menuSignal("asin");
			break;
		case 5:
			emit menuSignal("acos");
			break;
		case 6:
			emit menuSignal("atan");
			break;
		case 7:
			emit menuSignal("sinh");
			break;
		case 8:
			emit menuSignal("cosh");
			break;
		case 9:
			emit menuSignal("tanh");
			break;
		case 10:
			emit menuSignal("asinh");
			break;
		case 11:
			emit menuSignal("acosh");
			break;
		case 12:
			emit menuSignal("atanh");
			break;

	}
}

void Catalog::mathLogicSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("&&");
			break;
		case 2:
			emit menuSignal("||");
			break;
		case 3:
			emit menuSignal("!");
			break;
		case 4:
			emit menuSignal("==");
			break;
		case 5:
			emit menuSignal(">=");
			break;
		case 6:
			emit menuSignal("<=");
			break;
		case 7:
			emit menuSignal("!=");
			break;
		case 8:
			emit menuSignal(">");
			break;
		case 9:
			emit menuSignal("<");
			break;
		case 10:
			emit menuSignal("&");
			break;
		case 11:
			emit menuSignal("|");
			break;
		case 12:
			emit menuSignal("~");
			break;
		case 13:
			emit menuSignal("<<");
			break;
		case 14:
			emit menuSignal(">>");
			break;
	}
}


void Catalog::mathExtendedSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("abs");
			break;
		case 2:
			emit menuSignal("arg");
			break;
		case 3:
			emit menuSignal("conj");
			break;
		case 4:
			emit menuSignal("real");
			break;
		case 5:
			emit menuSignal("imag");
			break;
		case 6:
			emit menuSignal("!");
			break;
		case 7:
			emit menuSignal("%");
			break;
		case 8:
			emit menuSignal("rnd(<max>)");
			break;
		case 9:
			emit menuSignal("d/dx(<f(x)>,<value>)");
			break;
		case 10:
			emit menuSignal("integ(<f(x)>,<start>,<end>)");
			break;
	}
}

	
void Catalog::matrixSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("[<index>]");
			break;
		case 2:
			emit menuSignal("sprod");
			break;
		case 3:
			emit menuSignal("^-1");
			break;
	}
}

	
void Catalog::scriptStandardSlot(int id)
{

	switch(id)
	{
		case 1:
			emit menuSignal("if(<exp>) then <exp> else <exp>");
			break;
		case 2:
			emit menuSignal("for(<exp>;<exp>;<exp>)<exp>");
			break;
		case 3:
			emit menuSignal("while(<exp>)<exp>");
			break;
		case 4:
			emit menuSignal("break");
			break;
		case 5:
			emit menuSignal("continue");
			break;
		case 6:
			emit menuSignal("stop");
			break;
		case 7:
			emit menuSignal("sleep(<usec>)");
			break;
		case 8:
			emit menuSignal("run(<path>)");
			break;
		case 9:
			emit menuSignal("(bool)");
			break;
		case 10:
			emit menuSignal("(int)");
			break;
		case 11:
			emit menuSignal("(float)");
			break;
		case 12:
			emit menuSignal("(string)");
			break;
		case 13:
			emit menuSignal(";");
			break;
		case 14:
			emit menuSignal("{");
			break;
		case 15:
			emit menuSignal("}");
			break;
	}
}

void Catalog::scriptTextSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("print(<text>)");
			break;
		case 2:
			emit menuSignal("clear(");
			break;
		case 3:
			emit menuSignal("setcursor(<row>,<col>)");
			break;
		case 4:
			emit menuSignal("getline");
			break;
		case 5:
			emit menuSignal("getkey");
			break;
		case 6:
			emit menuSignal("keystate");
			break;
	}
}

void Catalog::scriptGraphicsSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("drawpoint(<x>,<y>)");
			break;
		case 2:
			emit menuSignal("drawline(<x start>,<y start>,<x end>,<y end>)");
			break;
		case 3:
			emit menuSignal("drawrect(<x start>,<y start>,<x end>,<y end>)");
			break;
		case 4:
			emit menuSignal("drawcircle(<x start>,<y start>,<x end>,<y end>)");
			break;
		case 5:
			emit menuSignal("drawstring(<x>,<y>,<text>)");
			break;
		case 6:
			emit menuSignal("drawcolor(<r>,<g>,<b>)");
			break;
		case 7:
			emit menuSignal("drawclear");
			break;
	}
}

void Catalog::scriptGLSlot(int id)
{

	switch(id)
	{
		case 1:
			emit menuSignal("glbegin(<type>)");
			break;
		case 2:
			emit menuSignal("glendlist");
			break;
		case 3:
			emit menuSignal("glend");
			break;
		case 4:
			emit menuSignal("glshow");
			break;
		case 5:
			emit menuSignal("glclear");
			break;
		case 6:
			emit menuSignal("glloadidentity");
			break;
		case 7:
			emit menuSignal("glstartlist");
			break;
		case 8:
			emit menuSignal("glcalllist");
			break;
		case 9:
			emit menuSignal("glpoint(<x>,<y>,<z>)");
			break;
		case 10:
			emit menuSignal("glscale(<x>,<y>,<z>)");
			break;
		case 11:
			emit menuSignal("glmove(<x>,<y>,<z>)");
			break;
		case 12:
			emit menuSignal("glrotate(<x>,<y>,<z>)");
			break;
		case 13:
			emit menuSignal("glcolor(<r>,<g>,<b>)");
			break;
		case 14:
			emit menuSignal("glstring(<x>,<y>,<text>)");
			break;
	}
}

void Catalog::scriptFileSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("readfile(<path>)");
			break;
		case 2:
			emit menuSignal("writefile(<path>,<content>)");
			break;
		case 3:
			emit menuSignal("removefile(<path>)");
			break;
		case 4:
			emit menuSignal("appendfile(<path>,<content>)");
			break;
	}
}


void Catalog::constantsSlot(int id)
{
	if(id<pref.constLen)
		emit menuSignal(*(pref.constList[id].identifier));
	else 
	{
		cDialog->exec();
		
	}
}


void Catalog::setPref(Preferences newPref)
{
	pref=newPref;
	cDialog->setPref(pref);
  QList<QAction*>actions;
  QAction*tmpAction;

	if(state&CATCONSTANTS)
	{

    actions=constantsMath->actions();
    actions.append(constantsPhysics->actions());
    actions.append(constantsConv->actions());
    actions.append(constantsUser->actions());


    for(int c=0; c<actions.length(); c++)
      actions[c]->disconnect();


		constantsMath->clear();
		constantsPhysics->clear();
		constantsConv->clear();
		constantsUser->clear();

		
		mathConstLen=3;
		physicsConstLen=20;
		convConstLen=8;

				
		for(int c=0; c<mathConstLen && c<pref.constLen; c++)
    {
      tmpAction=constantsMath->addAction(*(pref.constList[c].description));
      connect(tmpAction,SIGNAL(triggered()),constantsMapper,SLOT(map()));
      constantsMapper->setMapping(tmpAction,c);
    }
				
		for(int c=0; c<physicsConstLen && c+mathConstLen<pref.constLen; c++)
    {
      tmpAction=constantsPhysics->addAction(*(pref.constList[c+mathConstLen].description));
      connect(tmpAction,SIGNAL(triggered()),constantsMapper,SLOT(map()));
      constantsMapper->setMapping(tmpAction,c+mathConstLen);
    }
				
		for(int c=0; c<convConstLen && c+mathConstLen+physicsConstLen<pref.constLen; c++)
    {
      tmpAction=constantsConv->addAction(*(pref.constList[c+mathConstLen+physicsConstLen].description));
      connect(tmpAction,SIGNAL(triggered()),constantsMapper,SLOT(map()));
      constantsMapper->setMapping(tmpAction,c+mathConstLen+physicsConstLen);
    }

    tmpAction=constantsUser->addAction(tr("add"));
    connect(tmpAction,SIGNAL(triggered()),constantsMapper,SLOT(map()));
    constantsMapper->setMapping(tmpAction,pref.constLen);

		for(int c=0; c<pref.userConstLen; c++)
    {
      tmpAction=constantsUser->addAction(*(pref.constList[c+pref.constLen-pref.userConstLen].description));
      connect(tmpAction,SIGNAL(triggered()),constantsMapper,SLOT(map()));
      constantsMapper->setMapping(tmpAction,c+pref.constLen-pref.userConstLen);
    }
	}
}

ConstantDialog::ConstantDialog(QWidget*parent,QString name,Preferences p) :QDialog(parent,name,true)
{
	pref=p;
	setCaption(tr("Change Constants"));

	constLabel=new QLabel(tr("Choose Constant"),this);
	descriptionLabel=new QLabel(tr("Description"),this);
	valueLabel=new QLabel(tr("Value"),this);
	identifierLabel=new QLabel(tr("Identifier"),this);

	descriptionLine=new QLineEdit(this);
	valueLine=new QLineEdit(this);
	identifierLine=new QLineEdit(this);
	identifierLine->setReadOnly(true);

	variablesBox=new Q3ListBox(this);

	okButton=new QPushButton(tr("OK"),this);
	cancelButton=new QPushButton(tr("Cancel"),this);
	addButton=new QPushButton(tr("Apply"),this);
	removeButton=new QPushButton(tr("Remove"),this);

	setGeometry(0,0,400,400);
	constLabel->setGeometry(20,20,260,20);
	variablesBox->setGeometry(20,50,160,280);

	identifierLabel->setGeometry(200,50,180,20);
	identifierLine->setGeometry(200,80,180,20);

	descriptionLabel->setGeometry(200,125,180,20);
	descriptionLine->setGeometry(200,155,180,20);

	valueLabel->setGeometry(200,200,180,20);
	valueLine->setGeometry(200,230,180,20);

	addButton->setGeometry(220,260,75,20);
	removeButton->setGeometry(305,260,75,20);

	okButton->setGeometry(210,350,80,30);
	cancelButton->setGeometry(300,350,80,30);

	connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
	connect(removeButton,SIGNAL(clicked()),this,SLOT(removeSlot()));
	connect(addButton,SIGNAL(clicked()),this,SLOT(applySlot()));
	connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
	connect(variablesBox,SIGNAL(currentChanged(Q3ListBoxItem*)),this,SLOT(boxSlot()));

	setPref(pref);
}

void ConstantDialog::boxSlot()
{
	int i = variablesBox->currentItem();
	if(i==0)
	{
		descriptionLine->setText("");
		valueLine->setText("");
		identifierLine->setText("c_usr"+QString::number(pref.userConstLen+1));
	}
	else 
	{
		identifierLine->setText("c_usr"+QString::number(i));
		descriptionLine->setText(*(pref.constList[i-1+pref.constLen-pref.userConstLen].description));
		valueLine->setText(*(pref.constList[i-1+pref.constLen-pref.userConstLen].value));
	}
}

void ConstantDialog::applySlot()
{
	if(variablesBox->currentItem()==0 && descriptionLine->text().length()>0)
	{
		pref.constList=(Constant*)realloc(pref.constList,sizeof(Constant)*(pref.constLen+1));
		pref.constLen++;
		pref.userConstLen++;
		pref.constList[pref.constLen-1].description=new QString(descriptionLine->text());
		pref.constList[pref.constLen-1].value=new QString(valueLine->text());
		pref.constList[pref.constLen-1].identifier=new QString("c_usr"+QString::number(pref.userConstLen));
			
	}
	else if(variablesBox->currentItem()>0)
	{
		int i=variablesBox->currentItem()-1;
		*(pref.constList[pref.constLen-pref.userConstLen+i].description)=descriptionLine->text();
		*(pref.constList[pref.constLen-pref.userConstLen+i].value)=valueLine->text();
	}
	else if(variablesBox->currentItem()==-1)
	{
		variablesBox->setCurrentItem(0);
	}
	emit prefChange(pref);
}

void ConstantDialog::removeSlot()
{
	if(variablesBox->currentItem()!=0)
	{
		int i=variablesBox->currentItem()-1;
		delete pref.constList[pref.constLen-pref.userConstLen+i].description;
		delete pref.constList[pref.constLen-pref.userConstLen+i].identifier;
		delete pref.constList[pref.constLen-pref.userConstLen+i].value;
		for(int c=i+pref.constLen-pref.userConstLen+1; c<pref.constLen; c++)
			pref.constList[c-1]=pref.constList[c];
		pref.constLen--;
		pref.userConstLen--;
		pref.constList=(Constant*)realloc(pref.constList,sizeof(Constant)*(pref.constLen));
	}
	emit prefChange(pref);
}


void ConstantDialog::setPref(Preferences newPref)
{
	pref=newPref;
	variablesBox->clear();
	variablesBox->insertItem(tr("New"));
	if(pref.constList!=NULL)
	{
	for(int c=pref.constLen-pref.userConstLen; c<pref.constLen; c++)
		variablesBox->insertItem(*(pref.constList[c].description));
	}
}






