/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         calctable.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "calctable.h"   



void CalcTable::paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg )
{
	QTableItem*paintItem=item(row,col);
	if(paintItem==NULL)
	{
		setText(row,col," ");
		paintItem=item(row,col);
	}
	QColorGroup g(cg);


	
	if(col == coloredCol && row < colorTable.GetLen())
	{
		g.setColor(QColorGroup::Text,colorTable[row]);
	}
	
	
	paintItem->paint(p,g,cr,selected);
//	paintCell(p,row,col,cr,selected,g);

		
}


QWidget *CalcTable::beginEdit( int row, int col, bool replace )
{
	emit cellEditStarted(row,col);
	if ( isReadOnly() || isRowReadOnly( row ) || isColumnReadOnly( col ) || (!editable&&col==coloredCol))
		return 0;
	QTableItem *itm = item( row, col );
	if ( itm && !itm->isEnabled() )
		return 0;
	if ( cellWidget( row, col ) )
		return 0;
	ensureCellVisible( row, col );
	QWidget *e = createEditor( row, col, !replace );
	if ( !e )
		return 0;
	setCellWidget( row, col, e );
	e->setActiveWindow();
	e->setFocus();
	updateCell( row, col );
	return e;
}









void CalcTable::changeColor(int row,QColor color)
{
	int rowNum=numRows();
	if(rowNum != colorTable.GetLen())
	{
		for(int c=0; c<rowNum; c++)
			colorTable.NewItem(QColor(0,0,0));
	}
	
	if(row < colorTable.GetLen())
		colorTable[row]=color;
}







