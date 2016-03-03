#ifndef FILE_CMD_CLOSE_H
#define FILE_CMD_CLOSE_H

#include "FileCmdAbstract.h"

class QXmlStreamReader;

/// Command for closing a file
class FileCmdClose : public FileCmdAbstract {
public:
  /// Constructor for parsing file script xml
  FileCmdClose(QXmlStreamReader &reader);

  virtual ~FileCmdClose();

  virtual void redo(MainWindow &mainWindow);

private:
  FileCmdClose();
};

#endif // FILE_CMD_CLOSE_H
