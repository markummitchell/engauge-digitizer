#ifndef DLG_SETTINGS_COORDS_H
#define DLG_SETTINGS_COORDS_H

#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "DlgSettingsAbstractBase.h"

class DlgValidatorAbstract;
class DocumentModelCoords;
class QComboBox;
class QDoubleValidator;
class QGridLayout;
class QGroupBox;
class QGraphicsScene;
class QGraphicsView;
class QLineEdit;
class QRadioButton;
class ViewPreview;

/// Dialog for editing coordinates settings.
class DlgSettingsCoords : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCoords(MainWindow &mainWindow);
  virtual ~DlgSettingsCoords();

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotCartesianPolar (bool);
  void slotDate (const QString &);
  void slotPolarOriginRadius(const QString &);
  void slotTime (const QString &);
  void slotUnitsXTheta(const QString &);
  void slotUnitsYRadius(const QString &);
  void slotXThetaLinear();
  void slotXThetaLog();
  void slotYRadiusLinear();
  void slotYRadiusLog();

protected:
  virtual void handleOk ();

private:

  void annotateAngles(const QFont &defaultFont);
  void annotateRadiusAtOrigin(const QFont &defaultFont);
  QRectF boundingRectGraph (CmdMediator &cmdMediator,
                            bool &isEmpty) const;
  void createDateTime(QGridLayout *layout,
                      int &row);
  void createGroupCoordsType(QGridLayout *layout,
                             int &row);
  void createGroupXTheta(QGridLayout *layout,
                        int &row);
  void createGroupYRadius(QGridLayout *layout,
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
  void loadComboBoxDate();
  void loadComboBoxTime();
  void loadComboBoxUnitsNonPolar (QComboBox &cmb,
                                  CoordUnitsNonPolarTheta coordUnits);
  void loadComboBoxUnitsPolar (QComboBox &cmb,
                               CoordUnitsPolarTheta coordUnits);
  void resetSceneRectangle();
  void updateControls();
  void updatePreview();

  QGroupBox *m_boxCoordsType;
  QRadioButton *m_btnCartesian;
  QRadioButton *m_btnPolar;

  QGroupBox *m_boxXTheta;
  QRadioButton *m_xThetaLinear;
  QRadioButton *m_xThetaLog;
  QComboBox *m_cmbXThetaUnits;

  QGroupBox *m_boxYRadius;
  QRadioButton *m_yRadiusLinear;
  QRadioButton *m_yRadiusLog;
  QComboBox *m_cmbYRadiusUnits;
  QLineEdit *m_editOriginRadius;
  DlgValidatorAbstract *m_validatorOriginRadius;

  QComboBox *m_cmbDate;
  QComboBox *m_cmbTime;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelCoords *m_modelCoordsBefore;
  DocumentModelCoords *m_modelCoordsAfter;
};

#endif // DLG_SETTINGS_COORDS_H
