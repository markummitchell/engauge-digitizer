/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineLine.h"
#include "Guidelines.h"
#include "MainWindow.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <qmath.h>

Guidelines::Guidelines (MainWindow &mainWindow) :
  m_mainWindow (mainWindow)
{
}

Guidelines::~Guidelines ()
{
  clear ();
}

void Guidelines::clear ()
{
  QGraphicsScene *scene = nullptr;

  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    if (scene == nullptr) {
      scene = &guideline->scene();
    }

    guideline->removeFromScene (scene);
  }

  m_guidelineContainer.clear ();
}

GuidelineAbstract *Guidelines::createGuideline (GuidelineState stateInitial)
{
  // This method is used to create non-template Guidelines after the template Guidelines
  // have been created. We grab the scene from the first Guideline in the list
  ENGAUGE_ASSERT (m_guidelineContainer.size () > 0);

  GuidelineAbstract *guidelineFirst = m_guidelineContainer.at (0);
  QGraphicsScene &scene = guidelineFirst->scene ();

  GuidelineAbstract *guideline = new GuidelineLine (scene,
                                                    *this,
                                                    stateInitial);

  ENGAUGE_CHECK_PTR (guideline);

  registerGuideline (guideline);

  return guideline;
}

void Guidelines::initialize (QGraphicsScene &scene,
                             bool guidelinesAreActive)
{
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING));
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING));
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING));
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING));

  showHide (guidelinesAreActive);
}

void Guidelines::registerGuideline (GuidelineAbstract *guideline)
{
  m_guidelineContainer.push_back (guideline);
}

void Guidelines::showHide (bool show)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->handleShowHide (show);
  }
}

Transformation Guidelines::transformation() const
{
  return m_mainWindow.transformation ();
}

void Guidelines::update (bool guidelinesAreActive)
{
  if (guidelinesAreActive) {
    showHide (true);
  } else{
    showHide (false);
  }
}

void Guidelines::updateGuidelinesSelectability (bool selectable)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    QGraphicsItem::GraphicsItemFlags flags = guideline->graphicsItemFlags ();

    if (selectable) {
      // Add flag
      flags |= QGraphicsItem::ItemIsSelectable;
    } else {
      // Remove flag
      flags &= ~QGraphicsItem::ItemIsSelectable;
    }

    guideline->setGraphicsItemFlags (flags);
  }
}
