/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EnumsToQt.h"
#include "GuidelineFormat.h"
#include <QColor>

GuidelineFormat::GuidelineFormat(ColorPalette color) :
  m_color (ColorPaletteToQColor (color))
{
}

GuidelineFormat::~GuidelineFormat()
{
}

QColor GuidelineFormat::colorDeployedHover () const
{
  QColor color (m_color);
  color.setAlphaF (0.8);

  return color;
}

QColor GuidelineFormat::colorDeployedNonHover () const
{
  return m_color;
}

QColor GuidelineFormat::colorHidden () const
{
  return QColor (Qt::transparent);
}

double GuidelineFormat::lineWidthHover () const
{
  return 5.0; // Wide so easy to see and click on
}

double GuidelineFormat::lineWidthNonHover () const
{
  return 0.8; // Narrow for precision
}

