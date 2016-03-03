/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveConnectAs.h"
#include <QObject>

QString curveConnectAsToString (CurveConnectAs curveConnectAs)
{
  switch (curveConnectAs) {

    case CONNECT_AS_FUNCTION_SMOOTH:
      return QObject::tr ("FunctionSmooth");

    case CONNECT_AS_FUNCTION_STRAIGHT:
      return QObject::tr ("FunctionStraight");

    case CONNECT_AS_RELATION_SMOOTH:
      return QObject::tr ("RelationSmooth");

    case CONNECT_AS_RELATION_STRAIGHT:
      return QObject::tr ("RelationStraight");

    case CONNECT_SKIP_FOR_AXIS_CURVE:
      return QObject::tr ("ConnectSkipForAxisCurve");

    default:
      return QObject::tr ("Unknown");
  }
}
