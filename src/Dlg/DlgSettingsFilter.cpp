#include "CmdMediator.h"
#include "CmdSettingsFilter.h"
#include "DlgFilterThread.h"
#include "DlgSettingsFilter.h"
#include "Filter.h"
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

const int PROFILE_HEIGHT_IN_ROWS = 6;
const int HISTOGRAM_BINS = 70;
const int PROFILE_SCENE_WIDTH = 100;
const int PROFILE_SCENE_HEIGHT = 100;

DlgSettingsFilter::DlgSettingsFilter(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Filter", mainWindow),
  m_modelFilterBefore (0),
  m_modelFilterAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsFilter::createControls (QGridLayout *layout, int &row)
{
  QLabel *labelProfile = new QLabel ("Filter parameter:");
  layout->addWidget (labelProfile, row++, 1);

  m_btnIntensity = new QRadioButton ("Intensity");
  m_btnIntensity->setWhatsThis (tr ("Filter the original image into black and white pixels using the Intensity parameter, "
                                    "to hide unimportant information and emphasize important information.\n\n"
                                    "The Intensity value of a pixel is computed from the red, green "
                                    "and blue components as I = squareroot (R * R + G * G + B * B)"));
  connect (m_btnIntensity, SIGNAL (released ()), this, SLOT (slotIntensity ()));
  layout->addWidget (m_btnIntensity, row++, 1);

  m_btnForeground = new QRadioButton ("Foreground");
  m_btnForeground->setWhatsThis (tr ("Filter the original image into black and white pixels by isolating the foreground from the background, "
                                     "to hide unimportant information and emphasize important information.\n\n"
                                     "The background color is shown on the left side of the scale bar.\n\n"
                                     "The distance of any color (R, G, B) from the background color (Rb, Gb, Bb) is computed as "
                                     "F = squareroot ((R - Rb) * (R - Rb) + (G - Gb) * (G - Gb) + (B - Bb)). On the left end of the "
                                     "scale, the foreground distance value is zero, and it increases linearly to the maximum on the far right."));
  connect (m_btnForeground, SIGNAL (released ()), this, SLOT (slotForeground ()));
  layout->addWidget (m_btnForeground, row++, 1);

  m_btnHue = new QRadioButton ("Hue");
  m_btnHue->setWhatsThis (tr ("Filter the original image into black and white pixels using the Hue component of the "
                              "Hue, Saturation and Value (HSV) color components, "
                              "to hide unimportant information and emphasize important information."));
  connect (m_btnHue, SIGNAL (released ()), this, SLOT (slotHue ()));
  layout->addWidget (m_btnHue, row++, 1);

  m_btnSaturation = new QRadioButton ("Saturation");
  m_btnSaturation->setWhatsThis (tr ("Filter the original image into black and white pixels using the Saturation component of the "
                                     "Hue, Saturation and Value (HSV) color components, "
                                     "to hide unimportant information and emphasize important information."));
  connect (m_btnSaturation, SIGNAL (released ()), this, SLOT (slotSaturation ()));
  layout->addWidget (m_btnSaturation, row++, 1);

  m_btnValue = new QRadioButton ("Value");
  m_btnValue->setWhatsThis (tr ("Filter the original image into black and white pixels using the Value component of the "
                                "Hue, Saturation and Value (HSV) color components, "
                                "to hide unimportant information and emphasize important information.\n\n"
                                "The Value component is also called the Lightness."));
  connect (m_btnValue, SIGNAL (released ()), this, SLOT (slotValue ()));
  layout->addWidget (m_btnValue, row++, 1);
}

void DlgSettingsFilter::createPreview (QGridLayout *layout, int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 5);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the filtering of the original image."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  m_viewPreview->setRenderHint(QPainter::Antialiasing);

  layout->addWidget (m_viewPreview, row++, 0, 1, 5);
}

void DlgSettingsFilter::createProfileAndScale (QGridLayout *layout, int &row)
{
  QLabel *labelProfile = new QLabel ("Filter Parameter Histogram Profile");
  layout->addWidget (labelProfile, row++, 3);

  m_sceneProfile = new QGraphicsScene;
  m_sceneProfile->setSceneRect(0, 0, PROFILE_SCENE_WIDTH, PROFILE_SCENE_HEIGHT);

  m_viewProfile = new ViewProfile (m_sceneProfile);
  m_viewProfile->setWhatsThis (tr ("Histogram profile of the selected filter parameter. The two Dividers can be moved back and forth to adjust "
                                   "the range of filter parameter values that will be included in the filtered image. The clear portion will "
                                   "be included, and the shaded portion will be excluded."));

  layout->addWidget (m_viewProfile, row, 3, PROFILE_HEIGHT_IN_ROWS, 1);
  row += PROFILE_HEIGHT_IN_ROWS;

  m_scale = new ViewProfileScale;
  m_scale->setWhatsThis (tr ("This read-only box displays a graphical representation of the horizontal axis in the histogram profile above."));
  m_scale->setAutoFillBackground(true);
  layout->addWidget (m_scale, row++, 3);
}

