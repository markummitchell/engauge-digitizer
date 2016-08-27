/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveConnectAs.h"
#include "GeometryStrategyContext.h"
#include "GeometryStrategyFunctionSmooth.h"
#include "GeometryStrategyFunctionStraight.h"
#include "GeometryStrategyRelationSmooth.h"
#include "GeometryStrategyRelationStraight.h"
#include "Transformation.h"

GeometryStrategyContext::GeometryStrategyContext()
{
  m_strategies.insert (CONNECT_AS_FUNCTION_SMOOTH  , new GeometryStrategyFunctionSmooth   ());
  m_strategies.insert (CONNECT_AS_FUNCTION_STRAIGHT, new GeometryStrategyFunctionStraight ());
  m_strategies.insert (CONNECT_AS_RELATION_SMOOTH  , new GeometryStrategyRelationSmooth   ());
  m_strategies.insert (CONNECT_AS_RELATION_STRAIGHT, new GeometryStrategyRelationStraight ());
}

GeometryStrategyContext::~GeometryStrategyContext()
{
}

void GeometryStrategyContext::calculateGeometry (const Points &points,
                                                 const DocumentModelCoords &modelCoords,
                                                 const DocumentModelGeneral &modelGeneral,
                                                 const MainWindowModel &modelMainWindow,
                                                 const Transformation &transformation,
                                                 CurveConnectAs connectAs,
                                                 QString &funcArea,
                                                 QString &polyArea,
                                                 QVector<QString> &x,
                                                 QVector<QString> &y,
                                                 QVector<QString> &distanceGraphForward,
                                                 QVector<QString> &distancePercentForward,
                                                 QVector<QString> &distanceGraphBackward,
                                                 QVector<QString> &distancePercentBackward) const
{
  if (transformation.transformIsDefined()) {

    m_strategies [connectAs]->calculateGeometry (points,
                                                 modelCoords,
                                                 modelGeneral,
                                                 modelMainWindow,
                                                 transformation,
                                                 funcArea,
                                                 polyArea,
                                                 x,
                                                 y,
                                                 distanceGraphForward,
                                                 distancePercentForward,
                                                 distanceGraphBackward,
                                                 distancePercentBackward);
  }
}
