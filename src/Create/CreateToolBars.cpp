/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateToolBars.h"
#include "DlgSettingsAxesChecker.h"
#include "DlgSettingsColorFilter.h"
#include "DlgSettingsCoords.h"
#include "DlgSettingsCurveAddRemove.h"
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
#include <QComboBox>
#include <QPushButton>
#include <QToolBar>
#include "ViewPointStyle.h"
#include "ViewSegmentFilter.h"

CreateToolBars::CreateToolBars()
{
}

void CreateToolBars::create (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateToolBars::create";

  const int VIEW_SIZE = 22;

  // Background toolbar widgets
  mw.m_cmbBackground = new QComboBox ();
  mw.m_cmbBackground->setEnabled (false);
  mw.m_cmbBackground->setStatusTip (tr ("Select background image"));
  mw.m_cmbBackground->setWhatsThis (tr ("Selected Background\n\n"
                                        "Select background image:\n"
                                        "1) No background which highlights points\n"
                                        "2) Original image which shows everything\n"
                                        "3) Filtered image which highlights important details"));
  mw.m_cmbBackground->addItem (tr ("No background"), QVariant (BACKGROUND_IMAGE_NONE));
  mw.m_cmbBackground->addItem (tr ("Original image"), QVariant (BACKGROUND_IMAGE_ORIGINAL));
  mw.m_cmbBackground->addItem (tr ("Filtered image"), QVariant (BACKGROUND_IMAGE_FILTERED));
  // selectBackgroundOriginal needs currentIndexChanged
  connect (mw.m_cmbBackground, SIGNAL (currentIndexChanged (int)), &mw, SLOT (slotCmbBackground (int)));

  // Background toolbar
  mw.m_toolBackground = new QToolBar (tr ("Background"), &mw);
  mw.m_toolBackground->addWidget (mw.m_cmbBackground);
  mw.addToolBar (mw.m_toolBackground);

  // Digitize toolbar widgets that are not created elsewhere
  mw.m_cmbCurve = new QComboBox ();
  mw.m_cmbCurve->setEnabled (false);
  mw.m_cmbCurve->setMinimumWidth (180);
  mw.m_cmbCurve->setStatusTip (tr ("Select curve for new points."));
  mw.m_cmbCurve->setWhatsThis (tr ("Selected Curve Name\n\n"
                                   "Select curve for any new points. Every point belongs to one curve.\n\n"
                                   "This can be changed while in Curve Point, Point Match, Color Picker or Segment Fill mode."));
  connect (mw.m_cmbCurve, SIGNAL (activated (int)), &mw, SLOT (slotCmbCurve (int))); // activated() ignores code changes

  // Digitize toolbar
  mw.m_toolDigitize = new QToolBar (tr ("Drawing"), &mw);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizeSelect);
  mw.m_toolDigitize->insertSeparator (mw.m_actionDigitizeAxis);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizeAxis);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizeScale);
  mw.m_toolDigitize->insertSeparator (mw.m_actionDigitizeCurve);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizeCurve);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizePointMatch);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizeColorPicker);
  mw.m_toolDigitize->addAction (mw.m_actionDigitizeSegment);
  mw.m_toolDigitize->addWidget (mw.m_cmbCurve);
  mw.addToolBar (mw.m_toolDigitize);

  // Views toolbar widgets
  mw.m_viewPointStyle = new ViewPointStyle();
  mw.m_viewPointStyle->setMinimumSize(VIEW_SIZE, VIEW_SIZE);
  mw.m_viewPointStyle->setMaximumSize(VIEW_SIZE, VIEW_SIZE);
  mw.m_viewPointStyle->setStatusTip (tr ("Points style for the currently selected curve"));
  mw.m_viewPointStyle->setWhatsThis (tr ("Points Style\n\n"
                                         "Points style for the currently selected curve. The points style is only "
                                         "displayed in this toolbar. To change the points style, "
                                         "use the Curve Properties dialog."));

  mw.m_viewSegmentFilter = new ViewSegmentFilter();
  mw.m_viewSegmentFilter->setMinimumSize(VIEW_SIZE, VIEW_SIZE);
  mw.m_viewSegmentFilter->setMaximumSize(VIEW_SIZE, VIEW_SIZE);
  mw.m_viewSegmentFilter->setStatusTip (tr ("View of filter for current curve in Segment Fill mode"));
  mw.m_viewSegmentFilter->setWhatsThis (tr ("Segment Fill Filter\n\n"
                                            "View of filter for the current curve in Segment Fill mode. The filter settings are only "
                                            "displayed in this toolbar. To changed the filter settings, "
                                            "use the Color Picker mode or the Filter Settings dialog."));

  // Settings views toolbar
  mw.m_toolSettingsViews = new QToolBar (tr ("Views"), &mw);
  mw.m_toolSettingsViews->addWidget (mw.m_viewPointStyle);
  mw.m_toolSettingsViews->addWidget (new QLabel (" ")); // A hack, but this works to put some space between the adjacent widgets
  mw.m_toolSettingsViews->addWidget (mw.m_viewSegmentFilter);
  mw.addToolBar (mw.m_toolSettingsViews);

  // Coordinate system toolbar
  mw.m_cmbCoordSystem = new QComboBox;
  mw.m_cmbCoordSystem->setEnabled (false);
  mw.m_cmbCoordSystem->setStatusTip (tr ("Currently selected coordinate system"));
  mw.m_cmbCoordSystem->setWhatsThis (tr ("Selected Coordinate System\n\n"
                                         "Currently selected coordinate system. This is used to switch between coordinate systems "
                                         "in documents with multiple coordinate systems"));
  connect (mw.m_cmbCoordSystem, SIGNAL (activated (int)), &mw, SLOT (slotCmbCoordSystem (int)));

  mw.m_btnShowAll = new QPushButton(QIcon(":/engauge/img/icon_show_all.png"), "");
  mw.m_btnShowAll->setEnabled (false);
  mw.m_btnShowAll->setAcceptDrops(false);
  mw.m_btnShowAll->setStatusTip (tr ("Show all coordinate systems"));
  mw.m_btnShowAll->setWhatsThis (tr ("Show All Coordinate Systems\n\n"
                                     "When pressed and held, this button shows all digitized points and lines for all coordinate systems."));
  connect (mw.m_btnShowAll, SIGNAL (pressed ()), &mw, SLOT (slotBtnShowAllPressed ()));
  connect (mw.m_btnShowAll, SIGNAL (released ()), &mw, SLOT (slotBtnShowAllReleased ()));

  mw.m_btnPrintAll = new QPushButton(QIcon(":/engauge/img/icon_print_all.png"), "");
  mw.m_btnPrintAll->setEnabled (false);
  mw.m_btnPrintAll->setAcceptDrops(false);
  mw.m_btnPrintAll->setStatusTip (tr ("Print all coordinate systems"));
  mw.m_btnPrintAll->setWhatsThis (tr ("Print All Coordinate Systems\n\n"
                                      "When pressed, this button Prints all digitized points and lines for all coordinate systems."));
  connect (mw.m_btnPrintAll, SIGNAL (pressed ()), &mw, SLOT (slotBtnPrintAll ()));

  mw.m_toolCoordSystem = new QToolBar (tr ("Coordinate System"), &mw);
  mw.m_toolCoordSystem->addWidget (mw.m_cmbCoordSystem);
  mw.m_toolCoordSystem->addWidget (mw.m_btnShowAll);
  mw.m_toolCoordSystem->addWidget (mw.m_btnPrintAll);
  mw.addToolBar (mw.m_toolCoordSystem);
}

