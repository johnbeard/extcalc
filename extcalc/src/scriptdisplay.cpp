/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         scriptdisplay.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/

#include "scriptdisplay.h"
#include <QPainter>
#include <QResizeEvent>

/** The constructor of ScriptDisplay class initializes the buffer.
  * @param parent is a pointer to the parent widget.
  *
  */
ScriptDisplay::ScriptDisplay(QWidget*parent) :QWidget(parent)
{
  imageBuffer=new QPixmap(600,400);
  imageBuffer->fill(QColor(0,0,255));
  setBaseSize(100,100);
  setSizeIncrement(1,1);
  selectStartRow=selectStartColumn=selectEndRow=selectEndColumn=0;
  textMode=true;

  drawFont=new QFont("monospace",10);
  drawFont->setFixedPitch(true);
  drawFont->setItalic(false);
  drawFont->setBold(false);
  columns=rows=0;

  QFontMetrics fontSize(*drawFont);
  charWidth=fontSize.size(0,QString("m")).width();
  charHeight=fontSize.size(0,QString("m")).height();
}

/// Destructor to free the buffer memory
ScriptDisplay::~ScriptDisplay()
{
  delete imageBuffer;

}

/// Event handler for resize events. Resizes the buffer.
void ScriptDisplay::resizeEvent(QResizeEvent*e)
{
  int c,cols;
  QSize s=e->size();
  (*imageBuffer)=imageBuffer->scaledToWidth(s.width());
  imageBuffer->fill();



  cols=imageBuffer->width()/charWidth;

  for(c=0; c<textBuffer.size(); c++)
  {
    textBuffer[c]=textBuffer[c].leftJustified(cols,' ',true);
  }

  if(cursorCol>cols)
    cursorCol=cols;

  columns=cols;
}

/// Event handler for paint events. Prints the current buffer-content to the screen.
void ScriptDisplay::paintEvent(QPaintEvent*)
{
  QPainter p;
  p.begin(this);
  p.setBackground(QColor(255,255,255));
  p.setBackgroundMode(Qt::OpaqueMode);
  p.setBrush(QColor(255,255,255));
  p.setPen(QColor(0,0,0));
  p.setFont(*drawFont);
  int tmpSelStartRow,tmpSelEndRow,tmpSelStartColumn,tmpSelEndColumn;

  if(textMode)
  {
    for(int c=0; c<textBuffer.size(); c++)
    {
      p.drawText(0,charHeight*(c+1),textBuffer[c]);
    }

    if(selectStartRow!=selectEndRow  || selectStartColumn!=selectEndColumn)
    {
      if(selectStartRow>selectEndRow || (selectStartRow==selectEndRow && selectStartColumn>selectEndColumn))
      {
        tmpSelStartRow=selectEndRow;
        tmpSelStartColumn=selectEndColumn;
        tmpSelEndRow=selectStartRow;
        tmpSelEndColumn=selectStartColumn;
      }
      else {
        tmpSelStartRow=selectStartRow;
        tmpSelStartColumn=selectStartColumn;
        tmpSelEndRow=selectEndRow;
        tmpSelEndColumn=selectEndColumn;
      }

      p.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
      p.setPen(QColor(255,255,255));
      p.setBrush(QColor(255,255,255));
      if(tmpSelStartRow!=tmpSelEndRow)
      {
        p.drawRect(tmpSelStartColumn*charWidth,(tmpSelStartRow)*charHeight,imageBuffer->width()-tmpSelStartColumn*charWidth,charHeight);
        if(tmpSelEndRow-tmpSelStartRow>1)
          p.drawRect(0,(tmpSelStartRow+1)*charHeight,imageBuffer->width(),(tmpSelEndRow-tmpSelStartRow-1)*charHeight);
        p.drawRect(0,(tmpSelEndRow)*charHeight,charWidth*tmpSelEndColumn,charHeight);
      }
      else p.drawRect(tmpSelStartColumn*charWidth,(tmpSelStartRow)*charHeight,(tmpSelEndColumn-tmpSelStartColumn)*charWidth,charHeight);
      p.setCompositionMode(QPainter::CompositionMode_SourceOver);
      p.setPen(QColor(0,0,0));
      p.setBrush(QColor(255,255,255));

    }

    p.drawLine(charWidth*cursorCol,charHeight*(cursorRow),charWidth*cursorCol,charHeight*(cursorRow+1));
  }
  else p.drawPixmap(0,0,*imageBuffer);
}


/// Event handler for the MousePress event. Starts text selection, if necessary.
void ScriptDisplay::mousePressEvent(QMouseEvent*e)
{
  if(e->button()==Qt::RightButton)
  {
    if(textMode)
    {
      QPoint menuPos=e->pos();
      //menuPos=mapToGlobal(menuPos);
      //contextMenu->popup(menuPos,EDITCOPY);
    }
    return;
  }

  if(!textMode)
    return;
  int mouseX,mouseY;
  mouseX=e->x();
  mouseY=e->y();


  selectEndRow=selectStartRow=(mouseY)/charHeight;
  selectEndColumn=selectStartColumn=(mouseX)/charWidth;

  if(mouseX>=0 && mouseX <=imageBuffer->width() && mouseY>=0 && mouseY<=imageBuffer->height())
  {
    cursorCol=(mouseX+charWidth/2)/charWidth;
    cursorRow=(mouseY)/charHeight;
    if(cursorCol>=columns)
      cursorCol=columns-1;
    if(cursorRow>=rows)
      cursorRow=rows-1;
  }
  update();
}

