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
#include "MainWindowModel.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QImage>
#include <QMessageBox>
#include <QTimer>
#include "QtToString.h"
#include "Transformation.h"
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
                                                cmdMediator->document().modelCoords(),
                                                context().mainWindow().modelMainWindow(),
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

  double *x = 0, *y = 0;

  if (pointIdentifiers.count() == 1) {

    // There is exactly one point so pass its coordinates to the dialog
    x = new double;
    y = new double;

    QPointF posScreenBefore = cmdMediator->document().positionScreen (pointIdentifiers.first());
    QPointF posGraphBefore;
    context().mainWindow().transformation().transformScreenToRawGraph (posScreenBefore,
                                                                       posGraphBefore);

    // Ask user for coordinates
    *x = posGraphBefore.x();
    *y = posGraphBefore.y();
  }

  DlgEditPointCurve *dlg = new DlgEditPointCurve (context().mainWindow(),
                                                  cmdMediator->document().modelCoords(),
                                                  context().mainWindow().modelMainWindow(),
                                                  context().mainWindow().transformation(),
                                                  x,
                                                  y);
  if (x != 0) {
    delete x;
    x = 0;
  }

  if (y != 0) {
    delete y;
    y = y;
  }

  int rtn = dlg->exec ();


  delete dlg;
}

void DigitizeStateAbstractBase::setCursor(CmdMediator *cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAbstractBase::setCursor";

  // Note that we are setting the QGraphicsView cursor and NOT the QApplication override cursor
  m_context.view ().setCursor (cursor (cmdMediator));
}
