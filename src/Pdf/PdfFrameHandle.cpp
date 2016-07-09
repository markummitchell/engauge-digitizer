/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PdfCropping.h"
#include "PdfFrameHandle.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStyleOptionGraphicsItem>

const double HANDLE_SIZE_AS_FRACTION_OF_WINDOW_SIZE = 30;

PdfFrameHandle::PdfFrameHandle (QGraphicsScene &scene,
                                QGraphicsView &view,
                                const QPointF &pointReference,
                                int orientationFlags,
                                PdfCropping &pdfCropping,
                                int zValue) :
  m_pdfCropping (pdfCropping),
  m_orientationFlags (orientationFlags),
  m_disableEventsWhileMovingAutomatically (false),
  m_scene (scene),
  m_view (view)
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
  // ItemIgnoresTransformations flag must agree with the QGraphicsRectItem used for the frame box by PdfCropping
  setFlags (QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemSendsScenePositionChanges);

  // Fill with nice color for better visibility. Note that the pen is disabled by overriding the paint method
  setBrush (QBrush (Qt::blue));
  setVisible (true);
  setZValue (zValue);
  setOpacity (SUBTLE_OPACITY);
  setPos (pointReference); // Point position is handled in scene/view coordinates

  // Add to scene
  scene.addItem (this);

  QSize handleSize = m_pdfCropping.windowSize() / HANDLE_SIZE_AS_FRACTION_OF_WINDOW_SIZE;

  // Adjust positions of handles that are not at the top left so handles are laid out symmetrically
  QPointF pointPos = pointReference;
  if ((orientationFlags && PdfCropping::PDF_CROPPING_LEFT) != 0) {
    pointPos.setX (pointPos.x() - handleSize.width() / 2.0);
  } else if ((orientationFlags && PdfCropping::PDF_CROPPING_RIGHT) != 0) {
    pointPos.setX (pointPos.x() + handleSize.width() / 2.0);
  }
  if ((orientationFlags && PdfCropping::PDF_CROPPING_TOP) != 0) {
    pointPos.setY (pointPos.y() - handleSize.height() / 2.0);
  } else if ((orientationFlags && PdfCropping::PDF_CROPPING_BOTTOM) != 0) {
    pointPos.setY (pointPos.y() + handleSize.height() / 2.0);
  }

  // Start with geometry. Since point positions are handled in scene/view coordinates, we have to convert
  // to local coordinates for the rectangle
  QPointF topLeftLocal = mapFromScene (pointPos);

  setRect (QRectF (topLeftLocal,
                   handleSize));
}

QVariant PdfFrameHandle::itemChange (GraphicsItemChange change,
                                     const QVariant &value)
{
  QVariant valueFiltered = value;

  if (change == ItemPositionChange && scene()) {

    QPointF sizeAsPointF (boundingRect().size().width(),
                          boundingRect().size().height());

    // New position is in the value argument
    QPointF newPos = valueFiltered.toPointF();
    QPointF oldPos = pos ();

    // This sequence is from http://www.qtcentre.org/threads/47248-How-to-efficiently-get-position-of-a-QGraphicsItem-in-view-coordinates
    QRectF newRectItem (newPos,
                        QSize (boundingRect().size().width(),
                               boundingRect().size().height()));
    QPolygonF newRectScene = mapToScene (newRectItem);
    QPolygon newRectView = m_view.mapFromScene (newRectScene.boundingRect());

    // Skip moving of this handle if it will go outside of the window
    QRectF rectWindow = m_scene.sceneRect();
    if (!rectWindow.contains (newRectView.boundingRect())) {

      // Keep the item inside the scene rectangle
      newPos.setX (qMin (rectWindow.right(), qMax (newPos.x(), rectWindow.left())));
      newPos.setY (qMin (rectWindow.bottom(), qMax (newPos.y(), rectWindow.top())));

      valueFiltered = (newPos);

    }

    // Skip moving of other handles, in response to the move of this handle, if event handling is (temporarily) off,
    // to prevent an infinite loop
    if (!m_disableEventsWhileMovingAutomatically) {

      bool left   = ((m_orientationFlags & PdfCropping::PDF_CROPPING_LEFT  ) != 0);
      bool right  = ((m_orientationFlags & PdfCropping::PDF_CROPPING_RIGHT ) != 0);
      bool top    = ((m_orientationFlags & PdfCropping::PDF_CROPPING_TOP   ) != 0);
      bool bottom = ((m_orientationFlags & PdfCropping::PDF_CROPPING_BOTTOM) != 0);

      if (left && top) {
        m_pdfCropping.moveTL (newPos, oldPos);
      } else if (right && top) {
        m_pdfCropping.moveTR (newPos, oldPos);
      } else if (right && bottom) {
        m_pdfCropping.moveBR (newPos, oldPos);
      } else if (left && bottom) {
        m_pdfCropping.moveBL (newPos, oldPos);
      }
    }
  }

  return QGraphicsItem::itemChange(change, valueFiltered);
}

void PdfFrameHandle::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  // Temporarily remove the selected option
  QStyleOptionGraphicsItem scrubbed (*option);
  scrubbed.state &= ~QStyle::State_Selected;
  QGraphicsRectItem::paint (painter, &scrubbed, widget);
}

void PdfFrameHandle::setDisableEventsWhileMovingAutomatically (bool disable)
{
  m_disableEventsWhileMovingAutomatically = disable;
}
