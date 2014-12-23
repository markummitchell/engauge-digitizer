#ifndef CURVE_H
#define CURVE_H

#include "CallbackSearchReturn.h"
#include "functor.h"
#include "LineStyle.h"
#include "Point.h"
#include "PointStyle.h"
#include <QHash>
#include <QList>
#include <QString>

typedef QList<Point> Points;

extern const QString AXIS_CURVE_NAME;
extern const QString DEFAULT_GRAPH_CURVE_NAME;

class CurvesGraphs;
class QTextStream;
class Transformation;

/// Container for one set of digitized Points
class Curve
{
public:
  /// Constructor from scratch.
  Curve(const QString &curveName,
        const LineStyle &lineStyle,
        const PointStyle &pointStyle);

  /// Copy constructor. Copying a Curve only helps for making a copy, since access to any Points inside must be via functor.
  Curve (const Curve &curve);

  /// Assignment constructor.
  Curve &operator=(const Curve &curve);

  /// Add Point to this Curve.
  void addPoint (Point point);

  /// Apply transformation that is stored and updated externally.
  void applyTransformation (const Transformation &transformation);

  /// Name of this Curve.
  QString curveName () const;

  /// Edit the graph coordinates of an axis point. This method does not apply to a graph point
  void editPoint (const QPointF &posGraph,
                  const QString &identifier);

  /// Export points in this Curve found in the specified point list.
  void exportToClipboard (const QHash<QString, bool> &selectedHash,
                          bool transformIsDefined,
                          QTextStream &strCsv,
                          QTextStream &strHtml,
                          CurvesGraphs &curvesGraphs) const;

  /// Apply functor to Points on Curve.
  void iterateThroughCurvePoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// Return the line style.
  LineStyle lineStyle () const;

  /// Translate the position of a point by the specified distance vector.
  void movePoint (const QString &pointIdentifier,
                  const QPointF &deltaScreen);

  /// Number of points.
  int numPoints () const;

  /// Return the position, in graph coordinates, of the specified Point.
  QPointF positionGraph (const QString &pointIdentifier) const;

  /// Return the position, in screen coordinates, of the specified Point.
  QPointF positionScreen (const QString &pointIdentifier) const;

  /// Return a shallow copy of the Points.
  const Points points () const;

  /// Return the point style.
  PointStyle pointStyle () const;

  /// Perform the opposite of addPointAtEnd.
  void removePoint (const QString &identifier);

  /// Change the curve name
  void setCurveName (const QString &curveName);

  /// Set line style.
  void setLineStyle (const LineStyle &lineStyle);

  /// Set point style.
  void setPointStyle (const PointStyle &pointStyle);

private:
  Curve();

  Point *pointForPointIdentifier (const QString pointIdentifier);

  QString m_curveName;
  Points m_points;

  LineStyle m_lineStyle;
  PointStyle m_pointStyle;
};

#endif // CURVE_H
