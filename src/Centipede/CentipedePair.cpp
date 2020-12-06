/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedePair.h"
#include "CentipedeSegmentAbstract.h"
#include "CentipedeSegmentConstantREllipse.h"
#include "CentipedeSegmentConstantTRadial.h"
#include "CentipedeSegmentConstantXLine.h"
#include "CentipedeSegmentConstantYLine.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGuideline.h"
#include "GraphicsScene.h"
#include "mmsubs.h"
#include "Transformation.h"

CentipedePair::CentipedePair(GraphicsScene &scene,
                             const Transformation &transformation,
                             const DocumentModelGuideline &modelGuideline,
                             const DocumentModelCoords &modelCoords,
                             const QPointF &posScreen) :
  m_modelGuideline (modelGuideline),
  m_centipedeXT (nullptr),
  m_centipedeYR (nullptr),
  m_posScreenStart (posScreen),
  m_selectedXTFinal (true),
  m_valueFinal (0)
{
  // Create visible Centipede items
  if (modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {
    m_centipedeXT = new CentipedeSegmentConstantXLine (scene,
                                                       modelGuideline,
                                                       transformation,
                                                       posScreen);
    m_centipedeYR = new CentipedeSegmentConstantYLine (scene,
                                                       modelGuideline,
                                                       transformation,
                                                       posScreen);
  } else {
    m_centipedeXT = new CentipedeSegmentConstantTRadial (scene,
                                                         modelCoords,
                                                         modelGuideline,
                                                         transformation,
                                                         posScreen);
    m_centipedeYR = new CentipedeSegmentConstantREllipse (scene,
                                                          modelCoords,
                                                          modelGuideline,
                                                          transformation,
                                                          posScreen);
  }

  // Save starting graph position
  transformation.transformScreenToRawGraph(posScreen,
                                           m_posGraphStart);
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

  return (distanceFromCenter > m_modelGuideline.creationCircleRadius ());
}

void CentipedePair::handleKeyPress (Qt::Key key,
                                    bool atLeastOneSelectedItem)
{
  m_context.handleKeyPress (key,
                            atLeastOneSelectedItem);
}

void CentipedePair::handleMouseMove (QPointF posScreen)
{
  m_context.handleMouseMove (posScreen);
}

void CentipedePair::handleMousePress (QPointF posScreen)
{
  m_context.handleMousePress (posScreen);
}

void CentipedePair::handleMouseRelease (QPointF posScreen)
{
  m_context.handleMouseRelease (posScreen);
}

void CentipedePair::move (const QPointF &posScreen)
{
  QPointF delta = posScreen - m_posScreenStart;
  double distanceFromCenter = magnitude (delta);

  if (updateFinalValues (posScreen)) {
    m_centipedeXT->updateRadius (m_modelGuideline.creationCircleRadius () + distanceFromCenter);
    m_centipedeYR->updateRadius (m_modelGuideline.creationCircleRadius () - distanceFromCenter);
  } else {
    m_centipedeXT->updateRadius (m_modelGuideline.creationCircleRadius () - distanceFromCenter);
    m_centipedeYR->updateRadius (m_modelGuideline.creationCircleRadius () + distanceFromCenter);
  }
}

bool CentipedePair::selectedXTFinal () const
{
  return m_selectedXTFinal;
}

bool CentipedePair::updateFinalValues (const QPointF &posScreen)
{
  // Update selection
  double distXT = m_centipedeXT->distanceToClosestEndpoint (posScreen);
  double distYR = m_centipedeYR->distanceToClosestEndpoint (posScreen);
  m_selectedXTFinal = (distXT < distYR);

  // Update value
  if (m_selectedXTFinal) {
    m_valueFinal = m_posGraphStart.x();
  } else {
    m_valueFinal = m_posGraphStart.y();
  }

  return m_selectedXTFinal;
}

double CentipedePair::valueFinal () const
{
  return m_valueFinal;
}
