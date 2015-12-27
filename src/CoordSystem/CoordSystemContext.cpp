#include "CoordSystemContext.h"
#include "Logger.h"

CoordSystemContext::CoordSystemContext()
{
}

CoordSystemContext::~CoordSystemContext()
{
}

void CoordSystemContext::addGraphCurveAtEnd (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addGraphCurveAtEnd";

  m_coordSystem.addGraphCurveAtEnd(curveName);
}

void CoordSystemContext::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                              const QPointF &posGraph,
                                                              QString &identifier,
                                                              double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointAxisWithGeneratedIdentifier";

  m_coordSystem.addPointAxisWithGeneratedIdentifier(posScreen,
                                                    posGraph,
                                                    identifier,
                                                    ordinal);
}

void CoordSystemContext::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                              const QPointF &posGraph,
                                                              const QString &identifier,
                                                              double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointAxisWithSpecifiedIdentifier";

  m_coordSystem.addPointAxisWithSpecifiedIdentifier(posScreen,
                                                    posGraph,
                                                    identifier,
                                                    ordinal);
}

void CoordSystemContext::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                               const QPointF &posScreen,
                                                               QString &generatedIdentifier,
                                                               double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointGraphWithGeneratedIdentifier";

  m_coordSystem.addPointGraphWithGeneratedIdentifier(curveName,
                                                     posScreen,
                                                     generatedIdentifier,
                                                     ordinal);
}

void CoordSystemContext::addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                               const QPointF &posScreen,
                                                               const QString &identifier,
                                                               double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointGraphWithSpecifiedIdentifier";

  m_coordSystem.addPointGraphWithSpecifiedIdentifier(curveName,
                                                     posScreen,
                                                     identifier,
                                                     ordinal);
}

void CoordSystemContext::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointsInCurvesGraphs";

  m_coordSystem.addPointsInCurvesGraphs(curvesGraphs);
}

void CoordSystemContext::checkAddPointAxis (const QPointF &posScreen,
                                            const QPointF &posGraph,
                                            bool &isError,
                                            QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::checkAddPointAxis";

  m_coordSystem.checkAddPointAxis(posScreen,
                                  posGraph,
                                  isError,
                                  errorMessage);
}

void CoordSystemContext::checkEditPointAxis (const QString &pointIdentifier,
                                             const QPointF &posScreen,
                                             const QPointF &posGraph,
                                             bool &isError,
                                             QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::checkEditPointAxis";

  m_coordSystem.checkEditPointAxis(pointIdentifier,
                                   posScreen,
                                   posGraph,
                                   isError,
                                   errorMessage);
}

const CoordSystem &CoordSystemContext::coordSystem () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::coordSystem";

  return m_coordSystem;
}

const Curve &CoordSystemContext::curveAxes () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curveAxes";

  return m_coordSystem.curveAxes();
}

Curve *CoordSystemContext::curveForCurveName (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curveForCurveName";

  return m_coordSystem.curveForCurveName(curveName);
}

const Curve *CoordSystemContext::curveForCurveName (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curveForCurveName";

  return m_coordSystem.curveForCurveName(curveName);
}

const CurvesGraphs &CoordSystemContext::curvesGraphs () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curvesGraphs";

  return m_coordSystem.curvesGraphs();
}

QStringList CoordSystemContext::curvesGraphsNames () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curvesGraphsNames";

  return m_coordSystem.curvesGraphsNames();
}

int CoordSystemContext::curvesGraphsNumPoints (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curvesGraphsNumPoints";

  return m_coordSystem.curvesGraphsNumPoints(curveName);
}

void CoordSystemContext::editPointAxis (const QPointF &posGraph,
                                        const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::editPointAxis";

  m_coordSystem.editPointAxis(posGraph,
                              identifier);
}

void CoordSystemContext::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvePointsAxes";

  m_coordSystem.iterateThroughCurvePointsAxes(ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvePointsAxes";

  m_coordSystem.iterateThroughCurvePointsAxes(ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurveSegments (const QString &curveName,
                                                      const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurveSegments";

  m_coordSystem.iterateThroughCurveSegments(curveName,
                                            ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvesPointsGraphs";

  m_coordSystem.iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvesPointsGraphs";

  m_coordSystem.iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

bool CoordSystemContext::loadCurvesFile (const QString &curvesFile)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::loadCurvesFile";

  return m_coordSystem.loadCurvesFile (curvesFile);
}

DocumentModelAxesChecker CoordSystemContext::modelAxesChecker() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelAxesChecker";

  return m_coordSystem.modelAxesChecker();
}

DocumentModelColorFilter CoordSystemContext::modelColorFilter() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelColorFilter";

  return m_coordSystem.modelColorFilter();
}

DocumentModelCoords CoordSystemContext::modelCoords () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelCoords";

  return m_coordSystem.modelCoords();
}

