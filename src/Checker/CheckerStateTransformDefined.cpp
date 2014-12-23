#include "CheckerStateContext.h"
#include "CheckerStateTransformDefined.h"
#include "Logger.h"

CheckerStateTransformDefined::CheckerStateTransformDefined(CheckerStateContext &context) :
  CheckerStateAbstractBase (context),
  m_checker (0)
{
}

void CheckerStateTransformDefined::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CheckerStateTransformDefined::begin";
}

void CheckerStateTransformDefined::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CheckerStateTransformDefined::end";
}
