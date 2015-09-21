#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelGridRemoval.h"
#include "FilterImage.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include <QPixmap>
#include "Transformation.h"

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

void BackgroundStateCurve::processImageFromSavedInputs (const Transformation &transformation,
                                                        const DocumentModelGridRemoval &modelGridRemoval,
                                                        const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::processImageFromSavedInputs";

  // Use the settings if the selected curve is known
  if (!m_curveSelected.isEmpty()) {

    // Generate filtered image
    FilterImage filterImage;
    QPixmap pixmapFiltered = filterImage.filter (m_pixmapOriginal.toImage(),
                                                 transformation,
                                                 m_curveSelected,
                                                 modelColorFilter,
                                                 modelGridRemoval);

    setProcessedPixmap (pixmapFiltered);

  } else {

    // Set the image in case BackgroundStateContext::fitInView is called, so the bounding rect is available
    setProcessedPixmap (m_pixmapOriginal);

  }
}

void BackgroundStateCurve::setCurveSelected (const Transformation &transformation,
                                             const DocumentModelGridRemoval &modelGridRemoval,
                                             const DocumentModelColorFilter &modelColorFilter,
                                             const QString &curveSelected)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setCurveSelected"
                              << " curve=" << curveSelected.toLatin1().data();

  // Even if m_curveSelected equals curveSelected we update the image, since the transformation
  // may have changed
  m_curveSelected = curveSelected;
  processImageFromSavedInputs (transformation,
                               modelGridRemoval,
                               modelColorFilter);
}

void BackgroundStateCurve::setPixmap (const Transformation &transformation,
                                      const DocumentModelGridRemoval &modelGridRemoval,
                                      const DocumentModelColorFilter &modelColorFilter,
                                      const QPixmap &pixmapOriginal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setPixmap";

  m_pixmapOriginal = pixmapOriginal;
  processImageFromSavedInputs (transformation,
                               modelGridRemoval,
                               modelColorFilter);
}

QString BackgroundStateCurve::state () const
{
  return "BackgroundStateCurve";
}

void BackgroundStateCurve::updateColorFilter (const Transformation &transformation,
                                              const DocumentModelGridRemoval &modelGridRemoval,
                                              const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::updateColorFilter";

  processImageFromSavedInputs (transformation,
                               modelGridRemoval,
                               modelColorFilter);
}
