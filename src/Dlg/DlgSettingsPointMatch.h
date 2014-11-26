#ifndef DLG_SETTINGS_POINT_MATCH_H
#define DLG_SETTINGS_POINT_MATCH_H

#include "CoordsType.h"
#include "DlgSettingsAbstractBase.h"

class DlgModelPointMatch;
class QComboBox;
class QDoubleValidator;
class QGridLayout;
class QGraphicsScene;
class QLineEdit;
class ViewPreview;

/// Stacked widget page for editing point match settings, for DigitizeStatePointMatch.
class DlgSettingsPointMatch : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsPointMatch(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotAcceptedPointColor (const QString &);
  void slotCandidatePointColor (const QString &);
  void slotPointSeparation (const QString &);
  void slotPointSize (const QString &);
  void slotRejectedPointColor (const QString &);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  void createPreview(QGridLayout *layout,
                     int &row);

  QLineEdit *m_editPointSeparation;
  QLineEdit *m_editPointSize;
  QComboBox *m_cmbAcceptedPointColor;
  QComboBox *m_cmbRejectedPointColor;
  QComboBox *m_cmbCandidatePointColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DlgModelPointMatch *m_modelPointMatchBefore;
  DlgModelPointMatch *m_modelPointMatchAfter;
};

#endif // DLG_SETTINGS_POINT_MATCH_H
