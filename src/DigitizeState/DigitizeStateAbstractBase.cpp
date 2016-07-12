/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdEditPointAxis.h"
#include "CmdMediator.h"
#include "DigitizeStateAbstractBase.h"
#include "DigitizeStateContext.h"
#include "DlgEditPointAxis.h"
#include "DlgEditPointCurve.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsScene>
#include <QImage>
#include <QMessageBox>
#include <QTimer>
#include "QtToString.h"
#include "Version.h"

DigitizeStateAbstractBase::DigitizeStateAbstractBase(DigitizeStateContext &context) :
  m_context (context)
{
}

DigitizeStateAbstractBase::~DigitizeStateAbstractBase()
{
}

DigitizeStateContext &DigitizeStateAbstractBase::context()
{
  return m_context;
}

const DigitizeStateContext &DigitizeStateAbstractBase::context() const
{
  return m_context;
}

void DigitizeStateAbstractBase::handleContextMenuEventAxis (CmdMediator *cmdMediator,
                                                            const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();

  QPointF posScreen = cmdMediator->document().positionScreen (pointIdentifier);
  QPointF posGraphBefore = cmdMediator->document().positionGraph (pointIdentifier);
  bool isXOnly = cmdMediator->document().isXOnly (pointIdentifier);

  // Ask user for coordinates
  double x = posGraphBefore.x();
  double y = posGraphBefore.y();

  DlgEditPointAxis *dlg = new DlgEditPointAxis (context().mainWindow(),
                                                *this,
                                                cmdMediator->document().modelCoords(),
                                                context().mainWindow().modelMainWindow(),
                                                cursor (cmdMediator),
                                                context().mainWindow().transformation(),
                                                cmdMediator->document().documentAxesPointsRequired(),
                                                isXOnly,
                                                &x,
                                                &y);
  int rtn = dlg->exec ();

  QPointF posGraphAfter = dlg->posGraph (isXOnly); // This call returns new values for isXOnly and the graph position
  delete dlg;

  if (rtn == QDialog::Accepted) {

    // User wants to edit this axis point, but let's perform sanity checks first

    bool isError;
    QString errorMessage;

    context().mainWindow().cmdMediator()->document().checkEditPointAxis(pointIdentifier,
                                                                        posScreen,
                                                                        posGraphAfter,
                                                                        isError,
                                                                        errorMessage);

    if (isError) {

      QMessageBox::warning (0,
                            engaugeWindowTitle(),
                            errorMessage);

    } else {

      // Create a command to edit the point
      CmdEditPointAxis *cmd = new CmdEditPointAxis (context().mainWindow(),
                                                    cmdMediator->document(),
                                                    pointIdentifier,
                                                    posGraphBefore,
                                                    posGraphAfter,
                                                    isXOnly);
      context().appendNewCmd(cmdMediator,
                             cmd);
    }
  }
}

void DigitizeStateAbstractBase::handleContextMenuEventCurve (CmdMediator *cmdMediator,
                                                             const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleContextMenuEventCurve "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();

  // Ask user for coordinates
//  double x = posGraphBefore.x();
//  double y = posGraphBefore.y();

//  DlgEditPointCurve *dlg = new DlgEditPointCurve (context().mainWindow(),
//                                                  *this,
//                                                  cmdMediator->document().modelCoords(),
//                                                  context().mainWindow().modelMainWindow(),
//                                                  cursor (cmdMediator),
//                                                  context().mainWindow().transformation(),
//                                                  &x,
//                                                  &y);
//  int rtn = dlg->exec ();

//  QPointF posGraphAfter = dlg->posGraph ();
//  delete dlg;

//  if (rtn == QDialog::Accepted) {

//    // User wants to edit this axis point, but let's perform sanity checks first

//    bool isError;
//    QString errorMessage;

//    context().mainWindow().cmdMediator()->document().checkEditPointAxis(pointIdentifier,
//                                                                        posScreen,
//                                                                        posGraphAfter,
//                                                                        isError,
//                                                                        errorMessage);

//    if (isError) {

//      QMessageBox::warning (0,
//                            engaugeWindowTitle(),
//                            errorMessage);

//    } else {

      // Create a command to edit the point
//      CmdEditPointCurve *cmd = new CmdEditPointCurve (context().mainWindow(),
//                                                      cmdMediator->document(),
//                                                      pointIdentifier);
//                                                      posGraphBefore,
//                                                      posGraphAfter,
//                                                      isXOnly);
//      context().appendNewCmd(cmdMediator,
//                             cmd);
//    }
//  }
}

void DigitizeStateAbstractBase::handleLeave (CmdMediator * /* cmdMediator */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAbstractBase::handleLeave";

  removeOverrideCursor ();
}

void DigitizeStateAbstractBase::handleSetOverrideCursor (CmdMediator * /* cmdMediator */,
                                                         const QCursor &cursor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleSetOverrideCursor setOverrideCursor="
                              << QtCursorToString (cursor.shape ()).toLatin1 ().data ();

  // Note that we are setting the QGraphicsView cursor and NOT the QApplication override cursor
  m_context.view ().setCursor (cursor);
}

void DigitizeStateAbstractBase::removeOverrideCursor ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleLeave restoreOverrideCursor";
}

void DigitizeStateAbstractBase::setCursor(CmdMediator *cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAbstractBase::setCursor";

  // Note that we are setting the QGraphicsView cursor and NOT the QApplication override cursor
  m_context.view ().setCursor (cursor (cmdMediator));
}
