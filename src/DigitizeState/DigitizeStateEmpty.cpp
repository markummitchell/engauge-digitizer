#include "DigitizeStateEmpty.h"
#include "DigitizeStateContext.h"
#include <QCursor>
#include "Logger.h"

DigitizeStateEmpty::DigitizeStateEmpty (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateEmpty::~DigitizeStateEmpty ()
{
}

void DigitizeStateEmpty::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::begin";

  setCursor();
}

Qt::CursorShape DigitizeStateEmpty::cursorShape() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEmpty::cursorShape";

  return Qt::ArrowCursor;
}

void DigitizeStateEmpty::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::end";
}

void DigitizeStateEmpty::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateEmpty::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleMousePress";
}

void DigitizeStateEmpty::handleMouseRelease (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleMouseRelease";
}
