#include "img/bannerapp.xpm"
#include "CmdCopy.h"
#include "CmdCut.h"
#include "CmdDelete.h"
#include "CmdMediator.h"
#include "Curve.h"
#include "DataKey.h"
#include "DigitizeStateContext.h"
#include "img/DigitAxis.xpm"
#include "img/DigitCurve.xpm"
#include "img/DigitPointMatch.xpm"
#include "img/DigitSegment.xpm"
#include "img/DigitSelect.xpm"
#include "Dlg/DlgSettingsCoords.h"
#include "Dlg/DlgSettingsCurveProperties.h"
#include "Dlg/DlgSettingsCurves.h"
#include "Dlg/DlgSettingsExport.h"
#include "Dlg/DlgSettingsFilter.h"
#include "Dlg/DlgSettingsGridDisplay.h"
#include "Dlg/DlgSettingsGridRemoval.h"
#include "Dlg/DlgSettingsPointMatch.h"
#include "Dlg/DlgSettingsSegments.h"
#include "GraphicsItemType.h"
#include "GraphicsPointPolygon.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "LoadImageFromUrl.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QImageReader>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QSettings>
#include <QTextStream>
#include <QToolBar>
#include <QToolButton>
#include "QtToString.h"
#include <QVBoxLayout>
#include <QWhatsThis>
#include "StatusBar.h"
#include "ZoomFactor.h"

const QString EMPTY_FILENAME ("");

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_curfile (EMPTY_FILENAME),
  m_layout (0),
  m_scene (0),
  m_view (0),
  m_image (0),
  m_cmdMediator (0)
{
  const int VersionNumber = 6;

  setWindowTitle (tr ("Engauge Digitizer %1")
      .arg (VersionNumber));
  QPixmap bannerIcon (bannerapp_xpm);
  setWindowIcon (bannerIcon);

  createCentralWidget();
  createActions ();
  createStatusBar ();
  createMenus ();
  createToolBars ();
  createScene ();
  createLoadImageFromUrl ();
  createStateContext ();
  createSettingsDialogs ();
  updateControls ();

  settingsRead ();
  setCurrentFile ("");
  setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave()) {
    settingsWrite ();
    event->accept ();
  } else {
    event->ignore ();
  }
}

CmdMediator &MainWindow::cmdMediator ()
{
  Q_ASSERT (m_cmdMediator != 0);

  return *m_cmdMediator;
}

void MainWindow::createActions()
{
  createActionsFile ();
  createActionsEdit ();
  createActionsDigitize ();
  createActionsView ();
  createActionsSettings ();
  createActionsHelp ();
}

void MainWindow::createActionsDigitize ()
{
  QPixmap pixmapAxis (DigitAxis_xpm);
  QPixmap pixmapCurve (DigitCurve_xpm);
  QPixmap pixmapPointMatch (DigitPointMatch_xpm);
  QPixmap pixmapSegment (DigitSegment_xpm);
  QPixmap pixmapSelect (DigitSelect_xpm);

  QIcon iconAxis (pixmapAxis);
  QIcon iconCurve (pixmapCurve);
  QIcon iconPointMatch (pixmapPointMatch);
  QIcon iconSegment (pixmapSegment);
  QIcon iconSelect (pixmapSelect);

  m_actionDigitizeSelect = new QAction (iconSelect, tr ("Select"), this);
  m_actionDigitizeSelect->setCheckable (true);
  m_actionDigitizeSelect->setStatusTip (tr ("Select points on screen."));
  m_actionDigitizeSelect->setWhatsThis (tr ("Select\n\n"
                                            "Select points on the screen."));
  connect (m_actionDigitizeSelect, SIGNAL (triggered ()), this, SLOT (slotDigitizeSelect ()));

  m_actionDigitizeAxis = new QAction (iconAxis, tr ("Axis Point"), this);
  m_actionDigitizeAxis->setCheckable (true);
  m_actionDigitizeAxis->setStatusTip (tr ("Digitize axis points."));
  m_actionDigitizeAxis->setWhatsThis (tr ("Digitize Axis Point\n\n"
                                          "Digitizes an axis point by placing a new point at the cursor "
                                          "after a mouse click. The coordinates of the axis point are then "
                                          "entered. In a graph, three axis points are required to define "
                                          "the graph coordinates."));
  connect (m_actionDigitizeAxis, SIGNAL (triggered ()), this, SLOT (slotDigitizeAxis ()));

  m_actionDigitizeCurve = new QAction (iconCurve, tr ("Curve Point"), this);
  m_actionDigitizeCurve->setCheckable (true);
  m_actionDigitizeCurve->setStatusTip (tr ("Digitize curve points."));
  m_actionDigitizeCurve->setWhatsThis (tr ("Digitize Curve Point\n\n"
                                           "Digitizes a curve point by placing a new point at the cursor "
                                           "after a mouse click. Use this mode to digitize points along curves "
                                           "one by one.\n\n"
                                           "New points will be assigned to the currently selected curve."));
  connect (m_actionDigitizeCurve, SIGNAL (triggered ()), this, SLOT (slotDigitizeCurve ()));

  m_actionDigitizePointMatch = new QAction (iconPointMatch, tr ("Point Match"), this);
  m_actionDigitizePointMatch->setCheckable (true);
  m_actionDigitizePointMatch->setStatusTip (tr ("Digitize points along a segment of a curve."));
  m_actionDigitizePointMatch->setWhatsThis (tr ("Digitize Segment Fill\n\n"
                                             "Digitizes a curve or segment by placing points along the "
                                             "segment under the cursor. Use this mode to quickly digitize multiple points along a "
                                             "curve with a single click.\n\n"
                                             "New points will be assigned to the currently selected curve."));
  connect (m_actionDigitizePointMatch, SIGNAL (triggered ()), this, SLOT (slotDigitizePointMatch ()));

  m_actionDigitizeSegment = new QAction (iconSegment, tr ("Segment Points"), this);
  m_actionDigitizeSegment->setCheckable (true);
  m_actionDigitizeSegment->setStatusTip (tr ("Digitize curve points in a point plot by matching a point."));
  m_actionDigitizeSegment->setWhatsThis (tr ("Digitize Curve Points by Point Matching\n\n"
                                             "Digitizes curve points in a point plot by finding points that match a sample point. The process "
                                             "starts by selecting a representative sample point.\n\n"
                                             "New points will be assigned to the currently selected curve."));
  connect (m_actionDigitizeSegment, SIGNAL (triggered ()), this, SLOT (slotDigitizeSegment ()));

  m_groupDigitize = new QActionGroup (this);
  m_groupDigitize->addAction (m_actionDigitizeSelect);
  m_groupDigitize->addAction (m_actionDigitizeAxis);
  m_groupDigitize->addAction (m_actionDigitizeCurve);
  m_groupDigitize->addAction (m_actionDigitizePointMatch);
  m_groupDigitize->addAction (m_actionDigitizeSegment);
}

void MainWindow::createActionsEdit ()
{
  m_actionEditUndo = new QAction(tr ("&Undo"), this);
  m_actionEditUndo->setShortcut (QKeySequence::Undo);
  m_actionEditUndo->setStatusTip (tr ("Undo the last operation."));
  m_actionEditUndo->setWhatsThis (tr ("Undo\n\n"
                                      "Undo the last operation."));
  // connect is applied when CmdMediator appears

  m_actionEditRedo = new QAction(tr ("&Redo"), this);
  m_actionEditRedo->setShortcut (QKeySequence::Redo);
  m_actionEditRedo->setStatusTip (tr ("Redo the last operation."));
  m_actionEditRedo->setWhatsThis (tr ("Redo\n\n"
                                      "Redo the last operation."));
  // connect is applied when CmdMediator appears

  m_actionEditCut = new QAction (tr ("Cut"), this);
  m_actionEditCut->setShortcut (QKeySequence::Cut);
  m_actionEditCut->setStatusTip (tr ("Cuts the selected points and copies them to the clipboard."));
  m_actionEditCut->setWhatsThis (tr ("Cut\n\n"
                                     "Cuts the selected points and copies them to the clipboard."));
  connect (m_actionEditCut, SIGNAL (triggered ()), this, SLOT (slotEditCut ()));

  m_actionEditCopy = new QAction (tr ("Copy"), this);
  m_actionEditCopy->setShortcut (QKeySequence::Copy);
  m_actionEditCopy->setStatusTip (tr ("Copies the selected points to the clipboard."));
  m_actionEditCopy->setWhatsThis (tr ("Copy\n\n"
                                     "Copies the selected points to the clipboard."));
  connect (m_actionEditCopy, SIGNAL (triggered ()), this, SLOT (slotEditCopy ()));

  m_actionEditPaste = new QAction (tr ("Paste"), this);
  m_actionEditPaste->setShortcut (QKeySequence::Paste);
  m_actionEditPaste->setStatusTip (tr ("Pastes the selected points from the clipboard."));
  m_actionEditPaste->setWhatsThis (tr ("Paste\n\n"
                                       "Pastes the selected points from the clipboard. They will be assigned to the current curve."));
  connect (m_actionEditPaste, SIGNAL (triggered ()), this, SLOT (slotEditPaste ()));

  m_actionEditDelete = new QAction (tr ("Delete"), this);
  m_actionEditDelete->setShortcut (QKeySequence::Delete);
  m_actionEditDelete->setStatusTip (tr ("Deletes the selected points, after copying them to the clipboard."));
  m_actionEditDelete->setWhatsThis (tr ("Delete\n\n"
                                        "Deletes the selected points, after copying them to the clipboard."));
  connect (m_actionEditDelete, SIGNAL (triggered ()), this, SLOT (slotEditDelete ()));
}

