#ifndef DLG_SETTINGS_GRID_REMOVAL_H
#define DLG_SETTINGS_GRID_REMOVAL_H

#include "DlgSettingsAbstractBase.h"

class DlgModelGridRemoval;
class QCheckBox;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QHBoxLayout;
class QLineEdit;
class ViewPreview;

/// Stacked widget page for editing grid removal settings.
class DlgSettingsGridRemoval : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsGridRemoval(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotRemoveGridLines (int);
  void slotCloseDistance(const QString &);

  void slotDisableX(const QString &);
  void slotCountX(const QString &);
  void slotStartX(const QString &);
  void slotStepX(const QString &);
  void slotStopX(const QString &);

  void slotDisableY(const QString &);
  void slotCountY(const QString &);
  void slotStartY(const QString &);
  void slotStepY(const QString &);
  void slotStopY(const QString &);

  void slotRemoveParallel (int);

protected:
  virtual void handleOk ();

private:

  void createRemoveGridLines (QGridLayout *layout, int &row);
  void createRemoveGridLinesX (QGridLayout *layoutGridLines, int &row);
  void createRemoveGridLinesY (QGridLayout *layoutGridLines, int &row);
  void createRemoveParallel (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls ();

  QCheckBox *m_chkRemoveGridLines;
  QLineEdit *m_editCloseDistance;

  QComboBox *m_cmbDisableX;
  QLineEdit *m_editCountX;
  QLineEdit *m_editStartX;
  QLineEdit *m_editStepX;
  QLineEdit *m_editStopX;

  QComboBox *m_cmbDisableY;
  QLineEdit *m_editCountY;
  QLineEdit *m_editStartY;
  QLineEdit *m_editStepY;
  QLineEdit *m_editStopY;

  QCheckBox *m_chkRemoveParallel;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DlgModelGridRemoval *m_modelGridRemovalBefore;
  DlgModelGridRemoval *m_modelGridRemovalAfter;
};

#endif // DLG_SETTINGS_GRID_REMOVAL_H
