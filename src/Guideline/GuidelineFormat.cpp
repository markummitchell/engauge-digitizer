/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineFormat.h"
#include <QColor>

GuidelineFormat::GuidelineFormat()
{
}

GuidelineFormat::~GuidelineFormat()
{
}

QColor GuidelineFormat::colorDeployedHover () const
{
  QColor color (Qt::green);
  color.setAlphaF (0.8);

  return color;
}

QColor GuidelineFormat::colorDeployedNonHover () const
{
  return QColor (Qt::green);
}

QColor GuidelineFormat::colorHidden () const
{
  return QColor (Qt::transparent);
}

double GuidelineFormat::lineWidthHover () const
{
  return 2.0; // Wide so easy to see and click on
}

double GuidelineFormat::lineWidthNonHover () const
{
  return 0.8; // Narrow for precision
}
