#include "DlgModelCurveEntry.h"
#include "DlgModelCurves.h"
#include "Logger.h"
#include <QVariant>

DlgModelCurves::DlgModelCurves()
{
}

QVariant DlgModelCurves::data (const QModelIndex &index,
                               int /* role */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DlgModelCurves::data"
                               << " indexRow=" << index.row ();

  int row = index.row ();

  Q_ASSERT (row < m_modelCurveEntries.count ());

  QString value = m_modelCurveEntries.at (row);

  return QVariant (value);
}


Qt::ItemFlags DlgModelCurves::flags (const QModelIndex &index) const
{
  return flags (index) |
      Qt::ItemIsSelectable |
      Qt::ItemIsEditable;
}

bool DlgModelCurves::insertRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DlgModelCurves::insertRows"
                               << " row=" << row
                               << " count=" << count;

  Q_ASSERT (count == 1);

  beginInsertRows (parent,
                   row,
                   row + count - 1);

  QString emptyEntry;

  m_modelCurveEntries.insert (row,
                              emptyEntry);

  endInsertRows ();

  return true;
}

bool DlgModelCurves::removeRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DlgModelCurves::removeRows"
                               << " row=" << row
                               << " count=" << count;

  bool success = false;

  beginRemoveRows (parent,
                   row,
                   row + count - 1);

  endRemoveRows ();

  return success;
}

int DlgModelCurves::rowCount (const QModelIndex & /* parent */) const
{
  return m_modelCurveEntries.count ();
}

bool DlgModelCurves::setData (const QModelIndex &index,
                              const QVariant &value,
                              int /* role */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DlgModelCurves::setData"
                               << " indexRow=" << index.row ();

  bool success = false;

  int row = index.row ();
  if (row < m_modelCurveEntries.count ()) {

    DlgModelCurveEntry curveEntryNew (value.toString ());

    m_modelCurveEntries [row] = curveEntryNew.toString ();

    emit dataChanged (index,
                      index);

    success = true;
  }

  return success;
}
