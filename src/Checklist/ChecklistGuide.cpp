#include "ChecklistGuide.h"
#include "ChecklistGuideBrowser.h"
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

void ChecklistGuide::closeEvent(QCloseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuide::closeEvent";

  emit signalChecklistClosed();
}

void ChecklistGuide::setHtml(const QString &html)
{
  m_browser->setText (html);
}
