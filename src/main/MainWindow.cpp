/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "BackgroundImage.h"
#include "BackgroundStateContext.h"
#include "img/bannerapp_16.xpm"
#include "img/bannerapp_32.xpm"
#include "img/bannerapp_64.xpm"
#include "img/bannerapp_128.xpm"
#include "img/bannerapp_256.xpm"
#include "ChecklistGuide.h"
#include "ChecklistGuideWizard.h"
#include "CmdCopy.h"
#include "CmdCut.h"
#include "CmdDelete.h"
#include "CmdMediator.h"
#include "CmdSelectCoordSystem.h"
#include "CmdStackShadow.h"
#include "ColorFilter.h"
#include "Curve.h"
#include "DataKey.h"
#include "DigitizeStateContext.h"
#include "DigitAxis.xpm"
#include "DigitColorPicker.xpm"
#include "DigitCurve.xpm"
#include "DigitPointMatch.xpm"
#include "DigitScale.xpm"
#include "DigitSegment.xpm"
#include "DigitSelect.xpm"
#include "DlgAbout.h"
#include "DlgErrorReportLocal.h"
#include "DlgErrorReportNetworking.h"
#include "DlgImportAdvanced.h"
#include "DlgRequiresTransform.h"
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
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "ExportImageForRegression.h"
#include "ExportToFile.h"
#include "FileCmdScript.h"
#include "FittingCurve.h"
#include "FittingWindow.h"
#include "GeometryWindow.h"
#include "Ghosts.h"
#include "GraphicsItemsExtractor.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "GridLineFactory.h"
#include "GridLineLimiter.h"
#include "HelpWindow.h"
#ifdef ENGAUGE_JPEG2000
#include "Jpeg2000.h"
#endif // ENGAUGE_JPEG2000
#include "LoadFileInfo.h"
#ifdef NETWORKING
#include "LoadImageFromUrl.h"
#endif
#include "Logger.h"
#include "MainTitleBarFormat.h"
#include "MainWindow.h"
#ifdef NETWORKING
#include "NetworkClient.h"
#endif
#include "NonPdf.h"
#ifdef ENGAUGE_PDF
#include "Pdf.h"
#endif // ENGAUGE_PDF
#include "PdfResolution.h"
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QDebug>
#include <QDesktopServices>
#include <QDockWidget>
#include <QDomDocument>
#include <QKeyEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsLineItem>
#include <QImageReader>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPrintDialog>
#include <QPrinter>
#include <QSettings>
#include <QTextStream>
#include <QtHelp>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include "QtToString.h"
#include <QVBoxLayout>
#include <QWhatsThis>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "ScaleBarAxisPointsUnite.h"
#include "Settings.h"
#include "StatusBar.h"
#include "TransformationStateContext.h"
#include "TutorialDlg.h"
#include "Version.h"
#include "ViewPointStyle.h"
#include "ViewSegmentFilter.h"
#include "ZoomFactor.h"
#include "ZoomFactorInitial.h"

const QString EMPTY_FILENAME ("");
const char *ENGAUGE_FILENAME_DESCRIPTION = "Engauge Document";
const QString ENGAUGE_FILENAME_EXTENSION ("dig");
const int REGRESSION_INTERVAL = 400; // Milliseconds
const unsigned int MAX_RECENT_FILE_LIST_SIZE = 8;

MainWindow::MainWindow(const QString &errorReportFile,
                       const QString &fileCmdScriptFile,
                       bool isRegressionTest,
                       bool isGnuplot,
                       bool isReset,
                       QStringList loadStartupFiles,
                       QWidget *parent) :
  QMainWindow(parent),
  m_isDocumentExported (false),
  m_engaugeFile (EMPTY_FILENAME),
  m_currentFile (EMPTY_FILENAME),
  m_layout (0),
  m_scene (0),
  m_view (0),
  m_loadImageFromUrl (0),
  m_cmdMediator (0),
  m_digitizeStateContext (0),
  m_transformationStateContext (0),
  m_backgroundStateContext (0),
  m_networkClient (0),
  m_isGnuplot (isGnuplot),
  m_ghosts (0),
  m_timerRegressionErrorReport(0),
  m_fileCmdScript (0),
  m_isErrorReportRegressionTest (isRegressionTest),
  m_timerRegressionFileCmdScript(0),
  m_fittingCurve (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::MainWindow"
                              << " curDir=" << QDir::currentPath().toLatin1().data();

#if defined(OSX_DEBUG) || defined(OSX_RELEASE)
  qApp->setApplicationName ("Engauge Digitizer");
  qApp->setOrganizationDomain ("Mark Mitchell");
#endif

  LoggerUpload::bindToMainWindow(this);

  m_startupDirectory = QDir::currentPath();

  setCurrentFile ("");
  createIcons();
  setWindowFlags (Qt::WindowContextHelpButtonHint | windowFlags ()); // Add help to default buttons
  setWindowTitle (engaugeWindowTitle ());

  createCentralWidget();
  createActions ();
  createStatusBar ();
  createMenus ();
  createToolBars ();
  createDockableWidgets ();
  createHelpWindow ();
  createTutorial ();
  createScene ();
  createNetwork ();
  createLoadImageFromUrl ();
  createStateContextBackground ();
  createStateContextDigitize ();
  createStateContextTransformation ();
  createSettingsDialogs ();
  createCommandStackShadow ();
  createZoomMap ();
  updateControls ();

  settingsRead (isReset); // This changes the current directory when not regression testing
  setCurrentFile ("");
  setUnifiedTitleAndToolBarOnMac(true);

  installEventFilter(this);

  // Start regression scripting if appropriate. Regression scripts assume current directory is the original
  // current directory, so we temporarily reset the current directory
  QString originalPath = QDir::currentPath();
  QDir::setCurrent (m_startupDirectory);
  if (!errorReportFile.isEmpty()) {
    loadErrorReportFile(errorReportFile);
    if (m_isErrorReportRegressionTest) {
      startRegressionTestErrorReport(errorReportFile);
    }
  } else if (!fileCmdScriptFile.isEmpty()) {
    m_fileCmdScript = new FileCmdScript (fileCmdScriptFile);
    startRegressionTestFileCmdScript();
  } else {

    // Save file names for later, after gui becomes available. The file names are dropped if error report file is specified
    // since only one of the two modes is available at any time, for simplicity
    m_loadStartupFiles = loadStartupFiles;
  }
  QDir::setCurrent (originalPath);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addDockWindow (QDockWidget *dockWidget,
                                QSettings &settings,
                                const QString &settingsTokenArea,
                                const QString &settingsTokenGeometry,
                                Qt::DockWidgetArea dockWidgetArea)
{
  // Checklist guide is docked or undocked. Default is docked so it does not get overlooked by the user (which
  // can happen if it opens elsewhere). The user may not know it can be undocked, but at least can resize or
  // hide it if he/she needs more room for the main window.
  const bool DOCKED_EQUALS_NOT_FLOATING = false;
  Qt::DockWidgetArea area = (Qt::DockWidgetArea) settings.value (settingsTokenArea,
                                                                 Qt::NoDockWidgetArea).toInt();

  if (area == Qt::NoDockWidgetArea) {

    addDockWidget (dockWidgetArea,
                   dockWidget); // Add on the right to prevent error message, then immediately make undocked
    dockWidget->setFloating(DOCKED_EQUALS_NOT_FLOATING);
    if (settings.contains (settingsTokenGeometry)) {
      dockWidget->restoreGeometry (settings.value (settingsTokenGeometry).toByteArray());
    }

  } else {

    addDockWidget (area,
                   dockWidget);

  }
}

void MainWindow::applyZoomFactorAfterLoad()
{
  ZoomFactor zoomFactor;
  ZoomFactorInitial zoomFactorInitial = m_modelMainWindow.zoomFactorInitial();

  if (m_zoomMap.contains (zoomFactorInitial)) {
    zoomFactor = m_zoomMap [zoomFactorInitial];
  } else if (zoomFactorInitial == ZOOM_INITIAL_PREVIOUS) {
    zoomFactor = currentZoomFactor ();
  } else {
    ENGAUGE_ASSERT (false);
    zoomFactor = currentZoomFactor();
  }

  slotViewZoom (zoomFactor);
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

void MainWindow::cmdFileClose()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::cmdFileClose";

  setWindowModified (false); // Prevent popup query asking if changes should be saved
  slotFileClose();
}

void MainWindow::cmdFileExport(const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::cmdFileExport";

  ExportToFile exportStrategy;
  fileExport(fileName,
             exportStrategy);
}

void MainWindow::cmdFileImport(const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::cmdFileImport";

  m_regressionFile = exportFilenameFromInputFilename (fileName);
  fileImport (fileName,
              IMPORT_TYPE_SIMPLE);
}

void MainWindow::cmdFileOpen(const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::cmdFileOpen";

  m_regressionFile = exportFilenameFromInputFilename (fileName);
  loadDocumentFile(fileName);
}

CmdMediator *MainWindow::cmdMediator ()
{
  // We do not check m_cmdMediator with ENGAUGE_CHECK_PTR since calling code is expected to deal with null pointer at startup
  return m_cmdMediator;
}

void MainWindow::createActions()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActions";

  createActionsFile ();
  createActionsEdit ();
  createActionsDigitize ();
  createActionsView ();
  createActionsSettings ();
  createActionsHelp ();
}

void MainWindow::createActionsDigitize ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActionsDigitize";

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

  m_actionDigitizeSelect = new QAction (iconSelect, tr ("Select Tool"), this);
  m_actionDigitizeSelect->setShortcut (QKeySequence (tr ("Shift+F2")));
  m_actionDigitizeSelect->setCheckable (true);
  m_actionDigitizeSelect->setStatusTip (tr ("Select points on screen."));
  m_actionDigitizeSelect->setWhatsThis (tr ("Select\n\n"
                                            "Select points on the screen."));
  connect (m_actionDigitizeSelect, SIGNAL (triggered ()), this, SLOT (slotDigitizeSelect ()));

  m_actionDigitizeAxis = new QAction (iconAxis, tr ("Axis Point Tool"), this);
  m_actionDigitizeAxis->setShortcut (QKeySequence (tr ("Shift+F3")));
  m_actionDigitizeAxis->setCheckable (true);
  m_actionDigitizeAxis->setStatusTip (tr ("Digitize axis points for a graph."));
  m_actionDigitizeAxis->setWhatsThis (tr ("Digitize Axis Point\n\n"
                                          "Digitizes an axis point for a graph by placing a new point at the cursor "
                                          "after a mouse click. The coordinates of the axis point are then "
                                          "entered. In a graph, three axis points are required to define "
                                          "the graph coordinates."));
  connect (m_actionDigitizeAxis, SIGNAL (triggered ()), this, SLOT (slotDigitizeAxis ()));

  m_actionDigitizeScale = new QAction (iconScale, tr ("Scale Bar Tool"), this);
  m_actionDigitizeScale->setShortcut (QKeySequence (tr ("Shift+F8")));
  m_actionDigitizeScale->setCheckable (true);
  m_actionDigitizeScale->setStatusTip (tr ("Digitize scale bar for a map."));
  m_actionDigitizeScale->setWhatsThis (tr ("Digitize Scale Bar\n\n"
                                           "Digitize a scale bar for a map by clicking and dragging. The length of the "
                                           "scale bar is then entered. In a map, the two endpoints of the scale "
                                           "bar define the distances in graph coordinates.\n\n"
                                           "Maps must be imported using Import (Advanced)."));
  connect (m_actionDigitizeScale, SIGNAL (triggered ()), this, SLOT (slotDigitizeScale ()));

  m_actionDigitizeCurve = new QAction (iconCurve, tr ("Curve Point Tool"), this);
  m_actionDigitizeCurve->setShortcut (QKeySequence (tr ("Shift+F4")));
  m_actionDigitizeCurve->setCheckable (true);
  m_actionDigitizeCurve->setStatusTip (tr ("Digitize curve points."));
  m_actionDigitizeCurve->setWhatsThis (tr ("Digitize Curve Point\n\n"
                                           "Digitizes a curve point by placing a new point at the cursor "
                                           "after a mouse click. Use this mode to digitize points along curves "
                                           "one by one.\n\n"
                                           "New points will be assigned to the currently selected curve."));
  connect (m_actionDigitizeCurve, SIGNAL (triggered ()), this, SLOT (slotDigitizeCurve ()));

  m_actionDigitizePointMatch = new QAction (iconPointMatch, tr ("Point Match Tool"), this);
  m_actionDigitizePointMatch->setShortcut (QKeySequence (tr ("Shift+F5")));
  m_actionDigitizePointMatch->setCheckable (true);
  m_actionDigitizePointMatch->setStatusTip (tr ("Digitize curve points in a point plot by matching a point."));
  m_actionDigitizePointMatch->setWhatsThis (tr ("Digitize Curve Points by Point Matching\n\n"
                                                "Digitizes curve points in a point plot by finding points that match a sample point. The process "
                                                "starts by selecting a representative sample point.\n\n"
                                                "New points will be assigned to the currently selected curve."));
  connect (m_actionDigitizePointMatch, SIGNAL (triggered ()), this, SLOT (slotDigitizePointMatch ()));

  m_actionDigitizeColorPicker = new QAction (iconColorPicker, tr ("Color Picker Tool"), this);
  m_actionDigitizeColorPicker->setShortcut (QKeySequence (tr ("Shift+F6")));
  m_actionDigitizeColorPicker->setCheckable (true);
  m_actionDigitizeColorPicker->setStatusTip (tr ("Select color settings for filtering in Segment Fill mode."));
  m_actionDigitizeColorPicker->setWhatsThis (tr ("Select color settings for Segment Fill filtering\n\n"
                                                 "Select a pixel along the currently selected curve. That pixel and its neighbors will "
                                                 "define the filter settings (color, brightness, and so on) of the currently selected curve "
                                                 "while in Segment Fill mode."));
  connect (m_actionDigitizeColorPicker, SIGNAL (triggered ()), this, SLOT (slotDigitizeColorPicker ()));

  m_actionDigitizeSegment = new QAction (iconSegment, tr ("Segment Fill Tool"), this);
  m_actionDigitizeSegment->setShortcut (QKeySequence (tr ("Shift+F7")));
  m_actionDigitizeSegment->setCheckable (true);
  m_actionDigitizeSegment->setStatusTip (tr ("Digitize curve points along a segment of a curve."));
  m_actionDigitizeSegment->setWhatsThis (tr ("Digitize Curve Points With Segment Fill\n\n"
                                             "Digitizes curve points by placing new points along the highlighted "
                                             "segment under the cursor. Use this mode to quickly digitize multiple points along a "
                                             "curve with a single click.\n\n"
                                             "New points will be assigned to the currently selected curve."));
  connect (m_actionDigitizeSegment, SIGNAL (triggered ()), this, SLOT (slotDigitizeSegment ()));

  m_groupDigitize = new QActionGroup (this);
  m_groupDigitize->addAction (m_actionDigitizeSelect);
  m_groupDigitize->addAction (m_actionDigitizeAxis);
  m_groupDigitize->addAction (m_actionDigitizeScale);
  m_groupDigitize->addAction (m_actionDigitizeCurve);
  m_groupDigitize->addAction (m_actionDigitizePointMatch);
  m_groupDigitize->addAction (m_actionDigitizeColorPicker);
  m_groupDigitize->addAction (m_actionDigitizeSegment);
}

void MainWindow::createActionsEdit ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActionsEdit";

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

  m_actionEditPasteAsNew = new QAction (tr ("Paste As New"), this);
  m_actionEditPasteAsNew->setStatusTip (tr ("Pastes an image from the clipboard."));
  m_actionEditPasteAsNew->setWhatsThis (tr ("Paste as New\n\n"
                                            "Creates a new document by pasting an image from the clipboard."));
  connect (m_actionEditPasteAsNew, SIGNAL (triggered ()), this, SLOT (slotEditPasteAsNew ()));

  m_actionEditPasteAsNewAdvanced = new QAction (tr ("Paste As New (Advanced)..."), this);
  m_actionEditPasteAsNewAdvanced->setStatusTip (tr ("Pastes an image from the clipboard, in advanced mode."));
  m_actionEditPasteAsNewAdvanced->setWhatsThis (tr ("Paste as New (Advanced)\n\n"
                                                    "Creates a new document by pasting an image from the clipboard, in advanced mode."));
  connect (m_actionEditPasteAsNewAdvanced, SIGNAL (triggered ()), this, SLOT (slotEditPasteAsNewAdvanced ()));
}

void MainWindow::createActionsFile ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActionsFile";

  m_actionImport = new QAction(tr ("&Import..."), this);
  m_actionImport->setShortcut (tr ("Ctrl+I"));
  m_actionImport->setStatusTip (tr ("Creates a new document by importing an simple image."));
  m_actionImport->setWhatsThis (tr ("Import Image\n\n"
                                    "Creates a new document by importing an image with a single coordinate system, "
                                    "and axes both coordinates known.\n\n"
                                    "For more complicated images with multiple coordinate systems, "
                                    "and/or floating axes, Import (Advanced) is used instead."));
  connect (m_actionImport, SIGNAL (triggered ()), this, SLOT (slotFileImport ()));

  m_actionImportAdvanced = new QAction(tr ("Import (Advanced)..."), this);
  m_actionImportAdvanced->setStatusTip (tr ("Creates a new document by importing an image with support for advanced feaures."));
  m_actionImportAdvanced->setWhatsThis (tr ("Import (Advanced)\n\n"
                                            "Creates a new document by importing an image with support for advanced feaures. In "
                                            "advanced mode, there can be multiple coordinate systems and/or floating axes."));
  connect (m_actionImportAdvanced, SIGNAL (triggered ()), this, SLOT (slotFileImportAdvanced ()));

  m_actionImportImageReplace = new QAction (tr ("Import (Image Replace)..."), this);
  m_actionImportImageReplace->setStatusTip (tr ("Imports a new image into the current document, replacing the existing image."));
  m_actionImportImageReplace->setWhatsThis (tr ("Import (Image Replace)\n\n"
                                                "Imports a new image into the current document. The existing image is replaced, "
                                                "and all curves in the document are preserved. This operation is useful for applying "
                                                "the axis points and other settings from an existing document to a different image."));
  connect (m_actionImportImageReplace, SIGNAL (triggered ()), this, SLOT (slotFileImportImageReplace ()));

  m_actionOpen = new QAction(tr ("&Open..."), this);
  m_actionOpen->setShortcut (QKeySequence::Open);
  m_actionOpen->setStatusTip (tr ("Opens an existing document."));
  m_actionOpen->setWhatsThis (tr ("Open Document\n\n"
                                  "Opens an existing document."));
  connect (m_actionOpen, SIGNAL (triggered ()), this, SLOT (slotFileOpen ()));

#ifndef OSX_RELEASE
  for (unsigned int i = 0; i < MAX_RECENT_FILE_LIST_SIZE; i++) {
    QAction *recentFileAction = new QAction (this);
    recentFileAction->setVisible (true);
    connect (recentFileAction, SIGNAL (triggered ()), this, SLOT (slotRecentFileAction ()));
    m_actionRecentFiles.append (recentFileAction);
  }
#endif 

  m_actionClose = new QAction(tr ("&Close"), this);
  m_actionClose->setShortcut (QKeySequence::Close);
  m_actionClose->setStatusTip (tr ("Closes the open document."));
  m_actionClose->setWhatsThis (tr ("Close Document\n\n"
                                   "Closes the open document."));
  connect (m_actionClose, SIGNAL (triggered ()), this, SLOT (slotFileClose ()));

  m_actionSave = new QAction(tr ("&Save"), this);
  m_actionSave->setShortcut (QKeySequence::Save);
  m_actionSave->setStatusTip (tr ("Saves the current document."));
  m_actionSave->setWhatsThis (tr ("Save Document\n\n"
                                  "Saves the current document."));
  connect (m_actionSave, SIGNAL (triggered ()), this, SLOT (slotFileSave ()));

  m_actionSaveAs = new QAction(tr ("Save As..."), this);
  m_actionSaveAs->setShortcut (QKeySequence::SaveAs);
  m_actionSaveAs->setStatusTip (tr ("Saves the current document under a new filename."));
  m_actionSaveAs->setWhatsThis (tr ("Save Document As\n\n"
                                    "Saves the current document under a new filename."));
  connect (m_actionSaveAs, SIGNAL (triggered ()), this, SLOT (slotFileSaveAs ()));

  m_actionExport = new QAction (tr ("Export..."), this);
  m_actionExport->setShortcut (tr ("Ctrl+E"));
  m_actionExport->setStatusTip (tr ("Exports the current document into a text file."));
  m_actionExport->setWhatsThis (tr ("Export Document\n\n"
                                    "Exports the current document into a text file."));
  connect (m_actionExport, SIGNAL (triggered ()), this, SLOT (slotFileExport ()));

  m_actionPrint = new QAction (tr ("&Print..."), this);
  m_actionPrint->setShortcut (QKeySequence::Print);
  m_actionPrint->setStatusTip (tr ("Print the current document."));
  m_actionPrint->setWhatsThis (tr ("Print Document\n\n"
                                   "Print the current document to a printer or file."));
  connect (m_actionPrint, SIGNAL (triggered ()), this, SLOT (slotFilePrint ()));

  m_actionExit = new QAction(tr ("&Exit"), this);
  m_actionExit->setShortcut (QKeySequence::Quit);
  m_actionExit->setStatusTip (tr ("Quits the application."));
  m_actionExit->setWhatsThis (tr ("Exit\n\n"
                                  "Quits the application."));
  connect (m_actionExit, SIGNAL (triggered ()), this, SLOT (close ()));
}

