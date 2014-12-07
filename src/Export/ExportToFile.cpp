#include "ExportToFile.h"
#include "Logger.h"
#include <QTextStream>

ExportToFile::ExportToFile()
{
}

void ExportToFile::exportToFile (DocumentModelExport &modelExport,
                                 QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFile";

  str << "boy howdy";
}
