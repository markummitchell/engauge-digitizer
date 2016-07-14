/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURVES_GRAPHS_H
#define CURVES_GRAPHS_H

#include "CallbackSearchReturn.h"
#include "Curve.h"
#include <QList>
#include <QStringList>

class CurveStyles;
class Point;
class QXmlStreamReader;
class QXmlStreamWriter;
class Transformation;

typedef QList<Curve> CurveList;

/// Container for all graph curves. The axes point curve is external to this class.
class CurvesGraphs
{
public:
  CurvesGraphs();

  /// Append new graph Curve to end of Curve list.
  void addGraphCurveAtEnd (Curve curve);

  /// Append new Point to the specified Curve.
  void addPoint (const Point &point);

  /// Return the axis or graph curve for the specified curve name.
  Curve *curveForCurveName (const QString &curveName);

  /// Return the axis or graph curve for the specified curve name.
  const Curve *curveForCurveName (const QString &curveName) const;

  /// List of graph curve names.
  QStringList curvesGraphsNames () const;

  /// Point count.
  int curvesGraphsNumPoints (const QString &curveName) const;

  /// Set the x and/or y coordinate values of the specified points
  void editPointGraph (bool isX,
                       bool isY,
                       double x,
                       double y,
                       const QStringList &identifiers,
                       const Transformation &transformation);

  /// Apply functor to Points in the specified axis or graph Curve.
  void iterateThroughCurvePoints (const QString &curveNameWanted,
                                  const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// Apply functor to segments on the specified axis or graph Curve.
  void iterateThroughCurveSegments (const QString &curveNameWanted,
                                    const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// Apply functor to Points on all of the Curves.
  void iterateThroughCurvesPoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// Apply functor to Points on all of the Curves.
  void iterateThroughCurvesPoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// Load from serialized binary pre-version 6 file
  void loadPreVersion6 (QDataStream &str);

  /// Load from serialized xml post-version 5 file
  void loadXml(QXmlStreamReader &reader);

  /// Current number of graphs curves.
  int numCurves () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Remove the Point from its Curve.
  void removePoint (const QString &pointIdentifier);

  /// Serialize curves
  void saveXml(QXmlStreamWriter &writer) const;

  /// Update point ordinals to be consistent with their CurveStyle and x/theta coordinate
  void updatePointOrdinals (const Transformation &transformation);

private:

  CurveList m_curvesGraphs;
};

#endif // CURVES_GRAPHS_H
