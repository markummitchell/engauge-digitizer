#ifndef TUTORIAL_STATE_CHECKLIST_WIZARD_LINES_H
#define TUTORIAL_STATE_CHECKLIST_WIZARD_LINES_H

#include "TutorialStateChecklistWizardAbstract.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Checklist wizard panel for lines discusses the checklist wizard, and returns to TRANSITION_STATE_SEGMENT_FILL
class TutorialStateChecklistWizardLines : public TutorialStateChecklistWizardAbstract
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateChecklistWizardLines (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called to return to previous panel
  void slotPrevious();
};

#endif // TUTORIAL_STATE_CHECKLIST_WIZARD_LINES_H
