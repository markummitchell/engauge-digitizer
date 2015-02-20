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
  m_xGraphRange = other.xGraphRange ();
  m_yGraphRange = other.yGraphRange ();

  return *this;
}

bool Transformation::operator!=(const Transformation &other)
{
  return (m_transformIsDefined != other.transformIsDefined()) ||
         (m_transform != other.transformMatrix ()) ||
         (m_xGraphRange != other.xGraphRange()) ||
         (m_yGraphRange != other.yGraphRange());
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
    double angleRadians = atan2 (posGraphIn.y (),
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

      // Screen to graph
      QPointF cursorGraph, cursorGraphDelta;
      transform (cursorScreen, cursorGraph);
      transform (cursorScreenDelta, cursorGraphDelta);

      // Convert to polar if appropriate
      cursorGraph = cartesianOrPolarFromCartesian (m_modelCoords,
                                                   cursorGraph);
      cursorGraphDelta = cartesianOrPolarFromCartesian (m_modelCoords,
                                                        cursorGraphDelta);

      // Compute graph coordinates at cursor
      double xGraph = cursorGraph.x ();
      double yGraph = cursorGraph.y ();
      xGraph = roundOffSmallValues (xGraph, m_xGraphRange);
      yGraph = roundOffSmallValues (yGraph, m_yGraphRange);

      // Compute graph resolutions at cursor
      double resolutionXGraph = qAbs ((cursorGraphDelta.x () - cursorGraph.x ()) / X_DELTA_PIXELS);
      double resolutionYGraph = qAbs ((cursorGraphDelta.y () - cursorGraph.y ()) / Y_DELTA_PIXELS);
      resolutionXGraph = roundOffSmallValues (resolutionXGraph, m_xGraphRange);
      resolutionYGraph = roundOffSmallValues (resolutionYGraph, m_yGraphRange);

      coordsGraph = QString ("(%1, %2)")
                    .arg (xGraph, UNCONSTRAINED_FIELD_WIDTH, FORMAT, PRECISION_DIGITS)
                    .arg (yGraph, UNCONSTRAINED_FIELD_WIDTH, FORMAT, PRECISION_DIGITS);
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
  const QString DUMMY_CURVENAME ("dummy");

  Point p1 (DUMMY_CURVENAME, QPointF (0, 0), QPointF (0, 0));
  Point p2 (DUMMY_CURVENAME, QPointF (1, 0), QPointF (1, 0));
  Point p3 (DUMMY_CURVENAME, QPointF (0, 1), QPointF (0, 1));

  DocumentModelCoords modelCoords; // Default coordinates are simple linear and cartesian, which is what we want

  CallbackUpdateTransform cb (modelCoords);
  cb.callback (DUMMY_CURVENAME, p1);
  cb.callback (DUMMY_CURVENAME, p2);
  cb.callback (DUMMY_CURVENAME, p3);

  m_transformIsDefined = cb.transformIsDefined ();
  m_xGraphRange = cb.xGraphRange ();
  m_yGraphRange = cb.yGraphRange ();

  if (m_transformIsDefined) {
    m_transform = cb.transform ();
  }
}

double Transformation::roundOffSmallValues (double value, double range)
{
  if (qAbs (value) < range / qPow (10.0, PRECISION_DIGITS)) {
    value = 0.0;
  }

  return value;
}

void Transformation::transform (const QPointF &coordScreen,
                                QPointF &coordGraph) const
{
  ENGAUGE_ASSERT (m_transformIsDefined);

  coordGraph = m_transform.transposed ().map (coordScreen);
}

void Transformation::transformInverse (const QPointF &coordGraph,
                                       QPointF &coordScreen) const
{
  ENGAUGE_ASSERT (m_transformIsDefined);

  coordScreen = m_transform.inverted ().transposed ().map (coordGraph);
}

QTransform Transformation::transformMatrix () const
{
  return m_transform;
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
    m_xGraphRange = ftor.xGraphRange ();
    m_yGraphRange = ftor.yGraphRange ();

    if (m_transformIsDefined) {

      // The transform is actually calculated by the callback
      m_transform = ftor.transform ();
    }
  }
}

double Transformation::xGraphRange() const
{
  return m_xGraphRange;
}

double Transformation::yGraphRange() const
{
  return m_yGraphRange;
}
