#include "CmdMediator.h"
#include "DocumentModelCoords.h"
#include "Logger.h"
#include <QXmlStreamWriter>

DocumentModelCoords::DocumentModelCoords() :
  m_coordsType (COORDS_TYPE_CARTESIAN),
  m_originRadius (0.0),
  m_coordScaleXTheta (COORD_SCALE_LINEAR),
  m_coordScaleYRadius (COORD_SCALE_LINEAR),
  m_coordThetaUnits (COORD_THETA_UNITS_DEGREES)
{
}

DocumentModelCoords::DocumentModelCoords(const CmdMediator &cmdMediator) :
  m_coordsType (cmdMediator.document().modelCoords().coordsType()),
  m_originRadius(cmdMediator.document().modelCoords().originRadius()),
  m_coordScaleXTheta(cmdMediator.document().modelCoords().coordScaleXTheta()),
  m_coordScaleYRadius(cmdMediator.document().modelCoords().coordScaleYRadius()),
  m_coordThetaUnits(cmdMediator.document().modelCoords().coordThetaUnits())
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

double DocumentModelCoords::originRadius() const
{
  return m_originRadius;
}

void DocumentModelCoords::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCoords::saveModel";

  stream.writeStartElement("DocumentModelCoords");
  stream.writeEndElement();
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

