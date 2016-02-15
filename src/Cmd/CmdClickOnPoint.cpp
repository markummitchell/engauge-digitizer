#include "CmdClickOnPoint.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Click on point");

CmdClickOnPoint::CmdClickOnPoint(MainWindow &mainWindow,
                                 Document &document,
                                 const QPointF &point) :
   CmdAbstract(mainWindow,
               document,
               CMD_DESCRIPTION),
   m_point (point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdClickOnPoint::CmdClickOnPoint";
}

CmdClickOnPoint::CmdClickOnPoint (MainWindow &mainWindow,
                                  Document &document,
                                  const QString &cmdDescription,
                                  QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdClickOnPoint::CmdClickOnPoint";

  bool success = true;

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CMD)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_POINT)) {

      QXmlStreamAttributes attributes = reader.attributes();

      if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_X) ||
          !attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_Y)) {
        ENGAUGE_ASSERT(false);
      }
      
      m_point.setX (attributes.value(DOCUMENT_SERIALIZE_POINT_X).toDouble());
      m_point.setY (attributes.value(DOCUMENT_SERIALIZE_POINT_Y).toDouble());

    }
  }

  if (!success) {
    reader.raiseError ("Cannot read click on point command");
  }
}

CmdClickOnPoint::~CmdClickOnPoint ()
{
}

void CmdClickOnPoint::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdClickOnPoint::cmdRedo";

  mainWindow().updateClickOnPoint(m_point);
  mainWindow().updateAfterCommand();
}

void CmdClickOnPoint::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdClickOnPoint::cmdUndo";

  // Noop in the undo direction
}

void CmdClickOnPoint::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_CLICK_ON_POINT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_point.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_point.y()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeEndElement();
}
