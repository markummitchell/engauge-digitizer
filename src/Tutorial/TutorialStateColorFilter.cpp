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
#include "TutorialStateColorFilter.h"
#include "TutorialStateContext.h"

TutorialStateColorFilter::TutorialStateColorFilter (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context),
  m_title (nullptr),
  m_background (nullptr),
  m_text0 (nullptr),
  m_text1 (nullptr),
  m_text2 (nullptr),
  m_text3 (nullptr),
  m_text4 (nullptr),
  m_back (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::TutorialStateColorFilter";
}

void TutorialStateColorFilter::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::begin ()";

  context().tutorialDlg().scene().clear ();

  m_title = createTitle (tr ("Color Filter"));
  m_background = createPixmapItem (":/engauge/img/panel_color_filter.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem (tr ("Each curve has Color Filter settings that\n"
                                "are applied in Segment Fill mode. For\n"
                                "black lines the defaults work well, but for\n"
                                "colored lines the settings can be improved."),
                            QPoint (260, 30));
  m_text1 = createTextItem (tr ("Step 1 - Select the Settings / Color\n"
                                "Filter menu option."),
                            QPoint (285, 115));
  m_text2 = createTextItem (tr ("Step 2 - Select the curve that will\n"
                                "be given the new settings."),
                            QPoint (285, 165));
  m_text3 = createTextItem (tr ("Step 3 - Select the mode. Intensity is\n"
                                "suggested for uncolored lines, and Hue\n"
                                "is suggested for colored lines."),
                            QPoint (285, 210));
  m_text4 = createTextItem (tr ("Step 4 - Adjust the included range by\n"
                                "dragging the green handles, until the\n"
                                "curve is clear in the preview window\n"
                                "below. The graph shows a histogram\n"
                                "distribution of the values underneath.\n"
                                "Click Ok when finished."),
                            QPoint (285, 280));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_back = new TutorialButton (tr ("Back"),
                               context().tutorialDlg().scene());
  m_back->setGeometry (QPoint (backgroundSize.width () / 2 - m_back->size().width () / 2,
                               backgroundSize.height() - buttonMargin() - m_back->size().height()));
  connect (m_back, SIGNAL (signalTriggered ()), this, SLOT (slotBack ()));
}

void TutorialStateColorFilter::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::end ()";

  // It is not safe to remove and deallocate items here since an active TutorialButton
  // may be on the stack. So we clear the scene as the first step in the next begin()
}

void TutorialStateColorFilter::slotBack ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::slotBack";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_SELECTION);
}
