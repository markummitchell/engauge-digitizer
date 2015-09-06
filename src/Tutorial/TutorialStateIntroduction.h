#ifndef TUTORIAL_STATE_INTRODUCTION_H
#define TUTORIAL_STATE_INTRODUCTION_H

class TutorialStateContext;

class QGraphicsPixmapItem;

/// Introduction state/panel is the first panel the user sees
class TutorialStateIntroduction : public TutorialStateAbstractBase
{
 public:
  /// Single constructor
  TutorialStateIntroduction (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 private:

  QGraphicsPixmapItem *m_background;
};

#endif // TUTORIAL_STATE_INTRODUCTION_H
