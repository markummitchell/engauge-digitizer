#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "CmdMediator.h"
#include "DocumentModelCoords.h"
#include <QPointF>
#include <QString>
#include <QTransform>

/// Affine transformation between screen and graph coordinates, based on digitized axis points
class Transformation
{
public:
  /// Default constructor. This is marked as undefined until the proper number of axis points are added
  Transformation();

  /// Assignment operator.
  Transformation &operator=(const Transformation &other);

  /// Identity transformation
  void identity();

  /// Inequality operator. This is marked as defined.
  bool operator!=(const Transformation &other);

  /// Output cartesian coordinates from input cartesian or polar coordinates. This is static for easier use externally
  static QPointF cartesianFromCartesianOrPolar (const DocumentModelCoords &modelCoords,
                                                const QPointF &posGraphIn);

  /// Output cartesian or polar coordinates from input cartesian coordinates. This is static for easier use externally
  static QPointF cartesianOrPolarFromCartesian (const DocumentModelCoords &modelCoords,
                                                const QPointF &posGraphIn);

  /// Return string descriptions of cursor coordinates for status bar
  void coordTextForStatusBar (QPointF cursorScreen,
                              QString &coordsScreen,
                              QString &coordsGraph,
                              QString &resolutionGraph);

  /// Transform is defined when at least three axis points have been digitized
  bool transformIsDefined() const { return m_transformIsDefined; }

  /// Transform from cartesian pixel screen coordinates to cartesian/polar graph coordinates
  void transform (const QPointF &coordScreen,
                  QPointF &coordGraph) const;

  /// Transform from cartesian/polar graph coordinates to cartesian pixel screen coordinates
  void transformInverse (const QPointF &coordGraph,
                         QPointF &coordScreen) const;

  /// Get method for copying only, for the transform matrix.
  QTransform transformMatrix () const;

  /// Update transform by iterating through the axis points.
  void update (bool fileIsLoaded,
               const CmdMediator &cmdMediator);

  /// Get method for copying only, for x epsilon.
  double xGraphRange() const;

  /// Get method for copying only, for y epsilon.
  double yGraphRange() const;

private:
  bool m_transformIsDefined;

  // Transform between cartesian screen coordinates and cartesian graph coordinates
  QTransform m_transform;

  // Coordinates information from last time the transform was updated. Only defined if  m_transformIsDefined is true
  DocumentModelCoords m_modelCoords;

  // No need to display values like 1E-17 when it is insignificant relative to the range
  double roundOffSmallValues (double value, double range);

  // Values for determining when an epsilon value is so close to zero that it should be displayed as zero
  double m_xGraphRange;
  double m_yGraphRange;
};

#endif // TRANSFORMATION_H
