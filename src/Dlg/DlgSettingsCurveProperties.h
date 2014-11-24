#ifndef DLG_SETTINGS_CURVE_PROPERTIES_H
#define DLG_SETTINGS_CURVE_PROPERTIES_H

#include "DlgModelCurveProperties.h"
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
  DlgSettingsCurveProperties(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

  /// Load information for the specified curve name. When called externally, the load method must have been called first.
  void setCurveName (const QString &curveName);

private slots:
  void slotCurveName(const QString &);
  void slotLineColor(const QString &);
  void slotLineSize(const QString &);
  void slotLineType(const QString &);
  void slotPointColor(const QString &);
  void slotPointShape(const QString &);
  void slotPointSize(const QString &);

protected:
  virtual void handleOk ();

private:

  void createCurveName (QGridLayout *layout, int &row);
  void createLine (QGridLayout *layout, int &row);
  void createPoint (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);

  QComboBox *m_cmbCurveName;

  QGroupBox *m_groupPoint;
  QComboBox *m_cmbPointShape;
  QComboBox *m_cmbPointSize;
  QComboBox *m_cmbPointColor;

  QGroupBox *m_groupLine;
  QComboBox *m_cmbLineSize;
  QComboBox *m_cmbLineColor;
  QComboBox *m_cmbLineType;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DlgModelCurveProperties *m_modelCurveProperties;
};

#endif // DLG_SETTINGS_CURVE_PROPERTIES_H
