#include "DlgModelCurveEntry.h"
#include "DlgModelCurves.h"
#include "Logger.h"
#include <QVariant>

QHash<int, QString> DlgModelCurves::m_rolesAsStrings;

DlgModelCurves::DlgModelCurves()
{
}

QVariant DlgModelCurves::data (const QModelIndex &index,
                               int role) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DlgModelCurves::data"
                               << " indexRow=" << index.row ()
                               << " role=" << roleAsString (role).toLatin1 ().data ();

  int row = index.row ();
  if (row < 0 || row >= m_modelCurveEntries.count ()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  QString value = m_modelCurveEntries.at (row);
  return value;
}


Qt::ItemFlags DlgModelCurves::flags (const QModelIndex &index) const
{
  return QAbstractListModel::flags (index) |
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

QString DlgModelCurves::roleAsString (int role) const
{
  if (m_rolesAsStrings.count () == 0) {
    m_rolesAsStrings [Qt::AccessibleDescriptionRole] = "AccessibleDescriptionRole";
    m_rolesAsStrings [Qt::AccessibleTextRole] = "AccessibleTextRole";
    m_rolesAsStrings [Qt::BackgroundRole] = "BackgroundRole";
    m_rolesAsStrings [Qt::BackgroundColorRole] = "BackgroundColorRole";
    m_rolesAsStrings [Qt::CheckStateRole] = "CheckStateRole";
    m_rolesAsStrings [Qt::DecorationRole] = "DecorationRole";
    m_rolesAsStrings [Qt::DisplayRole] = "DisplayRole";
    m_rolesAsStrings [Qt::EditRole] = "EditRole";
    m_rolesAsStrings [Qt::FontRole] = "FontRole";
    m_rolesAsStrings [Qt::ForegroundRole] = "ForegroundRole";
    m_rolesAsStrings [Qt::InitialSortOrderRole] = "InitialSortOrderRole";
    m_rolesAsStrings [Qt::SizeHintRole] = "SizeHintRole";
    m_rolesAsStrings [Qt::StatusTipRole] = "StatusTipRole";
    m_rolesAsStrings [Qt::TextAlignmentRole] = "TextAlignmentRole";
    m_rolesAsStrings [Qt::TextColorRole] = "TextColorRole";
    m_rolesAsStrings [Qt::ToolTipRole] = "ToolTipRole";
    m_rolesAsStrings [Qt::UserRole] = "UserRole";
    m_rolesAsStrings [Qt::WhatsThisRole] = "WhatsThisRole";
  }

  Q_ASSERT (m_rolesAsStrings.contains (role));

  return m_rolesAsStrings [role];
}

int DlgModelCurves::rowCount (const QModelIndex & /* parent */) const
{
  int count = m_modelCurveEntries.count ();

  LOG4CPP_DEBUG_S ((*mainCat)) << "DlgModelCurves::rowCount count=" << count;

  return count;
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
