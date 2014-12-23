#include "CallbackAxesCheckerFromAxesPoints.h"
#include "CmdMediator.h"
#include "GridClassifier.h"
#include "Logger.h"
#include "Transformation.h"
#include "TransformationStateContext.h"
#include "TransformationStateDefined.h"

TransformationStateDefined::TransformationStateDefined(TransformationStateContext &context) :
  TransformationStateAbstractBase (context),
  m_transformation (0)
{
}

void TransformationStateDefined::begin(CmdMediator &cmdMediator,
                                       const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::begin";

  // Initialize grid removal settings so user does not have to
  int countX, countY;
  double startX, startY, stepX, stepY;
  GridClassifier gridClassifier;
  gridClassifier.classify (cmdMediator.document().pixmap(),
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

  // Create axes checker
  CallbackAxesCheckerFromAxesPoints ftor;
  Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                    &CallbackAxesCheckerFromAxesPoints::callback);
  cmdMediator.iterateThroughCurvePointsAxes (ftorWithCallback);

//  m_axesChecker = new Checker (ftor.polygon ());
}

void TransformationStateDefined::end(CmdMediator &cmdMediator,
                                     const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::end";
}
