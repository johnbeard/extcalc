#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qtabwidget.h>
#include <qtabbar.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include "global.h"

//possible preferences:
//
//	- field of view: x-min x-max y-min y-max 
//	- field of view polar: max. radius max. angle
//	- raster, polar raster
//	- coordinate axes
//	- labels
//	- constant width-to-height ratio
//	- Raster size
//	- coordinate system types: standard, polar, 3D
//
//




class CoordinatePreferences :public QWidget
{
	QLabel*rectLabel,*xminLabel,*xmaxLabel,*yminLabel,*ymaxLabel;
	QLabel*polarLabel,*rasterSizeXLabel,*rasterSizeYLabel,*graphTypeLabel;
	QLabel*angleLabel,*radiusLabel,*rasterSizeAngleLabel,*rasterSizeRadiusLabel;
	QLabel*zminLabel,*zmaxLabel,*rasterSizeZLabel;
	QLineEdit *xmin,*xmax,*ymin,*ymax,*zmin,*zmax,*rasterSizeX,*rasterSizeY,*rasterSizeZ;
	QLineEdit*angle,*radius,*rasterSizeAngle,*rasterSizeRadius;
	QCheckBox*raster,*axis,*label,*autosize;
	QComboBox*graphType;
	QPushButton*stdButton,*angleButton;
	Preferences pref;
	Variable*vars;
	Q_OBJECT
public:
	CoordinatePreferences(Preferences p,QWidget*parent,Variable*v)
	:QWidget(parent)
	{
		pref=p;
		vars=v;
		rectLabel=new QLabel(GRAPHPREFH_STR2,this);
		xminLabel=new QLabel("x min:",this);
		xmaxLabel=new QLabel("x max:",this);
		yminLabel=new QLabel("y min:",this);
		ymaxLabel=new QLabel("y max:",this);
		zminLabel=new QLabel("z min:",this);
		zmaxLabel=new QLabel("z max:",this);
		polarLabel=new QLabel(GRAPHPREFH_STR10,this);
		angleLabel=new QLabel(GRAPHPREFH_STR11,this);
		radiusLabel=new QLabel(GRAPHPREFH_STR12,this);
		rasterSizeAngleLabel=new QLabel(GRAPHPREFH_STR13,this);
		rasterSizeRadiusLabel=new QLabel(GRAPHPREFH_STR14,this);
		raster=new QCheckBox(GRAPHPREFH_STR3,this);
		axis=new QCheckBox(GRAPHPREFH_STR4,this);
		label=new QCheckBox(GRAPHPREFH_STR5,this);
		autosize=new QCheckBox(GRAPHPREFH_STR6,this);
		rasterSizeXLabel=new QLabel(GRAPHPREFH_STR7,this);
		rasterSizeYLabel=new QLabel(GRAPHPREFH_STR8,this);
		rasterSizeZLabel=new QLabel(GRAPHPREFH_STR21,this);
		graphTypeLabel=new QLabel(GRAPHPREFH_STR9,this);
		axis->setChecked(pref.axis);
		label->setChecked(pref.label);
		raster->setChecked(pref.raster);
		autosize->setChecked(pref.autosize);
		
		xmin=new QLineEdit(QString::number(pref.xmin),this);
		xmax=new QLineEdit(QString::number(pref.xmax),this);
		ymin=new QLineEdit(QString::number(pref.ymin),this);
		ymax=new QLineEdit(QString::number(pref.ymax),this);
		zmin=new QLineEdit(QString::number(pref.zmin),this);
		zmax=new QLineEdit(QString::number(pref.zmax),this);
		rasterSizeX=new QLineEdit(QString::number(pref.rasterSizeX),this);
		rasterSizeY=new QLineEdit(QString::number(pref.rasterSizeY),this);
		rasterSizeZ=new QLineEdit(QString::number(pref.rasterSizeZ),this);
		radius=new QLineEdit(QString::number(pref.radiusMax),this);
		angle=new QLineEdit(QString::number(pref.angleMax),this);
		rasterSizeAngle=new QLineEdit(QString::number(pref.rasterSizeAngle),this);
		rasterSizeRadius=new QLineEdit(QString::number(pref.rasterSizeRadius),this);
		graphType=new QComboBox(false,this);
		stdButton=new QPushButton(GRAPHPREFH_BTN1,this);
		angleButton=new QPushButton(GRAPHPREFH_BTN2,this);
		
		graphType->insertItem(GRAPHPREFH_STR15);
		graphType->insertItem(GRAPHPREFH_STR16);
		graphType->insertItem(GRAPHPREFH_STR17);
		if(pref.graphType==GRAPHPOLAR)
			graphType->setCurrentText(GRAPHPREFH_STR16);
		else if(pref.graphType==GRAPH3D)
			graphType->setCurrentText(GRAPHPREFH_STR17);
		else graphType->setCurrentText(GRAPHPREFH_STR15);
		
		setGeometry(10,10,580,360); 
		setFixedWidth(580);
		setFixedHeight(360);
		
		graphTypeLabel->setGeometry(10,15,240,20);
		graphType->setGeometry(250,10,180,30);
		
		rectLabel->setGeometry(10,50,380,20);
		xminLabel->setGeometry( 10,80,100,20);
		xmin->setGeometry     (110,80, 80,20);
		xmaxLabel->setGeometry(200,80,100,20);
		xmax->setGeometry     (300,80, 80,20);
		yminLabel->setGeometry( 10,110,100,20);
		ymin->setGeometry     (110,110, 80,20);
		ymaxLabel->setGeometry(200,110,100,20);
		ymax->setGeometry     (300,110, 80,20);
		zminLabel->setGeometry( 10,140,100,20);
		zmin->setGeometry     (110,140, 80,20);
		zmaxLabel->setGeometry(200,140,100,20);
		zmax->setGeometry     (300,140, 80,20);
		rasterSizeXLabel->setGeometry(390,80,100,20);
		rasterSizeX->setGeometry     (490,80,80,20);
		rasterSizeYLabel->setGeometry(390,110,100,20);
		rasterSizeY->setGeometry     (490,110,80,20);
		rasterSizeZLabel->setGeometry(390,140,100,20);
		rasterSizeZ->setGeometry     (490,140,80,20);
		polarLabel->setGeometry(10,170,380,20);
		angleLabel->setGeometry(10,200,150,20);
		radiusLabel->setGeometry(10,230,150,20);
		angle->setGeometry(160,200,120,20);
		radius->setGeometry(160,230,120,20);
		rasterSizeAngleLabel->setGeometry(300,200,150,20);
		rasterSizeRadiusLabel->setGeometry(300,230,150,20);
		rasterSizeAngle->setGeometry(450,200,120,20);
		rasterSizeRadius->setGeometry(450,230,120,20);
		stdButton->setGeometry(135,260,150,30);
		angleButton->setGeometry(295,260,150,30);
		
		axis->setGeometry(10,300,180,20);
		label->setGeometry(200,300,180,20);
		raster->setGeometry(390,300,180,20);
		autosize->setGeometry(10,330,380,20);
		
		
		QObject::connect(stdButton,SIGNAL(clicked()),this,SLOT(stdButtonSlot()));
		QObject::connect(angleButton,SIGNAL(clicked()),this,SLOT(angleButtonSlot()));
		QObject::connect(graphType,SIGNAL(activated(int)),this,SLOT(graphTypeSlot(int)));
		graphTypeSlot(0);
	}

