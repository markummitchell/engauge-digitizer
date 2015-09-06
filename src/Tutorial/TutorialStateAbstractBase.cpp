#include "TutorialStateAbstractBase.h"
#include "TutorialStateContext.h"

TutorialStateAbstractBase::TutorialStateAbstractBase(TutorialStateContext &context) :
  m_context (context)
{
}

TutorialStateAbstractBase::~TutorialStateAbstractBase()
{
}

TutorialStateContext &TutorialStateAbstractBase::context ()
{
  return m_context;
}
