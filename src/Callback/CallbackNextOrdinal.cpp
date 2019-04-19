/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackNextOrdinal.h"
#include "Logger.h"
#include "Point.h"
#include <qmath.h>

CallbackNextOrdinal::CallbackNextOrdinal(const QString &curveName) :
  m_curveName (curveName),
  m_maxOrdinalUsed (0)
{
}

CallbackSearchReturn CallbackNextOrdinal::callback (const QString &curveName,
                                                    const Point &point)
{
  if (curveName == m_curveName) {
    if (point.ordinal() > m_maxOrdinalUsed) {
      m_maxOrdinalUsed = point.ordinal();
    }
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

double CallbackNextOrdinal::nextOrdinal () const
{
  int nextOrdinal = qFloor (m_maxOrdinalUsed) + 1;

  LOG4CPP_INFO_S ((*mainCat)) << "CallbackNextOrdinal::nextOrdinal"
                              << " ordinal=" << nextOrdinal;

  return nextOrdinal;
}
