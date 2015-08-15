#ifndef FORMAT_COORDS_UNITS_H
#define FORMAT_COORDS_UNITS_H

class DocumentModelCoords;
class QString;
class Transformation;

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

  /// Convert unformatted numeric value to formatted string. Transformation is used to determine best resolution
  void unformattedToFormatted (double xThetaUnformatted,
                               double yRadiusUnformatted,
                               const DocumentModelCoords &modelCoords,
                               QString &xThetaFormatted,
                               QString &yRadiusFormatted,
                               const Transformation &transformation) const;
};

#endif // FORMAT_COORDS_UNITS_H
