#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <QStringList>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

unsigned int Point::m_identifierIndex = 0;

const QString POINT_IDENTIFIER_DELIMITER ("_");

Point::Point ()
{
}

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QPointF posGraph) :
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_posGraph (posGraph),
  m_ordinal (0)
{
  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QString &identifier,
             const QPointF posGraph) :
  m_identifier (identifier),
  m_posScreen (posScreen),
  m_posGraph (posGraph),
  m_ordinal (0)
{
  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point (const Point &point)
{
  m_posScreen = point.posScreen ();
  m_posGraph = point.posGraph ();
  m_identifier = point.identifier ();
  m_ordinal = point.ordinal ();
}

Point::Point (QXmlStreamReader &reader)
{
  loadXml(reader);
}

Point &Point::operator=(const Point &point)
{
  m_posScreen = point.posScreen ();
  m_posGraph = point.posGraph ();
  m_identifier = point.identifier ();
  m_ordinal = point.ordinal ();

  return *this;
}

QString Point::curveNameFromPointIdentifier (const QString &pointIdentifier)
{
  QStringList tokens = pointIdentifier.split (POINT_IDENTIFIER_DELIMITER);
  return tokens.value (0);
}

QString Point::identifier() const
{
  return m_identifier;
}

unsigned int Point::identifierIndex ()
{
  return m_identifierIndex;
}

void Point::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_ORDINAL) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX)) {

    m_identifier = attributes.value(DOCUMENT_SERIALIZE_POINT_IDENTIFIER).toString();
    m_ordinal = attributes.value(DOCUMENT_SERIALIZE_POINT_ORDINAL).toDouble();
    m_identifierIndex = attributes.value(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX).toInt();

    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
           (reader.name () != DOCUMENT_SERIALIZE_POINT)) {

      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }

      if (reader.tokenType () == QXmlStreamReader::StartElement) {

        if (reader.name() == DOCUMENT_SERIALIZE_POINT_POSITION_SCREEN) {

          attributes = reader.attributes();

          if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_X) &&
              attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_Y)) {

            m_posScreen.setX (attributes.value(DOCUMENT_SERIALIZE_POINT_X).toDouble());
            m_posScreen.setY (attributes.value(DOCUMENT_SERIALIZE_POINT_Y).toDouble());

          } else {
            success = false;
            break;
          }
        } else if (reader.name() == DOCUMENT_SERIALIZE_POINT_POSITION_GRAPH) {

          attributes = reader.attributes();

          if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_X) &&
              attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_Y)) {

            m_posGraph.setX (attributes.value(DOCUMENT_SERIALIZE_POINT_X).toDouble());
            m_posGraph.setY (attributes.value(DOCUMENT_SERIALIZE_POINT_Y).toDouble());

          } else {
            success = false;
            break;
          }
        }
      }
    }
  } else {
    success = false;
  }

  if (!success) {
    reader.raiseError("Cannot read point data");
  }
}

double Point::ordinal () const
{
  return m_ordinal;
}

QPointF Point::posGraph () const
{
  return m_posGraph;
}

QPointF Point::posScreen () const
{
  return m_posScreen;
}

void Point::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER, m_identifier);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_ORDINAL, QString::number (m_ordinal));

  // Variable m_identifierIndex is static, but for simplicity this is handled like other values. Those values are all
  // the same, but simplicity wins over a few extra bytes of storage
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX, QString::number (m_identifierIndex));

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_POSITION_SCREEN);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_posScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_posScreen.y()));
  writer.writeEndElement();

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_POSITION_GRAPH);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_posGraph.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_posGraph.y()));
  writer.writeEndElement();

  writer.writeEndElement();
}

void Point::setIdentifierIndex (unsigned int identifierIndex)
{
  m_identifierIndex = identifierIndex;
}

void Point::setOrdinal(double ordinal)
{
  m_ordinal = ordinal;
}

void Point::setPosGraph (const QPointF &posGraph)
{
  m_posGraph = posGraph;
}

void Point::setPosScreen (const QPointF &posScreen)
{
  m_posScreen = posScreen;
}

QString Point::uniqueIdentifierGenerator (const QString &curveName)
{
  return QString ("%1%2point%3%4")
      .arg (curveName)
      .arg (POINT_IDENTIFIER_DELIMITER)
      .arg (POINT_IDENTIFIER_DELIMITER)
      .arg (m_identifierIndex++);
}
