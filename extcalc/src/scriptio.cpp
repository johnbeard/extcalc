/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptio.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
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
//		maximizeButton->setText(CALCWIDGETC_STR1);
		maximizeButton->setIconSet(*maximizeIcon);
		resizeEvent(NULL);
	}
	else 
	{
		calcButtons->hide();
		extButtons->hide();
//		maximizeButton->setText(CALCWIDGETC_STR2);
		maximizeButton->setIconSet(*minimizeIcon);
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
			if(pref.clearScriptMemory)
				clearMemSlot();
		}
		setDisplayMode(SCRIPTTEXT);
	}
}

void ScriptIOWidget::clearMemSlot()
{
	for(int c=0; c<VARNUM; c++)
	{
		threadData->vars[c]=(Number*)realloc(threadData->vars[c],sizeof(Number));
		threadData->numlen[c]=1;
		threadData->dimension[c][0]=threadData->dimension[c][1]=1;
	}
}

void ScriptIOWidget::paintEvent(QPaintEvent*)
{
	if(displayType==SCRIPTTEXT)
	{
		buffer->fill();
		QPainter p;
		p.begin(buffer);
		p.setFont(*drawFont);
		p.setBackgroundMode(Qt::OpaqueMode);
		int lineMemLen=lines.GetLen();
		int scrollbarPos;
		
		if(inputMode==IMSCRIPTING)
		{
			scrollbarPos=lineMemLen-lineNum;
			for(int c=scrollbarPos; c<scrollbarPos+lineNum; c++)
			p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c]);
		}
		else {
			if(inputMode!=IMDEFAULT)
				scrollbarPos=lineMemLen-lineNum;
			else scrollbarPos=scrollBar->value();
			
			int startRow,startLine,endRow,endLine;
			if(selectStartLine> selectEndLine || selectStartLine==selectEndLine && selectStartRow>selectEndRow)
			{
				startRow=selectEndRow;
				startLine=selectEndLine;
				endRow=selectStartRow;
				endLine=selectStartLine;
			}
			else{
				startRow=selectStartRow;
				startLine=selectStartLine;
				endRow=selectEndRow;
				endLine=selectEndLine;
			}
			if(startLine<scrollbarPos && endLine>=scrollbarPos)
			{
				p.setBackgroundColor(QColor(0,0,0));
				p.setPen(QColor(255,255,255));
			}
			
			for(int c=scrollbarPos; c<scrollbarPos+lineNum; c++)
			{
				if(c!=startLine &&c!=endLine)
					p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c]);
				else if(startLine==endLine)
				{
					p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c].left(startRow));
					p.setBackgroundColor(QColor(0,0,0));
					p.setPen(QColor(255,255,255));
					p.drawText(startRow*charWidth,charHeight*(c+1-scrollbarPos),lines[c].mid(startRow,startRow-endRow));
					p.setBackgroundColor(QColor(255,255,255));
					p.setPen(QColor(0,0,0));
					p.drawText(endRow*charWidth,charHeight*(c+1-scrollbarPos),lines[c].right(lines[c].length()-endRow));
		
				}
				else {
					
					if(c==startLine)
					{
						p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c].left(startRow));
						p.setBackgroundColor(QColor(0,0,0));
						p.setPen(QColor(255,255,255));
						p.drawText(startRow*charWidth,charHeight*(c+1-scrollbarPos),lines[c].right(lines[c].length()-startRow));
					}
					if(c==endLine)
					{
						p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c].left(endRow));
						p.setBackgroundColor(QColor(255,255,255));
						p.setPen(QColor(0,0,0));
						p.drawText(endRow*charWidth,charHeight*(c+1-scrollbarPos),lines[c].right(lines[c].length()-endRow));
					}
				}
			}
		}
	
		
	
	
		
		
		if((hasFocus() && inputMode==IMDEFAULT) || inputMode==IMGETLINE)
			p.drawLine(charWidth*cursorX,charHeight*(cursorY-scrollbarPos),charWidth*cursorX,charHeight*(cursorY+1-scrollbarPos));
	
		p.end();
		p.begin(this);

		p.drawPixmap(ioFieldX,ioFieldY,*buffer);
		p.end();
	}
	else if(displayType==SCRIPT3D)
		glWindow->repaint(true);
	else {
		QPainter p;
/*		buffer->fill();
		p.begin(buffer);
		p.drawText(100,100,"Hallo");
		p.end();
*/		p.begin(this);

		p.drawPixmap(ioFieldX,ioFieldY,*buffer);

		p.end();
	}

}



