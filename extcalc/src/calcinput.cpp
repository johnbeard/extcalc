#include "calcinput.h"

void CalcInput::keyPressEvent(QKeyEvent*e)
{
	int para;
	int pos;
	bool noCheck=false;

	getCursorPosition(&para,&pos);
	if(para != paragraphs()-1 && 
		  !((e->state() == Qt::ControlButton || e->stateAfter() == Qt::ControlButton)
		  && e->key() != Qt::Key_V && e->key() != Qt::Key_X ) &&
		  !(e->key() == Qt::Key_Right || e->key() == Qt::Key_Left ||
		  e->key() == Qt::Key_Up || e->key() == Qt::Key_Down)) 
	{
		QString content=text(para);
		content=content.stripWhiteSpace();

		if(hasSelectedText())
		{
			int startPara,endPara,startPos,endPos;
			getSelection(&startPara,&startPos,&endPara,&endPos,0);
			if(startPara != endPara)
			{
				setSelection(-1,-1,-1,-1,0);
				return;
			}
			else {
				setSelection(-1,-1,-1,-1,0);
				content.remove(startPos,endPos-startPos);
				pos=startPos;
				if(e->ascii()==8 || e->ascii()==127)
					noCheck=true;
			}
		}

		para=paragraphs()-1;
		setCursorPosition(para,0);
		while(text(para).length() > 1)
			del();
		setBold(false);
		setAlignment(Qt::AlignLeft);
		insert(content);
		setCursorPosition(para,pos);
	}

	if(!noCheck)
	switch(e->ascii())
	{
		case 13:								//enter
		{
			calculateKey();
			break;
		}
		case 8:									//backspace
				backKey();
			break;
		case 127:								//delete
			deleteKey();
			break;
		case 9:									//tab
			insert(" ");
			line.append(" ");
			lineCursor++;
			break;
		case 0:									//special keys
			if(e->key() == Qt::Key_Right)
				cursorKey(1);
			if(e->key() == Qt::Key_Left)
				cursorKey(3);
			if(e->key() == Qt::Key_Up)
				cursorKey(0);
			if(e->key() == Qt::Key_Down && para < paragraphs())
				cursorKey(2);
			break;
		default:
		{
			setBold(false);
			if(e->state() == Qt::ControlButton || e->stateAfter() == Qt::ControlButton)
			{
				switch(e->key())
				{
					case Qt::Key_V:
						paste();
						break;
				
					case Qt::Key_C:
				
//					MessageBox("copy");
						copy();
						break;
				
					case Qt::Key_X:
						cut();
						break;
					case Qt::Key_Y:
						redo();
						break;
					case Qt::Key_Z:
						undo();
						break;
				}
			}
			else {
				if(pos==0 && ( e->text() == "+" || e->text() == "^" || e->text() == "*" ||
							   e->text() == "/" || e->text() == "\xb2" || e->text() == "\xb3" ||
							   e->text() == "-" || e->text() == getUnicode(ROOTSTRING) ||
							   e->text() == "%" || e->text() == "!"))
				{
					if(!ansDone && ansAvailable)
					{
						insert("ans");
						ansDone=true;
					}
				}
				if(e->state()==Qt::Keypad && e->ascii()==',')
					insert(".");
				else insert(e->text());
			}
		}
	}
	getCursorPosition(&para,&pos);
}


QPopupMenu* CalcInput::createPopupMenu(const QPoint&)
{
	
	QPopupMenu*menu = new QPopupMenu(this);
	menu->insertItem(CALCWIDGETC_MENU1,1);
	menu->insertItem(CALCWIDGETC_MENU2,2);
	menu->insertSeparator();
	menu->insertItem(CALCWIDGETC_MENU3,3);
	menu->insertItem(CALCWIDGETC_MENU4,4);
	menu->insertItem(CALCWIDGETC_MENU5,5);	
	QObject::connect(menu,SIGNAL(activated(int)),this,SLOT(menuSlot(int)));
	
	return menu;
}

void CalcInput::menuSlot(int item)
{
	switch(item)
	{
		case 1:
			undo();
			break;
		case 2:
			redo();
			break;
		case 3:
			keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_X,(int)'x',Qt::ControlButton));
			break;
		case 4:
			keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_C,(int)'c',Qt::ControlButton));
			break;
		case 5:
			keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_V,(int)'v',Qt::ControlButton));
			break;
	}

}


void CalcInput::calculateKey()
{
	ansAvailable=true;
	ansDone=false;
	textInput("");
	int para;
	int pos;
	getCursorPosition(&para,&pos);
	Number nResult;
	
	setCursorPosition(para,paragraphLength(para));
	QString strResult;
	setBold(true);
	if(text(para).length() <= 1)
	{
		para--;
		setCursorPosition(para,0);
		char*cleanString=NULL;
		int c;
		for(c=resultParagraphs.GetLen()-1; c>=1; c--)
			if(resultParagraphs[c]-1 != resultParagraphs[c-1])
			{
				cleanString=checkString(text(resultParagraphs[c]-1),&pref);
				break;
			}
		if(c<=0)
			cleanString=checkString(text(0),&pref);
		Script s(NULL,cleanString,&pref,vars,threadData);
		nResult=s.exec();
		if(cleanString!=NULL)
			delete[]cleanString;
		setCursorPosition(paragraphs()-1,0);
	}
	else {
		insert(QString("\n"));
		char*cleanString=checkString(text(para),&pref);
		Script s(NULL,cleanString,&pref,vars,threadData);
		nResult=s.exec();
		if(cleanString!=NULL)
			delete[]cleanString;
	}
	

	
	strResult=formatOutput(nResult,&pref,threadData);
	
	if(nResult.type==NVECTOR)
	{
		threadData->vars[26]=(Number*)realloc(threadData->vars[26],sizeof(Number)*threadData->numlen[nResult.ival]);
		for(int c=0; c<threadData->numlen[nResult.ival];c++)
		{
			convertToFloat(&threadData->vars[nResult.ival][c]);
			threadData->vars[26][c].type=NFLOAT;
			threadData->vars[26][c].fval=threadData->vars[nResult.ival][c].fval;
		}
		threadData->numlen[26]=threadData->numlen[nResult.ival];
	}
	else threadData->vars[26][0]=nResult;
//	while(strResult->length() < (unsigned)(lineLength-3))
//		strResult->insert(0,' ');
	setAlignment(Qt::AlignRight);
	insert(strResult);
	resultParagraphs.NewItem(paragraphs()-1);
	setBold(false);
	insert(QString("\n"));
	setAlignment(Qt::AlignLeft);
	line="";
	lineCursor=0;
}

