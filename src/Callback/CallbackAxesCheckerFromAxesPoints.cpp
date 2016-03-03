/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackAxesCheckerFromAxesPoints.h"
#include "EngaugeAssert.h"

CallbackAxesCheckerFromAxesPoints::CallbackAxesCheckerFromAxesPoints()
{
}

CallbackSearchReturn CallbackAxesCheckerFromAxesPoints::callback (const QString & /* curveName */,
                                                                  const Point &point)
{
  m_points.push_back (point);

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

Points CallbackAxesCheckerFromAxesPoints::points() const
{
  return m_points;
}
