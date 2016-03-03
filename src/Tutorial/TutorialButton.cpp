/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "TutorialButton.h"
#include "TutorialButtonRect.h"
#include "TutorialButtonText.h"

const int HORIZONTAL_PADDING = 10;
const int VERTICAL_PADDING = 5;
const double Z_IN_FRONT = 1;

TutorialButton::TutorialButton (const QString &text,
                                QGraphicsScene &scene)
{
  createRect (scene);
  createText (text);
}

TutorialButton::~TutorialButton ()
{
  QGraphicsScene *scene = m_rect->scene();
  scene->removeItem (m_rect); // This also removes m_text from the scene
}

void TutorialButton::createRect (QGraphicsScene &scene)
{
  // Create rectangle and text items
  m_rect = new TutorialButtonRect (*this);
  m_rect->show ();
  m_rect->setPen (QPen (Qt::gray));
  m_rect->setBrush (QBrush (Qt::white));
  m_rect->setZValue (Z_IN_FRONT);
  scene.addItem (m_rect);
}

void TutorialButton::createText (const QString &text)
{
  // Create text. There is no need to call QGraphicsScene::addItem since it gets added automatically as the
  // child of m_rect
  m_text = new TutorialButtonText (*this,
                                   text,
                                   m_rect);
  m_text->show ();
}

QSize TutorialButton::size () const
{
  // The size of the rectangle is not updated until later so we use the size of the text
  return QSize (m_text->boundingRect().size().width() + 2 * HORIZONTAL_PADDING,
                m_text->boundingRect().size().height() + 2 * VERTICAL_PADDING);
}

void TutorialButton::handleTriggered()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialButton::handleTriggered";

  // Relay signal from internal widgets to outside world
  emit signalTriggered ();
}

void TutorialButton::setGeometry (const QPoint &pos)
{
  // Size the rectangle to fit the text, now that the extent of the text is known, with padding on the four sides
  m_rect->setRect(pos.x(),
                  pos.y(),
                  m_text->boundingRect().width() + 2 * HORIZONTAL_PADDING,
                  m_text->boundingRect().height() + 2 * VERTICAL_PADDING);

  // Put text at the center of the rectangle
  m_text->setPos (pos.x() + m_rect->boundingRect().width() / 2.0 - m_text->boundingRect().width() / 2.0,
                  pos.y() + m_rect->boundingRect().height() / 2.0 - m_text->boundingRect().height() / 2.0);
}
