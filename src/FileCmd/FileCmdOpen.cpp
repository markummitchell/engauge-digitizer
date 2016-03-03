#include "EngaugeAssert.h"
#include "FileCmdOpen.h"
#include "FileCmdSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION("Open File");

FileCmdOpen::FileCmdOpen(QXmlStreamReader &reader)
    : FileCmdAbstract(CMD_DESCRIPTION) {
  LOG4CPP_INFO_S((*mainCat)) << "FileCmdOpen::FileCmdOpen";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(FILE_CMD_SERIALIZE_FILENAME)) {
    xmlExitWithError(reader, QString("%1 %2")
                                 .arg(QObject::tr("Missing attribute"))
                                 .arg(FILE_CMD_SERIALIZE_FILENAME));
  }

  m_filename = attributes.value(FILE_CMD_SERIALIZE_FILENAME).toString();
}

FileCmdOpen::~FileCmdOpen() {}

void FileCmdOpen::redo(MainWindow &mainWindow) {
  LOG4CPP_INFO_S((*mainCat)) << "FileCmdOpen::redo";

  mainWindow.cmdFileOpen(m_filename);
}
