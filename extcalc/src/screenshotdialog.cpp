#include "screenshotdialog.h"
#include <QWidget>
#include <QFileDialog>
#include <QColorDialog>
#include "global.h"


/// ScreenshotDialog constructor to initialize ui and window
ScreenshotDialog::ScreenshotDialog(QWidget*parent) :QDockWidget(tr("Screenshot"),parent,Qt::Window)
{
  screenshotUi.setupUi(this);

    colorIcon=new QPixmap(20,20);
    paintColor.setRgb(255,0,0);
    colorIcon->fill(paintColor);
    screenshotUi.colorButton->setIcon(*colorIcon);
    drawState=DRAWNONE;

    screenshotUi.formatBox->insertItem("Auto");
    screenshotUi.formatBox->insertItem("PNG");
    screenshotUi.formatBox->insertItem("JPEG");
    screenshotUi.formatBox->insertItem("BMP");
    screenshotUi.formatBox->insertItem("XPM");

    QObject::connect(screenshotUi.pathButton,SIGNAL(clicked()),this,SLOT(openButtonSlot()));
    QObject::connect(screenshotUi.colorButton,SIGNAL(clicked()),this,SLOT(colorButtonSlot()));
    QObject::connect(screenshotUi.penBox,SIGNAL(valueChanged(int)),this,SLOT(penValueSlot(int)));
    QObject::connect(screenshotUi.redoButton,SIGNAL(clicked()),this,SLOT(forwardButtonSlot()));
    QObject::connect(screenshotUi.undoButton,SIGNAL(clicked()),this,SLOT(backButtonSlot()));
    QObject::connect(screenshotUi.clearButton,SIGNAL(clicked()),this,SLOT(clearButtonSlot()));
    QObject::connect(screenshotUi.freeButton,SIGNAL(clicked()),this,SLOT(freeButtonSlot()));
    QObject::connect(screenshotUi.lineButton,SIGNAL(clicked()),this,SLOT(lineButtonSlot()));
    QObject::connect(screenshotUi.rectButton,SIGNAL(clicked()),this,SLOT(rectButtonSlot()));
    QObject::connect(screenshotUi.ellipseButton,SIGNAL(clicked()),this,SLOT(circleButtonSlot()));
    QObject::connect(screenshotUi.rubberButton,SIGNAL(clicked()),this,SLOT(rubberButtonSlot()));
    QObject::connect(screenshotUi.textButton,SIGNAL(clicked()),this,SLOT(textButtonSlot()));
    QObject::connect(screenshotUi.saveButton,SIGNAL(clicked()),this,SLOT(saveButtonSlot()));
}

/// Shows the open file dialog to select a location for storing the screenshot
void ScreenshotDialog::openButtonSlot()
{
  QString path=QFileDialog::getSaveFileName(this,tr("Save Screenshot"),".","Images (*.png *.xpm *.jpg *.bmp)");
  screenshotUi.pathLine->setText(path);

}

/// Show the color dialog and update the stored draw color as well as the setting of the GraphOutput object
void ScreenshotDialog::colorButtonSlot()
{
  if(paintColor.red()==4 &&paintColor.green()==4 &&paintColor.blue()==4)
    paintColor.setRgb(0,0,0);
  QColor col=QColorDialog::getColor(paintColor,this,GRAPHSOLVEC_STR38);
  paintColor=col;
  colorIcon->fill(paintColor);
  screenshotUi.colorButton->setIconSet(*colorIcon);
  if(paintColor.red()<4 &&paintColor.green()<4 &&paintColor.blue()<4)
    paintColor.setRgb(4,4,4);

  emit drawSignal(drawState,paintColor,screenshotUi.penBox->value());
}

/// Select the draw pen width
void ScreenshotDialog::penValueSlot(int value)
{
  if(screenshotUi.rubberButton->isOn())
    emit drawSignal(drawState,QColor(0,0,0),value);
  else emit drawSignal(drawState,paintColor,value);
}

/// Redo button slot
void ScreenshotDialog::forwardButtonSlot()
{
  drawState=DRAWFORWARD;
  emit drawSignal(DRAWFORWARD,paintColor,screenshotUi.penBox->value());
}

/// Undo button slot
void ScreenshotDialog::backButtonSlot()
{
  drawState=DRAWBACK;
  emit drawSignal(DRAWBACK,paintColor,screenshotUi.penBox->value());
}

/// Clear all additional drawing from the graphics window
void ScreenshotDialog::clearButtonSlot()
{
  drawState=DRAWCLEAR;
  emit drawSignal(DRAWCLEAR,paintColor,screenshotUi.penBox->value());
}

/// Select the tool for drawing a free line
void ScreenshotDialog::freeButtonSlot()
{
  drawState=DRAWFREE;
  screenshotUi.freeButton->setOn(true);
  screenshotUi.lineButton->setOn(false);
  screenshotUi.rectButton->setOn(false);
  screenshotUi.ellipseButton->setOn(false);
  screenshotUi.rubberButton->setOn(false);
  screenshotUi.colorButton->setEnabled(true);
  screenshotUi.textButton->setOn(false);
  emit drawSignal(DRAWFREE,paintColor,screenshotUi.penBox->value());
}

