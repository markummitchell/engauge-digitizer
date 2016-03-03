/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_CURVE_PROPERTIES_H
#define DLG_SETTINGS_CURVE_PROPERTIES_H

#include "CurveStyles.h"
#include "DlgSettingsAbstractBase.h"

class GraphicsPoint;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QGroupBox;
class QSpinBox;
class ViewPreview;

/// Dialog for editing curve properties settings.
class DlgSettingsCurveProperties : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCurveProperties(MainWindow &mainWindow);
  virtual ~DlgSettingsCurveProperties();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

  /// Load information for the specified curve name. When called externally, the load method must have been called first.
  void setCurveName (const QString &curveName);

private slots:
  void slotCurveName(const QString &);
  void slotLineColor(const QString &);
  void slotLineType(const QString &);
  void slotLineWidth(int);
  void slotPointColor(const QString &);
  void slotPointLineWidth (int);
  void slotPointRadius(int);
  void slotPointShape(const QString &);
  void slotSaveDefault();

protected:
  virtual void handleOk ();

private:

  void createCurveName (QGridLayout *layout, int &row);
  void createLine (QGridLayout *layout, int &row);
  void createPoint (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void drawLine (bool isRelation,
                 const LineStyle &lineStyle);
  void drawPoints (const PointStyle &pointStyle);
  void loadForCurveName(const QString &curveName);
  void resetSceneRectangle();
  void updateControls();
  void updatePreview();

  QComboBox *m_cmbCurveName;

  QGroupBox *m_groupPoint;
  QComboBox *m_cmbPointShape;
  QSpinBox *m_spinPointRadius;
  QSpinBox *m_spinPointLineWidth;
  QComboBox *m_cmbPointColor;

  QGroupBox *m_groupLine;
  QSpinBox *m_spinLineWidth;
  QComboBox *m_cmbLineColor;
  QComboBox *m_cmbLineType;

  QPushButton *m_btnSaveDefault;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  CurveStyles *m_modelCurveStylesBefore;
  CurveStyles *m_modelCurveStylesAfter;

  bool m_isDirty;
};

#endif // DLG_SETTINGS_CURVE_PROPERTIES_H
