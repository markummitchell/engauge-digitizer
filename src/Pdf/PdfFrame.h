/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef PDF_FRAME_H
#define PDF_FRAME_H

class PdfFrameHandle;
class QGraphicsScene;
class QPointF;
class QRectF;

/// This class shows a frame around the selected portion of the pdf import preview window
class PdfFrame
{
public:
  /// Single constructor
  PdfFrame(QGraphicsScene &scene,
           const QRectF &imageRect);

  static const int PDF_FRAME_BOTTOM = 1; ///< Bit flag when handle is aligned with bottom edge at reference point
  static const int PDF_FRAME_CENTER = 2; ///< Bit flag when handle is aligned horizontally with reference point
  static const int PDF_FRAME_LEFT   = 4; ///< Bit flag when handle is aligned with left edge at reference point
  static const int PDF_FRAME_MIDDLE = 8; ///< Bit flag when handle is aligned vertically with reference point
  static const int PDF_FRAME_RIGHT  = 16; ///< Bit flag when handle is aligned with right edge at reference point
  static const int PDF_FRAME_TOP    = 32; ///< Bit flag when handle is aligned with top edge at reference point

  /// Bottom left corner handle was moved
  void moveBL (const QPointF &newPos,
               const QPointF &oldPos);

  /// Center bottom handle was moved
  void moveBottom (const QPointF &newPos,
                   const QPointF &oldPos);

  /// Bottom right corner handle was moved
  void moveBR (const QPointF &newPos,
               const QPointF &oldPos);

  /// Left side handle was moved
  void moveLeft (const QPointF &newPos,
                 const QPointF &oldPos);

  /// Right side handle was moved
  void moveRight (const QPointF &newPos,
                  const QPointF &oldPos);

  /// Top left corner handle was moved
  void moveTL (const QPointF &newPos,
               const QPointF &oldPos);

  /// Center top handle was moved
  void moveTop (const QPointF &newPos,
                const QPointF &oldPos);

  /// Top right corner handle was moved
  void moveTR (const QPointF &newPos,
               const QPointF &oldPos);

private:
  PdfFrame();

  void disableEventsWhileMovingAutomatically();
  void enableEventsWhileMovingAutomatically();

  PdfFrameHandle *m_handleTL;
  PdfFrameHandle *m_handleTop;
  PdfFrameHandle *m_handleTR;
  PdfFrameHandle *m_handleRight;
  PdfFrameHandle *m_handleBR;
  PdfFrameHandle *m_handleBottom;
  PdfFrameHandle *m_handleBL;
  PdfFrameHandle *m_handleLeft;
};

#endif // PDF_FRAME_H
