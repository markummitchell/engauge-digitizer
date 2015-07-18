#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <QStringList>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

unsigned int Point::m_identifierIndex = 0;

extern const QString AXIS_CURVE_NAME;
const QString POINT_IDENTIFIER_DELIMITER ("_");

const double MISSING_ORDINAL_VALUE = 0;
const double MISSING_POSGRAPH_VALUE = 0;

Point::Point ()
{
}

Point::Point(const QString &curveName,
             const QPointF &posScreen) :
  m_isAxisPoint (curveName == AXIS_CURVE_NAME),
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_hasPosGraph (false),
  m_posGraph (MISSING_POSGRAPH_VALUE, MISSING_POSGRAPH_VALUE),
  m_hasOrdinal (false),
  m_ordinal (MISSING_ORDINAL_VALUE)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point"
                              << " curveName=" << curveName.toLatin1().data()
                              << " identifierGenerated=" << m_identifier.toLatin1().data()
                              << " posScreen=" << QPointFToString (posScreen).toLatin1().data();

  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QPointF &posGraph) :
  m_isAxisPoint (true),
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_hasPosGraph (true),
  m_posGraph (posGraph),
  m_hasOrdinal (false),
  m_ordinal (MISSING_ORDINAL_VALUE)
{
  ENGAUGE_ASSERT (curveName == AXIS_CURVE_NAME);

  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point"
                              << " curveName=" << curveName.toLatin1().data()
                              << " identifierGenerated=" << m_identifier.toLatin1().data()
                              << " posScreen=" << QPointFToString (posScreen).toLatin1().data()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1().data();

  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point(const QString &curveName,
             const QString &identifier,
             const QPointF &posScreen,
             const QPointF &posGraph,
             double ordinal) :
  m_isAxisPoint (true),
  m_identifier (identifier),
  m_posScreen (posScreen),
  m_hasPosGraph (true),
  m_posGraph (posGraph),
  m_hasOrdinal (true),
  m_ordinal (ordinal)
{
  ENGAUGE_ASSERT (curveName == AXIS_CURVE_NAME);

  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point"
                              << " curveName=" << curveName.toLatin1().data()
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " posScreen=" << QPointFToString (posScreen).toLatin1().data()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1().data()
                              << " ordinal=" << ordinal;

  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QPointF &posGraph,
             double ordinal) :
  m_isAxisPoint (true),
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_hasPosGraph (true),
  m_posGraph (posGraph),
  m_hasOrdinal (true),
  m_ordinal (ordinal)
{
  ENGAUGE_ASSERT (curveName == AXIS_CURVE_NAME);

  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point"
                              << " curveName=" << curveName.toLatin1().data()
                              << " identifierGenerated=" << m_identifier.toLatin1().data()
                              << " posScreen=" << QPointFToString (posScreen).toLatin1().data()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1().data()
                              << " ordinal=" << ordinal;

  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point(const QString &curveName,
             const QString &identifier,
             const QPointF &posScreen,
             double ordinal) :
  m_isAxisPoint (false),
  m_identifier (identifier),
  m_posScreen (posScreen),
  m_hasPosGraph (false),
  m_posGraph (MISSING_POSGRAPH_VALUE, MISSING_POSGRAPH_VALUE),
  m_hasOrdinal (true),
  m_ordinal (ordinal)
{
  ENGAUGE_ASSERT (curveName != AXIS_CURVE_NAME);

  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point"
                              << " curveName=" << curveName.toLatin1().data()
                              << " identifier=" << identifier.toLatin1().data()
                              << " posScreen=" << QPointFToString (posScreen).toLatin1().data()
                              << " ordinal=" << ordinal;

  ENGAUGE_ASSERT (!curveName.isEmpty ());
}

Point::Point (const QString &curveName,
              const QPointF &posScreen,
              double ordinal) :
  m_isAxisPoint (false),
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_hasPosGraph (false),
  m_posGraph (MISSING_POSGRAPH_VALUE, MISSING_POSGRAPH_VALUE),
  m_hasOrdinal (true),
  m_ordinal (ordinal)
{
  ENGAUGE_ASSERT (curveName != AXIS_CURVE_NAME);

  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point(identifier,posScreen,posGraph,ordinal)"
                              << " identifierGenerated=" << m_identifier.toLatin1().data()
                              << " posScreen=" << QPointFToString (posScreen).toLatin1().data()
                              << " ordinal=" << ordinal;
}

Point::Point (QXmlStreamReader &reader)
{
  loadXml(reader);
}

Point &Point::operator=(const Point &point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::operator="
                              << " isAxisPoint=" << (point.isAxisPoint() ? "true" : "false")
                              << " identifier=" << point.identifier ().toLatin1().data()
                              << " posScreen=" << QPointFToString (point.posScreen ()).toLatin1().data()
                              << " hasPosGraph=" << (point.hasPosGraph() ? "true" : "false")
                              << " posGraph=" << QPointFToString (point.posGraph (SKIP_HAS_CHECK)).toLatin1().data()
                              << " hasOrdinal=" << (point.hasOrdinal() ? "true" : "false")
                              << " ordinal=" << point.ordinal (SKIP_HAS_CHECK);

  m_isAxisPoint = point.isAxisPoint ();
  m_identifier = point.identifier ();
  m_posScreen = point.posScreen ();
  m_hasPosGraph = point.hasPosGraph ();
  m_posGraph = point.posGraph (SKIP_HAS_CHECK);
  m_hasOrdinal = point.hasOrdinal ();
  m_ordinal = point.ordinal (SKIP_HAS_CHECK);

  return *this;
}

Point::Point (const Point &other)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::Point(const Point &other)"
                              << " isAxisPoint=" << (other.isAxisPoint() ? "true" : "false")
                              << " identifier=" << other.identifier ().toLatin1().data()
                              << " posScreen=" << QPointFToString (other.posScreen ()).toLatin1().data()
                              << " hasPosGraph=" << (other.hasPosGraph() ? "true" : "false")
                              << " posGraph=" << QPointFToString (other.posGraph (SKIP_HAS_CHECK)).toLatin1().data()
                              << " hasOrdinal=" << (other.hasOrdinal() ? "true" : "false")
                              << " ordinal=" << other.ordinal (SKIP_HAS_CHECK);

  m_isAxisPoint = other.isAxisPoint ();
  m_identifier = other.identifier ();
  m_posScreen = other.posScreen ();
  m_hasPosGraph = other.hasPosGraph ();
  m_posGraph = other.posGraph (SKIP_HAS_CHECK);
  m_hasOrdinal = other.hasOrdinal ();
  m_ordinal = other.ordinal (SKIP_HAS_CHECK);
}

QString Point::curveNameFromPointIdentifier (const QString &pointIdentifier)
{
  QStringList tokens = pointIdentifier.split (POINT_IDENTIFIER_DELIMITER);
  return tokens.value (0);
}

bool Point::hasOrdinal () const
{
  return m_hasOrdinal;
}

bool Point::hasPosGraph () const
{
  return m_hasPosGraph;
}

QString Point::identifier() const
{
  return m_identifier;
}

unsigned int Point::identifierIndex ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::identifierIndex"
                              << " identifierIndex=" << m_identifierIndex;

  return m_identifierIndex;
}