void MainWindow::createActionsHelp ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActionsHelp";

  m_actionHelpChecklistGuideWizard = new QAction (tr ("Checklist Guide Wizard"), this);
  m_actionHelpChecklistGuideWizard->setCheckable (true);
  m_actionHelpChecklistGuideWizard->setStatusTip (tr ("Open Checklist Guide Wizard during import to define digitizing steps"));
  m_actionHelpChecklistGuideWizard->setWhatsThis (tr ("Checklist Guide Wizard\n\n"
                                                      "Use Checklist Guide Wizard during import to generate a checklist of steps "
                                                      "for the imported document"));

  m_actionHelpWhatsThis = QWhatsThis::createAction(this);
  m_actionHelpWhatsThis->setShortcut (QKeySequence::WhatsThis);

  m_actionHelpTutorial = new QAction (tr ("Tutorial"), this);
  m_actionHelpTutorial->setStatusTip (tr ("Play tutorial showing steps for digitizing curves"));
  m_actionHelpTutorial->setWhatsThis (tr ("Tutorial\n\n"
                                          "Play tutorial showing steps for digitizing points from curves drawn with lines "
                                          "and/or point"));
  connect (m_actionHelpTutorial, SIGNAL (triggered ()), this, SLOT (slotHelpTutorial()));

#ifndef OSX_RELEASE
  m_actionHelpHelp = new QAction (tr ("Help"), this);
  m_actionHelpHelp->setShortcut (QKeySequence::HelpContents);
  m_actionHelpHelp->setStatusTip (tr ("Help documentation"));
  m_actionHelpHelp->setWhatsThis (tr ("Help Documentation\n\n"
                                      "Searchable help documentation"));
  // This action gets connected directly to the QDockWidget when that is created
#endif

  m_actionHelpAbout = new QAction(tr ("About Engauge"), this);
  m_actionHelpAbout->setStatusTip (tr ("About the application."));
  m_actionHelpAbout->setWhatsThis (tr ("About Engauge\n\nAbout the application."));
  connect (m_actionHelpAbout, SIGNAL (triggered ()), this, SLOT (slotHelpAbout ()));
}

void MainWindow::createActionsSettings ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActionsSettings";

  m_actionSettingsCoords = new QAction (tr ("Coordinates..."), this);
  m_actionSettingsCoords->setStatusTip (tr ("Edit Coordinate settings."));
  m_actionSettingsCoords->setWhatsThis (tr ("Coordinate Settings\n\n"
                                            "Coordinate settings determine how the graph coordinates are mapped to the pixels in the image"));
  connect (m_actionSettingsCoords, SIGNAL (triggered ()), this, SLOT (slotSettingsCoords ()));

  m_actionSettingsCurveAddRemove = new QAction (tr ("Add/Remove Curve..."), this);
  m_actionSettingsCurveAddRemove->setStatusTip (tr ("Add or Remove Curves."));
  m_actionSettingsCurveAddRemove->setWhatsThis (tr ("Add/Remove Curve\n\n"
                                                    "Add/Remove Curve settings control which curves are included in the current document"));
  connect (m_actionSettingsCurveAddRemove, SIGNAL (triggered ()), this, SLOT (slotSettingsCurveAddRemove ()));

  m_actionSettingsCurveProperties = new QAction (tr ("Curve Properties..."), this);
  m_actionSettingsCurveProperties->setStatusTip (tr ("Edit Curve Properties settings."));
  m_actionSettingsCurveProperties->setWhatsThis (tr ("Curve Properties Settings\n\n"
                                                     "Curves properties settings determine how each curve appears"));
  connect (m_actionSettingsCurveProperties, SIGNAL (triggered ()), this, SLOT (slotSettingsCurveProperties ()));

  m_actionSettingsDigitizeCurve = new QAction (tr ("Digitize Curve..."), this);
  m_actionSettingsDigitizeCurve->setStatusTip (tr ("Edit Digitize Axis and Graph Curve settings."));
  m_actionSettingsDigitizeCurve->setWhatsThis (tr ("Digitize Axis and Graph Curve Settings\n\n"
                                                   "Digitize Curve settings determine how points are digitized in Digitize Axis Point and "
                                                   "Digitize Graph Point modes"));
  connect (m_actionSettingsDigitizeCurve, SIGNAL (triggered ()), this, SLOT (slotSettingsDigitizeCurve ()));

  m_actionSettingsExport = new QAction (tr ("Export Format..."), this);
  m_actionSettingsExport->setStatusTip (tr ("Edit Export Format settings."));
  m_actionSettingsExport->setWhatsThis (tr ("Export Format Settings\n\n"
                                            "Export format settings affect how exported files are formatted"));
  connect (m_actionSettingsExport, SIGNAL (triggered ()), this, SLOT (slotSettingsExportFormat ()));

  m_actionSettingsColorFilter = new QAction (tr ("Color Filter..."), this);
  m_actionSettingsColorFilter->setStatusTip (tr ("Edit Color Filter settings."));
  m_actionSettingsColorFilter->setWhatsThis (tr ("Color Filter Settings\n\n"
                                                 "Color filtering simplifies the graphs for easier Point Matching and Segment Filling"));
  connect (m_actionSettingsColorFilter, SIGNAL (triggered ()), this, SLOT (slotSettingsColorFilter ()));

  m_actionSettingsAxesChecker = new QAction (tr ("Axes Checker..."), this);
  m_actionSettingsAxesChecker->setStatusTip (tr ("Edit Axes Checker settings."));
  m_actionSettingsAxesChecker->setWhatsThis (tr ("Axes Checker Settings\n\n"
                                                 "Axes checker can reveal any axis point mistakes, which are otherwise hard to find."));
  connect (m_actionSettingsAxesChecker, SIGNAL (triggered ()), this, SLOT (slotSettingsAxesChecker ()));

  m_actionSettingsGridDisplay = new QAction (tr ("Grid Line Display..."), this);
  m_actionSettingsGridDisplay->setStatusTip (tr ("Edit Grid Line Display settings."));
  m_actionSettingsGridDisplay->setWhatsThis (tr ("Grid Line Display Settings\n\n"
                                                 "Grid lines displayed on the graph can provide more accuracy than the Axis Checker, for distorted graphs. "
                                                 "In a distorted graph, the grid lines can be used to adjust the axis points for more accuracy in different regions."));
  connect (m_actionSettingsGridDisplay, SIGNAL (triggered ()), this, SLOT (slotSettingsGridDisplay ()));

  m_actionSettingsGridRemoval = new QAction (tr ("Grid Line Removal..."), this);
  m_actionSettingsGridRemoval->setStatusTip (tr ("Edit Grid Line Removal settings."));
  m_actionSettingsGridRemoval->setWhatsThis (tr ("Grid Line Removal Settings\n\n"
                                                 "Grid line removal isolates curve lines for easier Point Matching and Segment Filling, when "
                                                 "Color Filtering is not able to separate grid lines from curve lines."));
  connect (m_actionSettingsGridRemoval, SIGNAL (triggered ()), this, SLOT (slotSettingsGridRemoval ()));

  m_actionSettingsPointMatch = new QAction (tr ("Point Match..."), this);
  m_actionSettingsPointMatch->setStatusTip (tr ("Edit Point Match settings."));
  m_actionSettingsPointMatch->setWhatsThis (tr ("Point Match Settings\n\n"
                                                "Point match settings determine how points are matched while in Point Match mode"));
  connect (m_actionSettingsPointMatch, SIGNAL (triggered ()), this, SLOT (slotSettingsPointMatch ()));

  m_actionSettingsSegments = new QAction (tr ("Segment Fill..."), this);
  m_actionSettingsSegments->setStatusTip (tr ("Edit Segment Fill settings."));
  m_actionSettingsSegments->setWhatsThis (tr ("Segment Fill Settings\n\n"
                                              "Segment fill settings determine how points are generated in the Segment Fill mode"));
  connect (m_actionSettingsSegments, SIGNAL (triggered ()), this, SLOT (slotSettingsSegments ()));

  m_actionSettingsGeneral = new QAction (tr ("General..."), this);
  m_actionSettingsGeneral->setStatusTip (tr ("Edit General settings."));
  m_actionSettingsGeneral->setWhatsThis (tr ("General Settings\n\n"
                                             "General settings are document-specific settings that affect multiple modes. For example, the cursor size setting affects "
                                             "both Color Picker and Point Match modes"));
  connect (m_actionSettingsGeneral, SIGNAL (triggered ()), this, SLOT (slotSettingsGeneral ()));

  m_actionSettingsMainWindow = new QAction (tr ("Main Window..."), this);
  m_actionSettingsMainWindow->setEnabled (true);
  m_actionSettingsMainWindow->setStatusTip (tr ("Edit Main Window settings."));
  m_actionSettingsMainWindow->setWhatsThis (tr ("Main Window Settings\n\n"
                                                "Main window settings affect the user interface and are not specific to any document"));
  connect (m_actionSettingsMainWindow, SIGNAL (triggered ()), this, SLOT (slotSettingsMainWindow ()));
}

void MainWindow::createActionsView ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createActionsView";

  m_actionViewBackground = new QAction (tr ("Background Toolbar"), this);
  m_actionViewBackground->setCheckable (true);
  m_actionViewBackground->setChecked (true);
  m_actionViewBackground->setStatusTip (tr ("Show or hide the background toolbar."));
  m_actionViewBackground->setWhatsThis (tr ("View Background ToolBar\n\n"
                                            "Show or hide the background toolbar"));
  connect (m_actionViewBackground, SIGNAL (triggered ()), this, SLOT (slotViewToolBarBackground ()));

  m_actionViewChecklistGuide = new QAction (tr ("Checklist Guide Toolbar"), this);
  m_actionViewChecklistGuide->setCheckable (true);
  m_actionViewChecklistGuide->setChecked (false);
  m_actionViewChecklistGuide->setStatusTip (tr ("Show or hide the checklist guide."));
  m_actionViewChecklistGuide->setWhatsThis (tr ("View Checklist Guide\n\n"
                                                "Show or hide the checklist guide"));
  connect (m_actionViewChecklistGuide, SIGNAL (changed ()), this, SLOT (slotViewToolBarChecklistGuide()));

  m_actionViewFittingWindow = new QAction (tr ("Curve Fitting Window"), this);
  m_actionViewFittingWindow->setCheckable (true);
  m_actionViewFittingWindow->setChecked (false);
  m_actionViewFittingWindow->setStatusTip (tr ("Show or hide the curve fitting window."));
  m_actionViewFittingWindow->setWhatsThis (tr ("View Curve Fitting Window\n\n"
                                               "Show or hide the curve fitting window"));
  connect (m_actionViewFittingWindow, SIGNAL (changed ()), this, SLOT (slotViewToolBarFittingWindow()));

  m_actionViewGeometryWindow = new QAction (tr ("Geometry Window"), this);
  m_actionViewGeometryWindow->setCheckable (true);
  m_actionViewGeometryWindow->setChecked (false);
  m_actionViewGeometryWindow->setStatusTip (tr ("Show or hide the geometry window."));
  m_actionViewGeometryWindow->setWhatsThis (tr ("View Geometry Window\n\n"
                                                "Show or hide the geometry window"));
  connect (m_actionViewGeometryWindow, SIGNAL (changed ()), this, SLOT (slotViewToolBarGeometryWindow()));

  m_actionViewDigitize = new QAction (tr ("Digitizing Tools Toolbar"), this);
  m_actionViewDigitize->setCheckable (true);
  m_actionViewDigitize->setChecked (true);
  m_actionViewDigitize->setStatusTip (tr ("Show or hide the digitizing tools toolbar."));
  m_actionViewDigitize->setWhatsThis (tr ("View Digitizing Tools ToolBar\n\n"
                                          "Show or hide the digitizing tools toolbar"));
  connect (m_actionViewDigitize, SIGNAL (triggered ()), this, SLOT (slotViewToolBarDigitize()));

  m_actionViewSettingsViews = new QAction (tr ("Settings Views Toolbar"), this);
  m_actionViewSettingsViews->setCheckable (true);
  m_actionViewSettingsViews->setChecked (true);
  m_actionViewSettingsViews->setStatusTip (tr ("Show or hide the settings views toolbar."));
  m_actionViewSettingsViews->setWhatsThis (tr ("View Settings Views ToolBar\n\n"
                                               "Show or hide the settings views toolbar. These views graphically show the "
                                               "most important settings."));
  connect (m_actionViewSettingsViews, SIGNAL (triggered ()), this, SLOT (slotViewToolBarSettingsViews()));

  m_actionViewCoordSystem = new QAction (tr ("Coordinate System Toolbar"), this);
  m_actionViewCoordSystem->setCheckable (true);
  m_actionViewCoordSystem->setChecked (false);
  m_actionViewCoordSystem->setStatusTip (tr ("Show or hide the coordinate system toolbar."));
  m_actionViewCoordSystem->setWhatsThis (tr ("View Coordinate Systems ToolBar\n\n"
                                             "Show or hide the coordinate system selection toolbar. This toolbar is used "
                                             "to select the current coordinate system when the document has multiple "
                                             "coordinate systems. This toolbar is also used to view and print all coordinate "
                                             "systems.\n\n"
                                             "This toolbar is disabled when there is only one coordinate system."));
  connect (m_actionViewCoordSystem, SIGNAL (triggered ()), this, SLOT (slotViewToolBarCoordSystem()));

  m_actionViewToolTips = new QAction (tr ("Tool Tips"), this);
  m_actionViewToolTips->setCheckable (true);
  m_actionViewToolTips->setChecked (true);
  m_actionViewToolTips->setStatusTip (tr ("Show or hide the tool tips."));
  m_actionViewToolTips->setWhatsThis (tr ("View Tool Tips\n\n"
                                          "Show or hide the tool tips"));
  connect (m_actionViewToolTips, SIGNAL (triggered ()), this, SLOT (slotViewToolTips()));

  m_actionViewGridLines = new QAction (tr ("Grid Lines"), this);
  m_actionViewGridLines->setCheckable (true);
  m_actionViewGridLines->setChecked (false);
  m_actionViewGridLines->setStatusTip (tr ("Show or hide grid lines."));
  m_actionViewGridLines->setWhatsThis (tr ("View Grid Lines\n\n"
                                           "Show or hide grid lines that are added for accurate adjustments of the axes points, "
                                           "which can improve accuracy in distorted graphs"));
  connect (m_actionViewGridLines, SIGNAL (triggered ()), this, SLOT (slotViewGridLines()));

  m_actionViewBackgroundNone = new QAction (tr ("No Background"), this);
  m_actionViewBackgroundNone->setCheckable (true);
  m_actionViewBackgroundNone->setStatusTip (tr ("Do not show the image underneath the points."));
  m_actionViewBackgroundNone->setWhatsThis (tr ("No Background\n\n"
                                                "No image is shown so points are easier to see"));

  m_actionViewBackgroundOriginal = new QAction (tr ("Show Original Image"), this);
  m_actionViewBackgroundOriginal->setCheckable (true);
  m_actionViewBackgroundOriginal->setStatusTip (tr ("Show the original image underneath the points."));
  m_actionViewBackgroundOriginal->setWhatsThis (tr ("Show Original Image\n\n"
                                                    "Show the original image underneath the points"));

  m_actionViewBackgroundFiltered = new QAction (tr ("Show Filtered Image"), this);
  m_actionViewBackgroundFiltered->setCheckable (true);
  m_actionViewBackgroundFiltered->setChecked (true);
  m_actionViewBackgroundFiltered->setStatusTip (tr ("Show the filtered image underneath the points."));
  m_actionViewBackgroundFiltered->setWhatsThis (tr ("Show Filtered Image\n\n"
                                                    "Show the filtered image underneath the points.\n\n"
                                                    "The filtered image is created from the original image according to the "
                                                    "Filter preferences so unimportant information is hidden and important "
                                                    "information is emphasized"));

  m_actionViewCurvesNone = new QAction (tr ("Hide All Curves"), this);
  m_actionViewCurvesNone->setCheckable (true);
  m_actionViewCurvesNone->setStatusTip (tr ("Hide all digitized curves."));
  m_actionViewCurvesNone->setWhatsThis (tr ("Hide All Curves\n\n"
                                            "No axis points or digitized graph curves are shown so the image is easier to see."));

  m_actionViewCurvesSelected = new QAction (tr ("Show Selected Curve"), this);
  m_actionViewCurvesSelected->setCheckable (true);
  m_actionViewCurvesSelected->setStatusTip (tr ("Show only the currently selected curve."));
  m_actionViewCurvesSelected->setWhatsThis (tr ("Show Selected Curve\n\n"
                                                "Show only the digitized points and line that belong to the currently selected curve."));

  m_actionViewCurvesAll = new QAction (tr ("Show All Curves"), this);
  m_actionViewCurvesAll->setCheckable (true);
  m_actionViewCurvesAll->setChecked (true);
  m_actionViewCurvesAll->setStatusTip (tr ("Show all curves."));
  m_actionViewCurvesAll->setWhatsThis (tr ("Show All Curves\n\n"
                                           "Show all digitized axis points and graph curves"));

  m_groupBackground = new QActionGroup(this);
  m_groupBackground->addAction (m_actionViewBackgroundNone);
  m_groupBackground->addAction (m_actionViewBackgroundOriginal);
  m_groupBackground->addAction (m_actionViewBackgroundFiltered);
  connect (m_groupBackground, SIGNAL(triggered (QAction*)), this, SLOT (slotViewGroupBackground(QAction*)));

  m_groupCurves = new QActionGroup(this);
  m_groupCurves->addAction (m_actionViewCurvesNone);
  m_groupCurves->addAction (m_actionViewCurvesSelected);
  m_groupCurves->addAction (m_actionViewCurvesAll);
  connect (m_groupCurves, SIGNAL(triggered (QAction*)), this, SLOT (slotViewGroupCurves(QAction*)));

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
  // setShortCut is called by updateSettingsMainWindow
  connect (m_actionZoomOut, SIGNAL (triggered ()), this, SLOT (slotViewZoomOut ()));

  m_actionZoomIn = new QAction (tr ("Zoom In"), this);
  m_actionZoomIn->setStatusTip (tr ("Zoom in"));
  // setShortCut is called by updateSettingsMainWindow
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
  m_actionZoom1To1->setStatusTip (tr ("Zoom 1:1"));
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
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createCentralWidget";

  QWidget *widget = new QWidget;
  setCentralWidget (widget);
  m_layout = new QVBoxLayout;
  widget->setLayout (m_layout);
}

void MainWindow::createCommandStackShadow ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createCommandStackShadow";

  m_cmdStackShadow = new CmdStackShadow;
}

void MainWindow::createDockableWidgets ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createDockableWidgets";

  // Checklist guide starts out hidden. It will be positioned in settingsRead
  m_dockChecklistGuide = new ChecklistGuide (this);
  connect (m_dockChecklistGuide, SIGNAL (signalChecklistClosed()), this, SLOT (slotChecklistClosed()));

  // Fitting window starts out hidden since there is nothing to show initially. It will be positioned in settingsRead
  m_dockFittingWindow = new FittingWindow (this);
  connect (m_dockFittingWindow, SIGNAL (signalFittingWindowClosed()),
           this, SLOT (slotFittingWindowClosed()));
  connect (m_dockFittingWindow, SIGNAL (signalCurveFit(FittingCurveCoefficients, double, double, bool, bool)),
           this, SLOT (slotFittingWindowCurveFit(FittingCurveCoefficients, double, double, bool, bool)));

  // Geometry window starts out hidden since there is nothing to show initially. It will be positioned in settingsRead
  m_dockGeometryWindow = new GeometryWindow (this);
  connect (m_dockGeometryWindow, SIGNAL (signalGeometryWindowClosed()),
           this, SLOT (slotGeometryWindowClosed()));

}

void MainWindow::createHelpWindow ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createHelpWindow";

#ifndef OSX_RELEASE
  m_helpWindow = new HelpWindow (this);
  m_helpWindow->hide ();
  addDockWidget (Qt::RightDockWidgetArea,
                 m_helpWindow); // Dock area is required by addDockWidget but immediately overridden in next line
  m_helpWindow->setFloating (true);

  connect (m_actionHelpHelp, SIGNAL (triggered ()), m_helpWindow, SLOT (show ()));
#endif
}

void MainWindow::createIcons()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createIcons";

  QIcon icon;
  QPixmap icon16 (bannerapp_16);
  QPixmap icon32 (bannerapp_32);
  QPixmap icon64 (bannerapp_64);
  QPixmap icon128 (bannerapp_128);
  QPixmap icon256 (bannerapp_256);

  icon.addPixmap (icon16);
  icon.addPixmap (icon32);
  icon.addPixmap (icon64);
  icon.addPixmap (icon128);
  icon.addPixmap (icon256);

  setWindowIcon (icon);
}

