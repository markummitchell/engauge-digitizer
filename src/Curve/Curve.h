#ifndef CURVE_H
#define CURVE_H

#include "CallbackSearchReturn.h"
#include "ColorFilterSettings.h"
#include "CurveStyle.h"
#include "functor.h"
#include "Point.h"
#include "Points.h"
#include <QHash>
#include <QList>
#include <QString>

extern const QString AXIS_CURVE_NAME;
extern const QString DEFAULT_GRAPH_CURVE_NAME;
extern const QString DUMMY_CURVE_NAME;

class CurvesGraphs;
class QDataStream;
class QTextStream;
class QXmlStreamReader;
class QXmlStreamWriter;
class Transformation;

/// Container for one set of digitized Points
class Curve
{
public:
  /// Constructor from scratch.
  Curve(const QString &curveName,
        const ColorFilterSettings &colorFilterSettings,
        const CurveStyle &curveStyle);

  /// Constructor from serialized binary pre-version 6 file
  Curve  (QDataStream &str);

  /// Constructor for use when loading from serialized xml
  Curve (QXmlStreamReader &reader);

  /// Copy constructor. Copying a Curve only helps for making a copy, since access to any Points inside must be via functor.
  Curve (const Curve &curve);

  /// Assignment constructor.
  Curve &operator=(const Curve &curve);

  /// Add Point to this Curve.
  void addPoint (Point point);

  /// Return the color filter.
  ColorFilterSettings colorFilterSettings () const;

  /// Name of this Curve.
  QString curveName () const;

  /// Return the curve style
  CurveStyle curveStyle() const;

  /// Edit the graph coordinates of an axis point. This method does not apply to a graph point
  void editPoint (const QPointF &posGraph,
                  const QString &identifier);

  /// Export points in this Curve found in the specified point list.
  void exportToClipboard (const QHash<QString, bool> &selectedHash,
                          const Transformation &transformation,
                          QTextStream &strCsv,
                          QTextStream &strHtml,
                          CurvesGraphs &curvesGraphs) const;

  /// Apply functor to Points on Curve.
  void iterateThroughCurvePoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// Apply functor to successive Points, as line segments, on Curve. This could be a bit slow
  void iterateThroughCurveSegments (const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// Translate the position of a point by the specified distance vector.
  void movePoint (const QString &pointIdentifier,
                  const QPointF &deltaScreen);

  /// Number of points.
  int numPoints () const;

  /// Return a shallow copy of the Points.
  const Points points () const;

  /// Return the position, in graph coordinates, of the specified Point.
  QPointF positionGraph (const QString &pointIdentifier) const;

  /// Return the position, in screen coordinates, of the specified Point.
  QPointF positionScreen (const QString &pointIdentifier) const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Perform the opposite of addPointAtEnd.
  void removePoint (const QString &identifier);

  /// Serialize curve
  void saveXml(QXmlStreamWriter &writer) const;

  /// Set color filter.
  void setColorFilterSettings (const ColorFilterSettings &colorFilterSettings);

  /// Change the curve name
  void setCurveName (const QString &curveName);

  /// Set curve style.
  void setCurveStyle (const CurveStyle &curveStyle);

  /// See CurveGraphs::updatePointOrdinals. Same algorithm as GraphicsLineForCurve::updatePointOrdinalsAfterDrag, although
  /// graph coordinates of points have been updated before this is called so the graph coordinates are not updated by this method
  void updatePointOrdinals (const Transformation &transformation);

private:
  Curve();

  void loadCurvePoints(QXmlStreamReader &reader);
  void loadXml(QXmlStreamReader &reader);
  Point *pointForPointIdentifier (const QString pointIdentifier);
  void updatePointOrdinalsFunctions (const Transformation &transformation);
  void updatePointOrdinalsRelations ();

  QString m_curveName;
  Points m_points;

  ColorFilterSettings m_colorFilterSettings;
  CurveStyle m_curveStyle;
};

#endif // CURVE_H
