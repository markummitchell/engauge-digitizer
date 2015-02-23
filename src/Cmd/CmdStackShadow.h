#ifndef CMD_STACK_SHADOW_H
#define CMD_STACK_SHADOW_H

#include <QList>
#include <QObject>

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
class CmdStackShadow : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor
  CmdStackShadow();

  /// Return true if there is a command available
  bool canRedo () const;

  /// Load commands from serialized xml
  void loadCommands (MainWindow &mainWindow,
                     Document &document,
                     QXmlStreamReader &reader);

public slots:
  /// Move next command from list to CmdMediator. Noop if there are no more commands
  void slotRedo ();

  /// Throw away every command since trying to reconcile two different command stacks after an undo is too dangerous
  void slotUndo ();

private:

  MainWindow *m_mainWindow;

  CmdListInternal m_cmdList;
};

#endif // CMDSTACKSHADOW_H
