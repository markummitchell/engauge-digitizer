/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackCheckEditPointAxis.h"
#include "Point.h"

CallbackCheckEditPointAxis::CallbackCheckEditPointAxis(const DocumentModelCoords &modelCoords,
                                                       const QString &pointIdentifier,
                                                       const QPointF &posScreen,
                                                       const QPointF &posGraph,
                                                       DocumentAxesPointsRequired documentAxesPointsRequired) :
  CallbackAxisPointsAbstract (modelCoords,
                              pointIdentifier,
                              posScreen,
                              posGraph,
                              documentAxesPointsRequired)
{
}

bool CallbackCheckEditPointAxis::isError () const
{
  return CallbackAxisPointsAbstract::isError ();
}

QString CallbackCheckEditPointAxis::errorMessage () const
{
  return CallbackAxisPointsAbstract::errorMessage ();
}
