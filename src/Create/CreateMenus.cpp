/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateMenus.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QMenu>
#include <QMenuBar>

CreateMenus::CreateMenus()
{
}

void CreateMenus::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateMenus::create";

  mw.m_menuFile = mw.menuBar()->addMenu(tr("&File"));
  mw.m_menuFile->addAction (mw.m_actionImport);
  mw.m_menuFile->addAction (mw.m_actionImportAdvanced);
  mw.m_menuFile->addAction (mw.m_actionImportImageReplace);
  mw.m_menuFile->addAction (mw.m_actionOpen);
#if !defined(OSX_DEBUG) && !defined(OSX_RELEASE)
  mw.m_menuFileOpenRecent = new QMenu (tr ("Open &Recent"));
  for (unsigned int i = 0; i < MAX_RECENT_FILE_LIST_SIZE; i++) {
    mw.m_menuFileOpenRecent->addAction (mw.m_actionRecentFiles.at (i));
  }
  mw.m_menuFile->addMenu (mw.m_menuFileOpenRecent);
#endif
  mw.m_menuFile->addAction (mw.m_actionClose);
  mw.m_menuFile->insertSeparator (mw.m_actionSave);
  mw.m_menuFile->addAction (mw.m_actionSave);
  mw.m_menuFile->addAction (mw.m_actionSaveAs);
  mw.m_menuFile->addAction (mw.m_actionExport);
  mw.m_menuFile->insertSeparator (mw.m_actionPrint);
  mw.m_menuFile->addAction (mw.m_actionPrint);
  mw.m_menuFile->insertSeparator (mw.m_actionExit);
  mw.m_menuFile->addAction (mw.m_actionExit);

  mw.m_menuEdit = mw.menuBar()->addMenu(tr("&Edit"));
  connect (mw.m_menuEdit, SIGNAL (aboutToShow ()), &mw, SLOT (slotEditMenu ()));
  mw.m_menuEdit->addAction (mw.m_actionEditUndo);
  mw.m_menuEdit->addAction (mw.m_actionEditRedo);
  mw.m_menuEdit->insertSeparator (mw.m_actionEditCut);
  mw.m_menuEdit->addAction (mw.m_actionEditCut);
  mw.m_menuEdit->addAction (mw.m_actionEditCopy);
  mw.m_menuEdit->addAction (mw.m_actionEditPaste);
  mw.m_menuEdit->addAction (mw.m_actionEditDelete);
  mw.m_menuEdit->insertSeparator (mw.m_actionEditPasteAsNew);
  mw.m_menuEdit->addAction (mw.m_actionEditPasteAsNew);
  mw.m_menuEdit->addAction (mw.m_actionEditPasteAsNewAdvanced);

  mw.m_menuDigitize = mw.menuBar()->addMenu(tr("Digitize"));
  mw.m_menuDigitize->addAction (mw.m_actionDigitizeSelect);
  mw.m_menuDigitize->addAction (mw.m_actionDigitizeAxis);
  mw.m_menuDigitize->addAction (mw.m_actionDigitizeScale);
  mw.m_menuDigitize->addAction (mw.m_actionDigitizeCurve);
  mw.m_menuDigitize->addAction (mw.m_actionDigitizePointMatch);
  mw.m_menuDigitize->addAction (mw.m_actionDigitizeColorPicker);
  mw.m_menuDigitize->addAction (mw.m_actionDigitizeSegment);

  mw.m_menuView = mw.menuBar()->addMenu(tr("View"));
  mw.m_menuView->addAction (mw.m_actionViewBackground);
  mw.m_menuView->addAction (mw.m_actionViewDigitize);
  mw.m_menuView->addAction (mw.m_actionViewChecklistGuide);
  mw.m_menuView->addAction (mw.m_actionViewFittingWindow);
  mw.m_menuView->addAction (mw.m_actionViewGeometryWindow);
  mw.m_menuView->addAction (mw.m_actionViewSettingsViews);
  mw.m_menuView->addAction (mw.m_actionViewCoordSystem);
  mw.m_menuView->insertSeparator (mw.m_actionViewToolTips);
  mw.m_menuView->addAction (mw.m_actionViewToolTips);
  mw.m_menuView->addAction (mw.m_actionViewGridLines);
  mw.m_menuView->insertSeparator (mw.m_actionViewBackgroundNone);
  mw.m_menuViewBackground = new QMenu (tr ("Background"));
  mw.m_menuViewBackground->addAction (mw.m_actionViewBackgroundNone);
  mw.m_menuViewBackground->addAction (mw.m_actionViewBackgroundOriginal);
  mw.m_menuViewBackground->addAction (mw.m_actionViewBackgroundFiltered);
  mw.m_menuView->addMenu (mw.m_menuViewBackground);
  mw.m_menuViewCurves = new QMenu (tr ("Curves"));
  mw.m_menuViewCurves->addAction (mw.m_actionViewCurvesNone);
  mw.m_menuViewCurves->addAction (mw.m_actionViewCurvesSelected);
  mw.m_menuViewCurves->addAction (mw.m_actionViewCurvesAll);
  mw.m_menuView->addMenu (mw.m_menuViewCurves);
  mw.m_menuViewStatus = new QMenu (tr ("Status Bar"));
  mw.m_menuViewStatus->addAction (mw.m_actionStatusNever);
  mw.m_menuViewStatus->addAction (mw.m_actionStatusTemporary);
  mw.m_menuViewStatus->addAction (mw.m_actionStatusAlways);
  mw.m_menuView->addMenu (mw.m_menuViewStatus);
  mw.m_menuViewZoom = new QMenu (tr ("Zoom"));
  mw.m_menuViewZoom->addAction (mw.m_actionZoomOut);
  mw.m_menuViewZoom->addAction (mw.m_actionZoomIn);
  mw.m_menuViewZoom->insertSeparator (mw.m_actionZoom16To1);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom16To1);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom16To1Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom8To1Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom8To1);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom8To1Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom4To1Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom4To1);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom4To1Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom2To1Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom2To1);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom2To1Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To1Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To1);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To1Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To2Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To2);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To2Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To4Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To4);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To4Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To8Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To8);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To8Farther);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To16Closer);
  mw.m_menuViewZoom->addAction (mw.m_actionZoom1To16);
  mw.m_menuViewZoom->addAction (mw.m_actionZoomFill);
  mw.m_menuView->addMenu (mw.m_menuViewZoom);

  mw.m_menuSettings = mw.menuBar()->addMenu(tr ("Settings"));
  mw.m_menuSettings->addAction (mw.m_actionSettingsCoords);
  mw.m_menuSettings->addAction (mw.m_actionSettingsCurveAddRemove);
  mw.m_menuSettings->addAction (mw.m_actionSettingsCurveProperties);
  mw.m_menuSettings->addAction (mw.m_actionSettingsDigitizeCurve);
  mw.m_menuSettings->addAction (mw.m_actionSettingsExport);
  mw.m_menuSettings->addAction (mw.m_actionSettingsColorFilter);
  mw.m_menuSettings->addAction (mw.m_actionSettingsAxesChecker);
  mw.m_menuSettings->addAction (mw.m_actionSettingsGridDisplay);
  mw.m_menuSettings->addAction (mw.m_actionSettingsGridRemoval);
  mw.m_menuSettings->addAction (mw.m_actionSettingsPointMatch);
  mw.m_menuSettings->addAction (mw.m_actionSettingsSegments);
  mw.m_menuSettings->insertSeparator (mw.m_actionSettingsGeneral);
  mw.m_menuSettings->addAction (mw.m_actionSettingsGeneral);
  mw.m_menuSettings->addAction (mw.m_actionSettingsMainWindow);

  mw.m_menuHelp = mw.menuBar()->addMenu(tr("&Help"));
  mw.m_menuHelp->addAction (mw.m_actionHelpChecklistGuideWizard);
  mw.m_menuHelp->insertSeparator(mw.m_actionHelpWhatsThis);
  mw.m_menuHelp->addAction (mw.m_actionHelpWhatsThis);
  mw.m_menuHelp->addAction (mw.m_actionHelpTutorial);
#if !defined(OSX_DEBUG) && !defined(OSX_RELEASE)
  mw.m_menuHelp->addAction (mw.m_actionHelpHelp);
#endif
  mw.m_menuHelp->addAction (mw.m_actionHelpAbout);

  mw.updateRecentFileList();
}
