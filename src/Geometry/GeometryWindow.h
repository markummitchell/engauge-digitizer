/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_WINDOW_H
#define GEOMETRY_WINDOW_H

#include <QDockWidget>

/// Window that displays the geometry information, as a table, for the current curve
class GeometryWindow : public QDockWidget
{
  Q_OBJECT;

public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  GeometryWindow (QWidget *parent);
  virtual ~GeometryWindow ();

  /// Catch close event so corresponding menu item in MainWindow can be updated accordingly
  virtual void closeEvent(QCloseEvent *event);

signals:
  /// Signal that this QDockWidget was just closed
  void signalGeometryWindowClosed();

private:
  GeometryWindow();

};

#endif // GEOMETRY_WINDOW_H
