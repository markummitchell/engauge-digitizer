#ifndef FORMAT_COORDS_UNITS_POLAR_THETA_H
#define FORMAT_COORDS_UNITS_POLAR_THETA_H

#include "CoordUnitsPolarTheta.h"
#include <QString>

/// Format conversions between unformatted and formatted for CoordUnitsPolarTheta
class FormatCoordsUnitsPolarTheta {
 public:
  /// Single constructor
  FormatCoordsUnitsPolarTheta();

  /// Convert formatted string to simple unformatted number
  double formattedToUnformatted (const QString &string,
                                 CoordUnitsPolarTheta coordUnits) const;

  /// Convert simple unformatted number to formatted string. Pointer is null if value is unspecified
  QString unformattedToFormatted (const double *value,
                                  CoordUnitsPolarTheta coordUnits) const;
};

#endif // FORMAT_COORDS_UNITS_POLAR_THETA_H
