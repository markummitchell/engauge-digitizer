#ifndef DLG_SETTINGS_CURVE_PROPERTIES_H
#define DLG_SETTINGS_CURVE_PROPERTIES_H

#include "DlgSettingsAbstractBase.h"

class ViewPreview;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QGroupBox;

/// Stacked widget page for editing curve properties settings.
class DlgSettingsCurveProperties : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCurveProperties(CmdMediator &cmdMediator,
                             QWidget *parent = 0);

private slots:
  void slotLineColor(const QString &);
  void slotLineSize(const QString &);
  void slotLineType(const QString &);
  void slotPointLineColor(const QString &);
  void slotPointLineSize(const QString &);
  void slotPointInteriorColor(const QString &);
  void slotPointShape(const QString &);
  void slotPointSize(const QString &);

private:
  DlgSettingsCurveProperties(QWidget *parent = 0);

  void createCurveName (QGridLayout *layout, int &row);
  void createLine (QGridLayout *layout, int &row);
  void createPoint (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  virtual void load ();

  QComboBox *m_cmbCurveName;

  QGroupBox *m_groupPoint;
  QComboBox *m_cmbPointShape;
  QComboBox *m_cmbPointSize;
  QComboBox *m_cmbPointLineSize;
  QComboBox *m_cmbPointLineColor;
  QComboBox *m_cmbPointInteriorColor;

  QGroupBox *m_groupLine;
  QComboBox *m_cmbLineSize;
  QComboBox *m_cmbLineColor;
  QComboBox *m_cmbLineType;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_SETTINGS_CURVE_PROPERTIES_H
