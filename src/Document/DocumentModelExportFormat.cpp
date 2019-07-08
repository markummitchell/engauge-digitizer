/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DocumentModelExportFormat.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include  <QObject>
#include <QSettings>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Settings.h"
#include "Xml.h"

const QStringList DEFAULT_CURVE_NAMES_NOT_EXPORTED;
const double DEFAULT_POINTS_INTERVAL_FUNCTIONS = 10; // Consistent with DEFAULT_POINTS_INTERVAL_UNITS_FUNCTIONS
const double DEFAULT_POINTS_INTERVAL_RELATIONS = 10; // Consistent with DEFAULT_POINTS_INTERVAL_UNITS_RELATIONS
const QString DEFAULT_X_LABEL ("x");
const ExportPointsIntervalUnits DEFAULT_POINTS_INTERVAL_UNITS_FUNCTIONS = EXPORT_POINTS_INTERVAL_UNITS_SCREEN; // Consistent with DEFAULT_POINTS_INTERVAL_FUNCTIONS
const ExportPointsIntervalUnits DEFAULT_POINTS_INTERVAL_UNITS_RELATIONS = EXPORT_POINTS_INTERVAL_UNITS_SCREEN; // Consistent with DEFAULT_POINTS_INTERVAL_RELATIONS
const bool DEFAULT_EXPORT_DELIMITER_OVERRIDE = false; // Target beginner users who expect simplest behavior. Issue #169
const bool DEFAULT_EXTRAPOLATE = true; // Traditional behavior before version 11

DocumentModelExportFormat::DocumentModelExportFormat()
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_EXPORT);

  // Sync these settings with DlgSettingsExportFormat::slotLoadDefault()
  // and DlgSettingsExportFormat::slotSaveDefault()
  m_curveNamesNotExported = settings.value (SETTINGS_EXPORT_CURVE_NAMES_NOT_EXPORTED,
                                            QVariant (DEFAULT_CURVE_NAMES_NOT_EXPORTED)).toStringList();
  m_delimiter = static_cast<ExportDelimiter> (settings.value (SETTINGS_EXPORT_DELIMITER,
                                                              QVariant (EXPORT_DELIMITER_COMMA)).toInt());  
  m_extrapolateOutsideEndpoints = settings.value (SETTINGS_EXPORT_EXTRAPOLATE_OUTSIDE_ENDPOINTS,
                                                  QVariant (DEFAULT_EXTRAPOLATE)).toBool();
  m_overrideCsvTsv = settings.value (SETTINGS_EXPORT_DELIMITER_OVERRIDE_CSV_TSV,
                                     QVariant (DEFAULT_EXPORT_DELIMITER_OVERRIDE)).toBool();
  m_header = static_cast<ExportHeader> (settings.value (SETTINGS_EXPORT_HEADER,
                                                        QVariant (EXPORT_HEADER_SIMPLE)).toInt());
  m_layoutFunctions = static_cast<ExportLayoutFunctions> (settings.value (SETTINGS_EXPORT_LAYOUT_FUNCTIONS,
                                                                          QVariant (EXPORT_LAYOUT_ALL_PER_LINE)).toInt());
  m_pointsIntervalFunctions = settings.value (SETTINGS_EXPORT_POINTS_INTERVAL_FUNCTIONS,
                                              QVariant (DEFAULT_POINTS_INTERVAL_FUNCTIONS)).toDouble();
  m_pointsIntervalRelations = settings.value (SETTINGS_EXPORT_POINTS_INTERVAL_RELATIONS,
                                              QVariant (DEFAULT_POINTS_INTERVAL_RELATIONS)).toDouble();
  m_pointsIntervalUnitsFunctions = static_cast<ExportPointsIntervalUnits> (settings.value (SETTINGS_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS,
                                                                                           QVariant (DEFAULT_POINTS_INTERVAL_UNITS_FUNCTIONS)).toInt());
  m_pointsIntervalUnitsRelations = static_cast<ExportPointsIntervalUnits> (settings.value (SETTINGS_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS,
                                                                                           QVariant (DEFAULT_POINTS_INTERVAL_UNITS_RELATIONS)).toInt());
  m_pointsSelectionFunctions = static_cast<ExportPointsSelectionFunctions> (settings.value (SETTINGS_EXPORT_POINTS_SELECTION_FUNCTIONS,
                                                                                            QVariant (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES)).toInt());
  m_pointsSelectionRelations = static_cast<ExportPointsSelectionRelations> (settings.value (SETTINGS_EXPORT_POINTS_SELECTION_RELATIONS,
                                                                                            QVariant (EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE)).toInt());
  m_xLabel = settings.value (SETTINGS_EXPORT_X_LABEL,
                             QVariant (DEFAULT_X_LABEL)).toString();
}

