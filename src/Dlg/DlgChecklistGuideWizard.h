#ifndef DLG_CHECKLIST_GUIDE_WIZARD_H
#define DLG_CHECKLIST_GUIDE_WIZARD_H

#include <QDialog>

class MainWindow;
class QPushButton;

/// Dialog for setting up the checklist guide
class DlgChecklistGuideWizard : public QDialog
{
  Q_OBJECT;

 public:
  /// Single constructor
  DlgChecklistGuideWizard(MainWindow &mainWindow);

 private slots:
  /// Do preparation before dialog is displayed.
  virtual void showEvent (QShowEvent *event);

  /// Hide dialog
  void slotCancel();

  /// Save changes entered in dialog
  void slotOk ();

 private:
  DlgChecklistGuideWizard();

  void createWidgets();
  void handleOk();
  static int MINIMUM_DIALOG_WIDTH;
  void saveGeometryToSettings ();

  MainWindow &m_mainWindow;
  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QString m_dialogName;
};

#endif // DLG_CHECKLIST_GUIDE_WIZARD_H
