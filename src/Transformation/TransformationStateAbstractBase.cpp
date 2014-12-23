#include "TransformationStateAbstractBase.h"
#include "TransformationStateContext.h"

TransformationStateAbstractBase::TransformationStateAbstractBase(TransformationStateContext &context) :
  m_context (context)
{
}

TransformationStateAbstractBase::~TransformationStateAbstractBase()
{
}

TransformationStateContext &TransformationStateAbstractBase::context ()
{
  return m_context;
}
