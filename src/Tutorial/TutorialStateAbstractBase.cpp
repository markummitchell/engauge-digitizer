#include "TutorialStateAbstractBase.h"
#include "TutorialStateContext.h"

TutorialStateAbstractBase::TutorialStateAbstractBase(TutorialStateContext &context) :
  m_context (context)
{
}

TutorialStateAbstractBase::~TutorialStateAbstractBase()
{
}

int TutorialStateAbstractBase::buttonMargin () const
{
  return 10;
}

TutorialStateContext &TutorialStateAbstractBase::context ()
{
  return m_context;
}
