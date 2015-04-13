#include "CallbackSceneUpdateAfterCommand.h"
#include "DataKey.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "GraphicsLinesForCurves.h"
#include "GraphicsScene.h"
#include "Point.h"
#include <QGraphicsItem>

CallbackSceneUpdateAfterCommand::CallbackSceneUpdateAfterCommand(GraphicsLinesForCurves &graphicsLinesForCurves,
                                                                 GraphicsScene &scene,
                                                                 const Document &document) :
  m_graphicsLinesForCurves (graphicsLinesForCurves),
  m_scene (scene),
  m_document (document)
{
}

CallbackSearchReturn CallbackSceneUpdateAfterCommand::callback (const QString &curveName,
                                                                const Point &point)
{
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  m_graphicsLinesForCurves.updateAfterCommand (m_scene,
                                               m_document.modelCurveStyles (),
                                               curveName,
                                               point);

  return rtn;
}
