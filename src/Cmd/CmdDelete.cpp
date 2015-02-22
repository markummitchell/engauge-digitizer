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

const QString CMD_DESCRIPTION ("Delete");

CmdDelete::CmdDelete(MainWindow &mainWindow,
                     Document &document,
                     const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION)
{
  QStringList selected;
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::CmdDelete"
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";

  ExportToClipboard exportStrategy;
  QTextStream strCsv (&m_csv), strHtml (&m_html);
  exportStrategy.exportToClipboard (selected,
                                    mainWindow.transformIsDefined(),
                                    strCsv,
                                    strHtml,
                              m_curvesGraphs);
}

CmdDelete::CmdDelete (MainWindow &mainWindow,
                      Document &document,
                      const QString &cmdDescription,
                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::CmdDelete";

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
}

CmdDelete::~CmdDelete ()
{
}

void CmdDelete::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::cmdRedo";

  document().removePointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}

void CmdDelete::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::cmdUndo";

  document().addPointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
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
  m_curvesGraphs.saveXml(writer);
  writer.writeEndElement();
}
