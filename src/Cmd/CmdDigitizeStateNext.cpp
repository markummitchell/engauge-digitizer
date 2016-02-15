#include "CmdDigitizeStateNext.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Next digitize state");

CmdDigitizeStateNext::CmdDigitizeStateNext(MainWindow &mainWindow,
                                                     Document &document) :
   CmdAbstract(mainWindow,
               document,
               CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeStateNext::CmdDigitizeStateNext";
}

CmdDigitizeStateNext::CmdDigitizeStateNext (MainWindow &mainWindow,
                                                      Document &document,
                                                      const QString &cmdDescription,
                                                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeStateNext::CmdDigitizeStateNext";

  bool success = true;

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CMD)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read debug command");
  }
}

CmdDigitizeStateNext::~CmdDigitizeStateNext ()
{
}

void CmdDigitizeStateNext::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeStateNext::cmdRedo";

  mainWindow().updateDigitizeStateNext();
  mainWindow().updateAfterCommand();
}

void CmdDigitizeStateNext::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeStateNext::cmdUndo";

  mainWindow().updateDigitizeStatePrevious();
  mainWindow().updateAfterCommand();
}

void CmdDigitizeStateNext::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_DIGITIZE_STATE_NEXT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeEndElement();
}
