#include "CallbackSceneUpdateAfterCommand.h"
#include "DataKey.h"
#include "GraphicsScene.h"
#include "Point.h"
#include <QGraphicsItem>

CallbackSceneUpdateAfterCommand::CallbackSceneUpdateAfterCommand(PointIdentifierToGraphicsItem &pointIdentifierToGraphicsItem,
                                                                 GraphicsScene &scene,
                                                                 const SettingsCurves &settingsCurves) :
  m_pointIdentifierToGraphicsItem (pointIdentifierToGraphicsItem),
  m_scene (scene),
  m_settingsCurves (settingsCurves)
{
}

CallbackSearchReturn CallbackSceneUpdateAfterCommand::callback (const QString &curveName,
                                                                const Point &point)
{
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  QGraphicsItem *item = 0;
  if (m_pointIdentifierToGraphicsItem.contains (point.identifier())) {

    item = m_pointIdentifierToGraphicsItem [point.identifier ()];

  } else {

    // Point does not exist in scene yet so create it
    item = m_scene.addPoint (point.identifier (),
                             m_settingsCurves.pointStyleForCurveName (curveName),
                             point.posScreen ());
  }

  // Mark point as wanted
  item->setData (DATA_KEY_WANTED, true);

  return rtn;
}