void MainWindow::createActionsFile ()
{
  m_actionImport = new QAction(tr ("&Import"), this);
  m_actionImport->setShortcut (tr ("Ctrl+I"));
  m_actionImport->setStatusTip (tr ("Creates a new document by importing an image."));
  m_actionImport->setWhatsThis (tr ("New Document\n\n"
                                    "Creates a new document by importing an image."));
  connect (m_actionImport, SIGNAL (triggered ()), this, SLOT (slotFileImport ()));

  m_actionOpen = new QAction(tr ("&Open"), this);
  m_actionOpen->setShortcut (QKeySequence::Open);
  m_actionOpen->setStatusTip (tr ("Opens an existing document."));
  m_actionOpen->setWhatsThis (tr ("Open Document\n\n"
                                  "Opens an existing document."));
  connect (m_actionOpen, SIGNAL (triggered ()), this, SLOT (slotFileOpen ()));

  m_actionSave = new QAction(tr ("&Save"), this);
  m_actionSave->setShortcut (QKeySequence::Save);
  m_actionSave->setStatusTip (tr ("Saves the current document."));
  m_actionSave->setWhatsThis (tr ("Save Document\n\n"
                                  "Saves the current document."));
  connect (m_actionSave, SIGNAL (triggered ()), this, SLOT (slotFileSave ()));

  m_actionSaveAs = new QAction(tr ("Save As"), this);
  m_actionSaveAs->setShortcut (QKeySequence::SaveAs);
  m_actionSaveAs->setStatusTip (tr ("Saves the current document under a new filename."));
  m_actionSaveAs->setWhatsThis (tr ("Save Document As\n\n"
                                    "Saves the current document under a new filename."));
  connect (m_actionSaveAs, SIGNAL (triggered ()), this, SLOT (slotFileSaveAs ()));

  m_actionExport = new QAction (tr ("Export"), this);
  m_actionExport->setShortcut (tr ("Ctrl+E"));
  m_actionExport->setStatusTip (tr ("Exports the current document into a text file."));
  m_actionExport->setWhatsThis (tr ("Export Document\n\n"
                                    "Exports the current document into a text file."));
  connect (m_actionExport, SIGNAL (triggered ()), this, SLOT (slotFileExport ()));

  m_actionExportAs = new QAction (tr ("Export As"), this);
  m_actionExportAs->setStatusTip (tr ("Exports the current document into a text file under a new filename."));
  m_actionExportAs->setWhatsThis (tr ("Export Document As\n\n"
                                      "Exports the current document into a text file under a new filename."));
  connect (m_actionExportAs, SIGNAL (triggered ()), this, SLOT (slotFileExportAs ()));

  m_actionPrint = new QAction (tr ("&Print"), this);
  m_actionPrint->setShortcut (QKeySequence::Print);
  m_actionPrint->setStatusTip (tr ("Print the current document."));
  m_actionPrint->setWhatsThis (tr ("Print Document\n\n"
                                   "Print the current document to a printer or file."));
  connect (m_actionPrint, SIGNAL (triggered ()), this, SLOT (slotFilePrint ()));

  m_actionExit = new QAction(tr ("&Exit"), this);
  m_actionExit->setShortcut (QKeySequence::Quit);
  m_actionExit->setStatusTip (tr ("Quits the applicaiton."));
  m_actionExit->setWhatsThis (tr ("Exit\n\n"
                                  "Quits the applicaiton."));
  connect (m_actionExit, SIGNAL (triggered ()), this, SLOT (close ()));
}

void MainWindow::createActionsHelp ()
{
  m_actionAbout = new QAction(tr ("About Engauge"), this);
  m_actionAbout->setStatusTip (tr ("About the application."));
  m_actionAbout->setWhatsThis (tr ("About Engauge\n\nAbout the application."));
  connect (m_actionAbout, SIGNAL (triggered ()), this, SLOT (slotHelpAbout ()));

  m_actionWhatsThis = QWhatsThis::createAction(this);
  m_actionWhatsThis->setShortcut (QKeySequence::WhatsThis);
}

void MainWindow::createActionsSettings ()
{
  m_actionSettingsCoords = new QAction (tr ("Coords"), this);
  m_actionSettingsCoords->setStatusTip (tr ("Edit Coordinate settings."));
  m_actionSettingsCoords->setWhatsThis (tr ("Coordinate Settings"));
  connect (m_actionSettingsCoords, SIGNAL (triggered ()), this, SLOT (slotSettingsCoords ()));

  m_actionSettingsCurveProperties = new QAction (tr ("Curve Properties"), this);
  m_actionSettingsCurveProperties->setStatusTip (tr ("Edit Curve Properties settings."));
  m_actionSettingsCurveProperties->setWhatsThis (tr ("Coordinate Settings"));
  connect (m_actionSettingsCurveProperties, SIGNAL (triggered ()), this, SLOT (slotSettingsCurveProperties ()));

  m_actionSettingsCurves = new QAction (tr ("Curves"), this);
  m_actionSettingsCurves->setStatusTip (tr ("Edit Curves settings."));
  m_actionSettingsCurves->setWhatsThis (tr ("Curves Settings"));
  connect (m_actionSettingsCurves, SIGNAL (triggered ()), this, SLOT (slotSettingsCurves ()));

  m_actionSettingsExport = new QAction (tr ("Export"), this);
  m_actionSettingsExport->setStatusTip (tr ("Edit Export settings."));
  m_actionSettingsExport->setWhatsThis (tr ("Export Settings"));
  connect (m_actionSettingsExport, SIGNAL (triggered ()), this, SLOT (slotSettingsExport ()));

  m_actionSettingsFilter = new QAction (tr ("Filter"), this);
  m_actionSettingsFilter->setStatusTip (tr ("Edit Filter settings."));
  m_actionSettingsFilter->setWhatsThis (tr ("Filter Settings"));
  connect (m_actionSettingsFilter, SIGNAL (triggered ()), this, SLOT (slotSettingsFilter ()));

  m_actionSettingsGridDisplay = new QAction (tr ("Grid Display"), this);
  m_actionSettingsGridDisplay->setStatusTip (tr ("Edit Grid Display settings."));
  m_actionSettingsGridDisplay->setWhatsThis (tr ("Grid Display Settings"));
  connect (m_actionSettingsGridDisplay, SIGNAL (triggered ()), this, SLOT (slotSettingsGridDisplay ()));

  m_actionSettingsGridRemoval = new QAction (tr ("Grid Removal"), this);
  m_actionSettingsGridRemoval->setStatusTip (tr ("Edit Grid Removal settings."));
  m_actionSettingsGridRemoval->setWhatsThis (tr ("Grid Removal Settings"));
  connect (m_actionSettingsGridRemoval, SIGNAL (triggered ()), this, SLOT (slotSettingsGridRemoval ()));

  m_actionSettingsPointMatch = new QAction (tr ("Point Match"), this);
  m_actionSettingsPointMatch->setStatusTip (tr ("Edit Point Match settings."));
  m_actionSettingsPointMatch->setWhatsThis (tr ("Point Match Settings"));
  connect (m_actionSettingsPointMatch, SIGNAL (triggered ()), this, SLOT (slotSettingsPointMatch ()));

  m_actionSettingsSegments = new QAction (tr ("Segments"), this);
  m_actionSettingsSegments->setStatusTip (tr ("Edit Segments settings."));
  m_actionSettingsSegments->setWhatsThis (tr ("Segments Settings"));
  connect (m_actionSettingsSegments, SIGNAL (triggered ()), this, SLOT (slotSettingsSegments ()));
}

