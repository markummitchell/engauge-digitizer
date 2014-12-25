#ifndef DLG_SETTINGS_POINT_MATCH_H
#define DLG_SETTINGS_POINT_MATCH_H

#include "CoordsType.h"
#include "DlgSettingsAbstractBase.h"

class DocumentModelPointMatch;
class QComboBox;
class QDoubleValidator;
class QIntValidator;
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
  void updateControls();
  void updatePreview();

  QLineEdit *m_editPointSeparation;
  QIntValidator *m_validatorPointSeparation;
  QLineEdit *m_editPointSize;
  QIntValidator *m_validatorPointSize;
  QComboBox *m_cmbAcceptedPointColor;
  QComboBox *m_cmbRejectedPointColor;
  QComboBox *m_cmbCandidatePointColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelPointMatch *m_modelPointMatchBefore;
  DocumentModelPointMatch *m_modelPointMatchAfter;
};

#endif // DLG_SETTINGS_POINT_MATCH_H
