#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "ColorFilter.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include <QPixmap>

BackgroundStateCurve::BackgroundStateCurve(BackgroundStateContext &context,
                                           GraphicsScene &scene) :
  BackgroundStateAbstractBase(context,
                              scene)
{
}

void BackgroundStateCurve::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::begin";

  setImageVisible (true);
}

void BackgroundStateCurve::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::end";

  setImageVisible (false);
}

void BackgroundStateCurve::fitInView (GraphicsView &view)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::fitInView";

  view.fitInView (imageItem ().boundingRect());
}

void BackgroundStateCurve::processImageFromSavedInputs (const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::processImageFromSavedInputs";

  // Use the settings if the selected curve is known
  if (!m_curveSelected.isEmpty()) {

    // Filtered image
    ColorFilter filter;
    QImage imageUnfiltered (m_pixmapOriginal.toImage ());
    QImage imageFiltered (m_pixmapOriginal.width (),
                          m_pixmapOriginal.height (),
                          QImage::Format_RGB32);
    QRgb rgbBackground = filter.marginColor (&imageUnfiltered);
    filter.filterImage (imageUnfiltered,
                        imageFiltered,
                        modelColorFilter.colorFilterMode(m_curveSelected),
                        modelColorFilter.low(m_curveSelected),
                        modelColorFilter.high(m_curveSelected),
                        rgbBackground);

    setProcessedPixmap (QPixmap::fromImage (imageFiltered));

  } else {

    // Set the image in case BackgroundStateContext::fitInView is called, so the bounding rect is available
    setProcessedPixmap (m_pixmapOriginal);

  }
}

void BackgroundStateCurve::setCurveSelected (const DocumentModelColorFilter &modelColorFilter,
                                             const QString &curveSelected)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setCurveSelected"
                              << " curve=" << curveSelected.toLatin1().data();

  if (m_curveSelected != curveSelected) {

    m_curveSelected = curveSelected;
    processImageFromSavedInputs (modelColorFilter);
  }
}

void BackgroundStateCurve::setPixmap (const DocumentModelColorFilter &modelColorFilter,
                                      const QPixmap &pixmapOriginal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setPixmap";

  m_pixmapOriginal = pixmapOriginal;
  processImageFromSavedInputs (modelColorFilter);
}

QString BackgroundStateCurve::state () const
{
  return "BackgroundStateCurve";
}

void BackgroundStateCurve::updateColorFilter (const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::updateColorFilter";

  processImageFromSavedInputs (modelColorFilter);
}
