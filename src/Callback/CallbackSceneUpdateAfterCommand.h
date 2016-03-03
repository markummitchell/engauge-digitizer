#ifndef CALLBACK_SCENE_UPDATE_AFTER_COMMAND_H
#define CALLBACK_SCENE_UPDATE_AFTER_COMMAND_H

#include "CallbackSearchReturn.h"
#include "PointStyle.h"

class Document;
class GraphicsLinesForCurves;
class GraphicsScene;
class Point;

/// Callback for updating the QGraphicsItems in the scene after a command may
/// have modified Points in Curves.
class CallbackSceneUpdateAfterCommand {
public:
  /// Single constructor.
  CallbackSceneUpdateAfterCommand(
      GraphicsLinesForCurves &graphicsLinesForCurves, GraphicsScene &scene,
      const Document &document);

  /// Callback method.
  CallbackSearchReturn callback(const QString & /* curveName */,
                                const Point &point);

private:
  CallbackSceneUpdateAfterCommand();

  GraphicsLinesForCurves &m_graphicsLinesForCurves;
  GraphicsScene &m_scene;
  const Document &m_document;
};

#endif // CALLBACK_SCENE_UPDATE_AFTER_COMMAND_H
