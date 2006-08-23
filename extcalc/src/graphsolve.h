#ifndef GRAPHSOLVEH
#define GRAPHSOLVEH

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include "calctable.h"
#include "global.h"









class GraphSolveWidget :public QWidget
{

	Preferences pref;
	QLabel *xLabel,*x2Label,*x3Label,*yLabel,*aLabel;
	QLineEdit*xLine,*x2Line,*aLine;
	QSpinBox*spinBox;
	CalcTable*outputTable;
	QPushButton*solveButton;
	QComboBox*functionBox,*functionBox2;
	int solveType,solveOptions;
	Variable*vars;
	int*functionIndices;
	int functionType;
	bool aVisible;
	
	
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
		xLine=new QLineEdit(this);
		x2Line=new QLineEdit(this);
		aLine=new QLineEdit(this);
		
		spinBox=new QSpinBox(1,1000,1,this);
		spinBox->setValue(5);
		outputTable=new CalcTable(this,0);
//		outputTable->setDragEnabled(true);
		solveButton=new QPushButton(GRAPHSOLVEH_STR1,this);
		functionBox=new QComboBox(this);
		functionBox2=new QComboBox(this);
		solveType=CALCYVAL;
		solveOptions=0;
		
		QObject::connect(solveButton,SIGNAL(clicked()),this,SLOT(solveButtonSlot()));
		
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
	
};















#endif

