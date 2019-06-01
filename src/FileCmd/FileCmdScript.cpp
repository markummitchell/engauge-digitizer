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
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include "Xml.h"

FileCmdScript::FileCmdScript(const QString &fileCmdScriptFile)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FileCmdScript::FileCmdScript"
                              << " curDir=" << QDir::currentPath().toLatin1().data();

  // A non-existent script file is allowed in which case nothing gets done, as a way
  // of tracking MainWindow being in a regression test that has no command script
  if (!fileCmdScriptFile.isEmpty ()) {

    // Read commands into stack. The file is known to exist since it was checked in parseCmdLine
    QFile file (fileCmdScriptFile);

    QXmlStreamReader reader (&file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

      QString msg = QString ("%1 %2 %3 %4")
          .arg (QObject::tr ("Cannot read script file"))
          .arg (fileCmdScriptFile)
          .arg (QObject::tr ("from directory"))
          .arg (QDir::currentPath());
      QMessageBox::critical (nullptr,
                             "Script File",
                             msg);
      exit (-1);
    }

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
