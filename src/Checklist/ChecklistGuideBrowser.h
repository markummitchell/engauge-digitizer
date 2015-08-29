#ifndef CHECKLIST_GUIDE_BROWSER_H
#define CHECKLIST_GUIDE_BROWSER_H

#include <QTextBrowser>

/// Class that adds rudimentary tree collapse/expand functionality to QTextBrowser
class ChecklistGuideBrowser : public QTextBrowser
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuideBrowser();

  /// Modify the html before sending to QTextBrowser
  virtual void setHtml (const QString &html);

 private slots:
  void slotAnchorClicked (const QUrl &url);

};

#endif // CHECKLIST_GUIDE_BROWSER_H
