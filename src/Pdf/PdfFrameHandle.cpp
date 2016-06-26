/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PdfFrame.h"
#include "PdfFrameHandle.h"
#include <QBrush>
#include <QGraphicsScene>

const double HANDLE_SIZE_AS_FRACTION_OF_WINDOW_SIZE = 30;

PdfFrameHandle::PdfFrameHandle (QGraphicsScene &scene,
                                const QPointF &pointReference,
                                int orientationFlags,
                                PdfFrame &pdfFrame,
                                int zValue) :
  m_pdfFrame (pdfFrame),
  m_orientationFlags (orientationFlags),
  m_disableEventsWhileMovingAutomatically (false),
  m_scene (scene)
{
  const double SUBTLE_OPACITY = 0.2;

  // Advantages of using ItemIgnoresTransformations:
  //   1) handles do not get bigger or smaller depending on the size of the image
  //   2) handles never get ugly when zoomed in
  //   3) handles never get too tiny when zoomed out
  // Disadvantages of using ItemIgnoresTransformation:
  //   1) Resizing the preview window with ItemIgnoresTransformations moves the handles out of position
  //   2) More conversions back and forth between untransformed and transformed coordinates. This was the deal breaker since
  //      the transformations were undocumented and ultimately too difficult
  // The solution is to have constant-size handles WITHOUT ItemIgnoresTransformations. This means resizing the window
  // also involves resizing the handles, but everything else is pretty easy
  //
  // ItemIgnoresTransformations flag must agree with the QGraphicsRectItem used for the frame box by PdfFrame
  setFlags (QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemSendsScenePositionChanges);

  // Fill with nice color for better visibility
  setBrush (QBrush (Qt::blue));
  setVisible (true);
  setZValue (zValue);
  setOpacity (SUBTLE_OPACITY);
  setPos (pointReference);

  // Add to scene
  scene.addItem (this);

  updateAfterResize();
}

QVariant PdfFrameHandle::itemChange (GraphicsItemChange change,
                                     const QVariant &value)
{
  QVariant valueFiltered = value;

  if (change == ItemPositionChange && scene()) {

    QPointF sizeAsPointF (boundingRect().size().width(),
                          boundingRect().size().height());

    // New position is in the value argument
    QPointF newPosTL = valueFiltered.toPointF();
    QPointF newPosBR = newPosTL + sizeAsPointF;
    QPointF oldPos = pos ();

    // Skip moving of this handle if it will go outside of the window
    QRectF rectWindow = m_scene.sceneRect();
    if (!rectWindow.contains (newPosTL)) {

      // Keep the item inside the scene rectangle
      newPosTL.setX (qMin (rectWindow.right(), qMax (newPosTL.x(), rectWindow.left())));
      newPosTL.setY (qMin (rectWindow.bottom(), qMax (newPosTL.y(), rectWindow.top())));

      valueFiltered = newPosTL;
    } else if (!rectWindow.contains (newPosBR)) {

      // Keep the item inside the scene rectangle
      newPosBR.setX (qMin (rectWindow.right(), qMax (newPosBR.x(), rectWindow.left())));
      newPosBR.setY (qMin (rectWindow.bottom(), qMax (newPosBR.y(), rectWindow.top())));

      valueFiltered = newPosBR - sizeAsPointF;
    }

    // Skip moving of other handles, in response to the move of this handle, if event handling is (temporarily) off,
    // to prevent an infinite loop
    if (!m_disableEventsWhileMovingAutomatically) {

      bool left   = ((m_orientationFlags & PdfFrame::PDF_FRAME_LEFT  ) != 0);
      bool right  = ((m_orientationFlags & PdfFrame::PDF_FRAME_RIGHT ) != 0);
      bool top    = ((m_orientationFlags & PdfFrame::PDF_FRAME_TOP   ) != 0);
      bool bottom = ((m_orientationFlags & PdfFrame::PDF_FRAME_BOTTOM) != 0);

      if (left && top) {
        m_pdfFrame.moveTL (newPosTL, oldPos);
      } else if (right && top) {
        m_pdfFrame.moveTR (newPosTL, oldPos);
      } else if (right && bottom) {
        m_pdfFrame.moveBR (newPosTL, oldPos);
      } else if (left && bottom) {
        m_pdfFrame.moveBL (newPosTL, oldPos);
      }
    }
  }

  return QGraphicsItem::itemChange(change, valueFiltered);
}

void PdfFrameHandle::setDisableEventsWhileMovingAutomatically (bool disable)
{
  m_disableEventsWhileMovingAutomatically = disable;
}

void PdfFrameHandle::updateAfterResize ()
{
  QSize handleSize = m_pdfFrame.windowSize() / HANDLE_SIZE_AS_FRACTION_OF_WINDOW_SIZE;

  // Start with geometry
  QPointF topLeft = pos();

  setRect (QRectF (topLeft,
                   handleSize));
}
