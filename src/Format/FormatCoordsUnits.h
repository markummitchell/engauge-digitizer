#ifndef FORMAT_COORDS_UNITS_H
#define FORMAT_COORDS_UNITS_H

#include "FormatConstants.h"

class DocumentModelCoords;
class QString;

/// Highest-level wrapper around other Formats classes
class FormatCoordsUnits {
 public:
  /// Single constructor
  FormatCoordsUnits ();

  /// Convert formatted string to unformatted numeric value
  void formattedToUnformatted (const QString &xThetaFormatted,
                               const QString &yRadiusFormatted,
                               const DocumentModelCoords &modelCoords,
                               double &xThetaUnformatted,
                               double &yRadiusUnformatted) const;

  /// Convert unformatted numeric value to formatted string
  void unformattedToFormatted (double xThetaUnformatted,
                               double yRadiusUnformatted,
                               const DocumentModelCoords &modelCoords,
                               QString &xThetaFormatted,
                               QString &yRadiusFormatted,
                               int precisionDigitsForRawNumbers = DEFAULT_PRECISION) const;
};

#endif // FORMAT_COORDS_UNITS_H
