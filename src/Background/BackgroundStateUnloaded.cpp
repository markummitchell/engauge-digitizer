#include "BackgroundStateContext.h"
#include "BackgroundStateUnloaded.h"
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

void BackgroundStateUnloaded::setColorFilter (const DocumentModelColorFilter & /* modelColorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::setColorFilter";
}

void BackgroundStateUnloaded::setCurveSelected (const QString & /* curveSelected */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::setCurveSelected";
}

void BackgroundStateUnloaded::setPixmap (const QPixmap & /* pixmap */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::setPixmap";

  // This state has no displayed image
}
