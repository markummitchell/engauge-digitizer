#include "FileCmdAbstract.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QMessageBox>

FileCmdAbstract::FileCmdAbstract(const QString &cmdDescription) :
  m_cmdDescription (cmdDescription)
{
}

FileCmdAbstract::~FileCmdAbstract()
{
}

QString FileCmdAbstract::cmdDescription() const
{
  return m_cmdDescription;
}
