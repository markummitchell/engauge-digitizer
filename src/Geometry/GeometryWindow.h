/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_WINDOW_H
#define GEOMETRY_WINDOW_H

#include "DocumentModelExportFormat.h"
#include "GeometryStrategyContext.h"
#include "WindowAbstractBase.h"

class CmdMediator;
class Curve;
class GeometryModel;
class MainWindow;
class MainWindowModel;
class QItemSelection;
class QString;
class QTableView;
class Transformation;

/// Window that displays the geometry information, as a table, for the current curve
///
/// Column COLUMN_BODY_POINT_IDENTIFIERS is hidden. It contains the point identifiers so we can find
/// the line associated with a point, and then highlight that line
class GeometryWindow : public WindowAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  GeometryWindow (MainWindow *mainWindow);
  virtual ~GeometryWindow ();

  virtual void clear ();
  virtual void closeEvent(QCloseEvent *event);

  /// Hidden column that has the point identifiers
  static int columnBodyPointIdentifiers ();

  virtual void doCopy ();
  virtual void update (const CmdMediator &cmdMediator,
                       const MainWindowModel &modelMainWindow,
                       const QString &curveSelected,
                       const Transformation &transformation);
  virtual QTableView *view () const;

public slots:

  /// Highlight the row for the specified point
  void slotPointHoverEnter (QString);

  /// Unhighlight the row for the specified point
  void slotPointHoverLeave (QString);

signals:

  /// Signal that this QDockWidget was just closed
  void signalGeometryWindowClosed();

private:
  GeometryWindow();

  void createWidgets (MainWindow *mainWindow);
  void initializeHeader();
  void loadStrategies ();
  void resizeTable (int rowCount);
  void unselectAll (); // Unselect all cells. This cleans up nicely when Document is closed

  enum ColumnsHeader {
    COLUMN_HEADER_LABEL,
    COLUMN_HEADER_VALUE,
    NUM_HEADER_COLUMNS
  };

  enum ColumnsBody {
    COLUMN_BODY_X,
    COLUMN_BODY_Y,
    COLUMN_BODY_INDEX,
    COLUMN_BODY_DISTANCE_GRAPH_FORWARD,
    COLUMN_BODY_DISTANCE_PERCENT_FORWARD,
    COLUMN_BODY_DISTANCE_GRAPH_BACKWARD,
    COLUMN_BODY_DISTANCE_PERCENT_BACKWARD,
    COLUMN_BODY_POINT_IDENTIFIERS,
    NUM_BODY_COLUMNS
  };

  enum HeaderRows {
    HEADER_ROW_NAME,
    HEADER_ROW_FUNC_AREA,
    HEADER_ROW_POLY_AREA,
    HEADER_ROW_COLUMN_NAMES,
    NUM_HEADER_ROWS
  };

  QTableView *m_view;
  GeometryModel *m_model;

  GeometryStrategyContext m_geometryStrategyContext;

  // Export format is updated after every CmdAbstractBase gets redone/undone
  DocumentModelExportFormat m_modelExport;
};

#endif // GEOMETRY_WINDOW_H
