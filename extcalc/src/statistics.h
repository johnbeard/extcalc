/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         statistics.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Statistics window class of Extcalc.
The data table for statistical calculations is controlled by this class.
Graphical results were shown by the graphics window class.


////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef STATISTICS_H
#define STATISTICS_H


#include <QWidget>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qsplitter.h>
#include <qpushbutton.h>
#include <QToolBar>
#include <qicon.h>
#include <q3popupmenu.h>
#include <qtooltip.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QPixmap>
#include <QFrame>
#include <QGridLayout>
#include "functiontable.h"
#include "buttons.h"
#include "catalog.h"
#include "tabwidget.h"

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




class StatisticsWidget :public TabWidget
{
  StandardButtons*calcButtons;
  ExtButtons*extButtons;
	FunctionTable *functionTable;
	Q3Table *lists;
	QSplitter *horzSplit,*vertSplit;
	QPixmap *minimizeIcon,*maximizeIcon,*printIcon,*catalogIcon;
	Catalog *catalog;
	QComboBox *typeBox, *functionTypeBox,*copyFunction,*listNumberBox;
	QSpinBox *listNumber,*stepsBox;
	QPushButton *calculateButton,*maximizeButton,*drawButton,*copyButton,*catalogButton;
	QLabel *listNumberLabel,*resultLabel,*copyFunctionLabel,*functionTypeLabel,*stepsLabel;
	QLineEdit * result,*inputLine;
	QFrame *toolFrame;
	QGridLayout *toolFrameLayout;
  QAction*printAction,*maximizeAction,*catalogAction;
	
	double xmin,xmax,ymin,ymax;
	bool print,functionChanged;
	int type,changedRow;
	int menuBottom;

	Q_OBJECT
	public:
    StatisticsWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td,StandardButtons*cB,ExtButtons*eB);

		void setPref(Preferences);
		void writeListsFile();
		void readListsFile();
		void setCoordinateSystem();

  private:
    void updateUI();

	public slots:
		void getPref(Preferences);
    void viewSlot(bool);
		void typeBoxSlot(int);
		void calculateButtonSlot();
		void itemChangedSlot(int,int);
		void copyButtonSlot();
		void printButtonSlot();
    void processText(QString);
		void redrawGraphSlot();
		void dockWindowSlot();
		void catalogSlot();
		
		void selectionChangedSlot(int row,int col);
		void tableEditSlot(QString);
		void inputTextChanged(const QString&);
		void inputTextFinished();

//	protected:
        //	void resizeEvent(QResizeEvent*);

	signals:
		void prefChange(Preferences);
		void printSignal();
		void changeTabSignal(int);
		void drawPointsSignal(long double*,int,bool);
		void removeLinesSignal();

};

#endif


