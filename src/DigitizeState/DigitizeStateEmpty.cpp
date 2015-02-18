#include "DigitizeStateEmpty.h"
#include "DigitizeStateContext.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>

DigitizeStateEmpty::DigitizeStateEmpty (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateEmpty::~DigitizeStateEmpty ()
{
}

QString DigitizeStateEmpty::activeCurve () const
{
  return "";
}

void DigitizeStateEmpty::begin (DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::begin";

  setCursor();
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateEmpty::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEmpty::cursor";

  return QCursor (Qt::ArrowCursor);
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