void CalcInput::deleteKey()
{
	if(hasSelectedText())
	{
		
		textInput("");
		return;
	}
	else textInput("");

	del();
	line.remove(lineCursor,1);
}
void CalcInput::backKey()
{	
	if(hasSelectedText())
	{
		
		textInput("");
		return;
	}
	else textInput("");

	int para;
	int pos;
	getCursorPosition(&para,&pos);
	if(paragraphLength(para) > 0)
	{
		setCursorPosition(para,pos-1);
		del();

		line.remove(lineCursor-1,1);
		lineCursor--;

	}
}
void CalcInput::clearAll()
{
	ansAvailable=false;
	while(paragraphs() > 1)
		removeParagraph(0);
	removeParagraph(0);
	while(resultParagraphs.GetLen() > 0)
		resultParagraphs.DeleteItem(0);
	for(int c=0; c<VARNUM; c++)
	{
		threadData->vars[c]=(Number*)realloc(threadData->vars[c],sizeof(Number));
		convertToFloat(threadData->vars[c]);
		threadData->numlen[c]=1;
		threadData->dimension[c][0]=threadData->dimension[c][1]=1;
	}
}
void CalcInput::cursorKey(int key)
{
	//	0	=	up
	//	1	=	right
	//	2	=	down
	//	3	=	left
	int para;
	int pos;
	getCursorPosition(&para,&pos);
	
	
	if(key==1 && pos < paragraphLength(para))
	{
		setCursorPosition(para,pos+1);
		lineCursor++;
	}
	if(key==3 && pos > 0)
	{
		setCursorPosition(para,pos-1);
		lineCursor--;
	}
	if(key==0)
		setCursorPosition(para-1,pos);
	if(key==2 && para < paragraphs())
		setCursorPosition(para+1,pos);
}



void CalcInput::resizeEvent(QResizeEvent*)
{

	QFontMetrics fontSize=fontMetrics();
	charLength=fontSize.size(0,QString("m")).width();
	lineLength=(width())/charLength-1;

}
/*
void CalcInput::customEvent(QCustomEvent*ev)
{
	if(scriptExec && script!=NULL)
	{
		if(ev->type() == 50000)
		{
			char*text=(char*)ev->data();
		//	MessageBox("Text: "+QString(text));
			insert(QString(text));
		}
		else if(ev->type() == 50010)		//script stopped
		{
			insert(QString("\n"));
			insert(QString("*** finish ***"));
			insert(QString("\n"));
			scriptExec=false;
			script->wait();
			delete script;
			script=NULL;
		}
	}
}
*/
void CalcInput::cursorSlot(int para,int pos)
{
	getCursorPosition(&para,&pos);
	lineCursor=pos;
}





void CalcInput::textInput(QString inputText)
{
	int para;
	int pos;
	getCursorPosition(&para,&pos);
	if(para != paragraphs()-1)
	{
		QString content=text(para);
		while(content[0] == ' ' || content[0] == '\t')
		{
			content.remove(0,1);
			pos--;
		}
		
		if(hasSelectedText())
		{
			int startPara,endPara,startPos,endPos;
			getSelection(&startPara,&startPos,&endPara,&endPos,0);
			if(startPara != endPara)
			{
				setSelection(-1,-1,-1,-1,0);
				return;
			}
			else {
				setSelection(-1,-1,-1,-1,0);
				content.remove(startPos,endPos-startPos);
				pos=startPos;
			}
		}		
		
		para=paragraphs()-1;
		setCursorPosition(para,0);
		while(text(para).length() > 1)
			del();
		setBold(false);
		insert(content);
		setCursorPosition(para,pos);
	}
	if(pos==0 && ( inputText == "+" || inputText[0] == '^' || inputText == "*" ||
		  inputText == "/" || inputText == "\xb2" || inputText == "\xb3" ||
		  inputText[0] == '-' || inputText == getUnicode(ROOTSTRING) ||
		  inputText == "%" || inputText == "!"))
	{
		if(!ansDone && ansAvailable)
		{
			insert("ans");
			ansDone=true;
		}
	}
	
	insert(inputText);
	
}
/*

void CalcInput::scriptSlot(QString*code)
{
	textInput("");
	int para;
	int pos;
	
	setCursorPosition(paragraphs()-1,paragraphLength(paragraphs()-1));
	setAlignment(Qt::AlignLeft);
	setBold(false);
	insert(QString("\n"));
	insert(QString("*** script ***"));
	insert(QString("\n"));
	QString *strResult;
	setBold(true);


	char*cleanString=checkString(*code,&pref,vars);
	perror("cleanString: "+QString(cleanString));
	scriptObject=new Script(NULL,cleanString,&pref,vars,this);
//	Number result=testScript.exec();
	scriptExec=true;
	script=new ScriptThread(scriptObject,this);
	delete[]cleanString;
	script->start();
	

	line="";
	lineCursor=0;
	
}
*/




