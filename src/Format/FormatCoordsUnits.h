/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FORMAT_COORDS_UNITS_H
#define FORMAT_COORDS_UNITS_H

class DocumentModelCoords;
class MainWindowModel;
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
                               const MainWindowModel &mainWindowModel,
                               double &xThetaUnformatted,
                               double &yRadiusUnformatted) const;

  /// Convert unformatted numeric value to formatted string. Transformation is used to determine best resolution
  void unformattedToFormatted (double xThetaUnformatted,
                               double yRadiusUnformatted,
                               const DocumentModelCoords &modelCoords,
                               const MainWindowModel &mainWindowModel,
                               QString &xThetaFormatted,
                               QString &yRadiusFormatted,
                               const Transformation &transformation) const;
};

#endif // FORMAT_COORDS_UNITS_H
