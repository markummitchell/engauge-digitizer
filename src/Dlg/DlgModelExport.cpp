#include "CmdMediator.h"
#include "DlgModelExport.h"

DlgModelExport::DlgModelExport() :
  m_exportPointsSelectionFunctions (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES),
  m_exportPointsSelectionRelations (EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE),
  m_exportLayoutFunctions (EXPORT_LAYOUT_ALL_PER_LINE),
  m_exportDelimiter (EXPORT_DELIMITER_COMMA),
  m_exportHeader (EXPORT_HEADER_SIMPLE)
{
}

DlgModelExport::DlgModelExport (const CmdMediator &cmdMediator) :
  m_exportPointsSelectionFunctions (cmdMediator.document().dlgModelExport().exportPointsSelectionFunctions()),
  m_exportPointsSelectionRelations (cmdMediator.document().dlgModelExport().exportPointsSelectionRelations()),
  m_exportLayoutFunctions (cmdMediator.document().dlgModelExport().exportLayoutFunctions()),
  m_exportDelimiter (cmdMediator.document().dlgModelExport().exportDelimiter()),
  m_exportHeader (cmdMediator.document().dlgModelExport().exportHeader())
{
}

DlgModelExport::DlgModelExport(const DlgModelExport &other) :
  m_exportPointsSelectionFunctions (other.exportPointsSelectionFunctions()),
  m_exportPointsSelectionRelations (other.exportPointsSelectionRelations()),
  m_exportLayoutFunctions (other.exportLayoutFunctions()),
  m_exportDelimiter (other.exportDelimiter()),
  m_exportHeader (other.exportHeader())
{

}

DlgModelExport &DlgModelExport::operator=(const DlgModelExport &other)
{
  m_exportPointsSelectionFunctions = other.exportPointsSelectionFunctions();
  m_exportPointsSelectionRelations = other.exportPointsSelectionRelations();
  m_exportLayoutFunctions = other.exportLayoutFunctions();
  m_exportDelimiter = other.exportDelimiter();
  m_exportHeader = other.exportHeader();

  return *this;
}

QStringList DlgModelExport::curveNamesNotExported() const
{
  return m_curveNamesNotExported;
}

ExportDelimiter DlgModelExport::exportDelimiter() const
{
  return m_exportDelimiter;
}

ExportHeader DlgModelExport::exportHeader() const
{
  return m_exportHeader;
}

ExportLayoutFunctions DlgModelExport::exportLayoutFunctions() const
{
  return m_exportLayoutFunctions;
}

ExportPointsSelectionFunctions DlgModelExport::exportPointsSelectionFunctions() const
{
  return m_exportPointsSelectionFunctions;
}

ExportPointsSelectionRelations DlgModelExport::exportPointsSelectionRelations() const
{
  return m_exportPointsSelectionRelations;
}

void DlgModelExport::setCurveNamesNotExported(const QStringList &curveNamesNotExported)
{
  m_curveNamesNotExported = curveNamesNotExported;
}

void DlgModelExport::setExportDelimiter(ExportDelimiter exportDelimiter)
{
  m_exportDelimiter = exportDelimiter;
}

void DlgModelExport::setExportHeader(ExportHeader exportHeader)
{
  m_exportHeader = exportHeader;
}

void DlgModelExport::setExportLayoutFunctions(ExportLayoutFunctions exportLayoutFunctions)
{
  m_exportLayoutFunctions = exportLayoutFunctions;
}

void DlgModelExport::setExportPointsSelectionFunctions(ExportPointsSelectionFunctions exportPointsSelectionFunctions)
{
  m_exportPointsSelectionFunctions = exportPointsSelectionFunctions;
}

void DlgModelExport::setExportPointsSelectionRelations(ExportPointsSelectionRelations exportPointsSelectionRelations)
{
  m_exportPointsSelectionRelations = exportPointsSelectionRelations;
}
