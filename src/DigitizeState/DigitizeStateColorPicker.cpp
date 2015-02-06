#include "CmdMediator.h"
#include "CmdSettingsFilter.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateColorPicker.h"
#include "DocumentModelFilter.h"
#include "Filter.h"
#include "FilterHistogram.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>

DigitizeStateColorPicker::DigitizeStateColorPicker (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateColorPicker::~DigitizeStateColorPicker ()
{
}

QString DigitizeStateColorPicker::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateColorPicker::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

void DigitizeStateColorPicker::computeFilterFromPixel (const QPointF &posScreen,
                                                       const QString &curveName,
                                                       DocumentModelFilter &modelFilterAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::computeFilterFromPixel";

  // Adjust screen position so truncation gives round-up behavior
  QPointF posScreenPlusHalf = posScreen - QPointF (0.5, 0.5);

  QImage image = context().cmdMediator().document().pixmap().toImage();
  QColor pixel = image.pixel (posScreenPlusHalf.toPoint ());

  // The choice of which filter mode to use is determined, currently, by the selected pixel. This
  // could be maybe made smarter by looking at other pixels, or even the entire image
  int r = qRed (pixel.rgb());
  int g = qGreen (pixel.rgb());
  int b = qBlue (pixel.rgb());
  if (r == g && g == b) {

    // Pixel is gray scale, so we use intensity
    modelFilterAfter.setFilterMode (curveName,
                                    FILTER_MODE_INTENSITY);

  } else {

    // Pixel is not gray scale, so we use hue
    modelFilterAfter.setFilterMode (curveName,
                                    FILTER_MODE_HUE);

  }

  // Generate histogram
  double histogramBins [HISTOGRAM_BINS];

  Filter filter;
  FilterHistogram filterHistogram;
  int maxBinCount;
  filterHistogram.generate (filter,
                            histogramBins,
                            modelFilterAfter.filterMode (curveName),
                            image,
                            maxBinCount);

  // Background color
  QRgb rgbBackground = filter.marginColor(&image);

  // Bin for pixel
  int pixelBin = filterHistogram.binFromPixel(filter,
                                              modelFilterAfter.filterMode (curveName),
                                              pixel,
                                              rgbBackground);

  // Identify the entire width of the peak that the selected pixel belongs to. Go in both directions until the count
  // hits zero or goes up
  int lowerBin = pixelBin, upperBin = pixelBin;
  while ((lowerBin > 0) &&
         (histogramBins [lowerBin - 1] <= histogramBins [lowerBin]) &&
         (histogramBins [lowerBin] > 0)) {
    --lowerBin;
  }
  while ((upperBin < HISTOGRAM_BINS - 1) &&
         (histogramBins [upperBin + 1] <= histogramBins [upperBin]) &&
         (histogramBins [upperBin] > 0)) {
    ++upperBin;
  }

  // Compute values from bin numbers
  int lowerValue = filterHistogram.valueFromBin(filter,
                                                modelFilterAfter.filterMode (curveName),
                                                lowerBin);
  int upperValue = filterHistogram.valueFromBin(filter,
                                                modelFilterAfter.filterMode (curveName),
                                                upperBin);

  switch (modelFilterAfter.filterMode (curveName)) {
    case FILTER_MODE_FOREGROUND:
      modelFilterAfter.setForegroundLow(curveName,
                                        lowerValue);
      modelFilterAfter.setForegroundHigh(curveName,
                                         upperValue);
      break;

    case FILTER_MODE_HUE:
      modelFilterAfter.setHueLow(curveName,
                                 lowerValue);
      modelFilterAfter.setHueHigh(curveName,
                                  upperValue);
      break;

    case FILTER_MODE_INTENSITY:
      modelFilterAfter.setIntensityLow(curveName,
                                       lowerValue);
      modelFilterAfter.setIntensityHigh(curveName,
                                        upperValue);
      break;

    case FILTER_MODE_SATURATION:
      modelFilterAfter.setSaturationLow(curveName,
                                        lowerValue);
      modelFilterAfter.setSaturationHigh(curveName,
                                         upperValue);
      break;

    case FILTER_MODE_VALUE:
      modelFilterAfter.setValueLow(curveName,
                                   lowerValue);
      modelFilterAfter.setValueHigh(curveName,
                                    upperValue);
      break;

    default:
      Q_ASSERT (false);
  }
}

QCursor DigitizeStateColorPicker::cursor() const
{
  // Hot point is at the point of the eye dropper
  const int HOT_X_IN_BITMAP = 8;
  const int HOT_Y_IN_BITMAP = 24;
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateColorPicker::cursor";

  QBitmap bitmap (":/engauge/img/cursor_eyedropper.xpm");
  QBitmap bitmapMask (":/engauge/img/cursor_eyedropper_mask.xpm");
  return QCursor (bitmap,
                  bitmapMask,
                  HOT_X_IN_BITMAP,
                  HOT_Y_IN_BITMAP);
}

void DigitizeStateColorPicker::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::end";
}

void DigitizeStateColorPicker::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateColorPicker::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleMousePress";
}

void DigitizeStateColorPicker::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleMouseRelease";

  DocumentModelFilter modelFilterBefore = context().cmdMediator().document().modelFilter();
  DocumentModelFilter modelFilterAfter = context().cmdMediator().document().modelFilter();
  computeFilterFromPixel (posScreen,
                          context().mainWindow().selectedGraphCurve(),
                          modelFilterAfter);

  // Create command to change segment filter
  QUndoCommand *cmd = new CmdSettingsFilter (context ().mainWindow(),
                                             context ().cmdMediator ().document (),
                                             modelFilterBefore,
                                             modelFilterAfter);
  context().appendNewCmd(cmd);
}
