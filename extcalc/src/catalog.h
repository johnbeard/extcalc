/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         catalog.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This is a overloaded popup menu that serves a complete function catalog.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef CATALOGH
#define CATALOGH

#include <q3popupmenu.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <q3listbox.h>
#include <qlineedit.h>
#include <qdialog.h>
#include <QAction>
#include <QSignalMapper>
#include "global.h"


/*
math
pi											3,14159 26535 89793 23846 26433 83279 50288
euler										2,71828 18284 59045 23536 02874 71352 66249
(C)gamma (Euler-Mascheroni-Konstante)			0,57721 56649 01532 86060 65120 90082 40243

physics
c0	vacuum light speed						299 792 458						m/s
my0 magnetic field							12.566 370 614...x10^7			N/A^2
epsilon0 electric field						8.854 187 817...x10^12			F/m
Z0	Wellenwiderstand						376.730 313 461					Ohm
G (Gravitation)								6.6742x10^11					m^3/(kg s^2)
h (plancksches Wirkungsquantum				6.626 069 3x10^-34

e (Elementraladung)							1.602 176 53x10^-19				C
alpha (Feinstrukturkonstante)				7.297 352 568x10^-3

m_e Elektronenmasse							9.109 381 88(72)x10^-31			kg
m_p Protonenmasse							1.672 621 58(13)x10^-27			kg
m_n Neutronenmasse							1.674 927 16(13)x10^-27			kg

conversation
*/

class ConstantDialog :public QDialog
{
	QLabel *constLabel,*descriptionLabel,*valueLabel,*identifierLabel;
	QLineEdit *descriptionLine,*valueLine,*identifierLine;
	QPushButton *okButton,*cancelButton,*addButton,*removeButton;
	Q3ListBox *variablesBox;
	Preferences pref;
	Q_OBJECT
	
	
	public:
	ConstantDialog(QWidget*parent,QString name,Preferences p);
	
	public slots:
		
	void boxSlot();
	void applySlot();
	void removeSlot();
	void setPref(Preferences newPref);
	
	signals:
		void prefChange(Preferences);
	
};


class Catalog :public QMenu
{
  QMenu *mathStandard,*mathTrigonometric,*mathExtended,*mathLogic,*matrix,*scriptStandard;
  QMenu *scriptText,*scriptGraphics,*scriptGL,*scriptFile;
  QMenu *constantsMath,*constantsPhysics,*constantsConv,*constantsUser;

  QSignalMapper *mathStandardMapper,*mathTrigonometricMapper,*mathExtendedMapper,*mathLogicMapper;
  QSignalMapper *matrixMapper,*scriptStandardMapper,*scriptTextMapper,*scriptGraphicsMapper;
  QSignalMapper *scriptGLMapper,*scriptFileMapper;
  QSignalMapper *constantsMapper;


	Preferences pref;
	int mathConstLen,physicsConstLen,convConstLen;
	int state;
	ConstantDialog*cDialog;
	Q_OBJECT


	public:
	
  Catalog(int st, QWidget*parent,Preferences *p=NULL);
	
	void setPref(Preferences newPref);
	


	
	public slots:
		
	void mathStandardSlot(int);
	void mathTrigonometricSlot(int);
	void mathExtendedSlot(int);
	void mathLogicSlot(int);
	
	void matrixSlot(int);
	
	void scriptStandardSlot(int);
	void scriptTextSlot(int);
	void scriptGraphicsSlot(int);
	void scriptGLSlot(int);
	void scriptFileSlot(int);
	
	void constantsSlot(int);
	
	void getPref(Preferences pref)
	{emit prefChange(pref);}

	
	signals:
	
	void menuSignal(QString);
	void prefChange(Preferences);
	
	
};

#endif
