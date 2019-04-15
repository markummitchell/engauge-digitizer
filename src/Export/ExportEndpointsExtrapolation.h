/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_ENDPOINTS_EXTRAPOLATION_H
#define EXPORT_ENDPOINTS_EXTRAPOLATION_H

#include <QString>

// It would not help to add an option to stay within endpoints but also perform
// an extra step to add the endpoints themselves. This is explained for each case:
// 1) First curve - x values are exactly the x values extracted from the first curve, so
//    no other curves should contribute x values
// 2) All curves - Every x value is already included
// 3) Evenly spaced - The endpoints would not be evenly spaced
// 4) Grid lines - The endpoints would not be on the grid lines
// 5) Raw - x values would already be included
enum ExportEndpointsExtrapolation {
  EXPORT_ENDPOINTS_EXTRAPOLATION_STAY_WITHIN,
  EXPORT_ENDPOINTS_EXTRAPOLATION_EXTRAPOLATE_OUTSIDE
};

extern QString exportEndpointsExtrapolationToString (ExportEndpointsExtrapolation exportEndpointsExtrapolation);

#endif // EXPORT_ENDPOINTS_EXTRAPOLATION_H
