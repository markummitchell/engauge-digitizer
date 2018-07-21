/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsColorFilter.h"
#include "ColorFilter.h"
#include "ColorFilterHistogram.h"
#include "ColorConstants.h"
#include "DlgFilterThread.h"
#include "DlgSettingsColorFilter.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <qmath.h>
#include <QPixmap>
#include <QRadioButton>
#include <QRgb>
#include "ViewPreview.h"
#include "ViewProfile.h"
#include "ViewProfileDivider.h"
#include "ViewProfileScale.h"

const int MINIMUM_DIALOG_WIDTH_COLOR_FILTER = 640;
const int MINIMUM_HEIGHT = 500;

DlgSettingsColorFilter::DlgSettingsColorFilter(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Color Filter"),
                           "DlgSettingsColorFilter",
                           mainWindow),
  m_scenePreview (0),
  m_viewPreview (0),
  m_filterThread (0),
  m_modelColorFilterBefore (0),
  m_modelColorFilterAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::DlgSettingsColorFilter";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel,
               MINIMUM_DIALOG_WIDTH_COLOR_FILTER);
}

DlgSettingsColorFilter::~DlgSettingsColorFilter()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::~DlgSettingsColorFilter";
}

void DlgSettingsColorFilter::createControls (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::createControls";

  QLabel *labelCurve = new QLabel (tr ("Curve Name:"));
  layout->addWidget (labelCurve, row++, 1);

  m_cmbCurveName = new QComboBox ();
  m_cmbCurveName->setWhatsThis (tr ("Name of the curve that is currently selected for editing"));
  connect (m_cmbCurveName, SIGNAL (activated (const QString &)), this, SLOT (slotCurveName (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbCurveName, row++, 1);

  QLabel *labelProfile = new QLabel (tr ("Filter mode:"));
  layout->addWidget (labelProfile, row++, 1);

  m_btnIntensity = new QRadioButton (colorFilterModeToString (COLOR_FILTER_MODE_INTENSITY));
  m_btnIntensity->setWhatsThis (tr ("Filter the original image into black and white pixels using the Intensity parameter, "
                                    "to hide unimportant information and emphasize important information.\n\n"
                                    "The Intensity value of a pixel is computed from the red, green "
                                    "and blue components as I = squareroot (R * R + G * G + B * B)"));
  connect (m_btnIntensity, SIGNAL (released ()), this, SLOT (slotIntensity ()));
  layout->addWidget (m_btnIntensity, row++, 1);

  m_btnForeground = new QRadioButton (colorFilterModeToString (COLOR_FILTER_MODE_FOREGROUND));
  m_btnForeground->setWhatsThis (tr ("Filter the original image into black and white pixels by isolating the foreground from the background, "
                                     "to hide unimportant information and emphasize important information.\n\n"
                                     "The background color is shown on the left side of the scale bar.\n\n"
                                     "The distance of any color (R, G, B) from the background color (Rb, Gb, Bb) is computed as "
                                     "F = squareroot ((R - Rb) * (R - Rb) + (G - Gb) * (G - Gb) + (B - Bb)). On the left end of the "
                                     "scale, the foreground distance value is zero, and it increases linearly to the maximum on the far right."));
  connect (m_btnForeground, SIGNAL (released ()), this, SLOT (slotForeground ()));
  layout->addWidget (m_btnForeground, row++, 1);

  m_btnHue = new QRadioButton (colorFilterModeToString (COLOR_FILTER_MODE_HUE));
  m_btnHue->setWhatsThis (tr ("Filter the original image into black and white pixels using the Hue component of the "
                              "Hue, Saturation and Value (HSV) color components, "
                              "to hide unimportant information and emphasize important information."));
  connect (m_btnHue, SIGNAL (released ()), this, SLOT (slotHue ()));
  layout->addWidget (m_btnHue, row++, 1);

  m_btnSaturation = new QRadioButton (colorFilterModeToString (COLOR_FILTER_MODE_SATURATION));
  m_btnSaturation->setWhatsThis (tr ("Filter the original image into black and white pixels using the Saturation component of the "
                                     "Hue, Saturation and Value (HSV) color components, "
                                     "to hide unimportant information and emphasize important information."));
  connect (m_btnSaturation, SIGNAL (released ()), this, SLOT (slotSaturation ()));
  layout->addWidget (m_btnSaturation, row++, 1);

  m_btnValue = new QRadioButton (colorFilterModeToString (COLOR_FILTER_MODE_VALUE));
  m_btnValue->setWhatsThis (tr ("Filter the original image into black and white pixels using the Value component of the "
                                "Hue, Saturation and Value (HSV) color components, "
                                "to hide unimportant information and emphasize important information.\n\n"
                                "The Value component is also called the Lightness."));
  connect (m_btnValue, SIGNAL (released ()), this, SLOT (slotValue ()));
  layout->addWidget (m_btnValue, row++, 1);
}

void DlgSettingsColorFilter::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsColorFilter::createPreview (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 5);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the filtering of the original image."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  m_viewPreview->setRenderHint(QPainter::Antialiasing);

  layout->addWidget (m_viewPreview, row++, 0, 1, 5);
}

void DlgSettingsColorFilter::createProfileAndScale (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::createProfileAndScale";

  const int MINIMUM_VIEW_PROFILE_WIDTH = 70;

  QLabel *labelProfile = new QLabel (tr ("Filter Parameter Histogram Profile"));
  layout->addWidget (labelProfile, row++, 3);

  m_sceneProfile = new QGraphicsScene;
  m_sceneProfile->setSceneRect(0, 0, PROFILE_SCENE_WIDTH (), PROFILE_SCENE_HEIGHT ());

  m_viewProfile = new ViewProfile (m_sceneProfile,
                                   MINIMUM_VIEW_PROFILE_WIDTH);
  m_viewProfile->setWhatsThis (tr ("Histogram profile of the selected filter parameter. The two Dividers can be moved back and forth to adjust "
                                   "the range of filter parameter values that will be included in the filtered image. The clear portion will "
                                   "be included, and the shaded portion will be excluded."));
  layout->addWidget (m_viewProfile, row, 3, PROFILE_HEIGHT_IN_ROWS (), 1);
  row += PROFILE_HEIGHT_IN_ROWS ();

  m_scale = new ViewProfileScale (MINIMUM_VIEW_PROFILE_WIDTH);
  m_scale->setWhatsThis (tr ("This read-only box displays a graphical representation of the horizontal axis in the histogram profile above."));
  m_scale->setAutoFillBackground(true);
  layout->addWidget (m_scale, row++, 3, 1, 1);
}

QWidget *DlgSettingsColorFilter::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::createSubPanel";

  const int EMPTY_COLUMN_WIDTH = 40;

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 0); // Empty column
  layout->setColumnMinimumWidth(0, EMPTY_COLUMN_WIDTH);
  layout->setColumnStretch(1, 0); // Radio buttons
  layout->setColumnMinimumWidth(1, 210);
  layout->setColumnStretch(2, 0); // Empty column to put some space between previous and next columns, so they are not too close
  layout->setColumnMinimumWidth(2, 15);
  layout->setColumnStretch(3, 1); // Profile
  layout->setColumnMinimumWidth(4, EMPTY_COLUMN_WIDTH); // Empty column
  layout->setColumnStretch(4, 0);

  int rowLeft = 0, rowRight = 0;
  createControls (layout, rowLeft);
  createProfileAndScale (layout, rowRight);

  int row = qMax (rowLeft, rowRight);
  createPreview (layout, row);

  return subPanel;
}

