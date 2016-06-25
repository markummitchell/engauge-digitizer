/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef PDF_FRAME_H
#define PDF_FRAME_H

#include <QRect>
#include <QSize>

class PdfFrameHandle;
class QGraphicsRectItem;
class QGraphicsScene;
class QPointF;
class ViewPreview;

/// This class shows a frame around the selected portion of the pdf import preview window
///
/// Originally there were 4 handles at the corners and 4 handles at the middles of the sides, but dragging
/// the corner handles did not result in 1/2 the movement at the middle handles. The middle handles were deemed
/// not worth the effort
class PdfFrame
{
public:
  /// Single constructor
  PdfFrame(QGraphicsScene &scene,
           ViewPreview &view);

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

  static const int PDF_FRAME_BOTTOM = 1; ///< Bit flag when handle is aligned with bottom edge at reference point
  static const int PDF_FRAME_LEFT   = 2; ///< Bit flag when handle is aligned with left edge at reference point
  static const int PDF_FRAME_RIGHT  = 4; ///< Bit flag when handle is aligned with right edge at reference point
  static const int PDF_FRAME_TOP    = 8; ///< Bit flag when handle is aligned with top edge at reference point

  /// Size of window in scene coordinates
  QSize windowSize () const;

private:
  PdfFrame();

  void createWidgets (QGraphicsScene &scene);
  void disableEventsWhileMovingAutomatically();
  void enableEventsWhileMovingAutomatically();
  QRectF rectFromTLAndBR () const;
  void updateBox();

  ViewPreview &m_view;

  // Box
  QGraphicsRectItem *m_box;

  // Handles
  PdfFrameHandle *m_handleTL;
  PdfFrameHandle *m_handleTR;
  PdfFrameHandle *m_handleBR;
  PdfFrameHandle *m_handleBL;

};

#endif // PDF_FRAME_H
