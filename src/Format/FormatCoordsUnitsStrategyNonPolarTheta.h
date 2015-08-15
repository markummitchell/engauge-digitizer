#ifndef FORMAT_COORDS_UNITS_STRATEGY_NON_POLAR_THETA_H
#define FORMAT_COORDS_UNITS_STRATEGY_NON_POLAR_THETA_H

#include "CoordUnitsDate.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsTime.h"
#include "FormatCoordsUnitsStrategyAbstractBase.h"
#include <QString>

class Transformation;

/// Format conversions between unformatted and formatted for CoordUnitsNonPolarTheta
class FormatCoordsUnitsStrategyNonPolarTheta : public FormatCoordsUnitsStrategyAbstractBase
{
 public:
  /// Single constructor
  FormatCoordsUnitsStrategyNonPolarTheta();

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
                                  const Transformation &transformation,
                                  double valueUnformattedOther) const;

};

#endif // FORMAT_COORDS_UNITS_STRATEGY_NON_POLAR_THETA_H
