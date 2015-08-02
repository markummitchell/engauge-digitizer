#include "CoordUnitsDate.h"

QString coordUnitsDateToString (CoordUnitsDate coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_DATE_DAY_MONTH_YEAR:
      return "DD/MM/YYYY";

    case COORD_UNITS_DATE_MONTH_DAY_YEAR:
      return "MM/DD/YYYY";

    case COORD_UNITS_DATE_YEAR_MONTH_DAY:
      return "YYYY/MM/DD";

    case COORD_UNITS_DATE_SKIP:
      return "";

    default:
      return "unknown";
  }
}
