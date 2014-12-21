#ifndef DLG_SETTINGS_AXES_HIGHLIGHTS_H
#define DLG_SETTINGS_AXES_HIGHLIGHTS_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelAxesHighlights;
class QAbstractButton;
class QButtonGroup;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QRadioButton;
class ViewPreview;

/// Stacked widget page for editing axes highlights settings.
class DlgSettingsAxesHighlights : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsAxesHighlights(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotGroupMode (QAbstractButton*);
  void slotLineColor(const QString &);
  void slotSeconds (const QString &);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls();
  void updatePreview();

  QButtonGroup *m_groupMode;
  QRadioButton *m_btnNever;
  QRadioButton *m_btnNSeconds;
  QRadioButton *m_btnForever;

  QComboBox *m_cmbSeconds; // Seconds when HIGHLIGHT_MODE_N_SECONDS is applied

  QComboBox *m_cmbLineColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelAxesHighlights *m_modelAxesHighlightsBefore;
  DocumentModelAxesHighlights *m_modelAxesHighlightsAfter;
};

#endif // DLG_SETTINGS_AXES_HIGHLIGHTS_H
