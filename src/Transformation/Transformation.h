#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "CmdMediator.h"
#include <QPoint>
#include <QString>
#include <QTransform>

/// Affine transformation between screen and graph coordinates, based on digitized axis points
class Transformation
{
public:
  /// Default constructor.
  Transformation();

  /// Assignment operator.
  Transformation &operator=(const Transformation &other);

  /// Inequality operator.
  bool operator!=(const Transformation &other);

  /// Return string descriptions of cursor coordinates for status bar
  void coordTextForStatusBar (QPointF cursorScreen,
                              QString &coordsScreen,
                              QString &coordsGraph,
                              QString &resolutionGraph);

  /// Transform is defined when at least three axis points have been digitized
  bool transformIsDefined() const { return m_transformIsDefined; }

  /// Transform from pixel screen coordinates to graph coordinates
  void transform (const QPointF &coordScreen,
                  QPointF &coordGraph) const;

  /// Transform from graph coordinates to pixel screen coordinates
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
  QTransform m_transform;

  // No need to display values like 1E-17 when it is insignificant relative to the range
  double roundOffSmallValues (double value, double range);

  // Values for determining when an epsilon value is so close to zero that it should be displayed as zero
  double m_xGraphRange;
  double m_yGraphRange;
};

#endif // TRANSFORMATION_H
