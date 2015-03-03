#include "CurveConnectAs.h"

QString curveConnectAsToString (CurveConnectAs curveConnectAs)
{
  switch (curveConnectAs) {
    case CONNECT_AS_FUNCTION:
      return "Function";

    case CONNECT_AS_RELATION:
      return "Relation";

    default:
      return "Unknown";
  }
}
