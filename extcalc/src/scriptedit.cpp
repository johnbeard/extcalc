/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptedit.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "scriptedit.h"
//Added by qt3to4:
#include <QContextMenuEvent>
#include <QDragLeaveEvent>
#include <QKeyEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>


ScriptWidget::ScriptWidget(QWidget*parent,Preferences p,Variable*va,StandardButtons*cB,ExtButtons*eB) :TabWidget(parent,p,va,NULL,"scripteditor",true)
{
//		pref=p;
//		vars=va;
//		menuBottom=mB;
//		maximized=true;
	currentTextChanged=false;
	activeFileItem=NULL;
	clickedFileItem=NULL;

  calcButtons=cB;
  extButtons=eB;
	catalog=new Catalog(CATMATHSTD | CATMATHCOMPLEX | CATMATRIX | CATMATHLOGIC | CATSCRIPT,this);
	splitter=new QSplitter(Qt::Horizontal,this);
	fileBrowser=new Q3ListView(splitter);
	lineNumbers=new LineNumberView(splitter);
	editor=new Q3TextEdit(splitter);

	setMainWidget(splitter);


	fileBrowserMenu=new Q3PopupMenu(fileBrowser);
	modifiedIcon=new QPixmap(QString(INSTALLDIR)+"/data/modified.png");

  toolBar=new QToolBar(parent);


	fileBrowserMenu->insertItem(SCRIPTEDITH_STR4,FILEUPDATE);
	fileBrowserMenu->insertSeparator();
	fileBrowserMenu->insertItem(SCRIPTEDITH_STR5,FILENEWSCRIPT);
	fileBrowserMenu->insertItem(SCRIPTEDITH_STR6,FILENEWDIR);
	fileBrowserMenu->insertSeparator();
	fileBrowserMenu->insertItem(SCRIPTEDITH_STR7,FILESAVE);
	fileBrowserMenu->insertItem(SCRIPTEDITH_STR8,FILESAVEALL);
	fileBrowserMenu->insertSeparator();
	fileBrowserMenu->insertItem(SCRIPTEDITH_STR9,FILERENAME);
	fileBrowserMenu->insertItem(SCRIPTEDITH_STR10,FILEDELETE);

  newAction=new QAction(QIcon(":/filenew.png"),"",toolBar);
  importAction=new QAction(QIcon(":/fileimport.png"),"",toolBar);
  exportAction=new QAction(QIcon(":/fileexport.png"),"",toolBar);
  saveAction=new QAction(QIcon(":/filesaveas.png"),"",toolBar);
  saveallAction=new QAction(QIcon(":/save_all.png"),"",toolBar);
  undoAction=new QAction(QIcon(":/undo.png"),"",toolBar);
  redoAction=new QAction(QIcon(":/redo.png"),"",toolBar);
  cutAction=new QAction(QIcon(":/editcut.png"),"",toolBar);
  copyAction=new QAction(QIcon(":/editcopy.png"),"",toolBar);
  pasteAction=new QAction(QIcon(":/editpaste.png"),"",toolBar);
  catalogAction=new QAction(QIcon(":/catalog.png"),"",toolBar);
  catalogAction->setMenu(catalog);
  maximizeAction=new QAction(QIcon(":/view_top_bottom.png"),"",toolBar);
  maximizeAction->setCheckable(true);
  runAction=new QAction(QIcon(":/exec.png"),"",toolBar);

  toolBar->addAction(newAction);
  toolBar->addAction(importAction);
  toolBar->addAction(exportAction);
  toolBar->addSeparator();
  toolBar->addAction(saveAction);
  toolBar->addAction(saveallAction);
  toolBar->addSeparator();
  toolBar->addAction(undoAction);
  toolBar->addAction(redoAction);
  toolBar->addAction(cutAction);
  toolBar->addAction(copyAction);
  toolBar->addAction(pasteAction);
  toolBar->addSeparator();
  toolBar->addAction(catalogAction);
  toolBar->addAction(maximizeAction);
  toolBar->addSeparator();
  toolBar->addAction(runAction);

/*
	QToolTip::add(newButton,SCRIPTEDITH_STR12);
	QToolTip::add(saveButton,SCRIPTEDITH_STR13);
	QToolTip::add(saveallButton,SCRIPTEDITH_STR14);
	QToolTip::add(undoButton,SCRIPTEDITH_STR15);
	QToolTip::add(redoButton,SCRIPTEDITH_STR16);
	QToolTip::add(cutButton,SCRIPTEDITH_STR17);
	QToolTip::add(copyButton,SCRIPTEDITH_STR18);
	QToolTip::add(pasteButton,SCRIPTEDITH_STR19);
	QToolTip::add(importButton,SCRIPTEDITH_STR20);
	QToolTip::add(exportButton,SCRIPTEDITH_STR21);
	QToolTip::add(runButton,SCRIPTEDITH_STR22);
	QToolTip::add(minimizeButton,SCRIPTEDITH_STR23);
	QToolTip::add(catalogButton,SCRIPTEDITH_STR24);
*/


  stdFont=new QFont("monospace",10);
	stdFont->setFixedPitch(true);
	QFontMetrics fm(*stdFont);
	fontWidth=fm.maxWidth();
	fontHeight=fm.height();
	editor->setFont(*stdFont);
	editor->setTextFormat(Qt::PlainText);
	editor->setWordWrap(Q3TextEdit::NoWrap);

	lineNumbers->setFont(*stdFont);
	lineNumbers->setTextFormat(Qt::PlainText);
	lineNumbers->setVScrollBarMode(Q3ScrollView::AlwaysOff);
	lineNumbers->setHScrollBarMode(Q3ScrollView::AlwaysOff);
	lineNumbers->setWordWrap(Q3TextEdit::NoWrap);
	lineNumbers->setText(" 1");
	lineNumbers->setPaper(backgroundBrush());
	lineNumbers->setFixedWidth(fontWidth*3);
	lineNumbers->setReadOnly(true);



	editor->setWrapPolicy(Q3TextEdit::AtWordOrDocumentBoundary);
	splitter->setResizeMode(fileBrowser,QSplitter::KeepSize);

	fileBrowser->addColumn(SCRIPTEDITH_STR11);
	fileBrowser->setRootIsDecorated(true);

  maximizeSlot(true);


	QObject::connect(fileBrowser,SIGNAL(selectionChanged(Q3ListViewItem*)),this,SLOT(showFile(Q3ListViewItem*)));
	QObject::connect(fileBrowser,SIGNAL(contextMenuRequested(Q3ListViewItem*,const QPoint&,int)),this,SLOT(createFileBrowserMenu(Q3ListViewItem*,const QPoint&,int)));
	QObject::connect(editor,SIGNAL(contentsMoving (int,int)),this,SLOT(lineNumSlot(int,int)));
	QObject::connect(fileBrowserMenu,SIGNAL(activated(int)),this,SLOT(fileBrowserMenuSlot(int)));
	QObject::connect(editor,SIGNAL(textChanged()),this,SLOT(textChangedSlot()));
  QObject::connect(saveAction,SIGNAL(triggered()),this,SLOT(saveSlot()));
  QObject::connect(maximizeAction,SIGNAL(triggered(bool)),this,SLOT(viewSlot(bool)));
  QObject::connect(runAction,SIGNAL(triggered()),this,SLOT(runButtonSlot()));
  QObject::connect(saveallAction,SIGNAL(triggered()),this,SLOT(saveallSlot()));
  QObject::connect(newAction,SIGNAL(triggered()),this,SLOT(newSlot()));
  QObject::connect(importAction,SIGNAL(triggered()),this,SLOT(importSlot()));
  QObject::connect(exportAction,SIGNAL(triggered()),this,SLOT(exportSlot()));
  QObject::connect(copyAction,SIGNAL(triggered()),editor,SLOT(copy()));
  QObject::connect(pasteAction,SIGNAL(triggered()),editor,SLOT(paste()));
  QObject::connect(cutAction,SIGNAL(triggered()),editor,SLOT(cut()));
  QObject::connect(undoAction,SIGNAL(triggered()),editor,SLOT(undo()));
  QObject::connect(redoAction,SIGNAL(triggered()),editor,SLOT(redo()));
  QObject::connect(catalog,SIGNAL(menuSignal(QString)),this,SLOT(processText(QString)));
}


