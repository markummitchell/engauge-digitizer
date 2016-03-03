/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DigitizeStateEmpty.h"
#include "DigitizeStateContext.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>

DigitizeStateEmpty::DigitizeStateEmpty (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateEmpty::~DigitizeStateEmpty ()
{
}

QString DigitizeStateEmpty::activeCurve () const
{
  return "";
}

void DigitizeStateEmpty::begin (CmdMediator *cmdMediator,
                                DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::begin";

  setCursor(cmdMediator);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateEmpty::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEmpty::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateEmpty::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::end";
}

void DigitizeStateEmpty::handleCurveChange(CmdMediator * /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleCurveChange";
}

void DigitizeStateEmpty::handleKeyPress (CmdMediator * /* cmdMediator */,
                                         Qt::Key key,
                                         bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateEmpty::handleMouseMove (CmdMediator * /* cmdMediator */,
                                          QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateEmpty::handleMouseMove";
}

void DigitizeStateEmpty::handleMousePress (CmdMediator * /* cmdMediator */,
                                           QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleMousePress";
}

void DigitizeStateEmpty::handleMouseRelease (CmdMediator * /* cmdMediator */,
                                             QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::handleMouseRelease";
}

QString DigitizeStateEmpty::state() const
{
  return "DigitizeStateEmpty";
}

void DigitizeStateEmpty::updateModelDigitizeCurve (CmdMediator * /* cmdMediator */,
                                                   const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::updateModelDigitizeCurve";
}

void DigitizeStateEmpty::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateEmpty::updateModelSegments";
}
