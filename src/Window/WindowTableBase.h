/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef WINDOW_TABLE_BASE_H
#define WINDOW_TABLE_BASE_H

#include <QTableView>

class QMouseEvent;
class WindowModelBase;

/// Table view class with support for both drag-and-drop and copy-and-paste
class WindowTableBase : public QTableView
{
public:
  /// Single constructor.
  WindowTableBase(WindowModelBase &model);
  ~WindowTableBase();

private:
  WindowTableBase();
};

#endif // WINDOW_TABLE_BASE_H
