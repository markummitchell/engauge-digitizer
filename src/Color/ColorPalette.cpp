/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorPalette.h"

QString colorPaletteToString (ColorPalette colorPalette)
{
  switch (colorPalette) {
    case COLOR_PALETTE_BLACK:
      return "Black";

    case COLOR_PALETTE_BLUE:
      return "Blue";

    case COLOR_PALETTE_CYAN:
      return "Cyan";

    case COLOR_PALETTE_GOLD:
      return "Gold";

    case COLOR_PALETTE_GREEN:
      return "Green";

    case COLOR_PALETTE_MAGENTA:
      return "Magenta";

    case COLOR_PALETTE_RED:
      return "Red";

    case COLOR_PALETTE_TRANSPARENT:
      return "Transparent";

    case COLOR_PALETTE_YELLOW:
      return "Yellow";

    default:
      return "Unknown";
  }
}
