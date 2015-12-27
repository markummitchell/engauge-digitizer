#include "GraphContext.h"
#include "Logger.h"

GraphContext::GraphContext()
{
}

GraphContext::~GraphContext()
{
}

void GraphContext::addGraphCurveAtEnd (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addGraphCurveAtEnd";

  m_graph.addGraphCurveAtEnd(curveName);
}

void GraphContext::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                        const QPointF &posGraph,
                                                        QString &identifier,
                                                        double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addPointAxisWithGeneratedIdentifier";

  m_graph.addPointAxisWithGeneratedIdentifier(posScreen,
                                              posGraph,
                                              identifier,
                                              ordinal);
}

void GraphContext::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                        const QPointF &posGraph,
                                                        const QString &identifier,
                                                        double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addPointAxisWithSpecifiedIdentifier";

  m_graph.addPointAxisWithSpecifiedIdentifier(posScreen,
                                              posGraph,
                                              identifier,
                                              ordinal);
}

void GraphContext::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                         const QPointF &posScreen,
                                                         QString &generatedIdentifier,
                                                         double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addPointGraphWithGeneratedIdentifier";

  m_graph.addPointGraphWithGeneratedIdentifier(curveName,
                                               posScreen,
                                               generatedIdentifier,
                                               ordinal);
}

void GraphContext::addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                         const QPointF &posScreen,
                                                         const QString &identifier,
                                                         double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addPointGraphWithSpecifiedIdentifier";

  m_graph.addPointGraphWithSpecifiedIdentifier(curveName,
                                               posScreen,
                                               identifier,
                                               ordinal);
}

void GraphContext::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addPointsInCurvesGraphs";

  m_graph.addPointsInCurvesGraphs(curvesGraphs);
}

void GraphContext::checkAddPointAxis (const QPointF &posScreen,
                                      const QPointF &posGraph,
                                      bool &isError,
                                      QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::checkAddPointAxis";

  m_graph.checkAddPointAxis(posScreen,
                            posGraph,
                            isError,
                            errorMessage);
}

void GraphContext::checkEditPointAxis (const QString &pointIdentifier,
                                       const QPointF &posScreen,
                                       const QPointF &posGraph,
                                       bool &isError,
                                       QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::checkEditPointAxis";

  m_graph.checkEditPointAxis(pointIdentifier,
                             posScreen,
                             posGraph,
                             isError,
                             errorMessage);
}

const Curve &GraphContext::curveAxes () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::curveAxes";

  return m_graph.curveAxes();
}

Curve *GraphContext::curveForCurveName (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::curveForCurveName";

  return m_graph.curveForCurveName(curveName);
}

const Curve *GraphContext::curveForCurveName (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::curveForCurveName";

  return m_graph.curveForCurveName(curveName);
}

const CurvesGraphs &GraphContext::curvesGraphs () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::curvesGraphs";

  return m_graph.curvesGraphs();
}

QStringList GraphContext::curvesGraphsNames () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::curvesGraphsNames";

  return m_graph.curvesGraphsNames();
}

int GraphContext::curvesGraphsNumPoints (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::curvesGraphsNumPoints";

  return m_graph.curvesGraphsNumPoints(curveName);
}

void GraphContext::editPointAxis (const QPointF &posGraph,
                                  const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::editPointAxis";

  m_graph.editPointAxis(posGraph,
                        identifier);
}

const Graph &GraphContext::graph () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::graph";

  return m_graph;
}

void GraphContext::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::iterateThroughCurvePointsAxes";

  m_graph.iterateThroughCurvePointsAxes(ftorWithCallback);
}

void GraphContext::iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::iterateThroughCurvePointsAxes";

  m_graph.iterateThroughCurvePointsAxes(ftorWithCallback);
}

void GraphContext::iterateThroughCurveSegments (const QString &curveName,
                                                const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::iterateThroughCurveSegments";

  m_graph.iterateThroughCurveSegments(curveName,
                                      ftorWithCallback);
}

void GraphContext::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::iterateThroughCurvesPointsGraphs";

  m_graph.iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

void GraphContext::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::iterateThroughCurvesPointsGraphs";

  m_graph.iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

bool GraphContext::loadCurvesFile (const QString &curvesFile)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::loadCurvesFile";

  return m_graph.loadCurvesFile (curvesFile);
}

