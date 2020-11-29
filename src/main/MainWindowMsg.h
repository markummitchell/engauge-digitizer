/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MAIN_WINDOW_MSG_H
#define MAIN_WINDOW_MSG_H

#include <QMainWindow>
#include <QShowEvent>

class QAbstractButton;

/// Main window for momentary message dialog
///
/// Comments:
/// - Typically program will exit after showing this
/// - No logging is done since this is started (and finishes) before logging
class MainWindowMsg : public QMainWindow
{
  Q_OBJECT;

public:
  /// Single constructor
  MainWindowMsg(const QString &msg);
  ~MainWindowMsg();

  /// Processing performed after gui becomes available
  virtual void showEvent(QShowEvent *);

private slots:
  void slotClose (QAbstractButton *);

private:
  
  MainWindowMsg();

  const QString m_msg;
  
};

#endif // MAIN_WINDOW_MSG_H
