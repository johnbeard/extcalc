/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         screenshotdialog.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

A dialog to export screenshots from the graphics window.

////////////////////////////////////////////////////////////////////////////////////////////*/


#ifndef SCREENSHOTDIALOG_H
#define SCREENSHOTDIALOG_H


#include <QColor>
#include "global.h"
#include "toolwidget.h"
#include "ui_screenshotdialog.h"



/**
 * @class ScreenshotDialog
 * @brief Dialog for painting and exporting screenshots of drawn graphs
 *
 * The class provides controls for painting and screenshot export and
 * sends the draw commands via signal-slot interface to the GraphOutput
 * object.
 */
class ScreenshotDialog :public ToolWidget
{
  Q_OBJECT

  /// Qt Designer user interface data
  Ui::ScreenshotUi screenshotUi;
  /// The current painting color
  QColor paintColor;
  /// This icon shows the current painting color on the color button
  QPixmap*colorIcon;
  /// This variable stores the current painting tool
  int drawState;

  public:

  ScreenshotDialog(QWidget*parent);

  void setPref(Preferences newPref);


public slots:
  void screenshotSlot(QPixmap*);
  void openButtonSlot();
  void colorButtonSlot();
  void penValueSlot(int);
  void forwardButtonSlot();
  void backButtonSlot();
  void clearButtonSlot();
  void freeButtonSlot();
  void lineButtonSlot();
  void rectButtonSlot();
  void circleButtonSlot();
  void rubberButtonSlot();
  void textButtonSlot();
  void saveButtonSlot();

signals:
  void getScreenshotSignal(int,int);
  void drawSignal(int,QColor,int);
  void redrawGraphs();

};


#endif // SCREENSHOTDIALOG_H
