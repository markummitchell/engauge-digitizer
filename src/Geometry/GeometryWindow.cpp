/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetaValuesFunctions.h"
#include "CmdMediator.h"
#include "Curve.h"
#include "CurveConnectAs.h"
#include "CurveStyle.h"
#include "EngaugeAssert.h"
#include "GeometryModel.h"
#include "GeometryWindow.h"
#include "Logger.h"
#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QTableView>
#include <QTextStream>

// Token constraints:
// (1) should fit nicely into narrow columns. This eliminates details like Forward and Backward in the distance parameter tokens
// (2) should not have any spaces. This simplifies copying and pasting into spreadsheet programs
const QString TokenName (QObject::tr ("CurveName:"));
const QString TokenFunctionArea (QObject::tr ("FunctionArea:"));
const QString TokenPolygonArea (QObject::tr ("PolygonArea:"));
const QString TokenX (QObject::tr ("X"));
const QString TokenY (QObject::tr ("Y"));
const QString TokenIndex (QObject::tr ("Index"));
const QString TokenDistanceGraph (QObject::tr ("Distance"));
const QString TokenDistancePercent (QObject::tr ("Percent"));

GeometryWindow::GeometryWindow (QWidget *parent) :
  QDockWidget (parent)
{
  setVisible (false);
  setAllowedAreas (Qt::AllDockWidgetAreas);
  setWindowTitle (tr ("Geometry Window")); // Appears in title bar when undocked
  setStatusTip (tr ("Geometry Window"));
  setWhatsThis (tr ("Geometry Window\n\n"
                    "This table displays the following geometry data for the currently selected curve:\n\n"
                    "Function area = Area under the curve if it is a function\n\n"
                    "Polygon area = Area inside the curve if it is a relation. This value is only correct "
                    "if none of the curve lines intersect each other\n\n"
                    "X = X coordinate of each point\n\n"
                    "Y = Y coordinate of each point\n\n"
                    "Index = Point number\n\n"
                    "Distance = Distance along the curve in forward or backward direction, in either graph units "
                    "or as a percentage"));

  m_model = new GeometryModel;

  m_view = new QTableView;
  m_view->setModel (m_model); // Call before setSelectionModel since this also overrides the selection model
  m_view->horizontalHeader()->hide();
  m_view->verticalHeader()->hide();
  m_view->setEditTriggers(QAbstractItemView::NoEditTriggers); // Control is read only
  connect (m_view->selectionModel(), SIGNAL (selectionChanged (const QItemSelection &, const QItemSelection &)),
           this, SLOT (slotSelectionChanged (const QItemSelection &, const QItemSelection &)));

  setWidget (m_view);

  loadStrategies();

  initializeHeader ();
}

GeometryWindow::~GeometryWindow()
{
}

void GeometryWindow::clear ()
{
  // Resize table to remove stale body data
  resizeTable (NUM_HEADER_ROWS);

  // Clear stale header data values
  for (int row = 0; row < NUM_HEADER_ROWS - 1; row++) {
    m_model->setItem (row, COLUMN_HEADER_VALUE, new QStandardItem (""));
  }
}

void GeometryWindow::closeEvent(QCloseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::closeEvent";

  emit signalGeometryWindowClosed();
}

int GeometryWindow::fold2dIndexes (int row,
                                   int col,
                                   int rowLow,
                                   int colLow,
                                   int colHigh) const
{
  return (row - rowLow) * (colHigh - colLow + 1) + (col - colLow);
}

int GeometryWindow::columnBodyPointIdentifiers ()
{
  return COLUMN_BODY_POINT_IDENTIFIERS;
}

void GeometryWindow::initializeHeader ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::initializeHeader";

  resizeTable (NUM_HEADER_ROWS);

  m_model->setItem (HEADER_ROW_NAME, COLUMN_HEADER_LABEL, new QStandardItem (TokenName));
  m_model->setItem (HEADER_ROW_FUNC_AREA, COLUMN_HEADER_LABEL, new QStandardItem (TokenFunctionArea));
  m_model->setItem (HEADER_ROW_POLY_AREA, COLUMN_HEADER_LABEL, new QStandardItem (TokenPolygonArea));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_X, new QStandardItem (TokenX));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_Y, new QStandardItem (TokenY));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_INDEX, new QStandardItem (TokenIndex));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_GRAPH_FORWARD, new QStandardItem (TokenDistanceGraph));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_PERCENT_FORWARD, new QStandardItem (TokenDistancePercent));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_GRAPH_BACKWARD, new QStandardItem (TokenDistanceGraph));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_PERCENT_BACKWARD, new QStandardItem (TokenDistancePercent));
}

void GeometryWindow::loadStrategies ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::loadStrategies";
}

void GeometryWindow::resizeTable (int rowCount)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::resizeTable";

  unselectAll();

  m_model->setRowCount (rowCount);
  m_model->setColumnCount (NUM_BODY_COLUMNS);

}

void GeometryWindow::slotPointHoverEnter (QString pointIdentifier)
{
  m_model->setCurrentPointIdentifier (pointIdentifier);
}

void GeometryWindow::slotPointHoverLeave (QString /* pointIdentifier */)
{
  m_model->setCurrentPointIdentifier ("");
}

