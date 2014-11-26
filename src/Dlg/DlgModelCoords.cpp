#include "DlgModelCoords.h"

DlgModelCoords::DlgModelCoords() :
  m_coordsType (COORDS_TYPE_CARTESIAN),
  m_originRadius (0.0),
  m_coordScaleXTheta (COORD_SCALE_LINEAR),
  m_coordScaleYRadius (COORD_SCALE_LINEAR)
{
}

DlgModelCoords::DlgModelCoords(const DlgModelCoords &other) :
  m_coordsType (other.coordsType ()),
  m_originRadius (other.originRadius ()),
  m_coordScaleXTheta (other.coordScaleXTheta()),
  m_coordScaleYRadius (other.coordScaleYRadius ())
{
}

DlgModelCoords &DlgModelCoords::operator=(const DlgModelCoords &other)
{
  m_coordsType = other.coordsType();
  m_originRadius = other.originRadius();
  m_coordScaleXTheta = other.coordScaleXTheta();
  m_coordScaleYRadius = other.coordScaleYRadius();

  return *this;
}

CoordScale DlgModelCoords::coordScaleXTheta () const
{
  return m_coordScaleXTheta;
}

CoordScale DlgModelCoords::coordScaleYRadius () const
{
  return m_coordScaleYRadius;
}

CoordsType DlgModelCoords::coordsType () const
{
  return m_coordsType;
}

double DlgModelCoords::originRadius() const
{
  return m_originRadius;
}

void DlgModelCoords::setCoordScaleXTheta (CoordScale coordScale)
{
  m_coordScaleXTheta = coordScale;
}

void DlgModelCoords::setCoordScaleYRadius (CoordScale coordScale)
{
  m_coordScaleYRadius = coordScale;
}

void DlgModelCoords::setCoordsType (CoordsType coordsType)
{
  m_coordsType = coordsType;
}

void DlgModelCoords::setOriginRadius(double originRadius)
{
  m_originRadius = originRadius;
}
