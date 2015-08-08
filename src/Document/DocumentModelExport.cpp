#include "CmdMediator.h"
#include "DocumentModelExport.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const QStringList DEFAULT_CURVE_NAMES_NOT_EXPORTED;
const double DEFAULT_POINTS_INTERVAL_FUNCTIONS = 10; // Consistent with DEFAULT_POINTS_INTERVAL_UNITS_FUNCTIONS
const double DEFAULT_POINTS_INTERVAL_RELATIONS = 10; // Consistent with DEFAULT_POINTS_INTERVAL_UNITS_RELATIONS
const QString DEFAULT_X_LABEL ("x");
const ExportPointsIntervalUnits DEFAULT_POINTS_INTERVAL_UNITS_FUNCTIONS = EXPORT_POINTS_INTERVAL_UNITS_SCREEN; // Consistent with DEFAULT_POINTS_INTERVAL_FUNCTIONS
const ExportPointsIntervalUnits DEFAULT_POINTS_INTERVAL_UNITS_RELATIONS = EXPORT_POINTS_INTERVAL_UNITS_SCREEN; // Consistent with DEFAULT_POINTS_INTERVAL_RELATIONS

DocumentModelExport::DocumentModelExport() :
  m_curveNamesNotExported (DEFAULT_CURVE_NAMES_NOT_EXPORTED),
  m_pointsSelectionFunctions (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES),
  m_pointsIntervalFunctions (DEFAULT_POINTS_INTERVAL_FUNCTIONS),
  m_pointsIntervalUnitsFunctions (DEFAULT_POINTS_INTERVAL_UNITS_FUNCTIONS),
  m_pointsSelectionRelations (EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE),
  m_pointsIntervalRelations (DEFAULT_POINTS_INTERVAL_RELATIONS),
  m_pointsIntervalUnitsRelations (DEFAULT_POINTS_INTERVAL_UNITS_RELATIONS),
  m_layoutFunctions (EXPORT_LAYOUT_ALL_PER_LINE),
  m_delimiter (EXPORT_DELIMITER_COMMA),
  m_header (EXPORT_HEADER_SIMPLE),
  m_xLabel (DEFAULT_X_LABEL)
{
}

DocumentModelExport::DocumentModelExport (const Document &document) :
  m_curveNamesNotExported (document.modelExport().curveNamesNotExported()),
  m_pointsSelectionFunctions (document.modelExport().pointsSelectionFunctions()),
  m_pointsIntervalFunctions (document.modelExport().pointsIntervalFunctions()),
  m_pointsIntervalUnitsFunctions (document.modelExport().pointsIntervalUnitsFunctions()),
  m_pointsSelectionRelations (document.modelExport().pointsSelectionRelations()),
  m_pointsIntervalRelations (document.modelExport().pointsIntervalRelations()),
  m_pointsIntervalUnitsRelations (document.modelExport().pointsIntervalUnitsRelations()),
  m_layoutFunctions (document.modelExport().layoutFunctions()),
  m_delimiter (document.modelExport().delimiter()),
  m_header (document.modelExport().header()),
  m_xLabel (document.modelExport().xLabel())
{
}

DocumentModelExport::DocumentModelExport(const DocumentModelExport &other) :
  m_curveNamesNotExported (other.curveNamesNotExported()),
  m_pointsSelectionFunctions (other.pointsSelectionFunctions()),
  m_pointsIntervalFunctions (other.pointsIntervalFunctions()),
  m_pointsIntervalUnitsFunctions (other.pointsIntervalUnitsFunctions()),
  m_pointsSelectionRelations (other.pointsSelectionRelations()),
  m_pointsIntervalRelations (other.pointsIntervalRelations()),
  m_pointsIntervalUnitsRelations (other.pointsIntervalUnitsRelations()),
  m_layoutFunctions (other.layoutFunctions()),
  m_delimiter (other.delimiter()),
  m_header (other.header()),
  m_xLabel (other.xLabel ())
{

}

DocumentModelExport &DocumentModelExport::operator=(const DocumentModelExport &other)
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
  m_header = other.header();
  m_xLabel = other.xLabel();

  return *this;
}

QStringList DocumentModelExport::curveNamesNotExported() const
{
  return m_curveNamesNotExported;
}

ExportDelimiter DocumentModelExport::delimiter() const
{
  return m_delimiter;
}

ExportHeader DocumentModelExport::header() const
{
  return m_header;
}

