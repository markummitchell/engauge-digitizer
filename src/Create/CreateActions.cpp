/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateActions.h"
#include "DigitAxis.xpm"
#include "DigitColorPicker.xpm"
#include "DigitCurve.xpm"
#include "DigitPointMatch.xpm"
#include "DigitScale.xpm"
#include "DigitSegment.xpm"
#include "DigitSelect.xpm"
#include "Logger.h"
#include "MainWindow.h"
#include <QAction>
#include <QIcon>
#include <QPixmap>
#include <QSignalMapper>
#include <QWhatsThis>

CreateActions::CreateActions()
{
}

void CreateActions::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::create";

  createFile (mw);
  createEdit (mw);
  createDigitize (mw);
  createView (mw);
  createSettings (mw);
  createHelp (mw);
}

void CreateActions::createDigitize (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::createDigitize";

  QPixmap pixmapAxis (DigitAxis_xpm);
  QPixmap pixmapCurve (DigitCurve_xpm);
  QPixmap pixmapColorPicker (DigitColorPicker_xpm);
  QPixmap pixmapPointMatch (DigitPointMatch_xpm);
  QPixmap pixmapScale (DigitScale_xpm);
  QPixmap pixmapSegment (DigitSegment_xpm);
  QPixmap pixmapSelect (DigitSelect_xpm);

  QIcon iconAxis (pixmapAxis);
  QIcon iconCurve (pixmapCurve);
  QIcon iconColorPicker (pixmapColorPicker);
  QIcon iconPointMatch (pixmapPointMatch);
  QIcon iconScale (pixmapScale);
  QIcon iconSegment (pixmapSegment);
  QIcon iconSelect (pixmapSelect);

  mw.m_actionDigitizeSelect = new QAction (iconSelect, tr ("Select Tool"), &mw);
  mw.m_actionDigitizeSelect->setShortcut (QKeySequence (tr ("Shift+F2")));
  mw.m_actionDigitizeSelect->setCheckable (true);
  mw.m_actionDigitizeSelect->setStatusTip (tr ("Select points on screen."));
  mw.m_actionDigitizeSelect->setWhatsThis (tr ("Select\n\n"
                                               "Select points on the screen."));
  connect (mw.m_actionDigitizeSelect, SIGNAL (triggered ()), &mw, SLOT (slotDigitizeSelect ()));

  mw.m_actionDigitizeAxis = new QAction (iconAxis, tr ("Axis Point Tool"), &mw);
  mw.m_actionDigitizeAxis->setShortcut (QKeySequence (tr ("Shift+F3")));
  mw.m_actionDigitizeAxis->setCheckable (true);
  mw.m_actionDigitizeAxis->setStatusTip (tr ("Digitize axis points for a graph."));
  mw.m_actionDigitizeAxis->setWhatsThis (tr ("Digitize Axis Point\n\n"
                                             "Digitizes an axis point for a graph by placing a new point at the cursor "
                                             "after a mouse click. The coordinates of the axis point are then "
                                             "entered. After Import and Import (Advanced), three axis points with "
                                             "(X1,Y1) (X2,Y2) (X3,Y3) coordinates can be digitized to define the graph coordinates. "
                                             "Optionally, after Import (Advanced) four axis points with "
                                             "(X1) (X2) (Y3) (Y4) coordinates can be digitized to define the graph coordinates.\n\n"
                                             "This tool is disabled when a complete set of axis points has been defined, or "
                                             "after Import (Advanced) if Scale Bar is selected."));
  connect (mw.m_actionDigitizeAxis, SIGNAL (triggered ()), &mw, SLOT (slotDigitizeAxis ()));

  mw.m_actionDigitizeScale = new QAction (iconScale, tr ("Scale Bar Tool"), &mw);
  mw.m_actionDigitizeScale->setShortcut (QKeySequence (tr ("Shift+F8")));
  mw.m_actionDigitizeScale->setCheckable (true);
  mw.m_actionDigitizeScale->setStatusTip (tr ("Digitize scale bar for a map. Requires Import (Advanced)."));
  mw.m_actionDigitizeScale->setWhatsThis (tr ("Digitize Scale Bar\n\n"
                                              "Digitize a scale bar for a map by clicking and dragging. The length of the "
                                              "scale bar is then entered. In a map, the two endpoints of the scale "
                                              "bar define the distances in graph coordinates.\n\n"
                                              "This tool is enabled by selecting Scale Bar in Import (Advanced).\n\n"
                                              "This tool is disabled when a scale bar has been defined, or "
                                              "if axis points were selected during import."));
  connect (mw.m_actionDigitizeScale, SIGNAL (triggered ()), &mw, SLOT (slotDigitizeScale ()));

  mw.m_actionDigitizeCurve = new QAction (iconCurve, tr ("Curve Point Tool"), &mw);
  mw.m_actionDigitizeCurve->setShortcut (QKeySequence (tr ("Shift+F4")));
  mw.m_actionDigitizeCurve->setCheckable (true);
  mw.m_actionDigitizeCurve->setStatusTip (tr ("Digitize curve points."));
  mw.m_actionDigitizeCurve->setWhatsThis (tr ("Digitize Curve Point\n\n"
                                              "Digitizes a curve point by placing a new point at the cursor "
                                              "after a mouse click. Use this mode to digitize points along curves "
                                              "one by one.\n\n"
                                              "New points will be assigned to the currently selected curve."));
  connect (mw.m_actionDigitizeCurve, SIGNAL (triggered ()), &mw, SLOT (slotDigitizeCurve ()));

  mw.m_actionDigitizePointMatch = new QAction (iconPointMatch, tr ("Point Match Tool"), &mw);
  mw.m_actionDigitizePointMatch->setShortcut (QKeySequence (tr ("Shift+F5")));
  mw.m_actionDigitizePointMatch->setCheckable (true);
  mw.m_actionDigitizePointMatch->setStatusTip (tr ("Digitize curve points in a point plot by matching a point."));
  mw.m_actionDigitizePointMatch->setWhatsThis (tr ("Digitize Curve Points by Point Matching\n\n"
                                                   "Digitizes curve points in a point plot by finding points that match a sample point. The process "
                                                   "starts by selecting a representative sample point.\n\n"
                                                   "New points will be assigned to the currently selected curve."));
  connect (mw.m_actionDigitizePointMatch, SIGNAL (triggered ()), &mw, SLOT (slotDigitizePointMatch ()));

  mw.m_actionDigitizeColorPicker = new QAction (iconColorPicker, tr ("Color Picker Tool"), &mw);
  mw.m_actionDigitizeColorPicker->setShortcut (QKeySequence (tr ("Shift+F6")));
  mw.m_actionDigitizeColorPicker->setCheckable (true);
  mw.m_actionDigitizeColorPicker->setStatusTip (tr ("Select color settings for filtering in Segment Fill mode."));
  mw.m_actionDigitizeColorPicker->setWhatsThis (tr ("Select color settings for Segment Fill filtering\n\n"
                                                    "Select a pixel along the currently selected curve. That pixel and its neighbors will "
                                                    "define the filter settings (color, brightness, and so on) of the currently selected curve "
                                                    "while in Segment Fill mode."));
  connect (mw.m_actionDigitizeColorPicker, SIGNAL (triggered ()), &mw, SLOT (slotDigitizeColorPicker ()));

  mw.m_actionDigitizeSegment = new QAction (iconSegment, tr ("Segment Fill Tool"), &mw);
  mw.m_actionDigitizeSegment->setShortcut (QKeySequence (tr ("Shift+F7")));
  mw.m_actionDigitizeSegment->setCheckable (true);
  mw.m_actionDigitizeSegment->setStatusTip (tr ("Digitize curve points along a segment of a curve."));
  mw.m_actionDigitizeSegment->setWhatsThis (tr ("Digitize Curve Points With Segment Fill\n\n"
                                                "Digitizes curve points by placing new points along the highlighted "
                                                "segment under the cursor. Use this mode to quickly digitize multiple points along a "
                                                "curve with a single click.\n\n"
                                                "New points will be assigned to the currently selected curve."));
  connect (mw.m_actionDigitizeSegment, SIGNAL (triggered ()), &mw, SLOT (slotDigitizeSegment ()));

  mw.m_groupDigitize = new QActionGroup (&mw);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizeSelect);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizeAxis);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizeScale);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizeCurve);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizePointMatch);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizeColorPicker);
  mw.m_groupDigitize->addAction (mw.m_actionDigitizeSegment);
}

