/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
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
    Guideline *guideline = *itr;

    if (scene == nullptr) {
      scene = guideline->scene();
    }

    scene->removeItem (guideline);
  }

  m_guidelineContainer.clear ();
}

Guideline *Guidelines::createGuideline (GuidelineState stateInitial)
{
  // This method is used to create non-template Guidelines after the template Guidelines
  // have been created. We grab the scene from the first Guideline in the list
  ENGAUGE_ASSERT (m_guidelineContainer.size () > 0);

  Guideline *guidelineFirst = m_guidelineContainer.at (0);
  QGraphicsScene *scene = guidelineFirst->scene ();

  Guideline *guideline = new Guideline (*scene,
                                        *this,
                                        stateInitial);

  ENGAUGE_CHECK_PTR (guideline);

  registerGuideline (guideline);

  return guideline;
}

void Guidelines::initialize (QGraphicsScene &scene,
                             bool guidelinesAreActive)
{
  registerGuideline (new Guideline (scene,
                                    *this,
                                    GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING));
  registerGuideline (new Guideline (scene,
                                    *this,
                                    GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING));
  registerGuideline (new Guideline (scene,
                                    *this,
                                    GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING));
  registerGuideline (new Guideline (scene,
                                    *this,
                                    GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING));

  showHide (guidelinesAreActive);
}

void Guidelines::registerGuideline (Guideline *guideline)
{
  m_guidelineContainer.push_back (guideline);
}

void Guidelines::showHide (bool show)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    Guideline *guideline = *itr;
    guideline->handleShowHide (show);
  }
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
    Guideline *guideline = *itr;

    QGraphicsItem::GraphicsItemFlags flags = guideline->flags ();

    if (selectable) {
      // Add flag
      flags |= QGraphicsItem::ItemIsSelectable;
    } else {
      // Remove flag
      flags &= ~QGraphicsItem::ItemIsSelectable;
    }

    guideline->setFlags (flags);
  }
}
