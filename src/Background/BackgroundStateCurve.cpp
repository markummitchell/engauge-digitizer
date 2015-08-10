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

void BackgroundStateCurve::processImageFromSavedInputs ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::processImageFromSavedInputs";

  // Make sure the selected curve has already been set
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
                        m_modelColorFilter.colorFilterMode(m_curveSelected),
                        m_modelColorFilter.low(m_curveSelected),
                        m_modelColorFilter.high(m_curveSelected),
                        rgbBackground);

    setProcessedPixmap (QPixmap::fromImage (imageFiltered));
  }
}

void BackgroundStateCurve::setColorFilter (const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setColorFilter";

  m_modelColorFilter = modelColorFilter;
  processImageFromSavedInputs ();
}

void BackgroundStateCurve::setCurveSelected (const QString &curveSelected)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setCurveSelected"
                              << " curve=" << curveSelected.toLatin1().data();

  if (m_curveSelected != curveSelected) {

    m_curveSelected = curveSelected;
    processImageFromSavedInputs ();
  }
}

void BackgroundStateCurve::setPixmap (const QPixmap &pixmapOriginal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setPixmap";

  m_pixmapOriginal = pixmapOriginal;
  processImageFromSavedInputs ();
}
