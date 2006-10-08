#ifndef SCRIPTEDITH
#define SCRIPTEDITH

#include <qwidget.h>
#include <qtextedit.h>
#include <qlistview.h>
#include <qsplitter.h>
#include <qfont.h>
#include <qpopupmenu.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qlabel.h>
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
	QPopupMenu*fileBrowserMenu;
	QPixmap*modifiedIcon;
	bool maximized;
	List <QString> activeFiles;
	bool currentTextChanged;
	QListViewItem*activeFileItem;
	QListViewItem*clickedFileItem;
	
	Q_OBJECT
public:
	
	ScriptWidget(QWidget*parent,Preferences p,Variable*va) :QWidget(parent)
	{
		pref=p;
		vars=va;
		maximized=false;
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
		fileBrowserMenu=new QPopupMenu(fileBrowser);
		modifiedIcon=new QPixmap(QString(INSTALLDIR)+"/data/modified.png");
		
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
		lineNumbers->setText(" 1\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21");
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
	
	
protected:
virtual void resizeEvent(QResizeEvent*);
	
	
signals:
	void prefChange(Preferences);
	void runScript(QString*);
};


#endif