ExportLayoutFunctions DocumentModelExport::layoutFunctions() const
{
  return m_layoutFunctions;
}

void DocumentModelExport::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelExport::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

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

    setPointsSelectionFunctions ((ExportPointsSelectionFunctions) attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS).toInt());
    setPointsIntervalFunctions (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_FUNCTIONS).toDouble());
    setPointsIntervalUnitsFunctions ((ExportPointsIntervalUnits) attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS).toInt());
    setPointsSelectionRelations ((ExportPointsSelectionRelations) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS).toInt());
    setPointsIntervalRelations (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_RELATIONS).toDouble());
    setPointsIntervalUnitsRelations ((ExportPointsIntervalUnits) attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS).toInt());
    setLayoutFunctions ((ExportLayoutFunctions) attributes.value(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS).toInt());
    setDelimiter ((ExportDelimiter) attributes.value (DOCUMENT_SERIALIZE_EXPORT_DELIMITER).toInt());
    setHeader ((ExportHeader) attributes.value(DOCUMENT_SERIALIZE_EXPORT_HEADER).toInt());
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
    reader.raiseError ("Cannot read export data");
  }
}

double DocumentModelExport::pointsIntervalFunctions() const
{
  return m_pointsIntervalFunctions;
}

double DocumentModelExport::pointsIntervalRelations() const
{
  return m_pointsIntervalRelations;
}

ExportPointsIntervalUnits DocumentModelExport::pointsIntervalUnitsFunctions() const
{
  return m_pointsIntervalUnitsFunctions;
}

ExportPointsIntervalUnits DocumentModelExport::pointsIntervalUnitsRelations() const
{
  return m_pointsIntervalUnitsRelations;
}

ExportPointsSelectionFunctions DocumentModelExport::pointsSelectionFunctions() const
{
  return m_pointsSelectionFunctions;
}

ExportPointsSelectionRelations DocumentModelExport::pointsSelectionRelations() const
{
  return m_pointsSelectionRelations;
}

void DocumentModelExport::printStream(QString indentation,
                                      QTextStream &str) const
{
  str << indentation << "DocumentModelExport\n";

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
  str << indentation << "exportHeader=" << exportHeaderToString (m_header) << "\n";
  str << indentation << "xLabel=" << m_xLabel << "\n";
}

void DocumentModelExport::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelExport::saveXml";

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
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER_STRING, exportDelimiterToString (m_delimiter));
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

void DocumentModelExport::setCurveNamesNotExported(const QStringList &curveNamesNotExported)
{
  m_curveNamesNotExported = curveNamesNotExported;
}

void DocumentModelExport::setDelimiter(ExportDelimiter delimiter)
{
  m_delimiter = delimiter;
}

void DocumentModelExport::setHeader(ExportHeader header)
{
  m_header = header;
}

void DocumentModelExport::setLayoutFunctions(ExportLayoutFunctions layoutFunctions)
{
  m_layoutFunctions = layoutFunctions;
}

void DocumentModelExport::setPointsIntervalFunctions(double pointsIntervalFunctions)
{
  m_pointsIntervalFunctions = pointsIntervalFunctions;
}

void DocumentModelExport::setPointsIntervalRelations(double pointsIntervalRelations)
{
  m_pointsIntervalRelations = pointsIntervalRelations;
}

void DocumentModelExport::setPointsIntervalUnitsFunctions(ExportPointsIntervalUnits pointsIntervalUnitsFunctions)
{
  m_pointsIntervalUnitsFunctions = pointsIntervalUnitsFunctions;
}

void DocumentModelExport::setPointsIntervalUnitsRelations(ExportPointsIntervalUnits pointsIntervalUnitsRelations)
{
  m_pointsIntervalUnitsRelations = pointsIntervalUnitsRelations;
}

void DocumentModelExport::setPointsSelectionFunctions(ExportPointsSelectionFunctions pointsSelectionFunctions)
{
  m_pointsSelectionFunctions = pointsSelectionFunctions;
}

void DocumentModelExport::setPointsSelectionRelations(ExportPointsSelectionRelations pointsSelectionRelations)
{
  m_pointsSelectionRelations = pointsSelectionRelations;
}

void DocumentModelExport::setXLabel (const QString &xLabel)
{
  m_xLabel = xLabel;
}

QString DocumentModelExport::xLabel () const
{
  return m_xLabel;
}