void ScriptWidget::setPref(Preferences p)
{
	pref=p;
//	calcButtons->setPref(pref);
//	extButtons->setPref(pref);
	if(pref.scriptPath.length()>0)
		updateFileList();
}

void ScriptWidget::getPref(Preferences p)
{
	pref=p;
	emit prefChange(pref);
}

void ScriptWidget::processText(QString text)
{
	if(text == "calculate")
	{
		editor->doKeyboardAction(Q3TextEdit::ActionReturn);
	}
	else if(text == "backkey")
	{
		editor->doKeyboardAction(Q3TextEdit::ActionBackspace);
	}
	else if(text == "clearall")
	{
		editor->clear();
	}
	else {
		editor->insert(text);
	}
}

void ScriptWidget::viewSlot(bool min)
{
  if(min)
		maximizeSlot(false);
  else maximizeSlot(true);
  updateUI();
}

void ScriptWidget::editSlot(int type)
{
	if(editor->hasFocus() || hasFocus())
	{
		switch(type)
		{
			case EDITUNDO:
				editor->undo();
				break;
			case EDITREDO:
				editor->redo();
				break;
			case EDITCUT:
				editor->cut();
				break;
			case EDITCOPY:
				editor->copy();
				break;
			case EDITPASTE:
				editor->paste();
				break;
		}
	}
}

