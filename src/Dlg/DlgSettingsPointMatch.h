#ifndef DLG_SETTINGS_POINT_MATCH_H
#define DLG_SETTINGS_POINT_MATCH_H

#include "CoordsType.h"
#include "DlgSettingsAbstractBase.h"

class DocumentModelPointMatch;
class QComboBox;
class QGraphicsPixmapItem;
class QGraphicsRectItem;
class QGraphicsScene;
class QGridLayout;
class QSpinBox;
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
  void slotMaxPointSize (int);
  void slotMinPointSeparation (int);
  void slotMouseMove (QPointF pos);
  void slotRejectedPointColor (const QString &);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  void createPreview(QGridLayout *layout,
                     int &row);
  double radiusAlongDiagonal () const;
  void updateControls();
  void updatePreview();

  QSpinBox *m_spinMinPointSeparation;
  QSpinBox *m_spinPointSize;
  QComboBox *m_cmbAcceptedPointColor;
  QComboBox *m_cmbRejectedPointColor;
  QComboBox *m_cmbCandidatePointColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
  QGraphicsRectItem *m_boxSize;

  DocumentModelPointMatch *m_modelPointMatchBefore;
  DocumentModelPointMatch *m_modelPointMatchAfter;
};

#endif // DLG_SETTINGS_POINT_MATCH_H
