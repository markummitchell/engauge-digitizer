#include "CmdAddPointAxis.h"
#include "CmdMediator.h"
#include "DigitizeStateAxis.h"
#include "DigitizeStateContext.h"
#include "DlgEditPoint.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PointStyle.h"
#include <QCursor>
#include <QImage>
#include <QMessageBox>
#include <QTimer>

const QString TEMPORARY_POINT_NAME ("temporary");

DigitizeStateAxis::DigitizeStateAxis (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateAxis::~DigitizeStateAxis ()
{
}

void DigitizeStateAxis::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
}

Qt::CursorShape DigitizeStateAxis::cursorShape() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAxis::cursorShape";

  return Qt::CrossCursor;
}

void DigitizeStateAxis::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::end";
}

void DigitizeStateAxis::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAxis::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
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

    // Temporary point that user can see while DlgEditPoint is active
    PointStyle pointStyleAxis = context().cmdMediator().settingsCurves().pointStyleAxis();
    QGraphicsItem *item = context().mainWindow().scene().addPoint(TEMPORARY_POINT_NAME,
                                                                  pointStyleAxis,
                                                                  posScreen);

    // Ask user for coordinates
    DlgEditPoint *dlg = new DlgEditPoint (context ().mainWindow (),
                                          *this,
                                          cursorShape ());
    int rtn = dlg->exec ();
    QPointF posGraph = dlg->posGraph ();
    delete dlg;

    // Remove temporary point
    context().mainWindow().scene().removeItem (item);

    if (rtn == QDialog::Accepted) {

      // User wants to add this axis point, but let's perform sanity checks first

      bool isError;
      QString errorMessage;

      context().cmdMediator().document().checkAddPointAxis(posScreen,
                                                           posGraph,
                                                           isError,
                                                           errorMessage);

      if (isError) {

        QMessageBox::warning (0,
                              "Application",
                              errorMessage);

      } else {

        QUndoCommand *cmd = new CmdAddPointAxis (context ().mainWindow(),
                                                 context ().cmdMediator ().document (),
                                                 posScreen,
                                                 posGraph);
        context().appendNewCmd(cmd);
      }
    }
  }
}
