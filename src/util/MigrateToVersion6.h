/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MIGRATE_TO_VERSION_6_H
#define MIGRATE_TO_VERSION_6_H

#include "ColorPalette.h"
#include "CurveConnectAs.h"
#include "PointShape.h"

/// Converts old (=pre version 6) enums to new (=version 6) enums, for reading of old document files
class MigrateToVersion6
{
 public:
  /// Single constructor
  MigrateToVersion6 ();

  /// Color from color palette
  ColorPalette colorPalette (int preVersion6) const;

  /// Line drawn between points
  CurveConnectAs curveConnectAs (int preVersion6) const;

  /// Point shape
  PointShape pointShape (int preVersion6) const;

  /// Point radius
  int pointRadius (int preVersion6) const;
};

#endif // MIGRATE_TO_VERSION_6_H
