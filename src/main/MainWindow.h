#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "BackgroundImage.h"
#include "CoordSystemIndex.h"
#include "DigitizeStateAbstractBase.h"
#include "DocumentAxesPointsRequired.h"
#include "MainWindowModel.h"
#include <QCursor>
#include <QMainWindow>
#include <QUrl>
#include "Transformation.h"
#include "ZoomControl.h"
#include "ZoomFactor.h"

class BackgroundStateContext;
class ChecklistGuide;
class CmdMediator;
class CmdStackShadow;
class CurveStyles;
class DigitizeStateContext;
class DlgSettingsAxesChecker;
class DlgSettingsColorFilter;
class DlgSettingsCoords;
class DlgSettingsCurveAddRemove;
class DlgSettingsCurveProperties;
class DlgSettingsDigitizeCurve;
class DlgSettingsExportFormat;
class DlgSettingsGeneral;
class DlgSettingsGridRemoval;
class DlgSettingsMainWindow;
class DlgSettingsPointMatch;
class DlgSettingsSegments;
class DocumentModelAxesChecker;
class DocumentModelColorFilter;
class DocumentModelCoords;
class DocumentModelDigitizeCurve;
class DocumentModelExportFormat;
class DocumentModelGeneral;
class DocumentModelGridRemoval;
class DocumentModelPointMatch;
class DocumentModelSegments;
class ExportToFile;
class FileCmdScript;
class Ghosts;
class GraphicsScene;
class GraphicsView;
class HelpWindow;
class LoadImageFromUrl;
class NetworkClient;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QDomDocument;
class QGraphicsLineItem;
class QMenu;
class QPushButton;
class QSettings;
class QTextStream;
class QTimer;
class QToolBar;
class QVBoxLayout;
class StatusBar;
class TransformationStateContext;
class TutorialDlg;
class ViewPointStyle;
class ViewSegmentFilter;

