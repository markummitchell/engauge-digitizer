#ifndef DLG_PREFERENCES_PAGE_SEGMENTS_H
#define DLG_PREFERENCES_PAGE_SEGMENTS_H

#include <QWidget>

class CmdMediator;
class QCheckBox;
class QComboBox;
class QGridLayout;
class QGraphicsScene;
class QLineEdit;
class ViewPreview;

/// Stacked widget page for editing Segments preferences, for DigitizeStateSegment.
class DlgPreferencesPageSegments : public QWidget
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPageSegments(CmdMediator &cmdMediator,
                             QWidget *parent = 0);

private slots:
  void slotFillCorners (int state);
  void slotLineColor (const QString &);
  void slotLineSize (const QString &);
  void slotMinLength (const QString &);
  void slotPointSeparation (const QString &);

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);

  QLineEdit *m_editMinLength;
  QLineEdit *m_editPointSeparation;
  QCheckBox *m_chkFillCorners;
  QComboBox *m_cmbLineSize;
  QComboBox *m_cmbLineColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_PREFERENCES_PAGE_SEGMENTS_H
