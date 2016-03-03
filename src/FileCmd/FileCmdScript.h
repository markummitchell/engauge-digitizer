/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FILE_CMD_SCRIPT_H
#define FILE_CMD_SCRIPT_H

#include <QStack>

class FileCmdAbstract;
class MainWindow;

typedef QStack<FileCmdAbstract*> FileCmdStack;

/// File that manages a command stack for regression testing of file import/open/export/close. This command
/// stack (with a lifetime the same as the application's) is independent of the command stack in CmdMediator
/// (which is Document-specific)
class FileCmdScript
{
 public:
  /// Single constructor
  FileCmdScript(const QString &fileCmdScriptFile);
  ~FileCmdScript();

  /// Returns true if there is at least one command on the stack
  bool canRedo() const;

  /// Apply the next command. Requires non-empty stack
  void redo(MainWindow &mainWindow);

 private:
  FileCmdScript();

  FileCmdStack m_fileCmdStack;  
};

#endif // FILE_CMD_SCRIPT_H
