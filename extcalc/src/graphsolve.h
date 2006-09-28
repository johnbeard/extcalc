#ifndef GRAPHSOLVEH
#define GRAPHSOLVEH

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qcolordialog.h>
#include "calctable.h"
#include "global.h"









class GraphSolveWidget :public QWidget
{

	Preferences pref;
	QLabel *xLabel,*x2Label,*x3Label,*yLabel,*aLabel,*formatLabel,*penLabel;
	QLineEdit*xLine,*x2Line,*aLine;
	QSpinBox*spinBox,*spinBox2,*spinBox3;
	CalcTable*outputTable;
	QPushButton*solveButton,*saveButton,*openButton;
	QPushButton*freeButton,*lineButton,*rectButton,*circleButton,*rubberButton;
	QPushButton*backButton,*forwardButton,*clearButton,*colorButton;
	QComboBox*functionBox,*functionBox2;
	QComboBox*formatBox;
	int solveType,solveOptions;
	Variable*vars;
	int*functionIndices;
	int functionType;
	bool aVisible;
	QPixmap *openIcon,*freeIcon,*lineIcon,*rectIcon,*circleIcon,*rubberIcon,*colorIcon;
	QColor paintColor;
	int drawState;
	
	
	Q_OBJECT
public:
	
	GraphSolveWidget(QWidget*parent,Preferences pr,Variable*va) :QWidget(parent)
	{
		aVisible=false;
		vars=va;
		pref=pr;
		functionType=GRAPHSTD;
		functionIndices=new int[20];
		xLabel=new QLabel(" ",this);
		x2Label=new QLabel(" ",this);
		x3Label=new QLabel(" ",this);
		yLabel=new QLabel(" ",this);
		aLabel=new QLabel(GRAPHSOLVEH_STR2,this);
		formatLabel=new QLabel(" ",this);
		penLabel = new QLabel("Width",this);
		xLine=new QLineEdit(this);
		x2Line=new QLineEdit(this);
		aLine=new QLineEdit(this);
		drawState=DRAWNONE;
		
		spinBox=new QSpinBox(1,10000,1,this);
		spinBox->setValue(5);
		spinBox2=new QSpinBox(1,10000,1,this);
		spinBox2->setValue(5);
		spinBox3=new QSpinBox(1,10,1,this);
		spinBox3->setValue(1);
		
		outputTable=new CalcTable(this,0);
//		outputTable->setDragEnabled(true);
		solveButton=new QPushButton(GRAPHSOLVEH_STR1,this);
		saveButton=new QPushButton("Save",this);
		functionBox=new QComboBox(this);
		functionBox2=new QComboBox(this);
		formatBox=new QComboBox(this);
		openButton=new QPushButton("",this);
		openIcon=new QPixmap(INSTALLDIR+QString("/data/open.png"));
		openButton->setPixmap(*openIcon);

		backButton=new QPushButton("Undo",this);
		forwardButton=new QPushButton("Redo",this);
		clearButton=new QPushButton("Clear",this);
		freeButton=new QPushButton("",this);
		rectButton=new QPushButton("",this);
		lineButton=new QPushButton("",this);
		circleButton=new QPushButton("",this);
		rubberButton=new QPushButton("",this);

		freeIcon=new QPixmap(INSTALLDIR+QString("/data/free.png"));
		rectIcon=new QPixmap(INSTALLDIR+QString("/data/rect.png"));
		lineIcon=new QPixmap(INSTALLDIR+QString("/data/line.png"));
		circleIcon=new QPixmap(INSTALLDIR+QString("/data/circle.png"));
		rubberIcon=new QPixmap(INSTALLDIR+QString("/data/rubber.png"));
		colorIcon=new QPixmap(20,20);
		paintColor.setRgb(255,0,0);
		colorIcon->fill(paintColor);
		colorButton=new QPushButton(*colorIcon,"Color",this);

		freeButton->setToggleButton(true); 
		rectButton->setToggleButton(true); 
		lineButton->setToggleButton(true); 
		circleButton->setToggleButton(true); 
		rubberButton->setToggleButton(true); 

		freeButton->setPixmap(*freeIcon);
		rectButton->setPixmap(*rectIcon);
		lineButton->setPixmap(*lineIcon);
		circleButton->setPixmap(*circleIcon);
		rubberButton->setPixmap(*rubberIcon);

		solveType=CALCYVAL;
		solveOptions=0;

		QObject::connect(solveButton,SIGNAL(clicked()),this,SLOT(solveButtonSlot()));
		QObject::connect(openButton,SIGNAL(clicked()),this,SLOT(openButtonSlot()));
		QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(solveButtonSlot()));
		QObject::connect(colorButton,SIGNAL(clicked()),this,SLOT(colorButtonSlot()));
		QObject::connect(spinBox3,SIGNAL(valueChanged(int)),this,SLOT(penValueSlot(int)));
		QObject::connect(forwardButton,SIGNAL(clicked()),this,SLOT(forwardButtonSlot()));
		QObject::connect(backButton,SIGNAL(clicked()),this,SLOT(backButtonSlot()));
		QObject::connect(clearButton,SIGNAL(clicked()),this,SLOT(clearButtonSlot()));
		QObject::connect(freeButton,SIGNAL(clicked()),this,SLOT(freeButtonSlot()));
		QObject::connect(lineButton,SIGNAL(clicked()),this,SLOT(lineButtonSlot()));
		QObject::connect(rectButton,SIGNAL(clicked()),this,SLOT(rectButtonSlot()));
		QObject::connect(circleButton,SIGNAL(clicked()),this,SLOT(circleButtonSlot()));
		QObject::connect(rubberButton,SIGNAL(clicked()),this,SLOT(rubberButtonSlot()));
		
		resetDialog();
	}
	

	void resetDialog();
//	void updateFunctions(QString*,int);
	void setPref(Preferences newPref);
	void calculateYVal(QString);
	int calculateRoots(QString,long double, long double,long double**,int varIndex);
	void showRoots(QString,QColor color);
	void calculateNewton(QString);
	void setFunctionBox(QComboBox*fBox);
	
protected:

	virtual void resizeEvent(QResizeEvent*);
	
	
public slots:
	void solveButtonSlot();
	void graphLMButtonPressed(double,double);
	void setState(int newSolveType);
	void setFunctionType(int fType);
	void screenshotSlot(QPixmap*);
	void openButtonSlot();
	void colorButtonSlot();
	void penValueSlot(int);
	void forwardButtonSlot();
	void backButtonSlot();
	void clearButtonSlot();
	void freeButtonSlot();
	void lineButtonSlot();
	void rectButtonSlot();
	void circleButtonSlot();
	void rubberButtonSlot();
	
signals:
	void addVerticalLine(double x);
	void addHorizontalLine(double y);
	void addPolarLine(double angle);
	void addCircle(double radius);
	void add3dXLine(double y,double z);
	void add3dYLine(double x,double z);
	void add3dZLine(double x,double y);
	void removeLines();
	void prefChange(Preferences);
	void drawInequaityIntersection(int, int);
	void redrawGraphs();
	void getScreenshotSignal(int,int);
	void drawSignal(int,QColor,int);
	
};















#endif

