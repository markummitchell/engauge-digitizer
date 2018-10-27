/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_LINES_FOR_CURVE_H
#define GRAPHICS_LINES_FOR_CURVE_H

#include "Point.h"
#include "OrdinalToGraphicsPoint.h"
#include <QGraphicsPathItem>

class CurveStyle;
class GeometryWindow;
class GraphicsPoint;
class GraphicsScene;
class LineStyle;
class PointStyle;
class QPainterPath;
class QTestStream;
class SplineDrawer;
class Transformation;

/// This class stores the GraphicsLine objects for one Curve. The container is a QMap since that container
/// maintains order by key
class GraphicsLinesForCurve : public QGraphicsPathItem
{
public:
  /// Single constructor
  GraphicsLinesForCurve(const QString &curveName);
  ~GraphicsLinesForCurve();

  /// Add new line.
  ///
  /// The GraphicsPoint arguments are not const since this line binds to the points, so dragging points also drags the lines.
  /// The ordinal is already in the GraphicsPoint as DATA_KEY_ORDINAL
  void addPoint (const QString &pointIdentifier,
                 double ordinal,
                 GraphicsPoint &point);

  ///  Get ordinal for specified identifier
  double identifierToOrdinal (const QString &identifier) const;

  /// Mark the end of addPoint calls. Remove stale lines, insert missing lines, and draw the graphics lines
  void lineMembershipPurge (const LineStyle &lineStyle,
                            SplineDrawer &splineDrawer,
                            QPainterPath &pathMultiValued,
                            LineStyle &lineMultiValued);

  /// Mark points as unwanted. Afterwards, lineMembershipPurge gets called
  void lineMembershipReset ();

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Remove the specified point. The act of deleting it will automatically remove it from the GraphicsScene
  void removePoint (double ordinal);

  /// Remove temporary point if it exists. Temporary point handling is so complicated that this method quietly
  /// allows redundant calls to this method, without complaining that the point has already been removed when called again
  void removeTemporaryPointIfExists ();

  /// Update the GraphicsScene with the specified Point from the Document. If it does not exist yet in the scene, we add it
  void updateAfterCommand (GraphicsScene &scene,
                           const PointStyle &pointStyle,
                           const Point &point,
                           GeometryWindow *geometryWindow);

  /// Update the curve style for this curve
  void updateCurveStyle (const CurveStyle &curveStyle);

  /// Calls to moveLinesWithDraggedPoint have finished so update the lines correspondingly
  void updateGraphicsLinesToMatchGraphicsPoints (const LineStyle &lineStyle,
                                                 SplineDrawer &splineDrawer,
                                                 QPainterPath &pathMultiValued,
                                                 LineStyle &lineMultiValued);

  /// Update the highlight opacity value. This may or may not affect the current display immediately depending on the state
  void updateHighlightOpacity (double highlightOpacity);

  /// See GraphicsScene::updateOrdinalsAfterDrag. Pretty much the same steps as Curve::updatePointOrdinals
  void updatePointOrdinalsAfterDrag (const LineStyle &lineStyle,
                                     const Transformation &transformation);

private:

  QPainterPath drawLinesSmooth (const LineStyle &lineStyle,
                                SplineDrawer &splineDrawer,
                                QPainterPath &pathMultiValued,
                                LineStyle &lineMultiValued);
  QPainterPath drawLinesStraight (QPainterPath &pathMultiValued);
  bool needOrdinalRenumbering () const; // True if m_graphicsPoints ordinal keys need renumbering
  void renumberOrdinals(); // Renumbers m_graphicsPoints ordinal keys

  const QString m_curveName;
  OrdinalToGraphicsPoint m_graphicsPoints;
};

#endif // GRAPHICS_LINES_FOR_CURVE_H
