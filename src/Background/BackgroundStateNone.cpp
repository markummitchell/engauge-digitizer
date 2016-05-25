/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "BackgroundStateContext.h"
#include "BackgroundStateNone.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelGridRemoval.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
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

void BackgroundStateNone::fitInView (GraphicsView &view)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::fitInView";

  view.fitInView (imageItem ().boundingRect());
}

void BackgroundStateNone::setCurveSelected (const Transformation & /* transformation */,
                                            const DocumentModelGridRemoval & /* modelGridRemoval */,
                                            const DocumentModelColorFilter & /* modelColorFilter */,
                                            const QString & /* curveSelected */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::setCurveSelected";
}

void BackgroundStateNone::setPixmap (const Transformation & /* transformation */,
                                     const DocumentModelGridRemoval & /* modelGridRemoval */,
                                     const DocumentModelColorFilter & /* modelColorFilter */,
                                     const QPixmap &pixmapOriginal,
                                     const QString & /* curveSelected */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::setPixmap";

  // Empty background
  QPixmap pixmapNone (pixmapOriginal);
  pixmapNone.fill (Qt::white);
  setProcessedPixmap (pixmapNone);

}

QString BackgroundStateNone::state () const
{
  return "BackgroundStateNone";
}

void BackgroundStateNone::updateColorFilter (const Transformation & /* transformation */,
                                             const DocumentModelGridRemoval & /* modelGridRemoval */,
                                             const DocumentModelColorFilter & /* modelColorFilter */,
                                             const QString & /* curveSelected */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::updateColorFilter";
}
