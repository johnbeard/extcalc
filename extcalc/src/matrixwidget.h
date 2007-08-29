/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         matrixwidget.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

The class of the matrix/vector tab window.
Includes the matrix/vector window GUI and all needed math. functions.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H


#include <qwidget.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qtoolbar.h>
#include <qdockarea.h>
#include <qiconset.h>
#include <qpopupmenu.h>
#include <qtooltip.h>
#include <qsplitter.h>
#include "buttons.h"
#include "calcinput.h"
#include "calctable.h"
#include "catalog.h"





class MatrixWidget :public QWidget
{
	Preferences pref;
	ThreadSync*threadData;
	Variable*vars;
	StandardButtons *standardButtons;
	CalcTable*outputTable;
	CalcTable*varTable;
	CalcTable*resultTable;
	QPushButton*sprodButton,*invertButton,*detButton;
	QComboBox*operationBox;
	QSpinBox *size1Box,*size2Box;
	QComboBox *matrixBox,*vectorBox,*typeBox;
	QLabel *matrixLabel,*vectorLabel,*size1Label,*size2Label,*label1,*label2,*label3;
	QLineEdit *input1,*input2,*input3;
	QPushButton *calcButton,*sizeButton,*catalogButton;

	QToolBar*toolBar;
	QDockArea*dockArea;
	QPixmap *catalogIcon;
	Catalog *catalog;
	QSplitter *split;

	CalcInput*calcWidget;
	int currentVar;
	int state;
	bool fullscreen;

