#ifndef DLG_SETTINGS_COMMON_H
#define DLG_SETTINGS_COMMON_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelCommon;
class QGridLayout;
class QSpinBox;

/// Dialog for editing axes checker settings.
class DlgSettingsCommon : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCommon(MainWindow &mainWindow);
  virtual ~DlgSettingsCommon();

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotCursorSize (int);
  void slotExtraPrecision (int);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void updateControls();

  QSpinBox *m_spinCursorSize;
  QSpinBox *m_spinExtraPrecision;

  DocumentModelCommon *m_modelCommonBefore;
  DocumentModelCommon *m_modelCommonAfter;
};

#endif // DLG_SETTINGS_COMMON_H
