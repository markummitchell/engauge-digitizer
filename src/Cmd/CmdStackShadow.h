#ifndef CMD_STACK_SHADOW_H
#define CMD_STACK_SHADOW_H

#include <QList>

class CmdAbstract;
class Document;
class MainWindow;
class QXmlStreamReader;

typedef QList<CmdAbstract*> CmdListInternal;

/// Command stack that shadows the CmdMediator command stack at startup when reading commands from an error report file.
/// The commands are loaded into this container rather than CmdMediator, since CmdMediator would try to execute all the
/// commands immediately. For the best debugging, we want to be able to execute each command one by one. This container
/// nicely stores commands until we want to copy them to CmdMediator so they can be executed.
///
/// This class is not subclassed from QUndoStack since that class is designed to prevent access to individual commands,
/// to preserve their integrity
///
/// This class is not named CmdMediatorShadow since does not maintain a Document like CmdMediator, although in some ways
/// that name might be a useful alias
class CmdStackShadow
{
public:
  /// Single constructor
  CmdStackShadow();

  /// Load commands from serialized xml
  void loadCommands (MainWindow &mainWindow,
                     Document &document,
                     QXmlStreamReader &reader);

private:

  CmdListInternal m_cmdList;
};

#endif // CMDSTACKSHADOW_H
