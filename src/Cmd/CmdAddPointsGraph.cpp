/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddPointsGraph.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <qdebug.h>
#include "QtToString.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Add graph points");

CmdAddPointsGraph::CmdAddPointsGraph (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &curveName,
                                      const QList<QPoint> &points,
                                      const QList<double> &ordinals) :
  CmdPointChangeBase (mainWindow,
                      document,
                      CMD_DESCRIPTION),
  m_curveName (curveName),
  m_points (points),
  m_ordinals (ordinals)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointsGraph::CmdAddPointsGraph";
}

CmdAddPointsGraph::CmdAddPointsGraph (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader &reader) :
  CmdPointChangeBase (mainWindow,
                      document,
                      cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointsGraph::CmdAddPointsGraph";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_NAME)) {
    xmlExitWithError (reader,
                      QString ("%1 %2")
                      .arg (QObject::tr ("Missing attribute"))
                      .arg (DOCUMENT_SERIALIZE_CURVE_NAME));
  }

  m_curveName = attributes.value(DOCUMENT_SERIALIZE_CURVE_NAME).toString();

  bool success = true;
  while (loadNextFromReader (reader)) {

    if (reader.atEnd() || reader.hasError ()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::EndElement) &
        (reader.name() == DOCUMENT_SERIALIZE_CMD)) {
      break;
    }

    // Not done yet
    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_POINT)) {

      // This is an entry that we need to add
      QXmlStreamAttributes attributes = reader.attributes ();

      if (attributes.hasAttribute(DOCUMENT_SERIALIZE_IDENTIFIER) &&
          attributes.hasAttribute(DOCUMENT_SERIALIZE_ORDINAL) &&
          attributes.hasAttribute(DOCUMENT_SERIALIZE_SCREEN_X) &&
          attributes.hasAttribute(DOCUMENT_SERIALIZE_SCREEN_Y)) {

        m_identifiersAdded << attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
        m_ordinals << attributes.value(DOCUMENT_SERIALIZE_ORDINAL).toDouble();

        QPoint point (attributes.value(DOCUMENT_SERIALIZE_SCREEN_X).toInt(),
                      attributes.value(DOCUMENT_SERIALIZE_SCREEN_Y).toInt());
        m_points << point;
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read graph points"));
  }
}

CmdAddPointsGraph::~CmdAddPointsGraph ()
{
}

void CmdAddPointsGraph::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointsGraph::cmdRedo";

  saveOrCheckPreCommandDocumentStateHash (document ());
  saveDocumentState (document ());
  for (int index = 0; index < m_points.count(); index++) {

    QString identifierAdded;
    document().addPointGraphWithGeneratedIdentifier (m_curveName,
                                                     m_points.at (index),
                                                     identifierAdded,
                                                     m_ordinals.at (index));
    m_identifiersAdded.push_back (identifierAdded);
  }

  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdAddPointsGraph::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAddPointsGraph::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  restoreDocumentState (document ());
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdAddPointsGraph::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_ADD_POINTS_GRAPH);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_NAME, m_curveName);

  for (int index = 0; index < m_points.count(); index++) {

    writer.writeStartElement (DOCUMENT_SERIALIZE_POINT);
    writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_X, QString::number (m_points.at (index).x()));
    writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_Y, QString::number (m_points.at (index).y()));

    QString identifier;
    if (index < m_identifiersAdded.count()) {
      identifier = m_identifiersAdded.at (index);
    }

    writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, identifier);
    writer.writeAttribute(DOCUMENT_SERIALIZE_ORDINAL, QString::number (m_ordinals.at (index)));
    writer.writeEndElement();
  }
  writer.writeEndElement();
}
