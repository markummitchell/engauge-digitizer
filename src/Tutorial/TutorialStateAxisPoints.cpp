/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateAxisPoints.h"
#include "TutorialStateContext.h"

TutorialStateAxisPoints::TutorialStateAxisPoints (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context),
  m_title (nullptr),
  m_background (nullptr),
  m_text0 (nullptr),
  m_text1 (nullptr),
  m_text2 (nullptr),
  m_previous (nullptr),
  m_next (nullptr)
{
}

void TutorialStateAxisPoints::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::begin ()";

  context().tutorialDlg().scene().clear ();

  m_title = createTitle (tr ("Axis Points"));
  m_background = createPixmapItem (":/engauge/img/panel_axis_points.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem (tr ("Axis points are first defined to\n"
                                "define the coordinates. Step 1 -\n"
                                "Click on the Axis Points button"),
                            QPoint (320, 60));
  m_text1 = createTextItem (tr ("Step 2 - Click on an axis or grid\n"
                                "line with known coordinates. An axis\n"
                                "point appears, with a dialog window\n"
                                "for entering the axis point\n"
                                "coordinates"),
                            QPoint (300, 210));
  m_text2 = createTextItem (tr ("Step 3 - Enter the two coordinates\n"
                                "of the axis point and then click Ok.\n"
                                "Repeat steps 2 and 3 twice more\n"
                                "until three axis points are created"),
                            QPoint (280, 320));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton (tr ("Previous"),
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_next = new TutorialButton (tr ("Next"),
                               context().tutorialDlg().scene());
  m_next->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_next->size ().width (),
                               backgroundSize.height () - buttonMargin () - m_next->size ().height ()));
  connect (m_next, SIGNAL (signalTriggered ()), this, SLOT (slotNext ()));
}

void TutorialStateAxisPoints::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::end ()";

  // It is not safe to remove and deallocate items here since an active TutorialButton
  // may be on the stack. So we clear the scene as the first step in the next begin()
}

void TutorialStateAxisPoints::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::slotNextCurves";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_SELECTION);
}

void TutorialStateAxisPoints::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_INTRODUCTION);
}
