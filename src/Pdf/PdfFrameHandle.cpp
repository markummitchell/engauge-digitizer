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
  m_orientationFlags (orientationFlags)
{
  const double SUBTLE_OPACITY = 0.2;

  // Fill with nice color for better visibility
  setBrush (QBrush (Qt::blue));
  setFlags (ItemIsMovable | ItemIsSelectable | ItemSendsScenePositionChanges);
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
  } else if ((orientationFlags & PdfFrame::PDF_FRAME_UNDER) != 0) {
    topLeft.setY (topLeft.y() - handleSizeVer);
  }

  setRect (QRectF (topLeft,
                   QSizeF (handleSizeHor, handleSizeVer)));
}

QVariant PdfFrameHandle::itemChange (GraphicsItemChange change,
                                     const QVariant &value)
{
  if (change == ItemPositionChange && scene()) {

    // value is the new position.
    QPointF newPos = value.toPointF();
    QRectF rect = scene()->sceneRect();

    if (!rect.contains(newPos)) {

      // Keep the item inside the scene rect.
      newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
      newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));

      return newPos;
    }
  }

  return QGraphicsItem::itemChange(change, value);
}
