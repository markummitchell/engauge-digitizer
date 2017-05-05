/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsColorFilter.h"
#include "ColorFilter.h"
#include "ColorFilterHistogram.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateColorPicker.h"
#include "DocumentModelColorFilter.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QMessageBox>

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

void DigitizeStateColorPicker::begin (CmdMediator *cmdMediator,
                                      DigitizeState previousState)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);

  // Save current state stuff so it can be restored afterwards
  m_previousDigitizeState = previousState;
  m_previousBackground = context().mainWindow().selectOriginal(BACKGROUND_IMAGE_ORIGINAL); // Only makes sense to have original image with all its colors

  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

bool DigitizeStateColorPicker::canPaste (const Transformation & /* transformation */,
                                         const QSize & /* viewSize */) const
{
  return false;
}

bool DigitizeStateColorPicker::computeFilterFromPixel (CmdMediator *cmdMediator,
                                                       const QPointF &posScreen,
                                                       const QString &curveName,
                                                       DocumentModelColorFilter &modelColorFilterAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::computeFilterFromPixel";

  bool rtn = false;

  // Filter for background color now, and then later, once filter mode is set, processing of image
  ColorFilter filter;
  QImage image = cmdMediator->document().pixmap().toImage();
  QRgb rgbBackground = filter.marginColor(&image);

  // Adjust screen position so truncation gives round-up behavior
  QPointF posScreenPlusHalf = posScreen - QPointF (0.5, 0.5);

  QColor pixel;
  rtn = findNearestNonBackgroundPixel (cmdMediator,
                                       image,
                                       posScreenPlusHalf,
                                       rgbBackground,
                                       pixel);
  if (rtn) {

    // The choice of which filter mode to use is determined, currently, by the selected pixel. This
    // could be maybe made smarter by looking at other pixels, or even the entire image
    int r = qRed (pixel.rgb());
    int g = qGreen (pixel.rgb());
    int b = qBlue (pixel.rgb());
    if (r == g && g == b) {

      // Pixel is gray scale, so we use intensity
      modelColorFilterAfter.setColorFilterMode (curveName,
                                                COLOR_FILTER_MODE_INTENSITY);

    } else {

      // Pixel is not gray scale, so we use hue
      modelColorFilterAfter.setColorFilterMode (curveName,
                                                COLOR_FILTER_MODE_HUE);

    }

    // Generate histogram
    double *histogramBins = new double [ColorFilterHistogram::HISTOGRAM_BINS ()];

    ColorFilterHistogram filterHistogram;
    int maxBinCount;
    filterHistogram.generate (filter,
                              histogramBins,
                              modelColorFilterAfter.colorFilterMode (curveName),
                              image,
                              maxBinCount);

    // Bin for pixel
    int pixelBin = filterHistogram.binFromPixel(filter,
                                                modelColorFilterAfter.colorFilterMode (curveName),
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
    while ((upperBin < ColorFilterHistogram::HISTOGRAM_BINS () - 1) &&
           (histogramBins [upperBin + 1] <= histogramBins [upperBin]) &&
           (histogramBins [upperBin] > 0)) {
      ++upperBin;
    }

    // Compute and save values from bin numbers
    int lowerValue = filterHistogram.valueFromBin(filter,
                                                  modelColorFilterAfter.colorFilterMode (curveName),
                                                  lowerBin);
    int upperValue = filterHistogram.valueFromBin(filter,
                                                  modelColorFilterAfter.colorFilterMode (curveName),
                                                  upperBin);

    saveLowerValueUpperValue (modelColorFilterAfter,
                              curveName,
                              lowerValue,
                              upperValue);

    delete [] histogramBins;

  } else {

    QMessageBox::warning (0,
                          QObject::tr ("Color Picker"),
                          QObject::tr ("Sorry, but the color picker point must be near a non-background pixel. Please try again."));

  }

  return rtn;
}

QCursor DigitizeStateColorPicker::cursor(CmdMediator * /* cmdMediator */) const
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

  // Restore original background. The state transition was triggered earlier by either the user selecting
  // a valid point, or by user clicking on another digitize state button
  context().mainWindow().selectOriginal(m_previousBackground);
}