void MainWindow::createActionsView ()
{
  m_actionViewDigitize = new QAction (tr ("Digitize Toolbar"), this);
  m_actionViewDigitize->setCheckable (true);
  m_actionViewDigitize->setChecked (true);
  m_actionViewDigitize->setStatusTip (tr ("Show or hide the digitize toolbar."));
  m_actionViewDigitize->setWhatsThis (tr ("View Digitize ToolBar\n\n"
                                          "Show or hide the digitize toolbar"));
  connect (m_actionViewDigitize, SIGNAL (triggered ()), this, SLOT (slotViewDigitize()));

  m_actionViewDocumentImageNone = new QAction (tr ("Hide Image"), this);
  m_actionViewDocumentImageNone->setCheckable (true);
  m_actionViewDocumentImageNone->setStatusTip (tr ("Hide the image underneath the points."));
  m_actionViewDocumentImageNone->setWhatsThis (tr ("Hide Image\n\n"
                                                   "No image is shown so points are easier to see"));

  m_actionViewDocumentImageOriginal = new QAction (tr ("Show Original Image"), this);
  m_actionViewDocumentImageOriginal->setCheckable (true);
  m_actionViewDocumentImageOriginal->setStatusTip (tr ("Show the original image underneath the points."));
  m_actionViewDocumentImageOriginal->setWhatsThis (tr ("Show Original Image\n\n"
                                                       "Show the original image underneath the points"));

  m_actionViewDocumentImageFiltered = new QAction (tr ("Show Filtered Image"), this);
  m_actionViewDocumentImageFiltered->setCheckable (true);
  m_actionViewDocumentImageFiltered->setChecked (true);
  m_actionViewDocumentImageFiltered->setStatusTip (tr ("Show the filtered image underneath the points."));
  m_actionViewDocumentImageFiltered->setWhatsThis (tr ("Show Filtered Image\n\n"
                                                       "Show the filtered image underneath the points.\n\n"
                                                       "The filtered image is created from the original image according to the "
                                                       "Filter preferences so unimportant information is hidden and important "
                                                       "information is emphasized"));

  m_actionViewDocumentPointsNone = new QAction (tr ("Hide All Points"), this);
  m_actionViewDocumentPointsNone->setCheckable (true);
  m_actionViewDocumentPointsNone->setStatusTip (tr ("Hide all digitized points."));
  m_actionViewDocumentPointsNone->setWhatsThis (tr ("Hide All Points\n\n"
                                                    "No digitized points are shown so the image is easier to see."));

  m_actionViewDocumentPointsCurve = new QAction (tr ("Show Selected Curve's Points"), this);
  m_actionViewDocumentPointsCurve->setCheckable (true);
  m_actionViewDocumentPointsCurve->setStatusTip (tr ("Show only points in the currently selected curve."));
  m_actionViewDocumentPointsCurve->setWhatsThis (tr ("Show Curve's Points\n\n"
                                                     "Show only digitized points that belong to the currently selected curve."));

  m_actionViewDocumentPointsAll = new QAction (tr ("Show All Points"), this);
  m_actionViewDocumentPointsAll->setCheckable (true);
  m_actionViewDocumentPointsAll->setChecked (true);
  m_actionViewDocumentPointsAll->setStatusTip (tr ("Show all points."));
  m_actionViewDocumentPointsAll->setWhatsThis (tr ("Show All Points\n\n"
                                                   "Show all digitized axis and curve points"));

  m_groupDocumentImage = new QActionGroup(this);
  m_groupDocumentImage->addAction (m_actionViewDocumentImageNone);
  m_groupDocumentImage->addAction (m_actionViewDocumentImageOriginal);
  m_groupDocumentImage->addAction (m_actionViewDocumentImageFiltered);
  connect (m_groupDocumentImage, SIGNAL(triggered (QAction*)), this, SLOT (slotViewGroupDocumentImage(QAction*)));

  m_groupDocumentPoints = new QActionGroup(this);
  m_groupDocumentPoints->addAction (m_actionViewDocumentPointsNone);
  m_groupDocumentPoints->addAction (m_actionViewDocumentPointsCurve);
  m_groupDocumentPoints->addAction (m_actionViewDocumentPointsAll);
  connect (m_groupDocumentPoints, SIGNAL(triggered (QAction*)), this, SLOT (slotViewGroupDocumentPoints(QAction*)));

  m_actionStatusNever = new QAction (tr ("Hide Always"), this);
  m_actionStatusNever->setCheckable(true);
  m_actionStatusNever->setStatusTip (tr ("Always hide the status bar."));
  m_actionStatusNever->setWhatsThis (tr ("Hide the status bar. No temporary status or feedback messages will appear."));

  m_actionStatusTemporary = new QAction (tr ("Show Temporary Messages"), this);
  m_actionStatusTemporary->setCheckable(true);
  m_actionStatusTemporary->setStatusTip (tr ("Hide the status bar except when display temporary messages."));
  m_actionStatusTemporary->setWhatsThis (tr ("Hide the status bar, except when displaying temporary status and feedback messages."));

  m_actionStatusAlways = new QAction (tr ("Show Always"), this);
  m_actionStatusAlways->setCheckable(true);
  m_actionStatusAlways->setStatusTip (tr ("Always show the status bar."));
  m_actionStatusAlways->setWhatsThis (tr ("Show the status bar. Besides displaying temporary status and feedback messages, "
                                          "the status bar also displays information about the cursor position."));

  m_groupStatus = new QActionGroup(this);
  m_groupStatus->addAction (m_actionStatusNever);
  m_groupStatus->addAction (m_actionStatusTemporary);
  m_groupStatus->addAction (m_actionStatusAlways);
  connect (m_groupStatus, SIGNAL (triggered (QAction*)), this, SLOT (slotViewGroupStatus(QAction*)));

  m_actionZoomOut = new QAction (tr ("Zoom Out"), this);
  m_actionZoomOut->setStatusTip (tr ("Zoom out"));
  m_actionZoomOut->setShortcut (tr ("-"));
  connect (m_actionZoomOut, SIGNAL (triggered ()), this, SLOT (slotViewZoomOut ()));

  m_actionZoomIn = new QAction (tr ("Zoom In"), this);
  m_actionZoomIn->setStatusTip (tr ("Zoom in"));
  m_actionZoomIn->setShortcut (tr ("+"));
  connect (m_actionZoomIn, SIGNAL (triggered ()), this, SLOT (slotViewZoomIn ()));

  m_actionZoom16To1 = new QAction (tr ("16:1 (1600%)"), this);
  m_actionZoom16To1->setCheckable (true);
  m_actionZoom16To1->setStatusTip (tr ("Zoom 16:1"));
  connect (m_actionZoom16To1, SIGNAL (triggered ()), this, SLOT (slotViewZoom16To1 ()));

  m_actionZoom8To1 = new QAction (tr ("8:1 (800%)"), this);
  m_actionZoom8To1->setCheckable (true);
  m_actionZoom8To1->setStatusTip (tr ("Zoom 8:1"));
  connect (m_actionZoom8To1, SIGNAL (triggered ()), this, SLOT (slotViewZoom8To1 ()));

  m_actionZoom4To1 = new QAction (tr ("4:1 (400%)"), this);
  m_actionZoom4To1->setCheckable (true);
  m_actionZoom4To1->setStatusTip (tr ("Zoom 4:1"));
  connect (m_actionZoom4To1, SIGNAL (triggered ()), this, SLOT (slotViewZoom4To1 ()));

  m_actionZoom2To1 = new QAction (tr ("2:1 (200%)"), this);
  m_actionZoom2To1->setCheckable (true);
  m_actionZoom2To1->setStatusTip (tr ("Zoom 2:1"));
  connect (m_actionZoom2To1, SIGNAL (triggered ()), this, SLOT (slotViewZoom2To1 ()));

  m_actionZoom1To1 = new QAction (tr ("1:1 (100%)"), this);
  m_actionZoom1To1->setCheckable (true);
  m_actionZoom1To1->setChecked (true);
  m_actionZoom1To1->setStatusTip (tr ("Zoom 6:1"));
  connect (m_actionZoom1To1, SIGNAL (triggered ()), this, SLOT (slotViewZoom1To1 ()));

  m_actionZoom1To2 = new QAction (tr ("1:2 (50%)"), this);
  m_actionZoom1To2->setCheckable (true);
  m_actionZoom1To2->setStatusTip (tr ("Zoom 1:2"));
  connect (m_actionZoom1To2, SIGNAL (triggered ()), this, SLOT (slotViewZoom1To2 ()));

  m_actionZoom1To4 = new QAction (tr ("1:4 (25%)"), this);
  m_actionZoom1To4->setCheckable (true);
  m_actionZoom1To4->setStatusTip (tr ("Zoom 1:4"));
  connect (m_actionZoom1To4, SIGNAL (triggered ()), this, SLOT (slotViewZoom1To4 ()));

  m_actionZoom1To8 = new QAction (tr ("1:8 (12.5%)"), this);
  m_actionZoom1To8->setCheckable (true);
  m_actionZoom1To8->setStatusTip (tr ("Zoom 1:8"));
  connect (m_actionZoom1To8, SIGNAL (triggered ()), this, SLOT (slotViewZoom1To8 ()));

  m_actionZoom1To16 = new QAction (tr ("1:16 (6.25%)"), this);
  m_actionZoom1To16->setCheckable (true);
  m_actionZoom1To16->setStatusTip (tr ("Zoom 1:16"));
  connect (m_actionZoom1To16, SIGNAL (triggered ()), this, SLOT (slotViewZoom1To16 ()));

  m_actionZoomFill = new QAction (tr ("Fill"), this);
  m_actionZoomFill->setCheckable (true);
  m_actionZoomFill->setStatusTip (tr ("Zoom with stretching to fill window"));
  connect (m_actionZoomFill, SIGNAL (triggered ()), this, SLOT (slotViewZoomFill ()));

  m_groupZoom = new QActionGroup (this);
  m_groupZoom->addAction (m_actionZoom16To1);
  m_groupZoom->addAction (m_actionZoom8To1);
  m_groupZoom->addAction (m_actionZoom4To1);
  m_groupZoom->addAction (m_actionZoom2To1);
  m_groupZoom->addAction (m_actionZoom1To1);
  m_groupZoom->addAction (m_actionZoom1To2);
  m_groupZoom->addAction (m_actionZoom1To4);
  m_groupZoom->addAction (m_actionZoom1To8);
  m_groupZoom->addAction (m_actionZoom1To16);
  m_groupZoom->addAction (m_actionZoomFill);
}

