/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PdfFrame.h"
#include "PdfFrameHandle.h"
#include <QBrush>
#include <QGraphicsScene>

const double HANDLE_SIZE_AS_PERCENT_OF_SCREEN_SIZE = 4;

PdfFrameHandle::PdfFrameHandle (QGraphicsScene &scene,
                                const QRectF &imageRect,
                                const QPointF &pointReference,
                                int orientationFlags,
                                PdfFrame &pdfFrame) :
  m_pdfFrame (pdfFrame),
  m_orientationFlags (orientationFlags),
  m_disableEventsWhileMovingAutomatically (false)
{
  const double SUBTLE_OPACITY = 0.2;

  // Fill with nice color for better visibility
  setBrush (QBrush (Qt::blue));
  setFlags (QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemSendsScenePositionChanges);
  setVisible (true);
  setZValue (100);
  setOpacity (SUBTLE_OPACITY);

  // Add to scene
  scene.addItem (this);

  // Start with geometry
  QPointF topLeft = pointReference;

  // Horizontal adjustments
  double handleSizeHor = HANDLE_SIZE_AS_PERCENT_OF_SCREEN_SIZE * imageRect.width() / 100.0;
  if ((orientationFlags & PdfFrame::PDF_FRAME_CENTER) != 0) {
    topLeft.setX (topLeft.x() - handleSizeHor / 2);
  } else if ((orientationFlags & PdfFrame::PDF_FRAME_RIGHT) != 0) {
    topLeft.setX (topLeft.x() - handleSizeHor);
  }

  // Vertical adjustments
  double handleSizeVer = HANDLE_SIZE_AS_PERCENT_OF_SCREEN_SIZE * imageRect.height() / 100.0;
  if ((orientationFlags & PdfFrame::PDF_FRAME_MIDDLE) != 0) {
    topLeft.setY (topLeft.y() - handleSizeVer / 2);
  } else if ((orientationFlags & PdfFrame::PDF_FRAME_BOTTOM) != 0) {
    topLeft.setY (topLeft.y() - handleSizeVer);
  }

  setRect (QRectF (topLeft,
                   QSizeF (handleSizeHor, handleSizeVer)));
}

QVariant PdfFrameHandle::itemChange (GraphicsItemChange change,
                                     const QVariant &value)
{
  // Skip if event handling is (temporarily) off
  if (!m_disableEventsWhileMovingAutomatically) {

    if (change == ItemPositionChange && scene()) {

      // New position is in the value argument
      QPointF newPos = value.toPointF();
      QPointF oldPos = pos ();

      bool left   = ((m_orientationFlags & PdfFrame::PDF_FRAME_LEFT  ) != 0);
      bool center = ((m_orientationFlags & PdfFrame::PDF_FRAME_CENTER) != 0);
      bool right  = ((m_orientationFlags & PdfFrame::PDF_FRAME_RIGHT ) != 0);
      bool top    = ((m_orientationFlags & PdfFrame::PDF_FRAME_TOP   ) != 0);
      bool middle = ((m_orientationFlags & PdfFrame::PDF_FRAME_MIDDLE) != 0);
      bool bottom = ((m_orientationFlags & PdfFrame::PDF_FRAME_BOTTOM) != 0);

      if (left && top) {
        m_pdfFrame.moveTL (newPos, oldPos);
      } else if (center && top) {
        m_pdfFrame.moveTop (newPos, oldPos);
      } else if (right && top) {
        m_pdfFrame.moveTR (newPos, oldPos);
      } else if (right && middle) {
        m_pdfFrame.moveRight (newPos, oldPos);
      } else if (right && bottom) {
        m_pdfFrame.moveBR (newPos, oldPos);
      } else if (center && bottom) {
        m_pdfFrame.moveBottom (newPos, oldPos);
      } else if (left && bottom) {
        m_pdfFrame.moveBL (newPos, oldPos);
      } else if (left && middle) {
        m_pdfFrame.moveLeft (newPos, oldPos);
      }
    }
  }

  return QGraphicsItem::itemChange(change, value);
}

void PdfFrameHandle::setDisableEventsWhileMovingAutomatically (bool disable)
{
  m_disableEventsWhileMovingAutomatically = disable;
}
