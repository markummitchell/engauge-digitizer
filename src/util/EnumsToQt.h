/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef ENUMS_TO_QT_H
#define ENUMS_TO_QT_H

#include "ColorPalette.h"
#include <QColor>
#include <QString>
#include <QSysInfo>
#include <QXmlStreamReader>

extern QColor ColorPaletteToQColor (ColorPalette color);
extern QString EndianToString (QSysInfo::Endian endian);

#endif // ENUMS_TO_QT_H
