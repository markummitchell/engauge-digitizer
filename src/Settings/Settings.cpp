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
const QString SETTINGS_GROUP_MAIN_WINDOW ("MainWindow"); // Capitalize both M and W since this is a group string
const QString SETTINGS_HELP_POS ("helpPos");
const QString SETTINGS_HELP_SIZE ("helpSize");
const QString SETTINGS_POS ("pos");
const QString SETTINGS_RECENT_FILE_LIST ("recentFileList");
const QString SETTINGS_SIZE ("size");
const QString SETTINGS_VIEW_BACKGROUND_TOOLBAR ("viewBackgroundToolBar");
const QString SETTINGS_VIEW_DIGITIZE_TOOLBAR ("viewDigitizeToolBar");
const QString SETTINGS_VIEW_SETTINGS_VIEWS_TOOLBAR ("viewSettingsViewsToolBar");
const QString SETTINGS_VIEW_STATUS_BAR ("viewStatusBar");
const QString SETTINGS_VIEW_TOOL_TIPS ("viewToolTips");

// CurveStyle group. Note that point shape is ignored for graph curves since it is, usually, unique for each curve
const QString SETTINGS_CURVE_STYLE_LINE_COLOR ("lineColor");
const QString SETTINGS_CURVE_STYLE_LINE_CONNECT_AS ("lineConnectAs");
const QString SETTINGS_CURVE_STYLE_LINE_WIDTH ("lineWIdth");
const QString SETTINGS_CURVE_STYLE_POINT_COLOR ("pointColor");
const QString SETTINGS_CURVE_STYLE_POINT_LINE_WIDTH ("pointLineWidth");
const QString SETTINGS_CURVE_STYLE_POINT_RADIUS ("pointRadius");
const QString SETTINGS_CURVE_STYLE_POINT_SHAPE ("pointShape");
const QString SETTINGS_GROUP_CURVE_STYLE_AXES ("CurveStyleAxes");
const QString SETTINGS_GROUP_CURVE_STYLE_GRAPH ("CurveStyleGraph");
