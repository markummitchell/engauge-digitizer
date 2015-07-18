#include "DigitizeStateContext.h"
#include "DigitizeStateScale.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>

DigitizeStateScale::DigitizeStateScale (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateScale::~DigitizeStateScale ()
{
}

QString DigitizeStateScale::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateScale::begin (DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateScale::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateScale::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateScale::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::end";
}

void DigitizeStateScale::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateScale::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleMousePress";
}

void DigitizeStateScale::handleMouseRelease (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleMouseRelease";
}

QString DigitizeStateScale::state() const
{
  return "DigitizeStateScale";
}
