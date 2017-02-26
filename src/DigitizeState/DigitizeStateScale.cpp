/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddScale.h"
#include "CmdMediator.h"
#include "CursorFactory.h"
#include "DigitizeStateScale.h"
#include "DigitizeStateContext.h"
#include "DlgEditScale.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PointStyle.h"
#include <QCursor>
#include <QMessageBox>
#include "ScaleBar.h"

DigitizeStateScale::DigitizeStateScale (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context),
  m_scaleBar (0),
  m_substate (SUBSTATE_NOMINAL)
{
}

DigitizeStateScale::~DigitizeStateScale ()
{
}

QString DigitizeStateScale::activeCurve () const
{
  return AXIS_CURVE_NAME;
}

void DigitizeStateScale::begin (CmdMediator *cmdMediator,
                                DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateScale::cursor(CmdMediator *cmdMediator) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateScale::cursor";

  CursorFactory cursorFactory;
  QCursor cursor = cursorFactory.generate (cmdMediator->document().modelDigitizeCurve());

  return cursor;
}

void DigitizeStateScale::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::end";
}

void DigitizeStateScale::handleContextMenuEventAxis (CmdMediator * /* cmdMediator */,
                                                     const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();
}

void DigitizeStateScale::handleContextMenuEventGraph (CmdMediator * /* cmdMediator */,
                                                      const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleContextMenuEventGraph "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();
}

void DigitizeStateScale::handleCurveChange(CmdMediator * /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleCurveChange";
}

void DigitizeStateScale::handleKeyPress (CmdMediator * /* cmdMediator */,
                                         Qt::Key key,
                                         bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateScale::handleMouseMove (CmdMediator * /* cmdMediator */,
                                          QPointF posScreen)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateScale::handleMouseMove";

  if ((m_scaleBar != 0) &&
      (m_substate == SUBSTATE_MOVING_SECOND_ENDPOINT)) {

    m_scaleBar->moveSecondEndpointDuringCreation (posScreen);
  }
}

void DigitizeStateScale::handleMousePress (CmdMediator * /* cmdMediator */,
                                           QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleMousePress";

  // Create the scale bar to give the user immediate feedback that something was created
  m_scaleBar = context().mainWindow().scene().createAndAddScaleBar (posScreen);

  // Attempts to select an endpoint right here, or after an super short timer interval
  // failed. That would have been nice for having the click create the scale bar and, while
  // the mouse was still pressed, selecting an endpoint thus allowing a single click-and-drag to
  // create the scale bar. We fall back to the less elegant solution (which the user will never
  // notice) of capturing mouse move events and using those to move an endpoint
  m_substate = SUBSTATE_MOVING_SECOND_ENDPOINT;
}

void DigitizeStateScale::handleMouseRelease (CmdMediator *cmdMediator,
                                             QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleMouseRelease";

  m_substate = SUBSTATE_NOMINAL;
//  if (context().mainWindow().transformIsDefined()) {
//
//    QMessageBox::warning (0,
//                          QObject::tr ("Engauge Digitizer"),
//                          QObject::tr ("The scale bar has been defined, and another is not needed or allowed."));
//
//  } else {
//
//    // Ask user for coordinates
//    DlgEditScale *dlg = new DlgEditScale (context ().mainWindow (),
//                                          cmdMediator->document().modelCoords(),
//                                          cmdMediator->document().modelGeneral(),
//                                          context().mainWindow().modelMainWindow(),
//                                          context().mainWindow().transformation(),
//                                          cmdMediator->document().documentAxesPointsRequired());
//    int rtn = dlg->exec ();
//
//    bool isXOnly;
//    QPointF posGraph = dlg->posGraph (isXOnly);
//    delete dlg;
//
//    // Remove temporary point
//    context().mainWindow().scene().removePoint(Point::temporaryPointIdentifier ());
//
//    if (rtn == QDialog::Accepted) {
//
//      // User wants to add this scale point, but let's perform sanity checks first
//
//      bool isError;
//      QString errorMessage;
//      int nextOrdinal = cmdMediator->document().nextOrdinalForCurve(AXIS_CURVE_NAME);
//
//      cmdMediator->document().checkAddPointAxis(posScreen,
//                                                posGraph,
//                                                isError,
//                                                errorMessage,
//                                                isXOnly);
//
//      if (isError) {
//
//        QMessageBox::warning (0,
//                              QObject::tr ("Engauge Digitizer"),
//                              errorMessage);
//
//      } else {
//
//        // Create command to add point
//        Document &document = cmdMediator->document ();
//        QUndoCommand *cmd = new CmdAddScale (context ().mainWindow(),
//                                             document,
//                                             posScreen,
//                                             posGraph,
//                                             nextOrdinal,
//                                             isXOnly);
//        context().appendNewCmd(cmdMediator,
//                               cmd);
//      }
//    }
//  }
//
//  // TODO - deallocate the scale bar here even though it lives on in the scene
//  ENGAUGE_ASSERT (m_scaleBar == 0);
}

QString DigitizeStateScale::state() const
{
  return "DigitizeStateScale";
}

void DigitizeStateScale::updateAfterPointAddition ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::updateAfterPointAddition";
}

void DigitizeStateScale::updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                                  const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::updateModelDigitizeCurve";

  setCursor(cmdMediator);
}

void DigitizeStateScale::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::updateModelSegments";
}
