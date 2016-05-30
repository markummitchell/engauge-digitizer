/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordSystemContext.h"
#include "EngaugeAssert.h"
#include "Logger.h"

const CoordSystemIndex DEFAULT_COORD_SYSTEM_INDEX = 0;

CoordSystemContext::CoordSystemContext() :
  m_coordSystemIndex (DEFAULT_COORD_SYSTEM_INDEX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::CoordSystemContext";
}

CoordSystemContext::~CoordSystemContext()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::~CoordSystemContext";

  for (int i = 0; i < m_coordSystems.count(); i++) {
    CoordSystem *coordSystem = m_coordSystems.at (i);
    delete coordSystem;
  }

  m_coordSystems.clear ();
  m_coordSystemIndex = 0;
}

void CoordSystemContext::addCoordSystems(DocumentAxesPointsRequired documentAxesPointsRequired,
                                         unsigned int numberCoordSystemToAdd)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addCoordSystems"
                              << " numberToAdd=" << numberCoordSystemToAdd;

  // The CoordSystem vector is populated with defaults here
  for (unsigned int i = 0; i < numberCoordSystemToAdd; i++) {
    m_coordSystems.push_back (new CoordSystem (documentAxesPointsRequired));
  }
}

void CoordSystemContext::addGraphCurveAtEnd (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addGraphCurveAtEnd";

  m_coordSystems [m_coordSystemIndex]->addGraphCurveAtEnd(curveName);
}

void CoordSystemContext::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                              const QPointF &posGraph,
                                                              QString &identifier,
                                                              double ordinal,
                                                              bool isXOnly)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointAxisWithGeneratedIdentifier";

  m_coordSystems [m_coordSystemIndex]->addPointAxisWithGeneratedIdentifier(posScreen,
                                                                           posGraph,
                                                                           identifier,
                                                                           ordinal,
                                                                           isXOnly);
}

void CoordSystemContext::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                              const QPointF &posGraph,
                                                              const QString &identifier,
                                                              double ordinal,
                                                              bool isXOnly)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointAxisWithSpecifiedIdentifier";

  m_coordSystems [m_coordSystemIndex]->addPointAxisWithSpecifiedIdentifier(posScreen,
                                                                           posGraph,
                                                                           identifier,
                                                                           ordinal,
                                                                           isXOnly);
}

void CoordSystemContext::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                               const QPointF &posScreen,
                                                               QString &generatedIdentifier,
                                                               double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointGraphWithGeneratedIdentifier";

  m_coordSystems [m_coordSystemIndex]->addPointGraphWithGeneratedIdentifier(curveName,
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

  m_coordSystems [m_coordSystemIndex]->addPointGraphWithSpecifiedIdentifier(curveName,
                                                                            posScreen,
                                                                            identifier,
                                                                            ordinal);
}

void CoordSystemContext::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addPointsInCurvesGraphs";

  m_coordSystems [m_coordSystemIndex]->addPointsInCurvesGraphs(curvesGraphs);
}

void CoordSystemContext::checkAddPointAxis (const QPointF &posScreen,
                                            const QPointF &posGraph,
                                            bool &isError,
                                            QString &errorMessage,
                                            bool isXOnly)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::checkAddPointAxis";

  m_coordSystems [m_coordSystemIndex]->checkAddPointAxis(posScreen,
                                                         posGraph,
                                                         isError,
                                                         errorMessage,
                                                         isXOnly);
}

void CoordSystemContext::checkEditPointAxis (const QString &pointIdentifier,
                                             const QPointF &posScreen,
                                             const QPointF &posGraph,
                                             bool &isError,
                                             QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::checkEditPointAxis";

  m_coordSystems [m_coordSystemIndex]->checkEditPointAxis(pointIdentifier,
                                                          posScreen,
                                                          posGraph,
                                                          isError,
                                                          errorMessage);
}

const CoordSystem &CoordSystemContext::coordSystem () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::coordSystem";

  return *(m_coordSystems [m_coordSystemIndex]);
}

unsigned int CoordSystemContext::coordSystemCount() const
{
  return m_coordSystems.count();
}

CoordSystemIndex CoordSystemContext::coordSystemIndex () const
{
  return m_coordSystemIndex;
}

const Curve &CoordSystemContext::curveAxes () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curveAxes";

  return m_coordSystems [m_coordSystemIndex]->curveAxes();
}

Curve *CoordSystemContext::curveForCurveName (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curveForCurveName";

  return m_coordSystems [m_coordSystemIndex]->curveForCurveName(curveName);
}

const Curve *CoordSystemContext::curveForCurveName (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curveForCurveName";

  return m_coordSystems [m_coordSystemIndex]->curveForCurveName(curveName);
}

const CurvesGraphs &CoordSystemContext::curvesGraphs () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curvesGraphs";

  return m_coordSystems [m_coordSystemIndex]->curvesGraphs();
}

