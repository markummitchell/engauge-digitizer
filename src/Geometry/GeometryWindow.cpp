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
#include "GeometryWindow.h"
#include "Logger.h"
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextStream>

GeometryWindow::GeometryWindow (QWidget *parent) :
  QDockWidget (parent)
{
  setVisible (false);
  setAllowedAreas (Qt::AllDockWidgetAreas);
  setWindowTitle (tr ("Geometry Window")); // Appears in title bar when undocked
  setStatusTip (tr ("Geometry Window"));
  setWhatsThis (tr ("Geometry Window\n\n"
                    "This table displays geometry data for the currently selected curve."));

  m_view = new QTableView;
  m_view->horizontalHeader()->hide();
  m_view->verticalHeader()->hide();
  setWidget (m_view);

  m_model = new QStandardItemModel;
  m_view->setModel (m_model);

  loadStrategies();

  initializeHeader ();
}

GeometryWindow::~GeometryWindow()
{
}

void GeometryWindow::closeEvent(QCloseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::closeEvent";

  emit signalGeometryWindowClosed();
}

void GeometryWindow::initializeHeader ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::initializeHeader";

  resizeTable (NUM_HEADER_ROWS);

  m_model->setItem (HEADER_ROW_NAME, COLUMN_HEADER_LABEL, new QStandardItem (tr ("Name:")));
  m_model->setItem (HEADER_ROW_FUNC_AREA, COLUMN_HEADER_LABEL, new QStandardItem (tr ("Function area:")));
  m_model->setItem (HEADER_ROW_POLY_AREA, COLUMN_HEADER_LABEL, new QStandardItem (tr ("Polygon area:")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_X, new QStandardItem (tr ("X")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_Y, new QStandardItem (tr ("Y")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_INDEX, new QStandardItem (tr ("Index")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_GRAPH_FORWARD, new QStandardItem (tr ("Distance")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_PERCENT_FORWARD, new QStandardItem (tr ("Percent")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_GRAPH_BACKWARD, new QStandardItem (tr ("Distance")));
  m_model->setItem (HEADER_ROW_COLUMN_NAMES, COLUMN_BODY_DISTANCE_PERCENT_BACKWARD, new QStandardItem (tr ("Percent")));
}

void GeometryWindow::loadStrategies ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::loadStrategies";
}

void GeometryWindow::resizeTable (int rowCount)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::resizeTable";

  m_model->setRowCount (rowCount);
  m_model->setColumnCount (NUM_BODY_COLUMNS);
}

void GeometryWindow::update (const CmdMediator &cmdMediator,
                             const QString &curveSelected,
                             const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::update";

  // Gather and calculate geometry data
  const Curve *curve = cmdMediator.document().curveForCurveName (curveSelected);

  ENGAUGE_CHECK_PTR (curve);

  const Points points = curve->points();

  QVector<QString> x, y, distanceGraph, distancePercent;

  CurveStyle curveStyle = cmdMediator.document().modelCurveStyles().curveStyle (curveSelected);
  m_geometryStrategyContext.calculateGeometry (points,
                                               transformation,
                                               curveStyle.lineStyle().curveConnectAs(),
                                               x,
                                               y,
                                               distanceGraph,
                                               distancePercent);

  // Output to table
  resizeTable (NUM_HEADER_ROWS + points.count());

  m_model->setItem (HEADER_ROW_NAME, COLUMN_HEADER_VALUE, new QStandardItem (curveSelected));

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
    m_model->setItem (row, COLUMN_BODY_DISTANCE_GRAPH_FORWARD, new QStandardItem (distanceGraph [index]));
    m_model->setItem (row, COLUMN_BODY_DISTANCE_PERCENT_FORWARD, new QStandardItem (distancePercent [index]));
  }
}