/// Main window consisting of menu, graphics scene, status bar and optional
/// toolbars as a Single Document Interface
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  /// Single constructor.
  /// \param errorReportFile Optional error report file to be read at startup.
  /// Empty if unused. Incompatible with fileCmdScript
  /// \param fileCmdScriptFile Optional file command script file to be read at
  /// startup. Empty if unused. Incompatible with errorReportFile
  /// \param isRegressionTest True if errorReportFile or fileCmdScript is for
  /// regression testing, in which case it is executed and the program exits
  /// \param isGnuplot True if diagnostic gnuplot files are generated for
  /// math-intense sections of the code. Used for development and debugging
  /// \param loadStartupFiles Zero or more Engauge document files to load at
  /// startup. A separate instance of Engauge is created for each file
  /// \param parent Optional parent widget for this widget
  MainWindow(const QString &errorReportFile, const QString &fileCmdScriptFile,
             bool isRegressionTest, bool isGnuplot,
             QStringList loadStartupFiles, QWidget *parent = 0);
  ~MainWindow();

  /// Close file. This is called from a file script command
  void cmdFileClose();

  /// Export file. This is called from a file script command
  void cmdFileExport(const QString &fileName);

  /// Import file. This is called from a file script command
  void cmdFileImport(const QString &fileName);

  /// Open file. This is called from a file script command
  void cmdFileOpen(const QString &fileName);

  /// Accessor for commands to process the Document.
  CmdMediator *cmdMediator();

  /// Catch secret keypresses
  virtual bool eventFilter(QObject *, QEvent *);

  /// Background image that has been filtered for the current curve. This
  /// asserts if a curve-specific image is not being shown
  QImage imageFiltered() const;

  /// Get method for gnuplot flag
  bool isGnuplot() const;

  /// Get method for main window model
  MainWindowModel modelMainWindow() const;

  /// Intercept resize event so graphics scene can be appropriately resized when
  /// in Fill mode.
  void resizeEvent(QResizeEvent *event);

  /// Save error report and exit
  void saveErrorReportFileAndExit(const char *comment, const char *file,
                                  int line, const char *context) const;

  /// Scene container for the QImage and QGraphicsItems.
  GraphicsScene &scene();

  /// Make original background visible, for DigitizeStateColorPicker. This
  /// returns the previous background state for restoring
  /// when state finishes
  BackgroundImage selectOriginal(BackgroundImage backgroundImage);

  /// Curve name that is currently selected in m_cmbCurve.
  QString selectedGraphCurve() const;

  /// Processing performed after gui becomes available
  virtual void showEvent(QShowEvent *);

  /// Show temporary message in status bar
  void showTemporaryMessage(const QString &temporaryMessage);

  /// Return read-only copy of transformation
  Transformation transformation() const;

  /// Return true if all three axis points have been defined.
  bool transformIsDefined() const;

  /// See GraphicsScene::updateAfterCommand
  void updateAfterCommand();

  /// Call MainWindow::updateControls (which is private) after the very specific
  /// case - a mouse press/release.
  void updateAfterMouseRelease();

  /// Select a different CoordSystem
  void updateCoordSystem(CoordSystemIndex coordSystemIndex);

  /// After software-triggered state transition, this method manually triggers
  /// the action as if user had clicked on digitize button
  void updateDigitizeStateIfSoftwareTriggered(DigitizeState digitizeState);

  /// Update the graphics lines so they follow the graphics points, after a
  /// drag, addition, removal, and such. The points
  /// in the Document may (and probably are) out of date with respect to the
  /// graphics points
  void updateGraphicsLinesToMatchGraphicsPoints();

  /// Update with new axes indicator properties.
  void
  updateSettingsAxesChecker(const DocumentModelAxesChecker &modelAxesChecker);

  /// Update with new color filter properties.
  void
  updateSettingsColorFilter(const DocumentModelColorFilter &modelColorFilter);

  /// Update with new coordinate properties.
  void updateSettingsCoords(const DocumentModelCoords &modelCoords);

  /// Update with new curves.
  void updateSettingsCurveAddRemove(const CurvesGraphs &curvesGraphs);

  /// Update with new curve styles.
  void updateSettingsCurveStyles(const CurveStyles &modelCurveStyles);

  /// Update with new curve digitization styles.
  void updateSettingsDigitizeCurve(
      const DocumentModelDigitizeCurve &modelDigitizeCurve);

  /// Update with new export properties.
  void updateSettingsExportFormat(const DocumentModelExportFormat &modelExport);

  /// Update with new general properties.
  void updateSettingsGeneral(const DocumentModelGeneral &modelGeneral);

  /// Update with new grid removal properties.
  void
  updateSettingsGridRemoval(const DocumentModelGridRemoval &modelGridRemoval);

  /// Update with new main window properties.
  void updateSettingsMainWindow(const MainWindowModel &modelMainWindow);

  /// Update with new point match properties.
  void updateSettingsPointMatch(const DocumentModelPointMatch &modelPointMatch);

  /// Update with new segments properties.
  void updateSettingsSegments(const DocumentModelSegments &modelSegments);

  /// Update curve-specific view of settings. Private version gets active curve
  /// name from DigitizeStateContext
  void updateViewsOfSettings(const QString &activeCurve);

  /// View for the QImage and QGraphicsItems, without const.
  GraphicsView &view();

  /// View for the QImage and QGraphicsItems, without const.
  const GraphicsView &view() const;

