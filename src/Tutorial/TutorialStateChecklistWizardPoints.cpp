#include "Logger.h"
#include "TutorialButton.h"
#include "TutorialStateChecklistWizardPoints.h"
#include "TutorialStateContext.h"

TutorialStateChecklistWizardPoints::TutorialStateChecklistWizardPoints (TutorialStateContext &context) : 
  TutorialStateChecklistWizardAbstract (context)
{
}

void TutorialStateChecklistWizardPoints::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardPoints::begin ()";

  TutorialStateChecklistWizardAbstract::begin();
  connect (previous(), SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));
}

void TutorialStateChecklistWizardPoints::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardPoints::end ()";

  TutorialStateChecklistWizardAbstract::end();
}

void TutorialStateChecklistWizardPoints::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardPoints::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_POINT_MATCH);
}
