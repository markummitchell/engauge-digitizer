/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "FittingModel.h"
#include "FittingWindow.h"
#include "Logger.h"
#include <QMimeData>
#include <QTextStream>

const int COLUMN_COEFFICIENTS = 0;
const int COLUMN_POLYNOMIAL_TERMS = 1;

FittingModel::FittingModel ()
{
}

FittingModel::~FittingModel()
{
}

QVariant FittingModel::data(const QModelIndex &index, int role) const
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "FittingModel::data"
//                               << " index=(row=" << index.row() << ",col=" << index.column() << ",role=" << role << ")="
//                               << " rows=" << rowCount()
//                               << " cols=" << columnCount();

  if (role == Qt::BackgroundRole &&
      index.row() == rowCount() - 1 &&
      index.column() == COLUMN_POLYNOMIAL_TERMS) {

    // Bottom right cell would be empty so we gray it out
    return QVariant::fromValue (QColor (Qt::lightGray));
  }

  // Standard behavior
  return QStandardItemModel::data (index, role);
}

QMimeData *FittingModel::mimeData(const QModelIndexList &indexes) const
{
  if (indexes.isEmpty ()) {
    return Q_NULLPTR;
  }

  QMimeData *data = new QMimeData ();
  QString html;
  QTextStream str (&html);

  // Selection mode was set to ContiguousMode so we know the selected cell region is rectangular
  str << "<table>";

  int rowLast = -1;

  QModelIndexList::const_iterator itr;
  for (itr = indexes.begin (); itr != indexes.end (); itr++) {

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

  data->setHtml (html);

  return data;
}
