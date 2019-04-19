/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveConnectAs.h"
#include <QObject>

QString curveConnectAsToString (CurveConnectAs curveConnectAs)
{
  QString rtn;

  switch (curveConnectAs) {

    case CONNECT_AS_FUNCTION_SMOOTH:
      rtn = QObject::tr ("FunctionSmooth");
      break;

    case CONNECT_AS_FUNCTION_STRAIGHT:
      rtn = QObject::tr ("FunctionStraight");
      break;

    case CONNECT_AS_RELATION_SMOOTH:
      rtn = QObject::tr ("RelationSmooth");
      break;

    case CONNECT_AS_RELATION_STRAIGHT:
      rtn = QObject::tr ("RelationStraight");
      break;

    case CONNECT_SKIP_FOR_AXIS_CURVE:
      rtn = QObject::tr ("ConnectSkipForAxisCurve");
      break;
  }

  return rtn;
}
