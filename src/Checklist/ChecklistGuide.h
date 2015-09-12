#ifndef CHECKLIST_GUIDE_H
#define CHECKLIST_GUIDE_H

#include <QDockWidget>

class ChecklistGuideBrowser;
class CmdMediator;

/// Dockable text window containing checklist guide
class ChecklistGuide : public QDockWidget
{
  Q_OBJECT;

 public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  ChecklistGuide (QWidget *parent);

  /// When browser is empty, it is pointless to show it
  bool browserIsEmpty () const;

  /// Catch close event so corresponding menu item in MainWindow can be updated accordingly
  virtual void closeEvent(QCloseEvent *event);

  /// Populate the browser with template html
  void setTemplateHtml (const QString &html,
                        const QStringList &curveNames);

  /// Update using current CmdMediator/Document state
  void update (const CmdMediator &cmdMediator,
               bool documentIsExported);

 signals:
  /// Signal that this QDockWidget was just closed
  void signalChecklistClosed();

 private:
  ChecklistGuide ();

  // Display information using html, which is possible with QTextBrowser, so images can be embedded. Although the
  // format is structured as a tree, a tree widget is not used since tree widgets are not compatible with embedded images
  // (other than optional tree item icons on the left)
  ChecklistGuideBrowser *m_browser;
};

#endif // CHECKLIST_GUIDE_H