void ScriptWidget::updateFileList()
{
//	perror("updateFileList");
	QString activePath="";
	if(activeFileItem!=NULL)
	{
		activePath=getFileName(activeFileItem);
	}
	fileBrowser->clear();
	DIR*scriptDir;
	struct dirent*dirItem;
	struct stat itemStat;
	QString startPath=pref.scriptPath+"/"+pref.scriptDirName;
	scriptDir=opendir(startPath);
	if(scriptDir==NULL)
		return;

	while((dirItem=readdir(scriptDir))!=NULL)
	{
		if(lstat(startPath+QString("/")+QString(dirItem->d_name),&itemStat)==0 && dirItem->d_name[0]!='.')
		{
			Q3ListViewItem* newItem = new Q3ListViewItem(fileBrowser,dirItem->d_name);
			fileBrowser->insertItem(newItem);
			if(S_ISDIR(itemStat.st_mode))
				readDir(startPath+QString("/")+QString(dirItem->d_name),newItem);
		}
	}
	closedir(scriptDir);
	struct stat testFileStat;
	QString origFileString;
	for(int c=0; c<activeFiles.GetLen(); c++)
	{
		if(lstat(activeFiles[c],&testFileStat)==0)
		{
			origFileString=activeFiles[c];
			int slash=origFileString.findRev("/.tmp");
			origFileString.remove(slash+1,4);
//			MessageBox("origFileString: "+origFileString);
			Q3ListViewItem*changedItem=getFileItem(origFileString);
			if(changedItem!=NULL)
			{
//				MessageBox("ChangedItem: "+changedItem->text(0));
				changedItem->setPixmap(0,*modifiedIcon);
			}
//			else MessageBox("not found");
		}
		else {
			activeFiles.DeleteItem(c);
			c--;
		}
	}
	
	if(activePath.length()>0)
	{
//		perror("updateFileList: searching activeFileItem");
		activeFileItem=getFileItem(activePath);
		if(activeFileItem!=NULL)
		{
		//	showFile(activeFileItem);
			if(activeFileItem->parent()!=NULL)
				activeFileItem->parent()->setOpen(true);
			if(currentTextChanged)
				activeFileItem->setPixmap(0,*modifiedIcon);
				
		}
	}
//	perror("updateFileList finished");
}


