/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_SCALE_H
#define COORD_SCALE_H

#include <QString>

enum CoordScale {
  COORD_SCALE_LINEAR,
  COORD_SCALE_LOG
};

extern QString coordScaleToString (CoordScale coordScale);

#endif // COORD_SCALE_H
