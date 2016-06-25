/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PdfFrame.h"
#include "PdfFrameHandle.h"
#include <QGraphicsScene>
#include <QRect>

PdfFrame::PdfFrame (QGraphicsScene &scene,
                    const QRectF &imageRect)
{
  const double MARGIN_PERCENT = 10.0;

  double marginHor = imageRect.width()  * MARGIN_PERCENT / 100.0;
  double marginVer = imageRect.height() * MARGIN_PERCENT / 100.0;

  QRectF box (imageRect.left() + marginHor,
              imageRect.top()  + marginVer,
              imageRect.width() - 2 * marginHor,
              imageRect.height() - 2 * marginVer);
  QPointF topCenter    = (box.topLeft()     + box.topRight()   ) / 2.0;
  QPointF rightCenter  = (box.topRight()    + box.bottomRight()) / 2.0;
  QPointF bottomCenter = (box.bottomRight() + box.bottomLeft() ) / 2.0;
  QPointF leftCenter   = (box.bottomLeft()  + box.topLeft()    ) / 2.0;

  m_handleTL     = new PdfFrameHandle (scene, imageRect, box.topLeft()    , PDF_FRAME_RIGHT  | PDF_FRAME_UNDER  , *this);
  m_handleTop    = new PdfFrameHandle (scene, imageRect, topCenter        , PDF_FRAME_CENTER | PDF_FRAME_UNDER  , *this);
  m_handleTR     = new PdfFrameHandle (scene, imageRect, box.topRight()   , PDF_FRAME_LEFT   | PDF_FRAME_UNDER  , *this);
  m_handleRight  = new PdfFrameHandle (scene, imageRect, rightCenter      , PDF_FRAME_LEFT   | PDF_FRAME_MIDDLE , *this);
  m_handleBR     = new PdfFrameHandle (scene, imageRect, box.bottomRight(), PDF_FRAME_LEFT   | PDF_FRAME_ABOVE  , *this);
  m_handleBottom = new PdfFrameHandle (scene, imageRect, bottomCenter     , PDF_FRAME_CENTER | PDF_FRAME_ABOVE  , *this);
  m_handleBL     = new PdfFrameHandle (scene, imageRect, box.bottomLeft() , PDF_FRAME_RIGHT  | PDF_FRAME_ABOVE  , *this);
  m_handleLeft   = new PdfFrameHandle (scene, imageRect, leftCenter       , PDF_FRAME_RIGHT  | PDF_FRAME_MIDDLE , *this);
}
