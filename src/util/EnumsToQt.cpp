/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "EnumsToQt.h"

QColor ColorPaletteToQColor (ColorPalette color) {
  switch (color) {
    case COLOR_PALETTE_BLACK:
      return QColor (Qt::black);
      break;

    case COLOR_PALETTE_BLUE:
      return QColor (Qt::blue);
      break;

    case COLOR_PALETTE_CYAN:
      return QColor (Qt::cyan);
      break;

    case COLOR_PALETTE_GOLD:
      return QColor (255, 215, 0);
      break;

    case COLOR_PALETTE_GREEN:
      return QColor (Qt::green);
      break;

    case COLOR_PALETTE_MAGENTA:
      return QColor (255, 0, 255);
      break;

    case COLOR_PALETTE_RED:
      return QColor (Qt::red);
      break;

    case COLOR_PALETTE_YELLOW:
      return QColor (255, 255, 0);
      break;

    case COLOR_PALETTE_TRANSPARENT:
      return QColor (Qt::transparent);
      break;

    default:
      break;
  }

  ENGAUGE_ASSERT (false);
  return QColor (Qt::black);
}

QString EndianToString (QSysInfo::Endian endian)
{
  switch (endian) {
    case QSysInfo::BigEndian:
      return "BigEndian";
    case QSysInfo::LittleEndian:
      return "LittleEndian";
  }

  return "<Unknown>";
}
