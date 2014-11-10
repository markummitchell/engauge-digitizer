#include "CmdAddPointGraph.h"
#include "CmdMediator.h"
#include "DigitizeStateContext.h"
#include "DigitizeStatePointMatch.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QImage>

DigitizeStatePointMatch::DigitizeStatePointMatch (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStatePointMatch::~DigitizeStatePointMatch ()
{
}

void DigitizeStatePointMatch::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
}

Qt::CursorShape DigitizeStatePointMatch::cursorShape() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::cursorShape";

  return Qt::CrossCursor;
}

void DigitizeStatePointMatch::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::end";
}

void DigitizeStatePointMatch::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStatePointMatch::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMousePress";
}

void DigitizeStatePointMatch::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseRelease";

  QUndoCommand *cmd = new CmdAddPointGraph (context ().mainWindow(),
                                            context ().cmdMediator ().document (),
                                            context ().mainWindow().selectedCurrentCurve(),
                                            posScreen);
  context().appendNewCmd(cmd);
}
