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
