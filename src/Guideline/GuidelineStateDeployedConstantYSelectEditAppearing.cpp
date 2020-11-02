/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYSelectEditAppearing.h"
#include "Logger.h"
#include <QObject>
#include <QTimer>
#include "Transformation.h"

GuidelineStateDeployedConstantYSelectEditAppearing::GuidelineStateDeployedConstantYSelectEditAppearing (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context),
  m_timer (nullptr)
{
  m_timer = new QTimer ();
  m_timer->setSingleShot (true);  
}

GuidelineStateDeployedConstantYSelectEditAppearing::~GuidelineStateDeployedConstantYSelectEditAppearing ()
{
}

void GuidelineStateDeployedConstantYSelectEditAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectEditAppearing::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (true,
               false);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)

  // (Re)connect to timer
  QObject::connect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
  m_timer->start (APPEARING_TIMEOUT);
}

bool GuidelineStateDeployedConstantYSelectEditAppearing::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYSelectEditAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectEditAppearing::end";

  // Cancel timer if active so it does not interrupt the next state
  QObject::disconnect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
}

void GuidelineStateDeployedConstantYSelectEditAppearing::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantYSelectEditAppearing::handleGuidelineMode (bool visible,
                                                                              bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantYSelectEditAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_HOVER);
}

void GuidelineStateDeployedConstantYSelectEditAppearing::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYSelectEditAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}

void GuidelineStateDeployedConstantYSelectEditAppearing::handleTimeout ()
{
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantYSelectEditAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_APPEARING);
}
