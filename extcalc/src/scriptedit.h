/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptedit.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

The class for the script editor tab window. It does the script file management.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef SCRIPTEDITH
#define SCRIPTEDITH

#include <qwidget.h>
#include <qtextedit.h>
#include <qlistview.h>
#include <qsplitter.h>
#include <qfont.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qdockarea.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qiconset.h>
#include <qaction.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <list.h>
#include "buttons.h"


class LineNumberView :public QTextEdit
{
	
public:
	LineNumberView(QWidget*parent) :QTextEdit(parent)
	{
	}
	
protected:
	virtual void wheelEvent(QWheelEvent*);
	virtual void contentsMousePressEvent(QMouseEvent*);
	virtual void contentsMouseMoveEvent(QMouseEvent*);
	virtual void contentsMouseDoubleClickEvent(QMouseEvent*);
	virtual void keyPressEvent(QKeyEvent*);
	virtual void contentsContextMenuEvent(QContextMenuEvent*);
	virtual void contentsDragEnterEvent(QDragEnterEvent*);
	virtual void contentsDragMoveEvent(QDragMoveEvent*);
	virtual void contentsDragLeaveEvent(QDragLeaveEvent*);
	virtual void contentsDropEvent(QDropEvent*);
};

class ScriptWidget :public QWidget
{
	Preferences pref;
	Variable * vars;
	StandardButtons* standardButtons;
	ExtButtons* extButtons;
	QTextEdit*editor;
	QListView*fileBrowser;
	LineNumberView*lineNumbers;
//	QLabel*lineNumbers;
	QSplitter*splitter;
	QPushButton*maximizeButton,*runButton,*saveButton;
	QFont *stdFont;
	int fontWidth,fontHeight;
	int menuBottom;
	QPopupMenu*fileBrowserMenu;
	QPixmap*modifiedIcon;
	bool maximized;
	List <QString> activeFiles;
	bool currentTextChanged;
	QListViewItem*activeFileItem;
	QListViewItem*clickedFileItem;
	QToolBar*editorToolBar;
	QDockArea*dockArea;
	QPixmap*newIcon,*saveIcon,*saveallIcon,*undoIcon,*redoIcon,*cutIcon,*copyIcon,*pasteIcon,*importIcon,*exportIcon,*runIcon,*minimizeIcon;
	QAction*newAction,*saveAction,*saveallAction,*undoAction,*redoAction,*cutAction,*copyAction,*pasteAction,*importAction,*exportAction,*runAction,*minimizeAction;

	Q_OBJECT
public:

	ScriptWidget(QWidget*parent,Preferences p,Variable*va,int mB) :QWidget(parent)
	{
		pref=p;
		vars=va;
		menuBottom=mB;
		maximized=true;
		currentTextChanged=false;
		activeFileItem=NULL;
		clickedFileItem=NULL;

		standardButtons=new StandardButtons(this);void scriptSlot(QString*code);
		extButtons=new ExtButtons(this);
		splitter=new QSplitter(Qt::Horizontal,this);
		fileBrowser=new QListView(splitter);
		lineNumbers=new LineNumberView(splitter);
//		lineNumbers=new QLabel("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15",splitter);
		editor=new QTextEdit(splitter);
		maximizeButton=new QPushButton(SCRIPTEDITH_STR1,this);
		runButton=new QPushButton(SCRIPTEDITH_STR2,this);
		saveButton=new QPushButton(SCRIPTEDITH_STR3,this);
		
		maximizeButton->hide();
		runButton->hide();
		saveButton->hide();

		fileBrowserMenu=new QPopupMenu(fileBrowser);
		modifiedIcon=new QPixmap(QString(INSTALLDIR)+"/data/modified.png");
		dockArea=new QDockArea(Qt::Horizontal,QDockArea::Normal,this);
		editorToolBar=new QToolBar();
		
	
	
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

		newIcon=new QPixmap(INSTALLDIR+QString("/data/filenew.png"));
		saveIcon=new QPixmap(INSTALLDIR+QString("/data/fileexport.png"));
		saveallIcon=new QPixmap(INSTALLDIR+QString("/data/save_all.png"));
		undoIcon=new QPixmap(INSTALLDIR+QString("/data/undo.png"));
		redoIcon=new QPixmap(INSTALLDIR+QString("/data/redo.png"));
		cutIcon=new QPixmap(INSTALLDIR+QString("/data/editcut.png"));
		copyIcon=new QPixmap(INSTALLDIR+QString("/data/editcopy.png"));
		pasteIcon=new QPixmap(INSTALLDIR+QString("/data/editpaste.png"));
		importIcon=new QPixmap(INSTALLDIR+QString("/data/fileimport.png"));
		exportIcon=new QPixmap(INSTALLDIR+QString("/data/filesaveas.png"));
		runIcon=new QPixmap(INSTALLDIR+QString("/data/exec.png"));
		minimizeIcon=new QPixmap(INSTALLDIR+QString("/data/view_top_bottom.png"));
		

		newAction=new QAction(editorToolBar);
		saveAction=new QAction(editorToolBar);
		saveallAction=new QAction(editorToolBar);
		undoAction=new QAction(editorToolBar);
		redoAction=new QAction(editorToolBar);
		cutAction=new QAction(editorToolBar);
		copyAction=new QAction(editorToolBar);
		pasteAction=new QAction(editorToolBar);
		importAction=new QAction(editorToolBar);
		exportAction=new QAction(editorToolBar);
		runAction=new QAction(editorToolBar);
		minimizeAction=new QAction(editorToolBar);
		
		newAction->setIconSet(*newIcon);
		saveAction->setIconSet(*saveIcon);
		saveallAction->setIconSet(*saveallIcon);
		undoAction->setIconSet(*undoIcon);
		redoAction->setIconSet(*redoIcon);
		cutAction->setIconSet(*cutIcon);
		copyAction->setIconSet(*copyIcon);
		pasteAction->setIconSet(*pasteIcon);
		importAction->setIconSet(*importIcon);
		exportAction->setIconSet(*exportIcon);
		runAction->setIconSet(*runIcon);
		minimizeAction->setIconSet(*minimizeIcon);
		
		newAction->setToolTip(SCRIPTEDITH_STR12);
		saveAction->setToolTip(SCRIPTEDITH_STR13);
		saveallAction->setToolTip(SCRIPTEDITH_STR14);
		undoAction->setToolTip(SCRIPTEDITH_STR15);
		redoAction->setToolTip(SCRIPTEDITH_STR16);
		cutAction->setToolTip(SCRIPTEDITH_STR17);
		copyAction->setToolTip(SCRIPTEDITH_STR18);
		pasteAction->setToolTip(SCRIPTEDITH_STR19);
		importAction->setToolTip(SCRIPTEDITH_STR20);
		exportAction->setToolTip(SCRIPTEDITH_STR21);
		runAction->setToolTip(SCRIPTEDITH_STR22);
		minimizeAction->setToolTip(SCRIPTEDITH_STR23);
		
		newAction->addTo(editorToolBar);
		importAction->addTo(editorToolBar);
		exportAction->addTo(editorToolBar);
		editorToolBar->addSeparator();
		saveAction->addTo(editorToolBar);
		saveallAction->addTo(editorToolBar);
		editorToolBar->addSeparator();
		undoAction->addTo(editorToolBar);
		redoAction->addTo(editorToolBar);
		cutAction->addTo(editorToolBar);
		copyAction->addTo(editorToolBar);
		pasteAction->addTo(editorToolBar);
		editorToolBar->addSeparator();
		minimizeAction->addTo(editorToolBar);
		editorToolBar->addSeparator();
		runAction->addTo(editorToolBar);
		dockArea->moveDockWindow(editorToolBar);
		
		
		stdFont=new QFont("Courier");
		stdFont->setPixelSize(16);
		stdFont->setFixedPitch(true);
		QFontMetrics fm(*stdFont);
		fontWidth=fm.maxWidth();
		fontHeight=fm.height();
		editor->setFont(*stdFont);
		editor->setTextFormat(Qt::PlainText);
		editor->setWordWrap(QTextEdit::NoWrap);

		lineNumbers->setFont(*stdFont);
		lineNumbers->setTextFormat(Qt::PlainText);
		lineNumbers->setVScrollBarMode(QScrollView::AlwaysOff);
		lineNumbers->setHScrollBarMode(QScrollView::AlwaysOff);
		lineNumbers->setWordWrap(QTextEdit::NoWrap);
		lineNumbers->setText(" 1");
		lineNumbers->setPaper(backgroundBrush());
		lineNumbers->setFixedWidth(fontWidth*3);
		lineNumbers->setReadOnly(true);

		

		editor->setWrapPolicy(QTextEdit::AtWordOrDocumentBoundary);
		splitter->setResizeMode(fileBrowser,QSplitter::KeepSize);

		fileBrowser->addColumn(SCRIPTEDITH_STR11);
		fileBrowser->setRootIsDecorated(true);
		

		QObject::connect(standardButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(extButtons,SIGNAL(prefChange(Preferences)),this,SLOT(getPref(Preferences)));
		QObject::connect(standardButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(extButtons,SIGNAL(emitText(QString)),this,SLOT(buttonInputSlot(QString)));
		QObject::connect(maximizeButton,SIGNAL(released()),this,SLOT(maximizeButtonSlot()));
		QObject::connect(runButton,SIGNAL(released()),this,SLOT(runButtonSlot()));		
		QObject::connect(fileBrowser,SIGNAL(selectionChanged(QListViewItem*)),this,SLOT(showFile(QListViewItem*)));
		QObject::connect(fileBrowser,SIGNAL(contextMenuRequested(QListViewItem*,const QPoint&,int)),this,SLOT(createFileBrowserMenu(QListViewItem*,const QPoint&,int)));
		QObject::connect(editor,SIGNAL(contentsMoving (int,int)),this,SLOT(lineNumSlot(int,int)));
		QObject::connect(fileBrowserMenu,SIGNAL(activated(int)),this,SLOT(fileBrowserMenuSlot(int)));
		QObject::connect(editor,SIGNAL(textChanged()),this,SLOT(textChangedSlot()));
		QObject::connect(saveButton,SIGNAL(released()),this,SLOT(saveSlot()));
		QObject::connect(saveAction,SIGNAL(activated()),this,SLOT(saveSlot()));
		QObject::connect(minimizeAction,SIGNAL(activated()),this,SLOT(maximizeButtonSlot()));
		QObject::connect(runAction,SIGNAL(activated()),this,SLOT(runButtonSlot()));
		QObject::connect(saveallAction,SIGNAL(activated()),this,SLOT(saveallSlot()));
		QObject::connect(newAction,SIGNAL(activated()),this,SLOT(newSlot()));
		QObject::connect(importAction,SIGNAL(activated()),this,SLOT(importSlot()));
		QObject::connect(exportAction,SIGNAL(activated()),this,SLOT(exportSlot()));
		QObject::connect(copyAction,SIGNAL(activated()),editor,SLOT(copy()));
		QObject::connect(pasteAction,SIGNAL(activated()),editor,SLOT(paste()));
		QObject::connect(cutAction,SIGNAL(activated()),editor,SLOT(cut()));
		QObject::connect(undoAction,SIGNAL(activated()),editor,SLOT(undo()));
		QObject::connect(redoAction,SIGNAL(activated()),editor,SLOT(redo()));
	}
	
	
	void setPref(Preferences);
	
	void updateFileList();
	void readDir(QString,QListViewItem*);
	QString getFileName(QListViewItem*);
	QListViewItem* getFileItem(QString);
	bool quitProgram();
	bool saveFile(QString path,QString content);
	void createNumbers();
	
public slots:
	void getPref(Preferences);
	void buttonInputSlot(QString);
	void maximizeButtonSlot();
	void editSlot(int);
	void showFile(QListViewItem*);
	void createFileBrowserMenu(QListViewItem*,const QPoint&,int);
	void fileBrowserMenuSlot(int item);
	void textChangedSlot();
	void saveSlot();
	void runButtonSlot();
	void lineNumSlot(int,int);
	void saveallSlot();
	void newSlot();
	void importSlot();
	void exportSlot();

	
	
protected:
virtual void resizeEvent(QResizeEvent*);
	
signals:
	void prefChange(Preferences);
	void runScript(QString*);
	void controlScriptMenu(int);
};


#endif


