#include "CmdMediator.h"
#include "DocumentModelExport.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QXmlStreamWriter>
#include "Xml.h"

const QStringList DEFAULT_CURVE_NAMES_NOT_EXPORTED;
const double DEFAULT_POINTS_INTERVAL = 1.0; // Although rarely the right value, value of one is better than zero (=infinite loops)
const double DEFAULT_RELATIONS_INTERVAL = DEFAULT_POINTS_INTERVAL;
const QString DEFAULT_X_LABEL ("x");

DocumentModelExport::DocumentModelExport() :
  m_curveNamesNotExported (DEFAULT_CURVE_NAMES_NOT_EXPORTED),
  m_pointsSelectionFunctions (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES),
  m_pointsInterval (DEFAULT_POINTS_INTERVAL),
  m_pointsSelectionRelations (EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE),
  m_relationsInterval (DEFAULT_RELATIONS_INTERVAL),
  m_layoutFunctions (EXPORT_LAYOUT_ALL_PER_LINE),
  m_delimiter (EXPORT_DELIMITER_COMMA),
  m_header (EXPORT_HEADER_SIMPLE),
  m_xLabel (DEFAULT_X_LABEL)
{
}

DocumentModelExport::DocumentModelExport (const Document &document) :
  m_curveNamesNotExported (document.modelExport().curveNamesNotExported()),
  m_pointsSelectionFunctions (document.modelExport().pointsSelectionFunctions()),
  m_pointsInterval (document.modelExport().pointsInterval()),
  m_pointsSelectionRelations (document.modelExport().pointsSelectionRelations()),
  m_relationsInterval (document.modelExport().relationsInterval()),
  m_layoutFunctions (document.modelExport().layoutFunctions()),
  m_delimiter (document.modelExport().delimiter()),
  m_header (document.modelExport().header()),
  m_xLabel (document.modelExport().xLabel())
{
}

DocumentModelExport::DocumentModelExport(const DocumentModelExport &other) :
  m_curveNamesNotExported (other.curveNamesNotExported()),
  m_pointsSelectionFunctions (other.pointsSelectionFunctions()),
  m_pointsInterval (other.pointsInterval()),
  m_pointsSelectionRelations (other.pointsSelectionRelations()),
  m_relationsInterval (other.relationsInterval()),
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
  m_pointsInterval = other.pointsInterval();
  m_pointsSelectionRelations = other.pointsSelectionRelations();
  m_relationsInterval = other.relationsInterval();
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
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_RELATIONS_INTERVAL) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_HEADER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_X_LABEL)) {

    setPointsSelectionFunctions ((ExportPointsSelectionFunctions) attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS).toInt());
    setPointsInterval (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL).toDouble());
    setPointsSelectionRelations ((ExportPointsSelectionRelations) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS).toInt());
    setRelationsInterval (attributes.value(DOCUMENT_SERIALIZE_EXPORT_RELATIONS_INTERVAL).toDouble());
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

double DocumentModelExport::pointsInterval() const
{
  return m_pointsInterval;
}

ExportPointsSelectionFunctions DocumentModelExport::pointsSelectionFunctions() const
{
  return m_pointsSelectionFunctions;
}

ExportPointsSelectionRelations DocumentModelExport::pointsSelectionRelations() const
{
  return m_pointsSelectionRelations;
}

double DocumentModelExport::relationsInterval() const
{
  return m_relationsInterval;
}

void DocumentModelExport::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelExport::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_EXPORT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS, QString::number (m_pointsSelectionFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL, QString::number (m_pointsInterval));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS, QString::number (m_pointsSelectionRelations));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_RELATIONS_INTERVAL, QString::number (m_relationsInterval));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS, QString::number (m_layoutFunctions));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER, QString::number (m_delimiter));
  writer.writeAttribute(DOCUMENT_SERIALIZE_EXPORT_HEADER, QString::number (m_header));
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

void DocumentModelExport::setPointsInterval(double pointsInterval)
{
  m_pointsInterval = pointsInterval;
}

void DocumentModelExport::setPointsSelectionFunctions(ExportPointsSelectionFunctions pointsSelectionFunctions)
{
  m_pointsSelectionFunctions = pointsSelectionFunctions;
}

void DocumentModelExport::setRelationsInterval(double relationsInterval)
{
  m_relationsInterval = relationsInterval;
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
