#ifndef CALLBACK_AXIS_POINTS_ABSTRACT
#define CALLBACK_AXIS_POINTS_ABSTRACT

#include "CallbackSearchReturn.h"
#include "DocumentModelCoords.h"
#include <QString>
#include <QTransform>

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
  CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords);

  /// Constructor for when the data for one of the existing axis points is to be locally overwritten.
  CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords,
                             const QString pointIdentifierOverride,
                             const QPointF &posGraphOverride,
                             const QPointF &posScreenOverride);

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

  /// This value is checked after iterating to see what was wrong if the axis data was incorrect.
  QString errorMessage () const { return m_errorMessage; }

  /// This value is checked after iterating to see if the axis data is correct. The error state does NOT
  /// include the case when there are not enough axis points
  bool isError () const { return m_isError; }

  /// Number of axis points which is less than 3 if the axes curve is incomplete.
  unsigned int numberAxisPoints () const { return m_numberAxisPoints; }

private:

  bool anyColumnsRepeat (double m [3] [3], int numberColumns);
  bool threePointsAreCollinear (double m [3] [3], int numberColumns);

  // Coordinates information that will be applied to the coordinates before they are used to compute the transformation
  DocumentModelCoords m_modelCoords;

  // For overriding one existing Point. Identifier is empty for no overriding
  QString m_pointIdentifierOverride;
  QPointF m_posScreenOverride;
  QPointF m_posGraphOverride;

  int m_numberAxisPoints;
  QTransform m_screenInputs;
  QTransform m_graphOutputs;

  bool m_isError;
  QString m_errorMessage;

  // For computing the ranges of the graph coordinates
  double m_xGraphLow;
  double m_yGraphLow;
  double m_xGraphHigh;
  double m_yGraphHigh;
};

#endif // CALLBACK_AXIS_POINTS_ABSTRACT