void ScriptWidget::readDir(QString rootDir,Q3ListViewItem*parent)
{
//	perror("readDir");
	DIR*scriptDir;
	struct dirent*dirItem;
	struct stat itemStat;
	scriptDir=opendir(rootDir);
	if(scriptDir==NULL)
		return;

	while((dirItem=readdir(scriptDir))!=NULL)
	{
		if(lstat(rootDir+QString("/")+QString(dirItem->d_name),&itemStat)==0 && dirItem->d_name[0]!='.')
		{
			if(!parent->isExpandable())
				parent->setExpandable(true);
			Q3ListViewItem* newItem = new Q3ListViewItem(parent,dirItem->d_name);
			parent->insertItem(newItem);
			if(S_ISDIR(itemStat.st_mode))
				readDir(rootDir+QString("/")+QString(dirItem->d_name),newItem);
		}
	}
	closedir(scriptDir);
}


void ScriptWidget::showFile(Q3ListViewItem*activeItem)
{
//	perror("showFile");
	QString completePath=activeItem->text(0);
	Q3ListViewItem *parentItem=activeItem;
	if(parentItem==NULL)
		return;
	while((parentItem=parentItem->parent())!=NULL)
	{
		completePath.insert(0,'/');
		completePath.insert(0,parentItem->text(0));
	}
	completePath.insert(0,'/');
	completePath.insert(0,pref.scriptDirName);
	completePath.insert(0,'/');
	completePath.insert(0,pref.scriptPath);
	struct stat fileStat;
	if(lstat(completePath,&fileStat)!=0)
		return;
	if(S_ISREG(fileStat.st_mode))
	{
		if(currentTextChanged && activeFileItem==NULL)
		{
			int ret=YesNoCancelBox(SCRIPTEDITC_STR4);
			if(ret==0)
			{
				saveSlot();
//				perror("still alive");
				return;
			}
			else if(ret==-1)
				return;
		}
		
		
		
		bool exists=false;
		char*fileContent;
		FILE*codeFile=NULL;
		QString tempFilePath="";
		if(activeFileItem!=NULL && currentTextChanged)
		{
			tempFilePath=pref.scriptPath+"/"+pref.scriptDirName+"/"+getFileName(activeFileItem);
			int slash=tempFilePath.findRev('/');
			tempFilePath.insert(slash+1,".tmp");
			if(saveFile(tempFilePath,editor->text()))
			{
				activeFiles.NewItem(tempFilePath);
			}
		}
		QString newTempPath=pref.scriptPath+"/"+pref.scriptDirName+"/"+getFileName(activeItem);
		int slash=newTempPath.findRev('/');
		newTempPath.insert(slash+1,".tmp");
		activeFileItem=NULL;
		

		
		for(int c=0; c<activeFiles.GetLen(); c++)
			if(QString::compare(activeFiles[c],newTempPath) == 0)
			{
				exists=true;
				break;
			}
		
		if(exists)
		{
			if(lstat(newTempPath,&fileStat)!=0)
			{
				lstat(completePath,&fileStat);
				codeFile=fopen(completePath,"r");
			}
			else codeFile=fopen(newTempPath,"r");
		}
		else codeFile=fopen(completePath,"r");
		
		
		if(codeFile==NULL)
			return;

		editor->clear();
		if(fileStat.st_size>0)
		{
			fileContent=new char[fileStat.st_size+1];
			fread(fileContent,fileStat.st_size,1,codeFile);
			fileContent[fileStat.st_size]=(char)0;
			editor->setText(QString(fileContent));
			delete[]fileContent;
		}
		fclose(codeFile);
		activeFileItem=activeItem;
		
		if(exists)
			currentTextChanged=true;
		else currentTextChanged=false;

		createNumbers();
	}
}

void ScriptWidget::createNumbers()
{
	int maxNum=editor->paragraphs()+1;
	if(maxNum<editor->height()/16)
		maxNum=editor->height()/16;
	int textLen=QString::number(maxNum).length();
	QString lineNumText,numText;
	for(int c=1; c<maxNum; c++)
	{
		numText=QString::number(c);
		while((signed)numText.length()<textLen)
			numText.insert(0," ");
		lineNumText+=(numText);
		lineNumText+="\n";
	}

	lineNumbers->setFixedWidth(fontWidth*(1+QString::number(maxNum).length()));
	numText=QString::number(editor->paragraphs()+1);
	while((signed)numText.length()<textLen)
		numText.insert(0," ");
	lineNumText+=(numText);
	lineNumbers->setText("");
	lineNumbers->insert(lineNumText);
	lineNumbers->setContentsPos(0,editor->contentsY());
}

