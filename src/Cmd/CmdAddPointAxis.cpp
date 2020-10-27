/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddPointAxis.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QStringList>
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Add axis point");

CmdAddPointAxis::CmdAddPointAxis (MainWindow &mainWindow,
                                  Document &document,
                                  const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  double ordinal,
                                  bool isXOnly) :
  CmdPointChangeBase (mainWindow,
                      document,
                      CMD_DESCRIPTION),
  m_posScreen (posScreen),
  m_posGraph (posGraph),
  m_ordinal (ordinal),
  m_isXOnly (isXOnly)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::CmdAddPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " ordinal=" << ordinal;
}

CmdAddPointAxis::CmdAddPointAxis (MainWindow &mainWindow,
                                  Document &document,
                                  const QString &cmdDescription,
                                  QXmlStreamReader &reader) :
  CmdPointChangeBase (mainWindow,
                      document,
                      cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::CmdAddPointAxis";

  QXmlStreamAttributes attributes = reader.attributes();

  // Base attributes are handled by CmdPointChangeBase
  QStringList requiredAttributesLeaf;
  requiredAttributesLeaf << DOCUMENT_SERIALIZE_SCREEN_X
                         << DOCUMENT_SERIALIZE_SCREEN_Y
                         << DOCUMENT_SERIALIZE_GRAPH_X
                         << DOCUMENT_SERIALIZE_GRAPH_Y
                         << DOCUMENT_SERIALIZE_IDENTIFIER
                         << DOCUMENT_SERIALIZE_ORDINAL
                         << DOCUMENT_SERIALIZE_POINT_IS_X_ONLY;
  leafAttributes (attributes,
                  requiredAttributesLeaf,
                  reader);

  // Boolean values
  QString isXOnlyValue = attributes.value(DOCUMENT_SERIALIZE_POINT_IS_X_ONLY).toString();

  m_posScreen.setX(attributes.value(DOCUMENT_SERIALIZE_SCREEN_X).toDouble());
  m_posScreen.setY(attributes.value(DOCUMENT_SERIALIZE_SCREEN_Y).toDouble());
  m_posGraph.setX(attributes.value(DOCUMENT_SERIALIZE_GRAPH_X).toDouble());
  m_posGraph.setY(attributes.value(DOCUMENT_SERIALIZE_GRAPH_Y).toDouble());
  m_identifierAdded = attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
  m_ordinal = attributes.value(DOCUMENT_SERIALIZE_ORDINAL).toDouble();
  m_isXOnly = (isXOnlyValue == DOCUMENT_SERIALIZE_BOOL_TRUE);
}

CmdAddPointAxis::~CmdAddPointAxis ()
{
}

void CmdAddPointAxis::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::cmdRedo";

  restoreState ();
  saveOrCheckPreCommandDocumentStateHash (document ());
  saveDocumentState (document ());
  document().addPointAxisWithGeneratedIdentifier (m_posScreen,
                                                  m_posGraph,
                                                  m_identifierAdded,
                                                  m_ordinal,
                                                  m_isXOnly);
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  selectAddedPointForMoving (m_identifierAdded);
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdAddPointAxis::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointAxis::cmdUndo";

  restoreState ();
  saveOrCheckPostCommandDocumentStateHash (document ());
  restoreDocumentState (document ());
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdAddPointAxis::saveXml (QXmlStreamWriter &writer) const
{
  // For time coordinates, many digits of precision are needed since a typical date is 1,246,870,000 = July 6, 2009
  // and we want seconds of precision
  const char FORMAT = 'g';
  const int PRECISION = 16;

  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_ADD_POINT_AXIS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_X, QString::number (m_posScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_Y, QString::number (m_posScreen.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_X, QString::number (m_posGraph.x(), FORMAT, PRECISION));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_Y, QString::number (m_posGraph.y(), FORMAT, PRECISION));
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_identifierAdded);
  writer.writeAttribute(DOCUMENT_SERIALIZE_ORDINAL, QString::number (m_ordinal));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IS_X_ONLY, m_isXOnly ?
                          DOCUMENT_SERIALIZE_BOOL_TRUE :
                          DOCUMENT_SERIALIZE_BOOL_FALSE);
  baseAttributes (writer);
  writer.writeEndElement();
}
