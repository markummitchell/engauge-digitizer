/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_VALIDATOR_FACTORY_H
#define DLG_VALIDATOR_FACTORY_H

#include "CoordScale.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"

class DlgValidatorAbstract;
class QLocale;

/// Validator factory
class DlgValidatorFactory
{
public:
  /// Single constructor
  DlgValidatorFactory();

  /// Factory method for generating validators for either cartesian or polar case, when polar format is specified by CoordUnitsNonPolarTheta
  DlgValidatorAbstract *createCartesianOrPolarWithNonPolarPolar (CoordScale coordScale,
                                                                 bool isCartesian,
                                                                 CoordUnitsNonPolarTheta coordUnitsCartesian,
                                                                 CoordUnitsNonPolarTheta coordUnitsPolar,
                                                                 CoordUnitsDate coordUnitsDate,
                                                                 CoordUnitsTime coordUnitsTime,
                                                                 const QLocale &locale) const;

  /// Factory method for generating validators for either cartesian or polar case, when polar format is specified by CoordUnitsPolarTheta
  DlgValidatorAbstract *createCartesianOrPolarWithPolarPolar (CoordScale coordScale,
                                                              bool isCartesian,
                                                              CoordUnitsNonPolarTheta coordUnitsCartesian,
                                                              CoordUnitsPolarTheta coordUnitsPolar,
                                                              CoordUnitsDate coordUnitsDate,
                                                              CoordUnitsTime coordUnitsTime,
                                                              const QLocale &locale) const;

  /// Factory method for generating validators when cartesian/polar case handling is handled externally, and format is specified by CoordUnitsNonPolarTheta
  DlgValidatorAbstract *createWithNonPolar (CoordScale coordScale,
                                            CoordUnitsNonPolarTheta coordUnits,
                                            CoordUnitsDate coordUnitsDate,
                                            CoordUnitsTime coordUnitsTime,
                                            const QLocale &locale) const;

  /// Factory method for generating validators when cartesian/polar case handling is handled externally, and format is specified by CoordUnitsNonPolarTheta
  DlgValidatorAbstract *createWithPolar (CoordScale coordScale,
                                         CoordUnitsPolarTheta coordUnits,
                                         const QLocale &locale) const;
};

#endif // DLG_VALIDATOR_FACTORY_H
