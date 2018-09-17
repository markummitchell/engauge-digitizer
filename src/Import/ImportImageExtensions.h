/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef IMPORT_IMAGE_EXTENSIONS_H
#define IMPORT_IMAGE_EXTENSIONS_H

#include <QStringList>

/// Provides list of file extensions for import
class ImportImageExtensions
{
public:

  /// Single constructor
  ImportImageExtensions();

  /// File extensions for use in file dialogs
  QStringList fileExtensionsWithAsterisks () const;

  /// Return true if specified file extension is supported
  bool offers (const QString &fileExtension) const;
};

#endif // IMPORT_IMAGE_EXTENSIONS_H
