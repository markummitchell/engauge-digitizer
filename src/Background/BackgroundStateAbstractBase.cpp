#include "BackgroundStateAbstractBase.h"

BackgroundStateAbstractBase::BackgroundStateAbstractBase(BackgroundStateContext &context) :
  m_context (context)
{
}

BackgroundStateAbstractBase::~BackgroundStateAbstractBase()
{
}

BackgroundStateContext &BackgroundStateAbstractBase::context()
{
  return m_context;
}

const BackgroundStateContext &BackgroundStateAbstractBase::context() const
{
  return m_context;
}
