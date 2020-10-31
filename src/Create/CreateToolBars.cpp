/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateToolBars.h"
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

  createToolbarBackground (mw);
  createToolbarDigitize (mw);
  createToolbarSettingsView (mw);
  createToolbarCoordinateSystem (mw);
  createToolbarGuidelines (mw);
}

void CreateToolBars::createToolbarBackground (MainWindow &mw)
{
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
}

void CreateToolBars::createToolbarCoordinateSystem (MainWindow &mw)
{
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

void CreateToolBars::createToolbarDigitize (MainWindow &mw)
{
  mw.m_cmbCurve = new QComboBox ();
  mw.m_cmbCurve->setEnabled (false);
  mw.m_cmbCurve->setMinimumWidth (180);
  mw.m_cmbCurve->setStatusTip (tr ("Select curve for new points."));
  mw.m_cmbCurve->setWhatsThis (tr ("Selected Curve Name\n\n"
                                   "Select curve for any new points. Every point belongs to one curve.\n\n"
                                   "This can be changed while in Curve Point, Point Match, Color Picker or Segment Fill mode."));
  connect (mw.m_cmbCurve, SIGNAL (activated (int)), &mw, SLOT (slotCmbCurve (int))); // activated() ignores code changes
  
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
}

void CreateToolBars::createToolbarGuidelines (MainWindow &mw)
{

  QString statusTipR (tr ("Create an R (range) guideline."));
  QString statusTipT (tr ("Create a T (theta) guideline."));
  QString statusTipX (tr ("Create an X guideline."));
  QString statusTipY (tr ("Create a Y guideline."));

  QString whatsThisR (tr ("Create an R (Range) guideline\n\n"
                          "When pressed, a constant R (range) guideline is created. It can be moved by dragging, and "
                          "removed by dragging off screen"));
  QString whatsThisT (tr ("Create a T (Theta) guideline\n\n"
                          "When pressed, a constant T (theta) guideline is created. It can be moved by dragging, and "
                          "removed by dragging off screen"));
  QString whatsThisX (tr ("Create an X guideline\n\n"
                          "When pressed, a constant X guideline is created. It can be moved by dragging, and "
                          "removed by dragging off screen"));
  QString whatsThisY (tr ("Create a Y guideline\n\n"
                          "When pressed, a constant Y guideline is created. It can be moved by dragging, and "
                          "removed by dragging off screen"));

  mw.m_btnGuidelineXTCartesian = new QPushButton (QIcon(":/engauge/img/icon_guidelinesx.png"), "");
  mw.m_btnGuidelineXTCartesian->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);
  mw.m_btnGuidelineXTCartesian->setAcceptDrops (false);
  mw.m_btnGuidelineXTCartesian->setStatusTip (statusTipX);
  mw.m_btnGuidelineXTCartesian->setToolTip (tr ("Create an X guideline"));
  mw.m_btnGuidelineXTCartesian->setWhatsThis (whatsThisX);
  connect (mw.m_btnGuidelineXTCartesian, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineXT ()));

  mw.m_btnGuidelineXTPolar = new QPushButton (QIcon(":/engauge/img/icon_guidelinest.png"), "");
  mw.m_btnGuidelineXTPolar->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);
  mw.m_btnGuidelineXTPolar->setAcceptDrops (false);
  mw.m_btnGuidelineXTPolar->setStatusTip (statusTipT);
  mw.m_btnGuidelineXTPolar->setToolTip (tr ("Create a T (theta) guideline"));
  mw.m_btnGuidelineXTPolar->setWhatsThis (whatsThisT);
  connect (mw.m_btnGuidelineXTPolar, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineXT ()));

  mw.m_btnGuidelineYRCartesian = new QPushButton (QIcon(":/engauge/img/icon_guidelinesy.png"), "");
  mw.m_btnGuidelineYRCartesian->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);
  mw.m_btnGuidelineYRCartesian->setAcceptDrops (false);
  mw.m_btnGuidelineYRCartesian->setStatusTip (statusTipY);
  mw.m_btnGuidelineYRCartesian->setToolTip (tr ("Create a Y guideline"));
  mw.m_btnGuidelineYRCartesian->setWhatsThis (whatsThisY);
  connect (mw.m_btnGuidelineYRCartesian, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineYR ()));

  mw.m_btnGuidelineYRPolar = new QPushButton (QIcon(":/engauge/img/icon_guidelinesr.png"), "");
  mw.m_btnGuidelineYRPolar->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);
  mw.m_btnGuidelineYRPolar->setAcceptDrops (false);
  mw.m_btnGuidelineYRPolar->setStatusTip (statusTipR);
  mw.m_btnGuidelineYRPolar->setToolTip (tr ("Create an R (range) guideline"));
  mw.m_btnGuidelineYRPolar->setWhatsThis (whatsThisR);
  connect (mw.m_btnGuidelineYRPolar, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineYR ()));

  mw.m_toolGuidelines = new QToolBar (tr ("Guidelines"), &mw);
  mw.m_actionGuidelineXTCartesian = mw.m_toolGuidelines->addWidget (mw.m_btnGuidelineXTCartesian);
  mw.m_actionGuidelineXTPolar = mw.m_toolGuidelines->addWidget (mw.m_btnGuidelineXTPolar);
  mw.m_actionGuidelineYRCartesian = mw.m_toolGuidelines->addWidget (mw.m_btnGuidelineYRCartesian);
  mw.m_actionGuidelineYRPolar = mw.m_toolGuidelines->addWidget (mw.m_btnGuidelineYRPolar);
  mw.addToolBar (mw.m_toolGuidelines);
}

void CreateToolBars::createToolbarSettingsView (MainWindow &mw)
{
  const int VIEW_SIZE = 22;

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

  mw.m_toolSettingsViews = new QToolBar (tr ("Views"), &mw);
  mw.m_toolSettingsViews->addWidget (mw.m_viewPointStyle);
  mw.m_toolSettingsViews->addWidget (new QLabel (" ")); // A hack, but this works to put some space between the adjacent widgets
  mw.m_toolSettingsViews->addWidget (mw.m_viewSegmentFilter);
  mw.addToolBar (mw.m_toolSettingsViews);
}
