#ifndef DOCUMENT_MODEL_COORDS_H
#define DOCUMENT_MODEL_COORDS_H

#include "CoordScale.h"
#include "CoordsType.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

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

  /// Get method for date format when used.
  CoordUnitsDate coordUnitsDate () const;

  /// Get method for radius units.
  CoordUnitsNonPolarTheta coordUnitsRadius () const;

  /// Get method for theta unit.
  CoordUnitsPolarTheta coordUnitsTheta () const;

  /// Get method for time format when used.
  CoordUnitsTime coordUnitsTime () const;

  /// Get method for x units.
  CoordUnitsNonPolarTheta coordUnitsX () const;

  /// Get method for x units.
  CoordUnitsNonPolarTheta coordUnitsY () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for origin radius in polar mode.
  double originRadius () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for linear/log scale on x/theta.
  void setCoordScaleXTheta (CoordScale coordScale);

  /// Set method for linear/log scale on y/radius.
  void setCoordScaleYRadius (CoordScale coordScale);

  /// Set method for coordinates type.
  void setCoordsType (CoordsType coordsType);

  /// Set method for date units.
  void setCoordUnitsDate (CoordUnitsDate coordUnits);

  /// Set method for radius units.
  void setCoordUnitsRadius (CoordUnitsNonPolarTheta coordUnits);

  /// Set method for theta units.
  void setCoordUnitsTheta (CoordUnitsPolarTheta coordUnits);

  /// Set method for time units.
  void setCoordUnitsTime (CoordUnitsTime coordUnits);

  /// Set method for x units.
  void setCoordUnitsX (CoordUnitsNonPolarTheta coordUnits);

  /// Set method for y units.
  void setCoordUnitsY (CoordUnitsNonPolarTheta coordUnits);

  /// Set method for origin radius in polar mode.
  void setOriginRadius (double originRadius);

  /// Return the period of the theta value for polar coordinates, consistent with CoordThetaUnits
  double thetaPeriod () const;

private:

  CoordsType m_coordsType;
  double m_originRadius; // Applies to polar coordinates. Usually zero
  CoordScale m_coordScaleXTheta;
  CoordScale m_coordScaleYRadius;
  CoordUnitsNonPolarTheta m_coordUnitsX; // Applies to x for cartesian coordinates
  CoordUnitsNonPolarTheta m_coordUnitsY; // Applies to y for cartesian coordinates
  CoordUnitsPolarTheta m_coordUnitsTheta; // Applies to theta for polar coordinates
  CoordUnitsNonPolarTheta m_coordUnitsRadius; // Applies to radius for polar coordinates
  CoordUnitsDate m_coordUnitsDate; // Applies to date/time coordinates
  CoordUnitsTime m_coordUnitsTime;
};

#endif // DOCUMENT_MODEL_COORDS_H
