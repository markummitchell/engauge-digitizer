/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FILE_CMD_FACTORY_H
#define FILE_CMD_FACTORY_H

#include "FileCmdAbstract.h"

class QXmlStreamReader;

/// Factory that creates FileCmds from a file cmd script file, in xml format
class FileCmdFactory
{
 public:
  /// Single constructor
  FileCmdFactory();
  virtual ~FileCmdFactory();

  /// Create one FileCmdAbstract from the specified xml subtree
  FileCmdAbstract *createFileCmd (QXmlStreamReader &reader) const;
};

#endif // FILE_CMD_FACTORY_H
