#include "CmdCut.h"
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

const QString CMD_DESCRIPTION ("Cut");

CmdCut::CmdCut(MainWindow &mainWindow,
               Document &document,
               const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_transformIsDefined (mainWindow.transformIsDefined())
{
  QStringList selected;
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::CmdCut"
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";

  ExportToClipboard exportStrategy;
  QTextStream strCsv (&m_csv), strHtml (&m_html);
  exportStrategy.exportToClipboard (selected,
                                    mainWindow.transformIsDefined(),
                                    strCsv,
                                    strHtml,
                                    m_curvesGraphs);
}

CmdCut::CmdCut (MainWindow &mainWindow,
                Document &document,
                const QString &cmdDescription,
                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::CmdCut";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_CSV) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_HTML)) {
      ENGAUGE_ASSERT (false);
  }

  QString defined = attributes.value(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED).toString();

  m_transformIsDefined = (defined == DOCUMENT_SERIALIZE_BOOL_TRUE);
  m_csv = attributes.value(DOCUMENT_SERIALIZE_CSV).toString();
  m_html = attributes.value(DOCUMENT_SERIALIZE_HTML).toString();
  m_curvesGraphs.loadXml(reader);
}

CmdCut::~CmdCut ()
{
}

void CmdCut::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::cmdRedo";

  MimePoints *mimePoints;
  if (m_transformIsDefined) {
    mimePoints = new MimePoints (m_csv,
                                 m_html);
  } else {
    mimePoints = new MimePoints (m_csv);
  }

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setMimeData (mimePoints, QClipboard::Clipboard);

  document().removePointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}

void CmdCut::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::cmdUndo";

  document().addPointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}

void CmdCut::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_CUT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_TRANSFORM_DEFINED,
                        m_transformIsDefined ? DOCUMENT_SERIALIZE_BOOL_TRUE: DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CSV, m_csv);
  writer.writeAttribute(DOCUMENT_SERIALIZE_HTML, m_html);
  m_curvesGraphs.saveXml(writer);
  writer.writeEndElement();
}
