/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_EDIT_POINT_GRAPH_LINE_EDIT_H
#define DLG_EDIT_POINT_GRAPH_LINE_EDIT_H

#include <QLineEdit>

class QWidget;

/// Adds hover highlighting to QLineEdit
class DlgEditPointGraphLineEdit : public QLineEdit
{
  Q_OBJECT;

public:
  /// Single constructor
  DlgEditPointGraphLineEdit (QWidget *widget = 0);
  ~DlgEditPointGraphLineEdit ();

  /// Hover entry triggers clearing of the background color so user does not think of widget as disabled and is encouraged to enter text
  virtual void enterEvent(QEvent *);

  /// Hover exit triggers restoration of the background color
  virtual void leaveEvent (QEvent *);

  /// Update background given the current state
  void updateBackground ();

private:

  bool m_hover;
};

#endif // DLG_EDIT_POINT_GRAPH_LINE_EDIT_H
