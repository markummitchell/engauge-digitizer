/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineOffset.h"
#include "Logger.h"
#include <QGraphicsView>
#include "QtToString.h"
#include "Transformation.h"

GuidelineOffset::GuidelineOffset()
{
}

QPointF GuidelineOffset::XT (const QGraphicsView &view,
                             const Transformation &transformation) const
{
  // Get scrolled extent so new Guideline appears in visible portion
  QRect viewportRect = view.viewport()->rect();
  QRect scrolledRect = view.viewportTransform ().inverted ().mapRect (viewportRect);
  QRectF sceneRect = view.scene()->sceneRect();

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineOffset::bottomTop"
                               << " viewportRect=" << QRectFToString (viewportRect).toLatin1().data()
                               << " scrolledRect=" << QRectFToString (scrolledRect).toLatin1().data()
                               << " sceneRect=" << QRectFToString (sceneRect).toLatin1().data();

  // Use center of visible sscene
  QPointF posScene (scrolledRect.center().x(),
                    scrolledRect.center().y()), posGraph;

  transformation.transformScreenToRawGraph (posScene,
                                            posGraph);

  return posGraph;
}
                    
QPointF GuidelineOffset::YR (const QGraphicsView &view,
                             const Transformation &transformation) const
{
  // Get scrolled extent so new Guideline appears in visible portion
  QRect viewportRect = view.viewport()->rect();
  QRect scrolledRect = view.viewportTransform ().inverted ().mapRect (viewportRect);
  QRectF sceneRect = view.scene()->sceneRect();

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineOffset::leftRight"
                               << " viewportRect=" << QRectFToString (viewportRect).toLatin1().data()
                               << " scrolledRect=" << QRectFToString (scrolledRect).toLatin1().data()
                               << " sceneRect=" << QRectFToString (sceneRect).toLatin1().data();

  // Use center of visible sscene
  QPointF posScene (scrolledRect.center().x(),
                    scrolledRect.center().y()), posGraph;

  transformation.transformScreenToRawGraph (posScene,
                                            posGraph);

  return posGraph;
}
