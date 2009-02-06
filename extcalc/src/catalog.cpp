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
	if(state&CATCONSTANTS)
	{
		constantsMath->clear();
		constantsPhysics->clear();
		constantsConv->clear();
		constantsUser->clear();
		
		mathConstLen=3;
		physicsConstLen=20;
		convConstLen=8;

				
		for(int c=0; c<mathConstLen && c<pref.constLen; c++)
			constantsMath->insertItem(*(pref.constList[c].description),c);
				
		for(int c=0; c<physicsConstLen && c+mathConstLen<pref.constLen; c++)
			constantsPhysics->insertItem(*(pref.constList[c+mathConstLen].description),c+mathConstLen);
				
		for(int c=0; c<convConstLen && c+mathConstLen+physicsConstLen<pref.constLen; c++)
			constantsConv->insertItem(*(pref.constList[c+mathConstLen+physicsConstLen].description),c+mathConstLen+physicsConstLen);
		
		constantsUser->insertItem("add",pref.constLen);
		
		for(int c=0; c<pref.userConstLen; c++)
			constantsUser->insertItem(*(pref.constList[c+pref.constLen-pref.userConstLen].description),c+pref.constLen-pref.userConstLen);

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






