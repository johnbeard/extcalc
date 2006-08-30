#include "scriptio.h"


void ScriptIOWidget::getPref(Preferences newPref)
{
	emit prefChange(newPref);
}



void ScriptIOWidget::maximizeSlot()
{
	if(maximized)
	{
		maximized=false;
		calcButtons->show();
		extButtons->show();
		maximizeButton->setText(CALCWIDGETC_STR1);
		resizeEvent(NULL);
	}
	else 
	{
		calcButtons->hide();
		extButtons->hide();
		maximizeButton->setText(CALCWIDGETC_STR2);
		maximized=true;
		resizeEvent(NULL);
	}
	repaint();
}

void ScriptIOWidget::killSlot()
{
	if(scriptExec)
	{
		threadData->status=1;
		threadData->exit=true;
		t->stop();
	//	script->terminate();
		sleep(1);
		if(!script->wait(500))
		{
			ErrorBox(SCRIPTIO_STR2);
		}
		else {
			insert(QString(SCRIPTIO_STR3));
			scriptExec=false;
			delete script;
			script=NULL;
			inputMode=IMDEFAULT;
			killButton->setEnabled(false);
			scrollBar->show();
			resizeEvent(NULL);
		}
	}
}

void ScriptIOWidget::paintEvent(QPaintEvent*)
{
	buffer->fill();
	QPainter p;
	p.begin(buffer);
	p.setFont(*drawFont);
	int lineMemLen=lines.GetLen();
	int scrollbarPos;
	
	if(inputMode!=IMDEFAULT)
		scrollbarPos=lineMemLen-lineNum;
	else scrollbarPos=scrollBar->value();

	for(int c=scrollbarPos; c<scrollbarPos+lineNum; c++)
		p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c]);
	
	
	if((hasFocus() && inputMode==IMDEFAULT) || inputMode==IMGETLINE)
		p.drawLine(charWidth*cursorX,charHeight*(cursorY-scrollbarPos),charWidth*cursorX,charHeight*(cursorY+1-scrollbarPos));

	p.end();
	p.begin(this);
	p.drawPixmap(20,50,*buffer);
	p.end();

}



void ScriptIOWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right()-geometry().left();
	int height=geometry().bottom()-geometry().top();

	if(maximized)
	{
		maximizeButton->setGeometry(10,height-45,90,35);
		killButton->setGeometry(110,height-45,90,35);
		runButton->setGeometry(210,height-45,90,35);
		if(inputMode==IMDEFAULT)
			scrollBar->setGeometry(width-50,50,20,height-100);
		ioFieldWidth=width-50;
		ioFieldHeight=height-100;
	}
	else {
		calcButtons->setGeometry(20,height-220,280,200);
		extButtons->setGeometry(320,height-180,300,160);
		maximizeButton->setGeometry(325,height-220,90,35);
		killButton->setGeometry(425,height-220,90,35);
		runButton->setGeometry(525,height-220,90,35);
		if(inputMode==IMDEFAULT)
			scrollBar->setGeometry(width-40,50,20,height-290);
		ioFieldWidth=width-40;
		ioFieldHeight=height-290;
	}
	if(inputMode==IMDEFAULT)
		ioFieldWidth-=20;
	int oldCharNum=lines[0].length();
	charNum=ioFieldWidth/charWidth;
	lineNum=ioFieldHeight/charHeight;
	if(charNum<1)
		charNum=1;
	if(lineNum<1)
		lineNum=1;
	if(charNum>oldCharNum)
	{
		QString appString;
		appString.fill(' ',charNum-oldCharNum);
		for(int c=0; c<lines.GetLen(); c++)
			lines[c].append(appString);
	}
	
	while(lineNum>lines.GetLen())
	{
		QString str;
		str.fill(' ',charNum);
		lines.NewItem(str);
	}
	scrollBar->setMaxValue(lines.GetLen()-lineNum);
	

	buffer->resize(ioFieldWidth,ioFieldHeight);
	if(cursorX>charNum)
		cursorX=charNum;
	if(cursorY<scrollBar->value())
		cursorY=scrollBar->value();
}

