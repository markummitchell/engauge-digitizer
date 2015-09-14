#include "Logger.h"
#include "TutorialButton.h"
#include "TutorialStateChecklistWizardLines.h"
#include "TutorialStateContext.h"

TutorialStateChecklistWizardLines::TutorialStateChecklistWizardLines (TutorialStateContext &context) : 
  TutorialStateChecklistWizardAbstract (context)
{
}

void TutorialStateChecklistWizardLines::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardLines::begin ()";

  TutorialStateChecklistWizardAbstract::begin();
  connect (previous(), SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));
}

void TutorialStateChecklistWizardLines::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardLines::end ()";

  TutorialStateChecklistWizardAbstract::end();
}

void TutorialStateChecklistWizardLines::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardLines::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_SEGMENT_FILL);
}
