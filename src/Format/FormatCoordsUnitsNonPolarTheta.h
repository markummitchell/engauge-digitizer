#ifndef FORMAT_COORDS_UNITS_NON_POLAR_THETA_H
#define FORMAT_COORDS_UNITS_NON_POLAR_THETA_H

#include "CoordUnitsDate.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsTime.h"
#include <QString>

/// Format conversions between unformatted and formatted for CoordUnitsNonPolarTheta
class FormatCoordsUnitsNonPolarTheta {
 public:
  /// Single constructor
  FormatCoordsUnitsNonPolarTheta();

  /// Convert formatted string to simple unformatted number
  double formattedToUnformatted (const QString &string,
                                 CoordUnitsNonPolarTheta coordUnits,
                                 CoordUnitsDate coordUnitsDate,
                                 CoordUnitsTime coordUnitsTime) const;

  /// Convert simple unformatted number to formatted string. Pointer is null if value is unspecified
  QString unformattedToFormatted (const double *value,
                                  CoordUnitsNonPolarTheta coordUnits,
                                  CoordUnitsDate coordUnitsDate,
                                  CoordUnitsTime coordUnitsTime,
                                  bool isXTheta) const;
};

#endif // FORMAT_COORDS_UNITS_NON_POLAR_THETA_H
