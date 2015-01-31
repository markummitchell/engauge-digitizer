#include "DigitizeStateContext.h"
#include "DigitizeStateEyeDropper.h"
#include "Logger.h"
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

Qt::CursorShape DigitizeStateEyeDropper::cursorShape() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEyeDropper::cursorShape";

  return Qt::BitmapCursor;
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
