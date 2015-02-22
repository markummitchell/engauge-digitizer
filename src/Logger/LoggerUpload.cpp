#include <iostream>
#include "LoggerUpload.h"
#include "MainWindow.h"

const MainWindow *LoggerUpload::m_mainWindow = (const MainWindow*) 0;

LoggerUpload::LoggerUpload()
{
}

void LoggerUpload::bindToMainWindow (const MainWindow *mainWindow)
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
