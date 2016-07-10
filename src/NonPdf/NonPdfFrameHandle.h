/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef NON_PDF_FRAME_HANDLE_H
#define NON_PDF_FRAME_HANDLE_H

#include <QGraphicsRectItem>

class NonPdfCropping;
class QGraphicsScene;
class QGraphicsView;
class QPointF;
class QRectF;

/// This class acts as a single handle for the NonPdfCropping class
class NonPdfFrameHandle : public QGraphicsRectItem
{
public:
  /// Single constructor
  NonPdfFrameHandle(QGraphicsScene &scene,
                    QGraphicsView &view,
                    const QPointF &pointReference,
                    int orientationFlags,
                    NonPdfCropping &nonPdfCropping,
                    int zValue);

  /// Intercept the drags and process them, which is the whole point of handles
  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  /// Override the paint method so the dashed-border-when-selected can be removed
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /// Temporarily disable event handling so code can move this object without triggering a cascade of events
  void setDisableEventsWhileMovingAutomatically (bool disable);

private:
  NonPdfFrameHandle();

  NonPdfCropping &m_nonPdfCropping;
  int m_orientationFlags; // From PdfCropping constants

  bool m_disableEventsWhileMovingAutomatically;
  QGraphicsScene &m_scene;
  QGraphicsView &m_view;
};

#endif // NON_PDF_FRAME_HANDLE_H
