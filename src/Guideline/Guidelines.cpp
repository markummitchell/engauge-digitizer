/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "Document.h"
#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineEllipse.h"
#include "GuidelineLine.h"
#include "Guidelines.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMap>
#include <qmath.h>
#include <QTextStream>

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

ColorPalette Guidelines::color () const
{
  return m_mainWindow.modelMainWindow().guidelineColor();
}

CoordsType Guidelines::coordsType () const
{
  return m_mainWindow.cmdMediator()->document().modelCoords().coordsType();
}

GuidelineAbstract *Guidelines::createGuideline (GuidelineState stateInitial)
{
  // This method is used to create non-template Guidelines after the template Guidelines
  // have been created. We grab the scene from the first Guideline in the list
  ENGAUGE_ASSERT (m_guidelineContainer.size () > 0);

  GuidelineAbstract *guidelineFirst = m_guidelineContainer.at (0);
  QGraphicsScene &scene = guidelineFirst->scene ();

  // Map of states that get an ellipse
  QMap<GuidelineState, bool> guidelineStatesWithEllipse;
  guidelineStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE] = true;
  guidelineStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE] = true;
  guidelineStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER] = true;

  GuidelineAbstract *guideline = nullptr;

  if (guidelineStatesWithEllipse.contains (stateInitial)) {

    guideline = new GuidelineEllipse (scene,
                                      *this,
                                      stateInitial);

  } else {

    guideline = new GuidelineLine (scene,
                                      *this,
                                      stateInitial);

  }

  ENGAUGE_CHECK_PTR (guideline);

  registerGuideline (guideline);

  return guideline;
}

void Guidelines::handleActiveChange (bool active)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleActiveChange (active);
  }
}

void Guidelines::handleVisibleChange (bool visible)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleVisibleChange (visible);
  }
}

void Guidelines::initialize (QGraphicsScene &scene)
{
  GuidelineState stateVerticalLeft = GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING;
  GuidelineState stateVerticalRight = GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING;
  GuidelineState stateHorizontalTop = GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING;
  GuidelineState stateHorizontalBottom = GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING;

  if (!transformation().transformIsDefined()) {
    stateVerticalLeft = GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE;
    stateVerticalRight = GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE;
    stateHorizontalTop = GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE;
    stateHorizontalBottom = GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE;
  }

  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        stateVerticalLeft));
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        stateVerticalRight));
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        stateHorizontalTop));
  registerGuideline (new GuidelineLine (scene,
                                        *this,
                                        stateHorizontalBottom));
}

void Guidelines::registerGuideline (GuidelineAbstract *guideline)
{
  m_guidelineContainer.push_back (guideline);
}

QString Guidelines::stateDump () const
{
  // Sort the entries
  QStringList sorted;
  GuidelineContainerPrivate::const_iterator itrSort;
  for (itrSort = m_guidelineContainer.begin(); itrSort != m_guidelineContainer.end(); itrSort++) {
    GuidelineAbstract *guideline = *itrSort;

    sorted << guideline->state();
  }

  qSort (sorted.begin(),
         sorted.end());

  // Convert entries to output text
  QString out;
  QTextStream str (&out);

  str << "Guidelines::stateDump:\n";

  QStringList::const_iterator itrOut;
  for (itrOut = sorted.begin(); itrOut != sorted.end(); itrOut++) {
    QString entry = *itrOut;

    str << "                    " << entry << "\n";
  }

  return out;
}

Transformation Guidelines::transformation() const
{
  return m_mainWindow.transformation ();
}

void Guidelines::updateColor ()
{
  GuidelineContainerPrivate::const_iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->updateColor ();
  }
}

void Guidelines::updateWithLatestTransformation ()
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateWithLatestTransformation ();
  }
}
