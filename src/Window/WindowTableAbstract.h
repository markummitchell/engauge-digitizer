/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef WINDOW_TABLE_ABSTRACT_H
#define WINDOW_TABLE_ABSTRACT_H

#include <QTableView>

class QMouseEvent;
class QStandardItemModel;

/// Table view class with support for both drag-and-drop and copy-and-paste
class WindowTableAbstract : public QTableView
{
public:
  /// Single constructor.
  WindowTableAbstract(QStandardItemModel &model);
  ~WindowTableAbstract();

private:
  WindowTableAbstract();
};

#endif // WINDOW_TABLE_ABSTRACT_H
