#include "Document.h"
#include "ExportFileFunctions.h"
#include "ExportFileRelations.h"
#include "ExportToFile.h"
#include "Logger.h"
#include <QTextStream>
#include "Transformation.h"

ExportToFile::ExportToFile()
{
}

void ExportToFile::exportToFile (const DocumentModelExportFormat &modelExport,
                                 const Document &document,
                                 const Transformation &transformation,
                                 QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFile";

  ExportFileFunctions exportFunctions;
  exportFunctions.exportToFile (modelExport,
                                document,
                                transformation,
                                str);

  ExportFileRelations exportRelations;
  exportRelations.exportToFile (modelExport,
                                document,
                                transformation,
                                str);
}
