#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include "CmdMediator.h"
#include "GraphicsLinesForCurves.h"
#include "LineIdentifierToGraphicsLine.h"
#include "PointIdentifierToGraphicsPoint.h"
#include <QGraphicsScene>
#include <QHash>
#include <QMap>
#include <QStringList>

class CmdMediator;
class Curve;
class CurvesGraphs;
class CurveStyles;
class GraphicsPoint;
class MainWindow;
class PointStyle;

// Map ordinals to corresponding point identifiers. This augments the map from point identifier to GraphicsPoint
typedef QMap<double, QString> MapOrdinalToPointIdentifier;

/// Add point and line handling to generic QGraphicsScene. The primary tasks are:
/// -# update the graphics items to stay in sync with the explicit Points in the Document
/// -# update the graphics items to stay in sync with the implicit lines between the Points, according to Document settings
///
/// This class stores points and lines as QGraphicsItems, but also maintains identifier-to-QGraphicsItems mappings to
/// the points and lines are accessible for updates (like when dragging points around and we need to update the attached lines).
class GraphicsScene : public QGraphicsScene
{
public:
  /// Single constructor.
  GraphicsScene(MainWindow *mainWindow);

  /// Add one QGraphicsItem-based object that represents one Point.
  GraphicsPoint *addPoint (const QString &identifier,
                           const PointStyle &pointStyle,
                           const QPointF &posScreen);

  /// Return a list of identifiers for the points that have moved since the last call to resetPositionHasChanged.
  QStringList positionHasChangedPointIdentifiers () const;

  /// Remove specified point
  void removePoint (const QString &identifier);

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

  /// Update curve styles after settings changed.
  void updateCurveStyles(const CurveStyles &modelCurveStyles);

private:

  /// Create internal, temporary map of ordinal to point identifier
  MapOrdinalToPointIdentifier createMapOrdinalToPointIdentifier ();

  /// Dump all important cursors
  QString dumpCursors () const;

  const QGraphicsPixmapItem *image () const;

  /// Max ordinal of the Points.
  double maxOrdinal () const;

  /// Update lines using a multi-pass algorithm.
  void updateLineMembership (CmdMediator &cmdMediator);

  /// Update graph coordinates and (where applicable) ordinals of the points after point membership has been updated, so line
  /// membership can be updated
  void updatePointGraphCoordinatesAndOrdinals (CmdMediator &cmdMediator);

  /// Update Points using a multi-pass algorithm.
  void updatePointMembership (CmdMediator &cmdMediator);

  /// Mapping for moving lines when their points get moved
  LineIdentifierToGraphicsLine m_lineIdentifierToGraphicsLine;

  /// Mapping for finding Points.
  PointIdentifierToGraphicsPoint m_pointIdentifierToGraphicsPoint;

  /// Curve name to GraphicsLinesForCurve
  GraphicsLinesForCurves m_graphicsLinesForCurves;
};

#endif // GRAPHICS_SCENE_H
