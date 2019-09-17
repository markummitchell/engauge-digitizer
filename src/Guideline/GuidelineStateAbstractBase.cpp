/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "Guideline.h"
#include "GuidelineFormat.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <qmath.h>

GuidelineStateAbstractBase::GuidelineStateAbstractBase(GuidelineStateContext &context) :
  m_context (context)
{
}

GuidelineStateAbstractBase::~GuidelineStateAbstractBase ()
{
}

GuidelineStateContext &GuidelineStateAbstractBase::context () const
{
  return m_context;
}

void GuidelineStateAbstractBase::handleMousePressCommon (const QPointF &pos,
                                                         GuidelineState stateDeployed,
                                                         GuidelineState stateReplacement)
{
  context().setStateReplacement (stateReplacement);

  // Visible Guideline will follow this one. Its geometry will be set after every drag event
  Guideline *guidelineVisible = context().createGuideline (stateDeployed);

  GuidelineFormat guidelineFormat;
  guidelineVisible->setPenColor (guidelineFormat.colorDeployedNonHover (),
                                 guidelineFormat.lineWidthNonHover ());

  guidelineVisible->updateGeometry (pos);

  context().guideline().bindGuidelineVisible (guidelineVisible);

  context().requestStateTransition (GUIDELINE_STATE_HANDLE);
}

QRectF GuidelineStateAbstractBase::sceneRect () const
{
  return m_context.guideline().scene()->sceneRect();
}
