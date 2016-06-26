/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "PdfFrame.h"
#include "PdfFrameHandle.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QRect>
#include "QtToString.h"
#include "ViewPreview.h"

const int Z_BOX = 50; // Under box and over background image
const int Z_HANDLE = 100; // Over box and background image

PdfFrame::PdfFrame (QGraphicsScene &scene,
                    ViewPreview &view) :
  m_view (view)
{
  createWidgets (scene);
}

void PdfFrame::createWidgets(QGraphicsScene &scene)
{
  const double MARGIN_PERCENT = 5.0;
  const int ZERO_WIDTH_IS_ALWAYS_VISIBLE = 0;

  int marginHor = scene.width()  * MARGIN_PERCENT / 100.0;
  int marginVer = scene.height() * MARGIN_PERCENT / 100.0;

  QRect box (scene.sceneRect().left() + marginHor,
             scene.sceneRect().top()  + marginVer,
             scene.sceneRect().width() - 2 * marginHor,
             scene.sceneRect().height() - 2 * marginVer);

  m_handleTL     = new PdfFrameHandle (scene, m_view, box.topLeft()    , PDF_FRAME_LEFT   | PDF_FRAME_TOP    , *this, Z_HANDLE);
  m_handleTR     = new PdfFrameHandle (scene, m_view, box.topRight()   , PDF_FRAME_RIGHT  | PDF_FRAME_TOP    , *this, Z_HANDLE);
  m_handleBR     = new PdfFrameHandle (scene, m_view, box.bottomRight(), PDF_FRAME_RIGHT  | PDF_FRAME_BOTTOM , *this, Z_HANDLE);
  m_handleBL     = new PdfFrameHandle (scene, m_view, box.bottomLeft() , PDF_FRAME_LEFT   | PDF_FRAME_BOTTOM , *this, Z_HANDLE);

  m_box = new QGraphicsRectItem;
  m_box->setZValue (Z_BOX);
  m_box->setPen (QPen (QBrush (Qt::gray), ZERO_WIDTH_IS_ALWAYS_VISIBLE));
  scene.addItem (m_box);

  updateBox ();
}

void PdfFrame::disableEventsWhileMovingAutomatically ()
{
  m_handleTL->setDisableEventsWhileMovingAutomatically (true);
  m_handleTR->setDisableEventsWhileMovingAutomatically (true);
  m_handleBR->setDisableEventsWhileMovingAutomatically (true);
  m_handleBL->setDisableEventsWhileMovingAutomatically (true);
}

void PdfFrame::enableEventsWhileMovingAutomatically ()
{
  m_handleTL->setDisableEventsWhileMovingAutomatically (false);
  m_handleTR->setDisableEventsWhileMovingAutomatically (false);
  m_handleBR->setDisableEventsWhileMovingAutomatically (false);
  m_handleBL->setDisableEventsWhileMovingAutomatically (false);
}

QRectF PdfFrame::frameRect () const
{
  // The x(), y(), pos(), rect() and boundingRect() will return coordinates assuming origin at the initial position of
  // each handle. So to get the coordinates in the window reference frame it takes a two step process like
  // QGraphicsRectItem::mapRectToScene (QGraphicsRectItem::rect())

  QRectF rectTL = m_handleTL->mapRectToScene (m_handleTL->boundingRect());
  QRectF rectBR = m_handleBR->mapRectToScene (m_handleBR->boundingRect());

  QRectF rectUnited = rectTL.united (rectBR);

  return rectUnited;
}

void PdfFrame::moveBL (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  double deltaX = newPos.x() - oldPos.x();
  double deltaY = newPos.y() - oldPos.y();

  m_handleTL->moveBy (deltaX,
                      0);
  m_handleBR->moveBy (0,
                      deltaY);

  enableEventsWhileMovingAutomatically();

  updateBox();
}

void PdfFrame::moveBR (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  double deltaX = newPos.x() - oldPos.x();
  double deltaY = newPos.y() - oldPos.y();

  m_handleBL->moveBy (0,
                      deltaY);
  m_handleTR->moveBy (deltaX,
                      0);

  enableEventsWhileMovingAutomatically();

  updateBox();
}

void PdfFrame::moveTL (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  double deltaX = newPos.x() - oldPos.x();
  double deltaY = newPos.y() - oldPos.y();

  m_handleBL->moveBy (deltaX,
                      0);
  m_handleTR->moveBy (0,
                      deltaY);

  enableEventsWhileMovingAutomatically();

  updateBox();
}

void PdfFrame::moveTR (const QPointF &newPos,
                       const QPointF &oldPos)
{
  disableEventsWhileMovingAutomatically();

  double deltaX = newPos.x() - oldPos.x();
  double deltaY = newPos.y() - oldPos.y();

  m_handleTL->moveBy (0,
                      deltaY);
  m_handleBR->moveBy (deltaX,
                      0);

  enableEventsWhileMovingAutomatically();

  updateBox();
}

void PdfFrame::updateBox ()
{
  QRectF rectUnited = frameRect ();

  // Adjust by one pixel in both horizontal and vertical directions so bottom/right handles end on the box
  rectUnited.setWidth (rectUnited.width () - 1);
  rectUnited.setHeight (rectUnited.height () - 1);

  m_box->setRect (rectUnited);
}

QSize PdfFrame::windowSize () const
{
  return QSize (m_view.scene()->width(),
                m_view.scene()->height());
}
