/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateActions.h"
#include "CreateCentralWidget.h"
#include "CreateCommandStackShadow.h"
#include "CreateDockableWidgets.h"
#include "CreateFacade.h"
#include "CreateHelpWindow.h"
#include "CreateIcons.h"
#include "CreateLoadImage.h"
#include "CreateMenus.h"
#include "CreateNetwork.h"
#include "CreateScene.h"
#include "CreateSettingsDialogs.h"
#include "CreateStateContexts.h"
#include "CreateStatusBar.h"
#include "CreateToolBars.h"
#include "CreateTutorial.h"
#include "CreateZoomMaps.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Version.h"

CreateFacade::CreateFacade()
{
}

void CreateFacade::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateFacade::create";

  CreateActions createActions;
  CreateCentralWidget createCentralWidget;
  CreateCommandStackShadow createCommandStackShadow;
  CreateDockableWidgets createDockableWidgets;
  CreateHelpWindow createHelpWindow;
  CreateIcons createIcons;
  CreateLoadImage createLoadImage;
  CreateMenus createMenus;
  CreateNetwork createNetwork;
  CreateScene createScene;
  CreateSettingsDialogs createSettingsDialogs;
  CreateStateContexts createStateContexts;
  CreateStatusBar createStatusBar;
  CreateToolBars createToolBars;
  CreateTutorial createTutorial;
  CreateZoomMaps createZoomMaps;

  createIcons.create (mw);
#if !defined(OSX_DEBUG) && !defined(OSX_RELEASE)
  mw.setWindowFlags (Qt::WindowContextHelpButtonHint | mw.windowFlags ()); // Add help to default buttons
#endif
  mw.setWindowTitle (engaugeWindowTitle ());

  createCentralWidget.create (mw);
  createActions.create (mw);
  createStatusBar.create (mw);
  createMenus.create (mw);
  createToolBars.create (mw);
  createDockableWidgets.create (mw);
  createHelpWindow.create (mw);
  createTutorial.create (mw);
  createScene.create (mw);
  createNetwork.create (mw);
  createLoadImage.create (mw);
  createStateContexts.create (mw);
  createSettingsDialogs.create (mw);
  createCommandStackShadow.create (mw);
  createZoomMaps.create (mw);
}
