#ifndef FILE_CMD_OPEN_H
#define FILE_CMD_OPEN_H

#include "FileCmdAbstract.h"

class QXmlStreamReader;

/// Command for opening a file
class FileCmdOpen : public FileCmdAbstract {
public:
  /// Constructor for parsing file script xml
  FileCmdOpen(QXmlStreamReader &reader);

  virtual ~FileCmdOpen();

  virtual void redo(MainWindow &mainWindow);

private:
  FileCmdOpen();

  QString m_filename;
};

#endif // FILE_CMD_OPEN_H
