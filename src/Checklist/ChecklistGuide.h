#ifndef CHECKLIST_GUIDE_H
#define CHECKLIST_GUIDE_H

#include <QDockWidget>
#include <QTextBrowser>

/// Dockable text window containing checklist guide
class ChecklistGuide : public QDockWidget
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuide ();

  /// Catch close event so corresponding menu item in MainWindow can be updated accordingly
  virtual void closeEvent(QCloseEvent *event);

  /// Populate the browser with html
  void setHtml (const QString &html);

 signals:
  /// Signal that this QDockWidget was just closed
  void signalChecklistClosed();

 private:

  QTextBrowser *m_browser;
};

#endif // CHECKLIST_GUIDE_H