void ScriptIOWidget::keyPressEvent(QKeyEvent*e)
{
	switch(e->ascii())
	{
		case 13:
			if(inputMode==IMDEFAULT)
				insert("\n");
			else if(inputMode==IMSCRIPTING)
			{
				if(inputBuffer!=NULL)
					if(strlen(inputBuffer)>0)
						free(inputBuffer);
				inputBuffer="";
				bufferCursor=0;
			}
			else if(inputMode==IMGETKEY)
			{
				char*strBuf=new char[2];
				strBuf[1]=(char)0;
				if(strlen(inputBuffer)>0)
				{
					strBuf[0]=inputBuffer[0];
					inputBuffer++;
				}
				else strBuf[0]=(char)13;
				threadData->data=strBuf;
				inputMode=IMSCRIPTING;
			}
			else {
				threadData->data=inputBuffer;
				inputBuffer="";
				inputMode=IMSCRIPTING;
			}
			bufferCursor=0;
			break;
		case 8:
			if(inputMode==IMDEFAULT)
				backKey();
			else if(inputMode==IMGETLINE)
			{
				int bufLen;
				if((bufLen=strlen(inputBuffer))>0 && bufferCursor>0)
				{
					inputBuffer[bufLen-1]=(char)0;
					backKey();
					bufferCursor--;
				}
			}
			break;
		case 127:
			if(inputMode==IMDEFAULT)
				deleteKey();
			else if(inputMode==IMGETLINE)
			{
				if(bufferCursor<(signed)strlen(inputBuffer))
				{
					for(int c=bufferCursor; inputBuffer[c]!=(char)0; c++)
						inputBuffer[c]=inputBuffer[c+1];
					deleteKey();
				}
			}
			break;
		case 0:
			if(inputMode==IMDEFAULT)
			{
				if(e->key() == Qt::Key_Right && cursorX<charNum-1)
					cursorX++;
				if(e->key() == Qt::Key_Left && cursorX>0)
					cursorX--;
				if(e->key() == Qt::Key_Up && cursorY>scrollBar->value())
					cursorY--;
				if(e->key() == Qt::Key_Down && cursorY<scrollBar->value()+lineNum)
					cursorY++;
				repaint(20,50,ioFieldWidth,ioFieldHeight,false);
			}
			else if(inputMode==IMGETLINE)
			{
				if(e->key() == Qt::Key_Right && bufferCursor<(signed)strlen(inputBuffer))
				{
					bufferCursor++;
					if(cursorX<charNum-1)
						cursorX++;
					else if(cursorY<lines.GetLen()-1)
					{
						cursorX=0;
						cursorY++;
					}
				}
				if(e->key() == Qt::Key_Left && bufferCursor>0)
				{
					bufferCursor--;
					if(cursorX>0)
						cursorX--;
					else if(cursorY>lines.GetLen()-lineNum)
					{
						cursorY--;
						cursorX=charNum-1;
					}
				}
				repaint(20,50,ioFieldWidth,ioFieldHeight,false);
			}
			break;
		default:
		{
			if(e->state() == Qt::ControlButton || e->stateAfter() == Qt::ControlButton)
			{
				switch(e->key())
				{
					case Qt::Key_V:
						QClipboard*board=QApplication::clipboard();
						insert(board->text(QClipboard::Clipboard));
						break;
		/*			case Qt::Key_C:
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
			*/	}
			}
			else
			{
				if(inputMode==IMDEFAULT)
					insert(e->text());
				else if(inputMode==IMSCRIPTING || inputMode==IMGETLINE)
				{
					
					int bufLen=strlen(inputBuffer);
					if(bufferCursor<0)
						bufferCursor=0;
					if(bufferCursor>bufLen)
						bufferCursor=bufLen;
					if(bufLen<=0)
					{
						inputBuffer=(char*)malloc(2);
						inputBuffer[1]=(char)0;
						bufferCursor=0;
						bufLen=0;
					}
					else inputBuffer=(char*)realloc(inputBuffer,bufLen+2);
					if(bufferCursor!=bufLen)
							memcpy(&inputBuffer[bufferCursor+1],&inputBuffer[bufferCursor],bufLen-bufferCursor+1);
					else inputBuffer[bufferCursor+1]=(char)0;
					inputBuffer[bufferCursor]=(char)e->ascii();
					bufferCursor++;
					if(inputMode==IMGETLINE)
						insert(e->text());
				}
				else if(inputMode==IMGETKEY)
				{
					char*strBuf=new char[2];
					strBuf[1]=(char)0;
					if(strlen(inputBuffer)>0)
					{
						strBuf[0]=inputBuffer[0];
					for(int c=0; inputBuffer[c]!=(char)0; c++)
						inputBuffer[c]=inputBuffer[c+1];
					}
					else strBuf[0]=(char)e->ascii();
					threadData->data=strBuf;
					inputMode=IMSCRIPTING;
				}
			}
		}
	}
} 


