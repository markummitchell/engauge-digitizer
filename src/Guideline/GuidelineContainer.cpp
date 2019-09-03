/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineContainer.h"
#include <QGraphicsScene>

GuidelineContainer::GuidelineContainer() :
  m_guidelinePresuppliedLeft (nullptr),
  m_guidelinePresuppliedRight (nullptr),
  m_guidelinePresuppliedTop (nullptr),
  m_guidelinePresuppliedBottom (nullptr)
{
}

GuidelineContainer::~GuidelineContainer ()
{
  delete m_guidelinePresuppliedLeft;
  delete m_guidelinePresuppliedRight;
  delete m_guidelinePresuppliedTop;
  delete m_guidelinePresuppliedBottom;
}

void GuidelineContainer::updateGuidelines (QGraphicsScene &scene)
{
  if (m_guidelinePresuppliedLeft == nullptr) {
    m_guidelinePresuppliedLeft = new Guideline (scene);
  }

  if (m_guidelinePresuppliedRight == nullptr) {
    m_guidelinePresuppliedRight = new Guideline (scene);
  }

  if (m_guidelinePresuppliedTop == nullptr) {
    m_guidelinePresuppliedTop = new Guideline (scene);
  }

  if (m_guidelinePresuppliedBottom == nullptr) {
    m_guidelinePresuppliedBottom = new Guideline (scene);
  }

  // Shift to outermost pixels are at border
  double halfLinewidth = Guideline::linewidthPresupplied () / 2.0 - 2;

  // The presupplied guidelines are always just inside the scene boundaries, which means they are NOT aligned
  // with the graphics reference frame unless (rarely) the scene and graphics reference frames are co-aligned
  m_guidelinePresuppliedLeft->setLine(QLineF (scene.sceneRect().bottomLeft() + QPointF (halfLinewidth, 0),
                                              scene.sceneRect().topLeft() + QPointF (halfLinewidth, 0)));
  m_guidelinePresuppliedRight->setLine (QLineF (scene.sceneRect().bottomRight() - QPointF (halfLinewidth, 0),
                                                scene.sceneRect().topRight() - QPointF (halfLinewidth, 0)));
  m_guidelinePresuppliedTop->setLine (QLineF (scene.sceneRect().topLeft() + QPointF (0, halfLinewidth),
                                              scene.sceneRect().topRight() + QPointF (0, halfLinewidth)));
  m_guidelinePresuppliedBottom->setLine (QLineF (scene.sceneRect().bottomLeft() - QPointF (0, halfLinewidth),
                                                 scene.sceneRect().bottomRight() - QPointF (0, halfLinewidth)));
}
