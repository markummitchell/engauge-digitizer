/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_STRATEGY_ABSTRACT_BASE_H
#define GEOMETRY_STRATEGY_ABSTRACT_BASE_H

#include "Points.h"
#include <QPolygonF>
#include <QVector>

class DocumentModelCoords;
class DocumentModelGeneral;
class MainWindowModel;
class QPointF;
class Transformation;

/// Base class for all geometry strategies. Each strategy computes geometry parameters according to the curve's settings.
///
/// The numbering for the strategies is specified as the CurveConnectAs enumeration
class GeometryStrategyAbstractBase
{
public:
  /// Single constructor.
  GeometryStrategyAbstractBase();
  virtual ~GeometryStrategyAbstractBase ();

  /// Calculate geometry parameters
  virtual void calculateGeometry (const Points &points,
                                  const DocumentModelCoords &modelCoords,
                                  const DocumentModelGeneral &modelGeneral,
                                  const MainWindowModel &modelMainWindow,
                                  const Transformation &transformation,
                                  QString &funcArea,
                                  QString &polyArea,
                                  QVector<QString> &x,
                                  QVector<QString> &y,
                                  QVector<QString> &distanceGraphForward,
                                  QVector<QString> &distancePercentForward,
                                  QVector<QString> &distanceGraphBackward,
                                  QVector<QString> &distancePercentBackward) const = 0;

protected:

  /// Convert screen positions to graph positions
  void calculatePositionsGraph (const Points &points,
                                const Transformation &transformation,
                                QVector<QPointF> &positionsGraph) const;

  /// Use trapezoidal approximation to compute area under the function. Does not apply to relation
  double functionArea (const QVector<QPointF> &positionsGraph) const;

  /// Insert the specified number of subintervals into each interval. For straight curves subintervalsPerInterval=1 so the
  /// linearity is maintained, and for smooth curves subintervalsPerInterval>1 so the geometry calculations take into account
  /// the curvature(s) of the line
  void insertSubintervalsAndLoadDistances (int subintervalsPerInterval,
                                           const QVector<QPointF> &positionsGraph,
                                           QVector<QPointF> &positionsGraphWithSubintervals,
                                           QVector<QString> &distanceGraphForward,
                                           QVector<QString> &distancePercentForward,
                                           QVector<QString> &distanceGraphBackward,
                                           QVector<QString> &distancePercentBackward) const;

  /// Load x and y coordinate vectors
  void loadXY (const QVector<QPointF> &positionsGraph,
               const DocumentModelCoords &modelCoords,
               const DocumentModelGeneral &modelGeneral,
               const MainWindowModel &modelMainWindow,
               const Transformation &transformation,
               QVector<QString> &x,
               QVector<QString> &y) const;

  /// Area in polygon using Shoelace formula, which only works if polygon is simply connected. We do not
  /// check to see if the polygon is simply connected since that would be (1) slow and (2) much work
  double polygonAreaForSimplyConnected (const QVector<QPointF> &points) const;

};

#endif // GEOMETRY_STRATEGY_ABSTRACT_BASE_H
