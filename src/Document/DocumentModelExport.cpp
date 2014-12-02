#include "CmdMediator.h"
#include "DocumentModelExport.h"
#include "Logger.h"
#include <QXmlStreamWriter>

DocumentModelExport::DocumentModelExport() :
  m_exportPointsSelectionFunctions (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES),
  m_exportPointsSelectionRelations (EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE),
  m_exportLayoutFunctions (EXPORT_LAYOUT_ALL_PER_LINE),
  m_exportDelimiter (EXPORT_DELIMITER_COMMA),
  m_exportHeader (EXPORT_HEADER_SIMPLE)
{
}

DocumentModelExport::DocumentModelExport (const Document &document) :
  m_exportPointsSelectionFunctions (document.modelExport().exportPointsSelectionFunctions()),
  m_exportPointsSelectionRelations (document.modelExport().exportPointsSelectionRelations()),
  m_exportLayoutFunctions (document.modelExport().exportLayoutFunctions()),
  m_exportDelimiter (document.modelExport().exportDelimiter()),
  m_exportHeader (document.modelExport().exportHeader())
{
}

DocumentModelExport::DocumentModelExport(const DocumentModelExport &other) :
  m_exportPointsSelectionFunctions (other.exportPointsSelectionFunctions()),
  m_exportPointsSelectionRelations (other.exportPointsSelectionRelations()),
  m_exportLayoutFunctions (other.exportLayoutFunctions()),
  m_exportDelimiter (other.exportDelimiter()),
  m_exportHeader (other.exportHeader())
{

}

DocumentModelExport &DocumentModelExport::operator=(const DocumentModelExport &other)
{
  m_exportPointsSelectionFunctions = other.exportPointsSelectionFunctions();
  m_exportPointsSelectionRelations = other.exportPointsSelectionRelations();
  m_exportLayoutFunctions = other.exportLayoutFunctions();
  m_exportDelimiter = other.exportDelimiter();
  m_exportHeader = other.exportHeader();

  return *this;
}

QStringList DocumentModelExport::curveNamesNotExported() const
{
  return m_curveNamesNotExported;
}

ExportDelimiter DocumentModelExport::exportDelimiter() const
{
  return m_exportDelimiter;
}

ExportHeader DocumentModelExport::exportHeader() const
{
  return m_exportHeader;
}

ExportLayoutFunctions DocumentModelExport::exportLayoutFunctions() const
{
  return m_exportLayoutFunctions;
}

ExportPointsSelectionFunctions DocumentModelExport::exportPointsSelectionFunctions() const
{
  return m_exportPointsSelectionFunctions;
}

ExportPointsSelectionRelations DocumentModelExport::exportPointsSelectionRelations() const
{
  return m_exportPointsSelectionRelations;
}

void DocumentModelExport::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelExport::saveModel";

  stream.writeStartElement("DocumentModelExport");
  stream.writeEndElement();
}

void DocumentModelExport::setCurveNamesNotExported(const QStringList &curveNamesNotExported)
{
  m_curveNamesNotExported = curveNamesNotExported;
}

void DocumentModelExport::setExportDelimiter(ExportDelimiter exportDelimiter)
{
  m_exportDelimiter = exportDelimiter;
}

void DocumentModelExport::setExportHeader(ExportHeader exportHeader)
{
  m_exportHeader = exportHeader;
}

void DocumentModelExport::setExportLayoutFunctions(ExportLayoutFunctions exportLayoutFunctions)
{
  m_exportLayoutFunctions = exportLayoutFunctions;
}

void DocumentModelExport::setExportPointsSelectionFunctions(ExportPointsSelectionFunctions exportPointsSelectionFunctions)
{
  m_exportPointsSelectionFunctions = exportPointsSelectionFunctions;
}

void DocumentModelExport::setExportPointsSelectionRelations(ExportPointsSelectionRelations exportPointsSelectionRelations)
{
  m_exportPointsSelectionRelations = exportPointsSelectionRelations;
}
