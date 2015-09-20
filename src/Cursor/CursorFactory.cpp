#include "CursorFactory.h"
#include "CursorSize.h"
#include "DocumentModelDigitizeCurve.h"
#include <QBitmap>
#include <QPainter>
#include <QPixmap>

CursorFactory::CursorFactory()
{
}

QCursor CursorFactory::generate (const DocumentModelDigitizeCurve &modelDigitizeCurve) const
{
  // To prevent hideous drawing errors when the line is thicker, we
  // leave a padding region around the outside equal in size to the line width
  int innerRadius = modelDigitizeCurve.cursorInnerRadius();
  int size = CursorSizeToPixels (modelDigitizeCurve.cursorSize());
  int halfSize = size / 2;
  int lineWidth = modelDigitizeCurve.cursorLineWidth();
  int halfLineWidth = lineWidth / 2;

  if (modelDigitizeCurve.cursorStandardCross()) {

    // Standard cursor
    return QCursor (Qt::CrossCursor);

  } else {

    // Custom cursor
    const int BACKGROUND_COLOR = Qt::white, FOREGROUND_COLOR = Qt::black;

    // Cursor is created with pic image (which has nontrivial pen) masked by picMask image
    // (which has single color pen)
    QPixmap picMask (size,
                     size);
    QPainter picMaskPaint (&picMask);
    picMask.fill (QColor (BACKGROUND_COLOR));

    QPen pen (QBrush (FOREGROUND_COLOR),
              modelDigitizeCurve.cursorLineWidth());
    picMaskPaint.setPen (pen);

    picMaskPaint.drawLine (QPointF (halfSize,
                                    halfSize - innerRadius - halfLineWidth),
                           QPointF (halfSize,
                                    lineWidth)); // Up
    picMaskPaint.drawLine (QPointF (halfSize - innerRadius - halfLineWidth,
                                    halfSize),
                           QPointF (lineWidth,
                                    halfSize)); // Left
    picMaskPaint.drawLine (QPointF (halfSize,
                                    halfSize + innerRadius + halfLineWidth),
                           QPointF (halfSize,
                                    size - 1 - lineWidth)); // Down
    picMaskPaint.drawLine (QPointF (halfSize + innerRadius + halfLineWidth,
                                    halfSize),
                           QPointF (size - 1 - lineWidth,
                                    halfSize)); // Right

    QPixmap pic (size,
                 size);
    pic.fill (QColor (FOREGROUND_COLOR));

    return QCursor (pic.createMaskFromColor(QColor (BACKGROUND_COLOR)),
                  picMask.createMaskFromColor(QColor (BACKGROUND_COLOR)));
  }
}
