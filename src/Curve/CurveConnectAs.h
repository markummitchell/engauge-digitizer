/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURVE_CONNECT_AS
#define CURVE_CONNECT_AS

#include <QString>

enum CurveConnectAs {
  CONNECT_AS_FUNCTION_SMOOTH,
  CONNECT_AS_FUNCTION_STRAIGHT,
  CONNECT_AS_RELATION_SMOOTH,
  CONNECT_AS_RELATION_STRAIGHT,
  CONNECT_SKIP_FOR_AXIS_CURVE
};

extern QString curveConnectAsToString (CurveConnectAs curveConnectAs);

#endif // CURVE_CONNECT_AS


