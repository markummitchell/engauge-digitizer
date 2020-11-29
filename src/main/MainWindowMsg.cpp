/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "MainWindowMsg.h"
#include <QApplication>
#include <QMessageBox>

MainWindowMsg::MainWindowMsg (const QString &msg) :
  QMainWindow(),
  m_msg (msg)
{
}

MainWindowMsg::~MainWindowMsg()
{
}

void MainWindowMsg::showEvent (QShowEvent * /* event */)
{
  // Show message in gui instead of cout or cerr since console output is disabled in at least Microsoft Windows
  QMessageBox msgBox (QMessageBox::Information,
                      QObject::tr ("Engauge Digitizer"),
                      m_msg);

  // Connect so closing dialog also closes this class
  connect (&msgBox, SIGNAL (buttonClicked (QAbstractButton *)), this, SLOT (slotClose (QAbstractButton *)));

  msgBox.exec();
}

void MainWindowMsg::slotClose (QAbstractButton *)
{
  close ();
  qApp->quit();

  exit (0);
}
