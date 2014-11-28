#include "CmdMediator.h"
#include "DlgModelCoords.h"

DlgModelCoords::DlgModelCoords() :
  m_coordsType (COORDS_TYPE_CARTESIAN),
  m_originRadius (0.0),
  m_coordScaleXTheta (COORD_SCALE_LINEAR),
  m_coordScaleYRadius (COORD_SCALE_LINEAR),
  m_coordThetaUnits (COORD_THETA_UNITS_DEGREES)
{
}

DlgModelCoords::DlgModelCoords(const CmdMediator &cmdMediator) :
  m_coordsType (cmdMediator.document().modelCoords().coordsType()),
  m_originRadius(cmdMediator.document().modelCoords().originRadius()),
  m_coordScaleXTheta(cmdMediator.document().modelCoords().coordScaleXTheta()),
  m_coordScaleYRadius(cmdMediator.document().modelCoords().coordScaleYRadius()),
  m_coordThetaUnits(cmdMediator.document().modelCoords().coordThetaUnits())
{
}

DlgModelCoords::DlgModelCoords(const DlgModelCoords &other) :
  m_coordsType (other.coordsType ()),
  m_originRadius (other.originRadius ()),
  m_coordScaleXTheta (other.coordScaleXTheta()),
  m_coordScaleYRadius (other.coordScaleYRadius ()),
  m_coordThetaUnits (other.coordThetaUnits ())
{
}

DlgModelCoords &DlgModelCoords::operator=(const DlgModelCoords &other)
{
  m_coordsType = other.coordsType();
  m_originRadius = other.originRadius();
  m_coordScaleXTheta = other.coordScaleXTheta();
  m_coordScaleYRadius = other.coordScaleYRadius();
  m_coordThetaUnits = other.coordThetaUnits();

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

CoordThetaUnits DlgModelCoords::coordThetaUnits() const
{
  return m_coordThetaUnits;
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

void DlgModelCoords::setCoordThetaUnits (CoordThetaUnits coordThetaUnits)
{
  m_coordThetaUnits = coordThetaUnits;
}

void DlgModelCoords::setOriginRadius(double originRadius)
{
  m_originRadius = originRadius;
}

