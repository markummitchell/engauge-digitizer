#ifndef CURVE_CONNECT_AS
#define CURVE_CONNECT_AS

#include <QString>

enum CurveConnectAs {
  CONNECT_AS_FUNCTION,
  CONNECT_AS_RELATION
};

extern QString curveConnectAsToString (CurveConnectAs curveConnectAs);

#endif // CURVE_CONNECT_AS


