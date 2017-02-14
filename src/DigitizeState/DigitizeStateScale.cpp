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
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PointStyle.h"
#include <QCursor>
#include <QImage>
#include <QMessageBox>
#include <QTimer>

DigitizeStateScale::DigitizeStateScale (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
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
                                         QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateScale::handleMouseMove";
}

void DigitizeStateScale::handleMousePress (CmdMediator * /* cmdMediator */,
                                          QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleMousePress";
}

void DigitizeStateScale::handleMouseRelease (CmdMediator *cmdMediator,
                                            QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateScale::handleMouseRelease";

  if (context().mainWindow().transformIsDefined()) {

    QMessageBox::warning (0,
                          QObject::tr ("Engauge Digitizer"),
                          QObject::tr ("The scale bar has been defined, and another is not needed or allowed."));

  } else {

    // Ask user for coordinates
    DlgEditScale *dlg = new DlgEditScale (context ().mainWindow (),
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

      // User wants to add this scale point, but let's perform sanity checks first

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
        QUndoCommand *cmd = new CmdAddScale (context ().mainWindow(),
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
