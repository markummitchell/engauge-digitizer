#include "CallbackAxisPointsAbstract.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <qmath.h>
#include "QtToString.h"
#include "Transformation.h"

CallbackAxisPointsAbstract::CallbackAxisPointsAbstract(const DocumentModelCoords &modelCoords) :
  m_modelCoords (modelCoords),
  m_numberAxisPoints (0),
  m_isError (false)
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
  m_numberAxisPoints (0),
  m_isError (false)
{
}

bool CallbackAxisPointsAbstract::anyColumnsRepeat (double m [3] [3], int numberColumns)
{
  for (int colLeft = 0; colLeft < numberColumns; colLeft++) {
    for (int colRight = colLeft + 1; colRight < numberColumns; colRight++) {

      if ((m [0] [colLeft] == m [0] [colRight]) &&
          (m [1] [colLeft] == m [1] [colRight]) &&
          (m [2] [colLeft] == m [2] [colRight])) {

        // Columns colLeft and colRight repeat each other, which means matrix cannot be inverted
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
  CallbackSearchReturn rtn = CALLBACK_SEARCH_RETURN_CONTINUE;

  if (m_numberAxisPoints < 3) {

    QPointF posScreen = point.posScreen ();
    QPointF posGraph = point.posGraph ();

    if (m_pointIdentifierOverride == point.identifier ()) {

      // Override the old point coordinates with its new (if all tests are passed) coordinates
      posScreen = m_posScreenOverride;
      posGraph = m_posGraphOverride;
    }

    // Update range variables
    if ((m_numberAxisPoints == 0) || (posGraph.x () < m_xGraphLow)) { m_xGraphLow = posGraph.x (); }
    if ((m_numberAxisPoints == 0) || (posGraph.y () < m_yGraphLow)) { m_yGraphLow = posGraph.y (); }
    if ((m_numberAxisPoints == 0) || (posGraph.x () > m_xGraphHigh)) { m_xGraphHigh = posGraph.x (); }
    if ((m_numberAxisPoints == 0) || (posGraph.y () > m_yGraphHigh)) { m_yGraphHigh = posGraph.y (); }

    // Append one new column to each of the screen and graph coordinate matrices. Since QTransform::setTransform
    // deals with an entire array instead of element by element, we copy the QTransform arrays here, modify them,
    // and then copy them back. The local arrays are also handy for error checking

    double sm [3] [3] = {
      {m_screenInputs.m11 (), m_screenInputs.m12 (), m_screenInputs.m13 ()},
      {m_screenInputs.m21 (), m_screenInputs.m22 (), m_screenInputs.m23 ()},
      {m_screenInputs.m31 (), m_screenInputs.m32 (), m_screenInputs.m33 ()}};
    double gm [3] [3] = {
      {m_graphOutputs.m11 (), m_graphOutputs.m12 (), m_graphOutputs.m13 ()},
      {m_graphOutputs.m21 (), m_graphOutputs.m22 (), m_graphOutputs.m23 ()},
      {m_graphOutputs.m31 (), m_graphOutputs.m32 (), m_graphOutputs.m33 ()}};

    // Screen coordinates
    sm [0] [m_numberAxisPoints] = posScreen.x ();
    sm [1] [m_numberAxisPoints] = posScreen.y ();
    sm [2] [m_numberAxisPoints] = 1.0;

    // Graph coordinates
    gm [0] [m_numberAxisPoints] = posGraph.x ();
    gm [1] [m_numberAxisPoints] = posGraph.y ();
    gm [2] [m_numberAxisPoints] = 1.0;

    // Save screen matrix
    m_screenInputs.setMatrix (sm [0] [0], sm [0] [1], sm [0] [2],
                              sm [1] [0], sm [1] [1], sm [1] [2],
                              sm [2] [0], sm [2] [1], sm [2] [2]);

    // Save graph matrix. These are the raw graph coordinates, which means they may be polar coordinates
    // and/or have log scaling, since Transformation converts raw to linear cartesian cooordinates
    m_graphOutputs.setMatrix (gm [0] [0], gm [0] [1], gm [0] [2],
                              gm [1] [0], gm [1] [1], gm [1] [2],
                              gm [2] [0], gm [2] [1], gm [2] [2]);

    ++m_numberAxisPoints; // Update this number before calling anyColumnsRepeat and threePointsAreCollinear

    // Error checking
    if (anyColumnsRepeat (sm, m_numberAxisPoints)) {

      m_isError = true;
      m_errorMessage = "New axis point cannot be at the same screen position as an exisiting axis point";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (anyColumnsRepeat (gm, m_numberAxisPoints)) {

      m_isError = true;
      m_errorMessage = "New axis point cannot have the same graph coordinates as an existing axis point";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (threePointsAreCollinear (sm, m_numberAxisPoints)) {

      m_isError = true;
      m_errorMessage = "No more than two axis points can lie along the same line on the screen";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    } else if (threePointsAreCollinear (gm, m_numberAxisPoints)) {

      m_isError = true;
      m_errorMessage = "No more than two axis points can lie along the same line in graph coordinates";
      rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

    }
  }

  if (m_numberAxisPoints > 2) {

    // There are enough axis points
    rtn = CALLBACK_SEARCH_RETURN_INTERRUPT;

  }

  return rtn;
}

QTransform CallbackAxisPointsAbstract::matrixGraph () const
{
  return m_graphOutputs;
}

QTransform CallbackAxisPointsAbstract::matrixScreen () const
{
  return m_screenInputs;
}

bool CallbackAxisPointsAbstract::threePointsAreCollinear (double m [3] [3], int numberColumns)
{
  if (numberColumns == 3) {

    // Compute determinant to determine if the three points are collinear
    QTransform t (
        m [0] [0], m [0] [1], m [0] [2],
        m [1] [0], m [1] [1], m [1] [2],
        m [2] [0], m [2] [1], m [2] [2]);

    return (t.determinant() == 0);
  }

  return false;
}
