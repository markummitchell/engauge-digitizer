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

const bool ADD_TO_EDGE = true;
const double GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH = 0.05;
const bool SUBTRACT_FROM_EDGE = false;

GuidelineOffset::GuidelineOffset()
{
}

QPointF GuidelineOffset::bottom (const QGraphicsView &view,
                                 const Transformation &transformation) const
{
  return bottomTop (view,
                    transformation,
                    SUBTRACT_FROM_EDGE);
}

QPointF GuidelineOffset::bottomTop (const QGraphicsView &view,
                                    const Transformation &transformation,
                                    bool add) const
{
  // Get scrolled extent so new Guideline appears in visible portion
  QRect viewportRect = view.viewport()->rect();
  QRect scrolledRect = view.viewportTransform ().inverted ().mapRect (viewportRect);

  QRectF sceneRect = view.scene()->sceneRect();

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineOffset::bottomTop"
                               << " viewportRect=" << QRectFToString (viewportRect).toLatin1().data()
                               << " scrolledRect=" << QRectFToString (scrolledRect).toLatin1().data()
                               << " sceneRect=" << QRectFToString (sceneRect).toLatin1().data();

  double offset = scrolledRect.height () * GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH;
  
  // Halfway across and a little above-bottom/below-top if offsetVertical is negative/positive. If viewport
  // bigger than the scene (=there is an empty margin) then scrolledRect offsets are negative, and we use
  // sceneRect, otherwise we use scrolledRect
  double x = scrolledRect.center().x();
  double y = (add ?
              qMax (scrolledRect.y () + offset, offset) :
              qMin (scrolledRect.y () + scrolledRect.height () - offset, sceneRect.height () - offset));

  QPointF posScene (x, y), posGraph;

  transformation.transformScreenToRawGraph (posScene,
                                            posGraph);

  return posGraph;
}

QPointF GuidelineOffset::left (const QGraphicsView &view,
                               const Transformation &transformation) const
{
  return leftRight (view,
                    transformation,
                    ADD_TO_EDGE);
}
                    
QPointF GuidelineOffset::leftRight(const QGraphicsView &view,
                                   const Transformation &transformation,
                                   bool add) const
{
  // Get scrolled extent so new Guideline appears in visible portion
  QRect viewportRect = view.viewport()->rect();
  QRect scrolledRect = view.viewportTransform ().inverted ().mapRect (viewportRect);

  QRectF sceneRect = view.scene()->sceneRect();

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineOffset::leftRight"
                               << " viewportRect=" << QRectFToString (viewportRect).toLatin1().data()
                               << " scrolledRect=" << QRectFToString (scrolledRect).toLatin1().data()
                               << " sceneRect=" << QRectFToString (sceneRect).toLatin1().data();

  double offset = scrolledRect.width () * GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH;
  
  // Halfway down and a little left-of-right/right-of-left if offsetHorizontal is negative/positive. If viewport
  // bigger than the scene (=there is an empty margin) then scrolledRect offsets are negative, and we use
  // sceneRect, otherwise we use scrolledRect
  double x = (add ?
              qMax (scrolledRect.x () + offset, offset) :
              qMin (scrolledRect.x () + scrolledRect.width () - offset, sceneRect.width () - offset));
  double y =  scrolledRect.center().y();

  QPointF posScene (x, y), posGraph;

  transformation.transformScreenToRawGraph (posScene,
                                            posGraph);

  return posGraph;
}

QPointF GuidelineOffset::right (const QGraphicsView &view,
                                const Transformation &transformation) const
{
  return leftRight (view,
                    transformation,
                    SUBTRACT_FROM_EDGE);
}

QPointF GuidelineOffset::top (const QGraphicsView &view,
                              const Transformation &transformation) const
{
  return bottomTop (view,
                    transformation,
                    ADD_TO_EDGE);
}
