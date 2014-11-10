#include "Point.h"
#include <QStringList>

unsigned int Point::m_identifierIndex = 0;

const QString POINT_IDENTIFIER_DELIMITER ("_");

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QPointF posGraph) :
  m_identifier (uniqueIdentifierGenerator(curveName)),
  m_posScreen (posScreen),
  m_posGraph (posGraph)
{
  Q_ASSERT (!curveName.isEmpty ());
}

Point::Point(const QString &curveName,
             const QPointF &posScreen,
             const QString &identifier,
             const QPointF posGraph) :
  m_identifier (identifier),
  m_posScreen (posScreen),
  m_posGraph (posGraph)
{
  Q_ASSERT (!curveName.isEmpty ());
}

Point::Point (const Point &point)
{
  m_posScreen = point.posScreen ();
  m_posGraph = point.posGraph ();
  m_identifier = point.identifier ();
}

Point &Point::operator=(const Point &point)
{
  m_posScreen = point.posScreen ();
  m_posGraph = point.posGraph ();
  m_identifier = point.identifier ();

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

QPointF Point::posGraph () const
{
  return m_posGraph;
}

QPointF Point::posScreen () const
{
  return m_posScreen;
}

void Point::setIdentifierIndex (unsigned int identifierIndex)
{
  m_identifierIndex = identifierIndex;
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
