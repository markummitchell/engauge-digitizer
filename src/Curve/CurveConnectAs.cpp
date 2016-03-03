#include "CurveConnectAs.h"
#include <QObject>

QString curveConnectAsToString(CurveConnectAs curveConnectAs) {
  switch (curveConnectAs) {

  case CONNECT_AS_FUNCTION_SMOOTH:
    return QObject::tr("FunctionSmooth");

  case CONNECT_AS_FUNCTION_STRAIGHT:
    return QObject::tr("FunctionStraight");

  case CONNECT_AS_RELATION_SMOOTH:
    return QObject::tr("RelationSmooth");

  case CONNECT_AS_RELATION_STRAIGHT:
    return QObject::tr("RelationStraight");

  case CONNECT_SKIP_FOR_AXIS_CURVE:
    return QObject::tr("ConnectSkipForAxisCurve");

  default:
    return QObject::tr("Unknown");
  }
}
