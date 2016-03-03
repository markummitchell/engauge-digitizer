/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_SYMBOL_H
#define COORD_SYMBOL_H

/// Mathematical symbols for degrees, minutes, seconds input/outputs from/to users

#include <QString>

extern const int COORD_SYMBOL_DEGREES;
extern const int COORD_SYMBOL_MINUTES_PRIME;
extern const int COORD_SYMBOL_MINUTES_APOSTROPHE;
extern const int COORD_SYMBOL_SECONDS_DOUBLE_PRIME;
extern const int COORD_SYMBOL_SECONDS_QUOTATIONS;

extern const QChar THETA;

extern const QString POLAR_UNITS_DEGREES;
extern const QString POLAR_UNITS_DEGREES_MINUTES;
extern const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS;
extern const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS_NSEW;
extern const QString POLAR_UNITS_GRADIANS;
extern const QString POLAR_UNITS_RADIANS;
extern const QString POLAR_UNITS_TURNS;

#endif // COORD_SYMBOL_H

