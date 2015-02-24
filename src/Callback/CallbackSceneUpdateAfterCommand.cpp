#include "CallbackSceneUpdateAfterCommand.h"
#include "DataKey.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "Point.h"
#include <QGraphicsItem>

CallbackSceneUpdateAfterCommand::CallbackSceneUpdateAfterCommand(PointIdentifierToGraphicsPoint &pointIdentifierToGraphicsPoint,
                                                                 GraphicsScene &scene,
                                                                 const Document &document) :
  m_pointIdentifierToGraphicsPoint (pointIdentifierToGraphicsPoint),
  m_scene (scene),
  m_document (document)
{
}

CallbackSearchReturn CallbackSceneUpdateAfterCommand::callback (const QString &curveName,
                                                                const Point &point)
{
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  GraphicsPoint *graphicsPoint = 0;
  if (m_pointIdentifierToGraphicsPoint.contains (point.identifier())) {

    graphicsPoint = m_pointIdentifierToGraphicsPoint [point.identifier ()];

  } else {

    // Point does not exist in scene yet so create it
    const Curve *curve = m_document.curveForCurveName (curveName);
    ENGAUGE_CHECK_PTR (curve);
    graphicsPoint = m_scene.addPoint (point.identifier (),
                                      curve->curveStyle().pointStyle (),
                                      point.posScreen ());
  }

  // Mark point as wanted
  ENGAUGE_CHECK_PTR (graphicsPoint);
  graphicsPoint->setWanted ();

  return rtn;
}
