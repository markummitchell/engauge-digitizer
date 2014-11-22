#ifndef DLG_SETTINGS_COORDS_H
#define DLG_SETTINGS_COORDS_H

#include "CoordsType.h"
#include "DlgSettingsAbstractBase.h"

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
  void slotCartesian ();
  void slotPolar ();
  void slotPolarOriginRadius();
  void slotPolarUnits(const QString &);
  void slotXThetaLinear();
  void slotXThetaLog();
  void slotYRadiusLinear();
  void slotYRadiusLog();

protected:
  virtual void handleOk ();

private:

  void createGroupCoordsType(QGridLayout *layout,
                             int &row);
  void createGroupPolar(QGridLayout *layout,
                        int &row);
  void createGroupScale(QGridLayout *layout,
                        int &row);
  void createPreview(QGridLayout *layout,
                     int &row);
  void initializeGroupCoordsType();
  void loadPixmap (const QString &image);
  void updateControls();

  QGroupBox *m_boxCoordsType;
  CoordsType m_coordsType;
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
};

#endif // DLG_SETTINGS_COORDS_H
