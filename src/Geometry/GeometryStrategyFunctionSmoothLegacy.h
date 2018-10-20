/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_STRATEGY_FUNCTION_SMOOTH_LEGACY_H
#define GEOMETRY_STRATEGY_FUNCTION_SMOOTH_LEGACY_H

#include "GeometryStrategyAbstractBase.h"
#include <QVector>

class Transformation;

/// Calculate for line through the points that is smoothly connected as a function, using less reliable legacy method
class GeometryStrategyFunctionSmoothLegacy : public GeometryStrategyAbstractBase
{
public:
  /// Single constructor.
  GeometryStrategyFunctionSmoothLegacy();
  virtual ~GeometryStrategyFunctionSmoothLegacy ();

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
                                  QVector<QString> &distancePercentBackward) const;

};

#endif // GEOMETRY_STRATEGY_FUNCTION_SMOOTH_LEGACY_H
