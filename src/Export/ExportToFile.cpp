#include "Document.h"
#include "ExportToFile.h"
#include "Logger.h"
#include <QTextStream>

ExportToFile::ExportToFile()
{
}

void ExportToFile::exportToFile (const DocumentModelExport &modelExport,
                                 const Document &document,
                                 QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFile";

  str << "boy howdy";
}
