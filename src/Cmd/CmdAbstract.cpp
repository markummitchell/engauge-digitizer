#include "CmdAbstract.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"

CmdAbstract::CmdAbstract(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription) :
  QUndoCommand (cmdDescription),
  m_mainWindow (mainWindow),
  m_document (document),
  m_isFirstRedo (true)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::CmdAbstract";
}

CmdAbstract::~CmdAbstract()
{
}

Document &CmdAbstract::document ()
{
  return m_document;
}

const Document &CmdAbstract::document () const
{
  return m_document;
}

MainWindow &CmdAbstract::mainWindow ()
{
  return m_mainWindow;
}

void CmdAbstract::redo ()
{
  // Note that m_identifierIndexBeforeRedo and m_identifierIndexAfterRedo are not set until below (at which point they are logged)
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::redo";

  if (m_isFirstRedo) {

    m_identifierIndexBeforeRedo = Point::identifierIndex ();

  } else {

    // Reset state. The first time this is called, this is a noop since m_identifierIndex was just set to
    // GraphicsPointAbstractBase::identifierIndex in the constructor of this class
    Point::setIdentifierIndex (m_identifierIndexBeforeRedo);

  }

  // Invoke the leaf class redo method
  cmdRedo ();

  if (m_isFirstRedo) {

    m_isFirstRedo = false;
    m_identifierIndexAfterRedo = Point::identifierIndex();

  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::redo identifierIndex=" << m_identifierIndexBeforeRedo << "->"
                              << m_identifierIndexAfterRedo;
}

void CmdAbstract::undo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::undo identifierIndex=" << m_identifierIndexAfterRedo << "->"
                              << m_identifierIndexBeforeRedo;

  Point::setIdentifierIndex (m_identifierIndexAfterRedo);

  // Invoke the leaf class undo method
  cmdUndo ();

  Point::setIdentifierIndex (m_identifierIndexBeforeRedo);
}
