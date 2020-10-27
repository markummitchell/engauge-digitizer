/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdDelete.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "ExportToClipboard.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include <QtToString.h>
#include <QXmlStreamReader>
#include "Xml.h"

const QString ADDED_DELIMITER (",");
const QString CMD_DESCRIPTION ("Delete");

CmdDelete::CmdDelete(MainWindow &mainWindow,
                     Document &document,
                     const QStringList &deletedPointIdentifiers) :
  CmdPointChangeBase (mainWindow,
                      document,
                      CMD_DESCRIPTION),
  m_deletedPointIdentifiers (deletedPointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::CmdDelete";

  // Export to clipboard
  ExportToClipboard exportStrategy;
  QTextStream strCsv (&m_csv), strHtml (&m_html);
  exportStrategy.exportToClipboard (deletedPointIdentifiers,
                                    mainWindow.transformation(),
                                    strCsv,
                                    strHtml,
                                    document.curveAxes(),
                                    document.curvesGraphs(),
                                    m_curvesGraphsRemoved);
}

CmdDelete::CmdDelete (MainWindow &mainWindow,
                      Document &document,
                      const QString &cmdDescription,
                      QXmlStreamReader &reader) :
  CmdPointChangeBase (mainWindow,
                      document,
                      cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::CmdDelete";

  QXmlStreamAttributes attributes = reader.attributes();

  QStringList requiredAttributesLeaf;
  requiredAttributesLeaf << DOCUMENT_SERIALIZE_TRANSFORM_DEFINED
                         << DOCUMENT_SERIALIZE_CSV
                         << DOCUMENT_SERIALIZE_HTML
                         << DOCUMENT_SERIALIZE_CMD_DELETE_ADDED_POINTS;
  leafAndBaseAttributes (attributes,
                         requiredAttributesLeaf,
                         reader);

  // Boolean values
  QString defined = attributes.value(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED).toString();

  m_transformIsDefined = (defined == DOCUMENT_SERIALIZE_BOOL_TRUE);
  m_csv = attributes.value(DOCUMENT_SERIALIZE_CSV).toString();
  m_html = attributes.value(DOCUMENT_SERIALIZE_HTML).toString();
  m_deletedPointIdentifiers = attributes.value(DOCUMENT_SERIALIZE_CMD_DELETE_ADDED_POINTS).toString().split(ADDED_DELIMITER);
  m_curvesGraphsRemoved.loadXml(reader);
}

CmdDelete::~CmdDelete ()
{
}

void CmdDelete::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::cmdRedo";

  restoreState ();
  saveOrCheckPreCommandDocumentStateHash (document ());
  saveDocumentState (document ());
  document().removePointsInCurvesGraphs (m_curvesGraphsRemoved);

  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdDelete::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::cmdUndo";

  restoreState ();
  saveOrCheckPostCommandDocumentStateHash (document ());
  restoreDocumentState (document ());
  mainWindow().updateAfterCommand();
  selectAddedPointsForMoving(m_deletedPointIdentifiers);
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdDelete::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_DELETE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED,
                        m_transformIsDefined ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CSV, m_csv);
  writer.writeAttribute(DOCUMENT_SERIALIZE_HTML, m_html);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DELETE_ADDED_POINTS, m_deletedPointIdentifiers.join (ADDED_DELIMITER));
  m_curvesGraphsRemoved.saveXml(writer);
  baseAttributes (writer);
  writer.writeEndElement();
}
