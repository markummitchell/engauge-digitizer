#ifndef DLG_SETTINGS_FILTER_H
#define DLG_SETTINGS_FILTER_H

#include "DlgSettingsAbstractBase.h"

class QGraphicsScene;
class QGridLayout;
class QLabel;
class QRadioButton;
class ViewPreview;
class ViewProfile;

/// Stacked widget page for editing filtering settings.
class DlgSettingsFilter : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsFilter(QWidget *parent = 0);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotForeground();
  void slotHue();
  void slotIntensity();
  void slotSaturation();
  void slotValue();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void createProfileAndScale (QGridLayout *layout, int &row);

  QRadioButton *m_btnIntensity;
  QRadioButton *m_btnForeground;
  QRadioButton *m_btnHue;
  QRadioButton *m_btnSaturation;
  QRadioButton *m_btnValue;

  QGraphicsScene *m_sceneProfile;
  ViewProfile *m_viewProfile;

  QLabel *m_scale;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_SETTINGS_FILTER_H