	Q_OBJECT
	public:
		MatrixWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td) :QWidget(parent)
		{
			pref=p;
			threadData=td;
			vars=va;
			currentVar=0;
			state=MATCALC;
			
			split=new QSplitter(Qt::Horizontal,this);
			standardButtons=new StandardButtons(this);
			varTable=new CalcTable(split,0,true);
			outputTable=new CalcTable(split,0,true);
			outputTable->setNumRows(10);
			outputTable->setNumCols(4);
			
			
			catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX | CATMATRIX,this);
	
			catalogIcon=new QPixmap(INSTALLDIR+QString("/data/catalog.png"));
			
			dockArea=new QDockArea(Qt::Horizontal,QDockArea::Normal,this);
			toolBar=new QToolBar();
			dockArea->moveDockWindow(toolBar);
			
			
			varTable->setNumRows(27);
			varTable->setNumCols(3);
			QString headLine("A");
			for(int c=0; c<26; c++)
			{
				headLine[0]=(char)(c+65);
				varTable->verticalHeader()->setLabel(c,headLine);
			}
			varTable->verticalHeader()->setLabel(26,"ans");
			varTable->horizontalHeader()->setLabel(0,MATRIXWIDGETH_STR1);
			varTable->horizontalHeader()->setLabel(1,MATRIXWIDGETH_STR2);
			varTable->horizontalHeader()->setLabel(2,MATRIXWIDGETH_STR3);
			varTable->setSelectionMode(QTable::SingleRow);
			varTable->selectRow(currentVar);
			varTable->setColumnReadOnly(0,true);
			setVarTable();
			
			operationBox=new QComboBox(toolBar);
			sprodButton=new QPushButton(getUnicode(DEGREESTRING),toolBar);
			invertButton=new QPushButton(getUnicode(8315)+getUnicode(185),toolBar);
			detButton=new QPushButton("det",toolBar);
			catalogButton=new QPushButton(*catalogIcon,"",toolBar);
			
			
			operationBox->insertItem(MATRIXWIDGETH_STR4);
			operationBox->insertItem(MATRIXWIDGETH_STR5);
			operationBox->insertItem(MATRIXWIDGETH_STR6);
			operationBox->insertItem(MATRIXWIDGETH_STR7);
			operationBox->insertItem(MATRIXWIDGETH_STR8);

			calcWidget=new CalcInput(this,vars,threadData,true);
			size1Box=new QSpinBox(1,20,1,this);
			size2Box=new QSpinBox(1,20,1,this);
			size1Label=new QLabel(" ",this);
			size2Label=new QLabel(" ",this);
			matrixLabel=new QLabel(" ",this);
			vectorLabel=new QLabel(" ",this);
			label1=new QLabel(" ",this);
			label2=new QLabel(" ",this);
			label3=new QLabel(" ",this);
			input1=new QLineEdit(this);
			input2=new QLineEdit(this);
			input3=new QLineEdit(this);
			calcButton=new QPushButton(MATRIXWIDGETH_STR9,this);
			sizeButton=new QPushButton(MATRIXWIDGETH_STR10,this);
			resultTable=new CalcTable(this,0,true);
			matrixBox=new QComboBox(this);
			vectorBox=new QComboBox(this);
			
			QValueList<int> s = split->sizes();
			s[1]=150;
			s[0]=450;
			split->setSizes(s);
			invertButton->setFixedWidth(30);
			detButton->setFixedWidth(30);
			sprodButton->setFixedWidth(30);
			
			vectorBox->insertItem(MATRIXWIDGETH_STR11);
			for(int c=0; c<26; c++)
			{
				headLine[0]=(char)(c+65);
				matrixBox->insertItem(headLine);
				vectorBox->insertItem(headLine);
			}
			typeBox=new QComboBox(this);
			typeBox->insertItem(MATRIXWIDGETH_STR12);
			typeBox->insertItem(MATRIXWIDGETH_STR13);
			typeBox->insertItem(MATRIXWIDGETH_STR14);
			typeBox->insertItem(MATRIXWIDGETH_STR15);
			typeBox->insertItem(MATRIXWIDGETH_STR16);
			typeBox->insertItem(MATRIXWIDGETH_STR17);
			typeBox->insertItem(MATRIXWIDGETH_STR18);
			resetInterface();



			QObject::connect(standardButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(sprodButton,SIGNAL(clicked()),this,SLOT(sprodButtonSlot()));
			QObject::connect(invertButton,SIGNAL(clicked()),this,SLOT(invertButtonSlot()));
			QObject::connect(detButton,SIGNAL(clicked()),this,SLOT(detButtonSlot()));
			QObject::connect(operationBox,SIGNAL(activated(int)),this,SLOT(operationBoxSlot(int)));
			QObject::connect(calcWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(standardButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
			QObject::connect(varTable,SIGNAL(currentChanged(int,int)),this,SLOT(varSelectionSlot(int,int)));
			QObject::connect(varTable,SIGNAL(valueChanged(int,int)),this,SLOT(varChangedSlot(int,int)));
			QObject::connect(outputTable,SIGNAL(valueChanged(int,int)),this,SLOT(outputChangedSlot(int,int)));
			QObject::connect(calcWidget,SIGNAL(calcSignal()),this,SLOT(enterSlot()));
			QObject::connect(calcButton,SIGNAL(pressed()),this,SLOT(calcButtonSlot()));
			QObject::connect(matrixBox,SIGNAL(activated(int)),this,SLOT(matrixBoxSlot(int)));
			QObject::connect(vectorBox,SIGNAL(activated(int)),this,SLOT(vectorBoxSlot(int)));
			QObject::connect(typeBox,SIGNAL(activated(int)),this,SLOT(typeBoxSlot(int)));
			QObject::connect(size1Box,SIGNAL(valueChanged(int)),this,SLOT(size1BoxSlot(int)));
			QObject::connect(sizeButton,SIGNAL(pressed()),this,SLOT(sizeButtonSlot()));
			QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(buttonInputSlot(QString)));
			QObject::connect(catalogButton,SIGNAL(clicked()),this,SLOT(catalogSlot()));
			
		}
	
		void setPref(Preferences);
	
		void setVarTable();
		void setOutputTable(int num);
		void resizeVar(int var,int rows,int cols);
		void resetInterface();
		void setHeader(CalcTable*);
	
	public slots:
		void getPref(Preferences);
		void sprodButtonSlot();
		void invertButtonSlot();
		void detButtonSlot();
		void operationBoxSlot(int);
		void enterSlot();
		void buttonInputSlot(QString);
		void varSelectionSlot(int,int);
		void varChangedSlot(int,int);
		void outputChangedSlot(int,int);
		void calcButtonSlot();
		void matrixBoxSlot(int);
		void vectorBoxSlot(int);
		void size1BoxSlot(int);
		void sizeButtonSlot();
		void typeBoxSlot(int);
		void catalogSlot();
	
	protected:
		virtual void resizeEvent(QResizeEvent*);
	
	
	signals:
		void prefChange(Preferences);
	
};

#endif
