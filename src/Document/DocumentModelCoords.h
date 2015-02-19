#ifndef DOCUMENT_MODEL_COORDS_H
#define DOCUMENT_MODEL_COORDS_H

#include "CoordScale.h"
#include "CoordsType.h"
#include "CoordThetaUnits.h"
#include "DocumentModelAbstractBase.h"

class Document;

/// Model for DlgSettingsCoords and CmdSettingsCoords.
class DocumentModelCoords : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelCoords();

  /// Initial constructor from Document.
  DocumentModelCoords(const Document &document);

  /// Copy constructor.
  DocumentModelCoords(const DocumentModelCoords &other);

  /// Assignment constructor.
  DocumentModelCoords &operator=(const DocumentModelCoords &other);

  /// Get method for linear/log scale on x/theta.
  CoordScale coordScaleXTheta () const;

  /// Get method for linear/log scale on y/radius.
  CoordScale coordScaleYRadius () const;

  /// Get method for coordinates type.
  CoordsType coordsType () const;

  /// Get method for theta units.
  CoordThetaUnits coordThetaUnits () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for origin radius in polar mode.
  double originRadius () const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

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

#endif // DOCUMENT_MODEL_COORDS_H