void MainWindow::createCentralWidget ()
{
  QWidget *widget = new QWidget;
  setCentralWidget (widget);
  m_layout = new QVBoxLayout;
  widget->setLayout (m_layout);
}

void MainWindow::createLoadImageFromUrl ()
{
  m_loadImageFromUrl = new LoadImageFromUrl (*this);
}

void MainWindow::createMenus()
{
  m_menuFile = menuBar()->addMenu(tr("&File"));
  m_menuFile->addAction (m_actionImport);
  m_menuFile->addAction (m_actionOpen);
  m_menuFileOpenRecent = new QMenu (tr ("Open &Recent"));
  m_menuFile->addMenu (m_menuFileOpenRecent);
  m_menuFile->insertSeparator (m_actionSave);
  m_menuFile->addAction (m_actionSave);
  m_menuFile->addAction (m_actionSaveAs);
  m_menuFile->addAction (m_actionExport);
  m_menuFile->addAction (m_actionExportAs);
  m_menuFile->insertSeparator (m_actionPrint);
  m_menuFile->addAction (m_actionPrint);
  m_menuFile->insertSeparator (m_actionExit);
  m_menuFile->addAction (m_actionExit);

  m_menuEdit = menuBar()->addMenu(tr("&Edit"));
  m_menuEdit->addAction (m_actionEditUndo);
  m_menuEdit->addAction (m_actionEditRedo);
  m_menuEdit->insertSeparator (m_actionEditCut);
  m_menuEdit->addAction (m_actionEditCut);
  m_menuEdit->addAction (m_actionEditCopy);
  m_menuEdit->addAction (m_actionEditPaste);
  m_menuEdit->addAction (m_actionEditDelete);

  m_menuDigitize = menuBar()->addMenu(tr("Digitize"));
  m_menuDigitize->addAction (m_actionDigitizeSelect);
  m_menuDigitize->addAction (m_actionDigitizeAxis);
  m_menuDigitize->addAction (m_actionDigitizeCurve);
  m_menuDigitize->addAction (m_actionDigitizePointMatch);
  m_menuDigitize->addAction (m_actionDigitizeSegment);

  m_menuView = menuBar()->addMenu(tr("View"));
  m_menuView->addAction (m_actionViewDigitize);
  m_menuViewDocument = new QMenu (tr ("Document"));
  m_menuViewDocument->addAction (m_actionViewDocumentImageNone);
  m_menuViewDocument->addAction (m_actionViewDocumentImageOriginal);
  m_menuViewDocument->addAction (m_actionViewDocumentImageFiltered);
  m_menuViewDocument->insertSeparator(m_actionViewDocumentPointsNone);
  m_menuViewDocument->addAction (m_actionViewDocumentPointsNone);
  m_menuViewDocument->addAction (m_actionViewDocumentPointsCurve);
  m_menuViewDocument->addAction (m_actionViewDocumentPointsAll);
  m_menuView->addMenu (m_menuViewDocument);
  m_menuViewStatus = new QMenu (tr ("Status Bar"));
  m_menuViewStatus->addAction (m_actionStatusNever);
  m_menuViewStatus->addAction (m_actionStatusTemporary);
  m_menuViewStatus->addAction (m_actionStatusAlways);
  m_menuView->addMenu (m_menuViewStatus);
  m_menuViewZoom = new QMenu (tr ("Zoom"));
  m_menuViewZoom->addAction (m_actionZoomOut);
  m_menuViewZoom->addAction (m_actionZoomIn);
  m_menuViewZoom->insertSeparator (m_actionZoom16To1);
  m_menuViewZoom->addAction (m_actionZoom16To1);
  m_menuViewZoom->addAction (m_actionZoom8To1);
  m_menuViewZoom->addAction (m_actionZoom4To1);
  m_menuViewZoom->addAction (m_actionZoom2To1);
  m_menuViewZoom->addAction (m_actionZoom1To1);
  m_menuViewZoom->addAction (m_actionZoom1To2);
  m_menuViewZoom->addAction (m_actionZoom1To4);
  m_menuViewZoom->addAction (m_actionZoom1To8);
  m_menuViewZoom->addAction (m_actionZoom1To16);
  m_menuViewZoom->addAction (m_actionZoomFill);
  m_menuView->addMenu (m_menuViewZoom);

  m_menuSettings = menuBar()->addMenu(tr ("Settings"));
  m_menuSettings->addAction (m_actionSettingsCoords);
  m_menuSettings->addAction (m_actionSettingsCurveProperties);
  m_menuSettings->addAction (m_actionSettingsCurves);
  m_menuSettings->addAction (m_actionSettingsExport);
  m_menuSettings->addAction (m_actionSettingsFilter);
  m_menuSettings->addAction (m_actionSettingsGridDisplay);
  m_menuSettings->addAction (m_actionSettingsGridRemoval);
  m_menuSettings->addAction (m_actionSettingsPointMatch);
  m_menuSettings->addAction (m_actionSettingsSegments);

  m_menuHelp = menuBar()->addMenu(tr("&Help"));
  m_menuHelp->addAction (m_actionAbout);
  m_menuHelp->addAction (m_actionWhatsThis);
  m_menuHelp->insertSeparator (m_actionWhatsThis);
}

void MainWindow::createSettingsDialogs ()
{
  m_dlgSettingsCoords = new DlgSettingsCoords (*m_cmdMediator, this);
  m_dlgSettingsCurveProperties = new DlgSettingsCurveProperties (*m_cmdMediator, this);
  m_dlgSettingsCurves = new DlgSettingsCurves (*m_cmdMediator, this);
  m_dlgSettingsExport = new DlgSettingsExport (*m_cmdMediator, this);
  m_dlgSettingsFilter = new DlgSettingsFilter (*m_cmdMediator, this);
  m_dlgSettingsGridDisplay = new DlgSettingsGridDisplay (*m_cmdMediator, this);
  m_dlgSettingsGridRemoval = new DlgSettingsGridRemoval (*m_cmdMediator, this);
  m_dlgSettingsPointMatch = new DlgSettingsPointMatch (*m_cmdMediator, this);
  m_dlgSettingsSegments = new DlgSettingsSegments (*m_cmdMediator, this);

  m_dlgSettingsCoords->setVisible (false);
  m_dlgSettingsCurveProperties->setVisible (false);
  m_dlgSettingsCurves->setVisible (false);
  m_dlgSettingsExport->setVisible (false);
  m_dlgSettingsFilter->setVisible (false);
  m_dlgSettingsGridDisplay->setVisible (false);
  m_dlgSettingsGridRemoval->setVisible (false);
  m_dlgSettingsPointMatch->setVisible (false);
  m_dlgSettingsSegments->setVisible (false);
}

void MainWindow::createScene ()
{
  m_scene = new GraphicsScene (this);
  m_view = new GraphicsView (m_scene, *this);
  // Skip setStatusTip here since that will overwrite much more important messages, and trigger gratuitous showing of status bar
  m_view->setWhatsThis (tr ("Document\n\n"
                            "After an image file is imported, or an Engauge Document opened, an image appears in this area. "
                            "Points are added to the image.\n\n"
                            "If the image is a graph with two axes and one or more curves, then three axis points must be "
                            "created along those axes. Then curve points can be added along the curves.\n\n"
                            "If the image is a map with a scale to define length, then two axis points must be "
                            "created at either end of the scale. Then curve points can be added."));
  m_layout->addWidget (m_view);
}

void MainWindow::createStateContext ()
{
  m_digitizeStateContext = new DigitizeStateContext (*this,
                                                     *m_view);
}

