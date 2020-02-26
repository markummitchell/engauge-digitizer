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
#include "GuidelineStateDeployedConstantTAppearing.h"
#include "Logger.h"
#include <QObject>
#include <QTimer>
#include "Transformation.h"

GuidelineStateDeployedConstantTAppearing::GuidelineStateDeployedConstantTAppearing (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context),
  m_timer (nullptr)
{
  m_timer = new QTimer ();
  m_timer->setSingleShot (true);  
}

GuidelineStateDeployedConstantTAppearing::~GuidelineStateDeployedConstantTAppearing ()
{
}

void GuidelineStateDeployedConstantTAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTAppearing::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);

  // (Re)connect to timer
  QObject::connect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
  m_timer->start (APPEARING_TIMEOUT);
}

bool GuidelineStateDeployedConstantTAppearing::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTAppearing::end";

  // Cancel timer if active so it does not interrupt the next state
  QObject::disconnect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
}

void GuidelineStateDeployedConstantTAppearing::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTAppearing::handleGuidelineMode (bool visible,
                                                                    bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED);
  }
}

void GuidelineStateDeployedConstantTAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER);
}

void GuidelineStateDeployedConstantTAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER
}

void GuidelineStateDeployedConstantTAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_APPEARING);
}

void GuidelineStateDeployedConstantTAppearing::handleTimeout ()
{
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

QString GuidelineStateDeployedConstantTAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_APPEARING);
}
