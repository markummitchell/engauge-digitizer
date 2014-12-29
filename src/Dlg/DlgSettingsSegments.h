#ifndef DLG_SETTINGS_SEGMENTS_H
#define DLG_SETTINGS_SEGMENTS_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelSegments;
class QCheckBox;
class QComboBox;
class QGridLayout;
class QGraphicsScene;
class QIntValidator;
class QLineEdit;
class QSpinBox;
class ViewPreview;

/// Stacked widget page for editing Segments settings, for DigitizeStateSegment.
class DlgSettingsSegments : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsSegments(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotFillCorners (int state);
  void slotLineColor (const QString &);
  void slotLineWidth (int);
  void slotMinLength (const QString &);
  void slotPointSeparation (const QString &);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void createPreviewImage ();
  void updateControls();
  void updatePreview();

  QLineEdit *m_editMinLength;
  QIntValidator *m_validatorMinLength;
  QLineEdit *m_editPointSeparation;
  QIntValidator *m_validatorPointSeparation;
  QCheckBox *m_chkFillCorners;
  QSpinBox *m_spinLineWidth;
  QComboBox *m_cmbLineColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelSegments *m_modelSegmentsBefore;
  DocumentModelSegments *m_modelSegmentsAfter;
};

#endif // DLG_SETTINGS_SEGMENTS_H
