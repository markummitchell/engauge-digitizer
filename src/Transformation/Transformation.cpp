#include "CallbackUpdateTransform.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <qmath.h>
#include <QtGlobal>
#include "Transformation.h"

/// Max number of significant digits. Number of pixels in each direction should just fit into this
/// number of characters.
const int PRECISION_DIGITS = 4;

const double PI = 3.1415926535;

Transformation::Transformation() :
  m_transformIsDefined (false)
{
}

Transformation &Transformation::operator=(const Transformation &other)
{
  m_transformIsDefined = other.transformIsDefined();
  m_transform = other.transformMatrix ();

  return *this;
}

bool Transformation::operator!=(const Transformation &other)
{
  return (m_transformIsDefined != other.transformIsDefined()) ||
         (m_transform != other.transformMatrix ());
}

QTransform Transformation::calculateTransformFromLinearCartesianPoints (const QPointF &posFrom0,
                                                                        const QPointF &posFrom1,
                                                                        const QPointF &posFrom2,
                                                                        const QPointF &posTo0,
                                                                        const QPointF &posTo1,
                                                                        const QPointF &posTo2)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Transformation::calculateTransformFromLinearCartesianPoints";

  QTransform from, to;
  from.setMatrix (posFrom0.x(), posFrom1.x(), posFrom2.x(),
                  posFrom0.y(), posFrom1.y(), posFrom2.y(),
                  1.0,          1.0,          1.0);

  to.setMatrix (posTo0.x(), posTo1.x(), posTo2.x(),
                posTo0.y(), posTo1.y(), posTo2.y(),
                1.0,        1.0,        1.0);
  QTransform fromInv = from.inverted ();

  return to * fromInv;
}

QPointF Transformation::cartesianFromCartesianOrPolar (const DocumentModelCoords &modelCoords,
                                                       const QPointF &posGraphIn)
{
  // Initialize assuming input coordinates are already cartesian
  QPointF posGraphCartesian = posGraphIn;

  if (modelCoords.coordsType() == COORDS_TYPE_POLAR) {

    // Input coordinates are polar so convert them
    double angleRadians;
    switch (modelCoords.coordThetaUnits())
    {
      case COORD_THETA_UNITS_DEGREES:
      case COORD_THETA_UNITS_DEGREES_MINUTES:
      case COORD_THETA_UNITS_DEGREES_MINUTES_SECONDS:
        angleRadians = posGraphIn.x () * PI / 180.0;
        break;

      case COORD_THETA_UNITS_GRADIANS:
        angleRadians = posGraphIn.x () * PI / 200.0;
        break;

      case COORD_THETA_UNITS_RADIANS:
        angleRadians = posGraphIn.x ();
        break;

      case COORD_THETA_UNITS_TURNS:
        angleRadians = posGraphIn.x () * 2.0 * PI;
        break;

      default:
        ENGAUGE_ASSERT (false);
    }

    double radius = posGraphIn.y ();
    posGraphCartesian.setX (radius * cos (angleRadians));
    posGraphCartesian.setY (radius * sin (angleRadians));
  }

  return posGraphCartesian;
}

QPointF Transformation::cartesianOrPolarFromCartesian (const DocumentModelCoords &modelCoords,
                                                       const QPointF &posGraphIn)
{
  // Initialize assuming output coordinates are to be cartesian
  QPointF posGraphCartesianOrPolar = posGraphIn;

  if (modelCoords.coordsType() == COORDS_TYPE_POLAR) {

    // Output coordinates are to be polar so convert them
    double angleRadians = qAtan2 (posGraphIn.y (),
                                  posGraphIn.x ());
    switch (modelCoords.coordThetaUnits())
    {
      case COORD_THETA_UNITS_DEGREES:
      case COORD_THETA_UNITS_DEGREES_MINUTES:
      case COORD_THETA_UNITS_DEGREES_MINUTES_SECONDS:
        posGraphCartesianOrPolar.setX (angleRadians * 180.0 / PI);
        break;

      case COORD_THETA_UNITS_GRADIANS:
        posGraphCartesianOrPolar.setX (angleRadians * 200.0 / PI);
        break;

      case COORD_THETA_UNITS_RADIANS:
        posGraphCartesianOrPolar.setX (angleRadians);
        break;

      case COORD_THETA_UNITS_TURNS:
        posGraphCartesianOrPolar.setX (angleRadians / 2.0 / PI);
        break;

      default:
        ENGAUGE_ASSERT (false);
    }

    double radius = qSqrt (posGraphIn.x () * posGraphIn.x () + posGraphIn.y () * posGraphIn.y ());
    posGraphCartesianOrPolar.setY (radius);
  }

  return posGraphCartesianOrPolar;
}