QRgb DlgSettingsColorFilter::createThread ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::createThread";

  // Get background color
  QImage image = cmdMediator().document().pixmap().toImage();
  ColorFilter filter;
  QRgb rgbBackground = filter.marginColor(&image);

  // Only create thread once
  if (m_filterThread == 0) {

    m_filterThread = new DlgFilterThread (cmdMediator().document().pixmap(),
                                          rgbBackground,
                                          *this);
    m_filterThread->start(); // Now that thread is started, we can use signalApplyFilter
  }

  return rgbBackground;
}

void DlgSettingsColorFilter::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::handleOk";

  CmdSettingsColorFilter *cmd = new CmdSettingsColorFilter (mainWindow (),
                                                            cmdMediator ().document(),
                                                            *m_modelColorFilterBefore,
                                                            *m_modelColorFilterAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsColorFilter::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelColorFilterBefore != 0) {
    delete m_modelColorFilterBefore;
  }
  if (m_modelColorFilterAfter != 0) {
    delete m_modelColorFilterAfter;
  }

  // Save new data
  m_modelColorFilterBefore = new DocumentModelColorFilter (cmdMediator.document().modelColorFilter());
  m_modelColorFilterAfter = new DocumentModelColorFilter (cmdMediator.document().modelColorFilter());

  // Populate controls. First load curve name combobox. The curve-specific controls get loaded in slotCurveName
  m_cmbCurveName->clear ();
  m_cmbCurveName->addItem (AXIS_CURVE_NAME);
  QStringList curveNames = cmdMediator.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {

    QString curveName = *itr;
    m_cmbCurveName->addItem (curveName);
  }

  // This sets the curve name
  m_cmbCurveName->setCurrentText (mainWindow().selectedGraphCurve());
  loadForCurveName();

  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsColorFilter::loadForCurveName()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::loadForCurveName";

  // Get curve name from control
  QString curveName = m_cmbCurveName->currentText();

  // Skip if everything is not set up yet
  if (!curveName.isEmpty () && m_modelColorFilterAfter != 0) {

    // Populate controls
    ColorFilterMode colorFilterMode = m_modelColorFilterAfter->colorFilterMode(curveName);
    m_btnIntensity->setChecked (colorFilterMode == COLOR_FILTER_MODE_INTENSITY);
    m_btnForeground->setChecked (colorFilterMode == COLOR_FILTER_MODE_FOREGROUND);
    m_btnHue->setChecked (colorFilterMode == COLOR_FILTER_MODE_HUE);
    m_btnSaturation->setChecked (colorFilterMode == COLOR_FILTER_MODE_SATURATION);
    m_btnValue->setChecked (colorFilterMode == COLOR_FILTER_MODE_VALUE);

    m_scenePreview->clear();
    m_imagePreview = cmdMediator().document().pixmap().toImage();
    m_scenePreview->addPixmap (QPixmap::fromImage (m_imagePreview));

    QRgb rgbBackground = createThread ();
    m_scale->setBackgroundColor (rgbBackground);
    createThread ();
    updateHistogram();
    updatePreview(); // Needs thread initialized
  }
}

