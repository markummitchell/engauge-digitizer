/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineIdentifierGenerator.h"

int GuidelineIdentifierGenerator::m_count = 0;

GuidelineIdentifierGenerator::GuidelineIdentifierGenerator()
{
}

QString GuidelineIdentifierGenerator::next ()
{
  return QString ("guideline%1").arg (m_count++);
}
