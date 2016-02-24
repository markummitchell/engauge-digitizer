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
