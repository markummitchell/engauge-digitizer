/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PdfFrame.h"
#include "PdfFrameHandle.h"
#include <QGraphicsScene>
#include <QRect>

PdfFrame::PdfFrame (QGraphicsScene &scene,
                    const QRectF &imageRect)
{
  const double MARGIN_PERCENT = 10.0;

  double marginHor = imageRect.width()  * MARGIN_PERCENT / 100.0;
  double marginVer = imageRect.height() * MARGIN_PERCENT / 100.0;

  QRectF box (imageRect.left() + marginHor,
              imageRect.top()  + marginVer,
              imageRect.width() - 2 * marginHor,
              imageRect.height() - 2 * marginVer);
  QPointF topCenter    = (box.topLeft()     + box.topRight()   ) / 2.0;
  QPointF rightCenter  = (box.topRight()    + box.bottomRight()) / 2.0;
  QPointF bottomCenter = (box.bottomRight() + box.bottomLeft() ) / 2.0;
  QPointF leftCenter   = (box.bottomLeft()  + box.topLeft()    ) / 2.0;

  m_handleTL     = new PdfFrameHandle (scene, imageRect, box.topLeft()    , PDF_FRAME_LEFT   | PDF_FRAME_TOP    , *this);
  m_handleTop    = new PdfFrameHandle (scene, imageRect, topCenter        , PDF_FRAME_CENTER | PDF_FRAME_TOP    , *this);
  m_handleTR     = new PdfFrameHandle (scene, imageRect, box.topRight()   , PDF_FRAME_RIGHT  | PDF_FRAME_TOP    , *this);
  m_handleRight  = new PdfFrameHandle (scene, imageRect, rightCenter      , PDF_FRAME_RIGHT  | PDF_FRAME_MIDDLE , *this);
  m_handleBR     = new PdfFrameHandle (scene, imageRect, box.bottomRight(), PDF_FRAME_RIGHT  | PDF_FRAME_BOTTOM , *this);
  m_handleBottom = new PdfFrameHandle (scene, imageRect, bottomCenter     , PDF_FRAME_CENTER | PDF_FRAME_BOTTOM , *this);
  m_handleBL     = new PdfFrameHandle (scene, imageRect, box.bottomLeft() , PDF_FRAME_LEFT   | PDF_FRAME_BOTTOM , *this);
  m_handleLeft   = new PdfFrameHandle (scene, imageRect, leftCenter       , PDF_FRAME_LEFT   | PDF_FRAME_MIDDLE , *this);
}

void PdfFrame::disableEventsWhileMovingAutomatically ()
{
  m_handleTL->setDisableEventsWhileMovingAutomatically (true);
  m_handleTop->setDisableEventsWhileMovingAutomatically (true);
  m_handleTR->setDisableEventsWhileMovingAutomatically (true);
  m_handleRight->setDisableEventsWhileMovingAutomatically (true);
  m_handleBR->setDisableEventsWhileMovingAutomatically (true);
  m_handleBottom->setDisableEventsWhileMovingAutomatically (true);
  m_handleBL->setDisableEventsWhileMovingAutomatically (true);
  m_handleLeft->setDisableEventsWhileMovingAutomatically (true);
}

void PdfFrame::enableEventsWhileMovingAutomatically ()
{
  m_handleTL->setDisableEventsWhileMovingAutomatically (false);
  m_handleTop->setDisableEventsWhileMovingAutomatically (false);
  m_handleTR->setDisableEventsWhileMovingAutomatically (false);
  m_handleRight->setDisableEventsWhileMovingAutomatically (false);
  m_handleBR->setDisableEventsWhileMovingAutomatically (false);
  m_handleBottom->setDisableEventsWhileMovingAutomatically (false);
  m_handleBL->setDisableEventsWhileMovingAutomatically (false);
  m_handleLeft->setDisableEventsWhileMovingAutomatically (false);
}