void MainWindow::createStatusBar ()
{
  m_statusBar = new StatusBar (*statusBar ());
  connect (this, SIGNAL (signalZoom(int)), m_statusBar, SLOT (slotZoom(int)));
  connect (m_statusBar, SIGNAL (signalZoom (int)), this, SLOT (slotViewZoom (int)));
}

void MainWindow::createToolBars ()
{
  m_cmbCurve = new QComboBox ();
  m_cmbCurve->setMinimumWidth (180);
  m_cmbCurve->setStatusTip ("Select curve for new points.");
  m_cmbCurve->setWhatsThis (tr ("Selected Curve Name\n\n"
                                "Select curve for any new points. Every point belongs to one curve."));
  connect (m_cmbCurve, SIGNAL (currentIndexChanged (int)), this, SLOT (slotCmbCurve (int)));

  m_toolDigitize = new QToolBar (tr ("Drawing"), this);
  m_toolDigitize->addAction (m_actionDigitizeSelect);
  m_toolDigitize->insertSeparator (m_actionDigitizeAxis);
  m_toolDigitize->addAction (m_actionDigitizeAxis);
  m_toolDigitize->insertSeparator (m_actionDigitizeCurve);
  m_toolDigitize->addAction (m_actionDigitizeCurve);
  m_toolDigitize->addAction (m_actionDigitizePointMatch);
  m_toolDigitize->addAction (m_actionDigitizeSegment);
  m_toolDigitize->addWidget (m_cmbCurve);
  addToolBar (m_toolDigitize);
}

void MainWindow::fileImport (const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::fileImport fileName=" << fileName.toLatin1 ().data ();

  QImage image;
  if (!image.load (fileName)) {
    QMessageBox::warning (this,
                          tr("Application"),
                          tr("Cannot read file %1.").
                          arg(fileName));
    return;
  }

  loadImage (fileName,
             image);
}

void MainWindow::loadFile (const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadFile fileName=" << fileName.toLatin1 ().data ();

  QApplication::setOverrideCursor(Qt::WaitCursor);
  CmdMediator *cmdMediator = new CmdMediator (fileName);
  QApplication::restoreOverrideCursor();

  if (cmdMediator->successfulRead ()) {

    setCurrentPathFromFile (fileName);

    if (m_cmdMediator != 0) {
      removePixmap();
      delete m_cmdMediator;
      m_cmdMediator = 0;
    }

    m_cmdMediator = cmdMediator;
    m_digitizeStateContext->bindToCmdMediator (cmdMediator);
    connect (m_actionEditUndo, SIGNAL (triggered ()), m_cmdMediator, SLOT (undo ()));
    connect (m_actionEditRedo, SIGNAL (triggered ()), m_cmdMediator, SLOT (redo ()));
    connect (m_cmdMediator, SIGNAL (canRedoChanged(bool)), this, SLOT (slotCanRedoChanged (bool)));
    connect (m_cmdMediator, SIGNAL (canUndoChanged(bool)), this, SLOT (slotCanUndoChanged (bool)));
    connect (m_cmdMediator, SIGNAL (redoTextChanged (const QString &)), this, SLOT (slotRedoTextChanged (const QString &)));
    connect (m_cmdMediator, SIGNAL (undoTextChanged (const QString &)), this, SLOT (slotUndoTextChanged (const QString &)));
    loadCurveNamesFromCmdMediator ();
    setPixmap (m_cmdMediator->pixmap ());
    slotViewZoomFill();

    setCurrentFile(fileName);
    m_statusBar->showTemporaryMessage("File opened");
    m_statusBar->wakeUp ();

    // Start select mode
    m_actionDigitizeSelect->setChecked (true); // We assume user wants to first select existing stuff
    slotDigitizeSelect(); // Trigger transition so cursor gets updated immediately

    updateControls ();

  } else {

    QMessageBox::warning (this,
                          tr("Application"),
                          tr("Cannot read file %1:\n%2.").
                          arg(fileName).
                          arg(cmdMediator->reasonForUnsuccessfulRead ()));
    delete cmdMediator;

  }
}

void MainWindow::loadImage (const QString &fileName,
                            const QImage &image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadImage fileName=" << fileName.toLatin1 ().data ();

  QApplication::setOverrideCursor(Qt::WaitCursor);
  CmdMediator *cmdMediator = new CmdMediator (image);
  QApplication::restoreOverrideCursor();

  setCurrentPathFromFile (fileName);

  if (m_cmdMediator != 0) {
    removePixmap();
    delete m_cmdMediator;
    m_cmdMediator = 0;
  }

  m_cmdMediator = cmdMediator;
  m_digitizeStateContext->bindToCmdMediator (cmdMediator);
  connect (m_actionEditUndo, SIGNAL (triggered ()), m_cmdMediator, SLOT (undo ()));
  connect (m_actionEditRedo, SIGNAL (triggered ()), m_cmdMediator, SLOT (redo ()));
  connect (m_cmdMediator, SIGNAL (canRedoChanged(bool)), this, SLOT (slotCanRedoChanged (bool)));
  connect (m_cmdMediator, SIGNAL (canUndoChanged(bool)), this, SLOT (slotCanUndoChanged (bool)));
  connect (m_cmdMediator, SIGNAL (redoTextChanged (const QString &)), this, SLOT (slotRedoTextChanged (const QString &)));
  connect (m_cmdMediator, SIGNAL (undoTextChanged (const QString &)), this, SLOT (slotUndoTextChanged (const QString &)));
  loadCurveNamesFromCmdMediator ();
  setPixmap (m_cmdMediator->pixmap ());
  slotViewZoomFill();

  setCurrentFile(fileName);
  m_statusBar->showTemporaryMessage ("File imported");
  m_statusBar->wakeUp ();

  // Start axis mode
  m_actionDigitizeAxis->setChecked (true); // We assume user first wants to digitize axis points
  slotDigitizeAxis (); // Trigger transition so cursor gets updated immediately

  updateControls ();
}

void MainWindow::loadCurveNamesFromCmdMediator ()
{
  m_cmbCurve->clear ();
  QStringList curvesGraphsNames = m_cmdMediator->curvesGraphsNames ();
  QStringList::iterator itr;
  for (itr = curvesGraphsNames.begin (); itr != curvesGraphsNames.end (); itr++) {

    QString curvesGraphName = *itr;
    m_cmbCurve->addItem (curvesGraphName);
  }
  m_cmbCurve->setCurrentIndex (0);
}

bool MainWindow::maybeSave()
{
  if (m_cmdMediator != 0) {
    if (m_cmdMediator->isModified()) {
      QMessageBox::StandardButton ret = QMessageBox::warning (this,
                                                              tr("Application"),
                                                              tr("The document has been modified.\n"
                                                                 "Do you want to save your changes?"),
                                                              QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      if (ret == QMessageBox::Save) {
        return slotFileSave();
      } else if (ret == QMessageBox::Cancel) {
        return false;
      }
    }
  }

  return true;
}

void MainWindow::removePixmap ()
{
  if (m_image != 0) {
    m_scene->removeItem (m_image);
    m_image = 0;
  }
}

void MainWindow::resizeEvent(QResizeEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::resizeEvent";

  if (m_actionZoomFill->isChecked ()) {
    slotViewZoomFill();
  }
}

bool MainWindow::saveFile (const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::saveFile fileName=" << fileName.toLatin1 ().data ();

  QFile file(fileName);
  if (!file.open(QFile::WriteOnly)) {
    QMessageBox::warning (this,
                          tr("Application"),
                          tr ("Cannot write file %1: \n%2.").
                          arg(fileName).
                          arg(file.errorString()));
    return false;
  }

  QTextStream out(&file);
  QApplication::setOverrideCursor (Qt::WaitCursor);
//  out << textEdit->toPlainText ();
  QApplication::restoreOverrideCursor ();

  setCurrentFile(fileName);
  m_statusBar->showTemporaryMessage("File saved");
  return true;
}

GraphicsScene &MainWindow::scene ()
{
  Q_ASSERT (m_scene != 0);
  return *m_scene;
}

QString MainWindow::selectedCurrentCurve () const
{
  return m_cmbCurve->currentText ();
}

void MainWindow::setCurrentFile (const QString &fileName)
{
  m_curfile = fileName;

  QString shownName = m_curfile;
  if (m_curfile.isEmpty()) {
    shownName = "untitled.dig";
  }
  setWindowFilePath(shownName);
}

void MainWindow::setCurrentPathFromFile (const QString &fileName)
{
  QDir dir = QFileInfo (fileName).absoluteDir();

  if (dir.exists ()) {

    bool success = QDir::setCurrent (dir.absolutePath ()); // Return to chosen directory the next time
    Q_ASSERT (success);

  } else {

    // File was a url so it is irrelevant to the current directory
  }
}

void MainWindow::setPixmap (const QPixmap &pixmap)
{
  removePixmap();

  m_image = m_scene->addPixmap (pixmap);
  m_image->setData (DATA_KEY_IDENTIFIER, "view");
  m_image->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_IMAGE);
  m_scene->setSceneRect (m_image->boundingRect ()); // Reset or else small image after large image will be off-center

  m_digitizeStateContext->setImage (m_image);
}

