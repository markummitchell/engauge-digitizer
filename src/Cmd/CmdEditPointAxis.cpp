#include "CmdEditPointAxis.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Edit axis point");

CmdEditPointAxis::CmdEditPointAxis (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &pointIdentifier,
                                    const QPointF &posGraphBefore,
                                    const QPointF &posGraphAfter) :
  CmdAbstract (mainWindow,
               document,
               CMD_DESCRIPTION),
  m_pointIdentifier (pointIdentifier),
  m_posGraphBefore (posGraphBefore),
  m_posGraphAfter (posGraphAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::CmdEditPointAxis point="
                              << pointIdentifier.toLatin1 ().data ()
                              << " posGraphBefore=" << QPointFToString (posGraphBefore).toLatin1 ().data ()
                              << " posGraphAfter=" << QPointFToString (posGraphAfter).toLatin1 ().data ();
}

CmdEditPointAxis::CmdEditPointAxis (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &cmdDescription,
                                    QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::CmdEditPointAxis";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_X_BEFORE) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_Y_BEFORE) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_X_AFTER) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_Y_AFTER) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_IDENTIFIER)) {
      ENGAUGE_ASSERT (false);
  }

  m_posGraphBefore.setX(attributes.value(DOCUMENT_SERIALIZE_GRAPH_X_BEFORE).toDouble());
  m_posGraphBefore.setY(attributes.value(DOCUMENT_SERIALIZE_GRAPH_Y_BEFORE).toDouble());
  m_posGraphAfter.setX(attributes.value(DOCUMENT_SERIALIZE_GRAPH_X_AFTER).toDouble());
  m_posGraphAfter.setY(attributes.value(DOCUMENT_SERIALIZE_GRAPH_Y_AFTER).toDouble());
  m_pointIdentifier = attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
}

CmdEditPointAxis::~CmdEditPointAxis ()
{
}

void CmdEditPointAxis::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::cmdRedo";

  document().editPointAxis (m_posGraphAfter,
                            m_pointIdentifier);
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
}

void CmdEditPointAxis::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::cmdUndo";

  document().editPointAxis (m_posGraphBefore,
                            m_pointIdentifier);
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
}

void CmdEditPointAxis::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_EDIT_POINT_AXIS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_pointIdentifier);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_X_BEFORE, QString::number (m_posGraphBefore.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_Y_BEFORE, QString::number (m_posGraphBefore.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_X_AFTER, QString::number (m_posGraphAfter.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_Y_AFTER, QString::number (m_posGraphAfter.y()));
  writer.writeEndElement();
}
