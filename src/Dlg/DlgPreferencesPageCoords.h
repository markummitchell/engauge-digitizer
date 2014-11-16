#ifndef DLG_PREFERENCES_PAGE_COORDS_H
#define DLG_PREFERENCES_PAGE_COORDS_H

#include "CoordsType.h"
#include "DlgPreferencesPageAbstractBase.h"

class QComboBox;
class QGridLayout;
class QGroupBox;
class QGraphicsScene;
class QGraphicsView;
class QLineEdit;
class QRadioButton;
class ViewPreview;

/// Stacked widget page for editing coordinates preferences.
class DlgPreferencesPageCoords : public DlgPreferencesPageAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPageCoords(CmdMediator &cmdMediator,
                           QWidget *parent = 0);

  virtual void load ();

private slots:
  void slotCartesian ();
  void slotPolar ();
  void slotPolarOriginRadius();
  void slotPolarUnits(const QString &);
  void slotXThetaLinear();
  void slotXThetaLog();
  void slotYRadiusLinear();
  void slotYRadiusLog();

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

#endif // DLG_PREFERENCES_PAGE_COORDS_H