void DlgSettingsColorFilter::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsColorFilter::slotCurveName(const QString & /* curveName */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::slotCurveName";

  loadForCurveName ();
}

void DlgSettingsColorFilter::slotDividerHigh (double xCenter)
{
  m_modelColorFilterAfter->setHigh (m_cmbCurveName->currentText(),
                                    xCenter / (double) PROFILE_SCENE_WIDTH ());
  updatePreview();
}

void DlgSettingsColorFilter::slotDividerLow (double xCenter)
{
  m_modelColorFilterAfter->setLow (m_cmbCurveName->currentText(),
                                   xCenter / (double) PROFILE_SCENE_WIDTH ());
  updatePreview();
}

void DlgSettingsColorFilter::slotForeground ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::slotForeground";

  m_modelColorFilterAfter->setColorFilterMode(m_cmbCurveName->currentText(),
                                              COLOR_FILTER_MODE_FOREGROUND);
  updateHistogram();
  updatePreview();
}

void DlgSettingsColorFilter::slotHue ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::slotHue";

  m_modelColorFilterAfter->setColorFilterMode(m_cmbCurveName->currentText(),
                                              COLOR_FILTER_MODE_HUE);
  updateHistogram();
  updatePreview();
}

void DlgSettingsColorFilter::slotIntensity ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::slotIntensity";

  m_modelColorFilterAfter->setColorFilterMode(m_cmbCurveName->currentText(),
                                              COLOR_FILTER_MODE_INTENSITY);
  updateHistogram();
  updatePreview();
}

