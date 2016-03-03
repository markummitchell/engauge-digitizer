/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_ABSTRACT_H
#define CMD_ABSTRACT_H

#include "PointIdentifiers.h"
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

  /// Since the set of selected points has probably changed, changed that set back to the specified set. This
  /// lets the user move selected point(s) repeatedly using arrow keys. Also provides expected behavior when pasting
  void resetSelection(const PointIdentifiers &pointIdentifiersToSelect);

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
