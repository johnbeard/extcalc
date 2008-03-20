#ifndef GRAPHSETDIALOG_H
#define GRAPHSETDIALOG_H
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qdir.h>
#include <qlistbox.h>
#include <qinputdialog.h>
#include "global.h"


//functions:
//
//remove
//rename
//save current as
//create new


class GraphSetDialog :public QWidget
{
	QPushButton*okButton,*cancelButton,*removeButton,*renameButton;
	QListBox *table;
	QLabel*mainLabel;
	Preferences pref;
	QDir *graphsDir;
	bool dialog;
	
	Q_OBJECT
	public:
		GraphSetDialog(Preferences p,QWidget*parent);
	
	protected:
		virtual void windowActivationChange(bool);
		

	public slots:

		void okSlot();
		void removeSlot();
		void renameSlot();

};

#endif