DocumentModelExportFormat::DocumentModelExportFormat (const Document &document) :
  m_curveNamesNotExported (document.modelExport().curveNamesNotExported()),
  m_pointsSelectionFunctions (document.modelExport().pointsSelectionFunctions()),
  m_pointsIntervalFunctions (document.modelExport().pointsIntervalFunctions()),
  m_pointsIntervalUnitsFunctions (document.modelExport().pointsIntervalUnitsFunctions()),
  m_pointsSelectionRelations (document.modelExport().pointsSelectionRelations()),
  m_pointsIntervalRelations (document.modelExport().pointsIntervalRelations()),
  m_pointsIntervalUnitsRelations (document.modelExport().pointsIntervalUnitsRelations()),
  m_layoutFunctions (document.modelExport().layoutFunctions()),
  m_delimiter (document.modelExport().delimiter()),
  m_extrapolateOutsideEndpoints (document.modelExport().extrapolateOutsideEndpoints()),
  m_overrideCsvTsv (document.modelExport().overrideCsvTsv()),
  m_header (document.modelExport().header()),
  m_xLabel (document.modelExport().xLabel())
{
}

DocumentModelExportFormat::DocumentModelExportFormat(const DocumentModelExportFormat &other) :
  m_curveNamesNotExported (other.curveNamesNotExported()),
  m_pointsSelectionFunctions (other.pointsSelectionFunctions()),
  m_pointsIntervalFunctions (other.pointsIntervalFunctions()),
  m_pointsIntervalUnitsFunctions (other.pointsIntervalUnitsFunctions()),
  m_pointsSelectionRelations (other.pointsSelectionRelations()),
  m_pointsIntervalRelations (other.pointsIntervalRelations()),
  m_pointsIntervalUnitsRelations (other.pointsIntervalUnitsRelations()),
  m_layoutFunctions (other.layoutFunctions()),
  m_delimiter (other.delimiter()),
  m_extrapolateOutsideEndpoints (other.extrapolateOutsideEndpoints()),
  m_overrideCsvTsv (other.overrideCsvTsv()),
  m_header (other.header()),
  m_xLabel (other.xLabel ())
{
}

DocumentModelExportFormat &DocumentModelExportFormat::operator=(const DocumentModelExportFormat &other)
{
  m_curveNamesNotExported = other.curveNamesNotExported();
  m_pointsSelectionFunctions = other.pointsSelectionFunctions();
  m_pointsIntervalFunctions = other.pointsIntervalFunctions();
  m_pointsIntervalUnitsFunctions = other.pointsIntervalUnitsFunctions();
  m_pointsSelectionRelations = other.pointsSelectionRelations();
  m_pointsIntervalRelations = other.pointsIntervalRelations();
  m_pointsIntervalUnitsRelations = other.pointsIntervalUnitsRelations();
  m_layoutFunctions = other.layoutFunctions();
  m_delimiter = other.delimiter();
  m_extrapolateOutsideEndpoints = other.extrapolateOutsideEndpoints();
  m_overrideCsvTsv = other.overrideCsvTsv();
  m_header = other.header();
  m_xLabel = other.xLabel();

  return *this;
}

QStringList DocumentModelExportFormat::curveNamesNotExported() const
{
  return m_curveNamesNotExported;
}

ExportDelimiter DocumentModelExportFormat::delimiter() const
{
  return m_delimiter;
}

bool DocumentModelExportFormat::extrapolateOutsideEndpoints() const
{
  return m_extrapolateOutsideEndpoints;
}

ExportHeader DocumentModelExportFormat::header() const
{
  return m_header;
}

ExportLayoutFunctions DocumentModelExportFormat::layoutFunctions() const
{
  return m_layoutFunctions;
}

