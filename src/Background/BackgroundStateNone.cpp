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

  setImageVisible (true);
}

void BackgroundStateNone::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::end";

  setImageVisible (false);
}

void BackgroundStateNone::setColorFilter (const DocumentModelColorFilter & /* modelColorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::setColorFilter";
}

void BackgroundStateNone::setCurveSelected (const QString & /* curveSelected */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::setCurveSelected";
}

void BackgroundStateNone::setPixmap (const QPixmap &pixmapOriginal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::setPixmap";

  // Empty background
  QPixmap pixmapNone (pixmapOriginal);
  pixmapNone.fill (Qt::white);
  setProcessedPixmap (pixmapNone);

}
