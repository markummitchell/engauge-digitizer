/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <iostream>
#include "LoggerUpload.h"
#include "MainWindow.h"

MainWindow *LoggerUpload::m_mainWindow = (MainWindow*) 0;

LoggerUpload::LoggerUpload()
{
}

void LoggerUpload::bindToMainWindow (MainWindow *mainWindow)
{
  m_mainWindow = mainWindow;
}

void LoggerUpload::loggerAssert(const char *condition,
                                const char* file,
                                int line)
{
  loggerOutput (condition,
                file,
                line,
                "assert");
}

void LoggerUpload::loggerCheckPtr(const char *ptr,
                                  const char *file,
                                  int line)
{
  loggerOutput (ptr,
                file,
                line,
                "null pointer");
}

void LoggerUpload::loggerOutput(const char *comment,
                                const char *file,
                                int line,
                                const char *context)
{
  if (m_mainWindow != 0) {
    m_mainWindow->saveErrorReportFileAndExit(comment,
                                             file,
                                             line,
                                             context);
  }

  std::cerr << "Error '" << context << "' at file " << file << " line " << line << ": " << comment << std::endl;
  exit (-1); // Stop execution since it is no longer safe to continue
}
