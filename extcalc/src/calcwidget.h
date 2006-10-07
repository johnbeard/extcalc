#ifndef CALCWIDGETH
#define CALCWIDGETH



#include "buttons.h"
#include "calcinput.h"
#include <qcombobox.h>



class CalcWidget :public QWidget
{
	CalcInput*textEdit;
	StandardButtons*calcButtons;
	ExtButtons*extButtons;
	Preferences pref;
	QPushButton*maximizeButton,*baseButton;
	QComboBox*prefBox;
	bool maximized;
	Variable *vars;
	
	Q_OBJECT

//	QLabel *text1,*text2,*text3;
//	QLabel *num1,*num2,*num3,*num4;



	
	public:
	CalcWidget(QWidget*parent,Preferences p,Variable *va) :QWidget(parent)
	{
		vars=va;
		pref=p;
		maximized=false;	
		textEdit=new CalcInput(this,vars);
//		graph=new GraphOutput(this);
		calcButtons=new  StandardButtons(this);
		extButtons=new ExtButtons(this);
		maximizeButton=new QPushButton(CALCWIDGETH_STR1,this);
		baseButton=new QPushButton(CALCWIDGETH_STR3,this);
		prefBox=new QComboBox(this);
		
		prefBox->insertItem("DEG");
		prefBox->insertItem("RAD");
		prefBox->insertItem("GRA");
		if(pref.angle==DEG)
			prefBox->setCurrentItem(0);
		else if(pref.angle==RAD)
			prefBox->setCurrentItem(1);
		else prefBox->setCurrentItem(2);
			
			
		textEdit->setGeometry(20,50,600,310);
	
		calcButtons->setGeometry(20,380,280,200);
		extButtons->setGeometry(320,420,300,160);
		
		QObject::connect(calcButtons,SIGNAL(emitText(QString)),this,SLOT(processText(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(processText(QString)));
		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(calcButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(textEdit,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeSlot()));
		QObject::connect(baseButton,SIGNAL(clicked()),this,SLOT(baseSlot()));
		QObject::connect(prefBox,SIGNAL(activated(int)),this,SLOT(prefBoxSlot(int)));
		
	}
	
	void setPref(Preferences newPref)
	{
		pref=newPref;
		if(pref.calcType==SCIENTIFIC)
		{
			if(baseButton->text()!=CALCWIDGETH_STR3)
			{
				baseButton->setText(CALCWIDGETH_STR3);
				prefBox->clear();
				prefBox->insertItem("DEG");
				prefBox->insertItem("RAD");
				prefBox->insertItem("GRA");
			}
			if(pref.angle==DEG)
				prefBox->setCurrentItem(0);
			else if(pref.angle==RAD)
				prefBox->setCurrentItem(1);
			else prefBox->setCurrentItem(2);
			
		}
		else if(pref.calcType==BASE)
		{
			if(baseButton->text()!=CALCWIDGETH_STR2)
			{
				baseButton->setText(CALCWIDGETH_STR2);
				prefBox->clear();
				prefBox->insertItem("HEX");
				prefBox->insertItem("DEC");
				prefBox->insertItem("OCT");
				prefBox->insertItem("BIN");
			}
			if(pref.base==HEX)
				prefBox->setCurrentItem(0);
			else if(pref.base==DEC)
				prefBox->setCurrentItem(1);
			else if(pref.base==OCT)
				prefBox->setCurrentItem(2);
			else prefBox->setCurrentItem(3);
		}
		calcButtons->setPref(pref);
		extButtons->setPref(pref);
		textEdit->setPref(pref);
	}
	

protected:
	
	virtual void resizeEvent(QResizeEvent*);

	
public slots:

	void getPref(Preferences newPref);
	void maximizeSlot();
	void baseSlot();
	void prefBoxSlot(int);
	void editSlot(int);

	
	void processText(QString text)
	{
	if(text == "calculate")
		textEdit->calculateKey();
	else if(text == "backkey")
		textEdit->backKey();
	else if(text == "clearall")
		textEdit->clearAll();
	else {
		textEdit->setBold(false);
		textEdit->textInput(text);
		}
	}
signals:
	void prefChange(Preferences);
	void runScript(QString*);
};

 
#endif

