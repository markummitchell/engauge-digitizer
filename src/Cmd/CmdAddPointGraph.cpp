/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddPointGraph.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Add graph point");

CmdAddPointGraph::CmdAddPointGraph (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &curveName,
                                    const QPointF &posScreen,
                                    double ordinal) :
  CmdPointChangeBase (mainWindow,
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
  CmdPointChangeBase (mainWindow,
                      document,
                      cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointGraph::CmdAddPointGraph";

  QXmlStreamAttributes attributes = reader.attributes();

  // Base attributes are handled by CmdPointChangeBase
  QStringList requiredAttributesLeaf;
  requiredAttributesLeaf << DOCUMENT_SERIALIZE_SCREEN_X
                         << DOCUMENT_SERIALIZE_SCREEN_Y
                         << DOCUMENT_SERIALIZE_CURVE_NAME
                         << DOCUMENT_SERIALIZE_ORDINAL
                         << DOCUMENT_SERIALIZE_IDENTIFIER;
  leafAttributes (attributes,
                  requiredAttributesLeaf,
                  reader);

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

  saveOrCheckPreCommandDocumentStateHash (document ());
  saveDocumentState (document ());
  document().addPointGraphWithGeneratedIdentifier (m_curveName,
                                                   m_posScreen,
                                                   m_identifierAdded,
                                                   m_ordinal);
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdAddPointGraph::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointGraph::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  restoreDocumentState (document ());
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
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
  baseAttributes (writer);
  writer.writeEndElement();
}
