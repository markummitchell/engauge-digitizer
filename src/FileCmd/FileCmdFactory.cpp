#include "EngaugeAssert.h"
#include "FileCmdClose.h"
#include "FileCmdExport.h"
#include "FileCmdImport.h"
#include "FileCmdOpen.h"
#include "FileCmdFactory.h"
#include "FileCmdSerialize.h"
#include <QXmlStreamReader>
#include "Xml.h"

FileCmdFactory::FileCmdFactory() {}

FileCmdFactory::~FileCmdFactory() {}

FileCmdAbstract *FileCmdFactory::createFileCmd(QXmlStreamReader &reader) const {
  FileCmdAbstract *cmd = 0;

  QXmlStreamAttributes attributes = reader.attributes();
  if (!attributes.hasAttribute(FILE_CMD_SERIALIZE_CMD_TYPE)) {
    xmlExitWithError(reader, QString("Missing attribute %1")
                                 .arg(FILE_CMD_SERIALIZE_CMD_TYPE));
  }

  // Get common attributes
  QString cmdType = attributes.value(FILE_CMD_SERIALIZE_CMD_TYPE).toString();

  if (cmdType == FILE_CMD_SERIALIZE_CMD_FILE_CLOSE) {
    cmd = new FileCmdClose(reader);
  } else if (cmdType == FILE_CMD_SERIALIZE_CMD_FILE_EXPORT) {
    cmd = new FileCmdExport(reader);
  } else if (cmdType == FILE_CMD_SERIALIZE_CMD_FILE_IMPORT) {
    cmd = new FileCmdImport(reader);
  } else if (cmdType == FILE_CMD_SERIALIZE_CMD_FILE_OPEN) {
    cmd = new FileCmdOpen(reader);
  } else {

    // Invalid xml
    ENGAUGE_ASSERT(false);
  }

  return cmd;
}
