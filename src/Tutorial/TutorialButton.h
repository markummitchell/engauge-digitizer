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
  /// Single constructor
  TutorialButton(const QPoint &pos,
                 const QString &text,
                 QGraphicsScene &scene);

  /// Callback to be called when button was triggered by mouse event
  void handleTriggered();

 signals:
  /// Signal that button was triggered
  void signalTriggered ();

 private slots:
  void slotTriggered ();

 private:
  TutorialButton();

  void createRect (QGraphicsScene &scene);
  void createText (const QString &text,
                   QGraphicsScene &scene);
  void setGeometry (const QPoint &pos);

  TutorialButtonRect *m_rect;
  TutorialButtonText *m_text; // Child to rectangle
};

#endif // TUTORIAL_BUTTON_H
