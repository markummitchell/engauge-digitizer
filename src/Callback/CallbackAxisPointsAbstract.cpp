/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
                                                       const QPointF &posGraphOverride,
                                                       DocumentAxesPointsRequired documentAxesPointsRequired) :
  m_modelCoords (modelCoords),
  m_pointIdentifierOverride (pointIdentifierOverride),
  m_posScreenOverride (posScreenOverride),
  m_posGraphOverride (posGraphOverride),
  m_isError (false),
  m_documentAxesPointsRequired (documentAxesPointsRequired)
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
      m_errorMessage = QObject::tr ("New axis point cannot be at the same screen position as an exisiting axis point");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (anyPointsRepeatPair (m_graphOutputs)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("New axis point cannot have the same graph coordinates as an existing axis point");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 3) && threePointsAreCollinear (m_screenInputsTransform)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("No more than two axis points can lie along the same line on the screen");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 3) && threePointsAreCollinear (m_graphOutputsTransform)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("No more than two axis points can lie along the same line in graph coordinates");
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
    m_errorMessage = QObject::tr ("Too many x axis points. There should only be two");
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

  } else if (m_screenInputsY.count() > 2) {

    m_isError = true;
    m_errorMessage = QObject::tr ("Too many y axis points. There should only be two");
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

  } else {

    if ((m_screenInputsX.count() == 2) &&
        (m_screenInputsY.count() == 2)) {

      // Done, although an error may intrude
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;
    }

    // Error checking
    if (anyPointsRepeatPair (m_screenInputsX) ||
        anyPointsRepeatPair (m_screenInputsY)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("New axis point cannot be at the same screen position as an exisiting axis point");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (anyPointsRepeatSingle (m_graphOutputsX) ||
               anyPointsRepeatSingle (m_graphOutputsY)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("New axis point cannot have the same graph coordinates as an existing axis point");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 4) && threePointsAreCollinear (m_screenInputsTransform)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("No more than two axis points can lie along the same line on the screen");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if ((numberPoints == 4) && threePointsAreCollinear (m_graphOutputsTransform)) {

      m_isError = true;
      m_errorMessage = QObject::tr ("No more than two axis points can lie along the same line in graph coordinates");
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    }
  }

  return rtn;
}

DocumentAxesPointsRequired CallbackAxisPointsAbstract::documentAxesPointsRequired() const
{
  return m_documentAxesPointsRequired;
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

  // Each of the four axes points has only one coordinate
  double x1Graph = m_graphOutputsX.at(0);
  double x2Graph = m_graphOutputsX.at(1);
  double y3Graph = m_graphOutputsY.at(0);
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
  double numeratorx = (b0 * A11 - A01 * b1);
  double numeratory = (A00 * b1 - b0 * A10);
  double denominator = (A00 * A11 - A01 * A10);
  double sx = numeratorx / denominator;
  double sy = numeratory / denominator;

  // Intersection point. For the graph coordinates, the initial implementation assumes cartesian coordinates
  double xIntScreen = (1.0 - sx) * x1Screen + sx * x2Screen;
  double yIntScreen = (1.0 - sy) * y3Screen + sy * y4Screen;
  double xIntGraph, yIntGraph;
  if (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LINEAR) {
    xIntGraph = (1.0 - sx) * x1Graph + sx * x2Graph;
  } else {
    xIntGraph = qExp ((1.0 - sx) * qLn (x1Graph) + sx * qLn (x2Graph));
  }
  if (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR) {
    yIntGraph = (1.0 - sy) * y3Graph + sy * y4Graph;
  } else {
    yIntGraph = qExp ((1.0 - sy) * qLn (y3Graph) + sy * qLn (y4Graph));
  }

  // Distances of 4 axis points from interception
  double distance1 = qSqrt ((x1Screen - xIntScreen) * (x1Screen - xIntScreen) +
                            (y1Screen - yIntScreen) * (y1Screen - yIntScreen));
  double distance2 = qSqrt ((x2Screen - xIntScreen) * (x2Screen - xIntScreen) +
                            (y2Screen - yIntScreen) * (y2Screen - yIntScreen));
  double distance3 = qSqrt ((x3Screen - xIntScreen) * (x3Screen - xIntScreen) +
                            (y3Screen - yIntScreen) * (y3Screen - yIntScreen));
  double distance4 = qSqrt ((x4Screen - xIntScreen) * (x4Screen - xIntScreen) +
                            (y4Screen - yIntScreen) * (y4Screen - yIntScreen));

  // We now have too many data points with both x and y coordinates:
  // (xInt,yInt) (xInt,y3) (xInt,y4) (x1,yInt) (x2,yInt)
  // so we pick just 3, making sure that those 3 are widely separated
  // (xInt,yInt) (x axis point furthest from xInt,yInt) (y axis point furthest from xInt,yInt)
  double xFurthestXAxisScreen, yFurthestXAxisScreen, xFurthestYAxisScreen, yFurthestYAxisScreen;
  double xFurthestXAxisGraph, yFurthestXAxisGraph, xFurthestYAxisGraph, yFurthestYAxisGraph;
  if (distance1 < distance2) {
    xFurthestXAxisScreen = x2Screen;
    yFurthestXAxisScreen = y2Screen;
    xFurthestXAxisGraph = x2Graph;
    yFurthestXAxisGraph = yIntGraph;
  } else {
    xFurthestXAxisScreen = x1Screen;
    yFurthestXAxisScreen = y1Screen;
    xFurthestXAxisGraph = x1Graph;
    yFurthestXAxisGraph = yIntGraph;
  }
  if (distance3 < distance4) {
    xFurthestYAxisScreen = x4Screen;
    yFurthestYAxisScreen = y4Screen;
    xFurthestYAxisGraph = xIntGraph;
    yFurthestYAxisGraph = y4Graph;
  } else {
    xFurthestYAxisScreen = x3Screen;
    yFurthestYAxisScreen = y3Screen;
    xFurthestYAxisGraph = xIntGraph;
    yFurthestYAxisGraph = y3Graph;
  }

  // Screen coordinates
  m_screenInputsTransform = QTransform (xIntScreen, xFurthestXAxisScreen, xFurthestYAxisScreen,
                                        yIntScreen, yFurthestXAxisScreen, yFurthestYAxisScreen,
                                        1.0       , 1.0                 , 1.0                 );

  // Graph coordinates
  m_graphOutputsTransform = QTransform (xIntGraph, xFurthestXAxisGraph, xFurthestYAxisGraph,
                                        yIntGraph, yFurthestXAxisGraph, yFurthestYAxisGraph,
                                        1.0      , 1.0                , 1.0                );
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
