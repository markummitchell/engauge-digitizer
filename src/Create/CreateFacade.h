/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_FACADE_H
#define CREATE_FACADE_H

#include <QObject>

class MainWindow;

/// Facade class that wraps around all of the create classes for MainWindow. We derive from QObject and
/// use Q_OBJECT so translations work
class CreateFacade : public QObject
{
  Q_OBJECT

public:
  /// Single constructor.
  CreateFacade();

  /// Create QAction facade
  void create (MainWindow &mw);

};

#endif // CREATE_FACADE_H
