/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineEllipse.h"
#include "GuidelineFactory.h"
#include "GuidelineLine.h"
#include "Guidelines.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsScene>

GuidelineFactory::GuidelineFactory (GraphicsScene *sceneMain) :
  m_sceneMain (sceneMain)
{
  createEllipseMap ();
}

GuidelineFactory::~GuidelineFactory ()
{
}

GuidelineAbstract *GuidelineFactory::createGuideline (Guidelines &guidelines,
                                                      GuidelineState stateInitial,
                                                      MainWindow &mainWindow,
                                                      const QString &identifier)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineFactory::createGuideline identifier="
                               << identifier.toLatin1().data();

  // Main scene or one of the guideline scenes?
  QGraphicsScene *scene = m_sceneMain;
  
  // Line or ellipse?
  GuidelineAbstract *guideline = nullptr;
  
  if (m_mapStatesWithEllipse.contains (stateInitial)) {

    guideline = new GuidelineEllipse (*scene,
                                      guidelines,
                                      stateInitial,
                                      identifier);
    
  } else {

    guideline = new GuidelineLine (*scene,
                                   guidelines,
                                   stateInitial,
                                   identifier);
  }

  QObject::connect (guideline, SIGNAL (signalGuidelineDragged (QString, double, bool, GuidelineState)),
                    &mainWindow, SLOT (slotGuidelineDragged (QString, double, bool, GuidelineState)));

  return guideline;
}

void GuidelineFactory::createEllipseMap ()
{
  // All other states get a line instead of an ellipse
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_APPEARING] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER] = true;
}