CurveStyles CoordSystemContext::modelCurveStyles() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelCurveStyles";

  return m_coordSystem.modelCurveStyles();
}

DocumentModelDigitizeCurve CoordSystemContext::modelDigitizeCurve() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelDigitizeCurve";

  return m_coordSystem.modelDigitizeCurve();
}

DocumentModelExportFormat CoordSystemContext::modelExport() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelExport";

  return m_coordSystem.modelExport();
}

DocumentModelGeneral CoordSystemContext::modelGeneral() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelGeneral";

  return m_coordSystem.modelGeneral();
}

DocumentModelGridRemoval CoordSystemContext::modelGridRemoval() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelGridRemoval";

  return m_coordSystem.modelGridRemoval();
}

DocumentModelPointMatch CoordSystemContext::modelPointMatch() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelPointMatch";

  return m_coordSystem.modelPointMatch();
}

DocumentModelSegments CoordSystemContext::modelSegments() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::modelSegments";

  return m_coordSystem.modelSegments();
}

void CoordSystemContext::movePoint (const QString &pointIdentifier,
                                    const QPointF &deltaScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::movePoint";

  return m_coordSystem.movePoint(pointIdentifier,
                                 deltaScreen);
}

int CoordSystemContext::nextOrdinalForCurve (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::nextOrdinalForCurve";

  return m_coordSystem.nextOrdinalForCurve(curveName);
}

QPointF CoordSystemContext::positionGraph (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::positionGraph";

  return m_coordSystem.positionGraph(pointIdentifier);
}

QPointF CoordSystemContext::positionScreen (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addGraphCurveAtEnd";

  return m_coordSystem.positionScreen(pointIdentifier);
}

void CoordSystemContext::print () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::print";

  return m_coordSystem.print();
}

void CoordSystemContext::printStream (QString indentation,
                                      QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::printStream";

  m_coordSystem.printStream(indentation,
                            str);
}

QString CoordSystemContext::reasonForUnsuccessfulRead () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::reasonForUnsuccessfulRead";

  return m_coordSystem.reasonForUnsuccessfulRead();
}

void CoordSystemContext::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::removePointAxis";

  m_coordSystem.removePointAxis(identifier);
}

void CoordSystemContext::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::removePointGraph";

  m_coordSystem.removePointGraph(identifier);
}

void CoordSystemContext::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::removePointsInCurvesGraphs";

  m_coordSystem.removePointsInCurvesGraphs(curvesGraphs);
}

void CoordSystemContext::saveXml (QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::saveXml";

  m_coordSystem.saveXml (writer);
}

void CoordSystemContext::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setCurvesGraphs";

  m_coordSystem.setCurvesGraphs(curvesGraphs);
}

void CoordSystemContext::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelAxesChecker";

  m_coordSystem.setModelAxesChecker(modelAxesChecker);
}

void CoordSystemContext::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelColorFilter";

  m_coordSystem.setModelColorFilter(modelColorFilter);
}

void CoordSystemContext::setModelCoords (const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelCoords";

  m_coordSystem.setModelCoords(modelCoords);
}

void CoordSystemContext::setModelCurveStyles(const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelCurveStyles";

  m_coordSystem.setModelCurveStyles(modelCurveStyles);
}

void CoordSystemContext::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelDigitizeCurve";

  m_coordSystem.setModelDigitizeCurve(modelDigitizeCurve);
}

void CoordSystemContext::setModelExport(const DocumentModelExportFormat &modelExport)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelExport";

  m_coordSystem.setModelExport (modelExport);
}

void CoordSystemContext::setModelGeneral (const DocumentModelGeneral &modelGeneral)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelGeneral";

  m_coordSystem.setModelGeneral(modelGeneral);
}

void CoordSystemContext::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelGridRemoval";

  m_coordSystem.setModelGridRemoval(modelGridRemoval);
}

void CoordSystemContext::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelPointMatch";

  m_coordSystem.setModelPointMatch(modelPointMatch);
}

void CoordSystemContext::setModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelSegments";

  m_coordSystem.setModelSegments(modelSegments);
}

bool CoordSystemContext::successfulRead () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::successfulRead";

  return m_coordSystem.successfulRead();
}

void CoordSystemContext::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::updatePointOrdinals";

  m_coordSystem.updatePointOrdinals(transformation);
}
