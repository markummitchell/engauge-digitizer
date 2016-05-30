/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdCopy.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "ExportToClipboard.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MimePoints.h"
#include <QApplication>
#include <QClipboard>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Copy");

CmdCopy::CmdCopy(MainWindow &mainWindow,
                 Document &document,
                 const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_transformIsDefined (mainWindow.transformIsDefined())
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::CmdCopy"
                              << " selected=" << selectedPointIdentifiers.count ();

  ExportToClipboard exportStrategy;
  QTextStream strCsv (&m_csv), strHtml (&m_html);
  exportStrategy.exportToClipboard (selectedPointIdentifiers,
                                    mainWindow.transformation(),
                                    strCsv,
                                    strHtml,
                                    document.curveAxes(),
                                    document.curvesGraphs(),
                                    m_curvesGraphs);
}

CmdCopy::CmdCopy (MainWindow &mainWindow,
                  Document &document,
                  const QString &cmdDescription,
                   QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::CmdCopy";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_CSV) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_HTML)) {
    xmlExitWithError (reader,
                      QString ("%1 %2, %3 %4 %5")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_TRANSFORM_DEFINED)
                      .arg (DOCUMENT_SERIALIZE_CSV)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_HTML));
  }

  QString defined = attributes.value(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED).toString();

  m_transformIsDefined = (defined == DOCUMENT_SERIALIZE_BOOL_TRUE);
  m_csv = attributes.value(DOCUMENT_SERIALIZE_CSV).toString();
  m_html = attributes.value(DOCUMENT_SERIALIZE_HTML).toString();
  m_curvesGraphs.loadXml(reader);
}

CmdCopy::~CmdCopy ()
{
}

void CmdCopy::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::cmdRedo";

  MimePoints *mimePoints;
  if (m_transformIsDefined) {
    mimePoints = new MimePoints (m_csv,
                                 m_html);
  } else {
    mimePoints = new MimePoints (m_csv);
  }

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setMimeData (mimePoints, QClipboard::Clipboard);

  saveOrCheckPreCommandDocumentStateHash (document ());
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdCopy::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdCopy::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_COPY);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED,
                        m_transformIsDefined ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CSV, m_csv);
  writer.writeAttribute(DOCUMENT_SERIALIZE_HTML, m_html);
  m_curvesGraphs.saveXml(writer);
  writer.writeEndElement();
}
