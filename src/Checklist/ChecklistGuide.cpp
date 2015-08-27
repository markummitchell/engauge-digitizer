#include "ChecklistGuide.h"
#include "Logger.h"
#include <QTextBrowser>

ChecklistGuide::ChecklistGuide () :
  m_browser (0)
{
  m_browser = new QTextBrowser;
  setWidget (m_browser);
}

void ChecklistGuide::setHtml(const QString &html)
{
  m_browser->setText (html);
}
