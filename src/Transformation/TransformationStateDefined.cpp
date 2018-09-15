/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackAxesCheckerFromAxesPoints.h"
#include "Checker.h"
#include "CmdMediator.h"
#include "Document.h"
#include "EnumsToQt.h"
#include "FilterImage.h"
#include "GridClassifier.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QImage>
#include <QTimer>
#include "Transformation.h"
#include "TransformationStateContext.h"
#include "TransformationStateDefined.h"

const int SECONDS_TO_MILLISECONDS = 1000.0;

TransformationStateDefined::TransformationStateDefined(TransformationStateContext &context,
                                                       QGraphicsScene &scene) :
  TransformationStateAbstractBase (context),
  m_axesChecker (new Checker (scene)),
  m_timer (new QTimer)
{
  m_timer->setSingleShot (true);
  connect (m_timer, SIGNAL (timeout()), this, SLOT (slotTimeout()));
}

void TransformationStateDefined::begin(bool isGnuplot,
                                       CmdMediator &cmdMediator,
                                       const Transformation &transformation,
                                       const QString &selectedGraphCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::begin";

  if (!cmdMediator.document().modelGridDisplay().stable()) {

    // Initialize or update the grid display settings since they are not stable yet
    initializeModelGridDisplay (cmdMediator,
                                transformation);

  }

  if (!cmdMediator.document().modelGridRemoval().stable()) {

    // Initialize or update the grid removal settings since they are not stable yet
    initializeModelGridRemoval (isGnuplot,
                                cmdMediator,
                                transformation,
                                selectedGraphCurve);

  }

  updateAxesChecker (cmdMediator,
                     transformation);
}

void TransformationStateDefined::end(CmdMediator & /* cmdMediator */,
                                     const Transformation & /* transformation */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::end";

  m_axesChecker->setVisible (false);
}

void TransformationStateDefined::initializeModelGridDisplay (CmdMediator &cmdMediator,
                                                             const Transformation &transformation)
{
  cmdMediator.document().initializeGridDisplay (transformation);
}

void TransformationStateDefined::initializeModelGridRemoval (bool isGnuplot,
                                                             CmdMediator &cmdMediator,
                                                             const Transformation &transformation,
                                                             const QString &selectedGraphCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::initializeModelGridRemoval";

  // Generate filtered image
  FilterImage filterImage;
  QPixmap pixmapFiltered = filterImage.filter (isGnuplot,
                                               cmdMediator.document().pixmap().toImage(),
                                               transformation,
                                               selectedGraphCurve,
                                               cmdMediator.document().modelColorFilter(),
                                               cmdMediator.document().modelGridRemoval());

  // Initialize grid removal settings so user does not have to
  int countX, countY;
  double startX, startY, stepX, stepY;
  GridClassifier gridClassifier;
  gridClassifier.classify (context().isGnuplot(),
                           pixmapFiltered,
                           transformation,
                           countX,
                           startX,
                           stepX,
                           countY,
                           startY,
                           stepY);
  DocumentModelGridRemoval modelGridRemoval (startX,
                                             startY,
                                             stepX,
                                             stepY,
                                             countX,
                                             countY);
  cmdMediator.document().setModelGridRemoval (modelGridRemoval);
}

void TransformationStateDefined::slotTimeout()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::slotTimeout";

  m_axesChecker->setVisible (false);
}

void TransformationStateDefined::startTimer (const DocumentModelAxesChecker &modelAxesChecker)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::startTimer";

  m_axesChecker->setVisible (modelAxesChecker.checkerMode () != CHECKER_MODE_NEVER);

  if (modelAxesChecker.checkerMode () == CHECKER_MODE_N_SECONDS) {

    // Start timer
    int milliseconds = modelAxesChecker.checkerSeconds() * SECONDS_TO_MILLISECONDS;
    m_timer->start (milliseconds);
  }
}

void TransformationStateDefined::updateAxesChecker (CmdMediator &cmdMediator,
                                                    const Transformation &transformation)
{
  CallbackAxesCheckerFromAxesPoints ftor;
  Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                    &CallbackAxesCheckerFromAxesPoints::callback);
  cmdMediator.iterateThroughCurvePointsAxes (ftorWithCallback);

  m_axesChecker->prepareForDisplay (ftor.points(),
                                    cmdMediator.document().modelCurveStyles().pointRadius(AXIS_CURVE_NAME),
                                    cmdMediator.document().modelAxesChecker(),
                                    cmdMediator.document().modelCoords(),
                                    transformation,
                                    cmdMediator.document().documentAxesPointsRequired());
  m_axesChecker->setVisible (true);
  startTimer (cmdMediator.document().modelAxesChecker());
}
