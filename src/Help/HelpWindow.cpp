/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "HelpBrowser.h"
#include "HelpWindow.h"
#include "Logger.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QHelpContentWidget>
#include <QHelpEngine>
#include <QHelpIndexWidget>
#include <QSplitter>
#include <QTabWidget>

const int MIN_WIDTH = 600;
const int MIN_HEIGHT = 600;

HelpWindow::HelpWindow(QWidget *parent) :
  QDockWidget (parent)
{
  setMinimumWidth (MIN_WIDTH);
  setMinimumHeight (MIN_HEIGHT);

#ifndef OSX_RELEASE
  QHelpEngine *helpEngine = new QHelpEngine (helpPath());
  helpEngine->setupData();

  QTabWidget *tabs = new QTabWidget;
  tabs->addTab (helpEngine->contentWidget(),
                tr ("Contents"));
  tabs->addTab (helpEngine->indexWidget(),
                tr ("Index"));

  HelpBrowser *browser = new HelpBrowser (helpEngine);

  // URL is constructed from <namespace>, <virtualFolder> and <file> in engauge.qhp
  browser->setSource (QUrl ("qthelp://engaugedigitizer.net/doc/index.html"));

  connect (helpEngine->contentWidget (), SIGNAL (linkActivated (QUrl)), browser, SLOT (setSource (QUrl)));
  connect (helpEngine->indexWidget (), SIGNAL (linkActivated (QUrl, QString)), browser, SLOT (setSource (QUrl)));

  QSplitter *splitter = new QSplitter (Qt::Horizontal);
  splitter->insertWidget (0, tabs);
  splitter->insertWidget (1, browser);

  setWidget (splitter);
#endif
}

#ifndef OSX_RELEASE
QString HelpWindow::helpPath() const
{
  // Possible locations of help file. Each entry is first tried as is, and then with
  // applicationDirPath as a prefix. Each entry should probably start with a slash. This
  // search approach offers some flexibility in the help file location
  QStringList paths;
#ifdef HELPDIR
#define QUOTE(string) _QUOTE(string)
#define _QUOTE(string) #string
  QString path = QString ("%1/engauge.qhc")
    .arg (QUOTE (HELPDIR));
  paths << path;
#endif
  paths << "/documentation/engauge.qhc";
  paths << "/../share/doc/engauge-digitizer/engauge.qhc";
  paths << "/usr/share/engauge-digitizer-doc/engauge.qhc";

  QStringList::iterator itr;
  for (itr = paths.begin(); itr != paths.end(); itr++) {

    QString pathAsIs = *itr;

    QFileInfo fileAsIs (pathAsIs);
    if (fileAsIs.exists()) {
      return pathAsIs;
    }

    QString pathWithPrefix = QApplication::applicationDirPath() + pathAsIs;

    QFileInfo fileWithPrefix (pathWithPrefix);
    if (fileWithPrefix.exists()) {
      return pathWithPrefix;
    }
  }

  return ""; // Empty file, since help file was never found, will simply result in empty help contents
}
#endif
