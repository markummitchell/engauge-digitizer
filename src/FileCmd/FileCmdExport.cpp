#include "EngaugeAssert.h"
#include "FileCmdExport.h"
#include "FileCmdSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Export File");

FileCmdExport::FileCmdExport (QXmlStreamReader &reader) :
  FileCmdAbstract (CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FileCmdExport::FileCmdExport";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(FILE_CMD_SERIALIZE_FILENAME)) {
    xmlExitWithError (reader,
                      QString ("Missing attribute %1").arg (FILE_CMD_SERIALIZE_FILENAME));
  }

  m_filename = attributes.value(FILE_CMD_SERIALIZE_FILENAME).toString();
}

FileCmdExport::~FileCmdExport ()
{
}

void FileCmdExport::redo (MainWindow &mainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FileCmdExport::redo";

  mainWindow.cmdFileExport (m_filename);
}
