#include "CmdAddPointAxis.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include "QtToString.h"

CmdAddPointAxis::CmdAddPointAxis (MainWindow &mainWindow,
                                  Document &document,
                                  const QPointF &posScreen,
                                  const QPointF &posGraph) :
  CmdAbstract (mainWindow,
               document,
               "Add axis point"),
  m_posScreen (posScreen),
  m_posGraph (posGraph)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::CmdAddPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();
}

CmdAddPointAxis::~CmdAddPointAxis ()
{
}

void CmdAddPointAxis::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::cmdRedo";

  document().addPointAxis (m_posScreen,
                           m_posGraph,
                           m_identifierAdded);
  mainWindow().updateAfterCommand();
}

void CmdAddPointAxis::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::cmdUndo";

  document().removePointAxis (m_identifierAdded);
  mainWindow().updateAfterCommand();
}
