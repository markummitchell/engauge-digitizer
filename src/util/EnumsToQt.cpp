/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include <QHash>
#include <QString>

static QHash<ColorPalette, QColor> colorPaletteLookupTable;
static QHash<QSysInfo::Endian, QString> endianLookupTable;

QColor ColorPaletteToQColor (ColorPalette color)
{
  if (colorPaletteLookupTable.count() == 0) {

    // Initialize
    colorPaletteLookupTable [COLOR_PALETTE_BLACK] = QColor (Qt::black);
    colorPaletteLookupTable [COLOR_PALETTE_BLUE] = QColor (Qt::blue);
    colorPaletteLookupTable [COLOR_PALETTE_CYAN] = QColor (Qt::cyan);
    colorPaletteLookupTable [COLOR_PALETTE_GOLD] = QColor (255, 215, 0);
    colorPaletteLookupTable [COLOR_PALETTE_GREEN] = QColor (Qt::green);
    colorPaletteLookupTable [COLOR_PALETTE_MAGENTA] = QColor (255, 0, 255);
    colorPaletteLookupTable [COLOR_PALETTE_RED] = QColor (Qt::red);
    colorPaletteLookupTable [COLOR_PALETTE_YELLOW] = QColor (255, 255, 0);
    colorPaletteLookupTable [COLOR_PALETTE_TRANSPARENT] = QColor (Qt::transparent);
  }

  if (colorPaletteLookupTable.contains (color)) {

    return colorPaletteLookupTable [color];

  } else {

    ENGAUGE_ASSERT (false);
    return colorPaletteLookupTable [COLOR_PALETTE_BLACK];

  }
}

QString EndianToString (QSysInfo::Endian endian)
{
  if (endianLookupTable.count() == 0) {

    // Initialize
    endianLookupTable [QSysInfo::BigEndian] = "BigEndian";
    endianLookupTable [QSysInfo::LittleEndian] = "LittleEndian";
  }

  if (endianLookupTable.contains (endian)) {

    return endianLookupTable [endian];

  } else {

    return "<Unknown>";

  }
}
