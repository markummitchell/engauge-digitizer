/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "MainDirectoryPersist.h"
#include <QFileInfo>

// QDir::current() gives "working directory" consistent with setting in qtcreator
QDir MainDirectoryPersist::m_directoryExportSave = QDir::current();
QDir MainDirectoryPersist::m_directoryImportOpen = QDir::current();

MainDirectoryPersist::MainDirectoryPersist()
{
}

QDir MainDirectoryPersist::getDirectoryExportSave() const
{
  return m_directoryExportSave;
}

QDir MainDirectoryPersist::getDirectoryImportOpen() const
{
  return m_directoryImportOpen;
}

void MainDirectoryPersist::setDirectoryExportSaveFromFilename(const QString &fileName)
{
  m_directoryExportSave = QFileInfo(fileName).dir();
}

void MainDirectoryPersist::setDirectoryImportOpenFromFilename(const QString &fileName)
{
  m_directoryImportOpen = QFileInfo(fileName).dir();
}