void CreateActions::createEdit (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::createEdit";

  mw.m_actionEditUndo = new QAction(tr ("&Undo"), &mw);
  mw.m_actionEditUndo->setShortcut (QKeySequence::Undo);
  mw.m_actionEditUndo->setStatusTip (tr ("Undo the last operation."));
  mw.m_actionEditUndo->setWhatsThis (tr ("Undo\n\n"
                                         "Undo the last operation."));
  // connect is applied when CmdMediator appears

  mw.m_actionEditRedo = new QAction(tr ("&Redo"), &mw);
  mw.m_actionEditRedo->setShortcut (QKeySequence::Redo);
  mw.m_actionEditRedo->setStatusTip (tr ("Redo the last operation."));
  mw.m_actionEditRedo->setWhatsThis (tr ("Redo\n\n"
                                         "Redo the last operation."));
  // connect is applied when CmdMediator appears

  mw.m_actionEditCut = new QAction (tr ("Cut"), &mw);
  mw.m_actionEditCut->setShortcut (QKeySequence::Cut);
  mw.m_actionEditCut->setStatusTip (tr ("Cuts the selected points and copies them to the clipboard."));
  mw.m_actionEditCut->setWhatsThis (tr ("Cut\n\n"
                                        "Cuts the selected points and copies them to the clipboard."));
  connect (mw.m_actionEditCut, SIGNAL (triggered ()), &mw, SLOT (slotEditCut ()));

  mw.m_actionEditCopy = new QAction (tr ("Copy"), &mw);
  mw.m_actionEditCopy->setShortcut (QKeySequence::Copy);
  mw.m_actionEditCopy->setStatusTip (tr ("Copies the selected points to the clipboard."));
  mw.m_actionEditCopy->setWhatsThis (tr ("Copy\n\n"
                                         "Copies the selected points to the clipboard."));
  connect (mw.m_actionEditCopy, SIGNAL (triggered ()), &mw, SLOT (slotEditCopy ()));

  mw.m_actionEditPaste = new QAction (tr ("Paste"), &mw);
  mw.m_actionEditPaste->setShortcut (QKeySequence::Paste);
  mw.m_actionEditPaste->setStatusTip (tr ("Pastes the selected points from the clipboard."));
  mw.m_actionEditPaste->setWhatsThis (tr ("Paste\n\n"
                                          "Pastes the selected points from the clipboard. They will be assigned to the current curve."));
  connect (mw.m_actionEditPaste, SIGNAL (triggered ()), &mw, SLOT (slotEditPaste ()));

  mw.m_actionEditDelete = new QAction (tr ("Delete"), &mw);
  mw.m_actionEditDelete->setShortcut (QKeySequence::Delete);
  mw.m_actionEditDelete->setStatusTip (tr ("Deletes the selected points, after copying them to the clipboard."));
  mw.m_actionEditDelete->setWhatsThis (tr ("Delete\n\n"
                                           "Deletes the selected points, after copying them to the clipboard."));
  connect (mw.m_actionEditDelete, SIGNAL (triggered ()), &mw, SLOT (slotEditDelete ()));

  mw.m_actionEditPasteAsNew = new QAction (tr ("Paste As New"), &mw);
  mw.m_actionEditPasteAsNew->setStatusTip (tr ("Pastes an image from the clipboard."));
  mw.m_actionEditPasteAsNew->setWhatsThis (tr ("Paste as New\n\n"
                                               "Creates a new document by pasting an image from the clipboard."));
  connect (mw.m_actionEditPasteAsNew, SIGNAL (triggered ()), &mw, SLOT (slotEditPasteAsNew ()));

  mw.m_actionEditPasteAsNewAdvanced = new QAction (tr ("Paste As New (Advanced)..."), &mw);
  mw.m_actionEditPasteAsNewAdvanced->setStatusTip (tr ("Pastes an image from the clipboard, in advanced mode."));
  mw.m_actionEditPasteAsNewAdvanced->setWhatsThis (tr ("Paste as New (Advanced)\n\n"
                                                       "Creates a new document by pasting an image from the clipboard, in advanced mode."));
  connect (mw.m_actionEditPasteAsNewAdvanced, SIGNAL (triggered ()), &mw, SLOT (slotEditPasteAsNewAdvanced ()));
}

