/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdEditPointAxis.h"
#include "CmdMediator.h"
#include "DigitizeStateAbstractBase.h"
#include "DigitizeStateContext.h"
#include "DlgEditPoint.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QImage>
#include <QMessageBox>
#include <QTimer>
#include "QtToString.h"
#include "Version.h"

DigitizeStateAbstractBase::DigitizeStateAbstractBase(DigitizeStateContext &context) :
  m_context (context),
  m_isOverrideCursor (false)
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

void DigitizeStateAbstractBase::handleContextMenuEvent (CmdMediator *cmdMediator,
                                                        const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleContextMenuEvent point=" << pointIdentifier.toLatin1 ().data ();

  QPointF posScreen = cmdMediator->document().positionScreen (pointIdentifier);
  QPointF posGraphBefore = cmdMediator->document().positionGraph (pointIdentifier);
  bool isXOnly = cmdMediator->document().isXOnly (pointIdentifier);

  // Ask user for coordinates
  double x = posGraphBefore.x();
  double y = posGraphBefore.y();

  DlgEditPoint *dlg = new DlgEditPoint(context().mainWindow(),
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

void DigitizeStateAbstractBase::handleLeave (CmdMediator * /* cmdMediator */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAbstractBase::handleLeave";

  removeOverrideCursor ();
}

void DigitizeStateAbstractBase::handleSetOverrideCursor (CmdMediator * /* cmdMediator */,
                                                         const QCursor &cursor)
{
  removeOverrideCursor ();

  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleSetOverrideCursor setOverrideCursor="
                              << QtCursorToString (cursor.shape ()).toLatin1 ().data ();

  QApplication::setOverrideCursor (cursor);
  m_isOverrideCursor = true;
}

void DigitizeStateAbstractBase::removeOverrideCursor ()
{
  if (m_isOverrideCursor) {

    LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateAbstractBase::handleLeave restoreOverrideCursor="
                                << QtCursorToString (QApplication::overrideCursor ()->shape ()).toLatin1 ().data ();

    // Override cursor from last QDialog must be restored
    QApplication::restoreOverrideCursor ();

    m_isOverrideCursor = false;
  }
}

void DigitizeStateAbstractBase::setCursor(CmdMediator *cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAbstractBase::setCursor";

  removeOverrideCursor ();
  context().view().setCursor (cursor (cmdMediator));
}
