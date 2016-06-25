/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef PDF_FRAME_H
#define PDF_FRAME_H

class PdfFrameHandle;
class QGraphicsScene;
class QRectF;

/// This class shows a frame around the selected portion of the pdf import preview window
class PdfFrame
{
public:
  /// Single constructor
  PdfFrame(QGraphicsScene &scene,
           const QRectF &imageRect);

  static const int PDF_FRAME_ABOVE  = 1; ///< Bit flag when handle is aligned with bottom edge at reference point
  static const int PDF_FRAME_CENTER = 2; ///< Bit flag when handle is aligned horizontally with reference point
  static const int PDF_FRAME_LEFT   = 4; ///< Bit flag when handle is aligned with right edge at reference point
  static const int PDF_FRAME_MIDDLE = 8; ///< Bit flag when handle is aligned vertically with reference point
  static const int PDF_FRAME_RIGHT  = 16; ///< Bit flag when handle is aligned with left edge at reference point
  static const int PDF_FRAME_UNDER  = 32; ///< Bit flag when handle is aligned with top edge at reference point

private:
  PdfFrame();

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
