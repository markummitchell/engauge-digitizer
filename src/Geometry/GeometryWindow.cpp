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
#include "MainWindow.h"
#include <QApplication>
#include <QClipboard>
#include <QItemSelectionModel>
#include <QTextStream>
#include "WindowTable.h"

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

GeometryWindow::GeometryWindow (MainWindow *mainWindow) :
  WindowAbstractBase (mainWindow)
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
                    "or as a percentage\n\n"
                    "If drag-and-drop is disabled, a rectangular set of cells may be selected by clicking and dragging. Otherwise, if "
                    "drag-and-drop is enabled, a rectangular set of cells may be selected using Click then Shift+Click, since click and drag "
                    "starts the dragging operation. Drag-and-drop mode is set in the Main Window settings"));

  createWidgets (mainWindow);
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

int GeometryWindow::columnBodyPointIdentifiers ()
{
  return COLUMN_BODY_POINT_IDENTIFIERS;
}

void GeometryWindow::createWidgets (MainWindow *mainWindow)
{
  m_model = new GeometryModel;

  m_view = new WindowTable (*m_model);
  connect (m_view, SIGNAL (signalTableStatusChange ()),
           mainWindow, SLOT (slotTableStatusChange ()));

  setWidget (m_view);
}

void GeometryWindow::doCopy ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::doCopy";

  QString text = m_model->selectionAsText (m_modelExport.delimiter());

  if (!text.isEmpty ()) {

    // Save to clipboard
    QApplication::clipboard ()->setText (text);

  }
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

void GeometryWindow::unselectAll ()
{
  QItemSelectionModel *selectionModel = m_view->selectionModel ();

  selectionModel->clearSelection ();
}

void GeometryWindow::update (const CmdMediator &cmdMediator,
                             const MainWindowModel &modelMainWindow,
                             const QString &curveSelected,
                             const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::update";

  // Save inputs
  m_modelExport = cmdMediator.document().modelExport();
  m_model->setDelimiter (m_modelExport.delimiter());
  m_view->setDragEnabled (modelMainWindow.dragDropExport());

  // Gather and calculate geometry data
  const Curve *curve = cmdMediator.document().curveForCurveName (curveSelected);

  ENGAUGE_CHECK_PTR (curve);

  const Points points = curve->points();

  QString funcArea, polyArea;
  QVector<QString> x, y, distanceGraphForward, distancePercentForward, distanceGraphBackward, distancePercentBackward;

  CurveStyle curveStyle = cmdMediator.document().modelCurveStyles().curveStyle (curveSelected);
  m_geometryStrategyContext.calculateGeometry (points,
                                               cmdMediator.document().modelCoords(),
                                               cmdMediator.document().modelGeneral(),
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

QTableView *GeometryWindow::view () const
{
  return dynamic_cast<QTableView*> (m_view);
}
