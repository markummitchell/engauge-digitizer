/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_COLOR_FILTER_H
#define DLG_SETTINGS_COLOR_FILTER_H

#include "ColorFilterMode.h"
#include "DlgSettingsAbstractBase.h"
#include <QColor>
#include <QImage>
#include <QPixmap>

class DlgFilterThread;
class DocumentModelColorFilter;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QLabel;
class QRadioButton;
class ViewPreview;
class ViewProfile;
class ViewProfileDivider;
class ViewProfileScale;

/// Dialog for editing filtering settings.
class DlgSettingsColorFilter : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsColorFilter(MainWindow &mainWindow);
  virtual ~DlgSettingsColorFilter();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);
  virtual void setSmallDialogs (bool smallDialogs);

public slots:
  /// Receive processed piece of preview image, to be inserted at xLeft to xLeft+pixmap.width().
  void slotTransferPiece (int xLeft,
                          QImage image);

signals:
  /// Send filter parameters to DlgFilterThread and DlgFilterWorker for processing.
  void signalApplyFilter (ColorFilterMode colorFilterMode,
                          double low,
                          double high);

private slots:
  void slotCurveName(const QString &curveName);
  void slotDividerHigh (double);
  void slotDividerLow (double);
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
  QRgb createThread (); // Returns background color
  void loadForCurveName();
  static int PROFILE_HEIGHT_IN_ROWS () { return 6; }
  static int PROFILE_SCENE_WIDTH () { return 100; }
  static int PROFILE_SCENE_HEIGHT () { return 100; }
  void updateHistogram();
  void updatePreview();

  QComboBox *m_cmbCurveName;

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

  QImage m_imagePreview;

  DocumentModelColorFilter *m_modelColorFilterBefore;
  DocumentModelColorFilter *m_modelColorFilterAfter;
};

#endif // DLG_SETTINGS_COLOR_FILTER_H