void MainWindow::createLoadImageFromUrl ()
{
#ifdef NETWORKING
  m_loadImageFromUrl = new LoadImageFromUrl (*this);
#endif
}

void MainWindow::createMenus()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createMenus";

  m_menuFile = menuBar()->addMenu(tr("&File"));
  m_menuFile->addAction (m_actionImport);
  m_menuFile->addAction (m_actionImportAdvanced);
  m_menuFile->addAction (m_actionImportImageReplace);
  m_menuFile->addAction (m_actionOpen);
#ifndef OSX_RELEASE
  m_menuFileOpenRecent = new QMenu (tr ("Open &Recent"));
  for (unsigned int i = 0; i < MAX_RECENT_FILE_LIST_SIZE; i++) {
    m_menuFileOpenRecent->addAction (m_actionRecentFiles.at (i));
  }
  m_menuFile->addMenu (m_menuFileOpenRecent);
#endif
  m_menuFile->addAction (m_actionClose);
  m_menuFile->insertSeparator (m_actionSave);
  m_menuFile->addAction (m_actionSave);
  m_menuFile->addAction (m_actionSaveAs);
  m_menuFile->addAction (m_actionExport);
  m_menuFile->insertSeparator (m_actionPrint);
  m_menuFile->addAction (m_actionPrint);
  m_menuFile->insertSeparator (m_actionExit);
  m_menuFile->addAction (m_actionExit);

  m_menuEdit = menuBar()->addMenu(tr("&Edit"));
  connect (m_menuEdit, SIGNAL (aboutToShow ()), this, SLOT (slotEditMenu ()));
  m_menuEdit->addAction (m_actionEditUndo);
  m_menuEdit->addAction (m_actionEditRedo);
  m_menuEdit->insertSeparator (m_actionEditCut);
  m_menuEdit->addAction (m_actionEditCut);
  m_menuEdit->addAction (m_actionEditCopy);
  m_menuEdit->addAction (m_actionEditPaste);
  m_menuEdit->addAction (m_actionEditDelete);
  m_menuEdit->insertSeparator (m_actionEditPasteAsNew);
  m_menuEdit->addAction (m_actionEditPasteAsNew);
  m_menuEdit->addAction (m_actionEditPasteAsNewAdvanced);

  m_menuDigitize = menuBar()->addMenu(tr("Digitize"));
  m_menuDigitize->addAction (m_actionDigitizeSelect);
  m_menuDigitize->addAction (m_actionDigitizeAxis);
  m_menuDigitize->addAction (m_actionDigitizeScale);
  m_menuDigitize->addAction (m_actionDigitizeCurve);
  m_menuDigitize->addAction (m_actionDigitizePointMatch);
  m_menuDigitize->addAction (m_actionDigitizeColorPicker);
  m_menuDigitize->addAction (m_actionDigitizeSegment);

  m_menuView = menuBar()->addMenu(tr("View"));
  m_menuView->addAction (m_actionViewBackground);
  m_menuView->addAction (m_actionViewDigitize);
  m_menuView->addAction (m_actionViewChecklistGuide);
  m_menuView->addAction (m_actionViewFittingWindow);
  m_menuView->addAction (m_actionViewGeometryWindow);
  m_menuView->addAction (m_actionViewSettingsViews);
  m_menuView->addAction (m_actionViewCoordSystem);
  m_menuView->insertSeparator (m_actionViewToolTips);
  m_menuView->addAction (m_actionViewToolTips);
  m_menuView->addAction (m_actionViewGridLines);
  m_menuView->insertSeparator (m_actionViewBackgroundNone);
  m_menuViewBackground = new QMenu (tr ("Background"));
  m_menuViewBackground->addAction (m_actionViewBackgroundNone);
  m_menuViewBackground->addAction (m_actionViewBackgroundOriginal);
  m_menuViewBackground->addAction (m_actionViewBackgroundFiltered);
  m_menuView->addMenu (m_menuViewBackground);
  m_menuViewCurves = new QMenu (tr ("Curves"));
  m_menuViewCurves->addAction (m_actionViewCurvesNone);
  m_menuViewCurves->addAction (m_actionViewCurvesSelected);
  m_menuViewCurves->addAction (m_actionViewCurvesAll);
  m_menuView->addMenu (m_menuViewCurves);
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
  m_menuSettings->addAction (m_actionSettingsCurveAddRemove);
  m_menuSettings->addAction (m_actionSettingsCurveProperties);
  m_menuSettings->addAction (m_actionSettingsDigitizeCurve);
  m_menuSettings->addAction (m_actionSettingsExport);
  m_menuSettings->addAction (m_actionSettingsColorFilter);
  m_menuSettings->addAction (m_actionSettingsAxesChecker);
  m_menuSettings->addAction (m_actionSettingsGridDisplay);
  m_menuSettings->addAction (m_actionSettingsGridRemoval);
  m_menuSettings->addAction (m_actionSettingsPointMatch);
  m_menuSettings->addAction (m_actionSettingsSegments);
  m_menuSettings->insertSeparator (m_actionSettingsGeneral);
  m_menuSettings->addAction (m_actionSettingsGeneral);
  m_menuSettings->addAction (m_actionSettingsMainWindow);

  m_menuHelp = menuBar()->addMenu(tr("&Help"));
  m_menuHelp->addAction (m_actionHelpChecklistGuideWizard);
  m_menuHelp->insertSeparator(m_actionHelpWhatsThis);
  m_menuHelp->addAction (m_actionHelpWhatsThis);
  m_menuHelp->addAction (m_actionHelpTutorial);
#ifndef OSX_RELEASE
  m_menuHelp->addAction (m_actionHelpHelp);
#endif
  m_menuHelp->addAction (m_actionHelpAbout);

  updateRecentFileList();
}

void MainWindow::createNetwork ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createNetwork";

#ifdef NETWORKING
  m_networkClient = new NetworkClient (this);
#endif
}

void MainWindow::createSettingsDialogs ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createSettingsDialogs";

  m_dlgSettingsCoords = new DlgSettingsCoords (*this);
  m_dlgSettingsCurveAddRemove = new DlgSettingsCurveAddRemove (*this);
  m_dlgSettingsCurveProperties = new DlgSettingsCurveProperties (*this);
  m_dlgSettingsDigitizeCurve = new DlgSettingsDigitizeCurve (*this);
  m_dlgSettingsExportFormat = new DlgSettingsExportFormat (*this);
  m_dlgSettingsColorFilter = new DlgSettingsColorFilter (*this);
  m_dlgSettingsAxesChecker = new DlgSettingsAxesChecker (*this);
  m_dlgSettingsGridDisplay = new DlgSettingsGridDisplay (*this);
  m_dlgSettingsGridRemoval = new DlgSettingsGridRemoval (*this);
  m_dlgSettingsPointMatch = new DlgSettingsPointMatch (*this);
  m_dlgSettingsSegments = new DlgSettingsSegments (*this);
  m_dlgSettingsGeneral = new DlgSettingsGeneral (*this);
  m_dlgSettingsMainWindow = new DlgSettingsMainWindow (*this);

  m_dlgSettingsCoords->setVisible (false);
  m_dlgSettingsCurveAddRemove->setVisible (false);
  m_dlgSettingsCurveProperties->setVisible (false);
  m_dlgSettingsDigitizeCurve->setVisible (false);
  m_dlgSettingsExportFormat->setVisible (false);
  m_dlgSettingsColorFilter->setVisible (false);
  m_dlgSettingsAxesChecker->setVisible (false);
  m_dlgSettingsGridDisplay->setVisible (false);
  m_dlgSettingsGridRemoval->setVisible (false);
  m_dlgSettingsPointMatch->setVisible (false);
  m_dlgSettingsSegments->setVisible (false);
  m_dlgSettingsGeneral->setVisible (false);
  m_dlgSettingsMainWindow->setVisible (false);
}

void MainWindow::createScene ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createScene";

  m_scene = new GraphicsScene (this);
  m_view = new GraphicsView (m_scene, *this);
  m_layout->addWidget (m_view);
}

void MainWindow::createStateContextBackground ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createStateContextBackground";

  m_backgroundStateContext = new BackgroundStateContext (*this);
}

void MainWindow::createStateContextDigitize ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createStateContextDigitize";

  m_digitizeStateContext = new DigitizeStateContext (*this,
                                                     *m_view,
                                                     m_isGnuplot);
}

void MainWindow::createStateContextTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createStateContextTransformation";

  ENGAUGE_CHECK_PTR (m_scene);

  m_transformationStateContext = new TransformationStateContext (*m_scene,
                                                                 m_isGnuplot);
}

void MainWindow::createStatusBar ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createStatusBar";

  m_statusBar = new StatusBar (*statusBar ());
  connect (this, SIGNAL (signalZoom(int)), m_statusBar, SLOT (slotZoom(int)));
  connect (m_statusBar, SIGNAL (signalZoom (int)), this, SLOT (slotViewZoom (int)));
}

void MainWindow::createToolBars ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createToolBars";

  const int VIEW_SIZE = 22;

  // Background toolbar widgets
  m_cmbBackground = new QComboBox ();
  m_cmbBackground->setEnabled (false);
  m_cmbBackground->setStatusTip (tr ("Select background image"));
  m_cmbBackground->setWhatsThis (tr ("Selected Background\n\n"
                                     "Select background image:\n"
                                     "1) No background which highlights points\n"
                                     "2) Original image which shows everything\n"
                                     "3) Filtered image which highlights important details"));
  m_cmbBackground->addItem (tr ("No background"), QVariant (BACKGROUND_IMAGE_NONE));
  m_cmbBackground->addItem (tr ("Original image"), QVariant (BACKGROUND_IMAGE_ORIGINAL));
  m_cmbBackground->addItem (tr ("Filtered image"), QVariant (BACKGROUND_IMAGE_FILTERED));
  // selectBackgroundOriginal needs currentIndexChanged
  connect (m_cmbBackground, SIGNAL (currentIndexChanged (int)), this, SLOT (slotCmbBackground (int)));

  // Background toolbar
  m_toolBackground = new QToolBar (tr ("Background"), this);
  m_toolBackground->addWidget (m_cmbBackground);
  addToolBar (m_toolBackground);

  // Digitize toolbar widgets that are not created elsewhere
  m_cmbCurve = new QComboBox ();
  m_cmbCurve->setEnabled (false);
  m_cmbCurve->setMinimumWidth (180);
  m_cmbCurve->setStatusTip (tr ("Select curve for new points."));
  m_cmbCurve->setWhatsThis (tr ("Selected Curve Name\n\n"
                                "Select curve for any new points. Every point belongs to one curve.\n\n"
                                "This can be changed while in Curve Point, Point Match, Color Picker or Segment Fill mode."));
  connect (m_cmbCurve, SIGNAL (activated (int)), this, SLOT (slotCmbCurve (int))); // activated() ignores code changes

  // Digitize toolbar
  m_toolDigitize = new QToolBar (tr ("Drawing"), this);
  m_toolDigitize->addAction (m_actionDigitizeSelect);
  m_toolDigitize->insertSeparator (m_actionDigitizeAxis);
  m_toolDigitize->addAction (m_actionDigitizeAxis);
  m_toolDigitize->addAction (m_actionDigitizeScale);
  m_toolDigitize->insertSeparator (m_actionDigitizeCurve);
  m_toolDigitize->addAction (m_actionDigitizeCurve);
  m_toolDigitize->addAction (m_actionDigitizePointMatch);
  m_toolDigitize->addAction (m_actionDigitizeColorPicker);
  m_toolDigitize->addAction (m_actionDigitizeSegment);
  m_toolDigitize->addWidget (m_cmbCurve);
  addToolBar (m_toolDigitize);

  // Views toolbar widgets
  m_viewPointStyle = new ViewPointStyle();
  m_viewPointStyle->setMinimumSize(VIEW_SIZE, VIEW_SIZE);
  m_viewPointStyle->setMaximumSize(VIEW_SIZE, VIEW_SIZE);
  m_viewPointStyle->setStatusTip (tr ("Points style for the currently selected curve"));
  m_viewPointStyle->setWhatsThis (tr ("Points Style\n\n"
                                      "Points style for the currently selected curve. The points style is only "
                                      "displayed in this toolbar. To change the points style, "
                                      "use the Curve Properties dialog."));

  m_viewSegmentFilter = new ViewSegmentFilter();
  m_viewSegmentFilter->setMinimumSize(VIEW_SIZE, VIEW_SIZE);
  m_viewSegmentFilter->setMaximumSize(VIEW_SIZE, VIEW_SIZE);
  m_viewSegmentFilter->setStatusTip (tr ("View of filter for current curve in Segment Fill mode"));
  m_viewSegmentFilter->setWhatsThis (tr ("Segment Fill Filter\n\n"
                                         "View of filter for the current curve in Segment Fill mode. The filter settings are only "
                                         "displayed in this toolbar. To changed the filter settings, "
                                         "use the Color Picker mode or the Filter Settings dialog."));

  // Settings views toolbar
  m_toolSettingsViews = new QToolBar (tr ("Views"), this);
  m_toolSettingsViews->addWidget (m_viewPointStyle);
  m_toolSettingsViews->addWidget (new QLabel (" ")); // A hack, but this works to put some space between the adjacent widgets
  m_toolSettingsViews->addWidget (m_viewSegmentFilter);
  addToolBar (m_toolSettingsViews);

  // Coordinate system toolbar
  m_cmbCoordSystem = new QComboBox;
  m_cmbCoordSystem->setEnabled (false);
  m_cmbCoordSystem->setStatusTip (tr ("Currently selected coordinate system"));
  m_cmbCoordSystem->setWhatsThis (tr ("Selected Coordinate System\n\n"
                                      "Currently selected coordinate system. This is used to switch between coordinate systems "
                                      "in documents with multiple coordinate systems"));
  connect (m_cmbCoordSystem, SIGNAL (activated (int)), this, SLOT (slotCmbCoordSystem (int)));

  m_btnShowAll = new QPushButton(QIcon(":/engauge/img/icon_show_all.png"), "");
  m_btnShowAll->setEnabled (false);
  m_btnShowAll->setAcceptDrops(false);
  m_btnShowAll->setStatusTip (tr ("Show all coordinate systems"));
  m_btnShowAll->setWhatsThis (tr ("Show All Coordinate Systems\n\n"
                                  "When pressed and held, this button shows all digitized points and lines for all coordinate systems."));
  connect (m_btnShowAll, SIGNAL (pressed ()), this, SLOT (slotBtnShowAllPressed ()));
  connect (m_btnShowAll, SIGNAL (released ()), this, SLOT (slotBtnShowAllReleased ()));

  m_btnPrintAll = new QPushButton(QIcon(":/engauge/img/icon_print_all.png"), "");
  m_btnPrintAll->setEnabled (false);
  m_btnPrintAll->setAcceptDrops(false);
  m_btnPrintAll->setStatusTip (tr ("Print all coordinate systems"));
  m_btnPrintAll->setWhatsThis (tr ("Print All Coordinate Systems\n\n"
                                  "When pressed, this button Prints all digitized points and lines for all coordinate systems."));
  connect (m_btnPrintAll, SIGNAL (pressed ()), this, SLOT (slotBtnPrintAll ()));

  m_toolCoordSystem = new QToolBar (tr ("Coordinate System"), this);
  m_toolCoordSystem->addWidget (m_cmbCoordSystem);
  m_toolCoordSystem->addWidget (m_btnShowAll);
  m_toolCoordSystem->addWidget (m_btnPrintAll);
  addToolBar (m_toolCoordSystem);
}

void MainWindow::createTutorial ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createTutorial";

  m_tutorialDlg = new TutorialDlg (this);
  m_tutorialDlg->setModal (true);
  m_tutorialDlg->setMinimumSize (500, 400);
  m_tutorialDlg->hide();
}

void MainWindow::createZoomMap ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::createZoomMap";

  m_zoomMap [ZOOM_INITIAL_16_TO_1] = ZOOM_16_TO_1;
  m_zoomMap [ZOOM_INITIAL_8_TO_1] = ZOOM_8_TO_1;
  m_zoomMap [ZOOM_INITIAL_4_TO_1] = ZOOM_4_TO_1;
  m_zoomMap [ZOOM_INITIAL_2_TO_1] = ZOOM_2_TO_1;
  m_zoomMap [ZOOM_INITIAL_1_TO_1] = ZOOM_1_TO_1;
  m_zoomMap [ZOOM_INITIAL_1_TO_2] = ZOOM_1_TO_2;
  m_zoomMap [ZOOM_INITIAL_1_TO_4] = ZOOM_1_TO_4;
  m_zoomMap [ZOOM_INITIAL_1_TO_8] = ZOOM_1_TO_8;
  m_zoomMap [ZOOM_INITIAL_1_TO_16] = ZOOM_1_TO_16;
  m_zoomMap [ZOOM_INITIAL_FILL] = ZOOM_FILL;
}

ZoomFactor MainWindow::currentZoomFactor () const
{
  if (m_actionZoom1To1->isChecked()) {
    return ZOOM_1_TO_1;
  } else if (m_actionZoom1To2->isChecked()) {
    return ZOOM_1_TO_2;
  } else if (m_actionZoom1To4->isChecked()) {
    return ZOOM_1_TO_4;
  } else if (m_actionZoom1To8->isChecked()) {
    return ZOOM_1_TO_8;
  } else if (m_actionZoom1To16->isChecked()) {
    return ZOOM_1_TO_16;
  } else if (m_actionZoom2To1->isChecked()) {
    return ZOOM_2_TO_1;
  } else if (m_actionZoom4To1->isChecked()) {
    return ZOOM_4_TO_1;
  } else if (m_actionZoom8To1->isChecked()) {
    return ZOOM_8_TO_1;
  } else if (m_actionZoom16To1->isChecked()) {
    return ZOOM_16_TO_1;
  } else if (m_actionZoomFill->isChecked()) {
    return ZOOM_FILL;
  } else {
    ENGAUGE_ASSERT (false);
    return ZOOM_1_TO_1;
  }
}
bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
  if (event->type () == QEvent::KeyPress) {

    QKeyEvent *eventKeyPress = (QKeyEvent *) event;

    // Special shortcuts. All of these are probably only useful for debugging and/or regression testing
    if ((eventKeyPress->key() == Qt::Key_E) &&
        ((eventKeyPress->modifiers() & Qt::ShiftModifier) != 0) &&
        ((eventKeyPress->modifiers() & Qt::ControlModifier) != 0)) {

      saveErrorReportFileAndExit ("Shift+Control+E",
                                  __FILE__,
                                  __LINE__,
                                  "userTriggered");

    }
  }

  return QObject::eventFilter (target, event);
}

#ifndef OSX_RELEASE
void MainWindow::exportAllCoordinateSystemsAfterRegressionTests()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::exportAllCoordinateSystemsAfterRegressionTests curDir=" << QDir::currentPath().toLatin1().data();

  // Output the regression test results. One file is output for every coordinate system
  for (CoordSystemIndex index = 0; index < m_cmdMediator->document().coordSystemCount(); index++) {

    updateCoordSystem (index); // Switch to the specified coordinate system

    QString regressionFile = QString ("%1_%2")
                             .arg (m_regressionFile)
                             .arg (index + 1); // Append the coordinate system index

    // Normally we just export to a file, but when regression testing the export will fail since coordinates are not defined. To
    // get an export file when regression testing, we just output the image size
    if (m_isErrorReportRegressionTest && !m_transformation.transformIsDefined()) {

      ExportImageForRegression exportStrategy (m_cmdMediator->pixmap ());
      exportStrategy.fileExport (regressionFile);

    } else {

      ExportToFile exportStrategy;

      fileExport (regressionFile,
                  exportStrategy);
    }
  }
}
#endif

QString MainWindow::exportFilenameFromInputFilename (const QString &fileName) const
{
  QString outFileName = fileName;

  outFileName = outFileName.replace (".xml", ".csv_actual"); // Applies when extension is xml
  outFileName = outFileName.replace (".dig", ".csv_actual"); // Applies when extension is dig
  outFileName = outFileName.replace (".pdf", ".csv_actual"); // Applies when extension is pdf

  return outFileName;
}

void MainWindow::fileExport(const QString &fileName,
                            ExportToFile exportStrategy)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::fileExport"
                              << " curDir=" << QDir::currentPath().toLatin1().data()
                              << " fileName=" << fileName.toLatin1().data();

  QFile file (fileName);
  if (file.open(QIODevice::WriteOnly)) {

    QTextStream str (&file);

    DocumentModelExportFormat modelExportFormat = modelExportOverride (m_cmdMediator->document().modelExport(),
                                                                       exportStrategy,
                                                                       fileName);
    exportStrategy.exportToFile (modelExportFormat,
                                 m_cmdMediator->document(),
                                 m_modelMainWindow,
                                 transformation (),
                                 str);

    updateChecklistGuide ();
    m_statusBar->showTemporaryMessage("File saved");

  } else {

    LOG4CPP_ERROR_S ((*mainCat)) << "MainWindow::fileExport"
                                 << " file=" << fileName.toLatin1().data()
                                 << " curDir=" << QDir::currentPath().toLatin1().data();
    QMessageBox::critical (0,
                           engaugeWindowTitle(),
                           tr ("Unable to export to file ") + fileName);
  }
}

