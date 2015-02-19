#include "CmdAddPointAxis.h"
#include "Document.h"
#include "DocumentSerialize.h"
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

void CmdAddPointAxis::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_ADD_POINT_AXIS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_X, QString::number (m_posScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_Y, QString::number (m_posScreen.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_X, QString::number (m_posGraph.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_Y, QString::number (m_posGraph.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_identifierAdded);
  writer.writeEndElement();
}
