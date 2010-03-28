#ifndef SCREENSHOTDIALOG_H
#define SCREENSHOTDIALOG_H


#include <QDockWidget>
#include <QColor>
#include "ui_screenshotdialog.h"



/**
 * @class ScreenshotDialog
 * @brief Dialog for painting and exporting screenshots of drawn graphs
 *
 * The class provides controls for painting and screenshot export and
 * sends the draw commands via signal-slot interface to the GraphOutput
 * object.
 *
 *
 */
class ScreenshotDialog :public QDockWidget
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
