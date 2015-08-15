#ifndef FORMAT_COORDS_UNITS_STRATEGY_ABSTRACT_BASE_H
#define FORMAT_COORDS_UNITS_STRATEGY_ABSTRACT_BASE_H

class Transformation;

/// Common methods for formatting strategies
class FormatCoordsUnitsStrategyAbstractBase
{
 public:
  /// Single constructor
  FormatCoordsUnitsStrategyAbstractBase();

 protected:

  /// Compute precision for outputting an unformatted value, consistent with the resolution at the point where that point lies.
  /// This algorithm causes many digits to appear when a graph's dynamic range is relatively small (like -118.4 to -118.2
  /// degrees in longitude), and fewer digits to appear when a graph's dynamic range is relatively large (like 0 to 100)
  int precisionDigitsForRawNumber (double valueUnformatted,
                                   double valueUnformattedOther,
                                   bool isXTheta,
                                   const Transformation &transformation) const;
};

#endif // FORMAT_COORDS_UNITS_STRATEGY_ABSTRACT_BASE_H
