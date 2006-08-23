#ifndef GRAPHINPUTH
#define GRAPHINPUTH


#include "global.h"
#include <qlineedit.h>





class GraphInput :public QLineEdit
{
	
	int cursorPos;
	Preferences pref;
	
	
	
public:
	
	GraphInput(QWidget*parent) :QLineEdit(parent)
	{
		cursorPos=0;
		
		
	}
	
	
	void insertText(QString ins);
	void delKey();

	
};



#endif   






  