void PdfFrame::moveBL (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleTL->moveBy (newPos.x() - oldPos.x(),
                      0);
  m_handleBR->moveBy (0,
                      newPos.y() - oldPos.y());

  m_handleLeft->setPos (m_handleTL->x(),
                        (m_handleTL->y() + m_handleBL->y()) / 2.0);
  m_handleBottom->setPos ((m_handleBL->x() + m_handleBR->x()) / 2.0,
                          m_handleBL->y());

  m_handleTop->setPos (m_handleBottom->x(),
                       m_handleTop->y());
  m_handleRight->setPos (m_handleRight->x(),
                         m_handleLeft->y());

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveBR (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleBL->moveBy (0,
                      newPos.y() - oldPos.y());
  m_handleTR->moveBy (newPos.x() - oldPos.x(),
                      0);

  m_handleBottom->setPos ((m_handleBL->x() + m_handleBR->x()) / 2.0,
                          m_handleBR->y());
  m_handleRight->setPos (m_handleBR->x(),
                         (m_handleBR->y() + m_handleTR->y()) / 2.0);

  m_handleLeft->setPos (m_handleLeft->x(),
                        m_handleRight->y());
  m_handleTop->setPos (m_handleBottom->x(),
                       m_handleTop->y());

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveBottom (const QPointF &newPos,
                           const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleBL->moveBy (0,
                      newPos.y() - oldPos.y());
  m_handleBR->moveBy (0,
                      newPos.y() - oldPos.y());

  m_handleLeft->setPos (m_handleLeft->x(),
                        (m_handleTL->y() + m_handleBL->y()) / 2.0);
  m_handleRight->setPos (m_handleRight->x(),
                         (m_handleTR->y() + m_handleBR->y()) / 2.0);

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveLeft (const QPointF &newPos,
                         const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleTL->moveBy (newPos.x() - oldPos.x(),
                      0);
  m_handleBL->moveBy (newPos.x() - oldPos.x(),
                      0);

  m_handleTop->setPos ((m_handleTL->x() + m_handleTR->x()) / 2.0,
                       m_handleTop->y());
  m_handleBottom->setPos ((m_handleBL->x() + m_handleBR->x()) / 2.0,
                          m_handleBottom->y());

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveRight (const QPointF &newPos,
                          const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleTR->moveBy (newPos.x() - oldPos.x(),
                      0);
  m_handleBR->moveBy (newPos.x() - oldPos.x(),
                      0);

  m_handleTop->setPos ((m_handleTL->x() + m_handleTR->x()) / 2.0,
                       m_handleTop->y());
  m_handleBottom->setPos ((m_handleBL->x() + m_handleBR->x()) / 2.0,
                          m_handleBottom->y());

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveTL (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleBL->moveBy (newPos.x() - oldPos.x(),
                      0);
  m_handleTR->moveBy (0,
                      newPos.y() - oldPos.y());

  m_handleLeft->setPos (m_handleTL->x(),
                        (m_handleTL->y() + m_handleBL->y()) / 2.0);
  m_handleTop->setPos ((m_handleTL->x() + m_handleTR->x()) / 2.0,
                       m_handleTL->y());

  m_handleRight->setPos (m_handleRight->x(),
                         m_handleLeft->y());
  m_handleBottom->setPos (m_handleTop->x(),
                          m_handleBottom->y());

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveTop (const QPointF &newPos,
                        const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleTL->moveBy (0,
                      newPos.y() - oldPos.y());
  m_handleTR->moveBy (0,
                      newPos.y() - oldPos.y());

  m_handleLeft->setPos (m_handleLeft->x(),
                        (m_handleTL->y() + m_handleBL->y()) / 2.0);
  m_handleRight->setPos (m_handleRight->x(),
                         (m_handleTR->y() + m_handleBR->y()) / 2.0);

  enableEventsWhileMovingAutomatically();
}

void PdfFrame::moveTR (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  m_handleTL->moveBy (0,
                      newPos.y() - oldPos.y());
  m_handleBR->moveBy (newPos.x() - oldPos.x(),
                      0);

  m_handleTop->setPos ((m_handleTL->x() + m_handleTR->x()) / 2.0,
                       m_handleTR->y());
  m_handleRight->setPos (newPos.x() - oldPos.x(),
                         (m_handleTR->y() + m_handleBR->y()) / 2.0);

  m_handleLeft->setPos (m_handleLeft->x(),
                        m_handleRight->y());
  m_handleBottom->setPos (m_handleTop->x(),
                          m_handleBottom->y());

  enableEventsWhileMovingAutomatically();
}
