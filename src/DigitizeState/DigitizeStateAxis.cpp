#include "CmdAddPointAxis.h"
#include "CmdMediator.h"
#include "CursorFactory.h"
#include "DigitizeStateAxis.h"
#include "DigitizeStateContext.h"
#include "DlgEditPoint.h"
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

void DigitizeStateAxis::begin (DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

void DigitizeStateAxis::createTemporaryPoint (const QPointF &posScreen)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::createTemporaryPoint";

  // Temporary point that user can see while DlgEditPoint is active
  const Curve &curveAxes = context().cmdMediator().curveAxes();
  PointStyle pointStyleAxes = curveAxes.curveStyle().pointStyle();
  GraphicsPoint *point = context().mainWindow().scene().createPoint(Point::temporaryPointIdentifier (),
                                                                    pointStyleAxes,
                                                                    posScreen);

  context().mainWindow().scene().addTemporaryPoint (Point::temporaryPointIdentifier(),
                                                    point);
}

QCursor DigitizeStateAxis::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::cursor";

  CursorFactory cursorFactory;
  QCursor cursor = cursorFactory.generate (context().cmdMediator().document().modelDigitizeCurve());

  return cursor;
}

void DigitizeStateAxis::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::end";
}

void DigitizeStateAxis::handleCurveChange()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleCurveChange";
}

void DigitizeStateAxis::handleKeyPress (Qt::Key key,
                                        bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateAxis::handleMouseMove (QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::handleMouseMove";
}

void DigitizeStateAxis::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleMousePress";
}

void DigitizeStateAxis::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleMouseRelease";

  if (context().mainWindow().transformIsDefined()) {

    QMessageBox::warning (0,
                          "Application",
                          "Three axis points have been defined, and no more are needed or allowed.");

  } else {

    createTemporaryPoint (posScreen);

    // Ask user for coordinates
    DlgEditPoint *dlg = new DlgEditPoint (context ().mainWindow (),
                                          *this,
                                          context().cmdMediator().document().modelCoords(),
                                          cursor (),
                                          context().mainWindow().transformation());
    int rtn = dlg->exec ();
    QPointF posGraph = dlg->posGraph ();
    delete dlg;

    // Remove temporary point
    context().mainWindow().scene().removePoint(Point::temporaryPointIdentifier ());

    if (rtn == QDialog::Accepted) {

      // User wants to add this axis point, but let's perform sanity checks first

      bool isError;
      QString errorMessage;
      int nextOrdinal = context().cmdMediator().document().nextOrdinalForCurve(AXIS_CURVE_NAME);

      context().cmdMediator().document().checkAddPointAxis(posScreen,
                                                           posGraph,
                                                           isError,
                                                           errorMessage);

      if (isError) {

        QMessageBox::warning (0,
                              "Application",
                              errorMessage);

      } else {

        // Create command to add point
        Document &document = context ().cmdMediator ().document ();
        QUndoCommand *cmd = new CmdAddPointAxis (context ().mainWindow(),
                                                 document,
                                                 posScreen,
                                                 posGraph,
                                                 nextOrdinal);
        context().appendNewCmd(cmd);
      }
    }
  }
}

QString DigitizeStateAxis::state() const
{
  return "DigitizeStateAxis";
}

void DigitizeStateAxis::updateModelDigitizeCurve (const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::updateModelDigitizeCurve";

  setCursor();
}

void DigitizeStateAxis::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::updateModelSegments";
}
