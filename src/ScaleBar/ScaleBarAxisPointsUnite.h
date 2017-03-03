/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SCALE_BAR_AXIS_POINTS_UNITE_H
#define SCALE_BAR_AXIS_POINTS_UNITE_H

#include "DocumentAxesPointsRequired.h"
#include <QStringList>

class CmdMediator;

/// Given a set of point identifiers, if a map is in effect (with its two axis endpoints) then both
/// axis points must be handled as a unit. For that to happen, for maps this class looks for one axis
/// endpoint in a point identifier list, and if just one is in the list then the other is also added
///
/// This class has absolutely no effect (=noop) when a map is not in effect, or a map is in effect but
/// zero or both axis endpoints are in the list
class ScaleBarAxisPointsUnite
{ 
public:
  /// Single constructor.
  ScaleBarAxisPointsUnite ();
  ~ScaleBarAxisPointsUnite ();

  /// Add 
  QStringList unite (CmdMediator *cmdMediator,
                     const QStringList &pointIdentifiersIn) const;

private:

  QStringList axisPointIdentifiers (CmdMediator *cmdMediator) const;
};

#endif // SCALE_BAR_AXIS_POINTS_UNITE_H
