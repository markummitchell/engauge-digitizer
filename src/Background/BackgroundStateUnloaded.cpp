#include "BackgroundStateContext.h"
#include "BackgroundStateUnloaded.h"
#include "GraphicsScene.h"
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

void BackgroundStateUnloaded::setPixmap (const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::setPixmap";
}

void BackgroundStateUnloaded::updateColorFilter (const DocumentModelColorFilter & /* colorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateUnloaded::updateColorFilter";
}
