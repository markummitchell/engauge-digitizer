#ifndef DLG_SETTINGS_AXES_HIGHLIGHT_H
#define DLG_SETTINGS_AXES_HIGHLIGHT_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelAxesHighlight;
class QAbstractButton;
class QButtonGroup;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QRadioButton;
class ViewPreview;

/// Stacked widget page for editing grid display settings.
class DlgSettingsAxesHighlight : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsAxesHighlight(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotGroupLifetime (QAbstractButton*);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls();
  void updatePreview();

  QButtonGroup *m_groupLifetime;
  QRadioButton *m_btnNever;
  QRadioButton *m_btn2Seconds;
  QRadioButton *m_btn10Seconds;
  QRadioButton *m_btnAlways;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelAxesHighlight *m_modelAxesHighlightBefore;
  DocumentModelAxesHighlight *m_modelAxesHighlightAfter;
};

#endif // DLG_SETTINGS_AXES_HIGHLIGHT_H