void ScriptWidget::createFileBrowserMenu(Q3ListViewItem*item,const QPoint&pos,int col)
{
	
	if(item!=NULL && col!=-1)
	{
		fileBrowserMenu->setItemEnabled(FILEUPDATE,true);
		fileBrowserMenu->setItemEnabled(FILERENAME,true);
		fileBrowserMenu->setItemEnabled(FILEDELETE,true);
		fileBrowserMenu->setItemEnabled(FILESAVE,true);
		fileBrowserMenu->setItemEnabled(FILENEWSCRIPT,true);
		if(item->isExpandable())
		{
			fileBrowserMenu->setItemEnabled(FILENEWDIR,true);
			fileBrowserMenu->setItemEnabled(FILESAVE,false);
		}
		else {
			fileBrowserMenu->setItemEnabled(FILENEWDIR,false);
			fileBrowserMenu->setItemEnabled(FILESAVE,true);
		}
	}
	else {
		fileBrowserMenu->setItemEnabled(FILEUPDATE,true);
		fileBrowserMenu->setItemEnabled(FILERENAME,false);
		fileBrowserMenu->setItemEnabled(FILEDELETE,false);
		fileBrowserMenu->setItemEnabled(FILENEWSCRIPT,true);
		fileBrowserMenu->setItemEnabled(FILENEWDIR,true);
		fileBrowserMenu->setItemEnabled(FILESAVE,false);
		fileBrowserMenu->setItemEnabled(FILESAVEALL,true);
	}
	clickedFileItem=item;
	fileBrowserMenu->popup(pos);
}


void ScriptWidget::lineNumSlot(int,int y)
{
	if(editor->paragraphs() > lineNumbers->paragraphs())
		createNumbers();
	
	lineNumbers->setContentsPos(0,y);
}




