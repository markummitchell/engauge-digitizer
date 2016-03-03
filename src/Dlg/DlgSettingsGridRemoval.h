/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_GRID_REMOVAL_H
#define DLG_SETTINGS_GRID_REMOVAL_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelGridRemoval;
class QCheckBox;
class QComboBox;
class QDoubleValidator;
class QGraphicsScene;
class QGridLayout;
class QHBoxLayout;
class QLineEdit;
class ViewPreview;

/// Dialog for editing grid removal settings.
class DlgSettingsGridRemoval : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsGridRemoval(MainWindow &mainWindow);
  virtual ~DlgSettingsGridRemoval();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
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

protected:
  virtual void handleOk ();

private:

  void createRemoveGridLines (QGridLayout *layout, int &row);
  void createRemoveGridLinesX (QGridLayout *layoutGridLines, int &row);
  void createRemoveGridLinesY (QGridLayout *layoutGridLines, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls ();
  void updatePreview();

  QCheckBox *m_chkRemoveGridLines;
  QLineEdit *m_editCloseDistance;
  QDoubleValidator *m_validatorCloseDistance;

  QComboBox *m_cmbDisableX;
  QLineEdit *m_editCountX;
  QLineEdit *m_editStartX;
  QLineEdit *m_editStepX;
  QLineEdit *m_editStopX;
  QDoubleValidator *m_validatorCountX;
  QDoubleValidator *m_validatorStartX;
  QDoubleValidator *m_validatorStepX;
  QDoubleValidator *m_validatorStopX;

  QComboBox *m_cmbDisableY;
  QLineEdit *m_editCountY;
  QLineEdit *m_editStartY;
  QLineEdit *m_editStepY;
  QLineEdit *m_editStopY;
  QDoubleValidator *m_validatorCountY;
  QDoubleValidator *m_validatorStartY;
  QDoubleValidator *m_validatorStepY;
  QDoubleValidator *m_validatorStopY;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelGridRemoval *m_modelGridRemovalBefore;
  DocumentModelGridRemoval *m_modelGridRemovalAfter;
};

#endif // DLG_SETTINGS_GRID_REMOVAL_H
