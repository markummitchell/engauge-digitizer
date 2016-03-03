#include "EngaugeAssert.h"
#include "FileCmdImport.h"
#include "FileCmdSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION("Import File");

FileCmdImport::FileCmdImport(QXmlStreamReader &reader)
    : FileCmdAbstract(CMD_DESCRIPTION) {
  LOG4CPP_INFO_S((*mainCat)) << "FileCmdImport::FileCmdImport";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(FILE_CMD_SERIALIZE_FILENAME)) {
    xmlExitWithError(reader, QString("%1 %2")
                                 .arg(QObject::tr("Missing attribute"))
                                 .arg(FILE_CMD_SERIALIZE_FILENAME));
  }

  m_filename = attributes.value(FILE_CMD_SERIALIZE_FILENAME).toString();
}

FileCmdImport::~FileCmdImport() {}

void FileCmdImport::redo(MainWindow &mainWindow) {
  LOG4CPP_INFO_S((*mainCat)) << "FileCmdImport::redo";

  mainWindow.cmdFileImport(m_filename);
}