void CreateActions::createFile (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::createFile";

  mw.m_actionImport = new QAction(tr ("&Import..."), &mw);
  mw.m_actionImport->setShortcut (tr ("Ctrl+I"));
  mw.m_actionImport->setStatusTip (tr ("Creates a new document by importing a simple image."));
  mw.m_actionImport->setWhatsThis (tr ("Import Image\n\n"
                                       "Creates a new document by importing an image with a single coordinate system, "
                                       "and axes both coordinates known.\n\n"
                                       "For more complicated images with multiple coordinate systems, "
                                       "and/or floating axes, Import (Advanced) is used instead."));
  connect (mw.m_actionImport, SIGNAL (triggered ()), &mw, SLOT (slotFileImport ()));

  mw.m_actionImportAdvanced = new QAction(tr ("Import (Advanced)..."), &mw);
  mw.m_actionImportAdvanced->setStatusTip (tr ("Creates a new document by importing an image with support for advanced feaures."));
  mw.m_actionImportAdvanced->setWhatsThis (tr ("Import (Advanced)\n\n"
                                               "Creates a new document by importing an image with support for advanced feaures. In "
                                               "advanced mode, there can be multiple coordinate systems and/or floating axes."));
  connect (mw.m_actionImportAdvanced, SIGNAL (triggered ()), &mw, SLOT (slotFileImportAdvanced ()));

  mw.m_actionImportImageReplace = new QAction (tr ("Import (Image Replace)..."), &mw);
  mw.m_actionImportImageReplace->setStatusTip (tr ("Imports a new image into the current document, replacing the existing image."));
  mw.m_actionImportImageReplace->setWhatsThis (tr ("Import (Image Replace)\n\n"
                                                   "Imports a new image into the current document. The existing image is replaced, "
                                                   "and all curves in the document are preserved. This operation is useful for applying "
                                                   "the axis points and other settings from an existing document to a different image."));
  connect (mw.m_actionImportImageReplace, SIGNAL (triggered ()), &mw, SLOT (slotFileImportImageReplace ()));

  mw.m_actionOpen = new QAction(tr ("&Open..."), &mw);
  mw.m_actionOpen->setShortcut (QKeySequence::Open);
  mw.m_actionOpen->setStatusTip (tr ("Opens an existing document."));
  mw.m_actionOpen->setWhatsThis (tr ("Open Document\n\n"
                                     "Opens an existing document."));
  connect (mw.m_actionOpen, SIGNAL (triggered ()), &mw, SLOT (slotFileOpen ()));

#if !defined(OSX_DEBUG) && !defined(OSX_RELEASE)
  for (unsigned int i = 0; i < MAX_RECENT_FILE_LIST_SIZE; i++) {
    QAction *recentFileAction = new QAction (&mw);
    recentFileAction->setVisible (true);
    connect (recentFileAction, SIGNAL (triggered ()), &mw, SLOT (slotRecentFileAction ()));
    mw.m_actionRecentFiles.append (recentFileAction);
  }
#endif 

  mw.m_actionClose = new QAction(tr ("&Close"), &mw);
  mw.m_actionClose->setShortcut (QKeySequence::Close);
  mw.m_actionClose->setStatusTip (tr ("Closes the open document."));
  mw.m_actionClose->setWhatsThis (tr ("Close Document\n\n"
                                      "Closes the open document."));
  connect (mw.m_actionClose, SIGNAL (triggered ()), &mw, SLOT (slotFileClose ()));

  mw.m_actionSave = new QAction(tr ("&Save"), &mw);
  mw.m_actionSave->setShortcut (QKeySequence::Save);
  mw.m_actionSave->setStatusTip (tr ("Saves the current document."));
  mw.m_actionSave->setWhatsThis (tr ("Save Document\n\n"
                                     "Saves the current document."));
  connect (mw.m_actionSave, SIGNAL (triggered ()), &mw, SLOT (slotFileSave ()));

  mw.m_actionSaveAs = new QAction(tr ("Save As..."), &mw);
  mw.m_actionSaveAs->setShortcut (QKeySequence::SaveAs);
  mw.m_actionSaveAs->setStatusTip (tr ("Saves the current document under a new filename."));
  mw.m_actionSaveAs->setWhatsThis (tr ("Save Document As\n\n"
                                       "Saves the current document under a new filename."));
  connect (mw.m_actionSaveAs, SIGNAL (triggered ()), &mw, SLOT (slotFileSaveAs ()));

  mw.m_actionExport = new QAction (tr ("Export..."), &mw);
  mw.m_actionExport->setShortcut (tr ("Ctrl+E"));
  mw.m_actionExport->setStatusTip (tr ("Exports the current document into a text file."));
  mw.m_actionExport->setWhatsThis (tr ("Export Document\n\n"
                                       "Exports the current document into a text file."));
  connect (mw.m_actionExport, SIGNAL (triggered ()), &mw, SLOT (slotFileExport ()));

  mw.m_actionPrint = new QAction (tr ("&Print..."), &mw);
  mw.m_actionPrint->setShortcut (QKeySequence::Print);
  mw.m_actionPrint->setStatusTip (tr ("Print the current document."));
  mw.m_actionPrint->setWhatsThis (tr ("Print Document\n\n"
                                      "Print the current document to a printer or file."));
  connect (mw.m_actionPrint, SIGNAL (triggered ()), &mw, SLOT (slotFilePrint ()));

  mw.m_actionExit = new QAction(tr ("&Exit"), &mw);
  mw.m_actionExit->setShortcut (QKeySequence::Quit);
  mw.m_actionExit->setStatusTip (tr ("Quits the application."));
  mw.m_actionExit->setWhatsThis (tr ("Exit\n\n"
                                     "Quits the application."));
  connect (mw.m_actionExit, SIGNAL (triggered ()), &mw, SLOT (close ()));
}

void CreateActions::createHelp (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::createHelp";

  mw.m_actionHelpChecklistGuideWizard = new QAction (tr ("Checklist Guide Wizard"), &mw);
  mw.m_actionHelpChecklistGuideWizard->setCheckable (true);
  mw.m_actionHelpChecklistGuideWizard->setStatusTip (tr ("Open Checklist Guide Wizard during import to define digitizing steps"));
  mw.m_actionHelpChecklistGuideWizard->setWhatsThis (tr ("Checklist Guide Wizard\n\n"
                                                         "Use Checklist Guide Wizard during import to generate a checklist of steps "
                                                         "for the imported document"));

  mw.m_actionHelpWhatsThis = QWhatsThis::createAction(&mw);
  mw.m_actionHelpWhatsThis->setShortcut (QKeySequence::WhatsThis);

  mw.m_actionHelpTutorial = new QAction (tr ("Tutorial"), &mw);
  mw.m_actionHelpTutorial->setStatusTip (tr ("Play tutorial showing steps for digitizing curves"));
  mw.m_actionHelpTutorial->setWhatsThis (tr ("Tutorial\n\n"
                                             "Play tutorial showing steps for digitizing points from curves drawn with lines "
                                             "and/or point"));
  connect (mw.m_actionHelpTutorial, SIGNAL (triggered ()), &mw, SLOT (slotHelpTutorial()));

#if !defined(OSX_DEBUG) && !defined(OSX_RELEASE)
  mw.m_actionHelpHelp = new QAction (tr ("Help"), &mw);
  mw.m_actionHelpHelp->setShortcut (QKeySequence::HelpContents);
  mw.m_actionHelpHelp->setStatusTip (tr ("Help documentation"));
  mw.m_actionHelpHelp->setWhatsThis (tr ("Help Documentation\n\n"
                                         "Searchable help documentation"));
  // This action gets connected directly to the QDockWidget when that is created
#endif

  mw.m_actionHelpAbout = new QAction(tr ("About Engauge"), &mw);
  mw.m_actionHelpAbout->setStatusTip (tr ("About the application."));
  mw.m_actionHelpAbout->setWhatsThis (tr ("About Engauge\n\nAbout the application."));
  connect (mw.m_actionHelpAbout, SIGNAL (triggered ()), &mw, SLOT (slotHelpAbout ()));
}

