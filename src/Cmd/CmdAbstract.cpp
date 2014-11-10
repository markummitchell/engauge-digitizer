#include "CmdAbstract.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"

CmdAbstract::CmdAbstract(MainWindow &mainWindow,
                         Document &document,
                         const QString &text) :
  QUndoCommand (text),
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
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::redo identifier=" << m_identifierIndexBeforeRedo << "->"
                              << m_identifierIndexAfterRedo;

  if (m_isFirstRedo) {

    m_identifierIndexBeforeRedo = Point::identifierIndex ();

  } else {

    // Reset state. The first time this is called, this is a noop since m_identifierIndex was just set to
    // GraphicsPointAbstractBase::identifierIndex in the constructor of this class
    Point::setIdentifierIndex (m_identifierIndexBeforeRedo);

  }

  cmdRedo ();

  if (m_isFirstRedo) {

    m_isFirstRedo = false;
    m_identifierIndexAfterRedo = Point::identifierIndex();

  }
}

void CmdAbstract::undo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::undo";

  Point::setIdentifierIndex (m_identifierIndexAfterRedo);

  cmdUndo ();

  Point::setIdentifierIndex (m_identifierIndexBeforeRedo);
}