QStringList CoordSystemContext::curvesGraphsNames () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curvesGraphsNames";

  return m_coordSystems [m_coordSystemIndex]->curvesGraphsNames();
}

int CoordSystemContext::curvesGraphsNumPoints (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::curvesGraphsNumPoints";

  return m_coordSystems [m_coordSystemIndex]->curvesGraphsNumPoints(curveName);
}

void CoordSystemContext::editPointAxis (const QPointF &posGraph,
                                        const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::editPointAxis";

  m_coordSystems [m_coordSystemIndex]->editPointAxis(posGraph,
                                                     identifier);
}

bool CoordSystemContext::isXOnly (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::isXOnly";

  return m_coordSystems [m_coordSystemIndex]->isXOnly (pointIdentifier);
}

void CoordSystemContext::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvePointsAxes";

  m_coordSystems [m_coordSystemIndex]->iterateThroughCurvePointsAxes(ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvePointsAxes";

  m_coordSystems [m_coordSystemIndex]->iterateThroughCurvePointsAxes(ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurveSegments (const QString &curveName,
                                                      const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurveSegments";

  m_coordSystems [m_coordSystemIndex]->iterateThroughCurveSegments(curveName,
                                                                   ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvesPointsGraphs";

  m_coordSystems [m_coordSystemIndex]->iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

void CoordSystemContext::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::iterateThroughCurvesPointsGraphs";

  m_coordSystems [m_coordSystemIndex]->iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

bool CoordSystemContext::loadCurvesFile (const QString &curvesFile)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::loadCurvesFile";

  return m_coordSystems [m_coordSystemIndex]->loadCurvesFile (curvesFile);
}

void CoordSystemContext::loadPreVersion6 (QDataStream &str,
                                          double version)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::loadPreVersion6";

  m_coordSystems [m_coordSystemIndex]->loadPreVersion6 (str,
                                                        version);
}

void CoordSystemContext::loadVersion6 (QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::loadVersion6";

  m_coordSystems [m_coordSystemIndex]->loadVersion6 (reader);
}

void CoordSystemContext::loadVersions7AndUp (QXmlStreamReader &reader,
                                             DocumentAxesPointsRequired documentAxesPointsRequired)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::loadVersion7AndUp";

  int indexLast = m_coordSystems.count() - 1;
  m_coordSystems [indexLast]->loadVersions7AndUp (reader,
                                                  documentAxesPointsRequired);
}

DocumentModelAxesChecker CoordSystemContext::modelAxesChecker() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelAxesChecker";

  return m_coordSystems [m_coordSystemIndex]->modelAxesChecker();
}

DocumentModelColorFilter CoordSystemContext::modelColorFilter() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelColorFilter";

  return m_coordSystems [m_coordSystemIndex]->modelColorFilter();
}

DocumentModelCoords CoordSystemContext::modelCoords () const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelCoords";

  return m_coordSystems [m_coordSystemIndex]->modelCoords();
}

CurveStyles CoordSystemContext::modelCurveStyles() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelCurveStyles";

  return m_coordSystems [m_coordSystemIndex]->modelCurveStyles();
}

DocumentModelDigitizeCurve CoordSystemContext::modelDigitizeCurve() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelDigitizeCurve";

  return m_coordSystems [m_coordSystemIndex]->modelDigitizeCurve();
}

DocumentModelExportFormat CoordSystemContext::modelExport() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelExport";

  return m_coordSystems [m_coordSystemIndex]->modelExport();
}

DocumentModelGeneral CoordSystemContext::modelGeneral() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelGeneral";

  return m_coordSystems [m_coordSystemIndex]->modelGeneral();
}

DocumentModelGridDisplay CoordSystemContext::modelGridDisplay() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelGridDisplay";

  return m_coordSystems [m_coordSystemIndex]->modelGridDisplay();
}

DocumentModelGridRemoval CoordSystemContext::modelGridRemoval() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelGridRemoval";

  return m_coordSystems [m_coordSystemIndex]->modelGridRemoval();
}

DocumentModelPointMatch CoordSystemContext::modelPointMatch() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelPointMatch";

  return m_coordSystems [m_coordSystemIndex]->modelPointMatch();
}

DocumentModelSegments CoordSystemContext::modelSegments() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CoordSystemContext::modelSegments";

  return m_coordSystems [m_coordSystemIndex]->modelSegments();
}

void CoordSystemContext::movePoint (const QString &pointIdentifier,
                                    const QPointF &deltaScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::movePoint";

  return m_coordSystems [m_coordSystemIndex]->movePoint(pointIdentifier,
                                                        deltaScreen);
}

int CoordSystemContext::nextOrdinalForCurve (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::nextOrdinalForCurve";

  return m_coordSystems [m_coordSystemIndex]->nextOrdinalForCurve(curveName);
}

