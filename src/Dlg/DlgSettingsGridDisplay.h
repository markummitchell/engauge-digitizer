/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_GRID_DISPLAY_H
#define DLG_SETTINGS_GRID_DISPLAY_H

#include "DlgSettingsAbstractBase.h"
#include "GridLines.h"

class DocumentModelGridDisplay;
class QCheckBox;
class QComboBox;
class QDoubleValidator;
class QGraphicsScene;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLineEdit;
class ViewPreview;

/// Dialog for editing grid display settings.
class DlgSettingsGridDisplay : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsGridDisplay(MainWindow &mainWindow);
  virtual ~DlgSettingsGridDisplay();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:

  void slotColor (const QString &);

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

  void createDisplayCommon (QGridLayout *layout, int &row);
  void createDisplayGridLinesX (QGridLayout *layoutGridLines, int &row);
  void createDisplayGridLinesY (QGridLayout *layoutGridLines, int &row);
  void createPreview (QGridLayout *layout, int &row);
  bool textItemsAreValid () const;
  void updateControls ();
  void updateDisplayedVariableX ();
  void updateDisplayedVariableY ();
  void updatePreview();

  QGroupBox *m_groupX;
  QComboBox *m_cmbDisableX;
  QLineEdit *m_editCountX;
  QLineEdit *m_editStartX;
  QLineEdit *m_editStepX;
  QLineEdit *m_editStopX;
  QDoubleValidator *m_validatorCountX;
  QDoubleValidator *m_validatorStartX;
  QDoubleValidator *m_validatorStepX;
  QDoubleValidator *m_validatorStopX;

  QGroupBox *m_groupY;
  QComboBox *m_cmbDisableY;
  QLineEdit *m_editCountY;
  QLineEdit *m_editStartY;
  QLineEdit *m_editStepY;
  QLineEdit *m_editStopY;
  QDoubleValidator *m_validatorCountY;
  QDoubleValidator *m_validatorStartY;
  QDoubleValidator *m_validatorStepY;
  QDoubleValidator *m_validatorStopY;

  QComboBox *m_cmbColor;

  GridLines m_gridLines;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelGridDisplay *m_modelGridDisplayBefore;
  DocumentModelGridDisplay *m_modelGridDisplayAfter;
};

#endif // DLG_SETTINGS_GRID_DISPLAY_H
