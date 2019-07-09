/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "TutorialButton.h"
#include "TutorialStateChecklistWizardLines.h"
#include "TutorialStateContext.h"

TutorialStateChecklistWizardLines::TutorialStateChecklistWizardLines (TutorialStateContext &context) : 
  TutorialStateChecklistWizardAbstract (context)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardLines::TutorialStateChecklistWizardLines";
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
