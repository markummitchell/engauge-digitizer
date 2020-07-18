/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef INACTIVE_OPACITY_H
#define INACTIVE_OPACITY_H

#include <QString>

/// Enum for opacity/alpha values used for segments that are not currently under hover. Just a few
/// values are needed since a continuous spectrum over the whole range would require multiple up/down
/// steps before any significant change could be seen
enum InactiveOpacity {
  INACTIVE_OPACITY_0,
  INACTIVE_OPACITY_32,
  INACTIVE_OPACITY_64,
  INACTIVE_OPACITY_96,
  INACTIVE_OPACITY_128,
  INACTIVE_OPACITY_160,
  INACTIVE_OPACITY_192,
  INACTIVE_OPACITY_224,
  INACTIVE_OPACITY_256                      
};

/// Default inactie opacity is not 0 so we see something, and not 255 which applies when active
const InactiveOpacity DEFAULT_INACTIVE_OPACITY_ENUM = INACTIVE_OPACITY_64;

/// Map InactiveOpacity enum to corresponding alpha value
extern int inactiveOpacityEnumToAlpha (InactiveOpacity inactiveOpacity);

/// Map InactiveOpacity enum to corresponding string value
extern QString inactiveOpacityEnumToQString (InactiveOpacity inactiveOpacity);

#endif // INACTIVE_OPACITY_H
