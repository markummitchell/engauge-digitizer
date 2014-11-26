#ifndef DLG_MODEL_COORDS_H
#define DLG_MODEL_COORDS_H

#include "CoordScale.h"
#include "CoordsType.h"

class CmdMediator;

class DlgModelCoords
{
public:
  /// Default constructor.
  DlgModelCoords();

  /// Initial constructor from Document.
  DlgModelCoords(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelCoords(const DlgModelCoords &other);

  /// Assignment constructor.
  DlgModelCoords &operator=(const DlgModelCoords &other);

  /// Get method for linear/log scale on x/theta.
  CoordScale coordScaleXTheta () const;

  /// Get method for linear/log scale on y/radius.
  CoordScale coordScaleYRadius () const;

  /// Get method for coordinates type.
  CoordsType coordsType () const;

  /// Get method for origin radius in polar mode.
  double originRadius () const;

  /// Set method for linear/log scale on x/theta.
  void setCoordScaleXTheta (CoordScale coordScale);

  /// Set method for linear/log scale on y/radius.
  void setCoordScaleYRadius (CoordScale coordScale);

  /// Set method for coordinates type.
  void setCoordsType (CoordsType coordsType);

  /// Set method for origin radius in polar mode.
  void setOriginRadius (double originRadius);

private:

  CoordsType m_coordsType;
  double m_originRadius;
  CoordScale m_coordScaleXTheta;
  CoordScale m_coordScaleYRadius;
};

#endif // DLG_MODEL_COORDS_H
