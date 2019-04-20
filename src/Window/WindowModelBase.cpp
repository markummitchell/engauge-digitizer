/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Logger.h"
#include <QItemSelectionModel>
#include <QMimeData>
#include <QTableView>
#include <QTextStream>
#include "WindowModelBase.h"
#include "WindowTable.h"

WindowModelBase::WindowModelBase () :
  m_view (nullptr)
{
}

WindowModelBase::~WindowModelBase()
{
}

int WindowModelBase::fold2dIndexes (int row,
                                    int col,
                                    int rowLow,
                                    int colLow,
                                    int colHigh) const
{
  return (row - rowLow) * (colHigh - colLow + 1) + (col - colLow);
}

QMimeData *WindowModelBase::mimeData(const QModelIndexList &indexes) const
{
  if (indexes.isEmpty ()) {
    return nullptr;
  }

  QMimeData *data = new QMimeData ();

  data->setHtml (selectionAsHtml ());
  data->setText (selectionAsText (m_delimiter));

  return data;
}

QString WindowModelBase::selectionAsHtml () const
{
  ENGAUGE_CHECK_PTR (m_view);

  int rowLow, colLow, rowHigh, colHigh;
  QVector<QString> table;

  // Get raw data as a rectangular table. Size may be zero
  selectionAsTable (rowLow,
                    colLow,
                    rowHigh,
                    colHigh,
                    table);

  // Concatenate table into output string
  QString html;
  QTextStream str (&html);

  str << "<table>";
  for (int row = rowLow; row <= rowHigh; row++) {
    str << "<tr>";
    for (int col = colLow; col <= colHigh; col++) {
      str << "<td>" << table [fold2dIndexes (row, col, rowLow, colLow, colHigh)] << "</td>";
    }
    str << "<tr>\n";
  }
  str << "</table>";

  return html;
}

void WindowModelBase::selectionAsTable (int &rowLow,
                                        int &colLow,
                                        int &rowHigh,
                                        int &colHigh,
                                        QVector<QString> &table) const
{
  // This algorithm supports any arbitrary set of selected cells. Specifically, the cells do not need
  // to be in a rectangular pattern. A rectangular grid that encompasses all selected cells will be created

  QItemSelectionModel *selectionModel = m_view->selectionModel ();
  QModelIndexList selection = selectionModel->selectedIndexes ();

  if (selection.size () > 0) {

    // Gather input. Initialization of row/col limits is needed only to keep some compilers happy
    rowLow = 0;
    colLow = 0;
    rowHigh = 0;
    colHigh = 0;
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
    table.resize (numRows * numCols);

    for (int i = 0; i < selection.size (); i++) {
      QModelIndex index = selection [i];
      QVariant d = data (index);
      QString text = d.toString ();
      table [fold2dIndexes (index.row(), index.column(), rowLow, colLow, colHigh)] = text;
    }
  } else {

    // Table has zero size
    rowLow = 0;
    colLow = 0;
    rowHigh = -1;
    colHigh = -1;

  }
}

QString WindowModelBase::selectionAsText (ExportDelimiter delimiter) const
{
  const bool NOT_GNUPLOT = false;

  ENGAUGE_CHECK_PTR (m_view);

  int rowLow, colLow, rowHigh, colHigh;
  QVector<QString> table;

  // Get raw data as a rectangular table. Size may be zero
  selectionAsTable (rowLow,
                    colLow,
                    rowHigh,
                    colHigh,
                    table);

  // Concatenate table into output string
  QString text;
  QTextStream str (&text);
  for (int row = rowLow; row <= rowHigh; row++) {
    QString delimiterStr;
    for (int col = colLow; col <= colHigh; col++) {
      str << delimiterStr << table [fold2dIndexes (row, col, rowLow, colLow, colHigh)];
      delimiterStr = exportDelimiterToText (delimiter,
                                            NOT_GNUPLOT);
    }
    str << "\n";
  }

  return text;
}

void WindowModelBase::setDelimiter (ExportDelimiter delimiter)
{
  m_delimiter = delimiter;
}

void WindowModelBase::setView (WindowTable &view)
{
  m_view = &view;
}