/// Event handler for the MouseRelease event. Finishes a text selection.
void ScriptDisplay::mouseReleaseEvent(QMouseEvent*me)
{


  int mouseX=me->x();
  int mouseY=me->y();

  selectEndRow=(mouseY)/charHeight;
  selectEndColumn=(mouseX)/charWidth;
  update();
}

/// Event handler for the MouseMove event. Changes the current selection, if the mouse button is pressed.
void ScriptDisplay::mouseMoveEvent(QMouseEvent*me)
{
  int oldEndColumn=selectEndColumn,oldEndRow=selectEndRow;


  int mouseX=me->x();
  int mouseY=me->y();


  selectEndRow=(mouseY)/charHeight;
  selectEndColumn=(mouseX)/charWidth;
  if(selectEndRow<0)
    selectEndRow=0;
  if(selectEndColumn<0)
    selectEndColumn=0;


  if(oldEndRow!=selectEndRow || oldEndColumn!=selectEndColumn)
    update();
}


/// This method returns a pointer to the display buffer, so that other classes are able to print into the buffer.
QPixmap* ScriptDisplay::getBufferPointer()
{
  return imageBuffer;
}

void ScriptDisplay::setTextMode(bool mode)
{
  textMode=mode;
  if(!textMode)
    emit pointVisibleSignal(0,0);
}

/// Sets the height of the window and display buffer to @param h
void ScriptDisplay::setHeight(int h)
{
  (*imageBuffer)=imageBuffer->scaledToHeight(h);
  setHeight(h);
  imageBuffer->fill();
}

/// Returns the height of th display buffer
int ScriptDisplay::getHeight()
{
    return imageBuffer->height();
}

/// returns the width of the display buffer
int ScriptDisplay::getWidth()
{
  return imageBuffer->width();
}


/// Sets the width of the  text buffer and adjusts the image buffer size
void ScriptDisplay::setRows(int newRows)
{
  if(newRows>textBuffer.size())
  {
    while(newRows>textBuffer.size())
      textBuffer.append(QString(columns,' '));
  }
  else {
    while(newRows<textBuffer.size())
      textBuffer.takeFirst();
    if(cursorRow>newRows)
      cursorRow=newRows;
  }
  rows=newRows;
  (*imageBuffer)=imageBuffer->scaledToHeight(rows*charHeight);
  this->setMinimumHeight(rows*charHeight);
}

/// Returns the size of the text buffer
int ScriptDisplay::getRows()
{
  return rows;
}

/// Returns the length of one text buffer line
int ScriptDisplay::getColumns()
{
  return columns;
}

/// Returns the selected text
QString ScriptDisplay::getSelectedText()
{
  return QString("");
}

/// Inserts the text @param text into the text buffer on the current cursor position and repaints the window if @param update is true.
void ScriptDisplay::insertText(QString text,bool update)
{
  QStringList lines=text.split("\n");
  int c;

  for(c=0; c<lines.size(); c++)
  {
    if(cursorRow<rows)
    {
      (textBuffer[cursorRow]).replace(cursorCol,strlen(lines[c]),lines[c]);
        textBuffer[cursorRow]=textBuffer[cursorRow].leftJustified(columns,' ',true);
      if(c<lines.size()-1)
      {
        cursorRow++;
        cursorCol=0;
      }
    }
    else {
      cursorRow=rows-1;
      textBuffer.append(lines[c]);
      textBuffer.takeFirst();
    }
  }
  cursorCol+=lines.last().length();
  if(cursorCol>=columns)
    cursorCol=columns;



  if(update)
  {
    repaint();
    emit pointVisibleSignal(cursorCol*charWidth,cursorRow*charHeight);
  }

}

/// Sets the selected text area
int ScriptDisplay::setSelection(int startRow,int startCol,int endRow,int endCol)
{
  selectStartColumn=startCol;
  selectEndColumn=endCol;
  selectStartRow=startRow;
  selectEndRow=endRow;
}

/// Sets the text cursor to @param row , @param col
void ScriptDisplay::setCursor(int row,int col)
{
  cursorCol=col;
  cursorRow=row;
}


/// Replaces a single char in the text buffer without changing the cursor
void ScriptDisplay::setChar(int row,int col,char c)
{
  if(row<rows)
  {
    if(col<textBuffer[row].length())
      textBuffer[row].replace(col,1,QChar(c));
  }
}

/// Deletes the character before the cursor in the text buffer
void ScriptDisplay::backKey()
{
  if(cursorCol>0)
  {
    textBuffer[cursorRow].remove(cursorCol-1,1);
    cursorCol--;
    textBuffer[cursorRow].append(" ");
  }
  repaint();
}

/// Deletes the charactur at cursor position in the text buffer
void ScriptDisplay::deleteKey()
{
    textBuffer[cursorRow].remove(cursorCol,1);
    textBuffer[cursorRow].append(" ");
    repaint();
}

/// Overwrites the complete text buffer with whitespace
void ScriptDisplay::clearText()
{
  cursorRow=cursorCol=0;
  for(int c=0; c<textBuffer.size(); c++)
  {
    textBuffer[c].fill(' ',columns);
  }
  repaint();
}




