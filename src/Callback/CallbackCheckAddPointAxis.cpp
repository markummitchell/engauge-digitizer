/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackCheckAddPointAxis.h"
#include "Curve.h"
#include "Point.h"

extern const QString AXIS_CURVE_NAME;

CallbackCheckAddPointAxis::CallbackCheckAddPointAxis(const DocumentModelCoords &modelCoords,
                                                     const QPointF &posScreen,
                                                     const QPointF &posGraph,
                                                     DocumentAxesPointsRequired documentAxesPointsRequired,
                                                     bool isXOnly) :
  CallbackAxisPointsAbstract (modelCoords,
                              documentAxesPointsRequired)
{
  // Insert an extra Point as if it already was in the axes curve. This is done before iterating rather
  // than after since there is no safe place to do this afterwards (isError and errorMessage may be called more than once)
  Point point (AXIS_CURVE_NAME,
               posScreen,
               posGraph,
               isXOnly);

  callback (AXIS_CURVE_NAME,
            point);
}

bool CallbackCheckAddPointAxis::isError () const
{
  return CallbackAxisPointsAbstract::isError ();
}

QString CallbackCheckAddPointAxis::errorMessage () const
{
  return CallbackAxisPointsAbstract::errorMessage ();
}
