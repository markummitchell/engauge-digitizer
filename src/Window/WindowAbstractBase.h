/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef WINDOW_ABSTRACT_BASE_H
#define WINDOW_ABSTRACT_BASE_H

#include <QDockWidget>

class CmdMediator;
class MainWindowModel;
class QString;
class QTableView;
class Transformation;

/// Dockable widget abstract base class. This class enforces support for the MainWindow class, in terms
/// of copying selected stuff, and also for performing clearing and updates
class WindowAbstractBase : public QDockWidget
{
  Q_OBJECT;

public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  WindowAbstractBase (QWidget *parent);
  virtual ~WindowAbstractBase ();

  /// Clear stale information
  virtual void clear () = 0;

  /// Catch close event so corresponding menu item in MainWindow can be updated accordingly
  virtual void closeEvent(QCloseEvent *event) = 0;

  /// Copy the current selection to the clipboard
  virtual void doCopy () = 0;

  /// Give table status so MainWindow can determine if table can be copied
  void getTableStatus (bool &tableIsActive,
                       bool &tableIsCopyable) const;

  /// Populate the table with the specified Curve
  virtual void update (const CmdMediator &cmdMediator,
                       const MainWindowModel &modelMainWindow,
                       const QString &curveSelected,
                       const Transformation &transformation) = 0;

protected:
  /// QTableView-based class used by child class
  virtual QTableView *view() const = 0;

private:
  WindowAbstractBase();

};

#endif // WINDOW_ABSTRACT_BASE_H
