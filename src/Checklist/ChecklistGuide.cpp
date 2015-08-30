#include "ChecklistGuide.h"
#include "ChecklistGuideBrowser.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QTextBrowser>

ChecklistGuide::ChecklistGuide () :
  m_browser (0)
{
  setVisible (false);
  setStatusTip (tr ("Checklist Guide"));
  setWhatsThis (tr ("Checklist Guide\n\n"
                    "This box contains a checklist of step suggested by the Checklist Guide Wizard. Following "
                    "these steps should produce a set of digitized points in an output file.\n\n"
                    "To run the Checklist Guide Wizard when an image file is imported, select the "
                    "Help / Checklist Wizard menu option."));

  m_browser = new ChecklistGuideBrowser;
  setWidget (m_browser);
}

void ChecklistGuide::bindToDocument(Document &document)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuide::bindToDocument";

  ENGAUGE_CHECK_PTR (m_browser);

  m_browser->bindToDocument(document);
}

void ChecklistGuide::closeEvent(QCloseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuide::closeEvent";

  emit signalChecklistClosed();
}

void ChecklistGuide::setTemplateHtml (const QString &html)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuide::setTemplateHtml";

  m_browser->setTemplateHtml (html);
}

void ChecklistGuide::unbindFromDocument()
{
  if (m_browser != 0) {
    m_browser->unbindFromDocument();
  }
}
