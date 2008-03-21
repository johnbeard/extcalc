#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qfiledialog.h>
#include "global.h"
#include "calctable.h"


//functions:
//#config color...
//#config type...
//#config dynamicon/off
//#config logicon/off
//function


class ImportDialog :public QWidget
{
	QPushButton*saveButton,*cancelButton,*openDialogButton,*saveDialogButton;
	QLabel *mainLabel,*openPathLabel,*savePathLabel;
	QLineEdit *openPathLine,*savePathLine;
	bool dialog;
	bool importFile;
	bool function;
	Preferences pref;
	QString directory;
	
	
	Q_OBJECT
	public:
		ImportDialog(Preferences p,QWidget*parent,bool importF,bool function=false);
	
	protected:
		virtual void windowActivationChange(bool);

	public slots:

		void saveSlot();
		void openDialogSlot();
		void saveDialogSlot();
		
	signals:
		void updateScriptSignal(int);
		void prefChange(Preferences);
};

#endif


