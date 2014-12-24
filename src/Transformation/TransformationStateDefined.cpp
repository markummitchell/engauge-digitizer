#include "CallbackAxesCheckerFromAxesPoints.h"
#include "Checker.h"
#include "CmdMediator.h"
#include "Document.h"
#include "EnumsToQt.h"
#include "GridClassifier.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"
#include "TransformationStateContext.h"
#include "TransformationStateDefined.h"

TransformationStateDefined::TransformationStateDefined(TransformationStateContext &context,
                                                       QGraphicsScene &scene) :
  TransformationStateAbstractBase (context),
  m_axesChecker (new Checker (scene))
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

  m_axesChecker->prepareForDisplay (ftor.points(),
                                    ColorPaletteToQColor (cmdMediator.document().modelAxesChecker().lineColor()));
  m_axesChecker->setVisible (true);
}

void TransformationStateDefined::end(CmdMediator &cmdMediator,
                                     const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::end";

  m_axesChecker->setVisible (false);
}

void TransformationStateDefined::updateLineColor (const QColor &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateDefined::updateLineColor";

  m_axesChecker->setLineColor (lineColor);
}
