/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptdisplay.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This class provides a window to render text and 2D-graphics output
of extcalc scripts.

////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef SCRIPTDISPLAY_H
#define SCRIPTDISPLAY_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QFont>


/**
 * @class ScriptDisplay
 * @brief This class provides a display widget for rendering 2D-script graphics and script text output
 *
 * The class provides a terminal for text output with variable size. The number of lines is set by the parent class,
 * while the line width is always adjusted to the window width.
 * ScriptDisplay may also be used for 2D-graphics output. Therefore, the parent may request the pointer to the graphics
 * output buffer where it may perform any drawing operation. In this case, the textMode of the ScriptDisplay class must
 * be switch of so that it does not overwrite the display buffer.
 */

class ScriptDisplay :public QWidget
{
  Q_OBJECT

  /// This image is used as a buffer for the displayed screen content. Other classes may paint into it.
  QPixmap*imageBuffer;
  /// Text buffer for text rendering
  QStringList textBuffer;
  /// Number of text columns
  int columns;
  /// Number of text rows
  int rows;
  /// If true, the text of textBuffer is drawn into into the buffer when a PaintEvent occurs
  bool textMode;
  /// Row number of the start point of text selection
  int selectStartRow;
  /// Row number of the end point of text selection
  int selectEndRow;
  /// Column number of the start point of text selection
  int selectStartColumn;
  /// Column number of the end point of text selection
  int selectEndColumn;
  /// Font for text rendering
  QFont*drawFont;
  /// Width of text character
  int charWidth;
  /// Line height for rendered text
  int charHeight;
  /// Text cursor column
  int cursorCol;
  /// Text cursor row
  int cursorRow;

public:
  ScriptDisplay(QWidget*parent);
  ~ScriptDisplay();

  QPixmap*getBufferPointer();
  void setHeight(int);
  int getHeight();
  int getWidth();

  void setRows(int);
  int getRows();
  int getColumns();
  void setSelection(int,int,int,int);
  QString getSelectedText();
  void insertText(QString,bool update=true);
  void setChar(int row,int col,char c);
  void setCursor(int,int);
  void setTextMode(bool mode);

  void backKey();
  void deleteKey();
  void clearText();

protected:

  virtual void paintEvent(QPaintEvent*);
  virtual void resizeEvent(QResizeEvent*);
  virtual void mousePressEvent(QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*);
  virtual void mouseMoveEvent(QMouseEvent*);

 signals:
  /// This signal hands information about the current cursor position to the view window
    void pointVisibleSignal(int,int);

};


#endif // SCRIPTDISPLAY_H
