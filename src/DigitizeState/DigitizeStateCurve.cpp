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

DigitizeStateCurve::DigitizeStateCurve(DigitizeStateContext &context)
    : DigitizeStateAbstractBase(context) {}

DigitizeStateCurve::~DigitizeStateCurve() {}

QString DigitizeStateCurve::activeCurve() const {
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateCurve::begin(CmdMediator *cmdMediator,
                               DigitizeState /* previousState */) {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve());
}

QCursor DigitizeStateCurve::cursor(CmdMediator *cmdMediator) const {
  LOG4CPP_DEBUG_S((*mainCat)) << "DigitizeStateCurve::cursor";

  CursorFactory cursorFactory;
  QCursor cursor =
      cursorFactory.generate(cmdMediator->document().modelDigitizeCurve());

  return cursor;
}

void DigitizeStateCurve::end() {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::end";
}

void DigitizeStateCurve::handleCurveChange(CmdMediator * /* cmdMediator */) {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::handleCurveChange";
}

void DigitizeStateCurve::handleKeyPress(CmdMediator * /* cmdMediator */,
                                        Qt::Key key,
                                        bool /* atLeastOneSelectedItem */) {
  LOG4CPP_INFO_S((*mainCat))
      << "DigitizeStateCurve::handleKeyPress"
      << " key=" << QKeySequence(key).toString().toLatin1().data();
}

void DigitizeStateCurve::handleMouseMove(CmdMediator * /* cmdMediator */,
                                         QPointF /* posScreen */) {
  //  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateCurve::handleMouseMove";
}

void DigitizeStateCurve::handleMousePress(CmdMediator * /* cmdMediator */,
                                          QPointF /* posScreen */) {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::handleMousePress";
}

void DigitizeStateCurve::handleMouseRelease(CmdMediator *cmdMediator,
                                            QPointF posScreen) {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::handleMouseRelease";

  // Create command to add point
  OrdinalGenerator ordinalGenerator;
  Document &document = cmdMediator->document();
  const Transformation &transformation =
      context().mainWindow().transformation();
  QUndoCommand *cmd = new CmdAddPointGraph(
      context().mainWindow(), document,
      context().mainWindow().selectedGraphCurve(), posScreen,
      ordinalGenerator.generateCurvePointOrdinal(document, transformation,
                                                 posScreen, activeCurve()));
  context().appendNewCmd(cmdMediator, cmd);
}

QString DigitizeStateCurve::state() const { return "DigitizeStateCurve"; }

void DigitizeStateCurve::updateModelDigitizeCurve(
    CmdMediator *cmdMediator,
    const DocumentModelDigitizeCurve & /*modelDigitizeCurve */) {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::updateModelDigitizeCurve";

  setCursor(cmdMediator);
}

void DigitizeStateCurve::updateModelSegments(
    const DocumentModelSegments & /* modelSegments */) {
  LOG4CPP_INFO_S((*mainCat)) << "DigitizeStateCurve::updateModelSegments";
}