private slots:
  void slotBtnPrintAll();
  void slotBtnShowAllPressed();
  void slotBtnShowAllReleased();
  void slotCanRedoChanged(bool);
  void slotCanUndoChanged(bool);
  void slotChecklistClosed();
  void slotCleanChanged(bool);
  void slotCmbBackground(int);
  void slotCmbCoordSystem(int);
  void slotCmbCurve(int);
  void slotContextMenuEvent(QString);
  void slotDigitizeAxis();
  void slotDigitizeColorPicker();
  void slotDigitizeCurve();
  void slotDigitizePointMatch();
  void slotDigitizeSegment();
  void slotDigitizeSelect();
  void slotEditCopy();
  void slotEditCut();
  void slotEditDelete();
  void slotEditMenu();
  void slotEditPaste();
  void slotEditPasteAsNew();
  void slotEditPasteAsNewAdvanced();
  void slotFileClose();
  void slotFileExport();
  void slotFileImport();
  void slotFileImportAdvanced();
  void slotFileImportDraggedImage(QImage);
  void slotFileImportDraggedImageUrl(QUrl);
  void slotFileImportImage(QString, QImage);
  void slotFileOpen();
  void slotFileOpenDraggedDigFile(QString);
  void slotFilePrint();
  bool slotFileSave();   /// Slot method that is sometimes called directly with
                         /// return value expected
  bool slotFileSaveAs(); /// Slot method that is sometimes called directly with
                         /// return value expected
  void slotHelpAbout();
  void slotHelpTutorial();
  void slotKeyPress(Qt::Key, bool);
  void slotLeave();
  void slotLoadStartupFiles();
  void slotMouseMove(QPointF);
  void slotMousePress(QPointF);
  void slotMouseRelease(QPointF);
  void slotRecentFileAction();
  void slotRecentFileClear();
  void slotRedoTextChanged(const QString &);
  void slotSetOverrideCursor(QCursor);
  void slotSettingsAxesChecker();
  void slotSettingsColorFilter();
  void slotSettingsCoords();
  void slotSettingsCurveAddRemove();
  void slotSettingsCurveProperties();
  void slotSettingsDigitizeCurve();
  void slotSettingsExportFormat();
  void slotSettingsGeneral();
  void slotSettingsGridRemoval();
  void slotSettingsMainWindow();
  void slotSettingsPointMatch();
  void slotSettingsSegments();
  void slotTimeoutRegressionErrorReport();
  void slotTimeoutRegressionFileCmdScript();
  void slotUndoTextChanged(const QString &);
  void slotViewGroupBackground(QAction *);
  void slotViewGroupCurves(QAction *);
  void slotViewGroupStatus(QAction *);
  void slotViewToolBarBackground();
  void slotViewToolBarChecklistGuide();
  void slotViewToolBarCoordSystem();
  void slotViewToolBarDigitize();
  void slotViewToolBarSettingsViews();
  void slotViewToolTips();
  void slotViewZoom16To1();
  void slotViewZoom8To1();
  void slotViewZoom4To1();
  void slotViewZoom2To1();
  void slotViewZoom1To1();
  void slotViewZoom1To2();
  void slotViewZoom1To4();
  void slotViewZoom1To8();
  void slotViewZoom1To16();
  void slotViewZoom(int);
  void slotViewZoomFill();
  void slotViewZoomIn();
  void slotViewZoomInFromWheelEvent();
  void slotViewZoomOut();
  void slotViewZoomOutFromWheelEvent();

signals:
  /// Send zoom selection, picked from menu or keystroke, to StatusBar.
  void signalZoom(int);

