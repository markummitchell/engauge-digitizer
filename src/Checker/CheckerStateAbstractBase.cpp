#include "CheckerStateAbstractBase.h"
#include "CheckerStateContext.h"

CheckerStateAbstractBase::CheckerStateAbstractBase(CheckerStateContext &context) :
  m_context (context)
{
}

CheckerStateAbstractBase::~CheckerStateAbstractBase()
{
}

CheckerStateContext &CheckerStateAbstractBase::context ()
{
  return m_context;
}