void MainWindow::settingsRead ()
{
  QSettings settings ("Engauge", "Digitizer");

  settingsReadEnvironment (settings);
  settingsReadMainWindow (settings);
}

void MainWindow::settingsReadEnvironment (QSettings &settings)
{
  settings.beginGroup ("Environment");
  QDir::setCurrent (settings.value ("currentDirectory",
                                    QDir::currentPath ()).toString ());
  settings.endGroup ();
}

void MainWindow::settingsReadMainWindow (QSettings &settings)
{
  settings.beginGroup("MainWindow");

  // Window geometry
  resize (settings.value ("size",
                          QSize (400, 400)).toSize ());
  move (settings.value ("pos",
                        QPoint (200, 200)).toPoint ());

  // Digitize toolbar visibility
  bool viewDigitizeToolBar = settings.value ("viewDigitizeToolBar",
                                             true).toBool ();
  m_actionViewDigitize->setChecked (viewDigitizeToolBar);
  m_toolDigitize->setVisible (viewDigitizeToolBar);

  // Statusbar visibility
  StatusBarMode statusBarMode = (StatusBarMode) settings.value ("viewStatusBar",
                                                                false).toInt ();
  m_statusBar->setStatusBarMode (statusBarMode);
  m_actionStatusNever->setChecked (statusBarMode == STATUS_BAR_MODE_NEVER);
  m_actionStatusTemporary->setChecked (statusBarMode == STATUS_BAR_MODE_TEMPORARY);
  m_actionStatusAlways->setChecked (statusBarMode == STATUS_BAR_MODE_ALWAYS);

  settings.endGroup();
}

void MainWindow::settingsWrite ()
{
  QSettings settings ("Engauge", "Digitizer");

  settings.beginGroup ("Environment");
  settings.setValue ("currentDirectory", QDir::currentPath ());
  settings.endGroup ();

  settings.beginGroup ("MainWindow");
  settings.setValue ("size", size ());
  settings.setValue ("pos", pos ());
  settings.setValue ("viewDigitizeToolBar", m_toolDigitize->isVisible ());
  settings.setValue ("viewStatusBar", m_statusBar->statusBarMode ());
  settings.endGroup ();
}

void MainWindow::slotCanRedoChanged (bool canRedo)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotCanRedoChanged";

  m_actionEditRedo->setEnabled (canRedo);
}

void MainWindow::slotCanUndoChanged (bool canUndo)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotCanUndoChanged";

  m_actionEditUndo->setEnabled (canUndo);
}

void MainWindow::slotCmbCurve(int /* currentIndex */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotCmbCurve";

  updateViewedPoints();
}

void MainWindow::slotContextMenuEvent (QString pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotContextMenuEvent point=" << pointIdentifier.toLatin1 ().data ();

  m_digitizeStateContext->handleContextMenuEvent (pointIdentifier);
}

void MainWindow::slotDigitizeAxis ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeAxis";

  m_digitizeStateContext->requestImmediateStateTransition (DIGITIZE_STATE_AXIS);
  m_cmbCurve->setEnabled (false);
}

void MainWindow::slotDigitizeCurve ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeCurve";

  m_digitizeStateContext->requestImmediateStateTransition (DIGITIZE_STATE_CURVE);
  m_cmbCurve->setEnabled (true);
}

void MainWindow::slotDigitizePointMatch ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizePointMatch";

  m_digitizeStateContext->requestImmediateStateTransition (DIGITIZE_STATE_POINT_MATCH);
  m_cmbCurve->setEnabled (true);
}

void MainWindow::slotDigitizeSegment ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeSegment";

  m_digitizeStateContext->requestImmediateStateTransition (DIGITIZE_STATE_SEGMENT);
  m_cmbCurve->setEnabled (true);
}

void MainWindow::slotDigitizeSelect ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeSelect";

  m_digitizeStateContext->requestImmediateStateTransition (DIGITIZE_STATE_SELECT);
  m_cmbCurve->setEnabled (false);
}

void MainWindow::slotEditCopy ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditCopy";

  CmdCopy *cmd = new CmdCopy (*this,
                              m_cmdMediator->document(),
                              m_scene->selectedPointIdentifiers ());
  m_digitizeStateContext->appendNewCmd (cmd);
}

void MainWindow::slotEditCut ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditCut";

  CmdCut *cmd = new CmdCut (*this,
                            m_cmdMediator->document(),
                            m_scene->selectedPointIdentifiers ());
  m_digitizeStateContext->appendNewCmd (cmd);
}

void MainWindow::slotEditDelete ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditDelete";

  CmdDelete *cmd = new CmdDelete (*this,
                                  m_cmdMediator->document(),
                                  m_scene->selectedPointIdentifiers ());
  m_digitizeStateContext->appendNewCmd (cmd);
}

void MainWindow::slotEditPaste ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditPaste";
}

void MainWindow::slotFileExport ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileExport";
}

void MainWindow::slotFileExportAs ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileExportAs";
}

void MainWindow::slotFileImport ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImport";

  if (maybeSave ()) {

    QString filter;
    QTextStream str (&filter);

    // Compile a list of supported formats into a filter
    str << "Image Files (";
    QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();
    QList<QByteArray>::iterator itr;
    QString delimiter;
    for (itr = supportedImageFormats.begin (); itr != supportedImageFormats.end (); itr++) {
      QByteArray arr = *itr;
      str << delimiter << "*." << arr.data ();
      delimiter = " ";
    }
    str << ")";

    QString fileName = QFileDialog::getOpenFileName (this,
                                                     tr("Open Image"),
                                                     QDir::currentPath (),
                                                     filter);
    if (!fileName.isEmpty ()) {
      fileImport (fileName);
    }
  }
}

void MainWindow::slotFileImportDraggedImage(QImage image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportDraggedImage";

  loadImage ("",
             image);
}

void MainWindow::slotFileImportDraggedImageUrl(QUrl url)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportDraggedImageUrl url=" << url.toString ().toLatin1 ().data ();

  m_loadImageFromUrl->startLoadImage (url);
}

void MainWindow::slotFileImportImage(QString fileName, QImage image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportImage fileName=" << fileName.toLatin1 ().data ();

  loadImage (fileName,
             image);
}

void MainWindow::slotFileOpen()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileOpen";

  if (maybeSave ()) {
    QString fileName = QFileDialog::getOpenFileName (this,
                                                     tr("Open Document"),
                                                     QDir::currentPath (),
                                                     tr ("Documents (*.dig)"));
    if (!fileName.isEmpty ()) {
      loadFile (fileName);
    }
  }
}

void MainWindow::slotFilePrint()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFilePrint";

  QPrinter printer (QPrinter::HighResolution);
  QPrintDialog dlg (&printer, this);
  if (dlg.exec() == QDialog::Accepted) {
    QPainter painter (&printer);
    m_view->render (&painter);
    painter.end();
  }
}

bool MainWindow::slotFileSave()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileSave";

  if (m_curfile.isEmpty()) {
    return slotFileSaveAs();
  } else {
    return saveFile (m_curfile);
  }
}

bool MainWindow::slotFileSaveAs()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileSaveAs";

  QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  if (dialog.exec()) {

    QStringList files = dialog.selectedFiles();
    return saveFile(files.at(0));
  }

  return false;
}

void MainWindow::slotHelpAbout()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotHelpAbout";

  QMessageBox aboutBox (this);
  aboutBox.setWindowTitle (tr ("About Engauge"));
  aboutBox.setTextFormat (Qt::RichText);
  aboutBox.setText (QString ("%1 %2 %3")
                    .arg (tr ("<p>Engauge Digitizer</b>"))
                    .arg ("Version 6.0")
                    .arg (tr ("</p><p>&copy; 2014 Mark Mitchell</p>"
                          "<p>Engauge Digitizer is an open source tool for efficiently extracting accurate numeric data from "
                          "images of graphs. The process may be considered as \"inverse graphing\". When you \"engauge\" a document, "
                          "you are converting pixels into numbers.</p>"
                          "<p>This is free software, and you are welcome to redistribute it under "
                          "certain conditions according to the GNU General Public License Version 2,"
                          "or (at your option) any later version.</p>"
                          "<p>Engauge Digitizer comes with ABSOLUTELY NO WARRANTY.</p>"
                          "<p>Read the included LICENSE file for details.</p>"
                          "<p>Engauge Digitizer Links<p>"
                          "<ul>"
                          "<li><a href='http://digitizer.sourceforge.net'>Project Home Page</a></li>"
                          "<li><a href='http://sourceforge.net/forum/forum.php?forum_id=229857'>Help Forum<a></li>"
                          "<li><a href='http://sourceforge.net/forum/forum.php?forum_id=229856'>Open Discussion Forum</a></li>"
                          "</ul>"
                          "<p>FFTW 3.X.X Links</p>"
                          "<ul>"
                          "<li><a href='http://www.fftw.org'>Project page</a></li>"
                          "</ul>")));
  aboutBox.exec ();
}

