#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H


#include <qwidget.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include "buttons.h"
#include "calcinput.h"
#include "calctable.h"





class MatrixWidget :public QWidget
{
	
	Preferences pref;
	ThreadSync*threadData;
	Variable*vars;
	StandardButtons *standardButtons;
	CalcTable*outputTable;
	CalcTable*varTable;
	QPushButton*sprodButton,*invertButton,*detButton;
	QComboBox*operationBox;

	CalcInput*calcWidget;
	int currentVar;
	bool fullscreen;
	
	Q_OBJECT
	public:
		MatrixWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td) :QWidget(parent)
		{
			pref=p;
			threadData=td;
			vars=va;
			currentVar=0;
			
			standardButtons=new StandardButtons(this);
			outputTable=new CalcTable(this,0,true);
			outputTable->setNumRows(10);
			outputTable->setNumCols(4);
			
			varTable=new CalcTable(this,0,true);
			varTable->setNumRows(27);
			varTable->setNumCols(3);
			QString headLine("A");
			for(int c=0; c<26; c++)
			{
				headLine[0]=(char)(c+65);
				varTable->verticalHeader()->setLabel(c,headLine);
			}
			varTable->verticalHeader()->setLabel(26,"ans");
			varTable->horizontalHeader()->setLabel(0,"Type");
			varTable->horizontalHeader()->setLabel(1,"Rows");
			varTable->horizontalHeader()->setLabel(2,"Columns");
			setVarTable();
			
			sprodButton=new QPushButton(getUnicode(DEGREESTRING),this);
			invertButton=new QPushButton("^-1",this);
			detButton=new QPushButton("det",this);
			operationBox=new QComboBox(this);
			operationBox->insertItem("Calculator");
			operationBox->insertItem("Inverse Matrix");
			operationBox->insertItem("Linear System of Equations");
			operationBox->insertItem("Polynomial Equations");
			operationBox->insertItem("Determinant");
			operationBox->insertItem("Matrix Transfomrations");
			operationBox->insertItem("Rank");
			
			calcWidget=new CalcInput(this,vars,threadData);


			QObject::connect(standardButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(sprodButton,SIGNAL(clicked()),this,SLOT(sprodButtonSlot()));
			QObject::connect(invertButton,SIGNAL(clicked()),this,SLOT(invertButtonSlot()));
			QObject::connect(detButton,SIGNAL(clicked()),this,SLOT(detButtonSlot()));
			QObject::connect(operationBox,SIGNAL(activated(const QString&)),this,SLOT(operationBoxSlot(const QString&)));
			QObject::connect(calcWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(standardButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		}
	
		void setPref(Preferences);
	
		void setVarTable();
		void setOutputTable(int num);
		
	
	public slots:
		void getPref(Preferences);
		void sprodButtonSlot();
		void invertButtonSlot();
		void detButtonSlot();
		void operationBoxSlot(const QString&);
		void enterSlot();
		void buttonInputSlot(QString);
	
	protected:
		virtual void resizeEvent(QResizeEvent*);
	
	
	signals:
		void prefChange(Preferences);
	
};











#endif