void MainWindow::fileImport (const QString &fileName,
                             ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::fileImport"
                              << " fileName=" << fileName.toLatin1 ().data ()
                              << " curDir=" << QDir::currentPath().toLatin1().data()
                              << " importType=" << importType;

  QString originalFileOld = m_originalFile;
  bool originalFileWasImported = m_originalFileWasImported;

  m_originalFile = fileName; // Make this available for logging in case an error occurs during the load
  m_originalFileWasImported = true;

  if (importType == IMPORT_TYPE_ADVANCED) {

    // Remove any existing points, axes checker(s) and such from the previous Document so they do not appear in setupAfterLoadNewDocument
    // when previewing for IMAGE_TYPE_ADVANCED
    slotFileClose();

    // Restore the background just closed by slotFileClose. This is required so when the image is loaded for preview, it will appear
    m_backgroundStateContext->setBackgroundImage(BACKGROUND_IMAGE_ORIGINAL);
  }

  QImage image;
  bool loaded = false;

#ifdef ENGAUGE_JPEG2000
  Jpeg2000 jpeg2000;
  loaded = jpeg2000.load (fileName,
                          image);
#endif // ENGAUGE_JPEG2000

#ifdef ENGAUGE_PDF
  if (!loaded) {
    
    Pdf pdf;
    PdfReturn pdfReturn = pdf.load (fileName,
                                    image,
                                    m_modelMainWindow.pdfResolution(),
                                    m_modelMainWindow.importCropping(),
                                    m_isErrorReportRegressionTest);
    if (pdfReturn == PDF_RETURN_CANCELED) {

      // User canceled so exit immediately
      return;

    }

    loaded = (pdfReturn == PDF_RETURN_SUCCESS);
  }
#endif // ENGAUGE_PDF

  if (!loaded) {
    NonPdf nonPdf;
    NonPdfReturn nonPdfReturn = nonPdf.load (fileName,
                                             image,
                                             m_modelMainWindow.importCropping(),
                                             m_isErrorReportRegressionTest);
    if (nonPdfReturn == NON_PDF_RETURN_CANCELED) {

      // User canceled so exit immediately
      return;

    }

    loaded = (nonPdfReturn == NON_PDF_RETURN_SUCCESS);
  }

  if (!loaded) {
    QString msg = QString("%1 %2 %3 %4.")
                  .arg (tr ("Cannot read file"))
                  .arg (fileName)
                  .arg (tr ("from directory"))
                  .arg (QDir::currentPath());
    QMessageBox::warning (this,
                          engaugeWindowTitle(),
                          msg);

    // Reset
    m_originalFile = originalFileOld;
    m_originalFileWasImported = originalFileWasImported;

  } else {

    loaded = loadImage (fileName,
                        image,
                        importType);

    if (!loaded) {

      // Failed
      if (importType == IMPORT_TYPE_ADVANCED) {

        // User cancelled after another file was imported so it could be previewed. In anticipation of the loading-for-preview,
        // we closed the current Document at the top of this method so we cannot reload. So, the only option is to close again
        // so the half-imported current Document is removed
        slotFileClose();

      } else {

        // Reset
        m_originalFile = originalFileOld;
        m_originalFileWasImported = originalFileWasImported;
      }
    }
  }
}

void MainWindow::fileImportWithPrompts (ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::fileImportWithPrompts"
                              << " importType=" << importType;

  // Skip maybeSave method for IMPORT_TYPE_REPLACE_IMAGE since open file dialog is enough to allow user to cancel the operation, and
  // since no information is lost in that case
  bool okToContinue = true;
  if (importType != IMPORT_TYPE_IMAGE_REPLACE) {
    okToContinue = maybeSave ();
  }

  if (okToContinue) {

    QString filter;
    QTextStream str (&filter);

    // Compile a list of supported formats into a filter
    QList<QByteArray>::const_iterator itr;
    QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();
    QStringList supportedImageFormatStrings;
    for (itr = supportedImageFormats.begin (); itr != supportedImageFormats.end (); itr++) {
      QByteArray arr = *itr;
      QString extensionAsWildcard = QString ("*.%1").arg (QString (arr));
      supportedImageFormatStrings << extensionAsWildcard;
    }
#ifdef ENGAUGE_JPEG2000
    Jpeg2000 jpeg2000;
    supportedImageFormatStrings << jpeg2000.supportedImageWildcards();
#endif // ENGAUGE_JPEG2000

#ifdef ENGAUGE_PDF
    supportedImageFormatStrings << "*.pdf";
#endif // ENGAUGE_PDF

    supportedImageFormatStrings.sort();

    str << "Image Files (" << supportedImageFormatStrings.join (" ") << ")";

    // Allow selection of files with strange suffixes in case the file extension was changed. Since
    // the default is the first filter, we add this afterwards (it is the off-nominal case)
    str << ";; All Files (*.*)";

    QString fileName = QFileDialog::getOpenFileName (this,
                                                     tr("Import Image"),
                                                     QDir::currentPath (),
                                                     filter);
    if (!fileName.isEmpty ()) {

      // We import the file BEFORE asking the number of coordinate systems, so user can see how many there are
      fileImport (fileName,
                  importType);
    }
  }
}

void MainWindow::filePaste (ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::filePaste"
                              << " importType=" << importType;

  QString originalFileOld = m_originalFile;
  bool originalFileWasImported = m_originalFileWasImported;

  QString fileName ("clipboard");
  m_originalFile = fileName; // Make this available for logging in case an error occurs during the load
  m_originalFileWasImported = true;

  if (importType == IMPORT_TYPE_ADVANCED) {

    // Remove any existing points, axes checker(s) and such from the previous Document so they do not appear in setupAfterLoadNewDocument
    // when previewing for IMAGE_TYPE_ADVANCED
    slotFileClose();

    // Restore the background just closed by slotFileClose. This is required so when the image is loaded for preview, it will appear
    m_backgroundStateContext->setBackgroundImage(BACKGROUND_IMAGE_ORIGINAL);
  }

  // An image was in the clipboard when this method was called but it may have disappeared
  QImage image = QApplication::clipboard()->image();

  bool loaded = false;
  if (!loaded) {
    loaded = !image.isNull();
  }

  if (!loaded) {
    QMessageBox::warning (this,
                          engaugeWindowTitle(),
                          QString("%1 %2 %3 %4.")
                          .arg (tr ("Cannot read file"))
                          .arg (fileName)
                          .arg (tr ("from directory"))
                          .arg (QDir::currentPath ()));

    // Reset
    m_originalFile = originalFileOld;
    m_originalFileWasImported = originalFileWasImported;

  } else {

    loaded = loadImage (fileName,
                        image,
                        importType);

    if (!loaded) {

      // Failed
      if (importType == IMPORT_TYPE_ADVANCED) {

        // User cancelled after another file was imported so it could be previewed. In anticipation of the loading-for-preview,
        // we closed the current Document at the top of this method so we cannot reload. So, the only option is to close again
        // so the half-imported current Document is removed
        slotFileClose();

      } else {

        // Reset
        m_originalFile = originalFileOld;
        m_originalFileWasImported = originalFileWasImported;
      }
    }
  }
}

void MainWindow::ghostsCreate ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::ghostsCreate";

  ENGAUGE_ASSERT (m_ghosts == 0);
  m_ghosts = new Ghosts (m_cmdMediator->document().coordSystemIndex());

  for (unsigned int index = 0; index < m_cmdMediator->document().coordSystemCount(); index++) {

    // Skip this coordinate system if it is the selected coordinate system since it will be displayed anyway, so no ghosts are required
    if (index != m_ghosts->coordSystemIndexToBeRestored ()) {

      updateCoordSystem (index);

      // Take a snapshot of the graphics items
      m_ghosts->captureGraphicsItems (*m_scene);
    }
  }

  // Restore the coordinate system that was originally selected, so its points/lines are visible
  updateCoordSystem (m_ghosts->coordSystemIndexToBeRestored ());

  // Make visible ghosts
  m_ghosts->createGhosts (*m_scene);
}

void MainWindow::ghostsDestroy ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::ghostsDestroy";

  ENGAUGE_CHECK_PTR (m_ghosts);

  m_ghosts->destroyGhosts(*m_scene);

  delete m_ghosts;
  m_ghosts = 0;
}

QImage MainWindow::imageFiltered () const
{
  return m_backgroundStateContext->imageForCurveState();
}

bool MainWindow::isGnuplot() const
{
  return m_isGnuplot;
}

void MainWindow::loadCoordSystemListFromCmdMediator ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadCoordSystemListFromCmdMediator";

  m_cmbCoordSystem->clear();

  unsigned int numberCoordSystem = m_cmdMediator->document().coordSystemCount();

  for (unsigned int i = 0; i < numberCoordSystem; i++) {
    int index1Based = i + 1;
    m_cmbCoordSystem->addItem (QString::number (index1Based),
                               QVariant (i));
  }

  // Always start with the first entry selected
  m_cmbCoordSystem->setCurrentIndex (0);

  // Disable the controls if there is only one entry. Hopefully the user will not even notice it, thus simplifying the interface
  bool enable = (m_cmbCoordSystem->count() > 1);
  m_cmbCoordSystem->setEnabled (enable);
  m_btnShowAll->setEnabled (enable);
  m_btnPrintAll->setEnabled (enable);
}

void MainWindow::loadCurveListFromCmdMediator ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadCurveListFromCmdMediator";

  m_cmbCurve->clear ();
  QStringList curvesGraphsNames = m_cmdMediator->curvesGraphsNames ();
  QStringList::iterator itr;
  for (itr = curvesGraphsNames.begin (); itr != curvesGraphsNames.end (); itr++) {

    QString curvesGraphName = *itr;
    m_cmbCurve->addItem (curvesGraphName);
  }

  // Select the curve that is associated with the current coordinate system
  m_cmbCurve->setCurrentText (m_cmdMediator->selectedCurveName ());
}

void MainWindow::loadDocumentFile (const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadDocumentFile fileName=" << fileName.toLatin1 ().data ();

  QApplication::setOverrideCursor(Qt::WaitCursor);
  CmdMediator *cmdMediator = new CmdMediator (*this,
                                              fileName);

  if (cmdMediator->successfulRead ()) {

    setCurrentPathFromFile (fileName);
    rebuildRecentFileListForCurrentFile(fileName);
    m_currentFile = fileName; // This enables the FileSaveAs menu option

    if (m_cmdMediator != 0) {
      delete m_cmdMediator;
      m_cmdMediator = 0;
    }

    m_cmdMediator = cmdMediator;
    setupAfterLoadNewDocument (fileName,
                               "File opened",
                               IMPORT_TYPE_SIMPLE);

    // Start select mode
    m_actionDigitizeSelect->setChecked (true); // We assume user wants to first select existing stuff
    slotDigitizeSelect(); // Trigger transition so cursor gets updated immediately

    m_engaugeFile = fileName;
    m_originalFile = fileName; // This is needed by updateAfterCommand below if an error report is generated
    m_originalFileWasImported = false;

    updateGridLines ();
    updateAfterCommand (); // Enable Save button now that m_engaugeFile is set

    QApplication::restoreOverrideCursor();

  } else {

    QApplication::restoreOverrideCursor();

    QMessageBox::warning (this,
                          engaugeWindowTitle(),
                          QString("%1 %2 %3 %4:\n%5.")
                          .arg (tr ("Cannot read file"))
                          .arg (fileName)
                          .arg (tr ("from directory"))
                          .arg (QDir::currentPath ())
                          .arg(cmdMediator->reasonForUnsuccessfulRead ()));
    delete cmdMediator;

  }
}

void MainWindow::loadErrorReportFile(const QString &errorReportFile)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadErrorReportFile"
                              << " file=" << errorReportFile.toLatin1().data();

  QFile file (errorReportFile);
  if (!file.exists()) {
    // Convert path from relative to absolute so file-not-found errors are easier to fix
    QFileInfo fileInfo (errorReportFile);

    QMessageBox::critical (this,
                           engaugeWindowTitle(),
                           tr ("File not found:") + " " + fileInfo.absoluteFilePath());
    exit (-1);
  }

  // Open the error report file as if it was a regular Document file
  QXmlStreamReader reader (&file);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  m_cmdMediator = new CmdMediator(*this,
                                  errorReportFile);

  // Load the commands into the shadow command stack
  m_cmdStackShadow->loadCommands (*this,
                                  m_cmdMediator->document(),
                                  reader);
  file.close();

  setupAfterLoadNewDocument (errorReportFile,
                             "Error report opened",
                             IMPORT_TYPE_SIMPLE);

  // Start select mode
  m_actionDigitizeSelect->setChecked (true); // We assume user wants to first select existing stuff
  slotDigitizeSelect(); // Trigger transition so cursor gets updated immediately

  updateAfterCommand ();
}

bool MainWindow::loadImage (const QString &fileName,
                            const QImage &image,
                            ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadImage"
                              << " fileName=" << fileName.toLatin1 ().data ()
                              << " importType=" << importType;

  bool success;
  if (importType == IMPORT_TYPE_IMAGE_REPLACE) {
    success = loadImageReplacingImage (fileName,
                                       image,
                                       importType);
  } else {
    success = loadImageNewDocument (fileName,
                                    image,
                                    importType);
  }

  return success;
}

bool MainWindow::loadImageNewDocument (const QString &fileName,
                                       const QImage &image,
                                       ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadImageNewDocument"
                              << " fileName=" << fileName.toLatin1 ().data ()
                              << " importType=" << importType;

  ENGAUGE_ASSERT (importType != IMPORT_TYPE_IMAGE_REPLACE);

  QApplication::setOverrideCursor(Qt::WaitCursor);
  CmdMediator *cmdMediator = new CmdMediator (*this,
                                              image);
  QApplication::restoreOverrideCursor();

  setCurrentPathFromFile (fileName);
  // We do not call rebuildRecentFileListForCurrentFile for an image file, so only proper Engauge document files appear in the recent file list
  m_engaugeFile = EMPTY_FILENAME; // Forces first Save to be treated as Save As

  if (m_cmdMediator != 0) {
    delete m_cmdMediator;
    m_cmdMediator = 0;
  }

  m_cmdMediator = cmdMediator;
  bool accepted = setupAfterLoadNewDocument (fileName,
                                             tr ("File imported"),
                                             importType);

  if (accepted) {

    // Show the wizard if user selected it and we are not running a script
    if (m_actionHelpChecklistGuideWizard->isChecked () &&
        (m_fileCmdScript == 0)) {

      // Show wizard
      ChecklistGuideWizard *wizard = new ChecklistGuideWizard (*this,
                                                               m_cmdMediator->document().coordSystemCount());
      if (wizard->exec() == QDialog::Accepted) {

        for (CoordSystemIndex coordSystemIndex = 0; coordSystemIndex < m_cmdMediator->document().coordSystemCount(); coordSystemIndex++) {

          // Populate the checklist guide
          m_dockChecklistGuide->setTemplateHtml (wizard->templateHtml(coordSystemIndex),
                                                 wizard->curveNames(coordSystemIndex));

          // Update Document
          CurvesGraphs curvesGraphs;
          wizard->populateCurvesGraphs (coordSystemIndex,
                                        curvesGraphs);
          m_cmdMediator->document().setCurvesGraphs(curvesGraphs);
        }

        // Unhide the checklist guide
        m_actionViewChecklistGuide->setChecked (true);

        // Update the curve dropdown
        loadCurveListFromCmdMediator();

        // Update the CoordSystem dropdown
        loadCoordSystemListFromCmdMediator();
      }
      delete wizard;
    }

    // Start axis mode
    m_actionDigitizeAxis->setChecked (true); // We assume user first wants to digitize axis points

    // Trigger transition so cursor gets updated immediately
    if (modeMap ()) {
      slotDigitizeScale ();
    } else if (modeGraph ()) {
      slotDigitizeAxis ();
    }

    updateControls ();
  }

  return accepted;
}

bool MainWindow::loadImageReplacingImage (const QString &fileName,
                                          const QImage &image,
                                          ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::loadImageReplacingImage"
                              << " fileName=" << fileName.toLatin1 ().data ()
                              << " importType=" << importType;

  ENGAUGE_ASSERT (importType == IMPORT_TYPE_IMAGE_REPLACE);

  setCurrentPathFromFile (fileName);
  // We do not call rebuildRecentFileListForCurrentFile for an image file, so only proper Engauge document files appear in the recent file list
  m_engaugeFile = EMPTY_FILENAME; // Forces first Save to be treated as Save As

  ENGAUGE_ASSERT (m_cmdMediator != 0); // Menu option should only be available when a document is currently open

  m_cmdMediator->document().setPixmap (image);

  bool accepted = setupAfterLoadReplacingImage (fileName,
                                                tr ("File imported"),
                                                importType);

  // No checklist guide wizard is displayed when just replacing the image

  return accepted;
}

void MainWindow::loadInputFileForErrorReport(QDomDocument &domInputFile) const
{
  QFile file (m_originalFile);

  // File should be available for opening, if not then the dom will be left empty. We assume it has not been
  // modified since opened
  if (!file.open (QIODevice::ReadOnly)) {
    return;
  }

  domInputFile.setContent (&file);
  file.close();
}

void MainWindow::loadToolTips()
{
  if (m_actionViewToolTips->isChecked ()) {

    // Show tool tips
    m_actionDigitizeSelect->setToolTip (m_actionDigitizeSelect->text());
    m_actionDigitizeAxis->setToolTip (m_actionDigitizeAxis->text());
    m_actionDigitizeScale->setToolTip (m_actionDigitizeScale->text());
    m_actionDigitizeCurve->setToolTip (m_actionDigitizeCurve->text());
    m_actionDigitizePointMatch->setToolTip (m_actionDigitizePointMatch->text());
    m_actionDigitizeColorPicker->setToolTip (m_actionDigitizeColorPicker->text());
    m_actionDigitizeSegment->setToolTip (m_actionDigitizeSegment->text());
    m_cmbBackground->setToolTip (tr ("Background image."));
    m_cmbCurve->setToolTip (tr ("Currently selected curve."));
    m_viewPointStyle->setToolTip (tr ("Point style for currently selected curve."));
    m_viewSegmentFilter->setToolTip (tr ("Segment Fill filter for currently selected curve."));

  } else {

    // Remove any previous tool tips
    m_actionDigitizeSelect->setToolTip ("");
    m_actionDigitizeAxis->setToolTip ("");
    m_actionDigitizeScale->setToolTip ("");
    m_actionDigitizeCurve->setToolTip ("");
    m_actionDigitizePointMatch->setToolTip ("");
    m_actionDigitizeColorPicker->setToolTip ("");
    m_actionDigitizeSegment->setToolTip ("");
    m_cmbBackground->setToolTip ("");
    m_cmbCurve->setToolTip ("");
    m_viewPointStyle->setToolTip ("");
    m_viewSegmentFilter->setToolTip ("");

  }
}

bool MainWindow::modeGraph () const
{
  bool success = false;

  if (m_cmdMediator != 0) {
    success = (m_cmdMediator->document().documentAxesPointsRequired() != DOCUMENT_AXES_POINTS_REQUIRED_2);
  }

  return success;
}

bool MainWindow::modeMap () const
{
  bool success = false;

  if (m_cmdMediator != 0) {
    success = (m_cmdMediator->document().documentAxesPointsRequired() == DOCUMENT_AXES_POINTS_REQUIRED_2);
  }

  return success;
}

