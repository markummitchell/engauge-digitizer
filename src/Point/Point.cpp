#include "DocumentSerialize.h"
#include "Logger.h"
#include "Point.h"
#include <QStringList>
#include <QXmlStreamWriter>

unsigned int Point::m_identifierIndex = 0;

const QString POINT_IDENTIFIER_DELIMITER ("_");

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QPointF posGraph) :
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_posGraph (posGraph),
  m_ordinal (0)
{
  Q_ASSERT (!curveName.isEmpty ());
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
  Q_ASSERT (!curveName.isEmpty ());
}

Point::Point (const Point &point)
{
  m_posScreen = point.posScreen ();
  m_posGraph = point.posGraph ();
  m_identifier = point.identifier ();
  m_ordinal = point.ordinal ();
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

void Point::saveDocument(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::saveDocument";

  stream.writeStartElement(DOCUMENT_SERIALIZE_POINT);
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER, m_identifier);
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_ORDINAL, QString::number (m_ordinal));

  // Variable m_identifierIndex is static, but for simplicity this is handled like other values. Those values are all
  // the same, but simplicity wins over a few extra bytes of storage
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX, QString::number (m_identifierIndex));

  stream.writeStartElement(DOCUMENT_SERIALIZE_POINT_POSITION_SCREEN);
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_posScreen.x()));
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_posScreen.y()));
  stream.writeEndElement();

  stream.writeStartElement(DOCUMENT_SERIALIZE_POINT_POSITION_GRAPH);
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_posGraph.x()));
  stream.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_posGraph.y()));
  stream.writeEndElement();

  stream.writeEndElement();
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
