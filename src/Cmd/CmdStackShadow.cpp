#include "CmdFactory.h"
#include "CmdStackShadow.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

CmdStackShadow::CmdStackShadow()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::CmdStackShadow";
}

void CmdStackShadow::loadCommands (MainWindow &mainWindow,
                                   Document &document,
                                   QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::loadCommands";

  // Load commands
  CmdFactory factory;
  while (!reader.atEnd() && !reader.hasError()) {

    if ((loadNextFromReader (reader) == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_CMD)) {

      // Extract and append new command to command stack
      m_cmdList.push_back (factory.createCmd (mainWindow,
                                              document,
                                              reader));
    }
  }
}
