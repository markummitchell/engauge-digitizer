/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "NonPdfCropping.h"
#include "NonPdfFrameHandle.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <qmath.h>
#include <QRect>
#include "QtToString.h"
#include "ViewPreview.h"

const int Z_BOX = 50; // Under box and over background image
const int Z_HANDLE = 100; // Over box and background image

NonPdfCropping::NonPdfCropping (QGraphicsScene &scene,
                                ViewPreview &view) :
  m_view (view),
  m_handleTL (nullptr),
  m_handleTR (nullptr),
  m_handleBR (nullptr),
  m_handleBL (nullptr)
{
  createWidgets (scene);
}

NonPdfCropping::~NonPdfCropping ()
{
  delete m_handleTL;
  delete m_handleTR;
  delete m_handleBR;
  delete m_handleBL;
}

void NonPdfCropping::createWidgets(QGraphicsScene &scene)
{
  const double MARGIN_PERCENT = 5.0;
  const int ZERO_WIDTH_IS_ALWAYS_VISIBLE = 0;

  int marginHor = qFloor (scene.width()  * MARGIN_PERCENT / 100.0);
  int marginVer = qFloor (scene.height() * MARGIN_PERCENT / 100.0);

  QRect box (qFloor (scene.sceneRect().left() + marginHor),
             qFloor (scene.sceneRect().top()  + marginVer),
             qFloor (scene.sceneRect().width() - 2 * marginHor),
             qFloor (scene.sceneRect().height() - 2 * marginVer));

  m_handleTL = new NonPdfFrameHandle (scene, m_view, box.topLeft()    , NON_PDF_CROPPING_LEFT   | NON_PDF_CROPPING_TOP    , *this, Z_HANDLE);
  m_handleTR = new NonPdfFrameHandle (scene, m_view, box.topRight()   , NON_PDF_CROPPING_RIGHT  | NON_PDF_CROPPING_TOP    , *this, Z_HANDLE);
  m_handleBR = new NonPdfFrameHandle (scene, m_view, box.bottomRight(), NON_PDF_CROPPING_RIGHT  | NON_PDF_CROPPING_BOTTOM , *this, Z_HANDLE);
  m_handleBL = new NonPdfFrameHandle (scene, m_view, box.bottomLeft() , NON_PDF_CROPPING_LEFT   | NON_PDF_CROPPING_BOTTOM , *this, Z_HANDLE);

  m_box = new QGraphicsRectItem;
  m_box->setZValue (Z_BOX);
  m_box->setPen (QPen (QBrush (Qt::gray), ZERO_WIDTH_IS_ALWAYS_VISIBLE));
  scene.addItem (m_box);

  updateBox ();
}

void NonPdfCropping::disableEventsWhileMovingAutomatically ()
{
  m_handleTL->setDisableEventsWhileMovingAutomatically (true);
  m_handleTR->setDisableEventsWhileMovingAutomatically (true);
  m_handleBR->setDisableEventsWhileMovingAutomatically (true);
  m_handleBL->setDisableEventsWhileMovingAutomatically (true);
}

void NonPdfCropping::enableEventsWhileMovingAutomatically ()
{
  m_handleTL->setDisableEventsWhileMovingAutomatically (false);
  m_handleTR->setDisableEventsWhileMovingAutomatically (false);
  m_handleBR->setDisableEventsWhileMovingAutomatically (false);
  m_handleBL->setDisableEventsWhileMovingAutomatically (false);
}

QRectF NonPdfCropping::frameRect () const
{
  // The x(), y(), pos(), rect() and boundingRect() will return coordinates assuming origin at the initial position of
  // each handle. So to get the coordinates in the window reference frame it takes a two step process like
  // QGraphicsRectItem::mapRectToScene (QGraphicsRectItem::rect())

  QRectF rectTL = m_handleTL->mapRectToScene (m_handleTL->boundingRect());
  QRectF rectBR = m_handleBR->mapRectToScene (m_handleBR->boundingRect());

  QRectF rectUnited = rectTL.united (rectBR);

  return rectUnited;
}

void NonPdfCropping::moveBL (const QPointF &newPos,
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

void NonPdfCropping::moveBR (const QPointF &newPos,
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

void NonPdfCropping::moveTL (const QPointF &newPos,
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

void NonPdfCropping::moveTR (const QPointF &newPos,
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

void NonPdfCropping::updateBox ()
{
  QRectF rectUnited = frameRect ();

  // Adjust by one pixel in both horizontal and vertical directions so bottom/right handles end on the box
  rectUnited.setWidth (rectUnited.width () - 1);
  rectUnited.setHeight (rectUnited.height () - 1);

  m_box->setRect (rectUnited);
}

QSize NonPdfCropping::windowSize () const
{
  return QSize (qFloor (m_view.scene()->width()),
                qFloor (m_view.scene()->height()));
}
