#include "HighlightsStateAbstractBase.h"
#include "HighlightsStateContext.h"

HighlightsStateAbstractBase::HighlightsStateAbstractBase(HighlightsStateContext &context) :
  m_context (context)
{
}

HighlightsStateAbstractBase::~HighlightsStateAbstractBase()
{
}

HighlightsStateContext &HighlightsStateAbstractBase::context ()
{
  return m_context;
}