void CreateActions::createSettings (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::createSettings";

  mw.m_actionSettingsCoords = new QAction (tr ("Coordinates..."), &mw);
  mw.m_actionSettingsCoords->setStatusTip (tr ("Edit Coordinate settings."));
  mw.m_actionSettingsCoords->setWhatsThis (tr ("Coordinate Settings\n\n"
                                               "Coordinate settings determine how the graph coordinates are mapped to the pixels in the image"));
  connect (mw.m_actionSettingsCoords, SIGNAL (triggered ()), &mw, SLOT (slotSettingsCoords ()));

  mw.m_actionSettingsCurveList = new QAction (tr ("Curve List..."), &mw);
  mw.m_actionSettingsCurveList->setStatusTip (tr ("Edit Curve List settings."));
  mw.m_actionSettingsCurveList->setWhatsThis (tr ("Curve List\n\n"
                                                  "Curve list settings add, rename and/or remove curves in the current document"));
  connect (mw.m_actionSettingsCurveList, SIGNAL (triggered ()), &mw, SLOT (slotSettingsCurveList ()));

  mw.m_actionSettingsCurveProperties = new QAction (tr ("Curve Properties..."), &mw);
  mw.m_actionSettingsCurveProperties->setStatusTip (tr ("Edit Curve Properties settings."));
  mw.m_actionSettingsCurveProperties->setWhatsThis (tr ("Curve Properties Settings\n\n"
                                                        "Curves properties settings determine how each curve appears"));
  connect (mw.m_actionSettingsCurveProperties, SIGNAL (triggered ()), &mw, SLOT (slotSettingsCurveProperties ()));

  mw.m_actionSettingsDigitizeCurve = new QAction (tr ("Digitize Curve..."), &mw);
  mw.m_actionSettingsDigitizeCurve->setStatusTip (tr ("Edit Digitize Axis and Graph Curve settings."));
  mw.m_actionSettingsDigitizeCurve->setWhatsThis (tr ("Digitize Axis and Graph Curve Settings\n\n"
                                                      "Digitize Curve settings determine how points are digitized in Digitize Axis Point and "
                                                      "Digitize Graph Point modes"));
  connect (mw.m_actionSettingsDigitizeCurve, SIGNAL (triggered ()), &mw, SLOT (slotSettingsDigitizeCurve ()));

  mw.m_actionSettingsExport = new QAction (tr ("Export Format..."), &mw);
  mw.m_actionSettingsExport->setStatusTip (tr ("Edit Export Format settings."));
  mw.m_actionSettingsExport->setWhatsThis (tr ("Export Format Settings\n\n"
                                               "Export format settings affect how exported files are formatted"));
  connect (mw.m_actionSettingsExport, SIGNAL (triggered ()), &mw, SLOT (slotSettingsExportFormat ()));

  mw.m_actionSettingsColorFilter = new QAction (tr ("Color Filter..."), &mw);
  mw.m_actionSettingsColorFilter->setStatusTip (tr ("Edit Color Filter settings."));
  mw.m_actionSettingsColorFilter->setWhatsThis (tr ("Color Filter Settings\n\n"
                                                    "Color filtering simplifies the graphs for easier Point Matching and Segment Filling"));
  connect (mw.m_actionSettingsColorFilter, SIGNAL (triggered ()), &mw, SLOT (slotSettingsColorFilter ()));

  mw.m_actionSettingsAxesChecker = new QAction (tr ("Axes Checker..."), &mw);
  mw.m_actionSettingsAxesChecker->setStatusTip (tr ("Edit Axes Checker settings."));
  mw.m_actionSettingsAxesChecker->setWhatsThis (tr ("Axes Checker Settings\n\n"
                                                    "Axes checker can reveal any axis point mistakes, which are otherwise hard to find."));
  connect (mw.m_actionSettingsAxesChecker, SIGNAL (triggered ()), &mw, SLOT (slotSettingsAxesChecker ()));

  mw.m_actionSettingsGridDisplay = new QAction (tr ("Grid Line Display..."), &mw);
  mw.m_actionSettingsGridDisplay->setStatusTip (tr ("Edit Grid Line Display settings."));
  mw.m_actionSettingsGridDisplay->setWhatsThis (tr ("Grid Line Display Settings\n\n"
                                                    "Grid lines displayed on the graph can provide more accuracy than the Axis Checker, for distorted graphs. "
                                                    "In a distorted graph, the grid lines can be used to adjust the axis points for more accuracy in different regions."));
  connect (mw.m_actionSettingsGridDisplay, SIGNAL (triggered ()), &mw, SLOT (slotSettingsGridDisplay ()));

  mw.m_actionSettingsGridRemoval = new QAction (tr ("Grid Line Removal..."), &mw);
  mw.m_actionSettingsGridRemoval->setStatusTip (tr ("Edit Grid Line Removal settings."));
  mw.m_actionSettingsGridRemoval->setWhatsThis (tr ("Grid Line Removal Settings\n\n"
                                                    "Grid line removal isolates curve lines for easier Point Matching and Segment Filling, when "
                                                    "Color Filtering is not able to separate grid lines from curve lines."));
  connect (mw.m_actionSettingsGridRemoval, SIGNAL (triggered ()), &mw, SLOT (slotSettingsGridRemoval ()));

  mw.m_actionSettingsPointMatch = new QAction (tr ("Point Match..."), &mw);
  mw.m_actionSettingsPointMatch->setStatusTip (tr ("Edit Point Match settings."));
  mw.m_actionSettingsPointMatch->setWhatsThis (tr ("Point Match Settings\n\n"
                                                   "Point match settings determine how points are matched while in Point Match mode"));
  connect (mw.m_actionSettingsPointMatch, SIGNAL (triggered ()), &mw, SLOT (slotSettingsPointMatch ()));

  mw.m_actionSettingsSegments = new QAction (tr ("Segment Fill..."), &mw);
  mw.m_actionSettingsSegments->setStatusTip (tr ("Edit Segment Fill settings."));
  mw.m_actionSettingsSegments->setWhatsThis (tr ("Segment Fill Settings\n\n"
                                                 "Segment fill settings determine how points are generated in the Segment Fill mode"));
  connect (mw.m_actionSettingsSegments, SIGNAL (triggered ()), &mw, SLOT (slotSettingsSegments ()));

  mw.m_actionSettingsGeneral = new QAction (tr ("General..."), &mw);
  mw.m_actionSettingsGeneral->setStatusTip (tr ("Edit General settings."));
  mw.m_actionSettingsGeneral->setWhatsThis (tr ("General Settings\n\n"
                                                "General settings are document-specific settings that affect multiple modes. For example, the cursor size setting affects "
                                                "both Color Picker and Point Match modes"));
  connect (mw.m_actionSettingsGeneral, SIGNAL (triggered ()), &mw, SLOT (slotSettingsGeneral ()));

  mw.m_actionSettingsMainWindow = new QAction (tr ("Main Window..."), &mw);
  mw.m_actionSettingsMainWindow->setEnabled (true);
  mw.m_actionSettingsMainWindow->setStatusTip (tr ("Edit Main Window settings."));
  mw.m_actionSettingsMainWindow->setWhatsThis (tr ("Main Window Settings\n\n"
                                                   "Main window settings affect the user interface and are not specific to any document"));
  connect (mw.m_actionSettingsMainWindow, SIGNAL (triggered ()), &mw, SLOT (slotSettingsMainWindow ()));
}

