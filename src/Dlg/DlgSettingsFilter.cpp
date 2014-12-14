#include "CmdMediator.h"
#include "CmdSettingsFilter.h"
#include "DlgDivider.h"
#include "DlgScale.h"
#include "DlgSettingsFilter.h"
#include "Filter.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <qmath.h>
#include <QRadioButton>
#include <QRgb>
#include "ViewPreview.h"
#include "ViewProfile.h"

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
                                    "and blue components as I = (R + G + B) / 3"));
  connect (m_btnIntensity, SIGNAL (released ()), this, SLOT (slotIntensity ()));
  layout->addWidget (m_btnIntensity, row++, 1);

  m_btnForeground = new QRadioButton ("Foreground");
  m_btnForeground->setWhatsThis (tr ("Filter the original image into black and white pixels by isolating the foreground from the background, "
                                     "to hide unimportant information and emphasize important information.\n\n"
                                     "The background color is shown on the left side of the scale bar. All pixels with approximately "
                                     "the background color are considered part of the background, and all other pixels are considered "
                                     "part of the foreground"));
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

  m_scale = new DlgScale;
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

  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

unsigned int DlgSettingsFilter::pixelToBin (const QColor &pixel)
{
  int bin = 0; // Must be negatie since value is sometimes -1 below

  switch (m_modelFilterAfter->filterParameter()) {
    case FILTER_PARAMETER_FOREGROUND:
      bin = pixel.hueF() * (HISTOGRAM_BINS - 1.0);
      if (bin < 0) {
        // Color is achromatic (r=g=b) so it has no hue
        bin = 0;
      }
      break;

    case FILTER_PARAMETER_HUE:
      bin = pixel.hueF() * (HISTOGRAM_BINS - 1.0);
      if (bin < 0) {
        // Color is achromatic (r=g=b) so it has no hue
        bin = 0;
      }
      break;

    case FILTER_PARAMETER_INTENSITY:
      bin = qGray (pixel.rgb()) * (HISTOGRAM_BINS - 1.0) / 255.0;
      break;

    case FILTER_PARAMETER_SATURATION:
      bin = pixel.saturationF() * (HISTOGRAM_BINS - 1.0);
      break;

    case FILTER_PARAMETER_VALUE:
      bin = pixel.valueF() * (HISTOGRAM_BINS - 1.0);
      break;

    default:
      Q_ASSERT (false);
  }

  return bin;
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

void DlgSettingsFilter::updateHistogram(const QPixmap &pixmap)
{
  m_sceneProfile->clear();

  m_scale->setFilterParameter (m_modelFilterAfter->filterParameter());

  QImage image = pixmap.toImage();

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

        int bin = pixelToBin (pixel);
        Q_ASSERT (0 <= bin && bin < HISTOGRAM_BINS);
        ++(histogramBins [bin]);

        if (histogramBins [bin] > maxBinCount) {
          maxBinCount = histogramBins [bin];
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

  m_dividerLow = new DlgDivider(*m_sceneProfile,
                                *m_viewProfile,
                                PROFILE_SCENE_WIDTH,
                                PROFILE_SCENE_HEIGHT,
                                PROFILE_SCENE_HEIGHT * 2.0 / 3.0,
                                true);
  m_dividerHigh = new DlgDivider(*m_sceneProfile,
                                 *m_viewProfile,
                                 PROFILE_SCENE_HEIGHT,
                                 PROFILE_SCENE_WIDTH,
                                 PROFILE_SCENE_HEIGHT / 3.0,
                                 false);
  connect (m_dividerLow, SIGNAL (signalMoved(double)), m_dividerHigh, SLOT (slotOtherMoved(double)));
  connect (m_dividerHigh, SIGNAL (signalMoved(double)), m_dividerLow, SLOT (slotOtherMoved(double)));

  if (m_btnForeground->isChecked()) {
    m_dividerLow->setX (m_modelFilterAfter->foregroundLow(), FOREGROUND_MIN, FOREGROUND_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->foregroundHigh(), FOREGROUND_MIN, FOREGROUND_MAX);
  } else if (m_btnIntensity->isChecked()) {
    m_dividerLow->setX (m_modelFilterAfter->intensityLow(), INTENSITY_MIN, INTENSITY_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->intensityHigh(), INTENSITY_MIN, INTENSITY_MAX);
  } else if (m_btnHue->isChecked()) {
    m_dividerLow->setX (m_modelFilterAfter->hueLow(), HUE_MIN, HUE_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->hueHigh(), HUE_MIN, HUE_MAX);
  } else if (m_btnSaturation->isChecked()) {
    m_dividerLow->setX (m_modelFilterAfter->saturationLow(), SATURATION_MIN, SATURATION_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->saturationHigh(), SATURATION_MIN, SATURATION_MAX);
  } else if (m_btnValue->isChecked()) {
    m_dividerLow->setX (m_modelFilterAfter->valueLow(), VALUE_MIN, VALUE_MAX);
    m_dividerHigh->setX (m_modelFilterAfter->valueHigh(), VALUE_MIN, VALUE_MAX);
  }
}

void DlgSettingsFilter::updatePreview ()
{
  QPixmap pixmap = cmdMediator().document().pixmap();
  updateHistogram(pixmap);

  m_scenePreview->clear();
  m_scenePreview->addPixmap (pixmap);
}