void ScriptWidget::fileBrowserMenuSlot(int item)
{
//	perror("fileBrowserMenuSlot");
	switch(item)
	{
		case FILEUPDATE:
			updateFileList();
			break;
		case FILERENAME:
		{
			if(clickedFileItem==NULL)
				break;
			bool answer;
			QString oldPath=pref.scriptPath+"/"+pref.scriptDirName+"/"+getFileName(clickedFileItem);
			QString newPath=oldPath.left(oldPath.findRev("/")+1);
			
			QString newName=QInputDialog::getText(SCRIPTEDITC_STR5,SCRIPTEDITC_STR6,
					QLineEdit::Normal,clickedFileItem->text(0),&answer,this );
			
			if(answer)
			{
				if(newName[0]=='/')
					newName=newName.right(newName.length()-1);
				if(newName.find('/') >=0 || newName.find('.')>=0)
				{
					ErrorBox(SCRIPTEDITC_STR7);
					break;
				}
				newPath+=newName;
				if(rename(oldPath,newPath)!=0)
					ErrorBox(SCRIPTEDITC_STR8+clickedFileItem->text(0)+"\n\n"+getErrorMessage());
				int slash=oldPath.findRev('/');
				oldPath.insert(slash+1,".tmp");
				slash=newPath.findRev('/');
				newPath.insert(slash+1,".tmp");
				for(int c=0; c<activeFiles.GetLen(); c++)
				{
					if(QString::compare(activeFiles[c],oldPath)==0)
					{
						activeFiles[c]=newPath;
						break;
					}
				}
				if(clickedFileItem==activeFileItem)
					activeFileItem->setText(0,newName);
				updateFileList();
			}
			break;
		}
		case FILEDELETE:
		{
			if(clickedFileItem==NULL)
				break;
			QString path=getFileName(clickedFileItem);
			if(YesNoBox(SCRIPTEDITC_STR9+path)==0)
			{
				if(remove(pref.scriptPath+"/"+pref.scriptDirName+"/"+path)!=0)
					ErrorBox(SCRIPTEDITC_STR10+path+"\n\n"+getErrorMessage());
				updateFileList();
			}
			break;
		}
		case FILENEWSCRIPT:
		{
			if(activeFileItem==NULL && currentTextChanged)
			{
				int ret=YesNoCancelBox(SCRIPTEDITC_STR12);
				if(ret==0)
					saveSlot();
				else if(ret==-1)
					break;
			}
			QString filePath=Q3FileDialog::getSaveFileName(
					pref.scriptPath+"/"+pref.scriptDirName,
			"*",
			this,
			"Create Dialog",
			SCRIPTEDITC_STR13 );
			if(filePath.length()<=0)
				break;
			if(filePath.find(pref.scriptPath+"/"+pref.scriptDirName) !=0)
			{
				MessageBox(SCRIPTEDITC_STR14);
				break;
			}
			struct stat testStat;
			if(lstat(filePath,&testStat)==0)
			{
				if(YesNoBox(SCRIPTEDITC_STR15+filePath)==1)
					break;
			}
			FILE*editorFile=fopen(filePath,"w");
			if(editorFile==NULL)
			{
				ErrorBox(SCRIPTEDITC_STR16+activeFileItem->text(0)+"\n\n"+getErrorMessage());
				break;
			}

			fclose(editorFile);

			updateFileList();
			showFile(getFileItem(filePath));
			break;
		}
		case FILENEWDIR:
		{
			bool answer;
			QString path=pref.scriptPath+"/"+pref.scriptDirName;
			if(clickedFileItem!=NULL)
				path+="/"+getFileName(clickedFileItem);
			QString dirName=QInputDialog::getText(SCRIPTEDITC_STR17,SCRIPTEDITC_STR18,
					QLineEdit::Normal,QString::null,&answer,this );
			if(answer)
			{
				if(dirName[0]=='/')
					dirName=dirName.right(dirName.length()-1);
				if(dirName.find('/') >=0 || dirName.find('.')>=0)
				{
					ErrorBox(SCRIPTEDITC_STR19);
					break;
				}
				path+="/";
				path+=dirName;
				
				if(mkdir(path,0750)!=0)
					ErrorBox(SCRIPTEDITC_STR20);
			}
			updateFileList();
			break;
		}
		case FILESAVE:
		{
			if(clickedFileItem==NULL)
				break;
			if(clickedFileItem==activeFileItem)
			{
				saveSlot();
				break;
			}
			QString filePath=pref.scriptPath+"/"+pref.scriptDirName+"/"+getFileName(clickedFileItem);
			QString tempFilePath=filePath;
			int slash=tempFilePath.findRev('/');
			tempFilePath.insert(slash+1,".tmp");
	
			rename(tempFilePath,filePath);
	
			for(int c=0; c<activeFiles.GetLen(); c++)
				if(QString::compare(activeFiles[c],tempFilePath)==0)
					activeFiles.DeleteItem(c);
			clickedFileItem->setPixmap(0,NULL);
			break;
		}
		case FILESAVEALL:
			while(activeFiles.GetLen()>0)
			{
				QString filePath=activeFiles[0];
				int slash=filePath.findRev("/.tmp");
				filePath.remove(slash+1,4);
				rename(activeFiles[0],filePath);
				activeFiles.DeleteItem(0);
			}
			saveSlot();
			updateFileList();
			break;
	}
	clickedFileItem=NULL;
}

void ScriptWidget::textChangedSlot()
{
	if(!currentTextChanged && activeFileItem!=NULL)
		activeFileItem->setPixmap(0,*modifiedIcon);
	currentTextChanged=true;
	
	if(editor->paragraphs() > lineNumbers->paragraphs())
		createNumbers();
	else {
			lineNumbers->setContentsPos(0,editor->contentsY());
	}
}

QString ScriptWidget::getFileName(Q3ListViewItem*startItem)
{
//	perror("getFilename");
	QString completePath=startItem->text(0);
	Q3ListViewItem *parentItem=startItem;
	while((parentItem=parentItem->parent())!=NULL)
	{
		completePath.insert(0,'/');
		completePath.insert(0,parentItem->text(0));
	}
	
	return completePath;
}

