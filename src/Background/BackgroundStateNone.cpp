#include "BackgroundStateContext.h"
#include "BackgroundStateNone.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QPixmap>

BackgroundStateNone::BackgroundStateNone(BackgroundStateContext &context,
                                         GraphicsScene &scene) :
  BackgroundStateAbstractBase(context,
                              scene)
{
}

void BackgroundStateNone::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::begin";
}

void BackgroundStateNone::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::end";
}

void BackgroundStateNone::setPixmap (const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::setPixmap";
}

void BackgroundStateNone::updateColorFilter (const DocumentModelColorFilter & /* colorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::updateColorFilter";
}
