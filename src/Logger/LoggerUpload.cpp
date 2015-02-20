#include "CmdMediator.h"
#include <iostream>
#include "LoggerUpload.h"

using namespace std;

const CmdMediator *LoggerUpload::m_cmdMediator = (const CmdMediator*) 0;

LoggerUpload::LoggerUpload()
{
}

void LoggerUpload::bindToCmdMediator(const CmdMediator *cmdMediator)
{
  m_cmdMediator = cmdMediator;
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
  if (m_cmdMediator != 0) {

    QString xmlCommands;
    QXmlStreamWriter writer (&xmlCommands);
    writer.setAutoFormatting(true);

    m_cmdMediator->saveXml(writer);

    cerr << "Error '" << context << "' in file " << file << " at line " << line << endl
         << "Details: " << comment << endl
         << xmlCommands.toLatin1().data() << endl;
  }

  exit (-1); // Stop execution since it is no longer safe to continue
}
