/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_REMOVE_POINTS_IN_CURVES_GRAPHS_H
#define CALLBACK_REMOVE_POINTS_IN_CURVES_GRAPHS_H

#include "CallbackSearchReturn.h"

class CoordSystem;
class Point;
class QString;

/// Callback that is used when iterating through a read-only CurvesGraphs to remove corresponding points in Document.
class CallbackRemovePointsInCurvesGraphs
{
public:
  /// Single constructor.
  CallbackRemovePointsInCurvesGraphs(CoordSystem &coordSystem);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

private:
  CallbackRemovePointsInCurvesGraphs ();

  CoordSystem &m_coordSystem;
};

#endif // CALLBACK_REMOVE_POINTS_IN_CURVES_GRAPHS_H
