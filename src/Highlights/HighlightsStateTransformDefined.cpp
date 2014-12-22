#include "HighlightsStateContext.h"
#include "HighlightsStateTransformDefined.h"
#include "Logger.h"

HighlightsStateTransformDefined::HighlightsStateTransformDefined(HighlightsStateContext &context) :
  HighlightsStateAbstractBase (context),
  m_highlightsPoint0 (0),
  m_highlightsPoint1 (0),
  m_highlightsPoint2 (0)
{
}

void HighlightsStateTransformDefined::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "HighlightsStateTransformDefined::begin";
}

void HighlightsStateTransformDefined::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "HighlightsStateTransformDefined::end";
}