private:
  MainWindow();

  enum ImportType { IMPORT_TYPE_SIMPLE, IMPORT_TYPE_ADVANCED };

  void applyZoomFactorAfterLoad();
  virtual void closeEvent(QCloseEvent *event);
  void createActions();
  void createActionsDigitize();
  void createActionsEdit();
  void createActionsFile();
  void createActionsHelp();
  void createActionsSettings();
  void createActionsView();
  void createCentralWidget();
  void createCommandStackShadow();
  void createHelpWindow();
  void createIcons();
  void createLoadImageFromUrl();
  void createMenus();
  void createNetwork();
  void createScene();
  void createSettingsDialogs();
  void createStateContextBackground();
  void createStateContextDigitize();
  void createStateContextTransformation();
  void createStatusBar();
  void createToolBars();
  void createTutorial();
  ZoomFactor currentZoomFactor() const;
  void exportAllCoordinateSystems();
  QString exportFilenameFromInputFilename(const QString &fileName) const;
  void fileExport(const QString &fileName, ExportToFile exportStrategy);
  void fileImport(const QString &fileName,
                  ImportType ImportType); /// Same steps as filePaste but with
                                          /// import from file
  void fileImportWithPrompts(ImportType ImportType); /// Wrapper around
                                                     /// fileImport that adds
                                                     /// user prompt(s)
  void filePaste(ImportType importType); /// Same steps as fileImport but with
                                         /// import from clipboard
  void ghostsCreate();  /// Create the ghosts for seeing all coordinate systems
                        /// at once
  void ghostsDestroy(); /// Destroy the ghosts for seeing all coordinate systems
                        /// at once
  void loadCoordSystemListFromCmdMediator(); /// Update the combobox that has
                                             /// the CoordSystem list
  void loadCurveListFromCmdMediator(); /// Update the combobox that has the
                                       /// curve names.
  void loadDocumentFile(const QString &fileName);
  void loadErrorReportFile(const QString &initialPath,
                           const QString &errorReportFile);
  bool loadImage(const QString &fileName, const QImage &image,
                 ImportType ImportType);
  void loadInputFileForErrorReport(QDomDocument &domInputFile) const;
  void loadToolTips();
  bool maybeSave();
  DocumentModelExportFormat
  modelExportOverride(const DocumentModelExportFormat &modelExportFormatBefore,
                      const ExportToFile &exportStrategy,
                      const QString &selectedNameFilter) const;
  void rebuildRecentFileListForCurrentFile(const QString &filePath);
  bool saveDocumentFile(const QString &fileName);
  QString saveErrorReportFileAndExitXml(const char *comment, const char *file,
                                        int line, const char *context) const;
  void saveStartingDocumentSnapshot();
  void setCurrentFile(const QString &fileName);
  void setCurrentPathFromFile(const QString &fileName);
  void setPixmap(const QPixmap &pixmap);
  void settingsRead();
  void settingsReadEnvironment(QSettings &settings);
  void settingsReadMainWindow(QSettings &settings);
  void settingsWrite();
  bool setupAfterLoad(const QString &fileName, const QString &temporaryMessage,
                      ImportType ImportType);
  void startRegressionTestErrorReport(const QString &regressionInputFile);
  void startRegressionTestFileCmdScript();
  void updateAfterCommandStatusBarCoords();
  void updateControls(); // Update the widgets (typically in terms of show/hide
                         // state) depending on the application state.
  void updateRecentFileList();
  void updateSettingsMainWindow();
  void updateTransformationAndItsDependencies();
  void updateViewedCurves();
  void updateViewsOfSettings(); // Private version gets active curve name from
                                // DigitizeContext
  void writeCheckpointToLogFile();

  QString m_originalFile;         // Original filename for error report
  bool m_originalFileWasImported; // True/false for imported/opened
  bool m_isDocumentExported;
  QString m_engaugeFile; // Not empty when a Document is currently loaded AND it
                         // was loaded and/or saved as an Engauge file
  QString m_currentFile; // Not empty when a Document is currently loaded

  QMenu *m_menuFile;
  QAction *m_actionImport;
  QAction *m_actionImportAdvanced;
  QAction *m_actionOpen;
  QMenu *m_menuFileOpenRecent;
  QList<QAction *> m_actionRecentFiles;
  QAction *m_actionClose;
  QAction *m_actionSave;
  QAction *m_actionSaveAs;
  QAction *m_actionExport;
  QAction *m_actionPrint;
  QAction *m_actionExit;

  QMenu *m_menuEdit;
  QAction *m_actionEditUndo;
  QAction *m_actionEditRedo;
  QAction *m_actionEditCut;
  QAction *m_actionEditCopy;
  QAction *m_actionEditPaste;
  QAction *m_actionEditDelete;
  QAction *m_actionEditPasteAsNew;
  QAction *m_actionEditPasteAsNewAdvanced;

  QMenu *m_menuDigitize;
  QActionGroup *m_groupDigitize;
  QAction *m_actionDigitizeSelect;
  QAction *m_actionDigitizeAxis;
  QAction *m_actionDigitizeCurve;
  QAction *m_actionDigitizePointMatch;
  QAction *m_actionDigitizeColorPicker;
  QAction *m_actionDigitizeSegment;

  QMenu *m_menuView;
  QAction *m_actionViewBackground;
  QAction *m_actionViewChecklistGuide;
  QAction *m_actionViewCoordSystem;
  QAction *m_actionViewDigitize;
  QAction *m_actionViewSettingsViews;
  QAction *m_actionViewToolTips;
  QMenu *m_menuViewBackground;
  QActionGroup *m_groupBackground;
  QAction *m_actionViewBackgroundNone;
  QAction *m_actionViewBackgroundOriginal;
  QAction *m_actionViewBackgroundFiltered;
  QMenu *m_menuViewCurves;
  QActionGroup *m_groupCurves;
  QAction *m_actionViewCurvesNone;
  QAction *m_actionViewCurvesSelected;
  QAction *m_actionViewCurvesAll;
  QMenu *m_menuViewStatus;
  QActionGroup *m_groupStatus;
  QAction *m_actionStatusNever;
  QAction *m_actionStatusTemporary;
  QAction *m_actionStatusAlways;
  QMenu *m_menuViewZoom;
  QAction *m_actionZoomOut;
  QAction *m_actionZoomIn;
  QActionGroup *m_groupZoom;
  QAction *m_actionZoomFill;
  QAction *m_actionZoom16To1;
  QAction *m_actionZoom8To1;
  QAction *m_actionZoom4To1;
  QAction *m_actionZoom2To1;
  QAction *m_actionZoom1To1;
  QAction *m_actionZoom1To2;
  QAction *m_actionZoom1To4;
  QAction *m_actionZoom1To8;
  QAction *m_actionZoom1To16;

  QMenu *m_menuSettings;
  QAction *m_actionSettingsAxesChecker;
  QAction *m_actionSettingsColorFilter;
  QAction *m_actionSettingsCoords;
  QAction *m_actionSettingsCurveAddRemove;
  QAction *m_actionSettingsCurveProperties;
  QAction *m_actionSettingsDigitizeCurve;
  QAction *m_actionSettingsExport;
  QAction *m_actionSettingsGeneral;
  QAction *m_actionSettingsGridRemoval;
  QAction *m_actionSettingsMainWindow;
  QAction *m_actionSettingsPointMatch;
  QAction *m_actionSettingsSegments;

  QMenu *m_menuHelp;
  QAction *m_actionHelpAbout;
  QAction *m_actionHelpChecklistGuideWizard;
  QAction *m_actionHelpHelp;
  QAction *m_actionHelpTutorial;
  QAction *m_actionHelpWhatsThis;

  QVBoxLayout *m_layout;
  GraphicsScene *m_scene;
  GraphicsView *m_view;

  StatusBar *m_statusBar;
  Transformation m_transformation;

  QComboBox *m_cmbCurve;
  QToolBar *m_toolDigitize;
  LoadImageFromUrl *m_loadImageFromUrl;

  QComboBox *m_cmbBackground;
  QToolBar *m_toolBackground;

  ViewPointStyle *m_viewPointStyle;
  ViewSegmentFilter *m_viewSegmentFilter;
  QToolBar *m_toolSettingsViews;
  ChecklistGuide *m_dockChecklistGuide;

  QComboBox *m_cmbCoordSystem;
  QPushButton *m_btnPrintAll;
  QPushButton *m_btnShowAll;
  QToolBar *m_toolCoordSystem;

  HelpWindow *m_helpWindow;
  TutorialDlg *m_tutorialDlg;

  CmdMediator *m_cmdMediator; /// Contains the Document as a private member
  CmdStackShadow *m_cmdStackShadow; /// Shadow of CmdMediator, for commands
                                    /// loaded from error report file

  // State machine for user interface states
  DigitizeStateContext *m_digitizeStateContext;

  // State machine for transformation states
  TransformationStateContext *m_transformationStateContext;

  // State machine for background image
  BackgroundStateContext *m_backgroundStateContext;

  DlgSettingsAxesChecker *m_dlgSettingsAxesChecker;
  DlgSettingsColorFilter *m_dlgSettingsColorFilter;
  DlgSettingsCoords *m_dlgSettingsCoords;
  DlgSettingsCurveAddRemove *m_dlgSettingsCurveAddRemove;
  DlgSettingsCurveProperties *m_dlgSettingsCurveProperties;
  DlgSettingsDigitizeCurve *m_dlgSettingsDigitizeCurve;
  DlgSettingsExportFormat *m_dlgSettingsExportFormat;
  DlgSettingsGeneral *m_dlgSettingsGeneral;
  DlgSettingsGridRemoval *m_dlgSettingsGridRemoval;
  DlgSettingsMainWindow *m_dlgSettingsMainWindow;
  DlgSettingsPointMatch *m_dlgSettingsPointMatch;
  DlgSettingsSegments *m_dlgSettingsSegments;

  // Crash reports
  QString m_startingDocumentSnapshot; // Serialized snapshot of document at
                                      // startup. Included in error report if
                                      // user approves
  NetworkClient *m_networkClient;

  // Main window settings
  bool m_isGnuplot; // From command line
  MainWindowModel
      m_modelMainWindow; // From settings file or DlgSettingsMainWindow

  // File names to be loaded at startup. Only one is loaded into the current
  // instance, with external instances created for the other files
  QTimer *m_timerLoadStartupFiles;
  QStringList m_loadStartupFiles;

  // Ghosts that are created for seeing all coordinate systems at once, when
  // there are multiple coordinate systems
  Ghosts *m_ghosts;

  // Timers for regression testing. Neither or one is first started by the
  // constructor for this class, but the first timeout
  // (and all succeeding timeouts) will be from after QMainWindow::exec is
  // called. Each timeout results in one command
  // from the command stack getting executed
  QTimer *m_timerRegressionErrorReport;
  FileCmdScript *m_fileCmdScript;
  QTimer *m_timerRegressionFileCmdScript;
  QString m_regressionFile;
};

#endif // MAIN_WINDOW_H
