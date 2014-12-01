#ifndef DLG_MODEL_COORDS_H
#define DLG_MODEL_COORDS_H

#include "CoordScale.h"
#include "CoordsType.h"
#include "CoordThetaUnits.h"
#include "DocumentModelAbstractBase.h"

class CmdMediator;

/// Model for DlgSettingsCoords and CmdSettingsCoords.
class DlgModelCoords : public DocumentModelAbstractBase
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

  /// Get method for theta units.
  CoordThetaUnits coordThetaUnits () const;

  /// Get method for origin radius in polar mode.
  double originRadius () const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for linear/log scale on x/theta.
  void setCoordScaleXTheta (CoordScale coordScale);

  /// Set method for linear/log scale on y/radius.
  void setCoordScaleYRadius (CoordScale coordScale);

  /// Set method for coordinates type.
  void setCoordsType (CoordsType coordsType);

  /// Set method for theta units.
  void setCoordThetaUnits (CoordThetaUnits coordThetaUnits);

  /// Set method for origin radius in polar mode.
  void setOriginRadius (double originRadius);

private:

  CoordsType m_coordsType;
  double m_originRadius; // Applies to polar coordinates. Usually zero
  CoordScale m_coordScaleXTheta;
  CoordScale m_coordScaleYRadius;
  CoordThetaUnits m_coordThetaUnits; // Applies to polar coordinates
};

#endif // DLG_MODEL_COORDS_H
