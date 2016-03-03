/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "FileCmdAbstract.h"
#include "FileCmdFactory.h"
#include "FileCmdScript.h"
#include "FileCmdSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QFile>
#include <QXmlStreamReader>
#include "Xml.h"

FileCmdScript::FileCmdScript(const QString &fileCmdScriptFile)
{
  // Read commands into stack. The file is known to exist since it was checked in parseCmdLine
  QFile file (fileCmdScriptFile);

  QXmlStreamReader reader (&file);
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  // Load commands
  FileCmdFactory factory;
  while (!reader.atEnd() && !reader.hasError()) {

    if ((loadNextFromReader (reader) == QXmlStreamReader::StartElement) &&
        (reader.name() == FILE_CMD_SERIALIZE_CMD)) {

      // Extract and append new command to command stack
      m_fileCmdStack.push_back (factory.createFileCmd (reader));
    }
  }
  file.close();
}

FileCmdScript::~FileCmdScript()
{
}

bool FileCmdScript::canRedo() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FileCmdScript::canRedo";

  return (m_fileCmdStack.count () > 0);
}

void FileCmdScript::redo(MainWindow &mainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FileCmdScript::redo";

  m_fileCmdStack.first()->redo(mainWindow);
  m_fileCmdStack.pop_front();
}
