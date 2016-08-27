/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddPointAxis.h"
#include "CmdMediator.h"
#include "CursorFactory.h"
#include "DigitizeStateAxis.h"
#include "DigitizeStateContext.h"
#include "DlgEditPointAxis.h"
#include "Document.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PointStyle.h"
#include <QCursor>
#include <QImage>
#include <QMessageBox>
#include <QTimer>

DigitizeStateAxis::DigitizeStateAxis (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateAxis::~DigitizeStateAxis ()
{
}

QString DigitizeStateAxis::activeCurve () const
{
  return AXIS_CURVE_NAME;
}

void DigitizeStateAxis::begin (CmdMediator *cmdMediator,
                               DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

void DigitizeStateAxis::createTemporaryPoint (CmdMediator *cmdMediator,
                                              const QPointF &posScreen)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::createTemporaryPoint";

  GeometryWindow *NULL_GEOMETRY_WINDOW = 0;

  // Temporary point that user can see while DlgEditPointAxis is active
  const Curve &curveAxes = cmdMediator->curveAxes();
  PointStyle pointStyleAxes = curveAxes.curveStyle().pointStyle();
  GraphicsPoint *point = context().mainWindow().scene().createPoint(Point::temporaryPointIdentifier (),
                                                                    pointStyleAxes,
                                                                    posScreen,
                                                                    NULL_GEOMETRY_WINDOW);

  context().mainWindow().scene().addTemporaryPoint (Point::temporaryPointIdentifier(),
                                                    point);
}

QCursor DigitizeStateAxis::cursor(CmdMediator *cmdMediator) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::cursor";

  CursorFactory cursorFactory;
  QCursor cursor = cursorFactory.generate (cmdMediator->document().modelDigitizeCurve());

  return cursor;
}

void DigitizeStateAxis::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::end";
}

void DigitizeStateAxis::handleContextMenuEventAxis (CmdMediator * /* cmdMediator */,
                                                    const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();
}

void DigitizeStateAxis::handleContextMenuEventGraph (CmdMediator * /* cmdMediator */,
                                                     const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleContextMenuEventGraph "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();
}

void DigitizeStateAxis::handleCurveChange(CmdMediator * /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleCurveChange";
}

void DigitizeStateAxis::handleKeyPress (CmdMediator * /* cmdMediator */,
                                        Qt::Key key,
                                        bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateAxis::handleMouseMove (CmdMediator * /* cmdMediator */,
                                         QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::handleMouseMove";
}

void DigitizeStateAxis::handleMousePress (CmdMediator * /* cmdMediator */,
                                          QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleMousePress";
}

void DigitizeStateAxis::handleMouseRelease (CmdMediator *cmdMediator,
                                            QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleMouseRelease";

  if (context().mainWindow().transformIsDefined()) {

    QMessageBox::warning (0,
                          QObject::tr ("Engauge Digitizer"),
                          QObject::tr ("Three axis points have been defined, and no more are needed or allowed."));

  } else {

    createTemporaryPoint (cmdMediator,
                          posScreen);

    // Ask user for coordinates
    DlgEditPointAxis *dlg = new DlgEditPointAxis (context ().mainWindow (),
                                                  cmdMediator->document().modelCoords(),
                                                  cmdMediator->document().modelGeneral(),
                                                  context().mainWindow().modelMainWindow(),
                                                  context().mainWindow().transformation(),
                                                  cmdMediator->document().documentAxesPointsRequired());
    int rtn = dlg->exec ();

    bool isXOnly;
    QPointF posGraph = dlg->posGraph (isXOnly);
    delete dlg;

    // Remove temporary point
    context().mainWindow().scene().removePoint(Point::temporaryPointIdentifier ());

    if (rtn == QDialog::Accepted) {

      // User wants to add this axis point, but let's perform sanity checks first

      bool isError;
      QString errorMessage;
      int nextOrdinal = cmdMediator->document().nextOrdinalForCurve(AXIS_CURVE_NAME);

      cmdMediator->document().checkAddPointAxis(posScreen,
                                                posGraph,
                                                isError,
                                                errorMessage,
                                                isXOnly);

      if (isError) {

        QMessageBox::warning (0,
                              QObject::tr ("Engauge Digitizer"),
                              errorMessage);

      } else {

        // Create command to add point
        Document &document = cmdMediator->document ();
        QUndoCommand *cmd = new CmdAddPointAxis (context ().mainWindow(),
                                                 document,
                                                 posScreen,
                                                 posGraph,
                                                 nextOrdinal,
                                                 isXOnly);
        context().appendNewCmd(cmdMediator,
                               cmd);
      }
    }
  }
}

QString DigitizeStateAxis::state() const
{
  return "DigitizeStateAxis";
}

void DigitizeStateAxis::updateAfterPointAddition ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::updateAfterPointAddition";
}

void DigitizeStateAxis::updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                                  const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::updateModelDigitizeCurve";

  setCursor(cmdMediator);
}

void DigitizeStateAxis::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::updateModelSegments";
}