bool MainWindow::maybeSave()
{
  if (m_cmdMediator != 0) {
    if (m_cmdMediator->isModified()) {
      QMessageBox::StandardButton ret = QMessageBox::warning (this,
                                                              engaugeWindowTitle(),
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

DocumentModelExportFormat MainWindow::modelExportOverride (const DocumentModelExportFormat &modelExportFormatBefore,
                                                           const ExportToFile &exportStrategy,
                                                           const QString &fileName) const
{
  DocumentModelExportFormat modelExportFormatAfter = modelExportFormatBefore;

  // See if delimiter setting overrides commas/tabs for files with csv/tsv file extensions respectively
  if (!modelExportFormatAfter.overrideCsvTsv()) {

    // Extract file extensions
    QString csvExtension = QString (".%1")
                           .arg (exportStrategy.fileExtensionCsv());
    QString tsvExtension = QString (".%1")
                           .arg (exportStrategy.fileExtensionTsv());
    QString fileExtensionVersusCsv = fileName.right (csvExtension.size());
    QString fileExtensionVersusTsv = fileName.right (tsvExtension.size());

    // Override if CSV or TSV was selected. We cannot use QFileDialog::selectedNameFilter() since that is
    // broken in Linux, so we use the file extension
    if (csvExtension.compare (fileExtensionVersusCsv, Qt::CaseInsensitive) == 0) {
      modelExportFormatAfter.setDelimiter (EXPORT_DELIMITER_COMMA);
    } else if (tsvExtension.compare (fileExtensionVersusTsv, Qt::CaseInsensitive) == 0) {
      modelExportFormatAfter.setDelimiter (EXPORT_DELIMITER_TAB);
    }
  }

  return modelExportFormatAfter;
}

MainWindowModel MainWindow::modelMainWindow () const
{
  return m_modelMainWindow;
}

void MainWindow::rebuildRecentFileListForCurrentFile(const QString &filePath)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::rebuildRecentFileListForCurrentFile";

  setWindowFilePath (filePath);

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  QStringList recentFilePaths = settings.value (SETTINGS_RECENT_FILE_LIST).toStringList();
  recentFilePaths.removeAll (filePath); // Remove previous instance of the current filePath
  recentFilePaths.prepend (filePath); // Insert current filePath at start
  while (recentFilePaths.count () > (int) MAX_RECENT_FILE_LIST_SIZE) {
    recentFilePaths.removeLast (); // Remove entry since the number of entries exceeds the limit
  }
  settings.setValue (SETTINGS_RECENT_FILE_LIST, recentFilePaths);

  updateRecentFileList();
}

void MainWindow::resizeEvent(QResizeEvent * /* event */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::resizeEvent";

  if (m_actionZoomFill->isChecked ()) {
    slotViewZoomFill();
  }
}

bool MainWindow::saveDocumentFile (const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::saveDocumentFile fileName=" << fileName.toLatin1 ().data ();

  QFile file(fileName);
  if (!file.open(QFile::WriteOnly)) {
    QMessageBox::warning (this,
                          engaugeWindowTitle(),
                          QString ("%1 %2: \n%3.")
                          .arg(tr ("Cannot write file"))
                          .arg(fileName)
                          .arg(file.errorString()));
    return false;
  }

  rebuildRecentFileListForCurrentFile (fileName);

  QApplication::setOverrideCursor (Qt::WaitCursor);
  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.writeStartDocument();
  writer.writeDTD("<!DOCTYPE engauge>");
  m_cmdMediator->document().saveXml(writer);
  writer.writeEndDocument();
  QApplication::restoreOverrideCursor ();

  // Notify the undo stack that the current state is now considered "clean". This will automatically trigger a
  // signal back to this class that will update the modified marker in the title bar
  m_cmdMediator->setClean ();

  setCurrentFile(fileName);
  m_engaugeFile = fileName;
  updateAfterCommand (); // Enable Save button now that m_engaugeFile is set
  m_statusBar->showTemporaryMessage("File saved");

  return true;
}

void MainWindow::saveErrorReportFileAndExit (const char *context,
                                             const char *file,
                                             int line,
                                             const char *comment) const
{
  // Skip if currently performing a regression test - in which case the preferred behavior is to let the current test fail and
  // continue on to execute the remaining tests
  if ((m_cmdMediator != 0) && !m_isErrorReportRegressionTest) {

    QString report = saveErrorReportFileAndExitXml (context,
                                                    file,
                                                    line,
                                                    comment);
#ifdef NETWORKING  
    DlgErrorReportNetworking dlg (report);

    // Ask user if report should be uploaded, and if the document is included when it is uploaded
    if (dlg.exec() == QDialog::Accepted) {

      // Upload the error report to the server
      m_networkClient->uploadErrorReport (dlg.xmlToUpload());
    }
#else
    DlgErrorReportLocal dlg (report);
    dlg.exec();
    exit (-1);
#endif
  }
}

QString MainWindow::saveErrorReportFileAndExitXml (const char *context,
                                                   const char *file,
                                                   int line,
                                                   const char *comment) const
{
  const bool DEEP_COPY = true;

  QString xmlErrorReport;
  QXmlStreamWriter writer (&xmlErrorReport);
  writer.setAutoFormatting(true);

  // Entire error report contains metadata, commands and other details
  writer.writeStartElement(DOCUMENT_SERIALIZE_ERROR_REPORT);

  // Version
  writer.writeStartElement(DOCUMENT_SERIALIZE_APPLICATION);
  writer.writeAttribute(DOCUMENT_SERIALIZE_APPLICATION_VERSION_NUMBER, VERSION_NUMBER);
  writer.writeEndElement();

  // Document
  // Insert snapshot xml into writer stream, by reading from reader stream. Highest level of snapshot is DOCUMENT_SERIALIZE_APPLICATION
  QXmlStreamReader reader (m_startingDocumentSnapshot);
  while (!reader.atEnd ()) {
    reader.readNext ();
    if (reader.tokenType() != QXmlStreamReader::StartDocument &&
        reader.tokenType() != QXmlStreamReader::EndDocument) {
      writer.writeCurrentToken (reader);
    }
  }

  // Operating system
  writer.writeStartElement(DOCUMENT_SERIALIZE_OPERATING_SYSTEM);
  writer.writeAttribute(DOCUMENT_SERIALIZE_OPERATING_SYSTEM_ENDIAN, EndianToString (QSysInfo::ByteOrder));
  writer.writeAttribute(DOCUMENT_SERIALIZE_OPERATING_SYSTEM_WORD_SIZE, QString::number (QSysInfo::WordSize));
  writer.writeEndElement();

  // Placeholder for original file, before the commands in the command stack were applied
  writer.writeStartElement(DOCUMENT_SERIALIZE_FILE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_FILE_IMPORTED,
                        m_originalFileWasImported ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeEndElement();

  // Commands
  m_cmdMediator->saveXml(writer);

  // Error
  writer.writeStartElement(DOCUMENT_SERIALIZE_ERROR);
  writer.writeAttribute(DOCUMENT_SERIALIZE_ERROR_CONTEXT, context);
  writer.writeAttribute(DOCUMENT_SERIALIZE_ERROR_FILE, file);
  writer.writeAttribute(DOCUMENT_SERIALIZE_ERROR_LINE, QString::number (line));
  writer.writeAttribute(DOCUMENT_SERIALIZE_ERROR_COMMENT, comment);
  writer.writeEndElement();

  writer.writeEndElement();

  // Put string into DOM
  QDomDocument domErrorReport ("ErrorReport");
  domErrorReport.setContent (xmlErrorReport);

  // Postprocessing
  if (!m_originalFileWasImported) {

    // Insert the original file into its placeholder, by manipulating the source and target xml as DOM documents. Very early
    // in the loading process, the original file may not be specified yet (m_originalFile is empty)
    QDomDocument domInputFile;
    loadInputFileForErrorReport (domInputFile);
    QDomDocumentFragment fragmentFileFrom = domErrorReport.createDocumentFragment();
    if (!domInputFile.isNull()) {
      fragmentFileFrom.appendChild (domErrorReport.importNode (domInputFile.documentElement(), DEEP_COPY));
    }
    QDomNodeList nodesFileTo = domErrorReport.elementsByTagName (DOCUMENT_SERIALIZE_FILE);
    if (nodesFileTo.count () > 0) {
      QDomNode nodeFileTo = nodesFileTo.at (0);
      nodeFileTo.appendChild (fragmentFileFrom);
    }

    // Replace DOCUMENT_SERIALIZE_IMAGE by same node with CDATA removed, since:
    // 1) it is very big and working with smaller files, especially in emails, is easier
    // 2) removing the image better preserves user's privacy
    // 3) having the actual image does not help that much when debugging
    QDomNodeList nodesDocument = domErrorReport.elementsByTagName (DOCUMENT_SERIALIZE_DOCUMENT);
    for (int i = 0 ; i < nodesDocument.count(); i++) {
      QDomNode nodeDocument = nodesDocument.at (i);
      QDomElement elemImage = nodeDocument.firstChildElement(DOCUMENT_SERIALIZE_IMAGE);
      if (!elemImage.isNull()) {

        // Get old image attributes so we can create an empty document with the same size
        if (elemImage.hasAttribute (DOCUMENT_SERIALIZE_IMAGE_WIDTH) &&
            elemImage.hasAttribute (DOCUMENT_SERIALIZE_IMAGE_HEIGHT)) {

          int width = elemImage.attribute(DOCUMENT_SERIALIZE_IMAGE_WIDTH).toInt();
          int height = elemImage.attribute(DOCUMENT_SERIALIZE_IMAGE_HEIGHT).toInt();

          QDomNode nodeReplacement;
          QDomElement elemReplacement = nodeReplacement.toElement();
          elemReplacement.setAttribute (DOCUMENT_SERIALIZE_IMAGE_WIDTH, width);
          elemReplacement.setAttribute (DOCUMENT_SERIALIZE_IMAGE_HEIGHT, height);

          // Replace with the new and then remove the old
          nodeDocument.insertBefore (nodeReplacement,
                                     elemImage);
          nodeDocument.removeChild(elemImage);
        }
      }
    }
  }

  return domErrorReport.toString();
}

void MainWindow::saveStartingDocumentSnapshot()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::saveStartingDocumentSnapshot";

  QXmlStreamWriter writer (&m_startingDocumentSnapshot);
  writer.setAutoFormatting (true);
  m_cmdMediator->document().saveXml (writer);
}

GraphicsScene &MainWindow::scene ()
{
  ENGAUGE_CHECK_PTR (m_scene);
  return *m_scene;
}

BackgroundImage MainWindow::selectOriginal(BackgroundImage backgroundImage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::selectBackgroundOriginal";

  BackgroundImage previousBackground = (BackgroundImage) m_cmbBackground->currentData().toInt();

  int index = m_cmbBackground->findData (backgroundImage);
  ENGAUGE_ASSERT (index >= 0);

  m_cmbBackground->setCurrentIndex(index);

  return previousBackground;
}

QString MainWindow::selectedGraphCurve () const
{
  return m_cmbCurve->currentText ();
}

void MainWindow::setCurrentFile (const QString &fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::setCurrentFile";

  QString fileNameStripped;
  if (!fileName.isEmpty()) {

    // Strip out path and file extension
    QFileInfo fileInfo (fileName);
    fileNameStripped = fileInfo.baseName();
  }

  m_currentFile = fileNameStripped;
  m_currentFileWithPathAndFileExtension = fileName;

  updateWindowTitle ();
}

void MainWindow::setCurrentPathFromFile (const QString &fileName)
{
  QDir dir = QFileInfo (fileName).absoluteDir();

  if (dir.exists ()) {

    bool success = QDir::setCurrent (dir.absolutePath ()); // Return to chosen directory the next time
    ENGAUGE_ASSERT (success);

  } else {

    // File was a url so it is irrelevant to the current directory
  }
}

void MainWindow::setPixmap (const QString &curveSelected,
                            const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::setPixmap";

  m_digitizeStateContext->setImageIsLoaded (m_cmdMediator,
                                            true);

  // We cannot reliably use m_cmbCurve->currentText below for the selected curve since that control
  // can be pointing to a curve that no longer exists so this method requires curveSelected as an argument
  m_backgroundStateContext->setPixmap (m_transformation,
                                       m_cmdMediator->document().modelGridRemoval(),
                                       m_cmdMediator->document().modelColorFilter(),
                                       pixmap,
                                       curveSelected);
}

void MainWindow::settingsRead (bool isReset)
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);

  if (isReset) {
    // Delete all settings. Default values are specified, later, for each settings as it is loaded
    settings.clear ();
  }

  settingsReadEnvironment (settings);
  settingsReadMainWindow (settings);
}

void MainWindow::settingsReadEnvironment (QSettings &settings)
{
  settings.beginGroup (SETTINGS_GROUP_ENVIRONMENT);
  QDir::setCurrent (settings.value (SETTINGS_CURRENT_DIRECTORY,
                                    QDir::currentPath ()).toString ());
  settings.endGroup ();
}

void MainWindow::settingsReadMainWindow (QSettings &settings)
{
  settings.beginGroup(SETTINGS_GROUP_MAIN_WINDOW);

  // Main window geometry
  resize (settings.value (SETTINGS_SIZE,
                          QSize (600, 600)).toSize ());
  move (settings.value (SETTINGS_POS,
                        QPoint (200, 200)).toPoint ());

  // Help window geometry
#ifndef OSX_RELEASE
  QSize helpSize = settings.value (SETTINGS_HELP_SIZE,
                                   QSize (900, 600)).toSize();
  m_helpWindow->resize (helpSize);
  if (settings.contains (SETTINGS_HELP_POS)) {
    QPoint helpPos = settings.value (SETTINGS_HELP_POS).toPoint();
    m_helpWindow->move (helpPos);
  }
#endif

  // Checklist guide wizard
  m_actionHelpChecklistGuideWizard->setChecked (settings.value (SETTINGS_CHECKLIST_GUIDE_WIZARD,
                                                            true).toBool ());

  // Background toolbar visibility
  bool viewBackgroundToolBar = settings.value (SETTINGS_VIEW_BACKGROUND_TOOLBAR,
                                               true).toBool ();
  m_actionViewBackground->setChecked (viewBackgroundToolBar);
  m_toolBackground->setVisible (viewBackgroundToolBar);
  BackgroundImage backgroundImage = (BackgroundImage) settings.value (SETTINGS_BACKGROUND_IMAGE,
                                                                      BACKGROUND_IMAGE_FILTERED).toInt ();
  int indexBackground = m_cmbBackground->findData (QVariant (backgroundImage));
  m_cmbBackground->setCurrentIndex (indexBackground);

  // Digitize toolbar visibility
  bool viewDigitizeToolBar = settings.value (SETTINGS_VIEW_DIGITIZE_TOOLBAR,
                                             true).toBool ();
  m_actionViewDigitize->setChecked (viewDigitizeToolBar);
  m_toolDigitize->setVisible (viewDigitizeToolBar);

  // Views toolbar visibility
  bool viewSettingsViewsToolBar = settings.value (SETTINGS_VIEW_SETTINGS_VIEWS_TOOLBAR,
                                                  true).toBool ();
  m_actionViewSettingsViews->setChecked (viewSettingsViewsToolBar);
  m_toolSettingsViews->setVisible (viewSettingsViewsToolBar);

  // Coordinate system toolbar visibility
  bool viewCoordSystemToolbar = settings.value (SETTINGS_VIEW_COORD_SYSTEM_TOOLBAR,
                                                false).toBool ();
  m_actionViewCoordSystem->setChecked (viewCoordSystemToolbar);
  m_toolCoordSystem->setVisible (viewCoordSystemToolbar);

  // Tooltips visibility
  bool viewToolTips = settings.value (SETTINGS_VIEW_TOOL_TIPS,
                                      true).toBool ();
  m_actionViewToolTips->setChecked (viewToolTips);
  loadToolTips ();

  // Statusbar visibility
  StatusBarMode statusBarMode = (StatusBarMode) settings.value (SETTINGS_VIEW_STATUS_BAR,
                                                                false).toInt ();
  m_statusBar->setStatusBarMode (statusBarMode);
  m_actionStatusNever->setChecked (statusBarMode == STATUS_BAR_MODE_NEVER);
  m_actionStatusTemporary->setChecked (statusBarMode == STATUS_BAR_MODE_TEMPORARY);
  m_actionStatusAlways->setChecked (statusBarMode == STATUS_BAR_MODE_ALWAYS);

  addDockWindow (m_dockChecklistGuide,
                 settings,
                 SETTINGS_CHECKLIST_GUIDE_DOCK_AREA,
                 SETTINGS_CHECKLIST_GUIDE_DOCK_GEOMETRY,
                 Qt::RightDockWidgetArea);
  addDockWindow (m_dockFittingWindow,
                 settings,
                 SETTINGS_FITTING_WINDOW_DOCK_AREA,
                 SETTINGS_FITTING_WINDOW_DOCK_GEOMETRY,
                 Qt::RightDockWidgetArea);
  addDockWindow (m_dockGeometryWindow,
                 settings,
                 SETTINGS_GEOMETRY_WINDOW_DOCK_AREA,
                 SETTINGS_GEOMETRY_WINDOW_DOCK_GEOMETRY,
                 Qt::RightDockWidgetArea);

  // Main window settings. Preference for initial zoom factor is 100%, rather than fill mode, for issue #25. Some or all
  // settings are saved to the application AND saved to m_modelMainWindow for use in DlgSettingsMainWindow. Note that
  // TranslatorContainer has previously extracted the locale from the settings
  QLocale localeDefault;
  QLocale::Language language = (QLocale::Language) settings.value (SETTINGS_LOCALE_LANGUAGE,
                                                                   QVariant (localeDefault.language())).toInt();
  QLocale::Country country = (QLocale::Country) settings.value (SETTINGS_LOCALE_COUNTRY,
                                                                QVariant (localeDefault.country())).toInt();
  QLocale locale (language,
                  country);
  slotViewZoom ((ZoomFactor) settings.value (SETTINGS_ZOOM_FACTOR,
                                             QVariant (ZOOM_1_TO_1)).toInt());
  m_modelMainWindow.setLocale (locale);
  m_modelMainWindow.setZoomFactorInitial((ZoomFactorInitial) settings.value (SETTINGS_ZOOM_FACTOR_INITIAL,
                                                                             QVariant (DEFAULT_ZOOM_FACTOR_INITIAL)).toInt());
  m_modelMainWindow.setZoomControl ((ZoomControl) settings.value (SETTINGS_ZOOM_CONTROL,
                                                                  QVariant (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS)).toInt());
  m_modelMainWindow.setMainTitleBarFormat ((MainTitleBarFormat) settings.value (SETTINGS_MAIN_TITLE_BAR_FORMAT,
                                                                                QVariant (MAIN_TITLE_BAR_FORMAT_PATH)).toInt());
  m_modelMainWindow.setPdfResolution (settings.value (SETTINGS_IMPORT_PDF_RESOLUTION,
                                                      QVariant (DEFAULT_IMPORT_PDF_RESOLUTION)).toInt ());
  m_modelMainWindow.setImportCropping ((ImportCropping) settings.value (SETTINGS_IMPORT_CROPPING,
                                                                        QVariant (DEFAULT_IMPORT_CROPPING)).toInt ());
  m_modelMainWindow.setMaximumGridLines (settings.value (SETTINGS_MAXIMUM_GRID_LINES,
                                                         QVariant (DEFAULT_MAXIMUM_GRID_LINES)).toInt ());
  m_modelMainWindow.setHighlightOpacity (settings.value (SETTINGS_HIGHLIGHT_OPACITY,
                                                         QVariant (DEFAULT_HIGHLIGHT_OPACITY)).toDouble ());
  m_modelMainWindow.setSmallDialogs (settings.value (SETTINGS_SMALL_DIALOGS,
                                                     QVariant (DEFAULT_SMALL_DIALOGS)).toBool ());
  m_modelMainWindow.setDragDropExport (settings.value (SETTINGS_DRAG_DROP_EXPORT,
                                                       QVariant (DEFAULT_DRAG_DROP_EXPORT)).toBool ());

  updateSettingsMainWindow();
  updateSmallDialogs();

  settings.endGroup();
}

void MainWindow::settingsWrite ()
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);

  settings.beginGroup (SETTINGS_GROUP_ENVIRONMENT);
  settings.setValue (SETTINGS_CURRENT_DIRECTORY, QDir::currentPath ());
  settings.endGroup ();

  settings.beginGroup (SETTINGS_GROUP_MAIN_WINDOW);
  settings.setValue (SETTINGS_SIZE, size ());
  settings.setValue (SETTINGS_POS, pos ());
#ifndef OSX_RELEASE
  settings.setValue (SETTINGS_HELP_SIZE, m_helpWindow->size());
  settings.setValue (SETTINGS_HELP_POS, m_helpWindow->pos ());
#endif
  if (m_dockChecklistGuide->isFloating()) {

    settings.setValue (SETTINGS_CHECKLIST_GUIDE_DOCK_AREA, Qt::NoDockWidgetArea);
    settings.setValue (SETTINGS_CHECKLIST_GUIDE_DOCK_GEOMETRY, m_dockChecklistGuide->saveGeometry ());

  } else {

    settings.setValue (SETTINGS_CHECKLIST_GUIDE_DOCK_AREA, dockWidgetArea (m_dockChecklistGuide));

  }
  if (m_dockFittingWindow->isFloating()) {

    settings.setValue (SETTINGS_FITTING_WINDOW_DOCK_AREA, Qt::NoDockWidgetArea);
    settings.setValue (SETTINGS_FITTING_WINDOW_DOCK_GEOMETRY, m_dockFittingWindow->saveGeometry());
  } else {

    settings.setValue (SETTINGS_FITTING_WINDOW_DOCK_AREA, dockWidgetArea (m_dockFittingWindow));
  }
  if (m_dockGeometryWindow->isFloating()) {

    settings.setValue (SETTINGS_GEOMETRY_WINDOW_DOCK_AREA, Qt::NoDockWidgetArea);
    settings.setValue (SETTINGS_GEOMETRY_WINDOW_DOCK_GEOMETRY, m_dockGeometryWindow->saveGeometry ());

  } else {

    settings.setValue (SETTINGS_GEOMETRY_WINDOW_DOCK_AREA, dockWidgetArea (m_dockGeometryWindow));

  }
  settings.setValue (SETTINGS_BACKGROUND_IMAGE, m_cmbBackground->currentData().toInt());
  settings.setValue (SETTINGS_CHECKLIST_GUIDE_WIZARD, m_actionHelpChecklistGuideWizard->isChecked ());
  settings.setValue (SETTINGS_DRAG_DROP_EXPORT, m_modelMainWindow.dragDropExport ());
  settings.setValue (SETTINGS_HIGHLIGHT_OPACITY, m_modelMainWindow.highlightOpacity());
  settings.setValue (SETTINGS_IMPORT_CROPPING, m_modelMainWindow.importCropping());
  settings.setValue (SETTINGS_IMPORT_PDF_RESOLUTION, m_modelMainWindow.pdfResolution ());
  settings.setValue (SETTINGS_LOCALE_LANGUAGE, m_modelMainWindow.locale().language());
  settings.setValue (SETTINGS_LOCALE_COUNTRY, m_modelMainWindow.locale().country());
  settings.setValue (SETTINGS_MAIN_TITLE_BAR_FORMAT, m_modelMainWindow.mainTitleBarFormat());
  settings.setValue (SETTINGS_MAXIMUM_GRID_LINES, m_modelMainWindow.maximumGridLines());
  settings.setValue (SETTINGS_SMALL_DIALOGS, m_modelMainWindow.smallDialogs());
  settings.setValue (SETTINGS_VIEW_BACKGROUND_TOOLBAR, m_actionViewBackground->isChecked());
  settings.setValue (SETTINGS_VIEW_DIGITIZE_TOOLBAR, m_actionViewDigitize->isChecked ());
  settings.setValue (SETTINGS_VIEW_STATUS_BAR, m_statusBar->statusBarMode ());
  settings.setValue (SETTINGS_VIEW_SETTINGS_VIEWS_TOOLBAR, m_actionViewSettingsViews->isChecked ());
  settings.setValue (SETTINGS_VIEW_COORD_SYSTEM_TOOLBAR, m_actionViewCoordSystem->isChecked ());
  settings.setValue (SETTINGS_VIEW_TOOL_TIPS, m_actionViewToolTips->isChecked ());
  settings.setValue (SETTINGS_ZOOM_CONTROL, m_modelMainWindow.zoomControl());
  settings.setValue (SETTINGS_ZOOM_FACTOR, currentZoomFactor ());
  settings.setValue (SETTINGS_ZOOM_FACTOR_INITIAL, m_modelMainWindow.zoomFactorInitial());
  settings.endGroup ();
}

