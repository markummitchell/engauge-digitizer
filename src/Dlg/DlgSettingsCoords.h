#ifndef DLG_SETTINGS_COORDS_H
#define DLG_SETTINGS_COORDS_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelCoords;
class QComboBox;
class QGridLayout;
class QGroupBox;
class QGraphicsScene;
class QGraphicsView;
class QLineEdit;
class QRadioButton;
class ViewPreview;

/// Stacked widget page for editing coordinates settings.
class DlgSettingsCoords : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCoords(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotCartesianPolar (bool);
  void slotPolarOriginRadius();
  void slotPolarUnits(const QString &);
  void slotXThetaLinear();
  void slotXThetaLog();
  void slotYRadiusLinear();
  void slotYRadiusLog();

protected:
  virtual void handleOk ();

private:

  void annotateAngles(const QFont &defaultFont);
  void annotateRadiusAtOrigin(const QFont &defaultFont);
  void createGroupCoordsType(QGridLayout *layout,
                             int &row);
  void createGroupPolar(QGridLayout *layout,
                        int &row);
  void createGroupScale(QGridLayout *layout,
                        int &row);
  void createPreview(QGridLayout *layout,
                     int &row);
  void drawCartesianLinearX();
  void drawCartesianLinearY();
  void drawCartesianLogX();
  void drawCartesianLogY();
  void drawPolarLinearRadius();
  void drawPolarLogRadius();
  void drawPolarTheta();
  void resetSceneRectangle();
  void updateControls();
  void updatePreview();

  QGroupBox *m_boxCoordsType;
  QRadioButton *m_btnCartesian;
  QRadioButton *m_btnPolar;

  QGroupBox *m_boxXTheta;
  QRadioButton *m_xThetaLinear;
  QRadioButton *m_xThetaLog;

  QGroupBox *m_boxYRadius;
  QRadioButton *m_yRadiusLinear;
  QRadioButton *m_yRadiusLog;

  QGroupBox *m_boxPolarCoords;
  QComboBox *m_cmbPolarUnits;

  QLineEdit *m_editOriginRadius;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelCoords *m_modelCoordsBefore;
  DocumentModelCoords *m_modelCoordsAfter;
};

#endif // DLG_SETTINGS_COORDS_H
