#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QUrl>
#include "Transformation.h"

class CmdMediator;
class DigitizeStateContext;
class DlgModelCoords;
class DlgModelCurveProperties;
class DlgModelCurves;
class DlgModelExport;
class DlgModelFilter;
class DlgModelGridDisplay;
class DlgModelGridRemoval;
class DlgModelPointMatch;
class DlgModelSegments;
class DlgSettingsCoords;
class DlgSettingsCurveProperties;
class DlgSettingsCurves;
class DlgSettingsExport;
class DlgSettingsFilter;
class DlgSettingsGridDisplay;
class DlgSettingsGridRemoval;
class DlgSettingsPointMatch;
class DlgSettingsSegments;
class GraphicsScene;
class GraphicsView;
class LoadImageFromUrl;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QGraphicsPixmapItem;
class QMenu;
class QSettings;
class QToolBar;
class QVBoxLayout;
class StatusBar;

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

  /// Update the combobox that has the curve names.
  void loadCurveNamesFromCmdMediator();

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

  /// Update with new coordinate properties.
  void updateSettingsCoords(const DlgModelCoords &modelCoords);

  /// Update with new curve properties.
  void updateSettingsCurveProperties(const DlgModelCurveProperties &modelCurveProperties);

  /// Update with new curves.
  void updateSettingsCurves (const CurvesGraphs &curvesGraphs);

  /// Update with new export properties.
  void updateSettingsExport(const DlgModelExport &modelExport);

  /// Update with new filter properties.
  void updateSettingsFilter(const DlgModelFilter &modelFilter);

  /// Update with new grid display properties.
  void updateSettingsGridDisplay(const DlgModelGridDisplay &modelGridDisplay);

  /// Update with new grid removal properties.
  void updateSettingsGridRemoval(const DlgModelGridRemoval &modelGridRemoval);

  /// Update with new point match properties.
  void updateSettingsPointMatch(const DlgModelPointMatch &modelPointMatch);

  /// Update with new segments properties.
  void updateSettingsSegments(const DlgModelSegments &modelSegments);

  /// View for the QImage and QGraphicsItems, without const.
  GraphicsView &view ();

  /// View for the QImage and QGraphicsItems, without const.
  const GraphicsView &view () const;

private slots:
  void slotCanRedoChanged (bool);
  void slotCanUndoChanged (bool);
  void slotCmbCurve(int);
  void slotContextMenuEvent (QString);
  void slotDigitizeAxis ();
  void slotDigitizeCurve ();
  void slotDigitizePointMatch ();
  void slotDigitizeSegment ();
  void slotDigitizeSelect ();
  void slotEditCopy ();
  void slotEditCut ();
  void slotEditDelete ();
  void slotEditPaste ();
  void slotFileExport ();
  void slotFileExportAs ();
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
  void slotSetOverrideCursor (Qt::CursorShape);
  void slotSettingsCoords ();
  void slotSettingsCurveProperties ();
  void slotSettingsCurves ();
  void slotSettingsExport ();
  void slotSettingsFilter ();
  void slotSettingsGridDisplay ();
  void slotSettingsGridRemoval ();
  void slotSettingsPointMatch ();
  void slotSettingsSegments ();
  void slotUndoTextChanged (const QString &);
  void slotViewDigitize ();
  void slotViewGroupDocumentImage(QAction*);
  void slotViewGroupDocumentPoints(QAction*);
  void slotViewGroupStatus(QAction*);
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
  void createLoadImageFromUrl ();
  void createMenus();
  void createScene ();
  void createSettingsDialogs ();
  void createStateContext();
  void createStatusBar();
  void createToolBars();
  void fileImport (const QString &fileName);
  void loadFile (const QString &fileName);
  void loadImage (const QString &fileName,
                  const QImage &image);
  bool maybeSave();
  void removePixmap();
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
  void updateViewedPoints ();

  QString m_curfile;

  QMenu *m_menuFile;
  QAction *m_actionImport;
  QAction *m_actionOpen;
  QMenu *m_menuFileOpenRecent;
  QAction *m_actionSave;
  QAction *m_actionSaveAs;
  QAction *m_actionExport;
  QAction *m_actionExportAs;
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
  QAction *m_actionDigitizeSegment;

  QMenu *m_menuView;
  QAction *m_actionViewDigitize;
  QMenu *m_menuViewDocument;
  QActionGroup *m_groupDocumentImage;
  QAction *m_actionViewDocumentImageNone;
  QAction *m_actionViewDocumentImageOriginal;
  QAction *m_actionViewDocumentImageFiltered;
  QActionGroup *m_groupDocumentPoints;
  QAction *m_actionViewDocumentPointsNone;
  QAction *m_actionViewDocumentPointsCurve;
  QAction *m_actionViewDocumentPointsAll;
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
  QAction *m_actionSettingsCoords;
  QAction *m_actionSettingsCurveProperties;
  QAction *m_actionSettingsCurves;
  QAction *m_actionSettingsExport;
  QAction *m_actionSettingsFilter;
  QAction *m_actionSettingsGridDisplay;
  QAction *m_actionSettingsGridRemoval;
  QAction *m_actionSettingsPointMatch;
  QAction *m_actionSettingsSegments;

  QMenu *m_menuHelp;
  QAction *m_actionAbout;
  QAction *m_actionWhatsThis;

  QVBoxLayout *m_layout;
  GraphicsScene *m_scene;
  GraphicsView *m_view;
  QGraphicsPixmapItem *m_image;

  StatusBar *m_statusBar;
  Transformation m_transformation;

  QComboBox *m_cmbCurve;
  QToolBar *m_toolDigitize;
  LoadImageFromUrl *m_loadImageFromUrl;

  CmdMediator *m_cmdMediator; /// Contains the Document as a private member
  DigitizeStateContext *m_digitizeStateContext;

  DlgSettingsCoords *m_dlgSettingsCoords;
  DlgSettingsCurveProperties *m_dlgSettingsCurveProperties;
  DlgSettingsCurves *m_dlgSettingsCurves;
  DlgSettingsExport *m_dlgSettingsExport;
  DlgSettingsFilter *m_dlgSettingsFilter;
  DlgSettingsGridDisplay *m_dlgSettingsGridDisplay;
  DlgSettingsGridRemoval *m_dlgSettingsGridRemoval;
  DlgSettingsPointMatch *m_dlgSettingsPointMatch;
  DlgSettingsSegments *m_dlgSettingsSegments;
};

#endif // MAIN_WINDOW_H
