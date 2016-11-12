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
#include "WindowTableBase.h"

WindowModelBase::WindowModelBase () :
  m_view (0)
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
    return Q_NULLPTR;
  }

  QMimeData *data = new QMimeData ();

  data->setHtml (selectionAsHtml ());
  data->setText (selectionAsText (m_delimiter));

  return data;
}

QString WindowModelBase::selectionAsHtml () const
{
  QString html;
  QTextStream str (&html);

  ENGAUGE_CHECK_PTR (m_view);

  QItemSelectionModel *selectionModel = m_view->selectionModel ();
  QModelIndexList selection = selectionModel->selectedIndexes ();

  str << "<table>";

  int rowLast = -1;

  QModelIndexList::const_iterator itr;
  for (itr = selection.begin (); itr != selection.end (); itr++) {

    const QModelIndex &index = *itr;

    if (index.row() != rowLast) {
      if (rowLast >= 0) {
        str << "</tr>"; // Close previous row
      }
      str << "<tr>"; // Start new row
      rowLast = index.row();
    }

    QString cellText = QString ("%1%2%3")
        .arg ("<td>")
        .arg (this->data (index, Qt::DisplayRole).toString ())
        .arg ("</td>");

    str << cellText;
  }
  str << "</tr>";

  str << "</table>";

  return html;
}

QString WindowModelBase::selectionAsText (ExportDelimiter delimiter) const
{
  const bool NOT_GNUPLOT = false;

  QString text;

  ENGAUGE_CHECK_PTR (m_view);

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
      QVariant d = data (index);
      QString text = d.toString ();
      table [fold2dIndexes (index.row(), index.column(), rowLow, colLow, colHigh)] = text;
    }

    // Concatenate table into output string
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
  }

  return text;
}

void WindowModelBase::setDelimiter (ExportDelimiter delimiter)
{
  m_delimiter = delimiter;
}

void WindowModelBase::setView (WindowTableBase &view)
{
  m_view = &view;
}
