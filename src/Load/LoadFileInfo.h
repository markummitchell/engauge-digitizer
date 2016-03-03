/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef LOAD_FILE_INFO_H
#define LOAD_FILE_INFO_H

#include <QString>

/// Returns information about files
class LoadFileInfo
{
public:
  /// Single constructor.
  LoadFileInfo();
  virtual ~LoadFileInfo();

  /// Returns true if specified file name can be loaded as a DIG file
  bool loadsAsDigFile (const QString &urlString) const;

};

#endif // LOAD_FILE_INFO_H
