/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_AXIS_POINTS_ABSTRACT
#define CALLBACK_AXIS_POINTS_ABSTRACT

#include "CallbackSearchReturn.h"
#include "DocumentAxesPointsRequired.h"
#include "DocumentModelCoords.h"
#include <QList>
#include <QString>
#include <QTransform>

typedef QList<QPointF> CoordPairVector;
typedef QList<double> CoordSingleVector;

class Point;

/// Callback for collecting axis points and then performing common calculations on those axis points.
/// This class collects 3x3 matrix G which contains columns of graph coordinates, and 3x3 matrix S
/// which contains columns of screen coordinates. Although it goes almost as far as solving (G) = (T) (S)
/// for the transformation T, that is left for the Transformation class. This class does, however, do the
/// sanity checking (like for collinear points) so the gui can provide immediate feedback to the user
/// well before the Transformation class gets involved
///
/// This class is versatile. The cases are:
/// -# Use all existing axis points, and then the subclass can effectively append one more point to check if that
///    additional point would violate any constraints (prior to adding the point)
/// -# Use all existing axis points, but override the details of one existing axis point to see if those
///    details violate any constraint (prior to editing the point)
/// -# Use all existing axis points as is. This is for computing the transformation after axis points are added/edited
class CallbackAxisPointsAbstract
{
  /// For unit testing
  friend class TestGraphCoords;

public:
  /// Constructor for when all of the existing axis points are to be processed as is.
  CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords,
                             DocumentAxesPointsRequired documentAxesPointsRequired);

  /// Constructor for when the data for one of the existing axis points is to be locally overwritten.
  CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords,
                             const QString pointIdentifierOverride,
                             const QPointF &posGraphOverride,
                             const QPointF &posScreenOverride,
                             DocumentAxesPointsRequired documentAxesPointsRequired);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Returns graph coordinates matrix after transformIsDefined has already indicated success. Since QMatrix is deprecated
  /// the results are returned as QTransform
  QTransform matrixGraph () const;

  /// Returns screen coordinates matrix after transformIsDefined has already indicated success. Since QMatrix is deprecated
  /// the results are returned as QTransform
  QTransform matrixScreen () const;

  /// Return the range of the x graph coordinate from low to high, after the transform is defined.
  double xGraphRange () const { return m_xGraphHigh - m_xGraphLow; }

  /// Return the range of the y graph coordinate from low to high, after the transform is defined.
  double yGraphRange () const { return m_yGraphHigh - m_yGraphLow; }

protected:

  /// Number of axes points required for the transformation
  DocumentAxesPointsRequired documentAxesPointsRequired() const;

  /// This value is checked after iterating to see what was wrong if the axis data was incorrect.
  QString errorMessage () const { return m_errorMessage; }

  /// This value is checked after iterating to see if the axis data is correct. The error state does NOT
  /// include the case when there are not enough axis points
  bool isError () const { return m_isError; }

  /// Number of axis points which is less than 3 if the axes curve is incomplete.
  unsigned int numberAxisPoints () const;

private:

  bool anyPointsRepeatPair (const CoordPairVector &vector) const;
  bool anyPointsRepeatSingle (const CoordSingleVector &vector) const;
  CallbackSearchReturn callbackRequire2AxisPoints (const QPointF &posScreen,
                                                   const QPointF &posGraph);
  CallbackSearchReturn callbackRequire3AxisPoints (const QPointF &posScreen,
                                                   const QPointF &posGraph);
  CallbackSearchReturn callbackRequire4AxisPoints (bool isXOnly,
                                                   const QPointF &posScreen,
                                                   const QPointF &posGraph);
  void computeTransforms3();
  void computeTransforms4();
  void loadTransforms2();
  void loadTransforms3();
  void loadTransforms4();
  bool threePointsAreCollinear (const QTransform &transform);

  // Coordinates information that will be applied to the coordinates before they are used to compute the transformation
  DocumentModelCoords m_modelCoords;

  // For overriding one existing Point. Identifier is empty for no overriding
  QString m_pointIdentifierOverride;
  QPointF m_posScreenOverride;
  QPointF m_posGraphOverride;

  // Storage of (x,y) axes points for DOCUMENT_AXES_POINTS_REQUIRED_3
  CoordPairVector m_screenInputs;
  CoordPairVector m_graphOutputs;

  // Storage of (x) and (y) axes points for DOCUMENT_AXES_POINTS_REQUIRED_4
  CoordPairVector m_screenInputsX; // Accumulated screen coordinates for x axis points
  CoordPairVector m_screenInputsY; // Accumulated screen coordinates for y axis points
  CoordSingleVector m_graphOutputsX; // Accumulated x values for x axis points
  CoordSingleVector m_graphOutputsY; // Accumulated y values for y axis points

  // Transforms computed from DOCUMENT_AXES_POINTS_REQUIRED_3 or DOCUMENT_AXES_POINTS_REQUIRED_4 variables
  QTransform m_screenInputsTransform;
  QTransform m_graphOutputsTransform;

  // Errors
  bool m_isError;
  QString m_errorMessage;

  // For computing the ranges of the graph coordinates
  double m_xGraphLow;
  double m_yGraphLow;
  double m_xGraphHigh;
  double m_yGraphHigh;

  // Either 3 points (each having x AND y coordinates) or 4 points (each having x OR y coordinate) define the transform
  DocumentAxesPointsRequired m_documentAxesPointsRequired;
};

#endif // CALLBACK_AXIS_POINTS_ABSTRACT
