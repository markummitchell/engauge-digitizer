#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include "CmdMediator.h"
#include "PointIdentifierToGraphicsItem.h"
#include <QGraphicsScene>
#include <QStringList>

class CmdMediator;
class Curve;
class CurvesGraphs;
class DlgModelCurveProperties;
class MainWindow;
class PointStyle;
class QGraphicsItem;

/// Add Point handling to generic QGraphicsScene. The primary task is to update the graphics items to stay in
/// sync with the Points in the Document.
class GraphicsScene : public QGraphicsScene
{
public:
  /// Single constructor.
  GraphicsScene(MainWindow *mainWindow);

  /// Add one QGraphicsItem-based object that represents one Point.
  QGraphicsItem *addPoint (const QString &identifier,
                           const PointStyle &pointStyle,
                           const QPointF &posScreen);

  /// Dump all important cursors
  QString dumpCursors () const;

  /// Create a map from Point identifier to graphics item in the scene. Typically the map lives only briefly and
  /// gets regenerated whenever it is needed.
  PointIdentifierToGraphicsItem mapPointIdentifierToGraphicsItem ();

  /// Return a list of identifiers for the points that have moved since the last call to resetPositionHasChanged.
  QStringList positionHasChangedPointIdentifiers () const;

  /// Reset positionHasChanged flag for all items. Typically this is done as part of mousePressEvent.
  void resetPositionHasChanged();

  /// Return a list of identifiers for the currently selected points.
  QStringList selectedPointIdentifiers () const;

  /// Show or hide all the Points in the Curves (if showAll is true) or just the selected Curve (if showAll is false);
  void showPoints (bool show,
                   bool showAll = false,
                   const QString &curveName = "");

  /// Update the Curves and their Points after executing a command.
  void updateAfterCommand (CmdMediator &cmdMediator);

  /// Update curve properties after settings changed.
  void updateCurveProperties(const DlgModelCurveProperties &modelCurveProperties);

private:
  const QGraphicsPixmapItem *image () const;
};

#endif // GRAPHICS_SCENE_H
