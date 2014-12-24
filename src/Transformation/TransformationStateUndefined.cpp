#include "CmdMediator.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"
#include "TransformationStateContext.h"
#include "TransformationStateUndefined.h"

TransformationStateUndefined::TransformationStateUndefined(TransformationStateContext &context,
                                                           QGraphicsScene & /* scene */) :
  TransformationStateAbstractBase (context)
{
}

void TransformationStateUndefined::begin(CmdMediator &cmdMediator,
                                         const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateUndefined::begin";
}

void TransformationStateUndefined::end(CmdMediator &cmdMediator,
                                       const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateUndefined::end";
}

void TransformationStateUndefined::updateLineColor (const QColor & /* lineColor */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateUndefined::updateLineColor";

  // Noop
}