QWidget *DlgSettingsFilter::createSubPanel ()
{
  const int EMPTY_COLUMN_WIDTH = 40;

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 0); // Empty column
  layout->setColumnMinimumWidth(0, EMPTY_COLUMN_WIDTH);
  layout->setColumnStretch(1, 0); // Radio buttons
  layout->setColumnStretch(2, 0); // Empty column to put some space between previous and next columns, so they are not too close
  layout->setColumnMinimumWidth(2, 15);
  layout->setColumnStretch(3, 1); // Profile
  layout->setColumnMinimumWidth(4, EMPTY_COLUMN_WIDTH); // Empty column

  int rowLeft = 0, rowRight = 0;
  createControls (layout, rowLeft);
  createProfileAndScale (layout, rowRight);

  int row = qMax (rowLeft, rowRight);
  createPreview (layout, row);

  return subPanel;
}

QRgb DlgSettingsFilter::createThread ()
{
  // Get background color
  QImage image = cmdMediator().document().pixmap().toImage();
  Filter filter;
  QRgb rgbBackground = filter.marginColor(&image);

  m_filterThread = new DlgFilterThread (cmdMediator().document().pixmap(),
                                        rgbBackground,
                                        *this);
  m_filterThread->start(); // Now that thread is started, we can use signalApplyFilter

  return rgbBackground;
}

void DlgSettingsFilter::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::handleOk";

  CmdSettingsFilter *cmd = new CmdSettingsFilter (mainWindow (),
                                                  cmdMediator ().document(),
                                                  *m_modelFilterBefore,
                                                  *m_modelFilterAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsFilter::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::load";

  setCmdMediator (cmdMediator);

  m_modelFilterBefore = new DocumentModelFilter (cmdMediator.document());
  m_modelFilterAfter = new DocumentModelFilter (cmdMediator.document());

  FilterParameter filterParameter = m_modelFilterAfter->filterParameter();
  m_btnIntensity->setChecked (filterParameter == FILTER_PARAMETER_INTENSITY);
  m_btnForeground->setChecked (filterParameter == FILTER_PARAMETER_FOREGROUND);
  m_btnHue->setChecked (filterParameter == FILTER_PARAMETER_HUE);
  m_btnSaturation->setChecked (filterParameter == FILTER_PARAMETER_SATURATION);
  m_btnValue->setChecked (filterParameter == FILTER_PARAMETER_VALUE);

  m_scenePreview->clear();
  m_imagePreview = cmdMediator.document().pixmap().toImage();
  m_scenePreview->addPixmap (QPixmap::fromImage (m_imagePreview));

  QRgb rgbBackground = createThread ();
  m_scale->setBackgroundColor (rgbBackground);
  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  createThread ();
  updatePreview(); // Needs thread initialized
}

void DlgSettingsFilter::slotDividerHigh (double xCenter)
{
  m_modelFilterAfter->setHigh (xCenter / (double) PROFILE_SCENE_WIDTH);
}

void DlgSettingsFilter::slotDividerLow (double xCenter)
{
  m_modelFilterAfter->setLow (xCenter / (double) PROFILE_SCENE_WIDTH);
}

void DlgSettingsFilter::slotForeground ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::slotForeground";

  m_modelFilterAfter->setFilterParameter(FILTER_PARAMETER_FOREGROUND);
  updateControls();
  updatePreview();
}

void DlgSettingsFilter::slotHue ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::slotHue";

  m_modelFilterAfter->setFilterParameter(FILTER_PARAMETER_HUE);
  updateControls();
  updatePreview();
}

void DlgSettingsFilter::slotIntensity ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::slotIntensity";

  m_modelFilterAfter->setFilterParameter(FILTER_PARAMETER_INTENSITY);
  updateControls();
  updatePreview();
}

void DlgSettingsFilter::slotSaturation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::slotSaturation";

  m_modelFilterAfter->setFilterParameter(FILTER_PARAMETER_SATURATION);
  updateControls();
  updatePreview();
}

void DlgSettingsFilter::slotTransferPiece (int xLeft,
                                           QImage image)
{
  // Overwrite one piece of the processed image. This approach is a bit slow because the entire QPixmap
  // in the QGraphicsScene gets exchanged as part of each update, but that seems to be the only possible
  // approach when using QGraphicsScene. If not fast enough or there is ugly flicker, we may replace
  // QGraphicsScene by a simple QWidget and override the paint function - but that approach may get
  // complicated when resizing the QGraphicsView
  qDebug() << "shit " << m_imagePreview.width() << " " << m_imagePreview.height() << " " << xLeft
              << image.width() << " " << image.height();

  int xStop = xLeft + image.width ();
  for (int xFrom = 0, xTo = xLeft; xFrom < image.width(); xFrom++, xTo++) {
    for (int y = 0; y < image.height (); y++) {

      QColor pixel = image.pixel (xFrom, y);
      m_imagePreview.setPixel (xTo, y, pixel.rgb());
    }
  }

  m_sceneProfile->addPixmap (QPixmap::fromImage (m_imagePreview));
}

void DlgSettingsFilter::slotValue ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsFilter::slotValue";

  m_modelFilterAfter->setFilterParameter(FILTER_PARAMETER_VALUE);
  updateControls();
  updatePreview();
}

