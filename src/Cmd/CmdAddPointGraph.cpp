#include "CmdAddPointGraph.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "QtToString.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Add graph point");

CmdAddPointGraph::CmdAddPointGraph (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &curveName,
                                    const QPointF &posScreen,
                                    double ordinal) :
  CmdAbstract (mainWindow,
               document,
               CMD_DESCRIPTION),
  m_curveName (curveName),
  m_posScreen (posScreen),
  m_ordinal (ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointGraph::CmdAddPointGraph"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " ordinal=" << m_ordinal;
}

CmdAddPointGraph::CmdAddPointGraph (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &cmdDescription,
                                    QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointGraph::CmdAddPointGraph";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_SCREEN_X) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_SCREEN_Y) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_NAME) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_ORDINAL) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_IDENTIFIER)) {
      ENGAUGE_ASSERT (false);
  }

  m_posScreen.setX(attributes.value(DOCUMENT_SERIALIZE_SCREEN_X).toDouble());
  m_posScreen.setY(attributes.value(DOCUMENT_SERIALIZE_SCREEN_Y).toDouble());
  m_curveName = attributes.value(DOCUMENT_SERIALIZE_CURVE_NAME).toString();
  m_identifierAdded = attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
  m_ordinal = attributes.value(DOCUMENT_SERIALIZE_ORDINAL).toDouble();
}

CmdAddPointGraph::~CmdAddPointGraph ()
{
}

void CmdAddPointGraph::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointGraph::cmdRedo";

  document().addPointGraphWithGeneratedIdentifier (m_curveName,
                                                   m_posScreen,
                                                   m_identifierAdded,
                                                   m_ordinal);
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
}

void CmdAddPointGraph::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointGraph::cmdUndo";

  document().removePointGraph (m_identifierAdded);
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
}

void CmdAddPointGraph::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_ADD_POINT_GRAPH);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_NAME, m_curveName);
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_X, QString::number (m_posScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_Y, QString::number (m_posScreen.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_identifierAdded);
  writer.writeAttribute(DOCUMENT_SERIALIZE_ORDINAL, QString::number (m_ordinal));
  writer.writeEndElement();
}
