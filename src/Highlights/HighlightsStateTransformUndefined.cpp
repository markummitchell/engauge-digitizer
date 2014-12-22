#include "HighlightsStateContext.h"
#include "HighlightsStateTransformUndefined.h"
#include "Logger.h"

HighlightsStateTransformUndefined::HighlightsStateTransformUndefined(HighlightsStateContext &context) :
  HighlightsStateAbstractBase (context)
{
}

void HighlightsStateTransformUndefined::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "HighlightsStateTransformUndefined::begin";
}

void HighlightsStateTransformUndefined::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "HighlightsStateTransformUndefined::end";
}
