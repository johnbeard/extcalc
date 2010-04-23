/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         toolwidget.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This ist the base class for tool windows.

////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QDockWidget>
#include "global.h"


/**
 * @class ToolWidget
 * @brief DockWidget for calculator controls
 *
 * This ist the base class for the calculator tool windows.
 * Any tool widget must be a child of this class to manage common
 * controls.
 */
class ToolWidget :public QDockWidget
{
  /// If true, widget is shown in standard view
  bool active;

protected:
  /// Local copy of the preferences struct
  Preferences pref;

public:

  ToolWidget(QWidget*parent);

  virtual void setPref(Preferences newPref)=0;

  void setActive(bool ac)
  {
    active=ac;
  }

  bool isActive()
  {
    return active;
  }

};


#endif // TOOLWIDGET_H