void MainWindow::slotKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotKeyPress key=" << QKeySequence (key).toString().toLatin1 ().data ();

  m_digitizeStateContext->handleKeyPress (key);
}

void MainWindow::slotLeave ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotLeave";

  m_digitizeStateContext->handleLeave ();
}

void MainWindow::slotMouseMove (QPointF pos)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotMouseMove pos=" << QPointFToString (pos).toLatin1 ().data ();

  QString coordsScreen, coordsGraph, resolutionGraph;
  m_transformation.coordTextForStatusBar (pos,
                                          coordsScreen,
                                          coordsGraph,
                                          resolutionGraph);
  m_statusBar->setCoordinates (coordsScreen,
                               coordsGraph,
                               resolutionGraph);
}

void MainWindow::slotMousePress (QPointF pos)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotMousePress";

  m_view->resetPositionHasChangedFlags();

  m_digitizeStateContext->handleMousePress (pos);
}

void MainWindow::slotMouseRelease (QPointF pos)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotMouseRelease";

  m_digitizeStateContext->handleMouseRelease (pos);
}

void MainWindow::slotRedoTextChanged (const QString &text)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotRedoTextChanged";

  QString completeText ("Redo");
  if (!text.isEmpty ()) {
    completeText += QString (" \"%1\"").arg (text);
  }
  m_actionEditRedo->setText (completeText);
}

void MainWindow::slotSetOverrideCursor (Qt::CursorShape cursorShape)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSetOverrideCursor";

  m_digitizeStateContext->handleSetOverrideCursor (cursorShape);
}

void MainWindow::slotSettingsCoords ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsCoords->show ();
}

void MainWindow::slotSettingsCurveProperties ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsCurveProperties->show ();
}

void MainWindow::slotSettingsCurves ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsCurves->show ();
}

void MainWindow::slotSettingsExport ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsExport->show ();
}

void MainWindow::slotSettingsFilter ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsFilter->show ();
}

void MainWindow::slotSettingsGridDisplay ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsGridDisplay->show ();
}

void MainWindow::slotSettingsGridRemoval ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsGridRemoval->show ();
}

void MainWindow::slotSettingsPointMatch ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsPointMatch->show ();
}

void MainWindow::slotSettingsSegments ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsSegments->show ();
}

void MainWindow::slotUndoTextChanged (const QString &text)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotUndoTextChanged";

  QString completeText ("Undo");
  if (!text.isEmpty ()) {
    completeText += QString (" \"%1\"").arg (text);
  }
  m_actionEditUndo->setText (completeText);
}

void MainWindow::slotViewDigitize ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewDigitize";

  if (m_actionViewDigitize->isChecked ()) {
    m_toolDigitize->show();
  } else {
    m_toolDigitize->hide();
  }
}

void MainWindow::slotViewGroupDocumentImage(QAction *action)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewGroupDocumentImage";

  if (action == m_actionViewDocumentImageFiltered) {

    m_image->setPixmap(m_cmdMediator->pixmap ());

  } else if (action == m_actionViewDocumentImageNone) {

    // Replace image by plain background, so boundary is still visible and useful as a reference for the points
    QPixmap allWhite (m_cmdMediator->pixmap ());
    allWhite.fill (Qt::white);
    m_image->setPixmap (allWhite);

  } else if (action == m_actionViewDocumentImageOriginal) {

    m_image->setPixmap(m_cmdMediator->pixmap ());

  } else {
    Q_ASSERT (false);
  }
}

void MainWindow::slotViewGroupDocumentPoints(QAction * /* action */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewGroupDocumentPoints";

  updateViewedPoints ();
}

void MainWindow::slotViewGroupStatus(QAction *action)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewGroupStatus";

  Q_ASSERT (m_statusBar != 0); // At startup, make sure status bar is already set up when View menu gets initialized

  if (action == m_actionStatusNever) {
    m_statusBar->setStatusBarMode(STATUS_BAR_MODE_NEVER);
  } else if (action == m_actionStatusTemporary) {
    m_statusBar->setStatusBarMode(STATUS_BAR_MODE_TEMPORARY);
  } else {
    m_statusBar->setStatusBarMode(STATUS_BAR_MODE_ALWAYS);
  }
}

void MainWindow::slotViewZoom(int zoom)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoom";

  switch ((ZoomFactor) zoom) {
    case ZOOM_16_TO_1:
      m_actionZoom16To1->setChecked(true);
      slotViewZoom16To1 ();
      break;
    case ZOOM_8_TO_1:
      m_actionZoom8To1->setChecked(true);
      slotViewZoom8To1 ();
      break;
    case ZOOM_4_TO_1:
      m_actionZoom4To1->setChecked(true);
      slotViewZoom4To1 ();
      break;
    case ZOOM_2_TO_1:
      m_actionZoom2To1->setChecked(true);
      slotViewZoom2To1 ();
      break;
    case ZOOM_1_TO_1:
      m_actionZoom1To1->setChecked(true);
      slotViewZoom1To1 ();
      break;
    case ZOOM_1_TO_2:
      m_actionZoom1To2->setChecked(true);
      slotViewZoom1To2 ();
      break;
    case ZOOM_1_TO_4:
      m_actionZoom1To4->setChecked(true);
      slotViewZoom1To4 ();
      break;
    case ZOOM_1_TO_8:
      m_actionZoom1To8->setChecked(true);
      slotViewZoom1To8 ();
      break;
    case ZOOM_1_TO_16:
      m_actionZoom1To16->setChecked(true);
      slotViewZoom1To16 ();
      break;
    case ZOOM_FILL:
      m_actionZoomFill->setChecked(true);
      slotViewZoomFill ();
      break;
  }
}

void MainWindow::slotViewZoom16To1 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoom16To1";

  QTransform transform;
  transform.scale (16.0, 16.0);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_16_TO_1);
}

void MainWindow::slotViewZoom8To1 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoom8To1";

  QTransform transform;
  transform.scale (8.0, 8.0);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_8_TO_1);
}

void MainWindow::slotViewZoom4To1 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoom4To1";

  QTransform transform;
  transform.scale (4.0, 4.0);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_4_TO_1);
}

void MainWindow::slotViewZoom2To1 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotZoom2To1";

  QTransform transform;
  transform.scale (2.0, 2.0);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_2_TO_1);
}

void MainWindow::slotViewZoom1To1 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoom1To1";

  QTransform transform;
  transform.scale (1.0, 1.0);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_1_TO_1);
}

void MainWindow::slotViewZoom1To2 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotZoom1To2";

  QTransform transform;
  transform.scale (0.5, 0.5);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_1_TO_2);
}

void MainWindow::slotViewZoom1To4 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotZoom1To4";

  QTransform transform;
  transform.scale (0.25, 0.25);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_1_TO_4);
}

void MainWindow::slotViewZoom1To8 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotZoom1To8";

  QTransform transform;
  transform.scale (0.125, 0.125);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_1_TO_8);
}

void MainWindow::slotViewZoom1To16 ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotZoom1To16";

  QTransform transform;
  transform.scale (0.0625, 0.0625);
  m_view->setTransform (transform);
  emit signalZoom(ZOOM_1_TO_16);
}

void MainWindow::slotViewZoomFill ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomFill";

  m_view->fitInView (m_image);
  emit signalZoom(ZOOM_FILL);
}

