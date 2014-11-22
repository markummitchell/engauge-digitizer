#ifndef DLG_SETTINGS_GRID_DISPLAY_H
#define DLG_SETTINGS_GRID_DISPLAY_H

#include "DlgSettingsAbstractBase.h"

class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QLineEdit;
class ViewPreview;

/// Stacked widget page for editing grid display settings.
class DlgSettingsGridDisplay : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsGridDisplay(QWidget *parent = 0);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
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

  void createX (QGridLayout *layout, int &row);
  void createY (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);

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

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_SETTINGS_GRID_DISPLAY_H
