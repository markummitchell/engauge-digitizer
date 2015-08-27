#ifndef CHECKLIST_GUIDE_H
#define CHECKLIST_GUIDE_H

#include <QDockWidget>
#include <QTextBrowser>

/// Dockable text window containing checklist guide
class ChecklistGuide : public QDockWidget
{
 public:
  /// Single constructor
  ChecklistGuide ();

  /// Populate the browser with html
  void setHtml (const QString &html);

 private:

  QTextBrowser *m_browser;
};

#endif // CHECKLIST_GUIDE_H