QPointF CoordSystemContext::positionGraph (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::positionGraph";

  return m_coordSystems [m_coordSystemIndex]->positionGraph(pointIdentifier);
}

QPointF CoordSystemContext::positionScreen (const QString &pointIdentifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::addGraphCurveAtEnd";

  return m_coordSystems [m_coordSystemIndex]->positionScreen(pointIdentifier);
}

void CoordSystemContext::print () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::print";

  return m_coordSystems [m_coordSystemIndex]->print();
}

void CoordSystemContext::printStream (QString indentation,
                                      QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::printStream";

  m_coordSystems [m_coordSystemIndex]->printStream(indentation,
                                                   str);
}

QString CoordSystemContext::reasonForUnsuccessfulRead () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::reasonForUnsuccessfulRead";

  return m_coordSystems [m_coordSystemIndex]->reasonForUnsuccessfulRead();
}

void CoordSystemContext::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::removePointAxis";

  m_coordSystems [m_coordSystemIndex]->removePointAxis(identifier);
}

void CoordSystemContext::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::removePointGraph";

  m_coordSystems [m_coordSystemIndex]->removePointGraph(identifier);
}

void CoordSystemContext::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::removePointsInCurvesGraphs";

  m_coordSystems [m_coordSystemIndex]->removePointsInCurvesGraphs(curvesGraphs);
}

void CoordSystemContext::saveXml (QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::saveXml";

  for (int index = 0; index < m_coordSystems.count(); index++) {
    m_coordSystems [index]->saveXml (writer);
  }
}

QString CoordSystemContext::selectedCurveName () const
{
  return m_coordSystems [m_coordSystemIndex]->selectedCurveName();
}

void CoordSystemContext::setCoordSystemIndex(CoordSystemIndex coordSystemIndex)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setCoordSystemIndex"
                              << " index=" << coordSystemIndex;

  ENGAUGE_ASSERT(coordSystemIndex < (unsigned int) m_coordSystems.count());

  m_coordSystemIndex = coordSystemIndex;
}

void CoordSystemContext::setCurveAxes (const Curve &curveAxes)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setCurveAxes";

  m_coordSystems [m_coordSystemIndex]->setCurveAxes(curveAxes);
}

void CoordSystemContext::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setCurvesGraphs";

  m_coordSystems [m_coordSystemIndex]->setCurvesGraphs(curvesGraphs);
}

void CoordSystemContext::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelAxesChecker";

  m_coordSystems [m_coordSystemIndex]->setModelAxesChecker(modelAxesChecker);
}

void CoordSystemContext::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelColorFilter";

  m_coordSystems [m_coordSystemIndex]->setModelColorFilter(modelColorFilter);
}

void CoordSystemContext::setModelCoords (const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelCoords";

  m_coordSystems [m_coordSystemIndex]->setModelCoords(modelCoords);
}

void CoordSystemContext::setModelCurveStyles(const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelCurveStyles";

  m_coordSystems [m_coordSystemIndex]->setModelCurveStyles(modelCurveStyles);
}

void CoordSystemContext::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelDigitizeCurve";

  m_coordSystems [m_coordSystemIndex]->setModelDigitizeCurve(modelDigitizeCurve);
}

void CoordSystemContext::setModelExport(const DocumentModelExportFormat &modelExport)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelExport";

  m_coordSystems [m_coordSystemIndex]->setModelExport (modelExport);
}

void CoordSystemContext::setModelGeneral (const DocumentModelGeneral &modelGeneral)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelGeneral";

  m_coordSystems [m_coordSystemIndex]->setModelGeneral(modelGeneral);
}

void CoordSystemContext::setModelGridDisplay(const DocumentModelGridDisplay &modelGridDisplay)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelGridDisplay";

  m_coordSystems [m_coordSystemIndex]->setModelGridDisplay(modelGridDisplay);
}

void CoordSystemContext::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelGridRemoval";

  m_coordSystems [m_coordSystemIndex]->setModelGridRemoval(modelGridRemoval);
}

void CoordSystemContext::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelPointMatch";

  m_coordSystems [m_coordSystemIndex]->setModelPointMatch(modelPointMatch);
}

void CoordSystemContext::setModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::setModelSegments";

  m_coordSystems [m_coordSystemIndex]->setModelSegments(modelSegments);
}

void CoordSystemContext::setSelectedCurveName(const QString &selectedCurveName)
{
  m_coordSystems [m_coordSystemIndex]->setSelectedCurveName(selectedCurveName);
}

bool CoordSystemContext::successfulRead () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::successfulRead";

  return m_coordSystems [m_coordSystemIndex]->successfulRead();
}

void CoordSystemContext::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystemContext::updatePointOrdinals";

  m_coordSystems [m_coordSystemIndex]->updatePointOrdinals(transformation);
}
