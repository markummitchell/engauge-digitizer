#include "DlgValidatorAbstract.h"
#include "DlgValidatorDateTime.h"
#include "DlgValidatorDegreesMinutesSeconds.h"
#include "DlgValidatorFactory.h"
#include "DlgValidatorNumber.h"
#include "Logger.h"

DlgValidatorFactory::DlgValidatorFactory()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::DlgValidatorFactory";
}

DlgValidatorAbstract *DlgValidatorFactory::createWithNonPolar (CoordScale coordScale,
                                                               CoordUnitsNonPolarTheta coordUnits,
                                                               CoordUnitsDate coordUnitsDate,
                                                               CoordUnitsTime coordUnitsTime) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::createWithNonPolar";

  switch (coordUnits) {
    case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
      return new DlgValidatorDateTime (coordScale,
                                       coordUnitsDate,
                                       coordUnitsTime);

    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      return new DlgValidatorDegreesMinutesSeconds (coordScale);

    case COORD_UNITS_NON_POLAR_THETA_NUMBER:
      return new DlgValidatorNumber(coordScale);

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "DlgValidatorFactory::createWithNonPolar";
      exit (-1);
  }
}

DlgValidatorAbstract *DlgValidatorFactory::createWithPolar (CoordScale coordScale,
                                                            CoordUnitsPolarTheta coordUnits) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::createWithPolar";

  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      return new DlgValidatorDegreesMinutesSeconds (coordScale);

    case COORD_UNITS_POLAR_THETA_GRADIANS:
    case COORD_UNITS_POLAR_THETA_RADIANS:
    case COORD_UNITS_POLAR_THETA_TURNS:
      return new DlgValidatorNumber (coordScale);

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "DlgValidatorFactory::createWithNonPolar";
      exit (-1);
  }
}

DlgValidatorAbstract *DlgValidatorFactory::createCartesianOrPolarWithNonPolarPolar (CoordScale coordScale,
                                                                                    bool isCartesian,
                                                                                    CoordUnitsNonPolarTheta coordUnitsCartesian,
                                                                                    CoordUnitsNonPolarTheta coordUnitsPolar,
                                                                                    CoordUnitsDate coordUnitsDate,
                                                                                    CoordUnitsTime coordUnitsTime) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::createCartesianOrPolarWithNonPolarPolar";

  if (isCartesian) {
    return createWithNonPolar (coordScale,
                               coordUnitsCartesian,
                               coordUnitsDate,
                               coordUnitsTime);
  } else {
    return createWithNonPolar (coordScale,
                               coordUnitsPolar,
                               coordUnitsDate,
                               coordUnitsTime);
  }
}

DlgValidatorAbstract *DlgValidatorFactory::createCartesianOrPolarWithPolarPolar (CoordScale coordScale,
                                                                                 bool isCartesian,
                                                                                 CoordUnitsNonPolarTheta coordUnitsCartesian,
                                                                                 CoordUnitsPolarTheta coordUnitsPolar,
                                                                                 CoordUnitsDate coordUnitsDate,
                                                                                 CoordUnitsTime coordUnitsTime) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::createCartesianOrPolarWithPolarPolar";

  if (isCartesian) {
    return createWithNonPolar (coordScale,
                               coordUnitsCartesian,
                               coordUnitsDate,
                               coordUnitsTime);
  } else {
    return createWithPolar (coordScale,
                            coordUnitsPolar);
  }
}
