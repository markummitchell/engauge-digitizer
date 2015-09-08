#ifndef TUTORIAL_BUTTON_H
#define TUTORIAL_BUTTON_H

#include <QObject>

class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsTextItem;
class QString;
class TutorialButtonRect;
class TutorialButtonText;

/// Show a button with text for clicking ion. The button is implemented using layering of two graphics items (text and rectangle)
class TutorialButton : public QObject
{
  Q_OBJECT;

 public:
  /// Single constructor. Position is set after creation using setGeometry
  TutorialButton(const QString &text,
                 QGraphicsScene &scene);
  ~TutorialButton();

  /// Callback to be called when button was triggered by mouse event
  void handleTriggered();

  /// Set the position. This is called after creation so screen extent is available for positioning calculations
  void setGeometry (const QPoint &pos);

  /// Size of this button
  QSize size () const;

 signals:
  /// Signal that button was triggered
  void signalTriggered ();

 private:
  TutorialButton();

  void createRect (QGraphicsScene &scene);
  void createText (const QString &text);

  TutorialButtonRect *m_rect;
  TutorialButtonText *m_text; // Child to rectangle
};

#endif // TUTORIAL_BUTTON_H
