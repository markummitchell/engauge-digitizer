/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef WINDOW_MODEL_ABSTRACT_H
#define WINDOW_MODEL_ABSTRACT_H

#include <QStandardItemModel>
#include <QString>

/// Model for WindowTableAbstract
class WindowModelAbstract : public QStandardItemModel
{
public:
  /// Single constructor
  WindowModelAbstract ();
  virtual ~WindowModelAbstract ();

  /// Support dragging of multiple cells. Without this only one cell can be copied by dragging. Clipboard copying
  /// is handled elsewhere in the window class
  QMimeData *mimeData (const QModelIndexList &indexes) const;

private:

};

#endif // WINDOW_MODEL_ABSTRACT_H