void CreateActions::createView (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateActions::createView";

  mw.m_actionViewBackground = new QAction (tr ("Background Toolbar"), &mw);
  mw.m_actionViewBackground->setCheckable (true);
  mw.m_actionViewBackground->setChecked (true);
  mw.m_actionViewBackground->setStatusTip (tr ("Show or hide the background toolbar."));
  mw.m_actionViewBackground->setWhatsThis (tr ("View Background ToolBar\n\n"
                                               "Show or hide the background toolbar"));
  connect (mw.m_actionViewBackground, SIGNAL (triggered ()), &mw, SLOT (slotViewToolBarBackground ()));

  mw.m_actionViewChecklistGuide = new QAction (tr ("Checklist Guide Toolbar"), &mw);
  mw.m_actionViewChecklistGuide->setCheckable (true);
  mw.m_actionViewChecklistGuide->setChecked (false);
  mw.m_actionViewChecklistGuide->setStatusTip (tr ("Show or hide the checklist guide."));
  mw.m_actionViewChecklistGuide->setWhatsThis (tr ("View Checklist Guide\n\n"
                                                   "Show or hide the checklist guide"));
  connect (mw.m_actionViewChecklistGuide, SIGNAL (changed ()), &mw, SLOT (slotViewToolBarChecklistGuide()));

  mw.m_actionViewFittingWindow = new QAction (tr ("Curve Fitting Window"), &mw);
  mw.m_actionViewFittingWindow->setCheckable (true);
  mw.m_actionViewFittingWindow->setChecked (false);
  mw.m_actionViewFittingWindow->setStatusTip (tr ("Show or hide the curve fitting window."));
  mw.m_actionViewFittingWindow->setWhatsThis (tr ("View Curve Fitting Window\n\n"
                                                  "Show or hide the curve fitting window"));
  connect (mw.m_actionViewFittingWindow, SIGNAL (changed ()), &mw, SLOT (slotViewToolBarFittingWindow()));

  mw.m_actionViewGeometryWindow = new QAction (tr ("Geometry Window"), &mw);
  mw.m_actionViewGeometryWindow->setCheckable (true);
  mw.m_actionViewGeometryWindow->setChecked (false);
  mw.m_actionViewGeometryWindow->setStatusTip (tr ("Show or hide the geometry window."));
  mw.m_actionViewGeometryWindow->setWhatsThis (tr ("View Geometry Window\n\n"
                                                   "Show or hide the geometry window"));
  connect (mw.m_actionViewGeometryWindow, SIGNAL (changed ()), &mw, SLOT (slotViewToolBarGeometryWindow()));

  mw.m_actionViewDigitize = new QAction (tr ("Digitizing Tools Toolbar"), &mw);
  mw.m_actionViewDigitize->setCheckable (true);
  mw.m_actionViewDigitize->setChecked (true);
  mw.m_actionViewDigitize->setStatusTip (tr ("Show or hide the digitizing tools toolbar."));
  mw.m_actionViewDigitize->setWhatsThis (tr ("View Digitizing Tools ToolBar\n\n"
                                             "Show or hide the digitizing tools toolbar"));
  connect (mw.m_actionViewDigitize, SIGNAL (triggered ()), &mw, SLOT (slotViewToolBarDigitize()));

  mw.m_actionViewSettingsViews = new QAction (tr ("Settings Views Toolbar"), &mw);
  mw.m_actionViewSettingsViews->setCheckable (true);
  mw.m_actionViewSettingsViews->setChecked (true);
  mw.m_actionViewSettingsViews->setStatusTip (tr ("Show or hide the settings views toolbar."));
  mw.m_actionViewSettingsViews->setWhatsThis (tr ("View Settings Views ToolBar\n\n"
                                                  "Show or hide the settings views toolbar. These views graphically show the "
                                                  "most important settings."));
  connect (mw.m_actionViewSettingsViews, SIGNAL (triggered ()), &mw, SLOT (slotViewToolBarSettingsViews()));

  mw.m_actionViewCoordSystem = new QAction (tr ("Coordinate System Toolbar"), &mw);
  mw.m_actionViewCoordSystem->setCheckable (true);
  mw.m_actionViewCoordSystem->setChecked (false);
  mw.m_actionViewCoordSystem->setStatusTip (tr ("Show or hide the coordinate system toolbar."));
  mw.m_actionViewCoordSystem->setWhatsThis (tr ("View Coordinate Systems ToolBar\n\n"
                                                "Show or hide the coordinate system selection toolbar. This toolbar is used "
                                                "to select the current coordinate system when the document has multiple "
                                                "coordinate systems. This toolbar is also used to view and print all coordinate "
                                                "systems.\n\n"
                                                "This toolbar is disabled when there is only one coordinate system."));
  connect (mw.m_actionViewCoordSystem, SIGNAL (triggered ()), &mw, SLOT (slotViewToolBarCoordSystem()));

  mw.m_actionViewToolTips = new QAction (tr ("Tool Tips"), &mw);
  mw.m_actionViewToolTips->setCheckable (true);
  mw.m_actionViewToolTips->setChecked (true);
  mw.m_actionViewToolTips->setStatusTip (tr ("Show or hide the tool tips."));
  mw.m_actionViewToolTips->setWhatsThis (tr ("View Tool Tips\n\n"
                                             "Show or hide the tool tips"));
  connect (mw.m_actionViewToolTips, SIGNAL (triggered ()), &mw, SLOT (slotViewToolTips()));

  mw.m_actionViewGridLines = new QAction (tr ("Grid Lines"), &mw);
  mw.m_actionViewGridLines->setCheckable (true);
  mw.m_actionViewGridLines->setChecked (false);
  mw.m_actionViewGridLines->setStatusTip (tr ("Show or hide grid lines."));
  mw.m_actionViewGridLines->setWhatsThis (tr ("View Grid Lines\n\n"
                                              "Show or hide grid lines that are added for accurate adjustments of the axes points, "
                                              "which can improve accuracy in distorted graphs"));
  connect (mw.m_actionViewGridLines, SIGNAL (triggered ()), &mw, SLOT (slotViewGridLines()));

  mw.m_actionViewBackgroundNone = new QAction (tr ("No Background"), &mw);
  mw.m_actionViewBackgroundNone->setCheckable (true);
  mw.m_actionViewBackgroundNone->setStatusTip (tr ("Do not show the image underneath the points."));
  mw.m_actionViewBackgroundNone->setWhatsThis (tr ("No Background\n\n"
                                                   "No image is shown so points are easier to see"));

  mw.m_actionViewBackgroundOriginal = new QAction (tr ("Show Original Image"), &mw);
  mw.m_actionViewBackgroundOriginal->setCheckable (true);
  mw.m_actionViewBackgroundOriginal->setStatusTip (tr ("Show the original image underneath the points."));
  mw.m_actionViewBackgroundOriginal->setWhatsThis (tr ("Show Original Image\n\n"
                                                       "Show the original image underneath the points"));

  mw.m_actionViewBackgroundFiltered = new QAction (tr ("Show Filtered Image"), &mw);
  mw.m_actionViewBackgroundFiltered->setCheckable (true);
  mw.m_actionViewBackgroundFiltered->setChecked (true);
  mw.m_actionViewBackgroundFiltered->setStatusTip (tr ("Show the filtered image underneath the points."));
  mw.m_actionViewBackgroundFiltered->setWhatsThis (tr ("Show Filtered Image\n\n"
                                                       "Show the filtered image underneath the points.\n\n"
                                                       "The filtered image is created from the original image according to the "
                                                       "Filter preferences so unimportant information is hidden and important "
                                                       "information is emphasized"));

  mw.m_groupBackground = new QActionGroup(&mw);
  mw.m_groupBackground->addAction (mw.m_actionViewBackgroundNone);
  mw.m_groupBackground->addAction (mw.m_actionViewBackgroundOriginal);
  mw.m_groupBackground->addAction (mw.m_actionViewBackgroundFiltered);
  connect (mw.m_groupBackground, SIGNAL(triggered (QAction*)), &mw, SLOT (slotViewGroupBackground(QAction*)));

  mw.m_actionViewCurvesNone = new QAction (tr ("Hide All Curves"), &mw);
  mw.m_actionViewCurvesNone->setCheckable (true);
  mw.m_actionViewCurvesNone->setStatusTip (tr ("Hide all digitized curves."));
  mw.m_actionViewCurvesNone->setWhatsThis (tr ("Hide All Curves\n\n"
                                               "No axis points or digitized graph curves are shown so the image is easier to see."));

  mw.m_actionViewCurvesSelected = new QAction (tr ("Show Selected Curve"), &mw);
  mw.m_actionViewCurvesSelected->setCheckable (true);
  mw.m_actionViewCurvesSelected->setStatusTip (tr ("Show only the currently selected curve."));
  mw.m_actionViewCurvesSelected->setWhatsThis (tr ("Show Selected Curve\n\n"
                                                   "Show only the digitized points and line that belong to the currently selected curve."));

  mw.m_actionViewCurvesAll = new QAction (tr ("Show All Curves"), &mw);
  mw.m_actionViewCurvesAll->setCheckable (true);
  mw.m_actionViewCurvesAll->setChecked (true);
  mw.m_actionViewCurvesAll->setStatusTip (tr ("Show all curves."));
  mw.m_actionViewCurvesAll->setWhatsThis (tr ("Show All Curves\n\n"
                                              "Show all digitized axis points and graph curves"));

  mw.m_groupCurves = new QActionGroup(&mw);
  mw.m_groupCurves->addAction (mw.m_actionViewCurvesNone);
  mw.m_groupCurves->addAction (mw.m_actionViewCurvesSelected);
  mw.m_groupCurves->addAction (mw.m_actionViewCurvesAll);
  connect (mw.m_groupCurves, SIGNAL(triggered (QAction*)), &mw, SLOT (slotViewGroupCurves(QAction*)));

  mw.m_actionViewGuidelinesHide = new QAction (tr ("Hide Guidelines"), &mw);
  mw.m_actionViewGuidelinesHide->setCheckable (true);
  mw.m_actionViewGuidelinesHide->setChecked (true);
  mw.m_actionViewGuidelinesHide->setStatusTip (tr ("Hide guidelines."));
  mw.m_actionViewGuidelinesHide->setWhatsThis (tr ("Hide Guidelines\n\n"
                                                   "Guidelines are hidden to simplify the main window."));

  mw.m_actionViewGuidelinesEdit = new QAction (tr ("Edit Guidelines"), &mw);
  mw.m_actionViewGuidelinesEdit->setCheckable (true);
  mw.m_actionViewGuidelinesEdit->setStatusTip (tr ("Edit guidelines."));
  mw.m_actionViewGuidelinesEdit->setWhatsThis (tr ("Edit Guidelines\n\n"
                                                   "Add new guidelines by clicking on the guidelines toolbar, move "
                                                   "existing guidelines by dragging, or remove guidelines by dragging "
                                                   "out of the main window."));

  mw.m_actionViewGuidelinesLock = new QAction (tr ("Lock Guidelines"), &mw);
  mw.m_actionViewGuidelinesLock->setCheckable (true);
  mw.m_actionViewGuidelinesLock->setStatusTip (tr ("Lock guidelines."));
  mw.m_actionViewGuidelinesLock->setWhatsThis (tr ("Lock Guidelines\n\n"
                                                   "Lock the guidelines to prevent accidental movement or removal."));

  mw.m_groupGuidelines = new QActionGroup(&mw);
  mw.m_groupGuidelines->addAction (mw.m_actionViewGuidelinesHide);
  mw.m_groupGuidelines->addAction (mw.m_actionViewGuidelinesEdit);
  mw.m_groupGuidelines->addAction (mw.m_actionViewGuidelinesLock);
  connect (mw.m_groupGuidelines, SIGNAL (triggered (QAction*)), &mw, SLOT (slotViewGroupGuidelines(QAction*)));

  mw.m_actionStatusNever = new QAction (tr ("Hide Always"), &mw);
  mw.m_actionStatusNever->setCheckable(true);
  mw.m_actionStatusNever->setStatusTip (tr ("Always hide the status bar."));
  mw.m_actionStatusNever->setWhatsThis (tr ("Hide the status bar. No temporary status or feedback messages will appear."));

  mw.m_actionStatusTemporary = new QAction (tr ("Show Temporary Messages"), &mw);
  mw.m_actionStatusTemporary->setCheckable(true);
  mw.m_actionStatusTemporary->setStatusTip (tr ("Hide the status bar except when display temporary messages."));
  mw.m_actionStatusTemporary->setWhatsThis (tr ("Hide the status bar, except when displaying temporary status and feedback messages."));

  mw.m_actionStatusAlways = new QAction (tr ("Show Always"), &mw);
  mw.m_actionStatusAlways->setCheckable(true);
  mw.m_actionStatusAlways->setStatusTip (tr ("Always show the status bar."));
  mw.m_actionStatusAlways->setWhatsThis (tr ("Show the status bar. Besides displaying temporary status and feedback messages, "
                                             "the status bar also displays information about the cursor position."));

  mw.m_groupStatus = new QActionGroup(&mw);
  mw.m_groupStatus->addAction (mw.m_actionStatusNever);
  mw.m_groupStatus->addAction (mw.m_actionStatusTemporary);
  mw.m_groupStatus->addAction (mw.m_actionStatusAlways);
  connect (mw.m_groupStatus, SIGNAL (triggered (QAction*)), &mw, SLOT (slotViewGroupStatus(QAction*)));

  mw.m_actionZoomOut = new QAction (tr ("Zoom Out"), &mw);
  mw.m_actionZoomOut->setStatusTip (tr ("Zoom out"));
  // setShortCut is called by updateSettingsCreateActions
  connect (mw.m_actionZoomOut, SIGNAL (triggered ()), &mw, SLOT (slotViewZoomOut ()));

  mw.m_actionZoomIn = new QAction (tr ("Zoom In"), &mw);
  mw.m_actionZoomIn->setStatusTip (tr ("Zoom in"));
  // setShortCut is called by updateSettingsCreateActions
  connect (mw.m_actionZoomIn, SIGNAL (triggered ()), &mw, SLOT (slotViewZoomIn ()));

  mw.m_mapperZoomFactor = new QSignalMapper (&mw);
  connect (mw.m_mapperZoomFactor, SIGNAL (mapped (int)), &mw, SLOT (slotViewZoomFactorInt (int)));

  mw.m_actionZoom16To1 = new QAction (tr ("16:1 (1600%)"), &mw);
  mw.m_actionZoom16To1->setCheckable (true);
  mw.m_actionZoom16To1->setStatusTip (tr ("Zoom 16:1"));
  connect (mw.m_actionZoom16To1, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom16To1, ZOOM_16_TO_1);

  mw.m_actionZoom16To1Farther = new QAction (tr ("16:1 farther (1270%)"), &mw);
  mw.m_actionZoom16To1Farther->setCheckable (true);
  mw.m_actionZoom16To1Farther->setStatusTip (tr ("Zoom 12.7:1"));
  connect (mw.m_actionZoom16To1Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom16To1Farther, ZOOM_16_TO_1_FARTHER);

  mw.m_actionZoom8To1Closer = new QAction (tr ("8:1 closer (1008%)"), &mw);
  mw.m_actionZoom8To1Closer->setCheckable (true);
  mw.m_actionZoom8To1Closer->setStatusTip (tr ("Zoom 10.08:1"));
  connect (mw.m_actionZoom8To1Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom8To1Closer, ZOOM_8_TO_1_CLOSER);

  mw.m_actionZoom8To1 = new QAction (tr ("8:1 (800%)"), &mw);
  mw.m_actionZoom8To1->setCheckable (true);
  mw.m_actionZoom8To1->setStatusTip (tr ("Zoom 8:1"));
  connect (mw.m_actionZoom8To1, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom8To1, ZOOM_8_TO_1);

  mw.m_actionZoom8To1Farther = new QAction (tr ("8:1 farther (635%)"), &mw);
  mw.m_actionZoom8To1Farther->setCheckable (true);
  mw.m_actionZoom8To1Farther->setStatusTip (tr ("Zoom 6.35:1"));
  connect (mw.m_actionZoom8To1Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom8To1Farther, ZOOM_8_TO_1_FARTHER);

  mw.m_actionZoom4To1Closer = new QAction (tr ("4:1 closer (504%)"), &mw);
  mw.m_actionZoom4To1Closer->setCheckable (true);
  mw.m_actionZoom4To1Closer->setStatusTip (tr ("Zoom 5.04:1"));
  connect (mw.m_actionZoom4To1Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom4To1Closer, ZOOM_4_TO_1_CLOSER);

  mw.m_actionZoom4To1 = new QAction (tr ("4:1 (400%)"), &mw);
  mw.m_actionZoom4To1->setCheckable (true);
  mw.m_actionZoom4To1->setStatusTip (tr ("Zoom 4:1"));
  connect (mw.m_actionZoom4To1, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom4To1, ZOOM_4_TO_1);

  mw.m_actionZoom4To1Farther = new QAction (tr ("4:1 farther (317%)"), &mw);
  mw.m_actionZoom4To1Farther->setCheckable (true);
  mw.m_actionZoom4To1Farther->setStatusTip (tr ("Zoom 3.17:1"));
  connect (mw.m_actionZoom4To1Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom4To1Farther, ZOOM_4_TO_1_FARTHER);

  mw.m_actionZoom2To1Closer = new QAction (tr ("2:1 closer (252%)"), &mw);
  mw.m_actionZoom2To1Closer->setCheckable (true);
  mw.m_actionZoom2To1Closer->setStatusTip (tr ("Zoom 2.52:1"));
  connect (mw.m_actionZoom2To1Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom2To1Closer, ZOOM_2_TO_1_CLOSER);

  mw.m_actionZoom2To1 = new QAction (tr ("2:1 (200%)"), &mw);
  mw.m_actionZoom2To1->setCheckable (true);
  mw.m_actionZoom2To1->setStatusTip (tr ("Zoom 2:1"));
  connect (mw.m_actionZoom2To1, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom2To1, ZOOM_2_TO_1);

  mw.m_actionZoom2To1Farther = new QAction (tr ("2:1 farther (159%)"), &mw);
  mw.m_actionZoom2To1Farther->setCheckable (true);
  mw.m_actionZoom2To1Farther->setStatusTip (tr ("Zoom 1.59:1"));
  connect (mw.m_actionZoom2To1Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom2To1Farther, ZOOM_2_TO_1_FARTHER);

  mw.m_actionZoom1To1Closer = new QAction (tr ("1:1 closer (126%)"), &mw);
  mw.m_actionZoom1To1Closer->setCheckable (true);
  mw.m_actionZoom1To1Closer->setChecked (true);
  mw.m_actionZoom1To1Closer->setStatusTip (tr ("Zoom 1.3:1"));
  connect (mw.m_actionZoom1To1Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To1Closer, ZOOM_1_TO_1_CLOSER);

  mw.m_actionZoom1To1 = new QAction (tr ("1:1 (100%)"), &mw);
  mw.m_actionZoom1To1->setCheckable (true);
  mw.m_actionZoom1To1->setChecked (true);
  mw.m_actionZoom1To1->setStatusTip (tr ("Zoom 1:1"));
  connect (mw.m_actionZoom1To1, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To1, ZOOM_1_TO_1);

  mw.m_actionZoom1To1Farther = new QAction (tr ("1:1 farther (79%)"), &mw);
  mw.m_actionZoom1To1Farther->setCheckable (true);
  mw.m_actionZoom1To1Farther->setChecked (true);
  mw.m_actionZoom1To1Farther->setStatusTip (tr ("Zoom 0.8:1"));
  connect (mw.m_actionZoom1To1Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To1Farther, ZOOM_1_TO_1_FARTHER);

  mw.m_actionZoom1To2Closer = new QAction (tr ("1:2 closer (63%)"), &mw);
  mw.m_actionZoom1To2Closer->setCheckable (true);
  mw.m_actionZoom1To2Closer->setStatusTip (tr ("Zoom 1.3:2"));
  connect (mw.m_actionZoom1To2Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To2Closer, ZOOM_1_TO_2_CLOSER);

  mw.m_actionZoom1To2 = new QAction (tr ("1:2 (50%)"), &mw);
  mw.m_actionZoom1To2->setCheckable (true);
  mw.m_actionZoom1To2->setStatusTip (tr ("Zoom 1:2"));
  connect (mw.m_actionZoom1To2, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To2, ZOOM_1_TO_2);

  mw.m_actionZoom1To2Farther = new QAction (tr ("1:2 farther (40%)"), &mw);
  mw.m_actionZoom1To2Farther->setCheckable (true);
  mw.m_actionZoom1To2Farther->setStatusTip (tr ("Zoom 0.8:2"));
  connect (mw.m_actionZoom1To2Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To2Farther, ZOOM_1_TO_2_FARTHER);

  mw.m_actionZoom1To4Closer = new QAction (tr ("1:4 closer (31%)"), &mw);
  mw.m_actionZoom1To4Closer->setCheckable (true);
  mw.m_actionZoom1To4Closer->setStatusTip (tr ("Zoom 1.3:4"));
  connect (mw.m_actionZoom1To4Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To4Closer, ZOOM_1_TO_4_CLOSER);

  mw.m_actionZoom1To4 = new QAction (tr ("1:4 (25%)"), &mw);
  mw.m_actionZoom1To4->setCheckable (true);
  mw.m_actionZoom1To4->setStatusTip (tr ("Zoom 1:4"));
  connect (mw.m_actionZoom1To4, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To4, ZOOM_1_TO_4);

  mw.m_actionZoom1To4Farther = new QAction (tr ("1:4 farther (20%)"), &mw);
  mw.m_actionZoom1To4Farther->setCheckable (true);
  mw.m_actionZoom1To4Farther->setStatusTip (tr ("Zoom 0.8:4"));
  connect (mw.m_actionZoom1To4Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To4Farther, ZOOM_1_TO_4_FARTHER);

  mw.m_actionZoom1To8Closer = new QAction (tr ("1:8 closer (12.5%)"), &mw);
  mw.m_actionZoom1To8Closer->setCheckable (true);
  mw.m_actionZoom1To8Closer->setStatusTip (tr ("Zoom 1:8"));
  connect (mw.m_actionZoom1To8Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To8Closer, ZOOM_1_TO_8_CLOSER);

  mw.m_actionZoom1To8 = new QAction (tr ("1:8 (12.5%)"), &mw);
  mw.m_actionZoom1To8->setCheckable (true);
  mw.m_actionZoom1To8->setStatusTip (tr ("Zoom 1:8"));
  connect (mw.m_actionZoom1To8, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To8, ZOOM_1_TO_8);

  mw.m_actionZoom1To8Farther = new QAction (tr ("1:8 farther (10%)"), &mw);
  mw.m_actionZoom1To8Farther->setCheckable (true);
  mw.m_actionZoom1To8Farther->setStatusTip (tr ("Zoom 0.8:8"));
  connect (mw.m_actionZoom1To8Farther, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To8Farther, ZOOM_1_TO_8_FARTHER);

  mw.m_actionZoom1To16Closer = new QAction (tr ("1:16 closer (8%)"), &mw);
  mw.m_actionZoom1To16Closer->setCheckable (true);
  mw.m_actionZoom1To16Closer->setStatusTip (tr ("Zoom 1.3:16"));
  connect (mw.m_actionZoom1To16Closer, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To16Closer, ZOOM_1_TO_16_CLOSER);

  mw.m_actionZoom1To16 = new QAction (tr ("1:16 (6.25%)"), &mw);
  mw.m_actionZoom1To16->setCheckable (true);
  mw.m_actionZoom1To16->setStatusTip (tr ("Zoom 1:16"));
  connect (mw.m_actionZoom1To16, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoom1To16, ZOOM_1_TO_16);

  mw.m_actionZoomFill = new QAction (tr ("Fill"), &mw);
  mw.m_actionZoomFill->setCheckable (true);
  mw.m_actionZoomFill->setStatusTip (tr ("Zoom with stretching to fill window"));
  connect (mw.m_actionZoomFill, SIGNAL (triggered ()), mw.m_mapperZoomFactor, SLOT (map ()));
  mw.m_mapperZoomFactor->setMapping (mw.m_actionZoomFill, ZOOM_FILL);

  mw.m_groupZoom = new QActionGroup (&mw);
  mw.m_groupZoom->addAction (mw.m_actionZoom16To1);
  mw.m_groupZoom->addAction (mw.m_actionZoom16To1Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom8To1Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom8To1);
  mw.m_groupZoom->addAction (mw.m_actionZoom8To1Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom4To1Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom4To1);
  mw.m_groupZoom->addAction (mw.m_actionZoom4To1Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom2To1Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom2To1);
  mw.m_groupZoom->addAction (mw.m_actionZoom2To1Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To1Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To1);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To1Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To2Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To2);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To2Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To4Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To4);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To4Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To8Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To8);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To8Farther);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To16Closer);
  mw.m_groupZoom->addAction (mw.m_actionZoom1To16);
  mw.m_groupZoom->addAction (mw.m_actionZoomFill);
}