DocumentModelAxesChecker GraphContext::modelAxesChecker() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelAxesChecker";

  return m_graph.modelAxesChecker();
}

DocumentModelColorFilter GraphContext::modelColorFilter() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelColorFilter";

  return m_graph.modelColorFilter();
}

DocumentModelCoords GraphContext::modelCoords () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelCoords";

  return m_graph.modelCoords();
}

CurveStyles GraphContext::modelCurveStyles() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelCurveStyles";

  return m_graph.modelCurveStyles();
}

DocumentModelDigitizeCurve GraphContext::modelDigitizeCurve() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelDigitizeCurve";

  return m_graph.modelDigitizeCurve();
}

DocumentModelExportFormat GraphContext::modelExport() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelExport";

  return m_graph.modelExport();
}

DocumentModelGeneral GraphContext::modelGeneral() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelGeneral";

  return m_graph.modelGeneral();
}

DocumentModelGridRemoval GraphContext::modelGridRemoval() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelGridRemoval";

  return m_graph.modelGridRemoval();
}

DocumentModelPointMatch GraphContext::modelPointMatch() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelPointMatch";

  return m_graph.modelPointMatch();
}

DocumentModelSegments GraphContext::modelSegments() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::modelSegments";

  return m_graph.modelSegments();
}

void GraphContext::movePoint (const QString &pointIdentifier,
                              const QPointF &deltaScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::movePoint";

  return m_graph.movePoint(pointIdentifier,
                           deltaScreen);
}

int GraphContext::nextOrdinalForCurve (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::nextOrdinalForCurve";

  return m_graph.nextOrdinalForCurve(curveName);
}

QPointF GraphContext::positionGraph (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::positionGraph";

  return m_graph.positionGraph(pointIdentifier);
}

QPointF GraphContext::positionScreen (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::addGraphCurveAtEnd";

  return m_graph.positionScreen(pointIdentifier);
}

void GraphContext::print () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::print";

  return m_graph.print();
}

void GraphContext::printStream (QString indentation,
                                QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::printStream";

  m_graph.printStream(indentation,
                      str);
}

QString GraphContext::reasonForUnsuccessfulRead () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::reasonForUnsuccessfulRead";

  return m_graph.reasonForUnsuccessfulRead();
}

void GraphContext::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::removePointAxis";

  m_graph.removePointAxis(identifier);
}

void GraphContext::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::removePointGraph";

  m_graph.removePointGraph(identifier);
}

void GraphContext::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::removePointsInCurvesGraphs";

  m_graph.removePointsInCurvesGraphs(curvesGraphs);
}

void GraphContext::saveXml (QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::saveXml";

  m_graph.saveXml (writer);
}

void GraphContext::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setCurvesGraphs";

  m_graph.setCurvesGraphs(curvesGraphs);
}

void GraphContext::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelAxesChecker";

  m_graph.setModelAxesChecker(modelAxesChecker);
}

void GraphContext::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelColorFilter";

  m_graph.setModelColorFilter(modelColorFilter);
}

void GraphContext::setModelCoords (const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelCoords";

  m_graph.setModelCoords(modelCoords);
}

void GraphContext::setModelCurveStyles(const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelCurveStyles";

  m_graph.setModelCurveStyles(modelCurveStyles);
}

void GraphContext::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelDigitizeCurve";

  m_graph.setModelDigitizeCurve(modelDigitizeCurve);
}

void GraphContext::setModelExport(const DocumentModelExportFormat &modelExport)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelExport";

  m_graph.setModelExport (modelExport);
}

void GraphContext::setModelGeneral (const DocumentModelGeneral &modelGeneral)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelGeneral";

  m_graph.setModelGeneral(modelGeneral);
}

void GraphContext::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelGridRemoval";

  m_graph.setModelGridRemoval(modelGridRemoval);
}

void GraphContext::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelPointMatch";

  m_graph.setModelPointMatch(modelPointMatch);
}

void GraphContext::setModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::setModelSegments";

  m_graph.setModelSegments(modelSegments);
}

bool GraphContext::successfulRead () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::successfulRead";

  return m_graph.successfulRead();
}

void GraphContext::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphContext::updatePointOrdinals";

  m_graph.updatePointOrdinals(transformation);
}
