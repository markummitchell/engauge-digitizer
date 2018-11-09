/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef NON_PDF_CROPPING_H
#define NON_PDF_CROPPING_H

#include <QRect>
#include <QSize>

class NonPdfFrameHandle;
class QGraphicsRectItem;
class QGraphicsScene;
class QPointF;
class ViewPreview;

/// This class shows a frame around the selected portion of the import preview window
///
/// This class was developed as a non-pdf equivalent to the PdfCropping class. See that class for more details
class NonPdfCropping
{
public:
  /// Single constructor
  NonPdfCropping(QGraphicsScene &scene,
                 ViewPreview &view);
  ~NonPdfCropping();

  /// Frame rectangle selected by user
  QRectF frameRect () const;

  /// Bottom left corner handle was moved
  void moveBL (const QPointF &newPos,
               const QPointF &oldPos);

  /// Bottom right corner handle was moved
  void moveBR (const QPointF &newPos,
               const QPointF &oldPos);

  /// Top left corner handle was moved
  void moveTL (const QPointF &newPos,
               const QPointF &oldPos);

  /// Top right corner handle was moved
  void moveTR (const QPointF &newPos,
               const QPointF &oldPos);

  static const int NON_PDF_CROPPING_BOTTOM = 1; ///< Bit flag when handle is aligned with bottom edge at reference point
  static const int NON_PDF_CROPPING_LEFT   = 2; ///< Bit flag when handle is aligned with left edge at reference point
  static const int NON_PDF_CROPPING_RIGHT  = 4; ///< Bit flag when handle is aligned with right edge at reference point
  static const int NON_PDF_CROPPING_TOP    = 8; ///< Bit flag when handle is aligned with top edge at reference point

  /// Size of window in scene coordinates
  QSize windowSize () const;

private:
  NonPdfCropping ();

  void createWidgets (QGraphicsScene &scene);
  void disableEventsWhileMovingAutomatically();
  void enableEventsWhileMovingAutomatically();
  QRectF rectFromTLAndBR () const;
  void updateBox();

  ViewPreview &m_view;

  // Box
  QGraphicsRectItem *m_box;

  // Handles
  NonPdfFrameHandle *m_handleTL;
  NonPdfFrameHandle *m_handleTR;
  NonPdfFrameHandle *m_handleBR;
  NonPdfFrameHandle *m_handleBL;

};

#endif // NON_PDF_CROPPING_H
