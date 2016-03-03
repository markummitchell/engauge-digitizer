#include "Document.h"
#include "ExportFileFunctions.h"
#include "ExportFileRelations.h"
#include "ExportToFile.h"
#include "Logger.h"
#include "MainWindowModel.h"
#include <QTextStream>
#include "Transformation.h"

const QString CSV_FILENAME_EXTENSION("csv");
const QString TSV_FILENAME_EXTENSION("tsv");

ExportToFile::ExportToFile() {}

void ExportToFile::exportToFile(const DocumentModelExportFormat &modelExport,
                                const Document &document,
                                const MainWindowModel &modelMainWindow,
                                const Transformation &transformation,
                                QTextStream &str) const {
  LOG4CPP_INFO_S((*mainCat)) << "ExportToFile::exportToFile";

  ExportFileFunctions exportFunctions;
  exportFunctions.exportToFile(modelExport, document, modelMainWindow,
                               transformation, str);

  ExportFileRelations exportRelations;
  exportRelations.exportToFile(modelExport, document, modelMainWindow,
                               transformation, str);
}

QString ExportToFile::fileExtensionCsv() const {
  return CSV_FILENAME_EXTENSION;
}

QString ExportToFile::fileExtensionTsv() const {
  return TSV_FILENAME_EXTENSION;
}

QString ExportToFile::filterCsv() const {
  return QString("Text CSV (*.%1)").arg(CSV_FILENAME_EXTENSION);
}

QString ExportToFile::filterTsv() const {
  return QString("Text TSV (*.%1)").arg(TSV_FILENAME_EXTENSION);
}
