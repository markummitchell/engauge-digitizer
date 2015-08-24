#ifndef CHECKLIST_GUIDE_WIZARD_H
#define CHECKLIST_GUIDE_WIZARD_H

#include <QWizard>

class MainWindow;
class QPushButton;

/// Wizard for setting up the checklist guide
class ChecklistGuideWizard : public QWizard
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuideWizard(MainWindow &mainWindow);

 private slots:

  /// Hide dialog
  void slotCancel();

  /// Save changes entered in dialog
  void slotOk ();

 private:
  ChecklistGuideWizard();

  QWizardPage *createPageCurveNames() const;
  QWizardPage *createPageLinesOrPoints() const;
  void handleOk();

  MainWindow &m_mainWindow;
  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QString m_dialogName;
};

#endif // CHECKLIST_GUIDE_WIZARD_H
