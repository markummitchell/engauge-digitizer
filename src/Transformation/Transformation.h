/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "CmdMediator.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGeneral.h"
#include "MainWindowModel.h"
#include <QPointF>
#include <QString>
#include <QTransform>

/// Affine transformation between screen and graph coordinates, based on digitized axis points.
///
/// Transformation from screen pixels to graph coordinates involves two steps:
/// -# Transform from screen pixels (which are linear and cartesian) to linear cartesian graph coordinates
/// -# Transform from linear cartesian graph coordinates to the final graph coordinates, which are linear
///    or log scaled, and cartesian or polar
///
/// Transformation from graph coordinates to screen pixels reverses the steps involved in the
/// transformation from screen pixels to graph coordinates
///
/// Log scaling is calculated as (xLinear - xLogMin) / (xLogMax - xLogMin) = (ln(xLog) - ln(xLogMin)) / (ln(xLogMax) - ln(xLogMin)),
/// which leaves the points (xLogMin,yLonMin) and (xLogMax,yLogMax) unaffected but gives log growth on all
/// other points
class Transformation
{
  // For unit testing
  friend class TestTransformation;

public:
  /// Default constructor. This is marked as undefined until the proper number of axis points are added
  Transformation();

  /// Copy constructor
  Transformation (const Transformation &other);

  /// Assignment operator.
  Transformation &operator=(const Transformation &other);

  /// Identity transformation
  void identity();

  /// Inequality operator. This is marked as defined.
  bool operator!=(const Transformation &other);

  /// Calculate QTransform using from/to points that have already been adjusted for, when applicable,
  /// log scaling and polar coordinates. The points are linear and cartesian.
  ///
  /// This method is kept very generic since it used for different types of transformations:
  /// -# In many place to calculate screen-to/from-graph
  /// -# By Checker to calculate unaligned-to/from-aligned
  static QTransform calculateTransformFromLinearCartesianPoints (const QPointF &posFrom0,
                                                                 const QPointF &posFrom1,
                                                                 const QPointF &posFrom2,
                                                                 const QPointF &posTo0,
                                                                 const QPointF &posTo1,
                                                                 const QPointF &posTo2);

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

  /// Convert cartesian scaling from log to linear. Calling code is responsible for determining if this is necessary
  static double logToLinearCartesian (double xy);

  /// Convert radius scaling from log to linear. Calling code is responsible for determining if this is necessary
  static double logToLinearRadius (double r,
                                   double rCenter);

  /// Get method for DocumentModelCoords
  DocumentModelCoords modelCoords() const;

  /// Get method for DocumentModelGeneral
  DocumentModelGeneral modelGeneral() const;

  /// Get method for MainWindowModel
  MainWindowModel modelMainWindow() const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Reset, when loading a document after the first, to same state that first document was at when loaded
  void resetOnLoad();

  /// Transform is defined when at least three axis points have been digitized
  bool transformIsDefined() const;

  /// Transform from linear cartesian graph coordinates to cartesian, polar, linear, log coordinates
  void transformLinearCartesianGraphToRawGraph (const QPointF &coordGraph,
                                                QPointF &coordScreen) const;

  /// Transform from linear cartesian graph coordinates to cartesian pixel screen coordinates
  void transformLinearCartesianGraphToScreen (const QPointF &coordGraph,
                                              QPointF &coordScreen) const;

  /// Get method for copying only, for the transform matrix.
  QTransform transformMatrix () const;

  /// Convert graph coordinates (linear or log, cartesian or polar) to linear cartesian coordinates
  void transformRawGraphToLinearCartesianGraph (const QPointF &pointRaw,
                                                QPointF &pointLinearCartesian) const;

  /// Transform from raw graph coordinates to linear cartesian graph coordinates, then to screen coordinates
  void transformRawGraphToScreen (const QPointF &pointRaw,
                                  QPointF &pointScreen) const;

  /// Transform screen coordinates to linear cartesian coordinates
  void transformScreenToLinearCartesianGraph (const QPointF &pointScreen,
                                              QPointF &pointLinearCartesian) const;

  /// Transform from cartesian pixel screen coordinates to cartesian/polar graph coordinates
  void transformScreenToRawGraph (const QPointF &coordScreen,
                                  QPointF &coordGraph) const;

  /// Update transform by iterating through the axis points.
  void update (bool fileIsLoaded,
               const CmdMediator &cmdMediator,
               const MainWindowModel &modelMainWindow);

private:

  // No need to display values like 1E-17 when it is insignificant relative to the range
  double roundOffSmallValues (double value, double range);

  // Model coords are set upon entry from CmdMediator
  void setModelCoords (const DocumentModelCoords &modelCoords,
                       const DocumentModelGeneral &modelGeneral,
                       const MainWindowModel &modelMainWindow);

  // Compute transform from screen and graph points. The 3x3 matrices are handled as QTransform since QMatrix is deprecated
  void updateTransformFromMatrices (const QTransform &matrixScreen,
                                    const QTransform &matrixGraph);

  // State variable
  bool m_transformIsDefined;

  // Transform between cartesian screen coordinates and cartesian graph coordinates
  QTransform m_transform;

  // Coordinates information from last time the transform was updated. Only defined if  m_transformIsDefined is true
  DocumentModelCoords m_modelCoords;

  // General settings
  DocumentModelGeneral m_modelGeneral;

  // Formatting information
  MainWindowModel m_modelMainWindow;
};

/// Stream operator
std::ostringstream &operator<< (std::ostringstream &str,
                               const Transformation &transformation);

#endif // TRANSFORMATION_H
