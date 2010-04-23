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


#include <QWidget>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <qicon.h>
#include <q3popupmenu.h>
#include <qtooltip.h>
#include <qsplitter.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <Q3ValueList>
#include <QPixmap>
#include "buttons.h"
#include "calcinput.h"
#include "calctable.h"
#include "catalog.h"
#include "tabwidget.h"
#include <QFrame>





class MatrixWidget :public TabWidget
{
  StandardButtons*calcButtons;
  ExtButtons*extButtons;
	CalcTable*outputTable;
	CalcTable*varTable;
//	CalcTable*resultTable;
//	QPushButton*sprodButton,*invertButton,*detButton;
//	QComboBox*operationBox;
//	QSpinBox *size1Box,*size2Box;
//	QComboBox *matrixBox,*vectorBox
  QComboBox *operationBox;
  QComboBox *typeBox;
//	QLabel *matrixLabel,*vectorLabel,*size1Label,*size2Label,*label1,*label2,*label3;
//	QLineEdit *input1,*input2,*input3;
//	QPushButton *calcButton,*sizeButton,*catalogButton;
  QAction *maximizeAction;
  QAction *catalogAction;

//	QPixmap *catalogIcon;
	Catalog *catalog;
	QSplitter *split;
	QFrame*leftFrame,*rightFrame;

	CalcInput*calcWidget;
	int currentVar;
	int state;

	Q_OBJECT
	public:
    MatrixWidget(QWidget*parent,Preferences p,Variable*va,ThreadSync*td,StandardButtons*sB,ExtButtons*eB);
	
		void setPref(Preferences);
	
		void setVarTable();
		void setOutputTable(int num);
		void resizeVar(int var,int rows,int cols);
		void resetInterface();
		void setHeader(CalcTable*);

    private:
    void updateUI();
	
	public slots:
		void getPref(Preferences);
		void sprodButtonSlot();
		void invertButtonSlot();
		void detButtonSlot();
		void operationBoxSlot(int);
		void enterSlot();
    void processText(QString);
		void varSelectionSlot(int,int);
		void varChangedSlot(int,int);
		void outputChangedSlot(int,int);
		void calcButtonSlot();
		void matrixBoxSlot(int);
		void vectorBoxSlot(int);
		void size1BoxSlot(int);
		void sizeButtonSlot();
		void typeBoxSlot(int);
		void dockWindowSlot();
    void viewSlot(bool min);
	
//	protected:
//		virtual void resizeEvent(QResizeEvent*);
	
	
	signals:
		void prefChange(Preferences);
	
};

#endif
