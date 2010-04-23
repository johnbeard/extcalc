/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         buttons.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This file includes the classes for the two button fields of the calculator.
StandardButtons class for numbers and basic functions
ExtButtons for scientific functions

////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef BUTTONSH
#define BUTTONSH

#include "global.h"
#include <qpushbutton.h>
#include <QButtonGroup>
#include <QWidget>
#include <qstring.h>
#include <qfont.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <stdio.h>
#include "toolwidget.h"


/**
 * @class StandardButtons
 * @brief A DockWidget with some basic buttons for the calculator
 *
 * The StandardButtons class manages a set of basic buttons for the
 * calculator and hands the user input from the buttons by the
 * emitText signal to another object. The main widget may control
 * the input data by connecting the active widget to this signal.
 */
class StandardButtons :public ToolWidget
{
  /// The ButtonGroup contains all buttons and bundles the button signals
  QButtonGroup *buttons;
  /// Number of columns of the button field
  int cols;
  /// Number of rows of the button field
  int rows;

	Q_OBJECT
	
public:

  StandardButtons(QWidget *parent);
	
  void setPref(Preferences newPref);

  void setStandardSet();

  void setAlphaSet();
	
  void setShiftSet();
	

protected:
		
	virtual void resizeEvent( QResizeEvent * );

public slots:
	
	void buttonSlot(int);
	
	signals:
	void emitText(QString);
	void prefChange(Preferences);
	
};

/**
 * @class ExtButtons
 * @brief A DockWidget with extended buttons for the calculator
 *
 * The ExtButtons class manages a the extended buttons and behaves
 * essentially like the StandardButtons class. It also contains
 * the Shift, Hyp and Alpha buttons which may change the program
 * preferences.
 */
class ExtButtons :public ToolWidget
{
  /// The ButtonGroup contains all buttons and bundles the button signals
  QButtonGroup *buttons;
  /// Number of columns of the button field
  int cols;
  /// Number of rows of the button field
  int rows;

	Q_OBJECT
	
public:

  ExtButtons(QWidget *parent);
	
  void setPref(Preferences newPref);


  void setStandardSet();

  void setShiftSet();


  void setAlphaSet();

  void setHypSet();

  void setBaseStandardSet();

  void setBaseShiftSet();

	protected:

	virtual void resizeEvent( QResizeEvent * );

	public slots:
		
	void buttonSlot(int);

	signals:
	void emitText(QString);
	void prefChange(Preferences);
	
};


#endif

