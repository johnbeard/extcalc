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