Q3ListViewItem* ScriptWidget::getFileItem(QString path)
{
	//Search QListViewItem by path
	//Use this to set activeFileItem after updateFileList()
	//and to set activeFileItem for a new created File
	//and modifie updateFileList() not to remove the "modified"-Icons
	QString searchString;
	
	if(path.find(pref.scriptPath+"/"+pref.scriptDirName+"/")==0)
	{
		searchString=path;
		searchString=searchString.right(path.length()-pref.scriptPath.length()-pref.scriptDirName.length()-2);
	}
	else {
		if(path[0]=='/')
			searchString=path.right(path.length()-1);
		else searchString=path;
	}
	int pos1=0;
	int pos2=searchString.find('/');
	if(pos2==-1)
		pos2=searchString.length();
	QString searchPart=searchString.mid(pos1,pos2-pos1);
	Q3ListViewItem *treeItem=fileBrowser->findItem(searchPart,0);
	Q3ListViewItem *walkItem;
	
	while(true)
	{
		if(treeItem==NULL)
		{
			return NULL;
		}
		pos1=pos2+1;
		pos2=searchString.find('/',pos1);
		if(pos2==-1)
			pos2=searchString.length();
		if(pos1>=(signed)searchString.length()-1)
			return treeItem;
		searchPart=searchString.mid(pos1,pos2-pos1);

		
		walkItem=treeItem->firstChild();
		treeItem=NULL;
		if(walkItem==NULL)
			return NULL;
		else if(QString::compare(walkItem->text(0),searchPart)==0)
			treeItem=walkItem;
		else {
			while((walkItem=walkItem->nextSibling()) !=NULL)
			{
				if(QString::compare(walkItem->text(0),searchPart)==0)
				{
					treeItem=walkItem;
					break;
				}
			}
		}
		
	}
	//you can never reach this
	return NULL;
}

void ScriptWidget::updateUI()
{
  if(isVisible() && !isMaximized())
  {
    calcButtons->show();
    extButtons->show();
  }
  else if(isVisible() && isMaximized())
  {
    calcButtons->hide();
    extButtons->hide();
  }
}

void ScriptWidget::saveSlot()
{
	QString filePath;
	bool fileCreated=false;
	if(activeFileItem==NULL)
	{
		filePath=Q3FileDialog::getSaveFileName(
				pref.scriptPath+"/"+pref.scriptDirName,
				"*",
				this,
				"Save Dialog",
				SCRIPTEDITC_STR21 );
		if(filePath.length()<=0)
			return;
		if(filePath.find(pref.scriptPath+"/"+pref.scriptDirName) !=0)
		{
			MessageBox(SCRIPTEDITC_STR22);
			return;
		}
		fileCreated=true;
		
	}
	else filePath=pref.scriptPath+"/"+pref.scriptDirName+"/"+getFileName(activeFileItem);
	QString content=editor->text();
	
/*	FILE*editorFile=fopen(filePath,"w");
	
	if(editorFile==NULL)
	{
		return;
	}
	fwrite(content.ascii(),content.length(),1,editorFile);
	fclose(editorFile);
	*/
	
	if(!saveFile(filePath,content))
	{
		ErrorBox(SCRIPTEDITC_STR25+QString("\n\n")+filePath+"\n\n"+getErrorMessage());
		return;
	}
	
	if(fileCreated)
	{
		updateFileList();
		activeFileItem=getFileItem(filePath);
	}
	

	
	struct stat editorFileStat;
	if(lstat(filePath,&editorFileStat)== 0)
	{
		QString tempFilePath=pref.scriptPath+"/"+pref.scriptDirName+"/"+getFileName(activeFileItem);
		int slash=tempFilePath.findRev('/');
		tempFilePath.insert(slash+1,".tmp");
		
		remove(tempFilePath);
		
		for(int c=0; c<activeFiles.GetLen(); c++)
			if(QString::compare(activeFiles[c],tempFilePath)==0)
				activeFiles.DeleteItem(c);
		if(activeFileItem!=NULL)
			activeFileItem->setPixmap(0,NULL);
		currentTextChanged=false;
	}
	else MessageBox(SCRIPTEDITC_STR23+filePath+"\n\n"+getErrorMessage());
}


