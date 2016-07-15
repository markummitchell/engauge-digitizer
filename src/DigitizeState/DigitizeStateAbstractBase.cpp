/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DigitizeStateAbstractBase.h"
#include "DigitizeStateContext.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QImage>
#include <QTimer>
#include "QtToString.h"
#include "Transformation.h"

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

void DigitizeStateAbstractBase::setCursor(CmdMediator *cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateAbstractBase::setCursor";

  // Note that we are setting the QGraphicsView cursor and NOT the QApplication override cursor
  m_context.view ().setCursor (cursor (cmdMediator));
}
