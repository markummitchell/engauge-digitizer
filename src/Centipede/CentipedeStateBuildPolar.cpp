/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedePairPolar.h"
#include "CentipedeStateBuildPolar.h"
#include "CentipedeStateContext.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGuideline.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include "Transformation.h"

CentipedeStateBuildPolar::CentipedeStateBuildPolar (CentipedeStateContext &context) :
  CentipedeStateAbstractBase (context),
  m_centipedePair (0)
{
}

CentipedeStateBuildPolar::~CentipedeStateBuildPolar ()
{
  delete m_centipedePair;
}

void CentipedeStateBuildPolar::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeStateBuildPolar::begin";

  m_centipedePair = new CentipedePairPolar (context().scene(),
                                            context().transformation(),
                                            context().modelGuideline (),
                                            context().modelCoords (),
                                            context().posClickScreen ());
}

void CentipedeStateBuildPolar::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeStateBuildPolar::end";

  delete m_centipedePair;
  m_centipedePair = nullptr;
}

void CentipedeStateBuildPolar::handleKeyPress (Qt::Key /* key */,
                                               bool /* atLeastOneSelectedItem */)
{
  // Stop
  context().requestDelayedStateTransition (CENTIPEDE_STATE_PREBUILD);
}

void CentipedeStateBuildPolar::handleMouseMove (QPointF posScreen)
{
  if (m_centipedePair-> done (posScreen)) {

    // Done so make a command and exit this state
    context().createGuidelineCommand (m_centipedePair->selectedXTFinal (),
                                      m_centipedePair->valueFinal ());
    context().requestDelayedStateTransition (CENTIPEDE_STATE_PREBUILD);

  } else {

    m_centipedePair->move (posScreen);

  }
}

void CentipedeStateBuildPolar::handleMousePress (QPointF /* posScreen */)
{
 // Noop
}

void CentipedeStateBuildPolar::handleMouseRelease (QPointF /* posScreen */)
{
  context().requestDelayedStateTransition (CENTIPEDE_STATE_PREBUILD);
}
