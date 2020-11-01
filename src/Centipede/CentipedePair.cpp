/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedePair.h"
#include "CentipedeSegmentAbstract.h"
#include "CentipedeSegmentConstantXTLine.h"
#include "CentipedeSegmentConstantYRLine.h"
#include "GraphicsScene.h"
#include "mmsubs.h"
#include "Transformation.h"

const int INITIAL_RADIUS_PIXELS = 20;

CentipedePair::CentipedePair(GraphicsScene &scene,
                             const Transformation &transformation,
                             const QPointF &posScreen) :
  m_centipedeXT (nullptr),
  m_centipedeYR (nullptr),
  m_posScreenStart (posScreen)
{
  m_centipedeXT = new CentipedeSegmentConstantXTLine (transformation,
                                                      posScreen,
                                                      INITIAL_RADIUS_PIXELS);
  m_centipedeYR = new CentipedeSegmentConstantYRLine (transformation,
                                                      posScreen,
                                                      INITIAL_RADIUS_PIXELS);
  scene.addItem (m_centipedeXT->graphicsItem ());
  scene.addItem (m_centipedeYR->graphicsItem ());  
}

CentipedePair::~CentipedePair()
{
  delete m_centipedeXT;
  delete m_centipedeYR;
}

bool CentipedePair::done (const QPointF &posScreen)
{
  QPointF delta = posScreen - m_posScreenStart;
  double distanceFromCenter = magnitude (delta);

  return (distanceFromCenter > INITIAL_RADIUS_PIXELS);
}

void CentipedePair::move (const QPointF &posScreen)
{
  QPointF delta = posScreen - m_posScreenStart;
  double distanceFromCenter = magnitude (delta);

  if (selectedXT (posScreen)) {
    m_centipedeXT->updateRadius (INITIAL_RADIUS_PIXELS + distanceFromCenter);
    m_centipedeYR->updateRadius (INITIAL_RADIUS_PIXELS - distanceFromCenter);
  } else {
    m_centipedeXT->updateRadius (INITIAL_RADIUS_PIXELS - distanceFromCenter);
    m_centipedeYR->updateRadius (INITIAL_RADIUS_PIXELS +distanceFromCenter);
  }
}

bool CentipedePair::selectedXT (const QPointF &posScreen) const
{
  double distXT = m_centipedeXT->distanceToClosestEndpoint (posScreen);
  double distYR = m_centipedeYR->distanceToClosestEndpoint (posScreen);

  return (distXT < distYR);
}
