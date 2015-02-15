#include "CmdMediator.h"
#include "DocumentModelCoords.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QXmlStreamWriter>
#include "Xml.h"

DocumentModelCoords::DocumentModelCoords() :
  m_coordsType (COORDS_TYPE_CARTESIAN),
  m_originRadius (0.0),
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

void DocumentModelCoords::loadDocument(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCoords::loadDocument";

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
    }
  } else {
    reader.raiseError ("Cannot read coordinates data");
  }
}

double DocumentModelCoords::originRadius() const
{
  return m_originRadius;
}

void DocumentModelCoords::saveDocument(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCoords::saveDocument";

  writer.writeStartElement(DOCUMENT_SERIALIZE_COORDS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_TYPE, QString::number (m_coordsType));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS, QString::number (m_originRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA, QString::number (m_coordScaleXTheta));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS, QString::number (m_coordScaleYRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS, QString::number (m_coordThetaUnits));
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

