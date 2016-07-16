/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetaValuesFunctions.h"
#include "CmdMediator.h"
#include "Curve.h"
#include "EngaugeAssert.h"
#include "ExportDelimiter.h"
#include "ExportToFile.h"
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

void GeometryWindow::resizeTable (int rowCount)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::resizeTable";

  m_model->setRowCount (rowCount);
  m_model->setColumnCount (NUM_BODY_COLUMNS);
}

void GeometryWindow::update (const CmdMediator &cmdMediator,
                             const QString &curveSelected,
                             const MainWindowModel &modelMainWindow,
                             const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GeometryWindow::update";

  ENGAUGE_CHECK_PTR (m_model);

  const bool NOT_GNUPLOT = false;
  const int ROW_COUNT_ADJUSTMENT_FOR_SKIPPING_HEADER = 1;

  // Override the export class to select just the desired curve
  DocumentModelExportFormat modelExportOverride (cmdMediator.document().modelExport());
  QStringList curveNamesNotExported = cmdMediator.document().curvesGraphsNames(); // List of all curves
  curveNamesNotExported.removeAll (curveSelected); // Remove all curves except the selected curve
  modelExportOverride.setCurveNamesNotExported (curveNamesNotExported);

  // Use ExportToFile to get the coordinates so we are not replicating any processing or formatting (=code) that
  // is already in that class or its helpers
  QString text;
  QTextStream str (&text);
  ExportToFile exportToFile;
  exportToFile.exportToFile (modelExportOverride,
                             cmdMediator.document(),
                             modelMainWindow,
                             transformation,
                             str);

  // The output is a text string that has to be parsed line by line
  QStringList lines = text.trimmed().split("\n");
  QString delimiter = exportDelimiterToText (cmdMediator.document().modelExport().delimiter(),
                                             NOT_GNUPLOT);

  resizeTable (NUM_HEADER_ROWS + lines.count() - ROW_COUNT_ADJUSTMENT_FOR_SKIPPING_HEADER);

  m_model->setItem (HEADER_ROW_NAME, COLUMN_HEADER_VALUE, new QStandardItem (curveSelected));

  int row = NUM_HEADER_ROWS;
  int indexIn = ROW_COUNT_ADJUSTMENT_FOR_SKIPPING_HEADER;
  int indexOut = 1;
  for (; indexIn < lines.count(); row++, indexIn++, indexOut++) {
    QString line = lines.at (indexIn);
    QStringList fields = line.split (delimiter);

    if (fields.count() > 0) {
      m_model->setItem (row, COLUMN_BODY_X, new QStandardItem (fields [0]));
      if (fields.count() > 1) {
        m_model->setItem (row, COLUMN_BODY_Y, new QStandardItem (fields [1]));
      }
    }

    m_model->setItem (row, COLUMN_BODY_INDEX, new QStandardItem (QString::number (indexOut)));
  }
}
