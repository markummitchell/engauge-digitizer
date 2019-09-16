/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "Guidelines.h"
#include <QGraphicsScene>
#include <qmath.h>

Guidelines::Guidelines() :
  m_guidelinePresuppliedLeft (nullptr),
  m_guidelinePresuppliedRight (nullptr),
  m_guidelinePresuppliedTop (nullptr),
  m_guidelinePresuppliedBottom (nullptr)
{
}

Guidelines::~Guidelines ()
{
  delete m_guidelinePresuppliedLeft;
  delete m_guidelinePresuppliedRight;
  delete m_guidelinePresuppliedTop;
  delete m_guidelinePresuppliedBottom;
}

void Guidelines::clear ()
{
}
void Guidelines::initialize (QGraphicsScene &scene)
{
  if (m_guidelinePresuppliedLeft == nullptr) {
    m_guidelinePresuppliedLeft = new Guideline (scene,
                                                GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT);
  }

  if (m_guidelinePresuppliedRight == nullptr) {
    m_guidelinePresuppliedRight = new Guideline (scene,
                                                 GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT);
  }

  if (m_guidelinePresuppliedTop == nullptr) {
    m_guidelinePresuppliedTop = new Guideline (scene,
                                               GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP);
  }

  if (m_guidelinePresuppliedBottom == nullptr) {
    m_guidelinePresuppliedBottom = new Guideline (scene,
                                                  GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM);
  }
}

void Guidelines::showHide (bool show)
{
}

void Guidelines::update ()
{
}
