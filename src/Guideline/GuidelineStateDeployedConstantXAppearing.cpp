/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXAppearing.h"
#include "Logger.h"
#include <QObject>
#include <QTimer>
#include "Transformation.h"

GuidelineStateDeployedConstantXAppearing::GuidelineStateDeployedConstantXAppearing (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context),
  m_timer (nullptr)
{
  m_timer = new QTimer ();
  m_timer->setSingleShot (true);  
}

GuidelineStateDeployedConstantXAppearing::~GuidelineStateDeployedConstantXAppearing ()
{
}

void GuidelineStateDeployedConstantXAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXAppearing::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);

  // (Re)connect to timer
  QObject::connect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
  m_timer->start (APPEARING_TIMEOUT);
}

bool GuidelineStateDeployedConstantXAppearing::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXAppearing::end";

  // Cancel timer if active so it does not interrupt the next state
  QObject::disconnect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
}

void GuidelineStateDeployedConstantXAppearing::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXAppearing::handleGuidelineMode (bool visible,
                                                                    bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED);
  }
}

void GuidelineStateDeployedConstantXAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER);
}

void GuidelineStateDeployedConstantXAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER
}

void GuidelineStateDeployedConstantXAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_APPEARING);
}

void GuidelineStateDeployedConstantXAppearing::handleTimeout ()
{
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

QString GuidelineStateDeployedConstantXAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_APPEARING);
}
