/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgValidatorAbstract.h"
#include "DlgValidatorDateTime.h"
#include "DlgValidatorDegreesMinutesSeconds.h"
#include "DlgValidatorFactory.h"
#include "DlgValidatorNumber.h"
#include "Logger.h"
#include <QLocale>

DlgValidatorFactory::DlgValidatorFactory()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::DlgValidatorFactory";
}

DlgValidatorAbstract *DlgValidatorFactory::createCartesianOrPolarWithNonPolarPolar (CoordScale coordScale,
                                                                                    bool isCartesian,
                                                                                    CoordUnitsNonPolarTheta coordUnitsCartesian,
                                                                                    CoordUnitsNonPolarTheta coordUnitsPolar,
                                                                                    CoordUnitsDate coordUnitsDate,
                                                                                    CoordUnitsTime coordUnitsTime,
                                                                                    const QLocale &locale) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::createCartesianOrPolarWithNonPolarPolar";

  if (isCartesian) {
    return createWithNonPolar (coordScale,
                               coordUnitsCartesian,
                               coordUnitsDate,
                               coordUnitsTime,
                               locale);
  } else {
    return createWithNonPolar (coordScale,
                               coordUnitsPolar,
                               coordUnitsDate,
                               coordUnitsTime,
                               locale);
  }
}

DlgValidatorAbstract *DlgValidatorFactory::createCartesianOrPolarWithPolarPolar (CoordScale coordScale,
                                                                                 bool isCartesian,
                                                                                 CoordUnitsNonPolarTheta coordUnitsCartesian,
                                                                                 CoordUnitsPolarTheta coordUnitsPolar,
                                                                                 CoordUnitsDate coordUnitsDate,
                                                                                 CoordUnitsTime coordUnitsTime,
                                                                                 const QLocale &locale) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorFactory::createCartesianOrPolarWithPolarPolar";

  if (isCartesian) {
    return createWithNonPolar (coordScale,
                               coordUnitsCartesian,
                               coordUnitsDate,
                               coordUnitsTime,
                               locale);
  } else {
    return createWithPolar (coordScale,
                            coordUnitsPolar,
                            locale);
  }
}

DlgValidatorAbstract *DlgValidatorFactory::createWithNonPolar (CoordScale coordScale,
                                                               CoordUnitsNonPolarTheta coordUnits,
                                                               CoordUnitsDate coordUnitsDate,
                                                               CoordUnitsTime coordUnitsTime,
                                                               const QLocale &locale) const
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
      return new DlgValidatorNumber(coordScale,
                                    locale);

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "DlgValidatorFactory::createWithNonPolar";
      exit (-1);
  }
}

DlgValidatorAbstract *DlgValidatorFactory::createWithPolar (CoordScale coordScale,
                                                            CoordUnitsPolarTheta coordUnits,
                                                            const QLocale &locale) const
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
      return new DlgValidatorNumber (coordScale,
                                     locale);

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "DlgValidatorFactory::createWithNonPolar";
      exit (-1);
  }
}
