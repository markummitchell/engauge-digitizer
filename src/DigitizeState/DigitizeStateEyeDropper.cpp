#include "DigitizeStateContext.h"
#include "DigitizeStateEyeDropper.h"
#include "Logger.h"
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>

DigitizeStateEyeDropper::DigitizeStateEyeDropper (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateEyeDropper::~DigitizeStateEyeDropper ()
{
}

void DigitizeStateEyeDropper::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEyeDropper::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
}

QCursor DigitizeStateEyeDropper::cursor() const
{
  const int HOT_X_IN_BITMAP = 8;
  const int HOT_Y_IN_BITMAP = 24;
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEyeDropper::cursor";

  QBitmap bitmap (":/engauge/img/cursor_eyedropper.xpm");
  QBitmap bitmapMask (":/engauge/img/cursor_eyedropper_mask.xpm");
  return QCursor (bitmap,
                  bitmapMask,
                  HOT_X_IN_BITMAP,
                  HOT_Y_IN_BITMAP);
}

void DigitizeStateEyeDropper::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEyeDropper::end";
}

void DigitizeStateEyeDropper::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEyeDropper::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateEyeDropper::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEyeDropper::handleMousePress";
}

void DigitizeStateEyeDropper::handleMouseRelease (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEyeDropper::handleMouseRelease";
}