void Transformation::coordTextForStatusBar (QPointF cursorScreen,
                                            QString &coordsScreen,
                                            QString &coordsGraph,
                                            QString &resolutionsGraph)
{
  const int UNCONSTRAINED_FIELD_WIDTH = 0;
  const double X_DELTA_PIXELS = 1.0, Y_DELTA_PIXELS = 1.0;
  const char FORMAT = 'g';

  if (cursorScreen.x() < 0 ||
      cursorScreen.y() < 0) {

    // Out of bounds, so return empty text
    coordsScreen = "";
    coordsGraph = "";
    resolutionsGraph = "";

  } else {

    coordsScreen = QString("(%1, %2)")
                   .arg (cursorScreen.x ())
                   .arg (cursorScreen.y ());

    if (m_transformIsDefined) {

      // For resolution we compute graph coords for cursorScreen, and then for cursorScreen plus a delta
      QPointF cursorScreenDelta (cursorScreen.x () + X_DELTA_PIXELS,
                                 cursorScreen.y () + Y_DELTA_PIXELS);

      // Convert to graph coordinates
      QPointF pointGraph, pointGraphDelta;
      transformScreenToRawGraph (cursorScreen,
                                 pointGraph);
      transformScreenToRawGraph (cursorScreenDelta,
                                 pointGraphDelta);

      // Compute graph resolutions at cursor
      double resolutionXGraph = qAbs ((pointGraphDelta.x () - pointGraph.x ()) / X_DELTA_PIXELS);
      double resolutionYGraph = qAbs ((pointGraphDelta.y () - pointGraph.y ()) / Y_DELTA_PIXELS);

      coordsGraph = QString ("(%1, %2)")
                    .arg (pointGraph.x(), UNCONSTRAINED_FIELD_WIDTH, FORMAT, PRECISION_DIGITS)
                    .arg (pointGraph.y(), UNCONSTRAINED_FIELD_WIDTH, FORMAT, PRECISION_DIGITS);
      resolutionsGraph = QString ("(%1, %2)")
                         .arg (resolutionXGraph, UNCONSTRAINED_FIELD_WIDTH, FORMAT, PRECISION_DIGITS)
                         .arg (resolutionYGraph, UNCONSTRAINED_FIELD_WIDTH, FORMAT, PRECISION_DIGITS);

    } else {

      coordsGraph = "<font color=\"red\">Need more axis points</font>";
      resolutionsGraph = coordsGraph;

    }
  }
}

void Transformation::identity()
{
  // Initialize assuming points (0,0) (1,0) (0,1)
  m_transformIsDefined = true;

  QTransform ident;
  m_transform = ident;
}

DocumentModelCoords Transformation::modelCoords() const
{
  return m_modelCoords;
}

double Transformation::roundOffSmallValues (double value, double range)
{
  if (qAbs (value) < range / qPow (10.0, PRECISION_DIGITS)) {
    value = 0.0;
  }

  return value;
}

void Transformation::transformLinearCartesianGraphToRawGraph (const QPointF &pointLinearCartesianGraph,
                                                              QPointF &pointRawGraph) const
{
  // Apply polar coordinates if appropriate
  pointRawGraph = pointLinearCartesianGraph;

  if (m_modelCoords.coordsType() == COORDS_TYPE_POLAR) {
    pointRawGraph = cartesianOrPolarFromCartesian (m_modelCoords,
                                                   pointLinearCartesianGraph);
  }

  // Apply log scaling if appropriate
  if (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG) {
    pointRawGraph.setX (qExp (pointRawGraph.x()));
  }

  if (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
    pointRawGraph.setY (qExp (pointRawGraph.y()));
  }
}

void Transformation::transformLinearCartesianGraphToScreen (const QPointF &coordGraph,
                                                            QPointF &coordScreen) const
{
  ENGAUGE_ASSERT (m_transformIsDefined);

  coordScreen = m_transform.inverted ().transposed ().map (coordGraph);
}

QTransform Transformation::transformMatrix () const
{
  return m_transform;
}

void Transformation::transformRawGraphToLinearCartesianGraph (const QPointF &pointRaw,
                                                              QPointF &pointLinearCartesian) const
{
  double x = pointRaw.x();
  double y = pointRaw.y();

  // Apply log scaling if appropriate
  if (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG) {
    x = qLn (x);
  }

  if (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
    y = qLn (y);
  }

  // Apply polar coordinates if appropriate. Note range coordinate has just been transformed if it has log scaling
  if (m_modelCoords.coordsType() == COORDS_TYPE_POLAR) {
    QPointF pointCart = cartesianFromCartesianOrPolar (m_modelCoords,
                                                       QPointF (x, y));
    x = pointCart.x();
    y = pointCart.y();
  }

  pointLinearCartesian.setX (x);
  pointLinearCartesian.setY (y);
}

void Transformation::transformRawGraphToScreen (const QPointF &pointRaw,
                                                QPointF &pointScreen) const
{
  QPointF pointLinearCartesianGraph;

  transformRawGraphToLinearCartesianGraph (pointRaw,
                                           pointLinearCartesianGraph);
  transformLinearCartesianGraphToScreen (pointLinearCartesianGraph,
                                         pointScreen);
}

