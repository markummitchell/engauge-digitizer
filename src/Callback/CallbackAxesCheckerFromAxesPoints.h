/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_AXES_CHECKER_FROM_AXES_POINTS_H
#define CALLBACK_AXES_CHECKER_FROM_AXES_POINTS_H

#include "CallbackSearchReturn.h"
#include "Point.h"
#include "Points.h"
#include <QString>
#include <QList>

/// Callback for positioning the axes indicator according to the axes points
class CallbackAxesCheckerFromAxesPoints
{
public:
  /// Single constructor.
  CallbackAxesCheckerFromAxesPoints();

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Return the collected points as a polygon, in screen coordinates.
  Points points () const;

private:

  Points m_points;
};

#endif // CALLBACK_AXES_CHECKER_FROM_AXES_POINTS_H
