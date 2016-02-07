#include "CallbackAxisPointsAbstract.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <qmath.h>
#include "QtToString.h"
#include "Transformation.h"

CallbackAxisPointsAbstract::CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords,
                                                       DocumentAxesPointsRequired documentAxesPointsRequired) :
  m_modelCoords (modelCoords),
  m_isError (false),
  m_documentAxesPointsRequired (documentAxesPointsRequired)
{
}

CallbackAxisPointsAbstract::CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords,
                                                       const QString pointIdentifierOverride,
                                                       const QPointF &posScreenOverride,
                                                       const QPointF &posGraphOverride) :
  m_modelCoords (modelCoords),
  m_pointIdentifierOverride (pointIdentifierOverride),
  m_posScreenOverride (posScreenOverride),
  m_posGraphOverride (posGraphOverride),
  m_isError (false)
{
}

bool CallbackAxisPointsAbstract::anyPointsRepeatPair (const CoordPairVector &vector) const
{
  for (int pointLeft = 0; pointLeft < vector.count(); pointLeft++) {
    for (int pointRight = pointLeft + 1; pointRight < vector.count(); pointRight++) {

      if ((vector.at(pointLeft).x() == vector.at(pointRight).x()) &&
          (vector.at(pointLeft).y() == vector.at(pointRight).y())) {

        // Points pointLeft and pointRight repeat each other, which means matrix cannot be inverted
        return true;
      }
    }
  }

  // No columns repeat
  return false;
}

bool CallbackAxisPointsAbstract::anyPointsRepeatSingle (const CoordSingleVector &vector) const
{
  for (int pointLeft = 0; pointLeft < vector.count(); pointLeft++) {
    for (int pointRight = pointLeft + 1; pointRight < vector.count(); pointRight++) {

      if (vector.at(pointLeft) == vector.at(pointRight)) {

        // Points pointLeft and pointRight repeat each other, which means matrix cannot be inverted
        return true;
      }
    }
  }

  // No columns repeat
  return false;
}

CallbackSearchReturn CallbackAxisPointsAbstract::callback (const QString & /* curveName */,
                                                           const Point &point)
{
  QPointF posScreen = point.posScreen ();
  QPointF posGraph = point.posGraph ();

  if (m_pointIdentifierOverride == point.identifier ()) {

    // Override the old point coordinates with its new (if all tests are passed) coordinates
    posScreen = m_posScreenOverride;
    posGraph = m_posGraphOverride;
  }

  // Try to compute transform
  if (m_documentAxesPointsRequired == DOCUMENT_AXES_POINTS_REQUIRED_3) {
    return callbackRequire3AxisPoints (posScreen,
                                       posGraph);
  } else {
    return callbackRequire4AxisPoints (point.isXOnly(),
                                       posScreen,
                                       posGraph);
  }
}

CallbackSearchReturn CallbackAxisPointsAbstract::callbackRequire3AxisPoints (const QPointF &posScreen,
                                                                             const QPointF &posGraph)
{
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  // Update range variables
  int numberPoints = m_screenInputs.count();
  if ((numberPoints == 0) || (posGraph.x () < m_xGraphLow)) { m_xGraphLow = posGraph.x (); }
  if ((numberPoints == 0) || (posGraph.y () < m_yGraphLow)) { m_yGraphLow = posGraph.y (); }
  if ((numberPoints == 0) || (posGraph.x () > m_xGraphHigh)) { m_xGraphHigh = posGraph.x (); }
  if ((numberPoints == 0) || (posGraph.y () > m_yGraphHigh)) { m_yGraphHigh = posGraph.y (); }

  if (numberPoints < 3) {

    // Append new point
    m_screenInputs.push_back (posScreen);
    m_graphOutputs.push_back (posGraph);
    numberPoints = m_screenInputs.count();

    if (numberPoints == 3) {
      loadTransforms3 ();
    }

    // Error checking
    if (anyPointsRepeatPair (m_screenInputs)) {

      m_isError = true;
      m_errorMessage = "New axis point cannot be at the same screen position as an exisiting axis point";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (anyPointsRepeatPair (m_graphOutputs)) {

      m_isError = true;
      m_errorMessage = "New axis point cannot have the same graph coordinates as an existing axis point";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 3) && threePointsAreCollinear (m_screenInputsTransform)) {

      m_isError = true;
      m_errorMessage = "No more than two axis points can lie along the same line on the screen";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 3) && threePointsAreCollinear (m_graphOutputsTransform)) {

      m_isError = true;
      m_errorMessage = "No more than two axis points can lie along the same line in graph coordinates";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    }
  }

  if (m_screenInputs.count() > 2) {

    // There are enough axis points so quit
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

  }

  return rtn;
}

