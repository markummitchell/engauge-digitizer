/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_ABOUT_H
#define DLG_ABOUT_H

#include <QMessageBox>

class MainWindow;

/// About Engauge dialog. This provides a hidden shortcut for triggering ENGAUGE_ASSERT
class DlgAbout : public QMessageBox
{
  Q_OBJECT;

 public:
  /// Single constructor
  DlgAbout(MainWindow  &mainWindow);

 private:
  DlgAbout();
  
  MainWindow &m_mainWindow;
};

#endif // DLG_ABOUT_H