void ScriptIOWidget::resizeEvent(QResizeEvent*)
{
	int width=geometry().right()-geometry().left();
	int height=geometry().bottom()-geometry().top();
	
	
	if(maximized)
	{
//		maximizeButton->setGeometry(10,height-45,90,35);
//		killButton->setGeometry(110,height-45,90,35);
//		runButton->setGeometry(210,height-45,90,35);
		
		dockArea->setGeometry(0,menuBottom,width,35);
		
		if(inputMode==IMDEFAULT)
			scrollBar->setGeometry(width-40,menuBottom+40,20,height-100);
		ioFieldWidth=width-40;
		ioFieldHeight=height-100;
		ioFieldX=20;
		ioFieldY=menuBottom+40;
	}
	else {
		calcButtons->setGeometry(20,height-220,280,200);
		extButtons->setGeometry(320,height-180,300,160);
//		maximizeButton->setGeometry(325,height-220,90,35);
//		killButton->setGeometry(425,height-220,90,35);
//		runButton->setGeometry(525,height-220,90,35);
		dockArea->setGeometry(325,height-220,width-345,35);

		if(inputMode==IMDEFAULT)
			scrollBar->setGeometry(width-40,50,20,height-290);
		ioFieldWidth=width-40;
		ioFieldHeight=height-290;
		ioFieldX=20;
		ioFieldY=50;
	}
	if(displayType==SCRIPT3D)
	{
		int glWidth=ioFieldWidth,glHeight=ioFieldHeight;
		if(autosize)
		{
			if(glWidth>glHeight)
				glWidth=glHeight;
			else glHeight=glWidth;
		}

		glWindow->setGeometry(10+(width-20-glWidth)/2,ioFieldY,glWidth,glHeight);

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
//	buffer->fill();
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
				inputBuffer=(char*)calloc(1,1);
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
				inputBuffer=(char*)calloc(1,1);
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
				repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
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
				repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
			}
			break;
		default:
		{
			if(e->state() == Qt::ControlButton || e->stateAfter() == Qt::ControlButton)
			{
				switch(e->key())
				{
					case Qt::Key_V:
						contextMenuSlot(EDITPASTE);
						break;
					case Qt::Key_C:
						contextMenuSlot(EDITCOPY);
						break;
					case Qt::Key_A:
						contextMenuSlot(EDITSELECTALL);
						break;
				}
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
						memmove(&inputBuffer[bufferCursor+1],&inputBuffer[bufferCursor],bufLen-bufferCursor+1);
					else inputBuffer[bufferCursor+1]=(char)0;
					inputBuffer[bufferCursor]=(char)e->ascii();
					bufferCursor++;
					if(inputMode==IMGETLINE)
					{
						insert(e->text());
						int cx=cursorX,cy=cursorY;
						insert(&inputBuffer[bufferCursor],false);
						cursorX=cx;
						cursorY=cy;
						repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
					}
				}
				else if(inputMode==IMGETKEY)
				{
					char*strBuf=(char*)malloc(2);
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
	threadData->eventCount--;
	if(scriptExec && script!=NULL)
	{
//		perror("customEvent: "+QString::number(ev->type())+" "+QString::number(pthread_self()));
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
			case SIGCALLLIST:
			{
				int listNum;
				memcpy(&listNum,ev->data(),sizeof(int));
				free(ev->data());
				glWindow->scrCallList(listNum);
				break;
			}
			case SIGSTARTLIST:
			{
				glWindow->scrStartList();
				break;
			}
			case SIGENDLIST:
			{
				int index=glWindow->scrEndList();
				int *listData=(int*)malloc(sizeof(int));
				*listData=index;
				threadData->data=listData;
				break;
			}
			case SIGGRAPHSHOW:
			{
				glWindow->repaint();
				break;
			}
			case SIGGRAPHCLEAR:
			{
				glWindow->scrClear();
				break;
			}
			case SIGGRAPHEND:
			{
				glWindow->scrEnd();
				break;
			}
			case SIGGRAPHBEGIN:
			{

				int num=*((int*)ev->data());
				switch(num)
				{
					case 0:
						glWindow->scrBegin(GL_POINTS);
						break;
					case 1:
						glWindow->scrBegin(GL_LINES);
						break;
					case 2:
						glWindow->scrBegin(GL_LINE_STRIP);
						break;
					case 3:
						glWindow->scrBegin(GL_LINE_LOOP);
						break;
					case 4:
						glWindow->scrBegin(GL_TRIANGLES);
						break;
					case 5:
						glWindow->scrBegin(GL_TRIANGLE_STRIP);
						break;
					case 6:
						glWindow->scrBegin(GL_TRIANGLE_FAN);
						break;
					case 7:
						glWindow->scrBegin(GL_QUADS);
						break;
					case 8:
						glWindow->scrBegin(GL_QUAD_STRIP);
						break;
					default:
						glWindow->scrBegin(GL_POLYGON);
						break;
				}
				
				free(ev->data());
				break;
			}
			case SIGGRAPHVERTEX:
			{
				glWindow->scrVertex(((double*)ev->data())[0],((double*)ev->data())[1],((double*)ev->data())[2]);
				free(ev->data());
				break;
			}
			case SIGGRAPHCOLOR:
			{
				glWindow->scrColor(((int*)ev->data())[0],((int*)ev->data())[1],((int*)ev->data())[2]);
				free(ev->data());
				break;
			}
			case SIGGRAPHROTATE:
			{
				glWindow->scrRotate(((double*)ev->data())[3],((double*)ev->data())[0],((double*)ev->data())[1],((double*)ev->data())[2]);
				free(ev->data());
				break;
			}
			case SIGIDENTITY:
			{
				glWindow->scrIdentity();
				break;
			}
			case SIGGRAPHSCALE:
			{
				glWindow->scrScale(((double*)ev->data())[0],((double*)ev->data())[1],((double*)ev->data())[2]);
				free(ev->data());
				break;
			}
			case SIGGRAPHTRANSLATE:
			{
				glWindow->scrTranslate(((double*)ev->data())[0],((double*)ev->data())[1],((double*)ev->data())[2]);
				free(ev->data());
				break;
			}
			case SIGGRAPHTEXT:
			{
				int x=((int*)ev->data())[0],y=((int*)ev->data())[1];
				glWindow->scrText(x,y,&((char*)ev->data())[2*sizeof(int)]);
				free(ev->data());
				break;
			}
			case SIGDRAW:
			{
				if(displayType==SCRIPT2D)
				{
					char*data=(char*)ev->data();
					char command=data[0];
					QPainter p;
					p.begin(buffer);
					p.setPen(*drawPen);
					int r,g,b,x,y,xs,ys,xe,ye;
					switch(command)
					{
						case 0:
							buffer->fill();
							break;
						case 1:
							memcpy(&x,&data[1],4);
							memcpy(&y,&data[5],4);
							p.drawPoint(x,y);
							break;
						case 2:
							memcpy(&r,&data[1],4);
							memcpy(&g,&data[5],4);
							memcpy(&b,&data[9],4);
							drawPen->setColor(QColor(r,g,b));
							break;
						case 3:
							memcpy(&x,&data[1],4);
							memcpy(&y,&data[5],4);
							p.setFont(*drawFont);
							p.setBackgroundMode(Qt::OpaqueMode);
							p.drawText(x,y,&data[9]);
							break;
						case 4:
							memcpy(&xs,&data[1],4);
							memcpy(&ys,&data[5],4);
							memcpy(&xe,&data[9],4);
							memcpy(&ye,&data[13],4);
							p.drawLine(xs,ys,xe,ye);
							break;
						case 5:
							memcpy(&xs,&data[1],4);
							memcpy(&ys,&data[5],4);
							memcpy(&xe,&data[9],4);
							memcpy(&ye,&data[13],4);
							p.drawRect(xs,ys,xe,ye);
							break;
						case 6:
							memcpy(&xs,&data[1],4);
							memcpy(&ys,&data[5],4);
							memcpy(&xe,&data[9],4);
							memcpy(&ye,&data[13],4);
							p.drawEllipse(xs,ys,xe,ye);
							break;
					}
					p.end();
					gettimeofday(&currentTime,NULL);
					if(currentTime.tv_sec > drawTime.tv_sec || currentTime.tv_usec-drawTime.tv_usec > 20000)
					{
						gettimeofday(&drawTime,NULL);
						if(!t->isActive())
							t->start(30,true);
					}
				}
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
						inputBuffer=(char*)calloc(1,1);
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
						inputBuffer=(char*)calloc(1,1);
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
			case SIGFILEREAD:
			{
				QString path((char*)ev->data());
				free(ev->data());

				int pos=path.findRev('/');
				if(pos!=-1)
					path=path.right(path.length()-pos-1);
				path=pref.scriptPath+"/"+pref.dataDirName+"/"+path;

				char*fileData;
				struct stat fileStat;
				FILE*f;
				if(pref.scriptPath.length()>0 && lstat(path,&fileStat)==0)
				{
					f=fopen(path,"r");
					if(f!=NULL && fileStat.st_size>0 && S_ISREG(fileStat.st_mode))
					{
						fileData=new char[fileStat.st_size+1];
						fileData[fileStat.st_size]=(char)0;
						fread(fileData,fileStat.st_size,1,f);
						fclose(f);
					}
					else fileData=NULL;
				}
				else fileData=NULL;
				
				if(fileData==NULL)
					threadData->data=calloc(2,1);
				else threadData->data=fileData;
				break;
			}
			case SIGFILEAPPEND:
			{
				QString path((char*)ev->data());
				int pathLen=strlen((char*)ev->data());

				int pos=path.findRev('/');
				if(pos!=-1)
					path=path.right(path.length()-pos-1);
				path=pref.scriptPath+"/"+pref.dataDirName+"/"+path;
				
				FILE*f;
				if(pref.scriptPath.length()>0)
				{
					f=fopen(path,"a");
					if(f!=NULL)
					{
						int dataLen=strlen(&((char*)ev->data())[pathLen+1]);
						fwrite(&((char*)ev->data())[pathLen+1],dataLen,1,f);
						fclose(f);
					}
				}
				free(ev->data());
				break;
			}
			case SIGFILEWRITE:
			{
				QString path((char*)ev->data());
				int pathLen=strlen((char*)ev->data());

				int pos=path.findRev('/');
				if(pos!=-1)
					path=path.right(path.length()-pos-1);
				path=pref.scriptPath+"/"+pref.dataDirName+"/"+path;
				
				FILE*f;
				if(pref.scriptPath.length()>0)
				{
					f=fopen(path,"w");
					if(f!=NULL)
					{
						int dataLen=strlen(&((char*)ev->data())[pathLen+1]);
						fwrite(&((char*)ev->data())[pathLen+1],dataLen,1,f);
						fclose(f);
					}
				}
				free(ev->data());
				break;
			}
			case SIGFILEREMOVE:
			{
				QString path((char*)ev->data());
				free(ev->data());

				int pos=path.findRev('/');
				if(pos!=-1)
					path=path.right(path.length()-pos-1);
				path=pref.scriptPath+"/"+pref.dataDirName+"/"+path;
				
				if(pref.scriptPath.length()>0)
					remove(path);
				
				break;
			}
			case SIGFINISHED:		//script stopped
			{
				setDisplayMode(SCRIPTTEXT);
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
				if(pref.clearScriptMemory)
					clearMemSlot();
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
	if(e->button()==Qt::RightButton)
	{
		if(inputMode!=IMSCRIPTING)
		{
			QPoint menuPos=e->pos();
			menuPos=mapToGlobal(menuPos);
			contextMenu->popup(menuPos,EDITCOPY);
		}
		return;
	}
	int scrollbarPos=scrollBar->value();
	selectEndLine=selectStartLine=(e->y()-ioFieldY)/charHeight+scrollbarPos;
	selectEndRow=selectStartRow=(e->x()-ioFieldX)/charWidth;
	
	if(inputMode!=IMDEFAULT)
		return;
	int mouseX=e->x()-ioFieldX,mouseY=e->y()-ioFieldY;

	if(mouseX>=0 && mouseX <=ioFieldWidth && mouseY>=0 && mouseY<=ioFieldHeight)
	{
		cursorX=(mouseX+charWidth/2)/charWidth;
		cursorY=(mouseY)/charHeight+scrollBar->value();
		if(cursorX>charNum)
			cursorX=charNum;
		if(cursorY>scrollBar->value()+lineNum)
			cursorY=scrollBar->value()+lineNum;
	}
	


	repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
}
void ScriptIOWidget::mouseReleaseEvent(QMouseEvent*me)
{
	int scrollbarPos=scrollBar->value();
//	p.drawText(0,charHeight*(c+1-scrollbarPos),lines[c]);
	selectEndLine=(me->y()-ioFieldY)/charHeight+scrollbarPos;
	selectEndRow=(me->x()-ioFieldX)/charWidth;
	repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
}
void ScriptIOWidget::mouseMoveEvent(QMouseEvent*me)
{
	int scrollbarPos=scrollBar->value();
	int oldEndLine=selectEndLine,oldEndRow=selectEndRow;
	selectEndLine=(me->y()-ioFieldY)/charHeight+scrollbarPos;
	selectEndRow=(me->x()-ioFieldX)/charWidth;
	if(selectEndRow<0)
		selectEndRow=0;
	if(selectEndLine<0)
		selectEndLine=0;
	if(selectEndLine<scrollbarPos)
		scrollBar->setValue(selectEndLine);
	else if(selectEndLine>scrollbarPos+lineNum)
		scrollBar->setValue(selectEndLine-lineNum);
//	perror(QString::number(selectStartLine)+" "+QString::number(selectStartRow)+" "+QString::number(selectEndLine)+" "+QString::number(selectEndRow));
	if(oldEndRow!=selectEndRow || oldEndLine!=selectEndLine)
		repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
}


void ScriptIOWidget::insert(QString text,bool redraw)
{
	int len=text.length();
	int pos1=0,pos2=0,tabpos=0;
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
		while((tabpos=lines[cursorY].find('\t'))!=-1)
		{
			lines[cursorY].remove(tabpos,1);
			for(int c=0; c<(8-tabpos%8); c++)
				lines[cursorY].insert(tabpos,' ');
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
			while((tabpos=lines[cursorY].find('\t'))!=-1)
			{
				lines[cursorY].remove(tabpos,1);
				for(int c=0; c<(8-tabpos%8); c++)
					lines[cursorY].insert(tabpos,' ');
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
	//	pos1--;
	}
	
	lines[cursorY].replace(cursorX,len-pos1,text.mid(pos1,len-pos1));
	cursorX+=len-pos1;
	while((tabpos=lines[cursorY].find('\t'))!=-1)
	{
		lines[cursorY].remove(tabpos,1);
		for(int c=0; c<(8-tabpos%8); c++)
			lines[cursorY].insert(tabpos,' ');
		cursorX+=(8-tabpos%8)-1;
	}
	
	if(redraw)
		repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);

}


void ScriptIOWidget::backKey()
{
	if(cursorX>0)
	{
		lines[cursorY].remove(cursorX-1,1);
		cursorX--;
		repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
	}
}

void ScriptIOWidget::deleteKey()
{
		lines[cursorY].remove(cursorX,1);
		repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
}



void ScriptIOWidget::clearAll()
{
	cursorX=0;
	cursorY=lines.GetLen()-lineNum;
	for(int c=0; c<lines.GetLen(); c++)
	{
		lines[c].fill(' ',charNum);
	}
	repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
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
	threadData->eventCount=0;
	
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
	
	runningPref=pref;
	
	//test
	searchScripts(code);
	countDifference=0;
	initDebugging(code);
	runningPref.scriptGraphicsMode=SCRIPTTEXT;
	
	char* cleanString=preprocessor(code,&runningPref,true);
/*	perror("after");
	if(ret!=0)
	{
		switch(ret)
		{
			case PPINVALIDARGUMENT:
				insert("\nPreference Preprocessor: Invalid preference argument\n");
				return;
			case PPINVALIDPREF:
				insert("\nPreference Preprocessor: Invalid preference\n");
				return;	
			case PPEMPTY:
				insert("\nPreference Preprocessor: Result script file empty\n");
				return;
			default:
				insert("\nPreference Preprocessor: Unknown error\n");
				return;
		}
	}
	ret=macroPreprocessor(code);
	if(ret!=0)
	{
		if(ret==PINVALIDCOMMAND)
			insert("\nMacro Preprocessor: Invalid Preprocessor Command\n");
		else if(ret==MPINVALIDMACRO)
			insert("\nMacro Preprocessor: Invalid Macro\n");
		return;
	}
	



	char*cleanString=checkString(*code,&runningPref);
*/
	modeRequest=runningPref.scriptGraphicsMode;
	if(modeRequest==SCRIPT3D)
		glWindow->setPref(runningPref);
	delete scriptObject;
	insert(SCRIPTIO_STR8);
	if(cleanString==NULL)
	{
		insert("\nPreprocessor Error\n");
		return;
	}
	scriptObject=new Script(NULL,cleanString,&runningPref,vars,threadData);
	loadSubScripts();
	free(cleanString);

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
			inputBuffer=(char*)calloc(1,1);
		}

	bufferCursor=0;
	inputMode=IMSCRIPTING;

	scriptExec=true;
	script=new ScriptThread(scriptObject,this);

	killButton->setEnabled(true);
	scrollBar->hide();
	if(modeRequest==SCRIPT3D)
		setDisplayMode(SCRIPT3D);
	else if(modeRequest==SCRIPT2D)
		setDisplayMode(SCRIPT2D);
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
	Preferences tmpPref=pref;
	char*cleanStr=preprocessor(code,&tmpPref,true);
	if(cleanStr==NULL)
		return;
	char*scriptName;
	QString filePath;
	int len=strlen(cleanStr);
	int pos=0,pos2;
	FILE*subFile;
	while(pos<len)
	{
		if(strncmp(&cleanStr[pos],"run(\"",4) == 0) //run("")
		{
			pos2=bracketFind(cleanStr,")",pos+4);
			if(pos2-pos<7 || cleanStr[pos2-1]!='\"')
			{
				pos++;
				continue;
			}
			scriptName=new char[pos2-pos-5];
			strcopy(scriptName,&cleanStr[pos+5],pos2-pos-6);
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
	delete[] cleanStr;
}


void ScriptIOWidget::loadSubScripts()
{
	QString filePath;
	struct stat fileStat;
	char*subFileContent;
	char*cleanSubFileContent;
	QString qSubFileContent;
	Script*subScript;
	Preferences tmpPref=pref;
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
				cleanSubFileContent=preprocessor(&qSubFileContent,&tmpPref,true);
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


int ScriptIOWidget::preferencesPreprocessor(QString *code,Preferences*pref)
{
	int pos=0,newlinePos=-1,end,commentPos=0;
	QString configLine;
	bool quote=false;
	
	while(pos<(signed)code->length())
	{
		if(quote)
		{
			if((*code)[pos]=='"')
				quote=false;
		}
		else {
			if((*code)[pos]=='"')
				quote=true;
			else if((*code)[pos]=='/' && (*code)[pos+1]=='/')
			{
				pos=code->find('\n',pos);
				if(pos==-1)
					pos=code->length();
				else newlinePos=pos;
			}
			else if((*code)[pos]=='\n')
				newlinePos=pos;
			else if((*code)[pos]=='#')
			{
				end=code->find('\n',pos);
				if(end<0)
					end=code->length();
				
				configLine=code->mid(newlinePos+1,end-newlinePos-1);
				
				pos=newlinePos;
				configLine=configLine.stripWhiteSpace();
				if(configLine.find("#config")==0)
					configLine=configLine.right(configLine.length()-7);
				else
				{
					pos=newlinePos+2;
					continue;
				}
				code->remove(newlinePos+1,end-newlinePos-1);
				if((commentPos=configLine.find("//"))!=-1)
					configLine=configLine.left(commentPos);
				
				configLine=configLine.stripWhiteSpace();
				
				if(configLine=="complexon")
					pref->complex=true;
				else if(configLine=="complexoff")
					pref->complex=false;
				else if(configLine=="angledeg")
					pref->angle=DEG;
				else if(configLine=="anglerad")
					pref->angle=RAD;
				else if(configLine=="anglegra")
					pref->angle=GRA;
				else if(configLine=="modebase")
				{
					pref->calcType=BASE;
					pref->base=DEC;
				}
				else if(configLine=="modescientific")
					pref->calcType=SCIENTIFIC;
				else if(configLine=="clearmemory")
				{
					if(!pref->clearScriptMemory)
						clearMemSlot();
				}
				else if(configLine.find("outputlength")==0)
				{
					configLine=configLine.right(configLine.length()-12);
					int num=configLine.toInt();
					if(num>=2 && num<=pref->precision)
						pref->outputLength=num;
					else return PPINVALIDARGUMENT;
				}
				else if(configLine=="gl")
					modeRequest=SCRIPT3D;
				else if(configLine=="graphics")
					modeRequest=SCRIPT2D;
				else if(configLine=="rasteron")
					pref->raster=true;
				else if(configLine=="rasteroff")
					pref->raster=false;
				else if(configLine=="labelson")
					pref->label=true;
				else if(configLine=="labelsoff")
					pref->label=false;
				else if(configLine=="axeson")
					pref->axis=true;
				else if(configLine=="axesoff")
					pref->axis=false;
				else if(configLine=="autoscaleon")
					autosize=true;
				else if(configLine=="autoscaleoff")
					autosize=false;
				else return PPINVALIDPREF;
			}
		}
		pos++;
	}
	if(code->length()<=0)
		return PPEMPTY;
	else return 0;
}
int ScriptIOWidget::macroPreprocessor(QString *code)
{
	perror("macroPreprocessor: "+(*code));
	int pos=0,newlinePos=-1,end,commentPos=0,seperatorPos,macroPos;
	QString macroLine,macro,replacement;
	bool quote=false;
	
	while(pos<(signed)code->length())
	{
		perror("outer loop");
		if(quote)
		{
			if((*code)[pos]=='"')
				quote=false;
		}
		else {
			if((*code)[pos]=='"')
				quote=true;
			else if((*code)[pos]=='/' && (*code)[pos+1]=='/')
			{
				pos=code->find('\n',pos);
				if(pos==-1)
					pos=code->length();
				else newlinePos=pos;
			}
			else if((*code)[pos]=='\n')
				newlinePos=pos;
			else if((*code)[pos]=='#')
			{
				end=code->find('\n',pos);
				if(end<0)
					end=code->length();
				
				macroLine=code->mid(newlinePos+1,end-newlinePos-1);
				
				pos=newlinePos;
				macroLine=macroLine.stripWhiteSpace();
				if(macroLine.find("#define")==0)
					macroLine=macroLine.right(macroLine.length()-7);
				else return PINVALIDCOMMAND;
				if((commentPos=macroLine.find("//"))!=-1)
					macroLine=macroLine.left(commentPos);
				
				code->remove(newlinePos+1,end-newlinePos-1);
				macroLine=macroLine.stripWhiteSpace();

				
				seperatorPos=macroLine.find(" ");
				if(seperatorPos==-1)
					seperatorPos=macroLine.find("\t");
				if(seperatorPos>0)
				{
					macro=macroLine.left(seperatorPos);
					replacement=macroLine.right(macroLine.length()-seperatorPos-1);
					replacement=replacement.stripWhiteSpace();
					
					if(!(macro[0]>='a' && macro[0]<='z' ||
					    macro[0]>='A' && macro[0]<='A' ||
						macro[0]=='_'))
						return MPINVALIDMACRO;
					for(unsigned int c=1; c<macro.length(); c++)
					{
						if(!(macro[c]>='a' && macro[c]<='z' ||
						     macro[c]>='A' && macro[c]<='A' ||
						     macro[c]>='0' && macro[c]<='9' ||
							 macro[c]=='_'))
							return MPINVALIDMACRO;
					}

					macroPos=0;
					while((macroPos=code->find(macro,macroPos+1))!=-1)
					{
						if(!(macroPos>0 && ((*code)[macroPos-1] >= 'a' && (*code)[macroPos-1]<='z' ||
											   (*code)[macroPos-1] >= 'A' && (*code)[macroPos-1]<='Z'
											   || (*code)[macroPos-1] == '_') ||
											   code->length()>macroPos+macro.length() &&
											   ((*code)[macroPos+macro.length()] >= 'a' && (*code)[macroPos+macro.length()]<='z' ||
											   (*code)[macroPos+macro.length()] >= 'A' && (*code)[macroPos+macro.length()]<='Z' ||
											   (*code)[macroPos+macro.length()] >= '0' && (*code)[macroPos+macro.length()]<='9'
											   || (*code)[macroPos+macro.length()] == '_')
							))
						{
							code->replace(macroPos,macro.length(),replacement);
						}
					}

				}
			}
		}
		pos++;
	}
	if(code->length()<=0)
		return MPEMPTY;
	else return 0;
}

void ScriptIOWidget::editSlot(int type)
{
	if(hasFocus())
	{
		if(type==EDITCOPY || type==EDITPASTE)
			contextMenuSlot(type);
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
	repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
}


void ScriptIOWidget::contextMenuSlot(int item)
{
	switch(item)
	{
		case EDITCOPY:
		{
			QClipboard*board=QApplication::clipboard();
			QString copyText;
			int startRow,startLine,endRow,endLine;
			if(selectStartLine> selectEndLine || selectStartLine==selectEndLine && selectStartRow>selectEndRow)
			{
				startRow=selectEndRow;
				startLine=selectEndLine;
				endRow=selectStartRow;
				endLine=selectStartLine;
			}
			else{
				startRow=selectStartRow;
				startLine=selectStartLine;
				endRow=selectEndRow;
				endLine=selectEndLine;
			}
			if(startLine==endLine)
				copyText=lines[startLine].mid(startRow,endRow-startRow);
			else {
				for(int c = startLine; c<=endLine; c++)
				{
					if(c==startLine)
						copyText=lines[c].right(lines[c].length()-startRow);
					else if(c==endLine)
					{
						copyText+="\n";
						copyText+=lines[c].left(endRow);
					}
					else{
						copyText+="\n";
						copyText+=lines[c];
					}
				}
			}
			if(copyText.length()>0)
				board->setText(copyText,QClipboard::Clipboard);
			break;
		}
		case EDITPASTE:
		{
			QClipboard*board=QApplication::clipboard();
			insert(board->text(QClipboard::Clipboard));
			int bufLen=strlen(inputBuffer);
			if(inputMode==IMGETLINE)
			{
				const char*clipText=board->text(QClipboard::Clipboard).ascii();
				bufLen=strlen(inputBuffer)+board->text(QClipboard::Clipboard).length();
				inputBuffer=(char*)realloc(inputBuffer,bufLen+1);
				
				if(bufferCursor==(signed)strlen(inputBuffer))
				{
					memcpy(&inputBuffer[bufferCursor],clipText,strlen(clipText)+1);
					bufferCursor=bufLen;
				}
				else {
					int cx=cursorX,cy=cursorY;
					insert(&inputBuffer[bufferCursor],false);
					cursorX=cx;
					cursorY=cy;
					memmove(&inputBuffer[bufferCursor+strlen(clipText)],&inputBuffer[bufferCursor],strlen(inputBuffer)-bufferCursor+1);
					memcpy(&inputBuffer[bufferCursor],clipText,strlen(clipText));
					bufferCursor+=strlen(clipText);
					repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
				}
			}
			break;
		}
		case EDITCUT:
			clearAll();
			break;
		case EDITSELECTALL:
			selectStartRow=0;
			selectStartLine=0;
			selectEndLine=lines.GetLen()-1;
			selectEndRow=lines[selectEndLine].length()-1;
			repaint(ioFieldX,ioFieldY,ioFieldWidth,ioFieldHeight,false);
			break;
	}
}

void ScriptIOWidget::setDisplayMode(int mode)
{
	displayType=mode;

	if(mode==SCRIPT3D)
	{
		glWindow->show();
		glWindow->scrReset();
		glWindow->resetRotation();
		resizeEvent(NULL);
		repaint(true);
		
	}
	else {
		if(mode==SCRIPT2D)
		{
			drawPen->setColor(QColor(0,0,0));
			buffer->fill();
		}
		glWindow->hide();
		repaint(true);
	}
	
}


GLuint ScriptGL::draw3dAxes()
{
	
	double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin,zSize=pref.zmax-pref.zmin;
	int xSteps=(int)(xSize/pref.rasterSizeX);
	if(xSteps>200)
		pref.rasterSizeX=xSize/200;
	int ySteps=(int)(ySize/pref.rasterSizeY);
	if(ySteps>200)
		pref.rasterSizeY=ySize/200;
	int zSteps=(int)(zSize/pref.rasterSizeZ);
	if(zSteps>200)
		pref.rasterSizeZ=zSize/200;
	GLuint list;

	list = glGenLists( 1 );
	glEnable(GL_DEPTH_TEST);
	glNewList( list, GL_COMPILE );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	glBegin(GL_LINES);
	if(pref.raster)
	{
		qglColor( QColor(220,220,220) );
		for(float c=pref.xmin-fmod(pref.xmin,pref.rasterSizeX)+pref.rasterSizeX; c<pref.xmax; c+=pref.rasterSizeX)		
		{
			glVertex3f(c,pref.ymin,pref.zmax);//back side
			glVertex3f(c,pref.ymax,pref.zmax);
			glVertex3f(c,pref.ymin,pref.zmin);// bottom side
			glVertex3f(c,pref.ymin,pref.zmax);
		}
		for(float c=pref.ymin-fmod(pref.ymin,pref.rasterSizeY)+pref.rasterSizeY; c<pref.ymax; c+=pref.rasterSizeY)			
		{
			glVertex3f(pref.xmin,c,pref.zmax);//back side
			glVertex3f(pref.xmax,c,pref.zmax);
			glVertex3f(pref.xmin,c,pref.zmin);//left side
			glVertex3f(pref.xmin,c,pref.zmax);
		}

		for(float c=pref.zmin-fmod(pref.zmin,pref.rasterSizeZ)+pref.rasterSizeZ; c<pref.zmax; c+=pref.rasterSizeZ)	
		{
			glVertex3f(pref.xmin,pref.ymin,c);// bottom side
			glVertex3f(pref.xmax,pref.ymin,c);
			glVertex3f(pref.xmin,pref.ymin,c);//left side
			glVertex3f(pref.xmin,pref.ymax,c);
		}
	}
	
	
	if(pref.axis)
	{
		double xAxes=0.0,yAxes=0.0,zAxes=0.0;
		if(pref.xmin > 0.0)
			xAxes=pref.xmin;
		else if(pref.xmax < 0.0)
			xAxes=pref.xmax;
		if(pref.ymin > 0.0)
			yAxes=pref.ymin;
		else if(pref.ymax < 0.0)
			yAxes=pref.ymax;
		if(pref.zmin > 0.0)
			zAxes=pref.zmin;
		else if(pref.xmax < 0.0)
			zAxes=pref.zmax;
		
		qglColor( QColor(150,150,150) );
		glVertex3f(pref.xmin,yAxes,zAxes);
		glVertex3f(pref.xmax,yAxes,zAxes);
		
		glVertex3f(xAxes,pref.ymin,zAxes);
		glVertex3f(xAxes,pref.ymax,zAxes);
		
		glVertex3f(xAxes,yAxes,pref.zmin);
		glVertex3f(xAxes,yAxes,pref.zmax);
		
		glVertex3f(pref.xmax-xSize*0.015,yAxes+ySize*0.015,zAxes);
		glVertex3f(pref.xmax,yAxes,zAxes);
		glVertex3f(pref.xmax-xSize*0.015,yAxes+ySize*-0.015,zAxes);
		glVertex3f(pref.xmax,yAxes,zAxes);
		
		glVertex3f(xAxes+xSize*0.015,pref.ymax-ySize*0.015,zAxes);
		glVertex3f(xAxes,pref.ymax,zAxes);
		glVertex3f(xAxes+xSize*-0.015,pref.ymax-ySize*0.015,zAxes);
		glVertex3f(xAxes,pref.ymax,zAxes);
		
		glVertex3f(xAxes+xSize*0.015,yAxes,pref.zmax-zSize*0.015);
		glVertex3f(xAxes,yAxes,pref.zmax);
		glVertex3f(xAxes+xSize*-0.015,yAxes,pref.zmax-zSize*0.015);
		glVertex3f(xAxes,yAxes,pref.zmax);
	}
	glEnd();	
	glEndList();

	return list;
}


void ScriptGL::mouseMoveEvent(QMouseEvent*e)
{

	if(e->state() == Qt::RightButton)
	{
		if(unlock)
		{
			int moveX=e->x()-mouseX;
			int moveY=e->y()-mouseY;
			
			xRotation+=moveX;
			yRotation+=moveY;
			if(xRotation>360)
				xRotation-=360;
			if(yRotation>360)
				yRotation -=360;
			if(xRotation<0)
				xRotation+=360;
			if(yRotation<0)
				yRotation+=360;
			repaint();
		}
		mouseX=e->x();
		mouseY=e->y();
	}
}


void ScriptGL::mousePressEvent(QMouseEvent*e)
{
	mouseX=e->x();
	mouseY=e->y();
    if(e->stateAfter()==Qt::RightButton)
			unlock=true;
}

void ScriptGL::mouseReleaseEvent(QMouseEvent*)
{
		unlock=false;
}

void ScriptGL::wheelEvent(QWheelEvent*e)
{

		zMove+=e->delta()/120;
		e->accept();
		repaint();
		if(zMove<-27)
			zMove=-27;
}

void ScriptGL::initializeGL()
{
	if(paintActive)
		glEnd();
	if(drawListActive)
		drawListControl();
	if(staticListActive)
	{
		glEndList();
		staticListActive=false;
	}
	glClearColor( 1.0,1.0,1.0,1.0 ); 
	if(axes!=0xffffffff)
		glDeleteLists(axes,1);

	axes=draw3dAxes();
	scrClear();
	while(staticLists.GetLen()>0)
	{
		glDeleteLists(staticLists[0],1);
		staticLists.DeleteItem(0);
	}

	glShadeModel( GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode( GL_MODELVIEW );
}


void ScriptGL::resizeGL( int w, int h )
{
	glViewport( 0, 0, (GLint)w, (GLint)h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -10.0, 10.0, -10.0, 10.0, 5.0, 15.0 );
	glMatrixMode( GL_MODELVIEW );
}


void ScriptGL::paintGL()
{
	if(paintActive)
		return;
	if(drawListActive)
		drawListControl();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(-10.0,10.0,-10.0,10.0,1.0,100.0);
	glScalef(1.0,1.0,-0.05);
	glTranslatef(0.0,0.0,37.0+(float)zMove);
	glRotatef(xRotation,0.0f,1.0f,0.0f);
	glRotatef(yRotation,1.0f,0.0f,0.0f);	
	glScalef(20.0/(pref.xmax-pref.xmin),20.0/(pref.ymax-pref.ymin),20.0/(pref.zmax-pref.zmin));
	glTranslatef(((pref.xmax-pref.xmin)/2+pref.xmin)*-1,((pref.ymax-pref.ymin)/2+pref.ymin)*-1,((pref.zmax-pref.zmin)/2+pref.zmin)*-1);

	glCallList(axes);

	if(pref.label)
	{
		QFont stdFont("Helvetica");
		stdFont.setPixelSize(8);
		double xTrans=(pref.xmax-pref.xmin)/80;
		double yTrans=(pref.ymax-pref.ymin)/80;
		double staticX=xTrans,staticY=yTrans;
		double zTrans=(pref.zmax-pref.zmin)/80;
		double staticZ=zTrans;
		if(pref.zmax < zTrans)
			staticZ=pref.zmax-3*zTrans;
		else if(pref.zmin > -zTrans)
			staticZ=pref.zmin+zTrans;
			
		if(pref.xmax < xTrans)
			staticX=pref.xmax-3*xTrans;
		else if(pref.xmin > -xTrans)
			staticX=pref.xmin+xTrans;
		if(pref.ymax < yTrans)
			staticY=pref.ymax-3*yTrans;
		else if(pref.ymin > -yTrans)
			staticY=pref.ymin+yTrans;
		if(pref.graphType!=GRAPH3D)
			staticZ=0.0;
				
		qglColor( QColor(220,220,220) );
		for(float c=pref.xmin-fmod(pref.xmin,pref.rasterSizeX)+pref.rasterSizeX; c<pref.xmax; c+=pref.rasterSizeX)
			renderText(c-xTrans,staticY,staticZ,QString::number(c,'g',3),stdFont);
		for(float c=pref.ymin-fmod(pref.ymin,pref.rasterSizeY)+pref.rasterSizeY; c<pref.ymax; c+=pref.rasterSizeY)
			renderText(staticX,c-yTrans,staticZ,QString::number(c,'g',3),stdFont);
		if(pref.graphType == GRAPH3D)
		{
			staticZ=pref.zmin+zTrans;
			for(float c=pref.zmin-fmod(pref.zmin,pref.rasterSizeZ)+pref.rasterSizeZ; c<pref.zmax; c+=pref.rasterSizeZ)
				renderText(staticX,staticY,c-zTrans,QString::number(c,'g',3),stdFont);
		}
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	qglColor(QColor(0,0,0));
	for(int c=0; c<textList.GetLen(); c++)
		renderText(textList[c].x,textList[c].y,textList[c].text);
	
	for(int c=0; c<drawLists.GetLen(); c++)
		glCallList(drawLists[c]);
	
}









