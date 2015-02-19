#include "CmdEditPointAxis.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"

CmdEditPointAxis::CmdEditPointAxis (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &pointIdentifier,
                                    const QPointF &posGraphBefore,
                                    const QPointF &posGraphAfter) :
  CmdAbstract (mainWindow,
               document,
               "Edit axis point"),
  m_pointIdentifier (pointIdentifier),
  m_posGraphBefore (posGraphBefore),
  m_posGraphAfter (posGraphAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::CmdEditPointAxis point="
                              << pointIdentifier.toLatin1 ().data ()
                              << " posGraphBefore=" << QPointFToString (posGraphBefore).toLatin1 ().data ()
                              << " posGraphAfter=" << QPointFToString (posGraphAfter).toLatin1 ().data ();
}

CmdEditPointAxis::~CmdEditPointAxis ()
{
}

void CmdEditPointAxis::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::cmdRedo";

  document().editPointAxis (m_posGraphAfter,
                            m_pointIdentifier);
  mainWindow().updateAfterCommand();
}

void CmdEditPointAxis::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::cmdUndo";

  document().editPointAxis (m_posGraphBefore,
                            m_pointIdentifier);
  mainWindow().updateAfterCommand();
}

void CmdEditPointAxis::saveCommands (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_EDIT_POINT_AXIS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_pointIdentifier);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_X_BEFORE, QString::number (m_posGraphBefore.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_Y_BEFORE, QString::number (m_posGraphBefore.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_X_AFTER, QString::number (m_posGraphAfter.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_Y_AFTER, QString::number (m_posGraphAfter.y()));
  writer.writeEndElement();
}