	int savePref();


	
public slots:
	
	void stdButtonSlot();
	void angleButtonSlot();
	void graphTypeSlot(int);
	void getPref(Preferences pref);
	
	
signals:
	void prefChange(Preferences);
	
	
	
};

class ParameterPreferences :public QWidget
{
	Preferences pref;
	QLabel *parameterLabel,*parameterStartLabel,*parameterEndLabel,*parameterStepsLabel;
	QLineEdit*parameterStart,*parameterEnd,*parameterSteps;
	QPushButton*standardButton;
	Variable*vars;
	
	Q_OBJECT
	public:
	ParameterPreferences(Preferences p,QWidget*parent,Variable*v)
	:QWidget(parent)
	{
		pref=p;
		vars=v;
		setGeometry(10,10,580,360); 
		setFixedWidth(580);
		setFixedHeight(360);
		
		parameterLabel=new QLabel(GRAPHPREFH_STR18,this);
		parameterStartLabel=new QLabel(GRAPHPREFH_STR19,this);
		parameterEndLabel=new QLabel(GRAPHPREFH_STR20,this);
		parameterStepsLabel=new QLabel(GRAPHPREFH_STR22,this);
		standardButton=new QPushButton(GRAPHPREFH_STR23,this);
		
		parameterStart=new QLineEdit(QString::number(pref.parameterStart),this);
		parameterEnd=new QLineEdit(QString::number(pref.parameterEnd),this);
		parameterSteps=new QLineEdit(QString::number(pref.parameterSteps),this);
		
		parameterLabel->setGeometry(20,30,380,20);
		parameterStartLabel->setGeometry(20,70,100,20);
		parameterStart->setGeometry(180,70,170,20);
		parameterEndLabel->setGeometry(20,110,100,20);
		parameterEnd->setGeometry(180,110,170,20);
		parameterStepsLabel->setGeometry(20,150,100,20);
		parameterSteps->setGeometry(180,150,170,20);
		standardButton->setGeometry(40,190,80,25);
		QObject::connect(standardButton,SIGNAL(clicked()),this,SLOT(standardButtonSlot()));
	}

	int savePref();
		
	public slots:
	

	void getPref(Preferences pref);
	void standardButtonSlot();
	
	signals:
		void prefChange(Preferences);
	
};

class DynamicPreferences :public QWidget
{
	Preferences pref;
	QLabel *dynamicLabel,*parameterStartLabel,*parameterEndLabel;
	QLabel *parameterStepsLabel,*timeLabel;
	QLineEdit*parameterStart,*parameterEnd,*parameterSteps,*time;
	QRadioButton*upButton,*upDownButton;
	QButtonGroup *radioButtons;
	QCheckBox *singleStepBox;
	Variable*vars;
	
