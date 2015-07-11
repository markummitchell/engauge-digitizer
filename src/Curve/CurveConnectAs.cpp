#include "CurveConnectAs.h"

QString curveConnectAsToString (CurveConnectAs curveConnectAs)
{
  switch (curveConnectAs) {

    case CONNECT_AS_FUNCTION_SMOOTH:
      return "FunctionSmooth";

    case CONNECT_AS_FUNCTION_STRAIGHT:
      return "FunctionStraight";

    case CONNECT_AS_RELATION_SMOOTH:
      return "RelationSmooth";

    case CONNECT_AS_RELATION_STRAIGHT:
      return "RelationStraight";

    case CONNECT_SKIP_FOR_AXIS_CURVE:
      return "ConnectSkipForAxisCurve";

    default:
      return "Unknown";
  }
}
