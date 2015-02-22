#ifndef CMD_ABSTRACT_H
#define CMD_ABSTRACT_H

#include <QUndoCommand>

class Document;
class MainWindow;
class QXmlStreamWriter;

/// Wrapper around QUndoCommand. This simplifies the more complicated feature set of QUndoCommand
class CmdAbstract : public QUndoCommand
{
public:
  /// Single constructor
  CmdAbstract(MainWindow &mainWindow,
              Document &document,
              const QString &cmdDescription);

  virtual ~CmdAbstract();

  /// Redo method that is called when QUndoStack is moved one command forward.
  virtual void cmdRedo () = 0;

  /// Undo method that is called when QUndoStack is moved one command backward.
  virtual void cmdUndo () = 0;

  /// Save commands as xml for later uploading
  virtual void saveXml (QXmlStreamWriter &writer) const = 0;

protected:
  /// Return the Document that this command will modify during redo and undo.
  Document &document();

  /// Return a const copy of the Document for non redo/undo interaction.
  const Document &document() const;

  /// Return the MainWindow so it can be updated by this command as a last step.
  MainWindow &mainWindow ();

private:
  CmdAbstract();

  virtual void redo (); // Calls cmdRedo
  virtual void undo (); // Calls cmdUndo

  MainWindow &m_mainWindow;
  Document &m_document;

  // Snapshots of GraphicsPointAbstractBase::identifierIndex before and after redo
  bool m_isFirstRedo;
  unsigned int m_identifierIndexBeforeRedo;
  unsigned int m_identifierIndexAfterRedo;
};

#endif // CMD_ABSTRACT_H