/// Select the tool for a straight line
void ScreenshotDialog::lineButtonSlot()
{
  drawState=DRAWLINE;
  screenshotUi.freeButton->setOn(false);
  screenshotUi.lineButton->setOn(true);
  screenshotUi.rectButton->setOn(false);
  screenshotUi.ellipseButton->setOn(false);
  screenshotUi.rubberButton->setOn(false);
  screenshotUi.colorButton->setEnabled(true);
  screenshotUi.textButton->setOn(false);
  emit drawSignal(DRAWLINE,paintColor,screenshotUi.penBox->value());
}

/// Select the tool for a drawing a rectangle
void ScreenshotDialog::rectButtonSlot()
{
  drawState=DRAWRECT;
  screenshotUi.freeButton->setOn(false);
  screenshotUi.lineButton->setOn(false);
  screenshotUi.rectButton->setOn(true);
  screenshotUi.ellipseButton->setOn(false);
  screenshotUi.rubberButton->setOn(false);
  screenshotUi.colorButton->setEnabled(true);
  screenshotUi.textButton->setOn(false);
  emit drawSignal(DRAWRECT,paintColor,screenshotUi.penBox->value());
}

/// Select the tool for drawing an ellipse
void ScreenshotDialog::circleButtonSlot()
{
  drawState=DRAWCIRCLE;
  screenshotUi.freeButton->setOn(false);
  screenshotUi.lineButton->setOn(false);
  screenshotUi.rectButton->setOn(false);
  screenshotUi.ellipseButton->setOn(true);
  screenshotUi.rubberButton->setOn(false);
  screenshotUi.colorButton->setEnabled(true);
  screenshotUi.textButton->setOn(false);
  emit drawSignal(DRAWCIRCLE,paintColor,screenshotUi.penBox->value());
}

/// Select the rubber tool
void ScreenshotDialog::rubberButtonSlot()
{
  drawState=DRAWFREE;
  screenshotUi.freeButton->setOn(false);
  screenshotUi.lineButton->setOn(false);
  screenshotUi.rectButton->setOn(false);
  screenshotUi.ellipseButton->setOn(false);
  screenshotUi.rubberButton->setOn(true);
  screenshotUi.colorButton->setEnabled(false);
  screenshotUi.textButton->setOn(false);
  emit drawSignal(DRAWFREE,QColor(0,0,0),8);
}

/// Select the text tool
void ScreenshotDialog::textButtonSlot()
{
  drawState=DRAWTEXT;
  screenshotUi.freeButton->setOn(false);
  screenshotUi.lineButton->setOn(false);
  screenshotUi.rectButton->setOn(false);
  screenshotUi.ellipseButton->setOn(false);
  screenshotUi.rubberButton->setOn(false);
  screenshotUi.colorButton->setEnabled(true);
  screenshotUi.textButton->setOn(true);
  emit drawSignal(DRAWTEXT,paintColor,screenshotUi.penBox->value());
}

/// This slot receives a pointer to the rendered screenshot from the GraphOuput object and stores it to the location given in the pathLine
void ScreenshotDialog::screenshotSlot(QPixmap*scr)
{
  struct stat fileInfo;
  if(screenshotUi.pathLine->text().length() <=0)
  {
    ErrorBox(tr("Please insert a valid path to save screenshot!"));
    return;
  }
  if(lstat(screenshotUi.pathLine->text(),&fileInfo) == 0)
  {
    if(S_ISREG(fileInfo.st_mode))
    {
      if(YesNoCancelBox(tr("Really overwrite file %1").arg(screenshotUi.pathLine->text()))!=0)
        return;
    }
    else
    {
      ErrorBox(tr("%1 is no valid file.\n Can't overwrite it!").arg(screenshotUi.pathLine->text()));
      return;
    }
  }
  QString format;
  if(screenshotUi.formatBox->currentText() == "Auto")
  {
    format= screenshotUi.pathLine->text().right(3).upper();
    if(format=="JPG" ||  screenshotUi.pathLine->text().right(4).upper()=="JPEG")
      format=QString("JPEG");
    else if(format!="PNG" && format!="BMP" && format!="XPM")
    {
      WarningBox(tr("Unknown file format!\nAssuming png."));
      format=QString("PNG");
    }
  }
  else format=screenshotUi.formatBox->currentText();
  if(scr->save(screenshotUi.pathLine->text(),format))
    MessageBox(GRAPHSOLVEC_STR34);
  else ErrorBox(GRAPHSOLVEC_STR35);
}

void ScreenshotDialog::saveButtonSlot()
{

  emit getScreenshotSignal(screenshotUi.widthBox->value(),screenshotUi.heightBox->value());

}

