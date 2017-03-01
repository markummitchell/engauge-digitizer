/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_IDENTIFY_SCALE_BAR_POINT_IDENTIFIER_H
#define CALLBACK_IDENTIFY_SCALE_BAR_POINT_IDENTIFIER_H

#include "CallbackSearchReturn.h"
#include <QString>

class Point;

/// Callback for identifying, for the scale bar of a map, the identifier of the axis point containing the
/// scale length probably as (X,0) although the code should handle (0,Y). Other point is at the origin (0,0)
class CallbackIdentifyScaleBarPointIdentifier
{
public:
  /// Single constructor.
  CallbackIdentifyScaleBarPointIdentifier();

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Identified axis point
  QString scaleBarPointIdentifier () const;

private:

  QString m_scaleBarPointIdentifier;
};

#endif // CALLBACK_IDENTIFY_SCALE_BAR_POINT_IDENTIFIER_H
