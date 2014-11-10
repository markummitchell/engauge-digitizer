#ifndef CALLBACK_SCENE_UPDATE_AFTER_COMMAND_H
#define CALLBACK_SCENE_UPDATE_AFTER_COMMAND_H

#include "CallbackSearchReturn.h"
#include "PointIdentifierToGraphicsItem.h"
#include "PointStyle.h"
#include "SettingsCurves.h"

class GraphicsScene;
class Point;

/// Callback for updating the QGraphicsItems in the scene after a command may have modified Points in Curves.
class CallbackSceneUpdateAfterCommand
{
public:
  /// Single constructor.
  CallbackSceneUpdateAfterCommand(PointIdentifierToGraphicsItem &pointIdentifierToGraphicsItem,
                                  GraphicsScene &scene,
                                  const SettingsCurves &settingsCurves);

  /// Callback method.
  CallbackSearchReturn callback (const QString & /* curveName */,
                                 const Point &point);

private:
  CallbackSceneUpdateAfterCommand();

  PointIdentifierToGraphicsItem &m_pointIdentifierToGraphicsItem;
  GraphicsScene &m_scene;
  const SettingsCurves m_settingsCurves;
};

#endif // CALLBACK_SCENE_UPDATE_AFTER_COMMAND_H
