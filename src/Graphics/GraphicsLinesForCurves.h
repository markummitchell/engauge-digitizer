#ifndef GRAPHICS_LINES_FOR_CURVES_H
#define GRAPHICS_LINES_FOR_CURVES_H

#include <QHash>

class CurveStyles;
class GraphicsLinesForCurve;
class GraphicsPoint;
class GraphicsScene;
class Point;
class QGraphicsItem;
class QPointF;
class QTextStream;
class Transformation;

typedef QHash<QString, GraphicsLinesForCurve*> GraphicsLinesContainer;

/// This class stores the GraphicsLinesForCurves objects, one per Curve
class GraphicsLinesForCurves
{
public:
  /// Single constructor
  GraphicsLinesForCurves();

  /// Add new point.
  /// The ordinal is already in the GraphicsPoint as DATA_KEY_ORDINAL
  void addPoint (const QString &curveName,
                 const QString &pointIdentifier,
                 GraphicsPoint &point);

  /// Add new curves and remove expired curves to match the specified list
  void addRemoveCurves (GraphicsScene &scene,
                        const QStringList &curveNames);

  /// Mark the end of addPoint calls. Remove stale lines, insert missing lines, and draw the graphics lines
  void lineMembershipPurge (const CurveStyles &curveStyles);

  /// Mark points as unwanted. Afterwards, lineMembershipPurge gets called
  void lineMembershipReset ();

  /// Debugging method for printing directly from symbolic debugger
  void print () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Remove the specified point. The act of deleting it will automatically remove it from the GraphicsScene
  void removePoint (const QString &identifier);

  /// Update the GraphicsScene with the specified Point from the Document. If it does not exist yet in the scene, we add it
  void updateAfterCommand (GraphicsScene &scene,
                           const CurveStyles &curveStyles,
                           const QString &curveName,
                           const Point &point);

  /// Calls to moveLinesWithDraggedPoint have finished so update the lines correspondingly
  void updateGraphicsLinesToMatchGraphicsPoints (const CurveStyles &curveStyles);

  /// See GraphicsScene::updateOrdinalsAfterDrag
  void updatePointOrdinalsAfterDrag (const CurveStyles &curveStyles,
                                     const Transformation &transformation);

private:

  GraphicsLinesContainer m_graphicsLinesForCurve;
};

#endif // GRAPHICS_LINES_FOR_CURVES_H