void DocumentModelExportFormat::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelExportFormat::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  // DOCUMENT_SERIALIZE_EXPORT_EXTRAPOLATE_OUTSIDE_ENDPOINTS is specific to versions 11 and newer
  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_RELATIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_HEADER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_X_LABEL)) {

    setPointsSelectionFunctions (static_cast<ExportPointsSelectionFunctions> (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS).toInt()));
    setPointsIntervalFunctions (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_FUNCTIONS).toDouble());
    setPointsIntervalUnitsFunctions (static_cast<ExportPointsIntervalUnits> (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS).toInt()));
    setPointsSelectionRelations (static_cast<ExportPointsSelectionRelations> (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS).toInt()));
    setPointsIntervalRelations (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_RELATIONS).toDouble());
    setPointsIntervalUnitsRelations (static_cast<ExportPointsIntervalUnits> (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS).toInt()));
    setLayoutFunctions (static_cast<ExportLayoutFunctions> (attributes.value(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS).toInt()));
    setDelimiter (static_cast<ExportDelimiter> (attributes.value (DOCUMENT_SERIALIZE_EXPORT_DELIMITER).toInt()));
    if (attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER_OVERRIDE_CSV_TSV)) {

      // Boolean value
      QString stringOverrideCsvTsv = attributes.value (DOCUMENT_SERIALIZE_EXPORT_DELIMITER_OVERRIDE_CSV_TSV).toString();

      setOverrideCsvTsv(stringOverrideCsvTsv == DOCUMENT_SERIALIZE_BOOL_TRUE);
    }
    if (attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_EXTRAPOLATE_OUTSIDE_ENDPOINTS)) {

      // Boolean value
      QString stringExtrapolate = attributes.value (DOCUMENT_SERIALIZE_EXPORT_EXTRAPOLATE_OUTSIDE_ENDPOINTS).toString();
      
      setExtrapolateOutsideEndpoints (stringExtrapolate == DOCUMENT_SERIALIZE_BOOL_TRUE);
    }

    setHeader (static_cast<ExportHeader> (attributes.value(DOCUMENT_SERIALIZE_EXPORT_HEADER).toInt()));
    setXLabel (attributes.value(DOCUMENT_SERIALIZE_EXPORT_X_LABEL).toString());

    // Read element containing excluded curve names
    while ((loadNextFromReader (reader) != QXmlStreamReader::StartElement) ||
           (reader.name() != DOCUMENT_SERIALIZE_EXPORT_CURVE_NAMES_NOT_EXPORTED)) {

      if (reader.atEnd()) {
        success = false;
        break;
      }
    }

    if (success) {

      QStringList curveNamesNotExported;

      QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);
      while (tokenType == QXmlStreamReader::StartElement) {

        if (reader.name() == DOCUMENT_SERIALIZE_EXPORT_CURVE_NAME_NOT_EXPORTED) {
          curveNamesNotExported << reader.text().toString();
        }
        tokenType = loadNextFromReader(reader);
      }

      // Save curve names
      setCurveNamesNotExported(curveNamesNotExported);

      // Read until end of this subtree
      while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
      (reader.name() != DOCUMENT_SERIALIZE_EXPORT)){
        loadNextFromReader(reader);
        if (reader.atEnd()) {
          success = false;
          break;
        }
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read export data"));
  }
}

bool DocumentModelExportFormat::overrideCsvTsv() const
{
  return m_overrideCsvTsv;
}

double DocumentModelExportFormat::pointsIntervalFunctions() const
{
  return m_pointsIntervalFunctions;
}

double DocumentModelExportFormat::pointsIntervalRelations() const
{
  return m_pointsIntervalRelations;
}

ExportPointsIntervalUnits DocumentModelExportFormat::pointsIntervalUnitsFunctions() const
{
  return m_pointsIntervalUnitsFunctions;
}

ExportPointsIntervalUnits DocumentModelExportFormat::pointsIntervalUnitsRelations() const
{
  return m_pointsIntervalUnitsRelations;
}

ExportPointsSelectionFunctions DocumentModelExportFormat::pointsSelectionFunctions() const
{
  return m_pointsSelectionFunctions;
}

ExportPointsSelectionRelations DocumentModelExportFormat::pointsSelectionRelations() const
{
  return m_pointsSelectionRelations;
}

void DocumentModelExportFormat::printStream(QString indentation,
                                            QTextStream &str) const
{
  str << indentation << "DocumentModelExportFormat\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "curveNamesNotExported=";
  QStringList::const_iterator itr;
  for (itr = m_curveNamesNotExported.begin (); itr != m_curveNamesNotExported.end(); itr++) {
    QString curveName = *itr;
    str << indentation << curveName << " ";
  }
  str << "\n";

  str << indentation << "exportPointsSelectionFunctions=" 
      << exportPointsSelectionFunctionsToString (m_pointsSelectionFunctions) << "\n";
  str << indentation << "pointsIntervalFunctions=" << m_pointsIntervalFunctions << "\n";
  str << indentation << "pointsIntervalUnitsFunctions="
      << exportPointsIntervalUnitsToString (m_pointsIntervalUnitsFunctions) << "\n";
  str << indentation << "exportPointsSelectionRelations=" 
      << exportPointsSelectionRelationsToString (m_pointsSelectionRelations) << "\n";
  str << indentation << "pointsIntervalRelations=" << m_pointsIntervalRelations << "\n";
  str << indentation << "pointsIntervalUnitsRelations="
      << exportPointsIntervalUnitsToString (m_pointsIntervalUnitsRelations) << "\n";
  str << indentation << "exportLayoutFunctions=" << exportLayoutFunctionsToString (m_layoutFunctions) << "\n";
  str << indentation << "exportDelimiter=" << exportDelimiterToString (m_delimiter) << "\n";
  str << indentation << "exportExtrapolateOutsideEndpoints=" << (m_extrapolateOutsideEndpoints ? "yes" : "no") << "\n";
  str << indentation << "overrideCsvTsv=" << (m_overrideCsvTsv ? "true" : "false") << "\n";
  str << indentation << "exportHeader=" << exportHeaderToString (m_header) << "\n";
  str << indentation << "xLabel=" << m_xLabel << "\n";
}

