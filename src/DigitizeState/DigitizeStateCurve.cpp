#include "CmdAddPointGraph.h"
#include "CmdMediator.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateCurve.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QImage>

DigitizeStateCurve::DigitizeStateCurve (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateCurve::~DigitizeStateCurve ()
{
}

QString DigitizeStateCurve::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateCurve::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewPointStyle(activeCurve ());
}

QCursor DigitizeStateCurve::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateCurve::cursor";

  return QCursor (Qt::CrossCursor);
}

void DigitizeStateCurve::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::end";
}

void DigitizeStateCurve::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateCurve::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleMousePress";
}

void DigitizeStateCurve::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleMouseRelease";

  // Create command to add point
  QUndoCommand *cmd = new CmdAddPointGraph (context ().mainWindow(),
                                            context ().cmdMediator ().document (),
                                            context ().mainWindow().selectedGraphCurve(),
                                            posScreen);
  context().appendNewCmd(cmd);
}
