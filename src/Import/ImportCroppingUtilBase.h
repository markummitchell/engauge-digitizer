/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef IMPORT_CROPPING_UTIL_BASE_H
#define IMPORT_CROPPING_UTIL_BASE_H

#include "ImportCropping.h"
#include <QString>

/// Utility class for import cropping options. Default option is oldest, and simplest, behavior, which is no cropping.
///
/// A complication is that a dialog for cropping is not wanted during batch-mode regression testing, so this class
/// and its subclasses offer methods for overriding the current setting during regression testing
class ImportCroppingUtilBase
{
public:
  /// Single constructor
  ImportCroppingUtilBase();

  /// Option as string for display to user
  static QString importCroppingToString (ImportCropping importCropping);

};

#endif // IMPORT_CROPPING_UTIL_BASE_H
