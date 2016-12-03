/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "FittingModel.h"
#include "Logger.h"
#include <QTableView>

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