void Transformation::transformScreenToLinearCartesianGraph (const QPointF &coordScreen,
                                                            QPointF &coordGraph) const
{
  ENGAUGE_ASSERT (m_transformIsDefined);

  coordGraph = m_transform.transposed ().map (coordScreen);
}

void Transformation::transformScreenToRawGraph (const QPointF &coordScreen,
                                                QPointF &coordGraph) const
{
  QPointF pointLinearCartesianGraph;
  transformScreenToLinearCartesianGraph (coordScreen,
                                         pointLinearCartesianGraph);
  transformLinearCartesianGraphToRawGraph (pointLinearCartesianGraph,
                                           coordGraph);
}

void Transformation::update (bool fileIsLoaded,
                             const CmdMediator &cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Transformation::update";

  if (!fileIsLoaded) {

    m_transformIsDefined = false;

  } else {

    m_modelCoords = cmdMediator.document().modelCoords();

    CallbackUpdateTransform ftor (m_modelCoords);

    Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                      &CallbackUpdateTransform::callback);
    cmdMediator.iterateThroughCurvePointsAxes (ftorWithCallback);

    m_transformIsDefined = ftor.transformIsDefined ();

    if (m_transformIsDefined) {

      updateTransformFromMatrices (ftor.matrixScreen(),
                                   ftor.matrixGraph());
    }
  }
}

void Transformation::updateTransformFromMatrices (const QTransform &matrixScreen,
                                                  const QTransform &matrixGraph)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Transformation::updateTransformFromMatrices";

  QPointF pointGraphRaw0 (matrixScreen.m11(),
                          matrixScreen.m21());
  QPointF pointGraphRaw1 (matrixScreen.m12(),
                          matrixScreen.m22());
  QPointF pointGraphRaw2 (matrixScreen.m13(),
                          matrixScreen.m23());

  QPointF pointGraphLinearCart0, pointGraphLinearCart1, pointGraphLinearCart2;
  transformRawGraphToLinearCartesianGraph (pointGraphRaw0,
                                           pointGraphLinearCart0);
  transformRawGraphToLinearCartesianGraph (pointGraphRaw1,
                                           pointGraphLinearCart1);
  transformRawGraphToLinearCartesianGraph (pointGraphRaw2,
                                           pointGraphLinearCart2);

  double gm [3] [3] = {
    {matrixGraph.m11 (), matrixGraph.m12 (), matrixGraph.m13 ()},
    {matrixGraph.m21 (), matrixGraph.m22 (), matrixGraph.m23 ()},
    {matrixGraph.m31 (), matrixGraph.m32 (), matrixGraph.m33 ()}};

  // Apply log scaling if appropriate
  if (m_modelCoords.coordScaleXTheta()) {
    gm [0] [0] = qLn (gm [0] [0]);
    gm [0] [1] = qLn (gm [0] [1]);
    gm [0] [2] = qLn (gm [0] [2]);
  }

  if (m_modelCoords.coordScaleYRadius()) {
    gm [1] [0] = qLn (gm [1] [0]);
    gm [1] [1] = qLn (gm [1] [1]);
    gm [1] [2] = qLn (gm [1] [2]);
  }

  // Apply polar coordinates if appropriate. Note range coordinate has just been transformed if it has log scaling
  if (m_modelCoords.coordsType() == COORDS_TYPE_POLAR) {
    QPointF pointCart0 = Transformation::cartesianFromCartesianOrPolar (m_modelCoords,
                                                                        QPointF (gm [0] [0], gm [1] [0]));
    QPointF pointCart1 = Transformation::cartesianFromCartesianOrPolar (m_modelCoords,
                                                                        QPointF (gm [0] [1], gm [1] [1]));
    QPointF pointCart2 = Transformation::cartesianFromCartesianOrPolar (m_modelCoords,
                                                                        QPointF (gm [0] [2], gm [1] [2]));
    gm [0] [0] = pointCart0.x();
    gm [0] [1] = pointCart1.x();
    gm [0] [2] = pointCart2.x();
    gm [1] [0] = pointCart0.y();
    gm [1] [1] = pointCart1.y();
    gm [1] [2] = pointCart2.y();
  }

  // Calculate the transform
  m_transform = calculateTransformFromLinearCartesianPoints (QPointF (matrixScreen.m11(), matrixScreen.m21()),
                                                             QPointF (matrixScreen.m12(), matrixScreen.m22()),
                                                             QPointF (matrixScreen.m13(), matrixScreen.m23()),
                                                             QPointF (gm [0] [0], gm [1] [0]),
                                                             QPointF (gm [0] [1], gm [1] [1]),
                                                             QPointF (gm [0] [2], gm [1] [2]));
}
