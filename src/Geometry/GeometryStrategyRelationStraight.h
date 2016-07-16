/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_STRATEGY_RELATION_STRAIGHT_H
#define GEOMETRY_STRATEGY_RELATION_STRAIGHT_H

#include "GeometryStrategyAbstractBase.h"
#include <QVector>

class Transformation;

/// Calculate for line through the points that is straightly connected as a relation
class GeometryStrategyRelationStraight : public GeometryStrategyAbstractBase
{
public:
  /// Single constructor.
  GeometryStrategyRelationStraight();
  virtual ~GeometryStrategyRelationStraight ();

  /// Calculate geometry parameters
  virtual void calculateGeometry (const Points &points,
                                  const DocumentModelCoords &modelCoords,
                                  const MainWindowModel &modelMainWindow,
                                  const Transformation &transformation,
                                  QString &funcArea,
                                  QString &polyArea,
                                  QVector<QString> &x,
                                  QVector<QString> &y,
                                  QVector<QString> &distanceGraphForward,
                                  QVector<QString> &distancePercentForward,
                                  QVector<QString> &distanceGraphBackward,
                                  QVector<QString> &distancePercentBackward) const;

};

#endif // GEOMETRY_STRATEGY_RELATION_STRAIGHT_H