void DocumentModelExportFormat::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelExportFormat::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_EXPORT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS, QString::number (m_pointsSelectionFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS_STRING, exportPointsSelectionFunctionsToString (m_pointsSelectionFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_FUNCTIONS, QString::number (m_pointsIntervalFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS, QString::number (m_pointsIntervalUnitsFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS, QString::number (m_pointsSelectionRelations));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS_STRING, exportPointsSelectionRelationsToString (m_pointsSelectionRelations));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS, QString::number (m_pointsIntervalUnitsRelations));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_RELATIONS, QString::number (m_pointsIntervalRelations));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS, QString::number (m_layoutFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS_STRING, exportLayoutFunctionsToString (m_layoutFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER, QString::number (m_delimiter));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER_OVERRIDE_CSV_TSV, m_overrideCsvTsv ?
                        DOCUMENT_SERIALIZE_BOOL_TRUE :
                        DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER_STRING, exportDelimiterToString (m_delimiter));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_EXTRAPOLATE_OUTSIDE_ENDPOINTS, m_extrapolateOutsideEndpoints ?
                        DOCUMENT_SERIALIZE_BOOL_TRUE :
                        DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_HEADER, QString::number (m_header));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_HEADER_STRING, exportHeaderToString (m_header));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_X_LABEL, m_xLabel);

  // Loop through curve names that are not to be exported
  writer.writeStartElement(DOCUMENT_SERIALIZE_EXPORT_CURVE_NAMES_NOT_EXPORTED);
  QStringList::const_iterator itr;
  for (itr = m_curveNamesNotExported.begin (); itr != m_curveNamesNotExported.end (); itr++) {
    QString curveNameNotExported = *itr;
    writer.writeStartElement(DOCUMENT_SERIALIZE_EXPORT_CURVE_NAME_NOT_EXPORTED);
    writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_CURVE_NAME_NOT_EXPORTED_NAME, curveNameNotExported);
    writer.writeEndElement();
  }
  writer.writeEndElement();

  writer.writeEndElement();
}

void DocumentModelExportFormat::setCurveNamesNotExported(const QStringList &curveNamesNotExported)
{
  m_curveNamesNotExported = curveNamesNotExported;
}

void DocumentModelExportFormat::setDelimiter(ExportDelimiter delimiter)
{
  m_delimiter = delimiter;
}

void DocumentModelExportFormat::setExtrapolateOutsideEndpoints(bool extrapolateOutsideEndpoints)
{
  m_extrapolateOutsideEndpoints = extrapolateOutsideEndpoints;
}

void DocumentModelExportFormat::setHeader(ExportHeader header)
{
  m_header = header;
}

void DocumentModelExportFormat::setLayoutFunctions(ExportLayoutFunctions layoutFunctions)
{
  m_layoutFunctions = layoutFunctions;
}

void DocumentModelExportFormat::setOverrideCsvTsv(bool overrideCsvTsv)
{
  m_overrideCsvTsv = overrideCsvTsv;
}

void DocumentModelExportFormat::setPointsIntervalFunctions(double pointsIntervalFunctions)
{
  m_pointsIntervalFunctions = pointsIntervalFunctions;
}

void DocumentModelExportFormat::setPointsIntervalRelations(double pointsIntervalRelations)
{
  m_pointsIntervalRelations = pointsIntervalRelations;
}

void DocumentModelExportFormat::setPointsIntervalUnitsFunctions(ExportPointsIntervalUnits pointsIntervalUnitsFunctions)
{
  m_pointsIntervalUnitsFunctions = pointsIntervalUnitsFunctions;
}

void DocumentModelExportFormat::setPointsIntervalUnitsRelations(ExportPointsIntervalUnits pointsIntervalUnitsRelations)
{
  m_pointsIntervalUnitsRelations = pointsIntervalUnitsRelations;
}

void DocumentModelExportFormat::setPointsSelectionFunctions(ExportPointsSelectionFunctions pointsSelectionFunctions)
{
  m_pointsSelectionFunctions = pointsSelectionFunctions;
}

void DocumentModelExportFormat::setPointsSelectionRelations(ExportPointsSelectionRelations pointsSelectionRelations)
{
  m_pointsSelectionRelations = pointsSelectionRelations;
}

void DocumentModelExportFormat::setXLabel (const QString &xLabel)
{
  m_xLabel = xLabel;
}

QString DocumentModelExportFormat::xLabel () const
{
  return m_xLabel;
}
