#include "CheckerStateContext.h"
#include "CheckerStateTransformUndefined.h"
#include "Logger.h"

CheckerStateTransformUndefined::CheckerStateTransformUndefined(CheckerStateContext &context) :
  CheckerStateAbstractBase (context)
{
}

void CheckerStateTransformUndefined::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CheckerStateTransformUndefined::begin";
}

void CheckerStateTransformUndefined::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CheckerStateTransformUndefined::end";
}
