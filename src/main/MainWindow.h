#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QCursor>
#include <QMainWindow>
#include <QUrl>
#include "Transformation.h"

class CmdMediator;
class DigitizeStateContext;
class DlgSettingsAxesChecker;
class DlgSettingsCoords;
class DlgSettingsCurveProperties;
class DlgSettingsCurves;
class DlgSettingsExport;
class DlgSettingsFilter;
class DlgSettingsGridRemoval;
class DlgSettingsPointMatch;
class DlgSettingsSegments;
class DocumentModelAxesChecker;
class DocumentModelCoords;
class DocumentModelCurveProperties;
class DocumentModelCurves;
class DocumentModelExport;
class DocumentModelFilter;
class DocumentModelGridRemoval;
class DocumentModelPointMatch;
class DocumentModelSegments;
class GraphicsScene;
class GraphicsView;
class LoadImageFromUrl;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QGraphicsLineItem;
class QGraphicsPixmapItem;
class QMenu;
class QSettings;
class QToolBar;
class QVBoxLayout;
class StatusBar;
class TransformationStateContext;
class ViewSegmentFilter;

/// Main window consisting of menu, graphics scene, status bar and optional toolbars as a Single Document Interface
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /// Single constructor.
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  /// Accessor for commands to process the Document.
  CmdMediator &cmdMediator();

  /// Intercept resize event so graphics scene can be appropriately resized when in Fill mode.
  void resizeEvent (QResizeEvent *event);

  /// Scene container for the QImage and QGraphicsItems.
  GraphicsScene &scene();

  /// Curve name that is currently selected in m_comboCurve.
  QString selectedCurrentCurve () const;

  /// Return true if all three axis points have been defined.
  bool transformIsDefined() const;

  /// See GraphicsScene::updateAfterCommand.
  void updateAfterCommand();

  /// Call MainWindow::updateControls (which is private) after the very specific case - a mouse press/release.
  void updateAfterMouseRelease();

  /// Update with new axes indicator properties.
  void updateSettingsAxesChecker(const DocumentModelAxesChecker &modelAxesChecker);

  /// Update with new coordinate properties.
  void updateSettingsCoords(const DocumentModelCoords &modelCoords);

  /// Update with new curve properties.
  void updateSettingsCurveProperties(const DocumentModelCurveProperties &modelCurveProperties);

  /// Update with new curves.
  void updateSettingsCurves (const CurvesGraphs &curvesGraphs);

  /// Update with new export properties.
  void updateSettingsExport(const DocumentModelExport &modelExport);

  /// Update with new filter properties.
  void updateSettingsFilter(const DocumentModelFilter &modelFilter);

  /// Update with new grid removal properties.
  void updateSettingsGridRemoval(const DocumentModelGridRemoval &modelGridRemoval);

  /// Update with new point match properties.
  void updateSettingsPointMatch(const DocumentModelPointMatch &modelPointMatch);

  /// Update with new segments properties.
  void updateSettingsSegments(const DocumentModelSegments &modelSegments);

  /// View for the QImage and QGraphicsItems, without const.
  GraphicsView &view ();

  /// View for the QImage and QGraphicsItems, without const.
  const GraphicsView &view () const;

private slots:
  void slotCanRedoChanged (bool);
  void slotCanUndoChanged (bool);
  void slotCmbBackground(int);
  void slotCmbCurve(int);  
  void slotContextMenuEvent (QString);
  void slotDigitizeAxis ();
  void slotDigitizeColorPicker ();
  void slotDigitizeCurve ();
  void slotDigitizePointMatch ();
  void slotDigitizeSegment ();
  void slotDigitizeSelect ();
  void slotEditCopy ();
  void slotEditCut ();
  void slotEditDelete ();
  void slotEditPaste ();
  void slotFileExport ();
  void slotFileImport();
  void slotFileImportDraggedImage(QImage);
  void slotFileImportDraggedImageUrl(QUrl);
  void slotFileImportImage(QString, QImage);
  void slotFileOpen();
  void slotFilePrint();
  bool slotFileSave(); /// Slot method that is sometimes called directly with return value expected
  bool slotFileSaveAs(); /// Slot method that is sometimes called directly with return value expected
  void slotHelpAbout();
  void slotKeyPress (Qt::Key);
  void slotLeave ();
  void slotMouseMove (QPointF);
  void slotMousePress (QPointF);
  void slotMouseRelease (QPointF);
  void slotRedoTextChanged (const QString &);
  void slotSetOverrideCursor (QCursor);
  void slotSettingsAxesChecker ();
  void slotSettingsCoords ();
  void slotSettingsCurveProperties ();
  void slotSettingsCurves ();
  void slotSettingsExport ();
  void slotSettingsFilter ();
  void slotSettingsGridRemoval ();
  void slotSettingsPointMatch ();
  void slotSettingsSegments ();
  void slotUndoTextChanged (const QString &);
  void slotViewGroupBackground(QAction*);
  void slotViewGroupPoints(QAction*);
  void slotViewGroupStatus(QAction*);
  void slotViewToolBarBackground ();
  void slotViewToolBarDigitize ();
  void slotViewToolBarViews ();
  void slotViewZoom16To1 ();
  void slotViewZoom8To1 ();
  void slotViewZoom4To1 ();
  void slotViewZoom2To1 ();
  void slotViewZoom1To1 ();
  void slotViewZoom1To2 ();
  void slotViewZoom1To4 ();
  void slotViewZoom1To8 ();
  void slotViewZoom1To16 ();
  void slotViewZoom (int);
  void slotViewZoomFill ();
  void slotViewZoomIn ();
  void slotViewZoomOut ();

