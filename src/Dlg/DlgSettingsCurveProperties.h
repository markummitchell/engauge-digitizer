#ifndef DLG_SETTINGS_CURVE_PROPERTIES_H
#define DLG_SETTINGS_CURVE_PROPERTIES_H

#include "DocumentModelCurveProperties.h"
#include "DlgSettingsAbstractBase.h"

class DlgSpinBoxDouble;
class DlgSpinBoxInt;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QGroupBox;
class ViewPreview;

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
  void slotLineType(const QString &);
  void slotLineWidth(const QString &);
  void slotPointColor(const QString &);
  void slotPointLineWidth (const QString &);
  void slotPointRadius(const QString &);
  void slotPointShape(const QString &);

protected:
  virtual void handleOk ();

private:

  void createCurveName (QGridLayout *layout, int &row);
  void createLine (QGridLayout *layout, int &row);
  void createPoint (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void loadForCurveName(const QString &curveName);
  void resetSceneRectangle();
  void updateControls();
  void updatePreview();

  QComboBox *m_cmbCurveName;

  QGroupBox *m_groupPoint;
  QComboBox *m_cmbPointShape;
  DlgSpinBoxInt *m_spinPointRadius;
  DlgSpinBoxDouble *m_spinPointLineWidth;
  QComboBox *m_cmbPointColor;

  QGroupBox *m_groupLine;
  DlgSpinBoxInt *m_spinLineWidth;
  QComboBox *m_cmbLineColor;
  QComboBox *m_cmbLineType;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelCurveProperties *m_modelCurvePropertiesBefore;
  DocumentModelCurveProperties *m_modelCurvePropertiesAfter;
};

#endif // DLG_SETTINGS_CURVE_PROPERTIES_H
