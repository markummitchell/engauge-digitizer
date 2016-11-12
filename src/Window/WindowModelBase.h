/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef WINDOW_MODEL_BASE_H
#define WINDOW_MODEL_BASE_H

#include "ExportDelimiter.h"
#include <QStandardItemModel>
#include <QString>
#include <QVector>

class WindowTable;

/// Model for WindowTable
class WindowModelBase : public QStandardItemModel
{
public:
  /// Single constructor
  WindowModelBase ();
  virtual ~WindowModelBase ();

  /// Support dragging of multiple cells. Without this only one cell can be copied by dragging. Clipboard copying
  /// is handled elsewhere in the window class
  QMimeData *mimeData (const QModelIndexList &indexes) const;

  /// Convert the selection into exportable html which is good for spreadsheets
  QString selectionAsHtml () const;

  /// Convert the selection into exportable text which is good for text editors
  QString selectionAsText (ExportDelimiter delimiter) const;

  /// Save output delimiter
  void setDelimiter (ExportDelimiter delimiter);

  /// Save the view so this class can access the current selection
  void setView (WindowTable &view);

private:
  int fold2dIndexes (int row,
                     int col,
                     int rowLow,
                     int colLow,
                     int colHigh) const;
  void selectionAsTable (int &rowLow,
                         int &colLow,
                         int &rowHigh,
                         int &colHigh,
                         QVector<QString> &table) const;

  ExportDelimiter m_delimiter;
  WindowTable *m_view;
};

#endif // WINDOW_MODEL_BASE_H
