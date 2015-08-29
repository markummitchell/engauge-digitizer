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

  // Display information using html, which is possible with QTextBrowser, so images can be embedded. Although the
  // format is structured as a tree, a tree widget is not used since tree widgets are not compatible with embedded images
  // (other than optional tree item icons on the left)
  QTextBrowser *m_browser;
};

#endif // CHECKLIST_GUIDE_H
