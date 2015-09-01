#include "HelpBrowser.h"
#include "HelpWindow.h"
#include "Logger.h"
#include <QApplication>
#include <QHelpContentWidget>
#include <QHelpEngine>
#include <QHelpIndexWidget>
#include <QSplitter>
#include <QTabWidget>

HelpWindow::HelpWindow(QWidget *parent) :
  QDockWidget (parent)
{
  QString path = QApplication::applicationDirPath() + "/documentation/engauge.qhc";
  QHelpEngine *helpEngine = new QHelpEngine (path);
  helpEngine->setupData();

  QTabWidget *tabs = new QTabWidget;
  tabs->addTab (helpEngine->contentWidget(),
                "Contents");
  tabs->addTab (helpEngine->indexWidget(),
                "Index");

  HelpBrowser *browser = new HelpBrowser (helpEngine);
  browser->setSource (QUrl ("qthelp://engaugedigitizer.net/doc/index.html"));
  connect (helpEngine->contentWidget (), SIGNAL (linkActivated (QUrl)), browser, SLOT (setSource (QUrl)));
  connect (helpEngine->indexWidget (), SIGNAL (linkActivated (QUrl, QString)), browser, SLOT (setSource (QUrl)));

  QSplitter *splitter = new QSplitter (Qt::Horizontal);
  splitter->insertWidget (0, tabs);
  splitter->insertWidget (1, browser);

  setWidget (splitter);
}

