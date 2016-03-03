/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TUTORIAL_STATE_CHECKLIST_WIZARD_POINTS_H
#define TUTORIAL_STATE_CHECKLIST_WIZARD_POINTS_H

#include "TutorialStateChecklistWizardAbstract.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Checklist wizard panel for points discusses the checklist wizard, and returns to TRANSITION_STATE_POINT_MATCH
class TutorialStateChecklistWizardPoints : public TutorialStateChecklistWizardAbstract
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateChecklistWizardPoints (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called to return to previous panel
  void slotPrevious();
};

#endif // TUTORIAL_STATE_CHECKLIST_WIZARD_POINTS_H