CallbackSearchReturn CallbackAxisPointsAbstract::callbackRequire4AxisPoints (bool isXOnly,
                                                                             const QPointF &posScreen,
                                                                             const QPointF &posGraph)
{
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  // Update range variables
  int numberPoints = m_screenInputsX.count() + m_screenInputsY.count();
  if ((numberPoints == 0) || (posGraph.x () < m_xGraphLow)) { m_xGraphLow = posGraph.x (); }
  if ((numberPoints == 0) || (posGraph.y () < m_yGraphLow)) { m_yGraphLow = posGraph.y (); }
  if ((numberPoints == 0) || (posGraph.x () > m_xGraphHigh)) { m_xGraphHigh = posGraph.x (); }
  if ((numberPoints == 0) || (posGraph.y () > m_yGraphHigh)) { m_yGraphHigh = posGraph.y (); }

  if (numberPoints < 4) {

    // Append the new point
    if (isXOnly) {

      m_screenInputsX.push_back (posScreen);
      m_graphOutputsX.push_back (posGraph.x());

    } else {

      m_screenInputsY.push_back (posScreen);
      m_graphOutputsY.push_back (posGraph.y());

    }

    numberPoints = m_screenInputsX.count() + m_screenInputsY.count();
    if (numberPoints == 4) {
      loadTransforms4 ();
    }
  }

  if (m_screenInputsX.count() > 2) {

    m_isError = true;
    m_errorMessage = "Too many x axis points. There should only be two";
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

  } else if (m_screenInputsY.count() > 2) {

    m_isError = true;
    m_errorMessage = "Too many y axis points. There should only be two";
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

  } else {

    // Default assumes there are enough axis points
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    // Error checking
    if (anyPointsRepeatPair (m_screenInputsX) ||
        anyPointsRepeatPair (m_screenInputsY)) {

      m_isError = true;
      m_errorMessage = "New axis point cannot be at the same screen position as an exisiting axis point";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (anyPointsRepeatSingle (m_graphOutputsX) ||
               anyPointsRepeatSingle (m_graphOutputsY)) {

      m_isError = true;
      m_errorMessage = "New axis point cannot have the same graph coordinates as an existing axis point";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 4) && threePointsAreCollinear (m_screenInputsTransform)) {

      m_isError = true;
      m_errorMessage = "No more than two axis points can lie along the same line on the screen";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 4) && threePointsAreCollinear (m_graphOutputsTransform)) {

      m_isError = true;
      m_errorMessage = "No more than two axis points can lie along the same line in graph coordinates";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    }
  }

  return rtn;
}

void CallbackAxisPointsAbstract::loadTransforms3 ()
{
  // Screen coordinates
  m_screenInputsTransform = QTransform (m_screenInputs.at(0).x(), m_screenInputs.at(1).x(), m_screenInputs.at(2).x(),
                                        m_screenInputs.at(0).y(), m_screenInputs.at(1).y(), m_screenInputs.at(2).y(),
                                        1.0                     , 1.0                     , 1.0                     );

  // Graph coordinates
  m_graphOutputsTransform = QTransform (m_graphOutputs.at(0).x(), m_graphOutputs.at(1).x(), m_graphOutputs.at(2).x(),
                                        m_graphOutputs.at(0).y(), m_graphOutputs.at(1).y(), m_graphOutputs.at(2).y(),
                                        1.0                     , 1.0                     , 1.0                     );
}

