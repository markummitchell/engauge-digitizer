/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistGuide.h"
#include "CreateDockableWidgets.h"
#include "FittingWindow.h"
#include "GeometryWindow.h"
#include "Logger.h"
#include "MainWindow.h"

CreateDockableWidgets::CreateDockableWidgets()
{
}

void CreateDockableWidgets::create (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateDockableWidgets::create";

  // Checklist guide starts out hidden. It will be positioned in settingsRead
  mw.m_dockChecklistGuide = new ChecklistGuide (&mw);
  connect (mw.m_dockChecklistGuide, SIGNAL (signalChecklistClosed()), &mw, SLOT (slotChecklistClosed()));

  // Fitting window starts out hidden since there is nothing to show initially. It will be positioned in settingsRead
  mw.m_dockFittingWindow = new FittingWindow (&mw);
  connect (mw.m_dockFittingWindow, SIGNAL (signalFittingWindowClosed()),
           &mw, SLOT (slotFittingWindowClosed()));
  connect (mw.m_dockFittingWindow, SIGNAL (signalCurveFit(FittingCurveCoefficients, double, double, bool, bool)),
           &mw, SLOT (slotFittingWindowCurveFit(FittingCurveCoefficients, double, double, bool, bool)));

  // Geometry window starts out hidden since there is nothing to show initially. It will be positioned in settingsRead
  mw.m_dockGeometryWindow = new GeometryWindow (&mw);
  connect (mw.m_dockGeometryWindow, SIGNAL (signalGeometryWindowClosed()),
           &mw, SLOT (slotGeometryWindowClosed()));

}
