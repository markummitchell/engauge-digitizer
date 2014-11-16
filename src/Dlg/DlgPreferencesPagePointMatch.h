#ifndef DLG_PREFERENCES_PAGE_POINT_MATCH_H
#define DLG_PREFERENCES_PAGE_POINT_MATCH_H

#include "CoordsType.h"
#include "DlgPreferencesPageAbstractBase.h"

class QComboBox;
class QDoubleValidator;
class QGridLayout;
class QGraphicsScene;
class QLineEdit;
class ViewPreview;

/// Stacked widget page for editing point match preferences, for DigitizeStatePointMatch.
class DlgPreferencesPagePointMatch : public DlgPreferencesPageAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPagePointMatch(CmdMediator &cmdMediator,
                               QWidget *parent = 0);

  virtual void load ();

private slots:
  void slotAcceptedPointColor (const QString &);
  void slotCandidatePointColor (const QString &);
  void slotPointSeparation (const QString &);
  void slotPointSize (const QString &);
  void slotRejectedPointColor (const QString &);

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
};

#endif // DLG_PREFERENCES_PAGE_POINT_MATCH_H