void DlgSettingsColorFilter::slotSaturation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::slotSaturation";

  m_modelColorFilterAfter->setColorFilterMode(m_cmbCurveName->currentText(),
                                              COLOR_FILTER_MODE_SATURATION);
  updateHistogram();
  updatePreview();
}

void DlgSettingsColorFilter::slotTransferPiece (int xLeft,
                                                QImage image)
{
  // Overwrite one piece of the processed image. This approach is a bit slow because the entire QPixmap
  // in the QGraphicsScene gets exchanged as part of each update, but that seems to be the only possible
  // approach when using QGraphicsScene. If not fast enough or there is ugly flicker, we may replace
  // QGraphicsScene by a simple QWidget and override the paint function - but that approach may get
  // complicated when resizing the QGraphicsView
  for (int xFrom = 0, xTo = xLeft; xFrom < image.width(); xFrom++, xTo++) {
    for (int y = 0; y < image.height (); y++) {

      QColor pixel = image.pixel (xFrom, y);
      m_imagePreview.setPixel (xTo, y, pixel.rgb());
    }
  }

  // Remove old pixmap
  QGraphicsItem *itemPixmap = m_scenePreview->items().at(0);
  m_scenePreview->removeItem (itemPixmap);
  delete itemPixmap;

  // Save new pixmap. Only visible change should be the area covered by the pixels in image
  m_scenePreview->addPixmap (QPixmap::fromImage (m_imagePreview));
}

void DlgSettingsColorFilter::slotValue ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::slotValue";

  m_modelColorFilterAfter->setColorFilterMode(m_cmbCurveName->currentText(),
                                         COLOR_FILTER_MODE_VALUE);
  updateHistogram();
  updatePreview();
}

