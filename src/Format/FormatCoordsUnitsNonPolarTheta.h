#ifndef FORMAT_COORDS_UNITS_NON_POLAR_THETA_H
#define FORMAT_COORDS_UNITS_NON_POLAR_THETA_H

#include "CoordUnitsDate.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsTime.h"
#include "FormatConstants.h"
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

  /// Convert simple unformatted number to formatted string
  QString unformattedToFormatted (double valueUnformatted,
                                  CoordUnitsNonPolarTheta coordUnits,
                                  CoordUnitsDate coordUnitsDate,
                                  CoordUnitsTime coordUnitsTime,
                                  bool isXTheta,
                                  int precisionDigitsForRawNumber = DEFAULT_PRECISION) const;
};

#endif // FORMAT_COORDS_UNITS_NON_POLAR_THETA_H