void CallbackAxisPointsAbstract::loadTransforms4 ()
{
  double x1Screen = m_screenInputsX.at(0).x();
  double y1Screen = m_screenInputsX.at(0).y();
  double x2Screen = m_screenInputsX.at(1).x();
  double y2Screen = m_screenInputsX.at(1).y();
  double x3Screen = m_screenInputsY.at(0).x();
  double y3Screen = m_screenInputsY.at(0).y();
  double x4Screen = m_screenInputsY.at(1).x();
  double y4Screen = m_screenInputsY.at(1).y();

  double x1Graph = m_graphOutputsX.at(0);
  double y1Graph = m_graphOutputsX.at(0);
  double x2Graph = m_graphOutputsX.at(1);
  double y2Graph = m_graphOutputsX.at(1);
//  double x3Graph = m_graphOutputsY.at(0);
//  double y3Graph = m_graphOutputsY.at(0);
//  double x4Graph = m_graphOutputsY.at(1);
  double y4Graph = m_graphOutputsY.at(1);

  // Intersect the two lines of the two axes. The lines are defined parametrically for the screen coordinates, with
  // points 1 and 2 on the x axis and points 3 and 4 on the y axis, as:
  //   x = (1 - sx) * x1 + sx * x2
  //   y = (1 - sx) * y1 + sx * y2
  //   x = (1 - sy) * x3 + sy * x4
  //   y = (1 - sy) * y3 + sy * y4
  // Intersection of the 2 lines is at (x,y). Solving for sx and sy using Cramer's rule where Ax=b
  // (x1 - x3)   (x1 - x2     x4 - x3) (sx)
  // (y1 - y3) = (y1 - y2     y4 - y3) (sy)
  double A00 = x1Screen - x2Screen;
  double A01 = x4Screen - x3Screen;
  double A10 = y1Screen - y2Screen;
  double A11 = y4Screen - y3Screen;
  double b0 = x1Screen - x3Screen;
  double b1 = y1Screen - y3Screen;
  double numerator = (b0 * A11 - A01 * b1);
  double denominator = (A00 * A11 - A01 * A10);
  double sx = numerator / denominator;

  // Intersection point. For the graph coordinates, the initial implementation assumes cartesian and linear coordinates
  double xIntScreen = (1.0 - sx) * x1Screen + sx * x2Screen;
  double yIntScreen = (1.0 - sx) * y1Screen + sx * y2Screen;
  double xIntGraph = (1.0 - sx) * x1Graph + sx * x2Graph;
  double yIntGraph = (1.0 - sx) * y1Graph + sx * y2Graph;

  // We now have too many data points with both x and y coordinates:
  // (xIntGraph,yIntGraph) (xIntGraph,y3) (xIntGraph,y4) (x1,yIntGraph) (x2,yIntGraph)
  // so we pick just 3
  // (xIntGraph,yIntGraph)                (xIntGraph,y4)                (x2,yIntGraph)

  // Screen coordinates
  m_screenInputsTransform = QTransform (xIntScreen, xIntScreen, x2Screen,
                                        yIntScreen, y4Screen  , y2Screen,
                                        1.0       , 1.0       , 1.0     );

  // Graph coordinates
  m_graphOutputsTransform = QTransform (xIntGraph, xIntGraph, x2Graph,
                                        yIntGraph, y4Graph  , y2Graph,
                                        1.0      , 1.0      , 1.0    );
}

QTransform CallbackAxisPointsAbstract::matrixGraph () const
{
  return m_graphOutputsTransform;
}

QTransform CallbackAxisPointsAbstract::matrixScreen () const
{
  return m_screenInputsTransform;
}

unsigned int CallbackAxisPointsAbstract::numberAxisPoints () const
{
  if (m_documentAxesPointsRequired == DOCUMENT_AXES_POINTS_REQUIRED_3) {
    return m_screenInputs.count();
  } else {
    return m_screenInputsX.count() + m_screenInputsY.count();
  }
}

bool CallbackAxisPointsAbstract::threePointsAreCollinear (const QTransform &transform)
{
  return (transform.determinant() == 0);
}
