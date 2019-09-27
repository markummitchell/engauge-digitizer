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
  guidelineStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE] = true;
  guidelineStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER] = true;
  guidelineStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_NORMAL] = true;

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

void Guidelines::initialize (QGraphicsScene &scene)
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
}

void Guidelines::registerGuideline (GuidelineAbstract *guideline)
{
  m_guidelineContainer.push_back (guideline);
}

QString Guidelines::stateDump () const
{
  QString out, delimiter;
  QTextStream str (&out);

  GuidelineContainerPrivate::const_iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    str << delimiter << guideline->state();
    delimiter = ", ";
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

void Guidelines::updateSelectability (bool selectable)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guidelines::updateSelectability selectable="
                              << (selectable ? "on" : "off");

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

void Guidelines::updateVisiblity (bool show)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->handleShowHide (show);
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