signals:
  /// Send zoom selection, picked from menu or keystroke, to StatusBar.
  void signalZoom(int);

private:
  virtual void closeEvent(QCloseEvent *event);
  void createActions();
  void createActionsDigitize ();
  void createActionsEdit ();
  void createActionsFile ();
  void createActionsHelp ();
  void createActionsSettings ();
  void createActionsView ();
  void createCentralWidget ();
  void createIcons();
  void createLoadImageFromUrl ();
  void createMenus();
  void createScene ();
  void createSettingsDialogs ();
  void createStateContextDigitize();
  void createStateContextTransformation();
  void createStatusBar();
  void createToolBars();
  void fileImport (const QString &fileName);
  void loadCurveListFromCmdMediator(); /// Update the combobox that has the curve names.
  void loadFile (const QString &fileName);
  void loadImage (const QString &fileName,
                  const QImage &image);
  bool maybeSave();
  void removePixmaps();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  void setCurrentPathFromFile (const QString &fileName);
  void setPixmap (const QPixmap &pixmap);
  void settingsRead ();
  void settingsReadEnvironment (QSettings &settings);
  void settingsReadMainWindow (QSettings &settings);
  void settingsWrite ();
  void updateAfterCommandStatusBarCoords ();
  void updateControls (); // Update the widgets (typically in terms of show/hide state) depending on the application state.
  void updateImages (const QPixmap &pixmap);
  void updateViewedBackground();
  void updateViewedPoints ();

  QString m_engaugeFile;
  QString m_currentFile;

  QMenu *m_menuFile;
  QAction *m_actionImport;
  QAction *m_actionOpen;
  QMenu *m_menuFileOpenRecent;
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
  QAction *m_actionViewDigitize;
  QAction *m_actionViewViews;
  QMenu *m_menuViewBackground;
  QActionGroup *m_groupBackground;
  QAction *m_actionViewBackgroundNone;
  QAction *m_actionViewBackgroundOriginal;
  QAction *m_actionViewBackgroundFiltered;
  QMenu *m_menuViewPoints;
  QActionGroup *m_groupPoints;
  QAction *m_actionViewPointsNone;
  QAction *m_actionViewPointsCurve;
  QAction *m_actionViewPointsAll;
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
  QAction *m_actionSettingsCoords;
  QAction *m_actionSettingsCurveProperties;
  QAction *m_actionSettingsCurves;
  QAction *m_actionSettingsExport;
  QAction *m_actionSettingsFilter;
  QAction *m_actionSettingsGridRemoval;
  QAction *m_actionSettingsPointMatch;
  QAction *m_actionSettingsSegments;

  QMenu *m_menuHelp;
  QAction *m_actionAbout;
  QAction *m_actionWhatsThis;

  QVBoxLayout *m_layout;
  GraphicsScene *m_scene;
  GraphicsView *m_view;

  QGraphicsPixmapItem *m_imageNone; // White background with boundary indicating the edge of the original image
  QGraphicsPixmapItem *m_imageUnfiltered; // Original unfiltered image
  QGraphicsPixmapItem *m_imageFiltered; // Image produced by Filter class

  StatusBar *m_statusBar;
  Transformation m_transformation;

  QComboBox *m_cmbCurve;
  QToolBar *m_toolDigitize;
  LoadImageFromUrl *m_loadImageFromUrl;

  QComboBox *m_cmbBackground;
  QToolBar *m_toolBackground;

  ViewSegmentFilter *m_viewSegmentFilter;
  QToolBar *m_toolViews;

  CmdMediator *m_cmdMediator; /// Contains the Document as a private member

  // State machine for user interface states
  DigitizeStateContext *m_digitizeStateContext;

  // State machine for transformation states
  TransformationStateContext *m_transformationStateContext;

  DlgSettingsAxesChecker *m_dlgSettingsAxesChecker;
  DlgSettingsCoords *m_dlgSettingsCoords;
  DlgSettingsCurveProperties *m_dlgSettingsCurveProperties;
  DlgSettingsCurves *m_dlgSettingsCurves;
  DlgSettingsExport *m_dlgSettingsExport;
  DlgSettingsFilter *m_dlgSettingsFilter;
  DlgSettingsGridRemoval *m_dlgSettingsGridRemoval;
  DlgSettingsPointMatch *m_dlgSettingsPointMatch;
  DlgSettingsSegments *m_dlgSettingsSegments;
};

#endif // MAIN_WINDOW_H
