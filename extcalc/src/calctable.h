/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         calctable.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Overloaded QTable class that supports colored cells.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef CALCTABLE
#define CALCTABLE



#include <qtable.h>
#include <global.h>
#include "list.h"



class CalcTable :public QTable
{
	
	int coloredCol;
	bool editable;
	List <QColor> colorTable;
	
	Q_OBJECT
public:
	
	
	CalcTable(QWidget*parent,int coloredColumn=0,bool isEditable=true) :QTable(parent)
	{
		coloredCol=coloredColumn;
		editable=isEditable;
	}
	
	void changeColor(int row,QColor color);
	
	
protected:
	
	virtual void paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg );
	QWidget* beginEdit( int row, int col, bool replace );

	
	signals:
	void cellEditStarted(int,int);
	
	
}; 




#endif




