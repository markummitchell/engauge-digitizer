#include "BackgroundStateContext.h"
#include "BackgroundStateUnloaded.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelGridRemoval.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include <QPixmap>

BackgroundStateUnloaded::BackgroundStateUnloaded(BackgroundStateContext &context,
                                                 GraphicsScene &scene) :
  BackgroundStateAbstractBase(context,
                              scene)
{
}

void BackgroundStateUnloaded::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::begin";
}

void BackgroundStateUnloaded::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::end";
}

void BackgroundStateUnloaded::fitInView (GraphicsView & /* view */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::fitInView";
}

void BackgroundStateUnloaded::setCurveSelected (const Transformation & /* transformation */,
                                                const DocumentModelGridRemoval & /* modelGridRemoval */,
                                                const DocumentModelColorFilter & /* modelColorFilter */,
                                                const QString & /* curveSelected */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::setCurveSelected";
}

void BackgroundStateUnloaded::setPixmap (const Transformation & /* transformation */,
                                         const DocumentModelGridRemoval & /* modelGridRemoval */,
                                         const DocumentModelColorFilter & /* modelColorFilter */,
                                         const QPixmap & /* pixmap */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::setPixmap";

  // This state has no displayed image
}

QString BackgroundStateUnloaded::state () const
{
  return "BackgroundStateUnloaded";
}

void BackgroundStateUnloaded::updateColorFilter (const Transformation & /* transformation */,
                                                 const DocumentModelGridRemoval & /* modelGridRemoval */,
                                                 const DocumentModelColorFilter & /* modelColorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::updateColorFilter";
}
