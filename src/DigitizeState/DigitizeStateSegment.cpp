#include "DigitizeStateContext.h"
#include "DigitizeStateSegment.h"
#include "Logger.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>

DigitizeStateSegment::DigitizeStateSegment (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateSegment::~DigitizeStateSegment ()
{
}

void DigitizeStateSegment::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
}

Qt::CursorShape DigitizeStateSegment::cursorShape() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSegment::cursorShape";

  return Qt::ArrowCursor;
}

void DigitizeStateSegment::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::end";
}

void DigitizeStateSegment::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateSegment::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleMousePress";
}

void DigitizeStateSegment::handleMouseRelease (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleMouseRelease";
}