void DlgSettingsFilter::updateControls ()
{
  QImage image = cmdMediator().document().pixmap().toImage();

}

void DlgSettingsFilter::updateHistogram()
{
  m_sceneProfile->clear();

  m_scale->setFilterParameter (m_modelFilterAfter->filterParameter());

  // Start with original image
  QImage image = cmdMediator().document().pixmap().toImage();

  double histogramBins [HISTOGRAM_BINS];

  // Initialize histogram bins
  int bin;
  for (bin = 0; bin < HISTOGRAM_BINS; bin++) {
    histogramBins [bin] = 0;
  }

  Filter filter;
  QRgb rgbBackground = filter.marginColor(&image);

  // Populate histogram bins
  double maxBinCount = 0;
  for (int x = 0; x < image.width(); x++) {
    for (int y = 0; y < image.height(); y++) {
      QColor pixel (image.pixel (x, y));
      if (!filter.colorCompare (rgbBackground, pixel.rgb())) {

        double s = filter.pixelToZeroToOneOrMinusOne (m_modelFilterAfter->filterParameter(),
                                                      pixel,
                                                      rgbBackground);
        Q_ASSERT (s <= 1.0);
        if (s >= 0) {

          int bin = s * (HISTOGRAM_BINS - 1.0);
          ++(histogramBins [bin]);

          if (histogramBins [bin] > maxBinCount) {
            maxBinCount = histogramBins [bin];
          }
        }
      }
    }
  }

  // Draw histogram, normalizing so highest peak exactly fills the vertical range. Log scale is used
  // so smaller peaks do not disappear
  for (bin = 1; bin < HISTOGRAM_BINS; bin++) {

    double x0 = PROFILE_SCENE_WIDTH * (bin - 1.0) / (HISTOGRAM_BINS - 1.0);

    // Map 0 through maxBinCount to 0 through PROFILE_SCENE_HEIGHT-1, using log scale
    double count0 = maxBinCount - histogramBins [bin - 1] + 1; // Min value is 1 so log does not blow up
    double y0 = (PROFILE_SCENE_HEIGHT - 1.0) * qLn (count0) / qLn (maxBinCount + 1.0);

    double x1 = PROFILE_SCENE_WIDTH * (bin - 0.0) / (HISTOGRAM_BINS - 1.0);

    // Map 0 through maxBinCount to 0 through PROFILE_SCENE_HEIGHT-1, using log scale
    double count1 = maxBinCount - histogramBins [bin] + 1; // Min value is 1 so log does not blow up
    double y1 = (PROFILE_SCENE_HEIGHT - 1.0) * qLn (count1) / qLn (maxBinCount + 1.0);

    QGraphicsLineItem *line = new QGraphicsLineItem (x0, y0, x1, y1);
    m_sceneProfile->addItem (line);
  }

  // Create low and high dividers
  m_dividerLow = new ViewProfileDivider(*m_sceneProfile,
                                        *m_viewProfile,
                                        PROFILE_SCENE_WIDTH,
                                        PROFILE_SCENE_HEIGHT,
                                        PROFILE_SCENE_HEIGHT * 2.0 / 3.0,
                                        true);
  m_dividerHigh = new ViewProfileDivider(*m_sceneProfile,
                                         *m_viewProfile,
                                         PROFILE_SCENE_HEIGHT,
                                         PROFILE_SCENE_WIDTH,
                                         PROFILE_SCENE_HEIGHT / 3.0,
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
    m_dividerLow->setX (m_modelFilterAfter->foregroundLow(), FOREGROUND_MIN, FOREGROUND_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->foregroundHigh(), FOREGROUND_MIN, FOREGROUND_MAX);

  } else if (m_btnIntensity->isChecked()) {

    // Intensity
    m_dividerLow->setX (m_modelFilterAfter->intensityLow(), INTENSITY_MIN, INTENSITY_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->intensityHigh(), INTENSITY_MIN, INTENSITY_MAX);

  } else if (m_btnHue->isChecked()) {

    // Hue
    m_dividerLow->setX (m_modelFilterAfter->hueLow(), HUE_MIN, HUE_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->hueHigh(), HUE_MIN, HUE_MAX);

  } else if (m_btnSaturation->isChecked()) {

    // Saturation
    m_dividerLow->setX (m_modelFilterAfter->saturationLow(), SATURATION_MIN, SATURATION_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->saturationHigh(), SATURATION_MIN, SATURATION_MAX);

  } else if (m_btnValue->isChecked()) {

    // Value
    m_dividerLow->setX (m_modelFilterAfter->valueLow(), VALUE_MIN, VALUE_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->valueHigh(), VALUE_MIN, VALUE_MAX);

  } else {

    Q_ASSERT (false);

  }
}

void DlgSettingsFilter::updatePreview ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettings::updatePreview";

  updateHistogram();

  // This (indirectly) updates the preview
  emit signalApplyFilter (m_modelFilterAfter->filterParameter(),
                          m_modelFilterAfter->low(),
                          m_modelFilterAfter->high());
}
