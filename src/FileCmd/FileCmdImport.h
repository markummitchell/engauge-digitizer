/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FILE_CMD_IMPORT_H
#define FILE_CMD_IMPORT_H

#include "FileCmdAbstract.h"

class QXmlStreamReader;

/// Command for importing a file
class FileCmdImport : public FileCmdAbstract
{
public:
  /// Constructor for parsing file script xml
  FileCmdImport(QXmlStreamReader &reader);

  virtual ~FileCmdImport();

  virtual void redo (MainWindow &mainWindow);

private:
  FileCmdImport();

  QString m_filename;
};

#endif // FILE_CMD_IMPORT_H
