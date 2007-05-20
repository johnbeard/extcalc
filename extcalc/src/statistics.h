#ifndef STATISTICS_H
#define STATISTICS_H


#include <qwidget.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qsplitter.h>
#include <qpushbutton.h>
#include "functiontable.h"
#include "buttons.h"

#define LISTCOUNT		5

/*
- approximation
  - const
  - line
  - e-function
  - log
  - sin
- interpolation (newton)
- Gaussian distribution
- bar graph
- points
- lines
- normal propability distribution calculations
*/




class StatisticsWidget :public QWidget
{
	Preferences pref;
	ThreadSync*threadData;
	Variable*vars;
	FunctionTable *functionTable;
	StandardButtons *standardButtons;
	QTable *lists;
	QSplitter *splitter;
	QComboBox *typeBox, *functionTypeBox,*copyFunction,*listNumberBox;
	QSpinBox *listNumber;
	QPushButton *calculateButton,*maximizeButton,*drawButton,*copyButton;
	QLabel *listNumberLabel,*resultLabel,*copyFunctionLabel,*functionTypeLabel;
	QLineEdit * result;
	
	bool print;

	bool fullscreen;
	int type;

	Q_OBJECT
	public:
		StatisticsWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td) :QWidget(parent)
		{
			pref=p;
			threadData=td;
			vars=va;
			fullscreen=false;
			type=STATAPPROX;
			print=false;

			splitter=new QSplitter(Qt::Horizontal,this);
			functionTable=new FunctionTable(splitter,pref);
			standardButtons=new StandardButtons(this);
			lists=new QTable(splitter);
			lists->setNumRows(1);
			lists->setNumCols(2*LISTCOUNT);
			typeBox=new QComboBox(this);
			functionTypeLabel=new QLabel("Function Type",this);
			functionTypeBox=new QComboBox(this);
			listNumber=new QSpinBox(1,LISTCOUNT,1,this);
			listNumberLabel=new QLabel("Input List Number",this);
			resultLabel=new QLabel("Result Function",this);
			result=new QLineEdit(this);
			for(int c=0; c<5; c++)
			{
				lists->horizontalHeader()->setLabel(2*c,"X"+QString::number(c+1));
				lists->horizontalHeader()->setLabel(2*c+1,"Y"+QString::number(c+1));
			}

			copyFunctionLabel=new QLabel("Copy to",this);
			copyFunction=new QComboBox(this);
			copyButton=new QPushButton("Copy",this);
			for(int c=0; c<20; c++)
				copyFunction->insertItem("f"+QString::number(c+1)+"(x)");
			
			listNumberBox=new QComboBox(this);
			for(int c=0; c<LISTCOUNT; c++)
			{
				listNumberBox->insertItem("X"+QString::number(c+1));
				listNumberBox->insertItem("Y"+QString::number(c+1));
			}

			functionTypeBox->insertItem("const");
			functionTypeBox->insertItem("x");
			functionTypeBox->insertItem("x^2");
			functionTypeBox->insertItem("x^3");
			functionTypeBox->insertItem("x^4");
			functionTypeBox->insertItem("x^5");
			functionTypeBox->insertItem("x^6");

			typeBox->insertItem("Approximate");
			typeBox->insertItem("Interpolate");
			typeBox->insertItem("Show Line-Graph");
			typeBox->insertItem("Normal Distribution");
			typeBox->insertItem("Distribution Graph");


			calculateButton=new QPushButton("Calculate",this);
			maximizeButton=new QPushButton("Maximize",this);
			drawButton=new QPushButton("Print",this);
			readListsFile();

			typeBoxSlot(0);
			QObject::connect(functionTable,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
			QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeButtonSlot()));
			QObject::connect(calculateButton,SIGNAL(clicked()),this,SLOT(calculateButtonSlot()));
			QObject::connect(copyButton,SIGNAL(clicked()),this,SLOT(copyButtonSlot()));
			QObject::connect(drawButton,SIGNAL(clicked()),this,SLOT(printButtonSlot()));
			QObject::connect(typeBox,SIGNAL(activated(int)),this,SLOT(typeBoxSlot(int)));
			QObject::connect(lists,SIGNAL(valueChanged(int,int)),this,SLOT(itemChangedSlot(int,int)));
			QObject::connect(standardButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
			QObject::connect(standardButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		}

		void setPref(Preferences);
		void writeListsFile();
		void readListsFile();

	public slots:
		void getPref(Preferences);
		void maximizeButtonSlot();
		void typeBoxSlot(int);
		void calculateButtonSlot();
		void itemChangedSlot(int,int);
		void copyButtonSlot();
		void printButtonSlot();
		void buttonInputSlot(QString);

	protected:
		void resizeEvent(QResizeEvent*);

	signals:
		void prefChange(Preferences);
		void printSignal();
		void changeTabSignal(int);
		void drawPointsSignal(long double*,int,bool);
		void removeLinesSignal();

};

#endif