bool ScriptWidget::saveFile(QString path,QString content)
{

	int pos=0;
	QString sign(QChar((unsigned short)ROOTSTRING));
	while((pos=content.find(sign))>=0)
	{
		if(pos==0 || 
				!(content[pos-1]>='0' && 
				 content[pos-1]<='9' || 
				 content[pos-1]=='\xb2' || 
				 content[pos-1]=='\xb3') )
		{
			content.remove(pos,1);
			content.insert(pos,"sqrt");
		}
		else if(content[pos-1]=='2' || content[pos-1]=='\xb2')
		{
			content.remove(pos-1,2);
			content.insert(pos-1,"sqrt");
		}
		else if(content[pos-1]=='3' || content[pos-1]=='\xb3')
		{
			content.remove(pos-1,2);
			content.insert(pos-1,"curt");
		}
		else {
			content.remove(pos,1);
			content.insert(pos,"root");
		}
		
	}
	sign=(QChar((unsigned short)PISTRING));
	content.replace(sign,"pi");
	sign=(QChar((unsigned short)EULERSTRING));
	content.replace(sign,"eu");
	sign=(QChar((unsigned short)INTEGRALSTRING));
	content.replace(sign,"integ");
	sign=(QChar((unsigned short)DELTASTRING));
	content.replace(sign,"d/dx");
	sign=(QChar((unsigned short)MEGASTRING));
	content.replace(sign,"000000");
	sign=(QChar((unsigned short)GIGASTRING));
	content.replace(sign,"000000000");
	sign=(QChar((unsigned short)TERASTRING));
	content.replace(sign,"000000000000");

	FILE*editorFile=fopen(path,"w");
	
	if(editorFile==NULL)
	{
		return false;
	}
	fwrite(content.ascii(),content.length(),1,editorFile);

	fclose(editorFile);
	
	return true;
}


void ScriptWidget::runButtonSlot()
{
	QString txt=editor->text();
	emit runScript(&txt);
}



bool ScriptWidget::quitProgram()
{
	if(activeFiles.GetLen()>0 || currentTextChanged)
	{
		int ret=YesNoCancelBox(SCRIPTEDITC_STR24);
		if(ret==1)
		{
			while(activeFiles.GetLen()>0)
			{
				remove(activeFiles[0]);
				activeFiles.DeleteItem(0);
			}
			return true;
		}
		else if(ret==-1)
			return false;
	}
	else return true;
	while(activeFiles.GetLen()>0)
	{
		QString filePath=activeFiles[0];
		int slash=filePath.findRev("/.tmp");
		filePath.remove(slash+1,4);
		rename(activeFiles[0],filePath);
		activeFiles.DeleteItem(0);
	}
	saveSlot();
	return true;
}

void ScriptWidget::saveallSlot()
{
	fileBrowserMenuSlot(FILESAVEALL);
}

void ScriptWidget::newSlot()
{
	fileBrowserMenuSlot(FILENEWSCRIPT);
}

void ScriptWidget::importSlot()
{
	emit controlScriptMenu(IMPORTSCRIPT);
}

void ScriptWidget::dockWindowSlot()
{
//	dockArea->moveDockWindow(editorToolBar);
  updateUI();
  repaint();
}

void ScriptWidget::exportSlot()
{
	emit controlScriptMenu(EXPORTSCRIPT);
}
	
	

void LineNumberView::wheelEvent(QWheelEvent*){}
void LineNumberView::contentsMousePressEvent(QMouseEvent*){}
void LineNumberView::contentsMouseMoveEvent(QMouseEvent*){}
void LineNumberView::contentsMouseDoubleClickEvent(QMouseEvent*){}
void LineNumberView::keyPressEvent(QKeyEvent*){}
void LineNumberView::contentsContextMenuEvent (QContextMenuEvent*){}
void LineNumberView::contentsDragEnterEvent(QDragEnterEvent*){setContentsPos(0,contentsY());}
void LineNumberView::contentsDragMoveEvent(QDragMoveEvent*e){setContentsPos(0,contentsY());e->accept(geometry());}
void LineNumberView::contentsDragLeaveEvent(QDragLeaveEvent*){setContentsPos(0,contentsY());}
void LineNumberView::contentsDropEvent(QDropEvent*){}

