#ifndef DLG_SETTINGS_DIGITIZE_CURVE_H
#define DLG_SETTINGS_DIGITIZE_CURVE_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelDigitizeCurve;
class QCheckBox;
class QGridLayout;
class QGraphicsPixmapItem;
class QGraphicsScene;
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
  void slotCursorLineLength (const QString &);
  void slotCursorLineWidth (const QString &);
  void slotCursorInnerRadius (const QString &);
  void slotCursorStandard (bool);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls();
  void updatePreview();

  QRadioButton *m_btnCursorStandard;
  QRadioButton *m_btnCursorCustom;
  QSpinBox *m_spinInnerRadius;
  QSpinBox *m_spinLineLength;
  QSpinBox *m_spinLineWidth;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelDigitizeCurve *m_modelDigitizeCurveBefore;
  DocumentModelDigitizeCurve *m_modelDigitizeCurveAfter;
};

#endif // DLG_SETTINGS_DIGITIZE_CURVE_H
