#ifndef TABLEH
#define TABLEH 

#include <qwidget.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include "functiontable.h"
#include "buttons.h"





class TableWidget :public QWidget
{
	
	Preferences pref;
	ExtButtons *extButtons;
	StandardButtons *standardButtons;
	FunctionTable* functionTable;
	QLineEdit*inputLine;
	CalcTable*outputTable;
	QPushButton*calculateButton,*maximizeButton;
	QComboBox*typeBox;
	Variable*vars;
	bool fullscreen;
	
	Q_OBJECT
public:
	TableWidget(QWidget*parent,Preferences p,Variable*va) :QWidget(parent)
	{
		pref=p;
		vars=va;
		fullscreen=false;
		extButtons=new ExtButtons(this);
		standardButtons=new StandardButtons(this);
		functionTable=new FunctionTable(this,pref);
		inputLine=new QLineEdit(this);
		outputTable=new CalcTable(this,0,true);
		outputTable->setNumRows(10);
		outputTable->setNumCols(4);
		
		calculateButton=new QPushButton(TABLEH_STR1,this);
		maximizeButton=new QPushButton(TABLEH_STR2,this);
		typeBox=new QComboBox(this);
		
		typeBox->insertItem(TABLEH_STR3);
		typeBox->insertItem(TABLEH_STR4);
		typeBox->insertItem(TABLEH_STR5);
		typeBox->insertItem(TABLEH_STR6);
		typeBox->insertItem(TABLEH_STR7);
		
		QObject::connect(standardButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(functionTable,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(functionTable,SIGNAL(currentChanged(int,int)),this,SLOT(selectionChangedSlot(int,int)));
		QObject::connect(functionTable,SIGNAL(textEditStarted(QString)),this,SLOT(tableEditSlot(QString)));
		QObject::connect(inputLine,SIGNAL(returnPressed()),this,SLOT(inputTextChanged()));
		QObject::connect(inputLine,SIGNAL(lostFocus()),this,SLOT(inputTextChanged()));
		QObject::connect(calculateButton,SIGNAL(clicked()),this,SLOT(calculateButtonSlot()));
		QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeButtonSlot()));
		QObject::connect(standardButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(typeBox,SIGNAL(activated(const QString&)),this,SLOT(typeBoxSlot(const QString&)));
	}
	
	void setPref(Preferences);
	
public slots:
	void getPref(Preferences);
	void selectionChangedSlot(int row,int col);
	void tableEditSlot(QString);
	void inputTextChanged();
	void calculateButtonSlot();
	void typeBoxSlot(const QString&);
	void maximizeButtonSlot();
	void buttonInputSlot(QString);
	void editSlot(int);
	
protected:
	virtual void resizeEvent(QResizeEvent*);
	
	
signals:
	void prefChange(Preferences);
	
};






#endif





