#include "ChecklistGuideBrowser.h"
#include "Logger.h"

ChecklistGuideBrowser::ChecklistGuideBrowser ()
{
  setOpenLinks (false); // Disable automatic link following

  connect (this, SIGNAL (anchorClicked (const QUrl &)), this, SLOT (slotAnchorClicked (const QUrl &)));
}

void ChecklistGuideBrowser::setHtml (const QString &html)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::setHtml";

  QTextBrowser::setHtml (html);
}

void ChecklistGuideBrowser::slotAnchorClicked (const QUrl &url)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::slotAnchorClicked";

  QString anchor;
  if (url.hasFragment ()) {
    anchor = url.fragment ();
  }
}