void DlgSettingsColorFilter::updateHistogram()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsColorFilter::updateHistogram";

  enableOk (true);

  const double PEN_WIDTH = 0.0; // Zero value gives one-pixel width at all scales

  QString curveName = m_cmbCurveName->currentText();

  m_sceneProfile->clear();

  m_scale->setColorFilterMode (m_modelColorFilterAfter->colorFilterMode(curveName));

  // Start with original image
  QImage image = cmdMediator().document().pixmap().toImage();

  double *histogramBins = new double [ColorFilterHistogram::HISTOGRAM_BINS ()];

  ColorFilter filter;
  ColorFilterHistogram filterHistogram;
  int maxBinCount;
  filterHistogram.generate (filter,
                            histogramBins,
                            m_modelColorFilterAfter->colorFilterMode (curveName),
                            image,
                            maxBinCount);

  // Draw histogram, normalizing so highest peak exactly fills the vertical range. Log scale is used
  // so smaller peaks do not disappear
  double logMaxBinCount = qLn (maxBinCount);
  if (logMaxBinCount != 0) { // Will not have divide by zero from logMaxBinCount below
    for (int bin = 1; bin < ColorFilterHistogram::HISTOGRAM_BINS (); bin++) {

      double x0 = PROFILE_SCENE_WIDTH () * (bin - 1.0) / (ColorFilterHistogram::HISTOGRAM_BINS () - 1.0);

      // Map logPixelCount through 0 to 0 through PROFILE_SCENE_HEIGHT-1, using log scale
      double count0 = 1.0 + histogramBins [bin - 1];
      double y0 = (PROFILE_SCENE_HEIGHT () - 1.0) * (1.0 - qLn (count0) / logMaxBinCount);

      double x1 = PROFILE_SCENE_WIDTH () * (bin - 0.0) / (ColorFilterHistogram::HISTOGRAM_BINS () - 1.0);

      // Map logPixelCount through 0 to 0 through PROFILE_SCENE_HEIGHT-1, using log scale
      double count1 = 1.0 + histogramBins [bin];
      double y1 = (PROFILE_SCENE_HEIGHT () - 1.0) * (1.0 - qLn (count1) / logMaxBinCount);

      QGraphicsLineItem *line = new QGraphicsLineItem (x0, y0, x1, y1);
      line->setPen (QPen (QBrush (Qt::black), PEN_WIDTH));
      m_sceneProfile->addItem (line);
    }
  }

  // Create low and high dividers
  m_dividerLow = new ViewProfileDivider(*m_sceneProfile,
                                        *m_viewProfile,
                                        PROFILE_SCENE_WIDTH (),
                                        PROFILE_SCENE_HEIGHT (),
                                        PROFILE_SCENE_HEIGHT () * 2.0 / 3.0,
                                        true);
  m_dividerHigh = new ViewProfileDivider(*m_sceneProfile,
                                         *m_viewProfile,
                                         PROFILE_SCENE_HEIGHT (),
                                         PROFILE_SCENE_WIDTH (),
                                         PROFILE_SCENE_HEIGHT () / 3.0,
                                         false);

  // Connect the dividers to each other since the shaded areas depend on both divides when low divider is
  // moved to the right of the high divider
  connect (m_dividerLow, SIGNAL (signalMovedLow (double)), m_dividerHigh, SLOT (slotOtherMoved(double)));
  connect (m_dividerHigh, SIGNAL (signalMovedHigh (double)), m_dividerLow, SLOT (slotOtherMoved(double)));

  // Update preview when the dividers move
  connect (m_dividerLow, SIGNAL (signalMovedLow (double)), this, SLOT (slotDividerLow (double)));
  connect (m_dividerHigh, SIGNAL(signalMovedHigh (double)), this, SLOT (slotDividerHigh (double)));

  if (m_btnForeground->isChecked()) {

    // Foreground
    m_dividerLow->setX (m_modelColorFilterAfter->foregroundLow(curveName), FOREGROUND_MIN, FOREGROUND_MAX);
    m_dividerHigh->setX (m_modelColorFilterAfter->foregroundHigh(curveName), FOREGROUND_MIN, FOREGROUND_MAX);

  } else if (m_btnIntensity->isChecked()) {

    // Intensity
    m_dividerLow->setX (m_modelColorFilterAfter->intensityLow(curveName), INTENSITY_MIN, INTENSITY_MAX);
    m_dividerHigh->setX (m_modelColorFilterAfter->intensityHigh(curveName), INTENSITY_MIN, INTENSITY_MAX);

  } else if (m_btnHue->isChecked()) {

    // Hue
    m_dividerLow->setX (m_modelColorFilterAfter->hueLow(curveName), HUE_MIN, HUE_MAX);
    m_dividerHigh->setX (m_modelColorFilterAfter->hueHigh(curveName), HUE_MIN, HUE_MAX);

  } else if (m_btnSaturation->isChecked()) {

    // Saturation
    m_dividerLow->setX (m_modelColorFilterAfter->saturationLow(curveName), SATURATION_MIN, SATURATION_MAX);
    m_dividerHigh->setX (m_modelColorFilterAfter->saturationHigh(curveName), SATURATION_MIN, SATURATION_MAX);

  } else if (m_btnValue->isChecked()) {

    // Value
    m_dividerLow->setX (m_modelColorFilterAfter->valueLow(curveName), VALUE_MIN, VALUE_MAX);
    m_dividerHigh->setX (m_modelColorFilterAfter->valueHigh(curveName), VALUE_MIN, VALUE_MAX);

  } else {

    ENGAUGE_ASSERT (false);

  }

  free (histogramBins);
}

void DlgSettingsColorFilter::updatePreview ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettings::updatePreview";

  enableOk (true);

  // This (indirectly) updates the preview
  QString curveName = m_cmbCurveName->currentText();
  emit signalApplyFilter (m_modelColorFilterAfter->colorFilterMode(curveName),
                          m_modelColorFilterAfter->low(curveName),
                          m_modelColorFilterAfter->high(curveName));
}
