#ifndef TUTORIAL_STATE_CHECKLIST_WIZARD_ABSTRACT_H
#define TUTORIAL_STATE_CHECKLIST_WIZARD_ABSTRACT_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Abstract class that supports checklist wizard panels
class TutorialStateChecklistWizardAbstract : public TutorialStateAbstractBase
{
 public:
  /// Single constructor
  TutorialStateChecklistWizardAbstract (TutorialStateContext &context);

 protected:
  /// Common begin processing
  void begin();

  /// Common end processing
  void end();

  /// Previous button for hooking up button to slot
  TutorialButton *previous();

 private:

  QGraphicsTextItem *m_title;
  QGraphicsPixmapItem *m_background;
  QGraphicsTextItem *m_text0;
  QGraphicsTextItem *m_text1;
  QGraphicsTextItem *m_text2;
  QGraphicsTextItem *m_text3;
  TutorialButton *m_previous;
};

#endif // TUTORIAL_STATE_CHECKLIST_WIZARD_ABSTRACT_H
