#ifndef TUTORIAL_BUTTON_TEXT_H
#define TUTORIAL_BUTTON_TEXT_H

#include <QGraphicsTextItem>

class TutorialButton;

/// This class customizes QGraphicsTextItem so it performs a callback after a mouse event
class TutorialButtonText : public QGraphicsTextItem
{
 public:
  /// Single constructor
  TutorialButtonText (TutorialButton &tutorialButton,
                      const QString &text,
                      TutorialButtonRect *rect);

  /// Forward mouse event to TutorialButton
  virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

 private:
  TutorialButtonText ();

  TutorialButton &m_tutorialButton;
};

#endif // TUTORIAL_BUTTON_TEXT_H
