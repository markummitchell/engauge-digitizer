/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include <QMimeData>
#include <QTextStream>
#include "WindowModelAbstract.h"

WindowModelAbstract::WindowModelAbstract ()
{
}

WindowModelAbstract::~WindowModelAbstract()
{
}

QMimeData *WindowModelAbstract::mimeData(const QModelIndexList &indexes) const
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