bool DigitizeStateColorPicker::findNearestNonBackgroundPixel (CmdMediator *cmdMediator,
                                                              const QImage &image,
                                                              const QPointF &posScreenPlusHalf,
                                                              const QRgb &rgbBackground,
                                                              QColor &pixel)
{
  QPoint pos = posScreenPlusHalf.toPoint ();

  int maxRadiusForSearch = cmdMediator->document().modelGeneral().cursorSize();

  // Starting at pos, search in ever-widening squares for a non-background pixel
  for (int radius = 0; radius < maxRadiusForSearch; radius++) {

    for (int xOffset = -radius; xOffset <= radius; xOffset++) {
      for (int yOffset = -radius; yOffset <= radius; yOffset++) {

        // Top side
        pixel = image.pixel (pos.x () + xOffset, pos.y () - radius);
        if (pixel != rgbBackground) {
          return true;
        }

        // Bottom side
        pixel = image.pixel (pos.x () + xOffset, pos.y () + radius);
        if (pixel != rgbBackground) {
          return true;
        }

        // Left side
        pixel = image.pixel (pos.x () - radius, pos.y () - yOffset);
        if (pixel != rgbBackground) {
          return true;
        }

        // Right side
        pixel = image.pixel (pos.x () + radius, pos.y () + yOffset);
        if (pixel != rgbBackground) {
          return true;
        }
      }
    }
  }

  return false;
}

void DigitizeStateColorPicker::handleContextMenuEventAxis (CmdMediator * /* cmdMediator */,
                                                           const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();
}

void DigitizeStateColorPicker::handleContextMenuEventGraph (CmdMediator * /* cmdMediator */,
                                                            const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker ::handleContextMenuEventGraph "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();
}

void DigitizeStateColorPicker::handleCurveChange(CmdMediator * /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleCurveChange";
}

void DigitizeStateColorPicker::handleKeyPress (CmdMediator * /* cmdMediator */,
                                               Qt::Key key,
                                               bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateColorPicker::handleMouseMove (CmdMediator * /* cmdMediator */,
                                                QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateColorPicker::handleMouseMove";
}

void DigitizeStateColorPicker::handleMousePress (CmdMediator * /* cmdMediator */,
                                                 QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleMousePress";
}

void DigitizeStateColorPicker::handleMouseRelease (CmdMediator *cmdMediator,
                                                   QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleMouseRelease";

  DocumentModelColorFilter modelColorFilterBefore = cmdMediator->document().modelColorFilter();
  DocumentModelColorFilter modelColorFilterAfter = cmdMediator->document().modelColorFilter();
  if (computeFilterFromPixel (cmdMediator,
                              posScreen,
                              context().mainWindow().selectedGraphCurve(),
                              modelColorFilterAfter)) {

    // Trigger a state transition. The background restoration will be handled by the end method
    context().requestDelayedStateTransition(m_previousDigitizeState);

    // Create command to change segment filter
    QUndoCommand *cmd = new CmdSettingsColorFilter (context ().mainWindow(),
                                                    cmdMediator->document (),
                                                    modelColorFilterBefore,
                                                    modelColorFilterAfter);
    context().appendNewCmd(cmdMediator,
                           cmd);
  }
}

void DigitizeStateColorPicker::saveLowerValueUpperValue (DocumentModelColorFilter &modelColorFilterAfter,
                                                         const QString &curveName,
                                                         double lowerValue,
                                                         double upperValue)
{
  switch (modelColorFilterAfter.colorFilterMode (curveName)) {
    case COLOR_FILTER_MODE_FOREGROUND:
      modelColorFilterAfter.setForegroundLow(curveName,
                                             lowerValue);
      modelColorFilterAfter.setForegroundHigh(curveName,
                                              upperValue);
      break;

    case COLOR_FILTER_MODE_HUE:
      modelColorFilterAfter.setHueLow(curveName,
                                      lowerValue);
      modelColorFilterAfter.setHueHigh(curveName,
                                       upperValue);
      break;

    case COLOR_FILTER_MODE_INTENSITY:
      modelColorFilterAfter.setIntensityLow(curveName,
                                            lowerValue);
      modelColorFilterAfter.setIntensityHigh(curveName,
                                             upperValue);
      break;

    case COLOR_FILTER_MODE_SATURATION:
      modelColorFilterAfter.setSaturationLow(curveName,
                                             lowerValue);
      modelColorFilterAfter.setSaturationHigh(curveName,
                                              upperValue);
      break;

    case COLOR_FILTER_MODE_VALUE:
      modelColorFilterAfter.setValueLow(curveName,
                                        lowerValue);
      modelColorFilterAfter.setValueHigh(curveName,
                                         upperValue);
      break;

    default:
      ENGAUGE_ASSERT (false);
  }
}

QString DigitizeStateColorPicker::state() const
{
  return "DigitizeStateColorPicker";
}

void DigitizeStateColorPicker::updateAfterPointAddition ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::updateAfterPointAddition";
}

void DigitizeStateColorPicker::updateModelDigitizeCurve (CmdMediator * /* cmdMediator */,
                                                         const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::updateModelDigitizeCurve";
}

void DigitizeStateColorPicker::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::updateModelSegments";
}