bool Point::isAxisPoint() const
{
  return m_isAxisPoint;
}

void Point::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IS_AXIS_POINT)) {

    m_hasOrdinal = attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_ORDINAL);
    if (m_hasOrdinal) {
      m_ordinal = attributes.value(DOCUMENT_SERIALIZE_POINT_ORDINAL).toDouble();
    } else {
      m_ordinal = MISSING_ORDINAL_VALUE;
    }

    QString isAxisPoint = attributes.value(DOCUMENT_SERIALIZE_POINT_IS_AXIS_POINT).toString();

    m_identifier = attributes.value(DOCUMENT_SERIALIZE_POINT_IDENTIFIER).toString();
    m_identifierIndex = attributes.value(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX).toInt();
    m_isAxisPoint = (isAxisPoint == DOCUMENT_SERIALIZE_BOOL_TRUE);
    m_hasPosGraph = false;
    m_posGraph.setX (MISSING_POSGRAPH_VALUE);
    m_posGraph.setY (MISSING_POSGRAPH_VALUE);

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

          m_hasPosGraph = true;
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

    LOG4CPP_INFO_S ((*mainCat)) << "Point::loadXml"
                                << " identifier=" << m_identifier.toLatin1().data()
                                << " identifierIndex=" << m_identifierIndex
                                << " posScreen=" << QPointFToString (m_posScreen).toLatin1().data()
                                << " posGraph=" << QPointFToString (m_posGraph).toLatin1().data()
                                << " ordinal=" << m_ordinal;

  } else {
    success = false;
  }

  if (!success) {
    reader.raiseError("Cannot read point data");
  }
}

