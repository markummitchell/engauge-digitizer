#include "HelpBrowser.h"
#include "Logger.h"
#include <QHelpEngine>

HelpBrowser::HelpBrowser (QHelpEngine *engine,
                          QWidget *parent) :
  QTextBrowser (parent),
  m_engine (engine)
{
}

QVariant HelpBrowser::loadResource (int type, const QUrl &url)
{
  LOG4CPP_INFO_S ((*mainCat)) << "HelpBrowser::loadResource"
                              << " scheme=" << url.scheme().toLatin1().data();

  if (url.scheme() == "qthelp") {
    return QVariant (m_engine->fileData (url));
  } else {
    return QTextBrowser::loadResource (type, url);
  }
}
