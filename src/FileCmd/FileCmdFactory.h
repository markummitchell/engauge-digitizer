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
