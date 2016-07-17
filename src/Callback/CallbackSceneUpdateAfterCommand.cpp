/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackSceneUpdateAfterCommand.h"
#include "DataKey.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "GeometryWindow.h"
#include "GraphicsLinesForCurves.h"
#include "GraphicsScene.h"
#include "Point.h"
#include <QGraphicsItem>

CallbackSceneUpdateAfterCommand::CallbackSceneUpdateAfterCommand(GraphicsLinesForCurves &graphicsLinesForCurves,
                                                                 GraphicsScene &scene,
                                                                 const Document &document,
                                                                 GeometryWindow *geometryWindow) :
  m_graphicsLinesForCurves (graphicsLinesForCurves),
  m_scene (scene),
  m_document (document),
  m_geometryWindow (geometryWindow)
{
}

CallbackSearchReturn CallbackSceneUpdateAfterCommand::callback (const QString &curveName,
                                                                const Point &point)
{
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  m_graphicsLinesForCurves.updateAfterCommand (m_scene,
                                               m_document.modelCurveStyles (),
                                               curveName,
                                               point,
                                               m_geometryWindow);

  return rtn;
}
