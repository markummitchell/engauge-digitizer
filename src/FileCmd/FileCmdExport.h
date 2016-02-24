#ifndef FILE_CMD_EXPORT_H
#define FILE_CMD_EXPORT_H

#include "FileCmdAbstract.h"

class QXmlStreamReader;

/// Command for exporting a file
class FileCmdExport : public FileCmdAbstract
{
public:
  /// Constructor for parsing file script xml
  FileCmdExport(QXmlStreamReader &reader);

  virtual ~FileCmdExport();

  virtual void redo (MainWindow &mainWindow);

private:
  FileCmdExport();

  QString m_filename;
};

#endif // FILE_CMD_EXPORT_H
