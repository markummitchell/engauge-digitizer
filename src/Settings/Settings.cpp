/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Settings.h"

// Highest level
const QString SETTINGS_ENGAUGE ("Engauge");
const QString SETTINGS_DIGITIZER ("Digitizer");

// Environment group
const QString SETTINGS_GROUP_ENVIRONMENT ("Environment"); // capitalize E since this is a group string
const QString SETTINGS_CURRENT_DIRECTORY ("currentDirectory");

// MainWindow group
const QString SETTINGS_BACKGROUND_IMAGE ("backgroundImage");
const QString SETTINGS_CHECKLIST_GUIDE_DOCK_AREA ("checklistGuideDockArea");
const QString SETTINGS_CHECKLIST_GUIDE_DOCK_GEOMETRY ("checklistGuideDockGeometry");
const QString SETTINGS_CHECKLIST_GUIDE_WIZARD ("checklistGuideWizard");
const QString SETTINGS_DRAG_DROP_EXPORT ("dragDropExport");
const QString SETTINGS_FITTING_WINDOW_DOCK_AREA ("fittingWindowDockArea");
const QString SETTINGS_FITTING_WINDOW_DOCK_GEOMETRY ("fittingWindowDockGeometry");
const QString SETTINGS_GEOMETRY_WINDOW_DOCK_AREA ("geometryWIndowDockArea");
const QString SETTINGS_GEOMETRY_WINDOW_DOCK_GEOMETRY ("geometryWindowGeometry");
const QString SETTINGS_GROUP_MAIN_WINDOW ("MainWindow"); // Capitalize both M and W since this is a group string
const QString SETTINGS_HELP_POS ("helpPos");
const QString SETTINGS_HELP_SIZE ("helpSize");
const QString SETTINGS_HIGHLIGHT_OPACITY ("highlightOpacity");
const QString SETTINGS_LOCALE_COUNTRY ("country");
const QString SETTINGS_LOCALE_LANGUAGE ("language");
const QString SETTINGS_MAIN_TITLE_BAR_FORMAT ("titleBarFormat");
const QString SETTINGS_MAXIMUM_GRID_LINES ("maximumGridLines");
const QString SETTINGS_POS ("pos");
const QString SETTINGS_RECENT_FILE_LIST ("recentFileList");
const QString SETTINGS_SIGNIFICANT_DIGITS ("significantDigits");
const QString SETTINGS_SIZE ("size");
const QString SETTINGS_SMALL_DIALOGS ("smallDialogs");
const QString SETTINGS_VIEW_BACKGROUND_TOOLBAR ("viewBackgroundToolBar");
const QString SETTINGS_VIEW_COORD_SYSTEM_TOOLBAR ("viewCoordSystemToolBar");
const QString SETTINGS_VIEW_DIGITIZE_TOOLBAR ("viewDigitizeToolBar");
const QString SETTINGS_VIEW_SETTINGS_VIEWS_TOOLBAR ("viewSettingsViewsToolBar");
const QString SETTINGS_VIEW_STATUS_BAR ("viewStatusBar");
const QString SETTINGS_VIEW_TOOL_TIPS ("viewToolTips");
const QString SETTINGS_ZOOM_CONTROL ("zoomControl");
const QString SETTINGS_ZOOM_FACTOR ("zoomFactor");
const QString SETTINGS_ZOOM_FACTOR_INITIAL ("zoomFactorInitial");

// Curve styles and names group. Note that point shape is ignored for graph curves since it is, usually, unique for each curve
const QString SETTINGS_CURVE_LINE_COLOR ("lineColor");
const QString SETTINGS_CURVE_LINE_CONNECT_AS ("lineConnectAs");
const QString SETTINGS_CURVE_LINE_WIDTH ("lineWidth");
const QString SETTINGS_CURVE_NAME ("name");
const QString SETTINGS_CURVE_POINT_COLOR ("pointColor");
const QString SETTINGS_CURVE_POINT_LINE_WIDTH ("pointLineWidth");
const QString SETTINGS_CURVE_POINT_RADIUS ("pointRadius");
const QString SETTINGS_CURVE_POINT_SHAPE ("pointShape");
const QString SETTINGS_GROUP_CURVE_AXES ("CurveAxes");
const QString SETTINGS_GROUP_CURVE_GRAPH ("CurveGraph#");
const QString SETTINGS_GROUP_CURVE_GRAPH_PLACEHOLDER ("#"); // Field in SETTINGS_GROUP_CURVE_STYLE_GRAPH

// General group
const QString SETTINGS_GENERAL_CURSOR_SIZE ("cursorSize");
const QString SETTINGS_GENERAL_EXTRA_PRECISION ("extraPrecision");
const QString SETTINGS_GROUP_GENERAL ("GeneralEngauge"); // "General" group name is reserved for ungrouped settings

// Import group
const QString SETTINGS_GROUP_IMPORT ("Import");
const QString SETTINGS_IMPORT_CROPPING ("Cropping");
const QString SETTINGS_IMPORT_PDF_RESOLUTION ("PdfResolution");

// Export group
const QString SETTINGS_EXPORT_CURVE_NAMES_NOT_EXPORTED ("curveNamesNotExported");
const QString SETTINGS_EXPORT_DELIMITER ("delimiter");
const QString SETTINGS_EXPORT_DELIMITER_OVERRIDE_CSV_TSV ("overrideCsvTsv");
const QString SETTINGS_EXPORT_HEADER ("header");
const QString SETTINGS_EXPORT_LAYOUT_FUNCTIONS ("layoutFunctions");
const QString SETTINGS_EXPORT_POINTS_INTERVAL_FUNCTIONS ("pointsIntervalFunctions");
const QString SETTINGS_EXPORT_POINTS_INTERVAL_RELATIONS ("pointsIntervalRelations");
const QString SETTINGS_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS ("pointsIntervalUnitsFunctions");
const QString SETTINGS_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS ("pointsIntervalUnitsRelations");
const QString SETTINGS_EXPORT_POINTS_SELECTION_FUNCTIONS ("pointsSelectionFunctions");
const QString SETTINGS_EXPORT_POINTS_SELECTION_RELATIONS ("pointsSelectionRelations");
const QString SETTINGS_EXPORT_X_LABEL ("xLabel");
const QString SETTINGS_GROUP_EXPORT ("Export");

// Dialogs for import cropping group
const QString SETTINGS_GROUP_IMPORT_CROPPING ("ImportCropping");
const QString SETTINGS_IMPORT_CROPPING_POS ("pos");
