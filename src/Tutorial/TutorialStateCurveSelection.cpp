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
#include <qmath.h>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateCurveSelection.h"
#include "TutorialStateContext.h"

TutorialStateCurveSelection::TutorialStateCurveSelection (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context),
  m_title (nullptr),
  m_background (nullptr),
  m_text0 (nullptr),
  m_text1 (nullptr),
  m_text2 (nullptr),
  m_text3 (nullptr),
  m_previous (nullptr),
  m_colorFilter (nullptr),  
  m_next (nullptr)  
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveSelection::TutorialStateCurveSelection";
}

void TutorialStateCurveSelection::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveSelection::begin ()";

  context().tutorialDlg().scene().clear ();

  m_title = createTitle ("Curve Selection");
  m_background = createPixmapItem (":/engauge/img/panel_curve_selection.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem (tr ("After the axis points have been created, a\n"
                                "curve is selected to receive curve points.\n"
                                "Step 1 - click on Curve, Point Match, Color\n"
                                "Picker or Segment Fill buttons."),
                            QPoint (250, 40));
  m_text1 = createTextItem (tr ("Step 2 - Select the desired curve name. If\n"
                                "that curve name has not been created yet,\n"
                                "use the menu option Settings / Curve Names\n"
                                "to create it."),
                            QPoint (250, 120));
  m_text2 = createTextItem (tr ("Step 3 - Change the background from the\n"
                                "original image to the filtered image\n"
                                "produced for the current curve, using the\n"
                                "menu option View / Background / Filtered\n"
                                "Image. This filtering enables the powerful\n"
                                "automated algorithms discussed later in\n"
                                "the tutorial."),
                            QPoint (250, 200));
  m_text3 = createTextItem (tr ("If the current curve is no longer visible\n"
                                "in the filtered image, then change the\n"
                                "current Color Filter settings. In the figure,\n"
                                "the orange points have disappeared."),
                            QPoint (250, 330));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton (tr ("Previous"),
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_colorFilter = new TutorialButton (tr ("Color Filter Settings"),
                                      context().tutorialDlg().scene());
  m_colorFilter->setGeometry (QPoint (qFloor (backgroundSize.width () / 2.0 - m_colorFilter->size ().width () / 2),
                                      qFloor (backgroundSize.height () - buttonMargin () - m_colorFilter->size ().height ())));
  connect (m_colorFilter, SIGNAL (signalTriggered ()), this, SLOT (slotColorFilter ()));

  m_next = new TutorialButton (tr ("Next"),
                               context().tutorialDlg().scene());
  m_next->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_next->size ().width (),
                               backgroundSize.height () - buttonMargin () - m_next->size ().height ()));
  connect (m_next, SIGNAL (signalTriggered ()), this, SLOT (slotNext ()));
}

void TutorialStateCurveSelection::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveSelection::end ()";

  // It is not safe to remove and deallocate items here since an active TutorialButton
  // may be on the stack. So we clear the scene as the first step in the next begin()
}

void TutorialStateCurveSelection::slotColorFilter ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveSelection::slotColorFilter";

  context().requestDelayedStateTransition (TUTORIAL_STATE_COLOR_FILTER);
}

void TutorialStateCurveSelection::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveSelection::slotNextCurves";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}

void TutorialStateCurveSelection::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveSelection::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_AXIS_POINTS);
}
