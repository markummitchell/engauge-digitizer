#include "Logger.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "TutorialButton.h"
#include "TutorialButtonRect.h"
#include "TutorialButtonText.h"

TutorialButton::TutorialButton (const QPoint &pos,
                                const QString &text,
                                QGraphicsScene &scene)
{
  createRect (scene);
  createText (text,
              scene);
  setGeometry (pos);
}

void TutorialButton::createRect (QGraphicsScene &scene)
{
  // Create rectangle and text items
  m_rect = new TutorialButtonRect (*this);
  m_rect->show ();
  m_rect->setPen (QPen (Qt::gray));
  scene.addItem (m_rect);
  connect (m_rect, SIGNAL ())
}

void TutorialButton::createText (const QString &text,
                                 QGraphicsScene &scene)
{
  m_text = new TutorialButtonText (*this,
                                   text,
                                   m_rect);
  m_text->show ();
  scene.addItem (m_text);
}

void TutorialButton::handleTriggered()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialButton::handleTriggered";

  // Relay signal from internal widgets to outside world
  emit signalTriggered ();
}

void TutorialButton::setGeometry (const QPoint &pos)
{
  const int HORIZONTAL_PADDING = 10;
  const int VERTICAL_PADDING = 5;

  // Size the rectangle to fit the text, now that the extent of the text is known, with padding on the four sides
  m_rect->setRect(pos.x(),
                  pos.y(),
                  m_text->boundingRect().width() + 2 * HORIZONTAL_PADDING,
                  m_text->boundingRect().height() + 2 * VERTICAL_PADDING);

  // Put text at the center of the rectangle
  m_text->setPos (pos.x() + m_rect->boundingRect().width() / 2.0 - m_text->boundingRect().width() / 2.0,
                  pos.y() + m_rect->boundingRect().height() / 2.0 - m_text->boundingRect().height() / 2.0);
}
