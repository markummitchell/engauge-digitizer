/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_STRATEGY_ABSTRACT_BASE_H
#define GEOMETRY_STRATEGY_ABSTRACT_BASE_H

#include "Points.h"
#include <QVector>

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
};

#endif // GEOMETRY_STRATEGY_ABSTRACT_BASE_H
