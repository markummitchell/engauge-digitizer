#ifndef FORMAT_COORDS_UNITS_STRATEGY_POLAR_THETA_H
#define FORMAT_COORDS_UNITS_STRATEGY_POLAR_THETA_H

#include "CoordUnitsPolarTheta.h"
#include "FormatCoordsUnitsStrategyAbstractBase.h"
#include <QString>

class QLocale;
class Transformation;

/// Format conversions between unformatted and formatted for
/// CoordUnitsStrategyPolarTheta
class FormatCoordsUnitsStrategyPolarTheta
    : public FormatCoordsUnitsStrategyAbstractBase {
public:
  /// Single constructor
  FormatCoordsUnitsStrategyPolarTheta();

  /// Convert formatted string to simple unformatted number
  double formattedToUnformatted(const QString &string, const QLocale &locale,
                                CoordUnitsPolarTheta coordUnits) const;

  /// Convert simple unformatted number to formatted string
  QString unformattedToFormatted(double valueUnformatted, const QLocale &locale,
                                 CoordUnitsPolarTheta coordUnits,
                                 const Transformation &transformation,
                                 double valueUnformattedOther) const;
};

#endif // FORMAT_COORDS_UNITS_STRATEGY_POLAR_THETA_H
