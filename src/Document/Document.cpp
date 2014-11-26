#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Curve.h"
#include "Document.h"
#include "Logger.h"
#include "Point.h"
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QtToString.h>
#include "Transformation.h"

Document::Document (const QImage &image) :
  m_name ("untitled"),
  m_isModified (false),
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          LineStyle::defaultAxesCurve(),
                          PointStyle::defaultAxesCurve ()))
{
  m_successfulRead = true; // Reading from QImage always succeeds, resulting in empty Document

  m_pixmap.convertFromImage (image);

  m_curvesGraphs.addGraphCurveAtEnd (Curve (DEFAULT_GRAPH_CURVE_NAME,
                                            LineStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()),
                                            PointStyle::defaultGraphCurve (m_curvesGraphs.numCurves ())));
}

Document::Document (const QString &fileName) :
  m_name (fileName),
  m_isModified (false),
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          LineStyle::defaultAxesCurve(),
                          PointStyle::defaultAxesCurve()))
{
  m_successfulRead = true;

  QFile file(fileName);
  if (file.isReadable ()) {

    // Insert import code here

  } else {

    m_successfulRead = false;
    m_reasonForUnsuccessfulRead = "Operating system says file is not readable";
  }

  m_curvesGraphs.addGraphCurveAtEnd (Curve (DEFAULT_GRAPH_CURVE_NAME,
                                            LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                            PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves())));
}

void Document::addGraphCurveAtEnd (const QString &curveName)
{
  m_curvesGraphs.addGraphCurveAtEnd  (Curve (curveName,
                                             LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                             PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves())));
}

void Document::addPointAxis (const QPointF &posScreen,
                             const QPointF &posGraph,
                             QString &identifier)
{
  Point point (AXIS_CURVE_NAME,
               posScreen,
               posGraph);
  m_curveAxes->addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointAxis (const QPointF &posScreen,
                             const QPointF &posGraph,
                             const QString &identifier)
{
  Point point (AXIS_CURVE_NAME,
               posScreen,
               identifier,
               posGraph);
  m_curveAxes->addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointGraph (const QString &curveName,
                              const QPointF &posScreen,
                              QString &identifier)
{
  Point point (curveName,
               posScreen);
  m_curvesGraphs.addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraph"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointGraph (const QString &curveName,
                              const QPointF &posScreen,
                              const QString &identifier)
{
  Point point (curveName,
               posScreen,
               identifier);
  m_curvesGraphs.addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraph"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackAddPointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackAddPointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::applyTransformation (const Transformation &transformation)
{
  m_curvesGraphs.applyTransformation (transformation);
}

void Document::checkAddPointAxis (const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  bool &isError,
                                  QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::checkAddPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();

  CallbackCheckAddPointAxis ftor (posScreen,
                                  posGraph);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackCheckAddPointAxis::callback);
  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);

  isError = ftor.isError ();
  errorMessage = ftor.errorMessage ();
}

void Document::checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::checkEditPointAxis"
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();

  CallbackCheckEditPointAxis ftor (pointIdentifier,
                                   posScreen,
                                   posGraph);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackCheckEditPointAxis::callback);
  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);

  isError = ftor.isError ();
  errorMessage = ftor.errorMessage ();
}

const Curve &Document::curveAxes () const
{
  Q_ASSERT (m_curveAxes != 0);

  return *m_curveAxes;
}

Curve *Document::curveForCurveName (const QString &curveName)
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const Curve *Document::curveForCurveName (const QString &curveName) const
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const CurvesGraphs &Document::curvesGraphs () const
{
  return m_curvesGraphs;
}

QStringList Document::curvesGraphsNames() const
{
  return m_curvesGraphs.curvesGraphsNames();
}

int Document::curvesGraphsNumPoints(const QString &curveName) const
{
  return m_curvesGraphs.curvesGraphsNumPoints(curveName);
}

DlgModelCoords Document::dlgModelCoords() const
{
  return m_dlgModelCoords;
}

void Document::editPointAxis (const QPointF &posGraph,
                              const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::editPointAxis posGraph=("
                              << posGraph.x () << ", " << posGraph.y () << ") identifier="
                              << identifier.toLatin1 ().data ();

  m_curveAxes->editPoint (posGraph,
                          identifier);
}

void Document::exportToClipboard (const QStringList &selected,
                                  bool transformIsDefined,
                                  QTextStream &strCsv,
                                  QTextStream &strHtml,
                                  CurvesGraphs &curvesGraphs) const
{
  m_curvesGraphs.exportToClipboard (selected,
                                    transformIsDefined,
                                    strCsv,
                                    strHtml,
                                    curvesGraphs);
}

bool Document::isModified () const
{
  return m_isModified;
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  Q_ASSERT (m_curveAxes != 0);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  Q_ASSERT (m_curveAxes != 0);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  Q_ASSERT (m_curveAxes != 0);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::movePoint (const QString &pointIdentifier,
                          const QPointF &deltaScreen)
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  curve->movePoint (pointIdentifier,
                    deltaScreen);
}

QPixmap Document::pixmap () const
{
  return m_pixmap;
}

QPointF Document::positionGraph (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionGraph (pointIdentifier);
}

QPointF Document::positionScreen (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionScreen (pointIdentifier);
}

QString Document::reasonForUnsuccessfulRead () const
{
  Q_ASSERT (!m_successfulRead);

  return m_reasonForUnsuccessfulRead;
}

void Document::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointAxis identifier=" << identifier.toLatin1 ().data ();

  m_curveAxes->removePoint (identifier);
}

void Document::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointGraph identifier=" << identifier.toLatin1 ().data ();

  m_curvesGraphs.removePoint (identifier);
}

void Document::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackRemovePointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackRemovePointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setCurvesGraphs";

  m_curvesGraphs = curvesGraphs;
}

void Document::setDlgModelCoords (const DlgModelCoords &dlgModelCoords)
{
  m_dlgModelCoords = dlgModelCoords;
}

bool Document::successfulRead () const
{
  return m_successfulRead;
}