void MainWindow::slotViewZoomIn ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomIn";

  // Try to go in

  bool goto16To1 = false, goto8To1 = false, goto4To1 = false, goto2To1 = false;
  bool goto1To1 = false;
  bool goto1To2 = false, goto1To4 = false, goto1To8 = false, goto1To16 = false;
  if (m_actionZoomFill->isChecked ()) {

    // Zooming in means user probably wants the more squished direction to be zoomed in by one step
    double xScale = m_view->transform().m11();
    double yScale = m_view->transform().m22();
    double scale = qMin(xScale, yScale);
    if (scale < 0.125) {
      goto1To8 = true;
    } else if (scale < 0.25) {
      goto1To4 = true;
    } else if (scale < 0.5) {
      goto1To2 = true;
    } else if (scale < 1) {
      goto1To1 = true;
    } else if (scale < 2) {
      goto2To1 = true;
    } else if (scale < 4) {
      goto4To1 = true;
    } else if (scale < 8) {
      goto8To1 = true;
    } else {
      goto1To16 = true;
    }
  } else {
    goto16To1 = m_actionZoom8To1->isChecked ();
    goto8To1 = m_actionZoom4To1->isChecked ();
    goto4To1 = m_actionZoom2To1->isChecked ();
    goto2To1 = m_actionZoom1To1->isChecked ();
    goto1To1 = m_actionZoom1To2->isChecked ();
    goto1To2 = m_actionZoom1To4->isChecked ();
    goto1To4 = m_actionZoom1To8->isChecked ();
    goto1To8 = m_actionZoom1To16->isChecked ();
  }

  if (goto16To1) {
    m_actionZoom16To1->setChecked (true);
    slotViewZoom16To1 ();
  } else if (goto8To1) {
    m_actionZoom8To1->setChecked (true);
    slotViewZoom8To1 ();
  } else if (goto4To1) {
    m_actionZoom4To1->setChecked (true);
    slotViewZoom4To1 ();
  } else if (goto2To1) {
    m_actionZoom2To1->setChecked (true);
    slotViewZoom2To1 ();
  } else if (goto1To1) {
    m_actionZoom1To1->setChecked (true);
    slotViewZoom1To1 ();
  } else if (goto1To2) {
    m_actionZoom1To2->setChecked (true);
    slotViewZoom1To2 ();
  } else if (goto1To4) {
    m_actionZoom1To4->setChecked (true);
    slotViewZoom1To4 ();
  } else if (goto1To8) {
    m_actionZoom1To8->setChecked (true);
    slotViewZoom1To8 ();
  } else if (goto1To16) {
    m_actionZoom1To16->setChecked (true);
    slotViewZoom1To16 ();
  }
}

void MainWindow::slotViewZoomOut ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomOut";

  // Try to go out

  bool goto16To1 = false, goto8To1 = false, goto4To1 = false, goto2To1 = false;
  bool goto1To1 = false;
  bool goto1To2 = false, goto1To4 = false, goto1To8 = false, goto1To16 = false;
  if (m_actionZoomFill->isChecked ()) {

    // Zooming out means user probably wants the less squished direction to be zoomed out by one step
    double xScale = m_view->transform().m11();
    double yScale = m_view->transform().m22();
    double scale = qMax(xScale, yScale);
    if (scale > 8) {
      goto8To1 = true;
    } else if (scale > 4) {
      goto4To1 = true;
    } else if (scale > 2) {
      goto2To1 = true;
    } else if (scale > 1) {
      goto1To1 = true;
    } else if (scale > 0.5) {
      goto1To2 = true;
    } else if (scale > 0.25) {
      goto1To4 = true;
    } else if (scale > 0.125) {
      goto1To8 = true;
    } else {
      goto1To16 = true;
    }
  } else {
    goto8To1 = m_actionZoom16To1->isChecked ();
    goto4To1 = m_actionZoom8To1->isChecked ();
    goto2To1 = m_actionZoom4To1->isChecked ();
    goto1To1 = m_actionZoom2To1->isChecked ();
    goto1To2 = m_actionZoom1To1->isChecked ();
    goto1To4 = m_actionZoom1To2->isChecked ();
    goto1To8 = m_actionZoom1To4->isChecked ();
    goto1To16 = m_actionZoom1To8->isChecked ();
  }

  if (goto1To16) {
    m_actionZoom1To16->setChecked (true);
    slotViewZoom1To16 ();
  } else if (goto1To8) {
    m_actionZoom1To8->setChecked (true);
    slotViewZoom1To8 ();
  } else if (goto1To4) {
    m_actionZoom1To4->setChecked (true);
    slotViewZoom1To4 ();
  } else if (goto1To2) {
    m_actionZoom1To2->setChecked (true);
    slotViewZoom1To2 ();
  } else if (goto1To1) {
    m_actionZoom1To1->setChecked (true);
    slotViewZoom1To1 ();
  } else if (goto2To1) {
    m_actionZoom2To1->setChecked (true);
    slotViewZoom2To1 ();
  } else if (goto4To1) {
    m_actionZoom4To1->setChecked (true);
    slotViewZoom4To1 ();
  } else if (goto8To1) {
    m_actionZoom8To1->setChecked (true);
    slotViewZoom8To1 ();
  } else if (goto16To1) {
    m_actionZoom16To1->setChecked (true);
    slotViewZoom16To1 ();
  }
}

bool MainWindow::transformIsDefined() const
{
  return m_transformation.transformIsDefined();
}

void MainWindow::updateAfterCommand ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateAfterCommand";

  // Update the QGraphicsScene with the populated Curves
  m_scene->updateAfterCommand (*m_cmdMediator);

  updateControls ();
  updateAfterCommandStatusBarCoords ();
}

void MainWindow::updateAfterMouseRelease ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateAfterMouseRelease";

  updateControls ();
}

void MainWindow::updateAfterCommandStatusBarCoords ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateAfterCommandStatusBarCoords";

  // For some reason, mapFromGlobal(QCursor::pos) differs from event->pos by a little bit. We must compensate for
  // this so cursor coordinates in status bar match the DlgEditPoint inputs initially. After the mouse moves
  // the problem disappears since event->pos is available and QCursor::pos is no longer needed
  const QPoint HACK_SO_GRAPH_COORDINATE_MATCHES_INPUT (1, 1);

  m_transformation.update (!m_curfile.isEmpty (), *m_cmdMediator);

  if (m_transformation.transformIsDefined()) {
    m_cmdMediator->applyTransformation (m_transformation);
  }

  QPoint posLocal = m_view->mapFromGlobal (QCursor::pos ()) - HACK_SO_GRAPH_COORDINATE_MATCHES_INPUT;
  QPointF posScreen = m_view->mapToScene (posLocal);

  slotMouseMove (posScreen); // Update the status bar coordinates to reflect the newly updated transformation
}

void MainWindow::updateControls ()
{
//  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateControls";

  if (m_cmdMediator != 0) {
    setWindowModified (m_cmdMediator->isModified ()); // Put asterisk in title bar when document is modified
  }

  m_menuFileOpenRecent->setEnabled (m_menuFileOpenRecent->actions().count() > 0);
  m_actionSave->setEnabled (!m_curfile.isEmpty ());
  m_actionSaveAs->setEnabled (!m_curfile.isEmpty ());
  m_actionExport->setEnabled (!m_curfile.isEmpty ());
  m_actionExportAs->setEnabled (!m_curfile.isEmpty ());
  m_actionPrint->setEnabled (!m_curfile.isEmpty ());

  if (m_cmdMediator == 0) {
    m_actionEditUndo->setEnabled (false);
    m_actionEditRedo->setEnabled (false);
  } else {
    m_actionEditUndo->setEnabled (m_cmdMediator->canUndo ());
    m_actionEditRedo->setEnabled (m_cmdMediator->canRedo ());
  }
  m_actionEditCut->setEnabled (m_scene->selectedItems().count () > 0);
  m_actionEditCopy->setEnabled (m_scene->selectedItems().count () > 0);
  m_actionEditPaste->setEnabled (false);
  m_actionEditDelete->setEnabled (m_scene->selectedItems().count () > 0);

  m_actionDigitizeAxis->setEnabled (!m_curfile.isEmpty ());
  m_actionDigitizeCurve ->setEnabled (!m_curfile.isEmpty ());
  m_actionDigitizePointMatch->setEnabled (!m_curfile.isEmpty ());
  m_actionDigitizeSegment->setEnabled (!m_curfile.isEmpty ());
  m_actionDigitizeSelect->setEnabled (!m_curfile.isEmpty ());

  m_actionViewDigitize->setEnabled (!m_curfile.isEmpty ());

  m_actionSettingsCoords->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsCurveProperties->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsCurves->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsExport->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsFilter->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsGridDisplay->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsGridRemoval->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsPointMatch->setEnabled (!m_curfile.isEmpty ());
  m_actionSettingsSegments->setEnabled (!m_curfile.isEmpty ());

  m_groupDocumentImage->setEnabled (!m_curfile.isEmpty ());
  m_groupDocumentPoints->setEnabled (!m_curfile.isEmpty ());
  m_groupZoom->setEnabled (!m_curfile.isEmpty ());

  m_actionZoomIn->setEnabled (!m_curfile.isEmpty ()); // Disable at startup so shortcut has no effect
  m_actionZoomOut->setEnabled (!m_curfile.isEmpty ()); // Disable at startup so shortcut has no effect
}

void MainWindow::updateViewedPoints ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateViewedPoints";

  if (m_actionViewDocumentPointsAll->isChecked ()) {

    m_scene->showPoints (true, true);

  } else if (m_actionViewDocumentPointsCurve->isChecked ()) {

    m_scene->showPoints (true, false, m_cmbCurve->currentText ());

  } else if (m_actionViewDocumentPointsNone->isChecked ()) {

    m_scene->showPoints (false);

  } else {
    Q_ASSERT (false);
  }
}

GraphicsView &MainWindow::view ()
{
  Q_ASSERT (m_view != 0);
  return *m_view;
}

const GraphicsView &MainWindow::view () const
{
  Q_ASSERT (m_view != 0);
  return *m_view;
}
