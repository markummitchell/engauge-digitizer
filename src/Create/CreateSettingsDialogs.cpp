/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateSettingsDialogs.h"
#include "DlgSettingsAxesChecker.h"
#include "DlgSettingsColorFilter.h"
#include "DlgSettingsCoords.h"
#include "DlgSettingsCurveList.h"
#include "DlgSettingsCurveProperties.h"
#include "DlgSettingsDigitizeCurve.h"
#include "DlgSettingsExportFormat.h"
#include "DlgSettingsGeneral.h"
#include "DlgSettingsGridDisplay.h"
#include "DlgSettingsGridRemoval.h"
#include "DlgSettingsMainWindow.h"
#include "DlgSettingsPointMatch.h"
#include "DlgSettingsSegments.h"
#include "Logger.h"
#include "MainWindow.h"

CreateSettingsDialogs::CreateSettingsDialogs()
{
}

void CreateSettingsDialogs::create (MainWindow & mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateSettingsDialogs::create";

  mw.m_dlgSettingsCoords = new DlgSettingsCoords (mw);
  mw.m_dlgSettingsCurveList = new DlgSettingsCurveList (mw);
  mw.m_dlgSettingsCurveProperties = new DlgSettingsCurveProperties (mw);
  mw.m_dlgSettingsDigitizeCurve = new DlgSettingsDigitizeCurve (mw);
  mw.m_dlgSettingsExportFormat = new DlgSettingsExportFormat (mw);
  mw.m_dlgSettingsColorFilter = new DlgSettingsColorFilter (mw);
  mw.m_dlgSettingsAxesChecker = new DlgSettingsAxesChecker (mw);
  mw.m_dlgSettingsGridDisplay = new DlgSettingsGridDisplay (mw);
  mw.m_dlgSettingsGridRemoval = new DlgSettingsGridRemoval (mw);
  mw.m_dlgSettingsPointMatch = new DlgSettingsPointMatch (mw);
  mw.m_dlgSettingsSegments = new DlgSettingsSegments (mw);
  mw.m_dlgSettingsGeneral = new DlgSettingsGeneral (mw);
  mw.m_dlgSettingsMainWindow = new DlgSettingsMainWindow (mw);

  mw.m_dlgSettingsCoords->setVisible (false);
  mw.m_dlgSettingsCurveList->setVisible (false);
  mw.m_dlgSettingsCurveProperties->setVisible (false);
  mw.m_dlgSettingsDigitizeCurve->setVisible (false);
  mw.m_dlgSettingsExportFormat->setVisible (false);
  mw.m_dlgSettingsColorFilter->setVisible (false);
  mw.m_dlgSettingsAxesChecker->setVisible (false);
  mw.m_dlgSettingsGridDisplay->setVisible (false);
  mw.m_dlgSettingsGridRemoval->setVisible (false);
  mw.m_dlgSettingsPointMatch->setVisible (false);
  mw.m_dlgSettingsSegments->setVisible (false);
  mw.m_dlgSettingsGeneral->setVisible (false);
  mw.m_dlgSettingsMainWindow->setVisible (false);
}
