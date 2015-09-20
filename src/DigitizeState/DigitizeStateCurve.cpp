#include "CmdAddPointGraph.h"
#include "CmdMediator.h"
#include "CursorFactory.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateCurve.h"
#include "Logger.h"
#include "MainWindow.h"
#include "OrdinalGenerator.h"
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

void DigitizeStateCurve::begin (DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateCurve::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateCurve::cursor";

  CursorFactory cursorFactory;
  QCursor cursor = cursorFactory.generate (context().cmdMediator().document().modelDigitizeCurve());

  return cursor;
}

void DigitizeStateCurve::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::end";
}

void DigitizeStateCurve::handleCurveChange()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleCurveChange";
}

void DigitizeStateCurve::handleKeyPress (Qt::Key key,
                                         bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateCurve::handleMouseMove (QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateCurve::handleMouseMove";
}

void DigitizeStateCurve::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleMousePress";
}

void DigitizeStateCurve::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::handleMouseRelease";

  // Create command to add point
  OrdinalGenerator ordinalGenerator;
  Document &document = context ().cmdMediator ().document ();
  const Transformation &transformation = context ().mainWindow ().transformation();
  QUndoCommand *cmd = new CmdAddPointGraph (context ().mainWindow(),
                                            document,
                                            context ().mainWindow().selectedGraphCurve(),
                                            posScreen,
                                            ordinalGenerator.generateCurvePointOrdinal(document,
                                                                                       transformation,
                                                                                       posScreen,
                                                                                       activeCurve ()));
  context().appendNewCmd(cmd);
}

QString DigitizeStateCurve::state() const
{
  return "DigitizeStateCurve";
}

void DigitizeStateCurve::updateModelDigitizeCurve (const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::updateModelDigitizeCurve";

  setCursor();
}

void DigitizeStateCurve::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateCurve::updateModelSegments";
}