void GeometryWindow::slotSelectionChanged (const QItemSelection & /* selected */,
                                           const QItemSelection & /* deselected */)
{
  const bool NOT_GNUPLOT = false;

  QItemSelectionModel *selectionModel = m_view->selectionModel ();
  QModelIndexList selection = selectionModel->selectedIndexes ();

  if (selection.size () > 0) {

    // Gather input. A rectangular grid that encompasses all selected indexes will be copied
    int rowLow = 0, rowHigh = 0, colLow = 0, colHigh = 0;
    bool isFirst = true;
    for (QModelIndexList::const_iterator itr = selection.begin(); itr != selection.end(); itr++) {
      QModelIndex index = *itr;
      if (isFirst || index.row ()    < rowLow ) rowLow  = index.row ();
      if (isFirst || index.row ()    > rowHigh) rowHigh = index.row ();
      if (isFirst || index.column () < colLow ) colLow  = index.column ();
      if (isFirst || index.column () > colHigh) colHigh = index.column ();
      isFirst = false;
    }

    int numRows = rowHigh - rowLow + 1;
    int numCols = colHigh - colLow + 1;

    // Put data into two dimensional rowXcolumn table is handled as a flattened vector. Table is initialized
    // with empty strings
    QVector<QString> table (numRows * numCols);

    for (int i = 0; i < selection.size (); i++) {
      QModelIndex index = selection [i];
      QVariant data = m_model->data (index);
      QString text = data.toString ();
      table [fold2dIndexes (index.row(), index.column(), rowLow, colLow, colHigh)] = text;
    }

    // Concatenate table into output string
    QString output;
    QTextStream str (&output);
    for (int row = rowLow; row <= rowHigh; row++) {
      QString delimiter;
      for (int col = colLow; col <= colHigh; col++) {
        str << delimiter << table [fold2dIndexes (row, col, rowLow, colLow, colHigh)];
        delimiter = exportDelimiterToText (m_modelExport.delimiter(),
                                           NOT_GNUPLOT);
      }
      str << "\n";
    }

    // Save to clipboard
    QApplication::clipboard ()->setText (output);
  }
}

void GeometryWindow::update (const CmdMediator &cmdMediator,
                             const MainWindowModel &modelMainWindow,
                             const QString &curveSelected,
                             const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::update";

  // Save export format
  m_modelExport = cmdMediator.document().modelExport();

  // Gather and calculate geometry data
  const Curve *curve = cmdMediator.document().curveForCurveName (curveSelected);

  ENGAUGE_CHECK_PTR (curve);

  const Points points = curve->points();

  QString funcArea, polyArea;
  QVector<QString> x, y, distanceGraphForward, distancePercentForward, distanceGraphBackward, distancePercentBackward;

  CurveStyle curveStyle = cmdMediator.document().modelCurveStyles().curveStyle (curveSelected);
  m_geometryStrategyContext.calculateGeometry (points,
                                               cmdMediator.document().modelCoords(),
                                               modelMainWindow,
                                               transformation,
                                               curveStyle.lineStyle().curveConnectAs(),
                                               funcArea,
                                               polyArea,
                                               x,
                                               y,
                                               distanceGraphForward,
                                               distancePercentForward,
                                               distanceGraphBackward,
                                               distancePercentBackward);

  // Output to table
  resizeTable (NUM_HEADER_ROWS + points.count());

  m_model->setItem (HEADER_ROW_NAME, COLUMN_HEADER_VALUE, new QStandardItem (curveSelected));
  m_model->setItem (HEADER_ROW_FUNC_AREA, COLUMN_HEADER_VALUE, new QStandardItem (funcArea));
  m_model->setItem (HEADER_ROW_POLY_AREA, COLUMN_HEADER_VALUE, new QStandardItem (polyArea));

  if (transformation.transformIsDefined()) {

    int row = NUM_HEADER_ROWS;
    int index = 0;
    for (; index < points.count(); row++, index++) {

      const Point &point = points.at (index);

      QPointF posGraph;
      transformation.transformScreenToRawGraph (point.posScreen (),
                                                posGraph);

      m_model->setItem (row, COLUMN_BODY_X, new QStandardItem (x [index]));
      m_model->setItem (row, COLUMN_BODY_Y, new QStandardItem (y [index]));
      m_model->setItem (row, COLUMN_BODY_INDEX, new QStandardItem (QString::number (index + 1)));
      m_model->setItem (row, COLUMN_BODY_DISTANCE_GRAPH_FORWARD, new QStandardItem (distanceGraphForward [index]));
      m_model->setItem (row, COLUMN_BODY_DISTANCE_PERCENT_FORWARD, new QStandardItem (distancePercentForward [index]));
      m_model->setItem (row, COLUMN_BODY_DISTANCE_GRAPH_BACKWARD, new QStandardItem (distanceGraphBackward [index]));
      m_model->setItem (row, COLUMN_BODY_DISTANCE_PERCENT_BACKWARD, new QStandardItem (distancePercentBackward [index]));
      m_model->setItem (row, COLUMN_BODY_POINT_IDENTIFIERS, new QStandardItem (point.identifier()));
    }
  }

  // Unselect everything
  unselectAll ();

  // Make sure the hidden column stays hidden
  m_view->setColumnHidden (COLUMN_BODY_POINT_IDENTIFIERS, true);
}

void GeometryWindow::unselectAll ()
{
  QItemSelectionModel *selectionModel = m_view->selectionModel ();

  selectionModel->clearSelection ();
}
