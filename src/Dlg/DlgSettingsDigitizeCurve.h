#ifndef DLG_SETTINGS_DIGITIZE_CURVE_H
#define DLG_SETTINGS_DIGITIZE_CURVE_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelDigitizeCurve;
class QCheckBox;
class QComboBox;
class QGridLayout;
class QGraphicsPixmapItem;
class QGraphicsScene;
class QGroupBox;
class QRadioButton;
class QSpinBox;
class ViewPreview;

/// Dialog for editing DigitizeStateCurve settings. The preview window would should the selected
/// cursor in the center, but there is no way to access the image of Qt::CrossCursor (QCursor::pixmap
/// only works for custom cursors that were defined by a QPixmap)
class DlgSettingsDigitizeCurve : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsDigitizeCurve(MainWindow &mainWindow);
  virtual ~DlgSettingsDigitizeCurve();

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotCursorCustom (bool);
  void slotCursorInnerRadius (const QString &);
  void slotCursorLineWidth (const QString &);
  void slotCursorSize (const QString &);
  void slotCursorStandard (bool);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls();
  void updatePreview();

  QGroupBox *m_boxCursor;
  QRadioButton *m_btnStandard;
  QRadioButton *m_btnCustom;
  QComboBox *m_cmbSize;
  QSpinBox *m_spinInnerRadius;
  QSpinBox *m_spinLineWidth;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelDigitizeCurve *m_modelDigitizeCurveBefore;
  DocumentModelDigitizeCurve *m_modelDigitizeCurveAfter;
};

#endif // DLG_SETTINGS_DIGITIZE_CURVE_H