bool MainWindow::setupAfterLoadNewDocument (const QString &fileName,
                                            const QString &temporaryMessage ,
                                            ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::setupAfterLoadNewDocument"
                              << " file=" << fileName.toLatin1().data()
                              << " message=" << temporaryMessage.toLatin1().data()
                              << " importType=" << importType;

  // The steps in this method should theoretically be a superset of the steps in setupAfterLoadNewDocument. Therefore, any
  // changes to this method should be considered for application to the other method also

  const QString EMPTY_CURVE_NAME_TO_SKIP_BACKGROUND_PROCESSING; // For bootstrapping the preview

  // At this point the code assumes CmdMediator for the NEW Document is already stored in m_cmdMediator

  m_digitizeStateContext->resetOnLoad (m_cmdMediator); // Before setPixmap
  m_backgroundStateContext->setCurveSelected (m_transformation,
                                              m_cmdMediator->document().modelGridRemoval(),
                                              m_cmdMediator->document().modelColorFilter(),
                                              EMPTY_CURVE_NAME_TO_SKIP_BACKGROUND_PROCESSING); // Before setPixmap
  setPixmap (m_cmdMediator->document().curvesGraphsNames().first(),
             m_cmdMediator->pixmap ()); // Set background immediately so it is visible as a preview when any dialogs are displayed

  // Image is visible now so the user can refer to it when we ask for the number of coordinate systems. Note that the Document
  // may already have multiple CoordSystem if user loaded a file that had multiple CoordSystem entries
  if (importType == IMPORT_TYPE_ADVANCED) {

    applyZoomFactorAfterLoad(); // Apply the currently selected zoom factor

    DlgImportAdvanced dlgImportAdvanced (*this);
    dlgImportAdvanced.exec();

    if (dlgImportAdvanced.result() == QDialog::Rejected) {
      return false;
    }

    int numberCoordSystem = dlgImportAdvanced.numberCoordSystem();
    m_cmdMediator->document().addCoordSystems (numberCoordSystem - 1);
    m_cmdMediator->setDocumentAxesPointsRequired (dlgImportAdvanced.documentAxesPointsRequired());
  }

  m_transformation.resetOnLoad();
  m_transformationStateContext->resetOnLoad();
  m_scene->resetOnLoad();

  connect (m_actionEditUndo, SIGNAL (triggered ()), m_cmdMediator, SLOT (undo ()));
  connect (m_actionEditUndo, SIGNAL (triggered ()), m_cmdStackShadow, SLOT (slotUndo ()));
  connect (m_actionEditRedo, SIGNAL (triggered ()), m_cmdMediator, SLOT (redo ())); // No effect until CmdMediator::undo and CmdStackShadow::slotUndo get called
  connect (m_actionEditRedo, SIGNAL (triggered ()), m_cmdStackShadow, SLOT (slotRedo ())); // No effect after CmdMediator::undo and CmdStackShadow::slotUndo get called
  connect (m_cmdMediator, SIGNAL (canRedoChanged(bool)), this, SLOT (slotCanRedoChanged (bool)));
  connect (m_cmdMediator, SIGNAL (canUndoChanged(bool)), this, SLOT (slotCanUndoChanged (bool)));
  connect (m_cmdMediator, SIGNAL (redoTextChanged (const QString &)), this, SLOT (slotRedoTextChanged (const QString &)));
  connect (m_cmdMediator, SIGNAL (undoTextChanged (const QString &)), this, SLOT (slotUndoTextChanged (const QString &)));
  loadCurveListFromCmdMediator ();
  loadCoordSystemListFromCmdMediator ();
  updateViewsOfSettings ();

  m_isDocumentExported = false;

  // Background must be set (by setPixmap) before slotViewZoomFill which relies on the background. At this point
  // the transformation is undefined (unless the code is changed) so grid removal will not work
  // but updateTransformationAndItsDependencies will call this again to fix that issue. Note that the selected
  // curve name was set (by setCurveSelected) earlier before the call to setPixmap
  m_backgroundStateContext->setCurveSelected (m_transformation,
                                              m_cmdMediator->document().modelGridRemoval(),
                                              m_cmdMediator->document().modelColorFilter(),
                                              m_cmbCurve->currentText ());
  m_backgroundStateContext->setBackgroundImage ((BackgroundImage) m_cmbBackground->currentIndex ());

  applyZoomFactorAfterLoad(); // Zoom factor must be reapplied after background image is set, to have any effect

  setCurrentFile(fileName);
  m_statusBar->showTemporaryMessage (temporaryMessage);
  m_statusBar->wakeUp ();

  saveStartingDocumentSnapshot();

  updateAfterCommand(); // Replace stale points by points in new Document

  return true;
}

bool MainWindow::setupAfterLoadReplacingImage (const QString &fileName,
                                               const QString &temporaryMessage ,
                                               ImportType importType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::setupAfterLoadReplacingImage"
                              << " file=" << fileName.toLatin1().data()
                              << " message=" << temporaryMessage.toLatin1().data()
                              << " importType=" << importType;

  // The steps in this method should theoretically be just a subset of the steps in setupAfterLoadNewDocument

  // After this point there should be no commands in CmdMediator, since we effectively have a new document
  m_cmdMediator->clear();

  setPixmap (m_cmdMediator->document().curvesGraphsNames().first(),
             m_cmdMediator->pixmap ()); // Set background immediately so it is visible as a preview when any dialogs are displayed

  m_isDocumentExported = false;

  m_backgroundStateContext->setBackgroundImage ((BackgroundImage) m_cmbBackground->currentIndex ());

  applyZoomFactorAfterLoad(); // Zoom factor must be reapplied after background image is set, to have any effect

  setCurrentFile(fileName);
  m_statusBar->showTemporaryMessage (temporaryMessage);
  m_statusBar->wakeUp ();

  saveStartingDocumentSnapshot();

  updateAfterCommand(); // Replace stale points by points in new Document

  return true;
}

void MainWindow::showEvent (QShowEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::showEvent"
                              << " files=" << m_loadStartupFiles.join (",").toLatin1().data();

  QMainWindow::showEvent (event);

  if (m_loadStartupFiles.count() > 0) {

    m_timerLoadStartupFiles = new QTimer;
    m_timerLoadStartupFiles->setSingleShot (true);
    connect (m_timerLoadStartupFiles, SIGNAL (timeout ()), this, SLOT (slotLoadStartupFiles ()));
    m_timerLoadStartupFiles->start (0); // Zero delay still waits until execution finishes and gui is available

  }
}

void MainWindow::showTemporaryMessage (const QString &temporaryMessage)
{
  m_statusBar->showTemporaryMessage (temporaryMessage);
}

void MainWindow::slotBtnPrintAll ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotBtnPrintAll";

  ghostsCreate ();

  QPrinter printer (QPrinter::HighResolution);
  QPrintDialog dlg (&printer, this);
  if (dlg.exec() == QDialog::Accepted) {
    QPainter painter (&printer);
    m_view->render (&painter);
    painter.end();
  }

  ghostsDestroy ();
}

void MainWindow::slotBtnShowAllPressed ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotBtnShowAllPressed";

  // Start of press-release sequence
  ghostsCreate ();
}

void MainWindow::slotBtnShowAllReleased ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotBtnShowAllReleased";

  // End of press-release sequence
  ghostsDestroy ();
}

void MainWindow::slotCanRedoChanged (bool canRedo)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotCanRedoChanged";

  m_actionEditRedo->setEnabled (canRedo || m_cmdStackShadow->canRedo());
}

void MainWindow::slotCanUndoChanged (bool canUndo)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotCanUndoChanged";

  m_actionEditUndo->setEnabled (canUndo);
}

void MainWindow::slotChecklistClosed()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotChecklistClosed";

  m_actionViewChecklistGuide->setChecked (false);
}

void MainWindow::slotCleanChanged(bool clean)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotCleanChanged";

  setWindowModified (!clean);
}

void MainWindow::slotCmbBackground(int currentIndex)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotCmbBackground";

  switch (currentIndex) {
    case BACKGROUND_IMAGE_NONE:
      if (!m_actionViewBackgroundNone->isChecked()) {
        m_actionViewBackgroundNone->toggle();
      }
      break;

    case BACKGROUND_IMAGE_ORIGINAL:
      if (!m_actionViewBackgroundOriginal->isChecked ()) {
          m_actionViewBackgroundOriginal->toggle();
      }
      break;

    case BACKGROUND_IMAGE_FILTERED:
      if (!m_actionViewBackgroundFiltered->isChecked ()) {
        m_actionViewBackgroundFiltered->toggle();
      }
      break;
  }

  m_backgroundStateContext->setBackgroundImage ((BackgroundImage) currentIndex);
}

void MainWindow::slotCmbCoordSystem(int index)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotCmbCoordSystem";

  CmdSelectCoordSystem *cmd = new CmdSelectCoordSystem (*this,
                                                        m_cmdMediator->document(),
                                                        index);

  m_cmdMediator->push (cmd);
}

void MainWindow::slotCmbCurve(int /* index */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotCmbCurve";

  m_backgroundStateContext->setCurveSelected (m_transformation,
                                              m_cmdMediator->document().modelGridRemoval(),
                                              m_cmdMediator->document().modelColorFilter(),
                                              m_cmbCurve->currentText ());
  m_digitizeStateContext->handleCurveChange (m_cmdMediator);
  m_cmdMediator->setSelectedCurveName (m_cmbCurve->currentText ()); // Save for next time current coordinate system returns

  updateViewedCurves();
  updateViewsOfSettings();
  updateFittingWindow();
  updateGeometryWindow();
}

void MainWindow::slotContextMenuEventAxis (QString pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotContextMenuEventAxis point=" << pointIdentifier.toLatin1 ().data ();

  m_digitizeStateContext->handleContextMenuEventAxis (m_cmdMediator,
                                                      pointIdentifier);
}

void MainWindow::slotContextMenuEventGraph (QStringList pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotContextMenuEventGraph point=" << pointIdentifiers.join(",").toLatin1 ().data ();

  m_digitizeStateContext->handleContextMenuEventGraph (m_cmdMediator,
                                                       pointIdentifiers);
}

void MainWindow::slotDigitizeAxis ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeAxis";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_AXIS);
  m_cmbCurve->setEnabled (false); // Graph curve is irrelevant in this mode
  m_viewPointStyle->setEnabled (true); // Point style is important in this mode
  m_viewSegmentFilter->setEnabled (true); // Filtering is important in this mode
}

void MainWindow::slotDigitizeColorPicker ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeColorPicker";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_COLOR_PICKER);
  m_cmbCurve->setEnabled (true);
  m_viewPointStyle->setEnabled (true);
  m_viewSegmentFilter->setEnabled (true);
}

void MainWindow::slotDigitizeCurve ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeCurve";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_CURVE);
  m_cmbCurve->setEnabled (true);
  m_viewPointStyle->setEnabled (true);
  m_viewSegmentFilter->setEnabled (true);
}

void MainWindow::slotDigitizePointMatch ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizePointMatch";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_POINT_MATCH);
  m_cmbCurve->setEnabled (true);
  m_viewPointStyle->setEnabled (true);
  m_viewSegmentFilter->setEnabled (true);
}

void MainWindow::slotDigitizeScale ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeScale";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_SCALE);
  m_cmbCurve->setEnabled (false);
  m_viewPointStyle->setEnabled (false);
  m_viewSegmentFilter->setEnabled (false);
}

void MainWindow::slotDigitizeSegment ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeSegment";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_SEGMENT);
  m_cmbCurve->setEnabled (true);
  m_viewPointStyle->setEnabled (true);
  m_viewSegmentFilter->setEnabled (true);
}

void MainWindow::slotDigitizeSelect ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotDigitizeSelect";

  m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                           DIGITIZE_STATE_SELECT);
  m_cmbCurve->setEnabled (false);
  m_viewPointStyle->setEnabled (false);
  m_viewSegmentFilter->setEnabled (false);
}

void MainWindow::slotEditCopy ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditCopy";

  // Copy command is sent to FittingWindow or GeometryWindow, or processed locally
  bool tableFittingIsActive, tableFittingIsCopyable;
  bool tableGeometryIsActive, tableGeometryIsCopyable;
  m_dockFittingWindow->getTableStatus (tableFittingIsActive, tableFittingIsCopyable); // Fitting window status
  m_dockGeometryWindow->getTableStatus (tableGeometryIsActive, tableGeometryIsCopyable); // Geometry window status

  if (tableFittingIsActive) {

    // Send to FittingWindow
    m_dockFittingWindow->doCopy ();

  } else if (tableGeometryIsActive) {

    // Send to GeometryWindow
    m_dockGeometryWindow->doCopy ();

  } else {

    // Process curve points in main window
    GraphicsItemsExtractor graphicsItemsExtractor;
    const QList<QGraphicsItem*> &items = m_scene->selectedItems();
    QStringList pointIdentifiers = graphicsItemsExtractor.selectedPointIdentifiers (items);

    CmdCopy *cmd = new CmdCopy (*this,
                                m_cmdMediator->document(),
                                pointIdentifiers);
    m_digitizeStateContext->appendNewCmd (m_cmdMediator,
                                          cmd);
  }
}

void MainWindow::slotEditCut ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditCut";

  // Copy command is sent to FittingWindow or GeometryWindow, or processed locally
  bool tableFittingIsActive, tableFittingIsCopyable;
  bool tableGeometryIsActive, tableGeometryIsCopyable;
  m_dockFittingWindow->getTableStatus (tableFittingIsActive, tableFittingIsCopyable); // Fitting window status
  m_dockGeometryWindow->getTableStatus (tableGeometryIsActive, tableGeometryIsCopyable); // Geometry window status

  if (tableFittingIsActive || tableGeometryIsActive) {

    // Cannot delete from fitting or geometry windows

  } else {

    // Process curve points in main window
    GraphicsItemsExtractor graphicsItemsExtractor;
    const QList<QGraphicsItem*> &items = m_scene->selectedItems();
    QStringList pointIdentifiers = graphicsItemsExtractor.selectedPointIdentifiers (items);

    CmdCut *cmd = new CmdCut (*this,
                              m_cmdMediator->document(),
                              pointIdentifiers);
    m_digitizeStateContext->appendNewCmd (m_cmdMediator,
                                          cmd);
  }
}

void MainWindow::slotEditDelete ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditDelete";

  // Copy command is sent to FittingWindow or GeometryWindow, or processed locally
  bool tableFittingIsActive, tableFittingIsCopyable;
  bool tableGeometryIsActive, tableGeometryIsCopyable;
  m_dockFittingWindow->getTableStatus (tableFittingIsActive, tableFittingIsCopyable); // Fitting window status
  m_dockGeometryWindow->getTableStatus (tableGeometryIsActive, tableGeometryIsCopyable); // Geometry window status

  if (tableFittingIsActive || tableGeometryIsActive) {

    // Cannot delete from fitting or geometry windows

  } else {

    // If this is a map, which has a scale bar with two axis points, then selection of just one axis point
    // for deletion should result in deletion of the other point also so this object will enforce that. Otherwise
    // this class has no effect below
    ScaleBarAxisPointsUnite scaleBarAxisPoints;

    // Process curve points in main window
    GraphicsItemsExtractor graphicsItemsExtractor;
    const QList<QGraphicsItem*> &items = m_scene->selectedItems();
    QStringList pointIdentifiers = scaleBarAxisPoints.unite (m_cmdMediator,
                                                             graphicsItemsExtractor.selectedPointIdentifiers (items));

    CmdDelete *cmd = new CmdDelete (*this,
                                    m_cmdMediator->document(),
                                    pointIdentifiers);
    m_digitizeStateContext->appendNewCmd (m_cmdMediator,
                                          cmd);
  }
}

void MainWindow::slotEditMenu ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditMenu";

  m_actionEditPasteAsNew->setEnabled (!QApplication::clipboard()->image().isNull());
  m_actionEditPasteAsNewAdvanced->setEnabled (!QApplication::clipboard()->image().isNull());
}

void MainWindow::slotEditPaste ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditPaste";
}

void MainWindow::slotEditPasteAsNew ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditPasteAsNew";

  filePaste (IMPORT_TYPE_SIMPLE);
}

void MainWindow::slotEditPasteAsNewAdvanced ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotEditPasteAsNewAdvanced";

  filePaste (IMPORT_TYPE_ADVANCED);
}

void MainWindow::slotFileClose()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileClose";

  if (maybeSave ()) {

    // Transition from defined to undefined. This must be after the clearing of the screen
    // since the axes checker screen item (and maybe others) must still exist
    m_transformationStateContext->triggerStateTransition(TRANSFORMATION_STATE_UNDEFINED,
                                                         *m_cmdMediator,
                                                         m_transformation,
                                                         selectedGraphCurve());

    // Transition to empty state so an inadvertent mouse press does not trigger, for example,
    // the creation of an axis point on a non-existent GraphicsScene (=crash)
    m_digitizeStateContext->requestImmediateStateTransition (m_cmdMediator,
                                                             DIGITIZE_STATE_EMPTY);

    // Deallocate fitted curve
    if (m_fittingCurve != 0) {
      m_scene->removeItem (m_fittingCurve);
      m_fittingCurve = 0;
    }

    // Remove screen objects
    m_scene->resetOnLoad ();

    // Remove background
    m_backgroundStateContext->close ();

    // Remove scroll bars if they exist
    m_scene->setSceneRect (QRectF (0, 0, 1, 1));

    // Remove stale data from fitting window
    m_dockFittingWindow->clear ();

    // Remove stale data from geometry window
    m_dockGeometryWindow->clear ();

    // Deallocate Document
    delete m_cmdMediator;

    // Remove file information
    m_cmdMediator = 0;
    m_currentFile = "";
    m_engaugeFile = "";
    setWindowTitle (engaugeWindowTitle ());

    m_gridLines.clear();
    updateControls();
  }
}

void MainWindow::slotFileExport ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileExport";

  if (m_transformation.transformIsDefined()) {

    ExportToFile exportStrategy;
    QString filter = QString ("%1;;%2;;All files (*.*)")
                     .arg (exportStrategy.filterCsv ())
                     .arg (exportStrategy.filterTsv ());

    // OSX sandbox requires, for the default, a non-empty filename
    QString defaultFileName = QString ("%1/%2.%3")
                              .arg (QDir::currentPath ())
                              .arg (m_currentFile)
                              .arg (exportStrategy.fileExtensionCsv ());
    QFileDialog dlg;
    QString filterCsv = exportStrategy.filterCsv ();
    QString fileName = dlg.getSaveFileName (this,
                                            tr("Export"),
                                            defaultFileName,
                                            filter,
                                            &filterCsv);
    if (!fileName.isEmpty ()) {

      fileExport(fileName,
                 exportStrategy);
    }
  } else {
    DlgRequiresTransform dlg ("Export");
    dlg.exec ();
  }
}

void MainWindow::slotFileImport ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImport";

  fileImportWithPrompts (IMPORT_TYPE_SIMPLE);
}

void MainWindow::slotFileImportAdvanced ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportAdvanced";

  fileImportWithPrompts (IMPORT_TYPE_ADVANCED);
}

void MainWindow::slotFileImportDraggedImage(QImage image)
{  
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportDraggedImage";

  // No need to check return value from loadImage since there are no prompts that give the user a chance to cancel
  loadImage ("",
             image,
             IMPORT_TYPE_SIMPLE);
}