	Q_OBJECT
	public:
		DynamicPreferences(Preferences p,QWidget*parent,Variable*v)
	:QWidget(parent)
		{
			pref=p;
			vars=v;
			dynamicLabel=new QLabel(GRAPHPREFH_STR24,this);
			parameterStartLabel=new QLabel(GRAPHPREFH_STR25,this);
			parameterEndLabel=new QLabel(GRAPHPREFH_STR26,this);
			parameterStepsLabel=new QLabel(GRAPHPREFH_STR27,this);
			timeLabel=new QLabel(GRAPHPREFH_STR28,this);
			singleStepBox=new QCheckBox(GRAPHPREFH_STR29,this);
			
			parameterStart=new QLineEdit(QString::number(pref.dynamicStart),this);
			parameterEnd=new QLineEdit(QString::number(pref.dynamicEnd),this);
			parameterSteps=new QLineEdit(QString::number(pref.dynamicSteps),this);
			time=new QLineEdit(QString::number(pref.dynamicDelay),this);
			
			radioButtons=new QButtonGroup(this);
			upButton=new QRadioButton(GRAPHPREFH_STR30,radioButtons);
			upDownButton=new QRadioButton(GRAPHPREFH_STR31,radioButtons);
			
			if(pref.moveUpDown)
				upDownButton->setChecked(true);
			else upButton->setChecked(true);
			
			if(pref.dynamicDelay>0)
				singleStepBox->setChecked(true);
			else {
				singleStepBox->setChecked(false);
				time->setEnabled(false);
				time->setText("10");
			}

			
			dynamicLabel->setGeometry(20,30,380,20);
			parameterStartLabel->setGeometry(20,70,100,20);
			parameterStart->setGeometry(180,70,170,20);
			parameterEndLabel->setGeometry(20,110,100,20);
			parameterEnd->setGeometry(180,110,170,20);
			parameterStepsLabel->setGeometry(20,150,100,20);
			parameterSteps->setGeometry(180,150,170,20);
			timeLabel->setGeometry(20,190,160,20);
			time->setGeometry(180,190,170,20);
			
			singleStepBox->setGeometry(20,240,250,20);
			radioButtons->setGeometry(20,270,250,60);
			upButton->setGeometry(5,5,230,20);
			upDownButton->setGeometry(5,35,230,20);
			
			QObject::connect(singleStepBox,SIGNAL(toggled(bool)),time,SLOT(setEnabled(bool)));
			
			setGeometry(10,10,580,360); 
			setFixedWidth(580);
			setFixedHeight(360);


		}
	int savePref();
	public slots:
	
		void getPref(Preferences pref);
	
	signals:
		void prefChange(Preferences);
	
};




class GraphPreferences :public QTabWidget
{

	QTabBar *tabBar;
	CoordinatePreferences*coordinateWidget;
	ParameterPreferences*parameterWidget;
	DynamicPreferences*dynamicWidget;
	QPushButton*saveButton,*cancelButton;
	Preferences pref;
	Variable*vars;
	Q_OBJECT
public:
	GraphPreferences(Preferences p, QWidget*parent)
	:QTabWidget(parent,GRAPHPREFH_STR1,Qt::WStyle_Dialog | Qt::WType_Dialog)
	{
		pref=p;
		vars=new Variable[27];
		tabBar = new QTabBar(this);
		setTabBar(tabBar);
		
		coordinateWidget = new CoordinatePreferences(pref,this,vars);
		parameterWidget = new ParameterPreferences(pref,this,vars);
		dynamicWidget= new DynamicPreferences(pref,this,vars);
		addTab(coordinateWidget,GRAPHPREFH_STR32);
		addTab(parameterWidget,GRAPHPREFH_STR33);
		addTab(dynamicWidget,GRAPHPREFH_STR34);
			
		
		saveButton=new QPushButton(GRAPHPREFH_BTN3,this);
		cancelButton=new QPushButton(GRAPHPREFH_BTN4,this);
		
		setFixedWidth(coordinateWidget->width());
		setFixedHeight(coordinateWidget->height()+tabBar->height()+50);
		
		saveButton->setGeometry(width()-220,height()-50,100,40);
		cancelButton->setGeometry(width()-110,height()-50,100,40);
		
		QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(saveButtonSlot()));
		QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
		QObject::connect(coordinateWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(parameterWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(dynamicWidget,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));

	}
	
	protected:
		virtual void windowActivationChange(bool);	
	
	
public slots:
	void saveButtonSlot();
	void getPref(Preferences pr)
	{
		pref=pr;
		coordinateWidget->getPref(pref);
		parameterWidget->getPref(pref);
		dynamicWidget->getPref(pref);
		emit prefChange(pref);
	}
	
signals:
	void prefChange(Preferences);
	
};
