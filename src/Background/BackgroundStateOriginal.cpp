#include "BackgroundStateContext.h"
#include "BackgroundStateOriginal.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QPixmap>

BackgroundStateOriginal::BackgroundStateOriginal(BackgroundStateContext &context,
                                                 GraphicsScene &scene) :
  BackgroundStateAbstractBase(context,
                              scene)
{
}

void BackgroundStateOriginal::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateOriginal::begin";
}

void BackgroundStateOriginal::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateOriginal::end";
}

void BackgroundStateOriginal::setPixmap (const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateOriginal::setPixmap";
}

void BackgroundStateOriginal::updateColorFilter (const DocumentModelColorFilter & /* colorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateOriginal::updateColorFilter";
}