void MainWindow::slotFileImportDraggedImageUrl(QUrl url)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportDraggedImageUrl url=" << url.toString ().toLatin1 ().data ();

#ifdef NETWORKING
  m_loadImageFromUrl->startLoadImage (url);
#endif
}

void MainWindow::slotFileImportImage(QString fileName, QImage image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportImage fileName=" << fileName.toLatin1 ().data ();

  // No need to check return value from loadImage since there are no prompts that give the user a chance to cancel
  loadImage (fileName,
             image,
             IMPORT_TYPE_SIMPLE);
}

void MainWindow::slotFileImportImageReplace ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileImportImageReplace";

  fileImportWithPrompts (IMPORT_TYPE_IMAGE_REPLACE);
}

void MainWindow::slotFileOpen()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileOpen";

  if (maybeSave ()) {

    // Allow selection of files with strange suffixes in case the file extension was changed. Since
    // the default is the first filter, the wildcard filter is added afterwards (it is the off-nominal case)
    QString filter = QString ("%1 (*.%2);; All Files (*.*)")
                     .arg (ENGAUGE_FILENAME_DESCRIPTION)
                     .arg (ENGAUGE_FILENAME_EXTENSION);

    QString fileName = QFileDialog::getOpenFileName (this,
                                                     tr("Open Document"),
                                                     QDir::currentPath (),
                                                     filter);
    if (!fileName.isEmpty ()) {

      loadDocumentFile (fileName);

    }
  }
}

void MainWindow::slotFileOpenDraggedDigFile (QString fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileOpenDraggedDigFile";

  loadDocumentFile (fileName);
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

  if (m_engaugeFile.isEmpty()) {
    return slotFileSaveAs();
  } else {
    return saveDocumentFile (m_engaugeFile);
  }
}

bool MainWindow::slotFileSaveAs()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFileSaveAs";

  // Append engauge file extension if it is not already there
  QString filenameDefault = m_currentFile;
  if (!m_currentFile.endsWith (ENGAUGE_FILENAME_EXTENSION)) {
    filenameDefault = QString ("%1.%2")
                               .arg (m_currentFile)
                               .arg (ENGAUGE_FILENAME_EXTENSION);
  }

  if (!m_engaugeFile.isEmpty()) {
    filenameDefault = m_engaugeFile;
  }

  QString filterDigitizer = QString ("%1 (*.%2)")
                            .arg (ENGAUGE_FILENAME_DESCRIPTION)
                            .arg (ENGAUGE_FILENAME_EXTENSION);
  QString filterAll ("All files (*. *)");

  QStringList filters;
  filters << filterDigitizer;
  filters << filterAll;

  QFileDialog dlg(this);
  dlg.setFileMode (QFileDialog::AnyFile);
  dlg.selectNameFilter (filterDigitizer);
  dlg.setNameFilters (filters);
#if defined(OSX_DEBUG) || defined(OSX_RELEASE)
#else
  // Prevent hang in OSX
  dlg.setWindowModality(Qt::WindowModal);
#endif
  dlg.setAcceptMode(QFileDialog::AcceptSave);
  dlg.selectFile(filenameDefault);
  if (dlg.exec()) {

    QStringList files = dlg.selectedFiles();
    return saveDocumentFile(files.at(0));
  }

  return false;
}

void MainWindow::slotFittingWindowClosed()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFittingWindowClosed";

  m_actionViewFittingWindow->setChecked (false);
}

void MainWindow::slotFittingWindowCurveFit(FittingCurveCoefficients fittingCurveCoef,
                                           double xMin,
                                           double xMax,
                                           bool isLogXTheta,
                                           bool isLogYRadius)
{
  // Do not output elements in fittingCurveCoef here since that list may be empty
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotFittingWindowCurveFit"
                              << " order=" << fittingCurveCoef.size() - 1;

  if (m_fittingCurve != 0) {
    m_scene->removeItem (m_fittingCurve);
    delete m_fittingCurve;
    m_fittingCurve = 0;
  }

  m_fittingCurve = new FittingCurve (fittingCurveCoef,
                                     xMin,
                                     xMax,
                                     isLogXTheta,
                                     isLogYRadius,
                                     m_transformation);
  m_fittingCurve->setVisible (m_actionViewFittingWindow->isChecked ());
  m_scene->addItem (m_fittingCurve);
}

void MainWindow::slotGeometryWindowClosed()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotGeometryWindowClosed";

  m_actionViewGeometryWindow->setChecked (false);
}

void MainWindow::slotHelpAbout()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotHelpAbout";

  DlgAbout dlg (*this);
  dlg.exec ();
}

void MainWindow::slotHelpTutorial()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotHelpTutorial";

  m_tutorialDlg->show ();
  m_tutorialDlg->exec ();
}

void MainWindow::slotKeyPress (Qt::Key key,
                               bool atLeastOneSelectedItem)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotKeyPress"
                              << " key=" << QKeySequence (key).toString().toLatin1 ().data ()
                              << " atLeastOneSelectedItem=" << (atLeastOneSelectedItem ? "true" : "false");

  m_digitizeStateContext->handleKeyPress (m_cmdMediator,
                                          key,
                                          atLeastOneSelectedItem);
}

void MainWindow::slotLoadStartupFiles ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotLoadStartupFiles";

  ENGAUGE_ASSERT (m_loadStartupFiles.count() > 0);

  QString fileName = m_loadStartupFiles.front(); // Get next file name
  m_loadStartupFiles.pop_front(); // Remove next file name

  // Load next file into this instance of Engauge
  LoadFileInfo loadFileInfo;
  if (loadFileInfo.loadsAsDigFile(fileName)) {

    loadDocumentFile (fileName);

  } else {

    fileImport (fileName,
                IMPORT_TYPE_SIMPLE);

  }

  if (m_loadStartupFiles.count() > 0) {

    // Fork off another instance of this application to handle the remaining files recursively. New process
    // is detached so killing/terminating this process does not automatically kill the child process(es) also
    QProcess::startDetached (QCoreApplication::applicationFilePath(),
                             m_loadStartupFiles);
  }
}

void MainWindow::slotMouseMove (QPointF pos)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotMouseMove pos=" << QPointFToString (pos).toLatin1 ().data ();

  // Ignore mouse moves before Document is loaded
  if (m_cmdMediator != 0) {

    QString needMoreText = (modeMap () ?
                              QObject::tr ("Need scale bar") :
                              QObject::tr ("Need more axis points"));

    // Get status bar coordinates
    QString coordsScreen, coordsGraph, resolutionGraph;
    m_transformation.coordTextForStatusBar (pos,
                                            coordsScreen,
                                            coordsGraph,
                                            resolutionGraph,
                                            needMoreText);

    // Update status bar coordinates
    m_statusBar->setCoordinates (coordsScreen,
                                 coordsGraph,
                                 resolutionGraph);

    // There used to be a call to updateGraphicsLinesToMatchGraphicsPoints here, but that resulted
    // in hundreds of gratuitous log messages as the cursor was moved around, and nothing important happened

    m_digitizeStateContext->handleMouseMove (m_cmdMediator,
                                             pos);
  }
}

void MainWindow::slotMousePress (QPointF pos)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotMousePress";

  m_scene->resetPositionHasChangedFlags();

  m_digitizeStateContext->handleMousePress (m_cmdMediator,
                                            pos);
}

void MainWindow::slotMouseRelease (QPointF pos)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotMouseRelease";

  if (pos.x() < 0 || pos.y() < 0) {

    // Cursor is outside the image so drop this event. However, call updateControls since this may be
    // a click-and-drag to select in which case the controls (especially Copy and Cut) reflect the new selection
    updateControls ();

  } else {

    // Cursor is within the image so process this as a normal mouse release
    m_digitizeStateContext->handleMouseRelease (m_cmdMediator,
                                                pos);
  }
}

void MainWindow::slotRecentFileAction ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotRecentFileAction";

  QAction *action = qobject_cast<QAction*>(sender ());

  if (action) {
    QString fileName = action->data().toString();
    loadDocumentFile (fileName);
  }
}

void MainWindow::slotRecentFileClear ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotRecentFileClear";

  QStringList emptyList;

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.setValue (SETTINGS_RECENT_FILE_LIST,
                     emptyList);

  updateRecentFileList();
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

void MainWindow::slotSettingsAxesChecker ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsAxesChecker";

  m_dlgSettingsAxesChecker->load (*m_cmdMediator);
  m_dlgSettingsAxesChecker->show ();
}

void MainWindow::slotSettingsColorFilter ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsColorFilter";

  m_dlgSettingsColorFilter->load (*m_cmdMediator);
  m_dlgSettingsColorFilter->show ();
}

void MainWindow::slotSettingsCoords ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCoords";

  m_dlgSettingsCoords->load (*m_cmdMediator);
  m_dlgSettingsCoords->show ();
}

void MainWindow::slotSettingsCurveAddRemove ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCurveAddRemove";

  m_dlgSettingsCurveAddRemove->load (*m_cmdMediator);
  m_dlgSettingsCurveAddRemove->show ();
}

void MainWindow::slotSettingsCurveProperties ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsCurveProperties";

  m_dlgSettingsCurveProperties->load (*m_cmdMediator);
  m_dlgSettingsCurveProperties->setCurveName (selectedGraphCurve ());
  m_dlgSettingsCurveProperties->show ();
}

void MainWindow::slotSettingsDigitizeCurve ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsDigitizeCurve";

  m_dlgSettingsDigitizeCurve->load (*m_cmdMediator);
  m_dlgSettingsDigitizeCurve->show ();
}

void MainWindow::slotSettingsExportFormat ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsExportFormat";

  if (transformIsDefined()) {
    m_dlgSettingsExportFormat->load (*m_cmdMediator);
    m_dlgSettingsExportFormat->show ();
  } else {
    DlgRequiresTransform dlg ("Export settings");
    dlg.exec();
  }
}

void MainWindow::slotSettingsGeneral ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsGeneral";

  m_dlgSettingsGeneral->load (*m_cmdMediator);
  m_dlgSettingsGeneral->show ();
}

void MainWindow::slotSettingsGridDisplay()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsGridDisplay";

  m_dlgSettingsGridDisplay->load (*m_cmdMediator);
  m_dlgSettingsGridDisplay->show ();
}

void MainWindow::slotSettingsGridRemoval ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsGridRemoval";

  m_dlgSettingsGridRemoval->load (*m_cmdMediator);
  m_dlgSettingsGridRemoval->show ();
}

void MainWindow::slotSettingsPointMatch ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsPointMatch";

  m_dlgSettingsPointMatch->load (*m_cmdMediator);
  m_dlgSettingsPointMatch->show ();
}

void MainWindow::slotSettingsSegments ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsSegments";

  m_dlgSettingsSegments->load (*m_cmdMediator);
  m_dlgSettingsSegments->show ();
}

void MainWindow::slotTableStatusChange ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotTableStatusChange";

  // This slot is called when either window in FittingWindow or GeometryWindow loses/gains focus. This is
  // so the Copy menu item can be updated
  updateControls ();
}

void MainWindow::slotSettingsMainWindow ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotSettingsMainWindow";

  m_dlgSettingsMainWindow->loadMainWindowModel (*m_cmdMediator,
                                                m_modelMainWindow);
  m_dlgSettingsMainWindow->show ();
}

void MainWindow::slotTimeoutRegressionErrorReport ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotTimeoutRegressionErrorReport"
                              << " cmdStackIndex=" << m_cmdMediator->index()
                              << " cmdStackCount=" << m_cmdMediator->count();

  if (m_cmdStackShadow->canRedo()) {

    // Always reset current directory before the command. This guarantees the upcoming redo step will work
    QDir::setCurrent (m_startupDirectory);

    m_cmdStackShadow->slotRedo();

    // Always reset current directory after the command. This guarantees the final export to file will work
    QDir::setCurrent (m_startupDirectory);

  } else {

#ifndef OSX_RELEASE
    exportAllCoordinateSystemsAfterRegressionTests ();
#endif

    // Regression test has finished so exit. We unset the dirty flag so there is no prompt
    m_cmdMediator->setClean();
    close();

  }
}

void MainWindow::slotTimeoutRegressionFileCmdScript ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotTimeoutRegressionFileCmdScript";

  if (m_fileCmdScript->canRedo()) {

    // Always reset current directory before the command. This guarantees the upcoming redo step will work
    QDir::setCurrent (m_startupDirectory);

    m_fileCmdScript->redo(*this);

    // Always reset current directory after the command. This guarantees the final export to file will work
    QDir::setCurrent (m_startupDirectory);

  } else {

    // Script file might already have closed the Document so export only if last was not closed
    if (m_cmdMediator != 0) {

#ifndef OSX_RELEASE
      exportAllCoordinateSystemsAfterRegressionTests ();
#endif

      // We unset the dirty flag so there is no "Save changes?" prompt
      m_cmdMediator->setClean();

    }

    // Regression test has finished so exit
    close();

  }
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

void MainWindow::slotViewGridLines ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::slotViewGridLines";

  updateGridLines ();
}

void MainWindow::slotViewGroupBackground(QAction *action)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewGroupBackground";

  // Set the combobox
  BackgroundImage backgroundImage;
  int indexBackground;
  if (action == m_actionViewBackgroundNone) {
    indexBackground = m_cmbBackground->findData (QVariant (BACKGROUND_IMAGE_NONE));
    backgroundImage = BACKGROUND_IMAGE_NONE;
  } else if (action == m_actionViewBackgroundOriginal) {
    indexBackground = m_cmbBackground->findData (QVariant (BACKGROUND_IMAGE_ORIGINAL));
    backgroundImage = BACKGROUND_IMAGE_ORIGINAL;
  } else if (action == m_actionViewBackgroundFiltered) {
    indexBackground = m_cmbBackground->findData (QVariant (BACKGROUND_IMAGE_FILTERED));
    backgroundImage = BACKGROUND_IMAGE_FILTERED;
  } else {
    ENGAUGE_ASSERT (false);

    // Defaults if assert is disabled so execution continues
    indexBackground = m_cmbBackground->findData (QVariant (BACKGROUND_IMAGE_ORIGINAL));
    backgroundImage = BACKGROUND_IMAGE_ORIGINAL;
  }

  m_cmbBackground->setCurrentIndex (indexBackground);
  m_backgroundStateContext->setBackgroundImage (backgroundImage);
}

void MainWindow::slotViewGroupCurves(QAction * /* action */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewGroupCurves";

  updateViewedCurves ();
}

void MainWindow::slotViewGroupStatus(QAction *action)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewGroupStatus";

  ENGAUGE_CHECK_PTR (m_statusBar); // At startup, make sure status bar is already set up when View menu gets initialized

  if (action == m_actionStatusNever) {
    m_statusBar->setStatusBarMode(STATUS_BAR_MODE_NEVER);
  } else if (action == m_actionStatusTemporary) {
    m_statusBar->setStatusBarMode(STATUS_BAR_MODE_TEMPORARY);
  } else {
    m_statusBar->setStatusBarMode(STATUS_BAR_MODE_ALWAYS);
  }
}

void MainWindow::slotViewToolBarBackground ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarBackground";

  if (m_actionViewBackground->isChecked ()) {
    m_toolBackground->show();
  } else {
    m_toolBackground->hide();
  }
}

void MainWindow::slotViewToolBarChecklistGuide ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarChecklistGuide";

  if (m_actionViewChecklistGuide->isChecked ()) {
    m_dockChecklistGuide->show();
  } else {
    m_dockChecklistGuide->hide();
  }
}

void MainWindow::slotViewToolBarCoordSystem ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarCoordSystem";

  if (m_actionViewCoordSystem->isChecked ()) {
    m_toolCoordSystem->show();
  } else {
    m_toolCoordSystem->hide();
  }
}

void MainWindow::slotViewToolBarDigitize ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarDigitize";

  if (m_actionViewDigitize->isChecked ()) {
    m_toolDigitize->show();
  } else {
    m_toolDigitize->hide();
  }
}

void MainWindow::slotViewToolBarFittingWindow()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarFittingWindow";

  if (m_actionViewFittingWindow->isChecked()) {
    m_dockFittingWindow->show ();
    if (m_fittingCurve != 0) {
      m_fittingCurve->setVisible (true);
    }
  } else {
    m_dockFittingWindow->hide ();
    if (m_fittingCurve != 0) {
      m_fittingCurve->setVisible (false);
    }
  }
}

void MainWindow::slotViewToolBarGeometryWindow ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarGeometryWindow";

  if (m_actionViewGeometryWindow->isChecked ()) {
    m_dockGeometryWindow->show();
  } else {
    m_dockGeometryWindow->hide();
  }
}

void MainWindow::slotViewToolBarSettingsViews ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolBarSettingsViews";

  if (m_actionViewSettingsViews->isChecked ()) {
    m_toolSettingsViews->show();
  } else {
    m_toolSettingsViews->hide();
  }
}

void MainWindow::slotViewToolTips ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewToolTips";

  loadToolTips();
}

void MainWindow::slotViewZoom(int zoom)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoom";

  // Update zoom controls and apply the zoom factor
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

  m_backgroundStateContext->fitInView (*m_view);

  emit signalZoom(ZOOM_FILL);
}

void MainWindow::slotViewZoomIn ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomIn";

  // Try to zoom in. First determine what the next zoom factor should be

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

  // Update controls and apply zoom factor
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

void MainWindow::slotViewZoomInFromWheelEvent ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomInFromWheelEvent";

  if ((m_modelMainWindow.zoomControl() == ZOOM_CONTROL_MENU_WHEEL) ||
      (m_modelMainWindow.zoomControl() == ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS)) {

    // Anchor the zoom to the cursor position
    m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Forward this event
    slotViewZoomIn ();

    m_view->setTransformationAnchor(QGraphicsView::NoAnchor);
  }
}

void MainWindow::slotViewZoomOut ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomOut";

  // Try to zoom out. First determine what the next zoom factor should be

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

  // Update controls and apply zoom factor
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

void MainWindow::slotViewZoomOutFromWheelEvent ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::slotViewZoomOutFromWheelEvent";

  if ((m_modelMainWindow.zoomControl() == ZOOM_CONTROL_MENU_WHEEL) ||
      (m_modelMainWindow.zoomControl() == ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS)) {

    // Anchor the zoom to the cursor position
    m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Forward this event
    slotViewZoomOut ();

    m_view->setTransformationAnchor(QGraphicsView::NoAnchor);
  }
}

void MainWindow::startRegressionTestErrorReport(const QString &regressionInputFile)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::startRegressionTestErrorReport";

  // In order for point-deleting commands to work (CmdCut, CmdDelete) in the regression tests, we need to
  // reset the Point identifier index here:
  // 1) after loading of the file which has increased the index value to greater than 0
  // 2) before running any commands since those commands implicitly assume the index is zero
  Point::setIdentifierIndex(0);

  // Save output/export file name
  m_regressionFile = exportFilenameFromInputFilename (regressionInputFile);

  m_timerRegressionErrorReport = new QTimer();
  m_timerRegressionErrorReport->setSingleShot(false);
  connect (m_timerRegressionErrorReport, SIGNAL (timeout()), this, SLOT (slotTimeoutRegressionErrorReport()));

  m_timerRegressionErrorReport->start(REGRESSION_INTERVAL);
}

void MainWindow::startRegressionTestFileCmdScript()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::startRegressionTestFileCmdScript";

  m_timerRegressionFileCmdScript = new QTimer();
  m_timerRegressionFileCmdScript->setSingleShot(false);
  connect (m_timerRegressionFileCmdScript, SIGNAL (timeout()), this, SLOT (slotTimeoutRegressionFileCmdScript()));

  m_timerRegressionFileCmdScript->start(REGRESSION_INTERVAL);
}

Transformation MainWindow::transformation() const
{
  return m_transformation;
}

bool MainWindow::transformIsDefined() const
{
  return m_transformation.transformIsDefined();
}

void MainWindow::updateAfterCommand ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateAfterCommand";

  ENGAUGE_CHECK_PTR (m_cmdMediator);

  // Update transformation stuff, including the graph coordinates of every point in the Document, so coordinates in
  // status bar are up to date. Point coordinates in Document are also updated
  updateAfterCommandStatusBarCoords ();

  updateHighlightOpacity ();

  // Update graphics. Effectively, these steps do very little (just needed for highlight opacity)
  m_digitizeStateContext->updateAfterPointAddition (); // May or may not be needed due to point addition

  updateControls ();
  updateChecklistGuide ();
  updateFittingWindow ();
  updateGeometryWindow();

  // Final action at the end of a redo/undo is to checkpoint the Document and GraphicsScene to log files
  // so proper state can be verified
  writeCheckpointToLogFile ();

  // Since focus may have drifted over to Geometry Window or some other control we se focus on the GraphicsView
  // so the cursor is appropriate for the current state (otherwise it often ends up as default arrow)
  m_view->setFocus ();
}

