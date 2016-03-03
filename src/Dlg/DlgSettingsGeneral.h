/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_GENERAL_H
#define DLG_SETTINGS_GENERAL_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelGeneral;
class QGridLayout;
class QPushButton;
class QSpinBox;

/// Dialog for editing general settings.
class DlgSettingsGeneral : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsGeneral(MainWindow &mainWindow);
  virtual ~DlgSettingsGeneral();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotCursorSize (int);
  void slotExtraPrecision (int);
  void slotSaveDefault();

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  void updateControls();

  QSpinBox *m_spinCursorSize;
  QSpinBox *m_spinExtraPrecision;

  QPushButton *m_btnSaveDefault;

  DocumentModelGeneral *m_modelGeneralBefore;
  DocumentModelGeneral *m_modelGeneralAfter;
};

#endif // DLG_SETTINGS_GENERAL_H
