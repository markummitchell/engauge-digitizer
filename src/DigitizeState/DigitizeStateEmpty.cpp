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

void DigitizeStateEmpty::handleCurveChange()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleCurveChange";
}

void DigitizeStateEmpty::handleKeyPress (Qt::Key key,
                                         bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateEmpty::handleMouseMove (QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEmpty::handleMouseMove";
}

void DigitizeStateEmpty::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleMousePress";
}

void DigitizeStateEmpty::handleMouseRelease (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleMouseRelease";
}

QString DigitizeStateEmpty::state() const
{
  return "DigitizeStateEmpty";
}

void DigitizeStateEmpty::updateModelDigitizeCurve (const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::updateModelDigitizeCurve";
}

void DigitizeStateEmpty::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::updateModelSegments";
}