void MainWindow::updateAfterCommandStatusBarCoords ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateAfterCommandStatusBarCoords";

  // For some reason, mapFromGlobal(QCursor::pos) differs from event->pos by a little bit. We must compensate for
  // this so cursor coordinates in status bar match the DlgEditPointAxis inputs initially. After the mouse moves
  // the problem disappears since event->pos is available and QCursor::pos is no longer needed
  const QPoint HACK_SO_GRAPH_COORDINATE_MATCHES_INPUT (1, 1);

  Transformation m_transformationBefore (m_transformation);

  updateTransformationAndItsDependencies();

  // Trigger state transitions for transformation if appropriate
  if (!m_transformationBefore.transformIsDefined() && m_transformation.transformIsDefined()) {

    // Transition from undefined to defined
    m_transformationStateContext->triggerStateTransition(TRANSFORMATION_STATE_DEFINED,
                                                         *m_cmdMediator,
                                                         m_transformation,
                                                         selectedGraphCurve());

  } else if (m_transformationBefore.transformIsDefined() && !m_transformation.transformIsDefined()) {

    // Transition from defined to undefined
    m_transformationStateContext->triggerStateTransition(TRANSFORMATION_STATE_UNDEFINED,
                                                         *m_cmdMediator,
                                                         m_transformation,
                                                         selectedGraphCurve());

  } else if (m_transformation.transformIsDefined() && (m_transformationBefore != m_transformation)) {

    // There was not a define/undefined or undefined/defined transition, but the transformation changed so we
    // need to update the Checker
    m_transformationStateContext->updateAxesChecker(*m_cmdMediator,
                                                    m_transformation);

  }

  QPoint posLocal = m_view->mapFromGlobal (QCursor::pos ()) - HACK_SO_GRAPH_COORDINATE_MATCHES_INPUT;
  QPointF posScreen = m_view->mapToScene (posLocal);

  slotMouseMove (posScreen); // Update the status bar coordinates to reflect the newly updated transformation
}

void MainWindow::updateAfterMouseRelease ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateAfterMouseRelease";

  updateControls ();
}

void MainWindow::updateChecklistGuide ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateChecklistGuide";

  m_isDocumentExported = true; // Set for next line and for all checklist guide updates after this
  m_dockChecklistGuide->update (*m_cmdMediator,
                                m_isDocumentExported);
}

void MainWindow::updateControls ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateControls"
                              << " selectedItems=" << m_scene->selectedItems().count();

  m_cmbBackground->setEnabled (!m_currentFile.isEmpty ());

  m_actionImportImageReplace->setEnabled (m_cmdMediator != 0);
#ifndef OSX_RELEASE
  m_menuFileOpenRecent->setEnabled ((m_actionRecentFiles.count () > 0) &&
                                    (m_actionRecentFiles.at(0)->isVisible ())); // Need at least one visible recent file entry
#endif
  m_actionClose->setEnabled (!m_currentFile.isEmpty ());
  m_actionSave->setEnabled (!m_currentFile.isEmpty ());
  m_actionSaveAs->setEnabled (!m_currentFile.isEmpty ());
  m_actionExport->setEnabled (!m_currentFile.isEmpty ());
  m_actionPrint->setEnabled (!m_currentFile.isEmpty ());

  if (m_cmdMediator == 0) {
    m_actionEditUndo->setEnabled (false);
    m_actionEditRedo->setEnabled (false);
  } else {
    m_actionEditUndo->setEnabled (m_cmdMediator->canUndo ());
    m_actionEditRedo->setEnabled (m_cmdMediator->canRedo () || m_cmdStackShadow->canRedo ());
  }
  bool tableFittingIsActive, tableFittingIsCopyable;
  bool tableGeometryIsActive, tableGeometryIsCopyable;
  m_dockFittingWindow->getTableStatus (tableFittingIsActive, tableFittingIsCopyable); // Fitting window status
  m_dockGeometryWindow->getTableStatus (tableGeometryIsActive, tableGeometryIsCopyable); // Geometry window status
  m_actionEditCut->setEnabled (!tableFittingIsActive &&
                               !tableGeometryIsActive &&
                               m_scene->selectedItems().count () > 0);
  m_actionEditCopy->setEnabled ((!tableFittingIsActive && !tableGeometryIsActive && m_scene->selectedItems().count () > 0) ||
                                (tableFittingIsActive && tableFittingIsCopyable) ||
                                (tableGeometryIsActive && tableGeometryIsCopyable));
  m_actionEditPaste->setEnabled (false);
  m_actionEditDelete->setEnabled (!tableFittingIsActive &&
                                  !tableGeometryIsActive &&
                                  m_scene->selectedItems().count () > 0);
  // m_actionEditPasteAsNew and m_actionEditPasteAsNewAdvanced are updated when m_menuEdit is about to be shown

  m_actionDigitizeAxis->setEnabled (modeGraph ());
  m_actionDigitizeScale->setEnabled (modeMap ());
  m_actionDigitizeCurve ->setEnabled (!m_currentFile.isEmpty ());
  m_actionDigitizePointMatch->setEnabled (!m_currentFile.isEmpty ());
  m_actionDigitizeColorPicker->setEnabled (!m_currentFile.isEmpty ());
  m_actionDigitizeSegment->setEnabled (!m_currentFile.isEmpty ());
  m_actionDigitizeSelect->setEnabled (!m_currentFile.isEmpty ());
  if (m_transformation.transformIsDefined()) {
    m_actionViewGridLines->setEnabled (true);
  } else {
    m_actionViewGridLines->setEnabled (false);
    m_actionViewGridLines->setChecked (false);
  }
  m_actionViewBackground->setEnabled (!m_currentFile.isEmpty());
  m_actionViewChecklistGuide->setEnabled (!m_dockChecklistGuide->browserIsEmpty());
  m_actionViewDigitize->setEnabled (!m_currentFile.isEmpty ());
  m_actionViewSettingsViews->setEnabled (!m_currentFile.isEmpty ());

  m_actionSettingsCoords->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsCurveAddRemove->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsCurveProperties->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsDigitizeCurve->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsExport->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsColorFilter->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsAxesChecker->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsGridDisplay->setEnabled (!m_currentFile.isEmpty () && m_transformation.transformIsDefined());
  m_actionSettingsGridRemoval->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsPointMatch->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsSegments->setEnabled (!m_currentFile.isEmpty ());
  m_actionSettingsGeneral->setEnabled (!m_currentFile.isEmpty ());

  m_groupBackground->setEnabled (!m_currentFile.isEmpty ());
  m_groupCurves->setEnabled (!m_currentFile.isEmpty ());
  m_groupZoom->setEnabled (!m_currentFile.isEmpty ());

  m_actionZoomIn->setEnabled (!m_currentFile.isEmpty ()); // Disable at startup so shortcut has no effect
  m_actionZoomOut->setEnabled (!m_currentFile.isEmpty ()); // Disable at startup so shortcut has no effect
}

void MainWindow::updateCoordSystem(CoordSystemIndex coordSystemIndex)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateCoordSystem";

  // Set current curve in the Document and in the MainWindow combobox together so they are in sync. Setting
  // the selected curve prevents a crash in updateTransformationAndItsDependencies
  m_cmdMediator->document().setCoordSystemIndex (coordSystemIndex);
  loadCurveListFromCmdMediator ();

  updateTransformationAndItsDependencies(); // Transformation state may have changed
  updateSettingsAxesChecker(m_cmdMediator->document().modelAxesChecker()); // Axes checker dependes on transformation state

  // Nice trick for showing that a new coordinate system is in effect is to show the axes checker
  m_transformationStateContext->updateAxesChecker (*m_cmdMediator,
                                                   m_transformation);

  updateAfterCommand();
}

void MainWindow::updateDigitizeStateIfSoftwareTriggered (DigitizeState digitizeState)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateDigitizeStateIfSoftwareTriggered";

  switch (digitizeState) {
    case DIGITIZE_STATE_AXIS:
      m_actionDigitizeAxis->setChecked(true);
      slotDigitizeAxis(); // Call the slot that the setChecked call fails to trigger
      break;

    case DIGITIZE_STATE_COLOR_PICKER:
      m_actionDigitizeColorPicker->setChecked(true);
      slotDigitizeColorPicker(); // Call the slot that the setChecked call fails to trigger
      break;

    case DIGITIZE_STATE_CURVE:
      m_actionDigitizeCurve->setChecked(true);
      slotDigitizeCurve(); // Call the slot that the setChecked call fails to trigger
      break;

    case DIGITIZE_STATE_EMPTY:
      break;

    case DIGITIZE_STATE_POINT_MATCH:
      m_actionDigitizePointMatch->setChecked(true);
      slotDigitizePointMatch(); // Call the slot that the setChecked call fails to trigger
      break;

    case DIGITIZE_STATE_SCALE:
      m_actionDigitizeScale->setChecked(true);
      slotDigitizeScale(); // Call the slot that the setChecked call fails to trigger
      break;

    case DIGITIZE_STATE_SEGMENT:
      m_actionDigitizeSegment->setChecked(true);
       slotDigitizeSegment(); // Call the slot that the setChecked call fails to trigger
      break;

    case DIGITIZE_STATE_SELECT:
      m_actionDigitizeSelect->setChecked(true);
      slotDigitizeSelect(); // Call the slot that the setChecked call fails to trigger
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "MainWindow::updateDigitizeStateIfSoftwareTriggered";
      break;
  }
}

void MainWindow::updateFittingWindow ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateFittingWindow";

  if (m_cmdMediator != 0 &&
      m_cmbCurve != 0) {

    // Update fitting window
    m_dockFittingWindow->update (*m_cmdMediator,
                                 m_modelMainWindow,
                                 m_cmbCurve->currentText (),
                                 m_transformation);
  }
}

void MainWindow::updateGeometryWindow ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateGeometryWindow";

  if (m_cmdMediator != 0 &&
      m_cmbCurve != 0) {

    // Update geometry window
    m_dockGeometryWindow->update (*m_cmdMediator,
                                  m_modelMainWindow,
                                  m_cmbCurve->currentText (),
                                  m_transformation);
  }
}

void MainWindow::updateGraphicsLinesToMatchGraphicsPoints()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateGraphicsLinesToMatchGraphicsPoints";

  m_scene->updateGraphicsLinesToMatchGraphicsPoints(m_cmdMediator->document().modelCurveStyles(),
                                                    m_transformation);
}

void MainWindow::updateGridLines ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateGridLines";

  // Remove old grid lines
  m_gridLines.clear ();

  // Create new grid lines
  GridLineFactory factory (*m_scene,
                           m_cmdMediator->document().modelCoords());
  factory.createGridLinesForEvenlySpacedGrid (m_cmdMediator->document().modelGridDisplay(),
                                              m_cmdMediator->document(),
                                              m_modelMainWindow,
                                              m_transformation,
                                              m_gridLines);

  m_gridLines.setVisible (m_actionViewGridLines->isChecked());
}

void MainWindow::updateHighlightOpacity ()
{
  if (m_cmdMediator != 0) {

    // Update the QGraphicsScene with the populated Curves. This requires the points in the Document to be already updated
    // by updateAfterCommandStatusBarCoords
    m_scene->updateAfterCommand (*m_cmdMediator,
                                 m_modelMainWindow.highlightOpacity(),
                                 m_dockGeometryWindow);
  }
}

void MainWindow::updateRecentFileList()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateRecentFileList";

#ifndef OSX_RELEASE
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  QStringList recentFilePaths = settings.value(SETTINGS_RECENT_FILE_LIST).toStringList();

  // Determine the desired size of the path list
  unsigned int count = recentFilePaths.size();
  if (count > MAX_RECENT_FILE_LIST_SIZE) {
    count = MAX_RECENT_FILE_LIST_SIZE;
  }

  // Add visible entries
  unsigned int i;
  for (i = 0; i < count; i++) {
    QString strippedName = QFileInfo (recentFilePaths.at(i)).fileName();
    m_actionRecentFiles.at (i)->setText (strippedName);
    m_actionRecentFiles.at (i)->setData (recentFilePaths.at (i));
    m_actionRecentFiles.at (i)->setVisible (true);
  }

  // Hide any extra entries
  for (i = count; i < MAX_RECENT_FILE_LIST_SIZE; i++) {
    m_actionRecentFiles.at (i)->setVisible (false);
  }
#endif
}

void MainWindow::updateSettingsAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsAxesChecker";

  m_cmdMediator->document().setModelAxesChecker(modelAxesChecker);
  if (m_transformation.transformIsDefined()) {
    m_transformationStateContext->triggerStateTransition(TRANSFORMATION_STATE_DEFINED,
                                                         *m_cmdMediator,
                                                         m_transformation,
                                                         m_cmbCurve->currentText());
  } else {
    m_transformationStateContext->triggerStateTransition(TRANSFORMATION_STATE_UNDEFINED,
                                                         *m_cmdMediator,
                                                         m_transformation,
                                                         m_cmbCurve->currentText());
  }
}

void MainWindow::updateSettingsColorFilter(const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsColorFilter";

  m_cmdMediator->document().setModelColorFilter(modelColorFilter);
  m_backgroundStateContext->updateColorFilter (m_transformation,
                                               m_cmdMediator->document().modelGridRemoval(),
                                               modelColorFilter,
                                               m_cmbCurve->currentText());
  m_digitizeStateContext->handleCurveChange (m_cmdMediator);
  updateViewsOfSettings();
}

void MainWindow::updateSettingsCoords(const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsCoords";

  m_cmdMediator->document().setModelCoords(modelCoords);
}

void MainWindow::updateSettingsCurveAddRemove (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsCurveAddRemove";

  m_cmdMediator->document().setCurvesGraphs (curvesGraphs);
  loadCurveListFromCmdMediator();
  updateViewsOfSettings();
}

void MainWindow::updateSettingsCurveStyles(const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsCurveStyles";

  m_scene->updateCurveStyles(modelCurveStyles);
  m_cmdMediator->document().setModelCurveStyles(modelCurveStyles);
  updateViewsOfSettings();
}

void MainWindow::updateSettingsDigitizeCurve(const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsDigitizeCurve";

  m_cmdMediator->document().setModelDigitizeCurve(modelDigitizeCurve);
  m_digitizeStateContext->updateModelDigitizeCurve (m_cmdMediator,
                                                    modelDigitizeCurve);
}

void MainWindow::updateSettingsExportFormat(const DocumentModelExportFormat &modelExport)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsExportFormat";

  m_cmdMediator->document().setModelExport (modelExport);
}

void MainWindow::updateSettingsGeneral(const DocumentModelGeneral &modelGeneral)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsGeneral";

  m_cmdMediator->document().setModelGeneral(modelGeneral);
}

void MainWindow::updateSettingsGridDisplay(const DocumentModelGridDisplay &modelGridDisplay)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsGridDisplay";

  m_cmdMediator->document().setModelGridDisplay(modelGridDisplay);
}

void MainWindow::updateSettingsGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsGridRemoval";

  m_cmdMediator->document().setModelGridRemoval(modelGridRemoval);
}

void MainWindow::updateSettingsMainWindow()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsMainWindow";

  if (m_modelMainWindow.zoomControl() == ZOOM_CONTROL_MENU_ONLY ||
      m_modelMainWindow.zoomControl() == ZOOM_CONTROL_MENU_WHEEL) {

    m_actionZoomIn->setShortcut (tr (""));
    m_actionZoomOut->setShortcut (tr (""));

  } else {

    m_actionZoomIn->setShortcut (tr ("+"));
    m_actionZoomOut->setShortcut (tr ("-"));

  }

  if ((m_scene != 0) &&
      (m_cmdMediator != 0)) {
    m_scene->updateCurveStyles(m_cmdMediator->document().modelCurveStyles());
  }

  updateHighlightOpacity();
  updateWindowTitle();
  updateFittingWindow(); // Forward the drag and drop choice
  updateGeometryWindow(); // Forward the drag and drop choice
}

void MainWindow::updateSettingsMainWindow(const MainWindowModel &modelMainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsMainWindow";

  m_modelMainWindow = modelMainWindow;
  updateSettingsMainWindow();
}

void MainWindow::updateSettingsPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsPointMatch";

  m_cmdMediator->document().setModelPointMatch(modelPointMatch);
}

void MainWindow::updateSettingsSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateSettingsSegments";

  m_cmdMediator->document().setModelSegments(modelSegments);
  m_digitizeStateContext->updateModelSegments(modelSegments);
}

void MainWindow::updateSmallDialogs ()
{
  m_dlgSettingsAxesChecker->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsColorFilter->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsCoords->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsCurveAddRemove->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsCurveProperties->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsDigitizeCurve->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsExportFormat->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsGeneral->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsGridDisplay->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsGridRemoval->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsMainWindow->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsPointMatch->setSmallDialogs (m_modelMainWindow.smallDialogs ());
  m_dlgSettingsSegments->setSmallDialogs (m_modelMainWindow.smallDialogs ());
}

void MainWindow::updateTransformationAndItsDependencies()
{
  m_transformation.update (!m_currentFile.isEmpty (),
                           *m_cmdMediator,
                           m_modelMainWindow);

  // Grid removal is affected by new transformation above
  m_backgroundStateContext->setCurveSelected (m_transformation,
                                              m_cmdMediator->document().modelGridRemoval(),
                                              m_cmdMediator->document().modelColorFilter(),
                                              m_cmbCurve->currentText ());

  // Grid display is also affected by new transformation above, if there was a transition into defined state
  // in which case that transition triggered the initialization of the grid display parameters
  updateGridLines();
}

void MainWindow::updateViewedCurves ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateViewedCurves";

  if (m_actionViewCurvesAll->isChecked ()) {

    m_scene->showCurves (true, true);

  } else if (m_actionViewCurvesSelected->isChecked ()) {

    m_scene->showCurves (true, false, selectedGraphCurve ());

  } else if (m_actionViewCurvesNone->isChecked ()) {

    m_scene->showCurves (false);

  } else {
    ENGAUGE_ASSERT (false);
  }
}

void MainWindow::updateViewsOfSettings ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateViewsOfSettings";

  QString activeCurve = m_digitizeStateContext->activeCurve ();

  updateViewsOfSettings (activeCurve);
}

void MainWindow::updateViewsOfSettings (const QString &activeCurve)
{
  if (activeCurve.isEmpty ()) {

    m_viewPointStyle->unsetPointStyle ();
    m_viewSegmentFilter->unsetColorFilterSettings ();


  } else {

    PointStyle pointStyle = m_cmdMediator->document().modelCurveStyles().curveStyle(activeCurve).pointStyle();
    m_viewPointStyle->setPointStyle (pointStyle);

    ColorFilterSettings colorFilterSettings = m_cmdMediator->document().modelColorFilter().colorFilterSettings(activeCurve);
    m_viewSegmentFilter->setColorFilterSettings (colorFilterSettings,
                                                 m_cmdMediator->pixmap ());

  }
}

void MainWindow::updateWindowTitle ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::updateWindowTitle";

  const QString PLACEHOLDER ("[*]");

  QString title = QString (tr ("Engauge Digitizer %1")
                           .arg (VERSION_NUMBER));

  QString fileNameMaybeStripped;
  if (!m_currentFileWithPathAndFileExtension.isEmpty()) {

    QFileInfo fileInfo (m_currentFileWithPathAndFileExtension);

    switch (m_modelMainWindow.mainTitleBarFormat())
    {
      case MAIN_TITLE_BAR_FORMAT_NO_PATH:
        fileNameMaybeStripped = fileInfo.baseName(); // Remove file extension and path for "clean look"
        break;

      case MAIN_TITLE_BAR_FORMAT_PATH:
        fileNameMaybeStripped = m_currentFileWithPathAndFileExtension;
        break;
    }

    title += QString (": %1")
             .arg (fileNameMaybeStripped);
  }

  // To prevent "QWidget::setWindowModified: The window title does not contain a [*] placeholder" warnings,
  // we always append a placeholder
  title += PLACEHOLDER;

  setWindowTitle (title);
}

GraphicsView &MainWindow::view ()
{
  ENGAUGE_CHECK_PTR (m_view);
  return *m_view;
}

const GraphicsView &MainWindow::view () const
{
  ENGAUGE_CHECK_PTR (m_view);
  return *m_view;
}

void MainWindow::writeCheckpointToLogFile ()
{
  // Document
  QString checkpointDoc;
  QTextStream strDoc (&checkpointDoc);
  m_cmdMediator->document().printStream(INDENTATION_PAST_TIMESTAMP,
                                        strDoc);

  // Scene
  QString checkpointScene;
  QTextStream strScene (&checkpointScene);
  m_scene->printStream (INDENTATION_PAST_TIMESTAMP,
                        strScene);

  // Skip slow string manipulation if BEFORE call to LOG4CPP_DEBUG_S
  if (mainCat->getPriority() == log4cpp::Priority::DEBUG) {

    LOG4CPP_DEBUG_S ((*mainCat)) << "MainWindow::writeCheckpointToLogFile\n"
                                 << "--------------DOCUMENT CHECKPOINT START----------" << "\n"
                                 << checkpointDoc.toLatin1().data()
                                 << "---------------DOCUMENT CHECKPOINT END-----------" << "\n"
                                 << "----------------SCENE CHECKPOINT START-----------" << "\n"
                                 << checkpointScene.toLatin1().data()
                                 << "-----------------SCENE CHECKPOINT END------------" ;
  }
}
