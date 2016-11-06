/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_WINDOW_H
#define FITTING_WINDOW_H

#include <QDockWidget>

class CmdMediator;
class Curve;
class FittingModel;
class MainWindowModel;
class QItemSelection;
class QString;
class QTableView;
class Transformation;

/// Window that displays curve fitting as applied to the currently selected curve
///
/// The strategy used assumes no changes to the DIG file format will be made for the original implementation.
/// Since settings cannot be saved for the Document or Curves, this keeps the implementation siple
class FittingWindow : public QDockWidget
{
  Q_OBJECT;

public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  FittingWindow (QWidget *parent);
  virtual ~FittingWindow ();

  /// Clear stale information
  void clear ();

  /// Catch close event so corresponding menu item in MainWindow can be updated accordingly
  virtual void closeEvent(QCloseEvent *event);

  /// Populate the table with the specified Curve
  void update (const CmdMediator &cmdMediator,
               const MainWindowModel &modelMainWindow,
               const QString &curveSelected,
               const Transformation &transformation);

public slots:

signals:
  /// Signal that this QDockWidget was just closed
  void signalFittingWindowClosed();

private:
  FittingWindow();

  QTableView *m_view;
};

#endif // FITTING_WINDOW_H