double Point::ordinal (ApplyHasCheck applyHasCheck) const
{
  if (applyHasCheck == KEEP_HAS_CHECK) {
    ENGAUGE_ASSERT (m_hasOrdinal);
  }

  return m_ordinal;
}

QPointF Point::posGraph (ApplyHasCheck applyHasCheck) const
{
  if (applyHasCheck == KEEP_HAS_CHECK) {
    ENGAUGE_ASSERT (m_hasPosGraph);
  }

  return m_posGraph;
}

QPointF Point::posScreen () const
{
  return m_posScreen;
}

void Point::printStream(QString indentation,
                        QTextStream &str) const
{
  const QString UNDEFINED ("undefined");

  str << indentation << "Point\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "identifier=" << m_identifier << "\n";
  str << indentation << "posScreen=" << QPointFToString (m_posScreen) << "\n";
  if (m_hasPosGraph) {
    str << indentation << "posGraph=" << QPointFToString (m_posGraph) << "\n";
  } else {
    str << indentation << "posGraph=" << UNDEFINED << "\n";
  }
  if (m_hasOrdinal) {
    str << indentation << "ordinal=" << m_ordinal << "\n";
  } else {
    str << indentation << "ordinal=" << UNDEFINED << "\n";
  }
}

void Point::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER, m_identifier);
  if (m_hasOrdinal) {
    writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_ORDINAL, QString::number (m_ordinal));
  }
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IS_AXIS_POINT,
                        m_isAxisPoint ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);

  // Variable m_identifierIndex is static, but for simplicity this is handled like other values. Those values are all
  // the same, but simplicity wins over a few extra bytes of storage
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX, QString::number (m_identifierIndex));

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_POSITION_SCREEN);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_posScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_posScreen.y()));
  writer.writeEndElement();

  if (m_hasPosGraph) {
    writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_POSITION_GRAPH);
    writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_X, QString::number (m_posGraph.x()));
    writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_Y, QString::number (m_posGraph.y()));
    writer.writeEndElement();
  }

  writer.writeEndElement();
}

void Point::setIdentifierIndex (unsigned int identifierIndex)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::setIdentifierIndex"
                              << " identifierIndex=" << identifierIndex;

  m_identifierIndex = identifierIndex;
}

void Point::setOrdinal(double ordinal)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Point::setOrdinal"
                               << " identifier=" << m_identifier.toLatin1().data()
                               << " ordinal=" << ordinal;

  m_hasOrdinal = true;
  m_ordinal = ordinal;
}

void Point::setPosGraph (const QPointF &posGraph)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Point::setPosGraph"
                               << " identifier=" << m_identifier.toLatin1().data()
                               << " posGraph=" << QPointFToString(posGraph).toLatin1().data();

  // Curve point graph coordinates should always be computed on the fly versus stored in this class, to reduce the
  // chances for stale information
  ENGAUGE_ASSERT (m_isAxisPoint);

  m_hasPosGraph = true;
  m_posGraph = posGraph;
}

void Point::setPosScreen (const QPointF &posScreen)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Point::setPosScreen"
                               << " identifier=" << m_identifier.toLatin1().data()
                               << " posScreen=" << QPointFToString(posScreen).toLatin1().data();

  m_posScreen = posScreen;
}

QString Point::temporaryPointIdentifier ()
{
  return QString ("%1%2%3")
      .arg (AXIS_CURVE_NAME)
      .arg (POINT_IDENTIFIER_DELIMITER)
      .arg (0);
}

QString Point::uniqueIdentifierGenerator (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Point::uniqueIdentifierGenerator"
                              << " curveName=" << curveName.toLatin1().data()
                              << " identifierIndex=" << m_identifierIndex;

  return QString ("%1%2point%3%4")
      .arg (curveName)
      .arg (POINT_IDENTIFIER_DELIMITER)
      .arg (POINT_IDENTIFIER_DELIMITER)
      .arg (m_identifierIndex++);
}
