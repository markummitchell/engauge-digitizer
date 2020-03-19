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
#include "GuidelineStateDeployedConstantXSelectEditAppearing.h"
#include "Logger.h"
#include <QObject>
#include <QTimer>
#include "Transformation.h"

GuidelineStateDeployedConstantXSelectEditAppearing::GuidelineStateDeployedConstantXSelectEditAppearing (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context),
  m_timer (nullptr)
{
  m_timer = new QTimer ();
  m_timer->setSingleShot (true);  
}

GuidelineStateDeployedConstantXSelectEditAppearing::~GuidelineStateDeployedConstantXSelectEditAppearing ()
{
}

void GuidelineStateDeployedConstantXSelectEditAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectEditAppearing::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)

  // (Re)connect to timer
  QObject::connect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
  m_timer->start (APPEARING_TIMEOUT);
}

bool GuidelineStateDeployedConstantXSelectEditAppearing::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXSelectEditAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectEditAppearing::end";

  // Cancel timer if active so it does not interrupt the next state
  QObject::disconnect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
}

void GuidelineStateDeployedConstantXSelectEditAppearing::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantXSelectEditAppearing::handleGuidelineMode (bool visible,
                                                                              bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantXSelectEditAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_HOVER);
}

void GuidelineStateDeployedConstantXSelectEditAppearing::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantXSelectEditAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}

void GuidelineStateDeployedConstantXSelectEditAppearing::handleTimeout ()
{
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantXSelectEditAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_APPEARING);
}