void ScriptIOWidget::wheelEvent(QWheelEvent*ev)
{
	if(inputMode==IMDEFAULT)
		scrollBar->setValue(scrollBar->value()-ev->delta()/40);
}


void ScriptIOWidget::customEvent(QCustomEvent*ev)
{
	if(scriptExec && script!=NULL)
	{
//		perror("customEvent: "+QString::number(pthread_self()));
		switch(ev->type())
		{
			case SIGPRINT:
			{
				char*text=(char*)ev->data();
				gettimeofday(&currentTime,NULL);
				if(currentTime.tv_sec > drawTime.tv_sec || currentTime.tv_usec-drawTime.tv_usec > 20000)
				{
					gettimeofday(&drawTime,NULL);
					if(!t->isActive())
						t->start(30,true);
				}
				insert(text,false);
				free(ev->data());
				break;
			}
			case SIGCLEARTEXT:
			{
				
				clearAll();

				if(!t->isActive())
					t->start(30,true);

				break;
			}
			case SIGGETKEY:
			{

				if(!t->isActive())
					t->start(30,true);

				int len=strlen(inputBuffer);
				if(len>0)
				{
					char*strBuf=new char[2];
					strBuf[1]=(char)0;
					strBuf[0]=inputBuffer[0];
					for(int c=0; inputBuffer[c]!=(char)0; c++)
						inputBuffer[c]=inputBuffer[c+1];
					if(bufferCursor>0)
						bufferCursor--;
					threadData->data=strBuf;
					if(len==1)
					{
						free(inputBuffer);
						inputBuffer="";
					}
				}
				else inputMode=IMGETKEY;
				break;
			}
			case SIGKEYSTATE:
			{
				int len=strlen(inputBuffer);

				char*strBuf=(char*)malloc(2);
				strBuf[1]=(char)0;
				if(len>0)
				{
					strBuf[0]=inputBuffer[0];
					for(int c=0; inputBuffer[c]!=(char)0; c++)
						inputBuffer[c]=inputBuffer[c+1];
					if(bufferCursor>0)
						bufferCursor--;
					if(len==1)
					{
						free(inputBuffer);
						inputBuffer="";
					}
				}
				else strBuf[0]=(char)0;
				threadData->data=strBuf;
				break;
			}
			case SIGGETLINE:
			{
				if(!t->isActive())
					t->start(30,true);
				inputMode=IMGETLINE;
				break;
			}
			case SIGSETTEXTPOS:
			{
				int*pos=(int*)ev->data();
				if(pos[1] >=0 && pos[1]<lineNum&&
				  pos[0]>=0 && pos[0]<charNum)
				{
					cursorX=pos[0];
					cursorY=pos[1]+lines.GetLen()-lineNum;
				}
				free(ev->data());
				break;
			}
			case SIGFINISHED:		//script stopped
			{
				gettimeofday(&currentTime,NULL);
				int secs=currentTime.tv_sec-startTime.tv_sec;
				int usecs=currentTime.tv_usec-startTime.tv_usec;
				if(usecs<0)
				{
					usecs+=1000000;
					secs--;
				}
//				MessageBox("Time: "+QString::number(secs)+"."+QString::number(usecs));
				t->stop();
				insert(QString(SCRIPTIO_STR4));
				scriptExec=false;
				script->wait();
				delete script;
				script=NULL;
				inputMode=IMDEFAULT;
				scrollBar->show();
				resizeEvent(NULL);
				killButton->setEnabled(false);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else {
		if(ev->type()==SIGDEBUG)
		{
			errorFlag=true;
			if(!t->isActive())
				t->start(30,true);
			
			int*index=(int*)ev->data();
			if(*index >=semicolonLines.GetLen())
				insert("\nEnd of File            ");
			else 
			{
				if((*index>0) && semicolonLines[*index-1]< semicolonLines[*index]-1)
					insert("\nBefore or in line ");
				else insert("\nIn line           ");
	
				QString lineNum=QString::number(semicolonLines[*index]);
				while(lineNum.length()<5)lineNum.insert(0," ");
	
				insert(lineNum);
			}
			char*text=(char*)ev->data()+4;
			insert(": ");
			insert(text);
			
			free(ev->data());
		}
	}
}

void ScriptIOWidget::mousePressEvent(QMouseEvent*e)
{
	if(inputMode!=IMDEFAULT)
		return;
	int mouseX=e->x()-20,mouseY=e->y()-50;

	if(mouseX>=0 && mouseX <=ioFieldWidth && mouseY>=0 && mouseY<=ioFieldHeight)
	{
		cursorX=(mouseX+charWidth/2)/charWidth;
		cursorY=(mouseY)/charHeight+scrollBar->value();
		if(cursorX>charNum)
			cursorX=charNum;
		if(cursorY>scrollBar->value()+lineNum)
			cursorY=scrollBar->value()+lineNum;
	}
	repaint(20,50,ioFieldWidth,ioFieldHeight,false);
}
void ScriptIOWidget::mouseReleaseEvent(QMouseEvent*)
{
	
}
void ScriptIOWidget::mouseMoveEvent(QMouseEvent*)
{
}


void ScriptIOWidget::insert(QString text,bool redraw)
{
	int len=text.length();
	int pos1=0,pos2=0;
	while((pos2=text.find("\n",pos1)+1)>0)
	{
		if(charNum-cursorX<pos2-pos1-1)
		{
			pos2=pos1+charNum-cursorX;
			lines[cursorY].replace(cursorX,pos2-pos1-1,text.mid(pos1,pos2-pos1-1));
			pos1=pos2-1;
		}
		else {
			lines[cursorY].replace(cursorX,pos2-pos1-1,text.mid(pos1,pos2-pos1-1));
			pos1=pos2;
		}
		if(cursorY >= lines.GetLen()-1)
		{
			lines.NewItem(QString());
			lines[lines.GetLen()-1].fill(' ',charNum);
			if(lines.GetLen() > BUFFER_LENGTH)
				lines.DeleteItem(0);
			else {
				scrollBar->setMaxValue(lines.GetLen()-lineNum);
				scrollBar->setValue(lines.GetLen()-lineNum);
				cursorY++;
			}
		}
		else cursorY++;
		cursorX=0;
	}
	if(charNum-cursorX<len-pos1)
	{
		while((pos2=pos1+charNum-cursorX)<len)
		{
			lines[cursorY].replace(cursorX,charNum-cursorX,text.mid(pos1,charNum-cursorX));
			pos1=pos2;
			if(cursorY >= lines.GetLen()-1)
			{
				lines.NewItem(QString());
				lines[lines.GetLen()-1].fill(' ',charNum);
				if(lines.GetLen() > BUFFER_LENGTH)
					lines.DeleteItem(0);
				else {
					scrollBar->setMaxValue(lines.GetLen()-lineNum);
					scrollBar->setValue(lines.GetLen()-lineNum);
					cursorY++;
				}
			}
			else cursorY++;
			cursorX=0;
		}
	//	pos1--;
	}
	
	lines[cursorY].replace(cursorX,len-pos1,text.mid(pos1,len-pos1));
	cursorX+=len-pos1;
	
	if(redraw)
		repaint(20,50,ioFieldWidth,ioFieldHeight,false);

}


void ScriptIOWidget::backKey()
{
	if(cursorX>0)
	{
		lines[cursorY].remove(cursorX-1,1);
		cursorX--;
		repaint(20,50,ioFieldWidth,ioFieldHeight,false);
	}
}

void ScriptIOWidget::deleteKey()
{
		lines[cursorY].remove(cursorX,1);
		repaint(20,50,ioFieldWidth,ioFieldHeight,false);
}



void ScriptIOWidget::clearAll()
{
	cursorX=0;
	cursorY=lines.GetLen()-lineNum;
	for(int c=0; c<lines.GetLen(); c++)
	{
		lines[c].fill(' ',charNum);
	}
	repaint(20,50,ioFieldWidth,ioFieldHeight,false);
}


void ScriptIOWidget::processText(QString text)
{
	if(text == "calculate")
		insert("\n");
	else if(text == "backkey")
		backKey();
	else if(text == "clearall")
		clearAll();
	else 
		insert(text);
}   


void ScriptIOWidget::runScript(QString*code)
{
	if(scriptExec)
	{
		int ret=YesNoBox(SCRIPTIO_STR5);
		if(ret==0)
			killSlot();
		else return;
	}

	if(scriptExec)
		return;
	threadData->status=0;
	threadData->exit=false;
	threadData->usleep=false;
	threadData->bbreak=false;
	threadData->bcontinue=false;
	
	errorFlag=false;
	
	while(threadData->subprograms.GetLen()>0)
	{
		delete threadData->subprograms[0];
		threadData->subprograms.DeleteItem(0);
	}
	while(threadData->subprogramPath.GetLen()>0)
	{
		delete[]threadData->subprogramPath[0];
		threadData->subprogramPath.DeleteItem(0);
	}
	while(semicolonLines.GetLen()>0)
		semicolonLines.DeleteItem(0);
	
	searchScripts(code);
	countDifference=0;
	initDebugging(code);


	char*cleanString=checkString(*code,&pref,vars);

	delete scriptObject;
	insert(SCRIPTIO_STR8);
	if(cleanString==NULL)
	{
		insert("\nPreprocessor Error\n");
		return;
	}
	scriptObject=new Script(NULL,cleanString,&pref,vars,threadData);
	loadSubScripts();
	delete[]cleanString;

//	perror("main thread: "+QString::number(pthread_self()));
}

void ScriptIOWidget::runSlot()
{
	if(scriptExec)
	{
		int ret=YesNoBox(SCRIPTIO_STR5);
		if(ret==0)
			killSlot();
		else return;
	}

	if(scriptExec)
		return;
	threadData->status=0;
	threadData->exit=false;
	threadData->usleep=false;
	threadData->bbreak=false;
	threadData->bcontinue=false;
	

	insert(QString(SCRIPTIO_STR6));
	if(inputBuffer!=NULL)
		if(strlen(inputBuffer)>0)
		{
			free(inputBuffer);
			inputBuffer="";
		}

	bufferCursor=0;
	inputMode=IMSCRIPTING;

	scriptExec=true;
	script=new ScriptThread(scriptObject,this);

	killButton->setEnabled(true);
	scrollBar->hide();
	resizeEvent(NULL);
	gettimeofday(&drawTime,NULL);
//	t->start(timerInterval);
	gettimeofday(&startTime,NULL);
#if QT_VERSION < 0x030200			//priority parameter is supported sience QT 3.2
	script->start();
#else
	script->start(QThread::IdlePriority);
#endif
}

void ScriptIOWidget::searchScripts(QString*code)
{
	char*cleanString=checkString(*code,&pref,vars);
	if(cleanString==NULL)
		return;
	char*scriptName;
	QString filePath;
	int len=strlen(cleanString);
	int pos=0,pos2;
	FILE*subFile;
	while(pos<len)
	{
		if(strncmp(&cleanString[pos],"run(\"",4) == 0) //run("")
		{
			pos2=bracketFind(cleanString,")",pos+4);
			if(pos2-pos<7 || cleanString[pos2-1]!='\"')
			{
				pos++;
				continue;
			}
			scriptName=new char[pos2-pos-5];
			strcopy(scriptName,&cleanString[pos+5],pos2-pos-6);
			bool newScript=true;
			for(int c=0; c<threadData->subprogramPath.GetLen(); c++)
				if(strcmp(threadData->subprogramPath[c],scriptName)==0)
				{
					newScript=false;
					break;
				}
			if(newScript)
			{
				struct stat fileStat;
				char*subFileContent;
				QString qSubFileContent;
				filePath=pref.scriptPath+"/"+pref.scriptDirName+QString("/")+scriptName;
				if(lstat(filePath,&fileStat)!=0)
					;
				else {
					subFile=fopen(filePath,"r");
					if(subFile==NULL || fileStat.st_size<=0)
						;
					else
					{
						subFileContent=new char[fileStat.st_size+1];
						subFileContent[fileStat.st_size]=(char)0;
						fread(subFileContent,fileStat.st_size,1,subFile);
						fclose(subFile);
						threadData->subprogramPath.NewItem(scriptName);
						qSubFileContent=QString(subFileContent);
						searchScripts(&qSubFileContent);
						delete[]subFileContent;
					}
				}
			}
			pos=pos2+1;
		}
		else pos++;
	}
	delete[] cleanString;
}


void ScriptIOWidget::loadSubScripts()
{
	QString filePath;
	struct stat fileStat;
	char*subFileContent;
	char*cleanSubFileContent;
	QString qSubFileContent;
	Script*subScript;
	FILE*subFile;
	for(int c=0; c<threadData->subprogramPath.GetLen(); c++)
	{
		filePath=pref.scriptPath+"/"+pref.scriptDirName+QString("/")+threadData->subprogramPath[c];
		if(lstat(filePath,&fileStat)!=0)
			threadData->subprograms.NewItem((Math*)NULL);
		else {
			subFile=fopen(filePath,"r");
			if(subFile==NULL || fileStat.st_size<=0)
				threadData->subprograms.NewItem((Math*)NULL);
			else
			{
				subFileContent=new char[fileStat.st_size+1];
				subFileContent[fileStat.st_size]=(char)0;
				fread(subFileContent,fileStat.st_size,1,subFile);
				fclose(subFile);
				qSubFileContent=QString(subFileContent);
				countDifference+=semicolonLines.GetLen();
				initDebugging(&qSubFileContent);
				cleanSubFileContent=checkString(qSubFileContent,&pref,vars);
				qApp->processEvents();
				insert(SCRIPTIO_STR9);
				insert(threadData->subprogramPath[c]);
				if(cleanSubFileContent==NULL)
				{
					insert("\nPreprocessor Error\n");
					subScript=NULL;
				}
				else 
				{
					subScript=new Script(scriptObject,NULL,&pref,vars,threadData);
					subScript->split(cleanSubFileContent);
				}
				delete[]subFileContent;
				threadData->subprograms.NewItem(subScript);
			}
		}
	}
	qApp->processEvents();
	if(!errorFlag)
	{
		insert(SCRIPTIO_STR10);
		runButton->setEnabled(true);
	}
	else {
		insert(SCRIPTIO_STR11);
		runButton->setEnabled(false);
	}
}



void ScriptIOWidget::initDebugging(QString *code)
{
	int pos1=0,pos2=0;
	bool quote=false;
	QString line;
	int lineLen;
	int lineCount=0;
	int run=1;
	while(run)
	{
		pos2=code->find("\n",pos1);
		if(pos2<0)
		{
			pos2=code->length();
			run=0;
		}
		lineCount++;
		line=code->mid(pos1,pos2-pos1);
		lineLen=line.length();
		for(int c=0; c<lineLen && !(line[c]=='/' && line[c+1]=='/'); c++)
		{
			if(line[c]=='\"')
				quote=!quote;
			else if(!quote && line[c]==';')
			{
				semicolonLines.NewItem(lineCount);
			}
		}
		pos1=pos2+1;
	}
}


void ScriptIOWidget::editSlot(int type)
{
	if(hasFocus())
	{
		switch(type)
		{
			case EDITUNDO:
				break;
			case EDITREDO:
				break;
			case EDITCUT:
				break;
			case EDITCOPY:
				break;
			case EDITPASTE:
				QClipboard*board=QApplication::clipboard();
				insert(board->text(QClipboard::Clipboard));
				break;
		}
	}
}


void ScriptIOWidget::scrollbarSlot(int)
{
	paintEvent(NULL);
	
}


void ScriptIOWidget::timerSlot()
{
	/*
	if(qApp->hasPendingEvents())
	{
		redrawTime+=2000;
		timerInterval=1;
		t->changeInterval(timerInterval);
		threadData->sleepTime+=2000;
		threadData->usleep=true;
//		QApplication::sendPostedEvents();
		perror("waiting "+QString::number(threadData->sleepTime));
	}
	else {
		redrawTime=20000;
		if(timerInterval!=25)
		{
			timerInterval=25;
			t->changeInterval(timerInterval);
			threadData->sleepTime=1000;
		}
		threadData->usleep=true;
	}
	*/
	repaint(20,50,ioFieldWidth,ioFieldHeight,false);
}









