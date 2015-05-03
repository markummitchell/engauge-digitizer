#include "CmdMediator.h"
#include "DocumentModelCoords.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QXmlStreamWriter>
#include "Xml.h"

const double PI = 3.1415926535;
const double TWO_PI = 2.0 * PI;

// Zero default for origin radius, which is usually wanted for COORD_SCALE_LINEAR, it is illegal
// for COORD_SCALE_LOG (for which 1.0 is probably preferred as the default. Note linear is more common than log
const double DEFAULT_ORIGIN_RADIUS_LINEAR = 0.0;

DocumentModelCoords::DocumentModelCoords() :
  m_coordsType (COORDS_TYPE_CARTESIAN),
  m_originRadius (DEFAULT_ORIGIN_RADIUS_LINEAR),
  m_coordScaleXTheta (COORD_SCALE_LINEAR),
  m_coordScaleYRadius (COORD_SCALE_LINEAR),
  m_coordThetaUnits (COORD_THETA_UNITS_DEGREES)
{
}

DocumentModelCoords::DocumentModelCoords(const Document &document) :
  m_coordsType (document.modelCoords().coordsType()),
  m_originRadius(document.modelCoords().originRadius()),
  m_coordScaleXTheta(document.modelCoords().coordScaleXTheta()),
  m_coordScaleYRadius(document.modelCoords().coordScaleYRadius()),
  m_coordThetaUnits(document.modelCoords().coordThetaUnits())
{
}

DocumentModelCoords::DocumentModelCoords(const DocumentModelCoords &other) :
  m_coordsType (other.coordsType ()),
  m_originRadius (other.originRadius ()),
  m_coordScaleXTheta (other.coordScaleXTheta()),
  m_coordScaleYRadius (other.coordScaleYRadius ()),
  m_coordThetaUnits (other.coordThetaUnits ())
{
}

DocumentModelCoords &DocumentModelCoords::operator=(const DocumentModelCoords &other)
{
  m_coordsType = other.coordsType();
  m_originRadius = other.originRadius();
  m_coordScaleXTheta = other.coordScaleXTheta();
  m_coordScaleYRadius = other.coordScaleYRadius();
  m_coordThetaUnits = other.coordThetaUnits();

  return *this;
}

CoordScale DocumentModelCoords::coordScaleXTheta () const
{
  return m_coordScaleXTheta;
}

CoordScale DocumentModelCoords::coordScaleYRadius () const
{
  return m_coordScaleYRadius;
}

CoordsType DocumentModelCoords::coordsType () const
{
  return m_coordsType;
}

CoordThetaUnits DocumentModelCoords::coordThetaUnits() const
{
  return m_coordThetaUnits;
}

void DocumentModelCoords::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCoords::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_TYPE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS)) {

    setCoordsType ((CoordsType) attributes.value(DOCUMENT_SERIALIZE_COORDS_TYPE).toInt());
    setOriginRadius (attributes.value(DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS).toDouble());
    setCoordScaleXTheta ((CoordScale) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA).toInt());
    setCoordScaleYRadius ((CoordScale) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS).toInt());
    setCoordThetaUnits ((CoordThetaUnits) attributes.value(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_COORDS)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read coordinates data");
  }
}

double DocumentModelCoords::originRadius() const
{
  return m_originRadius;
}

void DocumentModelCoords::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCoords::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_COORDS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_TYPE, QString::number (m_coordsType));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_TYPE_STRING, coordsTypeToString (m_coordsType));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS, QString::number (m_originRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA, QString::number (m_coordScaleXTheta));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA_STRING, coordScaleToString (m_coordScaleXTheta));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS, QString::number (m_coordScaleYRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS_STRING, coordScaleToString (m_coordScaleYRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS, QString::number (m_coordThetaUnits));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS_STRING, coordThetaUnitsToString (m_coordThetaUnits));
  writer.writeEndElement();
}

void DocumentModelCoords::setCoordScaleXTheta (CoordScale coordScale)
{
  m_coordScaleXTheta = coordScale;
}

void DocumentModelCoords::setCoordScaleYRadius (CoordScale coordScale)
{
  m_coordScaleYRadius = coordScale;
}

void DocumentModelCoords::setCoordsType (CoordsType coordsType)
{
  m_coordsType = coordsType;
}

void DocumentModelCoords::setCoordThetaUnits (CoordThetaUnits coordThetaUnits)
{
  m_coordThetaUnits = coordThetaUnits;
}

void DocumentModelCoords::setOriginRadius(double originRadius)
{
  m_originRadius = originRadius;
}

double DocumentModelCoords::thetaPeriod () const
{
  switch (m_coordThetaUnits) {
    case COORD_THETA_UNITS_DEGREES:
    case COORD_THETA_UNITS_DEGREES_MINUTES:
    case COORD_THETA_UNITS_DEGREES_MINUTES_SECONDS:
      return 360;

    case COORD_THETA_UNITS_GRADIANS:
      return 400;

    case COORD_THETA_UNITS_RADIANS:
      return TWO_PI;

    case COORD_THETA_UNITS_TURNS:
      return 1;
  }

  ENGAUGE_ASSERT(false);
  return 0;
}
