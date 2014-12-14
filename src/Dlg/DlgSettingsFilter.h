#ifndef DLG_SETTINGS_FILTER_H
#define DLG_SETTINGS_FILTER_H

#include "DlgSettingsAbstractBase.h"
#include "FilterParameter.h"
#include <QColor>
#include <QPixmap>

class DlgFilterThread;
class DocumentModelFilter;
class QGraphicsScene;
class QGridLayout;
class QLabel;
class QRadioButton;
class ViewPreview;
class ViewProfile;
class ViewProfileDivider;
class ViewProfileScale;

/// Stacked widget page for editing filtering settings.
class DlgSettingsFilter : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsFilter(MainWindow &mainWindow);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

public slots:
  /// Receive processed piece of preview image, to be inserted at xLeft to xLeft+pixmap.width().
  void slotTransferPiece (int xLeft,
                          QPixmap pixmap);

signals:
  /// Send filter parameters to DlgFilterThread and DlgFilterWorker for processing.
  void signalApplyFilter (FilterParameter filterParameter,
                          double low,
                          double high);

private slots:
  void slotForeground();
  void slotHue();
  void slotIntensity();
  void slotSaturation();
  void slotValue();

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void createProfileAndScale (QGridLayout *layout, int &row);
  void createThread ();

  // Apply filter parameter to pixel. Result is signed since -1 values indicate an invalid conversion. Background is used
  // for filtering by foreground
  int pixelToBin (const QColor &pixel,
                  QRgb rgbBackground);

  void updateControls();
  void updateHistogram();
  void updatePreview();

  QRadioButton *m_btnIntensity;
  QRadioButton *m_btnForeground;
  QRadioButton *m_btnHue;
  QRadioButton *m_btnSaturation;
  QRadioButton *m_btnValue;

  QGraphicsScene *m_sceneProfile;
  ViewProfile *m_viewProfile;
  ViewProfileScale *m_scale;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
  ViewProfileDivider *m_dividerLow;
  ViewProfileDivider *m_dividerHigh;

  // Apply filter parameters to preview image in a separate thread so dragging the dividers in the profile
  // will not be slowed down by the filter parameter processing
  DlgFilterThread *m_filterThread;

  DocumentModelFilter *m_modelFilterBefore;
  DocumentModelFilter *m_modelFilterAfter;
};

#endif // DLG_SETTINGS_FILTER_H
