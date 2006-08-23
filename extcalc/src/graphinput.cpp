#include "graphinput.h"



void GraphInput::insertText(QString ins)
{

	int cursorPos=cursorPosition();
	QString fullText=text();
	fullText.insert(cursorPos,ins);
	setText(fullText);
	setCursorPosition(cursorPos+ins.length());
}

void GraphInput::delKey()
{
	int cursorPos=cursorPosition();
	if(cursorPos >0)
		  backspace();
	else del();
}





