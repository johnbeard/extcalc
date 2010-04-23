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

#include <QWidget>
#include <q3textedit.h>
#include <q3listview.h>
#include <qsplitter.h>
#include <qfont.h>
#include <q3popupmenu.h>
#include <q3toolbar.h>
#include <q3dockarea.h>
#include <q3filedialog.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qtooltip.h>
#include <qicon.h>
#include <qaction.h>
//Added by qt3to4:
#include <QContextMenuEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDragEnterEvent>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <list.h>
#include "buttons.h"
#include "catalog.h"
#include "tabwidget.h"


class LineNumberView :public Q3TextEdit
{
	
public:
	LineNumberView(QWidget*parent) :Q3TextEdit(parent)
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

class ScriptWidget :public TabWidget
{
//	Preferences pref;
//	Variable * vars;
  StandardButtons* calcButtons;
  ExtButtons* extButtons;
	Catalog *catalog;
	Q3TextEdit*editor;
	Q3ListView*fileBrowser;
	LineNumberView*lineNumbers;
//	QLabel*lineNumbers;
	QSplitter*splitter;
//	QPushButton*maximizeButton,*runButton,*saveButton;
	QFont *stdFont;
	int fontWidth,fontHeight;
//	int menuBottom;
	Q3PopupMenu*fileBrowserMenu;
	QPixmap*modifiedIcon;
//	bool maximized;
	List <QString> activeFiles;
	bool currentTextChanged;
	Q3ListViewItem*activeFileItem;
	Q3ListViewItem*clickedFileItem;
  QAction*newAction,*saveAction,*saveallAction,*undoAction,*redoAction,*cutAction,*copyAction,*pasteAction,*importAction,*exportAction,*runAction,*maximizeAction,*catalogAction;

	
	
	Q_OBJECT
public:

  ScriptWidget(QWidget*parent,Preferences p,Variable*va,StandardButtons*cB,ExtButtons*eB);


	void setPref(Preferences);
	
	void updateFileList();
	void readDir(QString,Q3ListViewItem*);
	QString getFileName(Q3ListViewItem*);
	Q3ListViewItem* getFileItem(QString);
	bool quitProgram();
	bool saveFile(QString path,QString content);
	void createNumbers();

private:
  void updateUI();

	
public slots:
	void getPref(Preferences);
  void processText(QString);
  void viewSlot(bool);
	void editSlot(int);
	void showFile(Q3ListViewItem*);
	void createFileBrowserMenu(Q3ListViewItem*,const QPoint&,int);
	void fileBrowserMenuSlot(int item);
	void textChangedSlot();
	void saveSlot();
	void runButtonSlot();
	void lineNumSlot(int,int);
	void saveallSlot();
	void newSlot();
	void importSlot();
	void exportSlot();
	void dockWindowSlot();

protected:
//virtual void resizeEvent(QResizeEvent*);
	
signals:
	void prefChange(Preferences);
	void runScript(QString*);
	void controlScriptMenu(int);

};


#endif


