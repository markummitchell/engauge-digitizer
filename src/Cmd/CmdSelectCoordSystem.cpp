/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSelectCoordSystem.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QClipboard>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Select Coordinate System");

CmdSelectCoordSystem::CmdSelectCoordSystem(MainWindow &mainWindow,
                                           Document &document,
                                           CoordSystemIndex coordSystemIndex) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_coordSystemIndexBefore (document.coordSystemIndex()),
  m_coordSystemIndexAfter (coordSystemIndex)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSelectCoordSystem::CmdSelectCoordSystem";
}

CmdSelectCoordSystem::CmdSelectCoordSystem (MainWindow &mainWindow,
                                            Document &document,
                                            const QString &cmdDescription,
                                            QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSelectCoordSystem::CmdSelectCoordSystem";

  QXmlStreamAttributes attributes = reader.attributes();

  QStringList requiredAttributesLeaf;
  requiredAttributesLeaf << DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_AFTER
                         << DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_BEFORE;
  leafAndBaseAttributes (attributes,
                         requiredAttributesLeaf,
                         reader);

  m_coordSystemIndexAfter = attributes.value(DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_AFTER).toInt ();
  m_coordSystemIndexBefore = attributes.value(DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_BEFORE).toInt ();
}

CmdSelectCoordSystem::~CmdSelectCoordSystem ()
{
}

void CmdSelectCoordSystem::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSelectCoordSystem::cmdRedo"
                              << " index=" << m_coordSystemIndexBefore << "->" << m_coordSystemIndexAfter;

  saveOrCheckPreCommandDocumentStateHash (document ());
  mainWindow().updateCoordSystem (m_coordSystemIndexAfter);
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdSelectCoordSystem::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSelectCoordSystem::cmdUndo"
                              << " index=" << m_coordSystemIndexAfter << "->" << m_coordSystemIndexBefore;

  saveOrCheckPostCommandDocumentStateHash (document ());
  mainWindow().updateCoordSystem (m_coordSystemIndexBefore);
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdSelectCoordSystem::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SELECT_COORD_SYSTEM);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_BEFORE, QString::number (m_coordSystemIndexBefore));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_AFTER, QString::number (m_coordSystemIndexAfter));
  baseAttributes (writer);
  writer.writeEndElement();
}
