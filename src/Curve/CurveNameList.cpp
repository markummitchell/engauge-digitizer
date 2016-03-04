/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveNameListEntry.h"
#include "CurveNameList.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "QtToString.h"
#include <QVariant>
#include <QXmlStreamWriter>

CurveNameList::CurveNameList()
{
}

int CurveNameList::columnCount (const QModelIndex & /* parent */) const
{
  return 3;
}

bool CurveNameList::containsCurveNameCurrent (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::containsCurveNameCurrent"
                              << " entryCount=" << m_modelCurvesEntries.count();

  // Search for curve with matching name
  QStringList::const_iterator itr;
  for (itr = m_modelCurvesEntries.begin (); itr != m_modelCurvesEntries.end (); itr++) {

    CurveNameListEntry curvesEntry (*itr);
    if (curveName == curvesEntry.curveNameCurrent()) {

      return true;
    }
  }

  return false;
}

bool CurveNameList::curveNameIsAcceptable (const QString &curveNameNew,
                                           int row) const
{
  // First test is to verify curve name is not empty
  bool success = (!curveNameNew.isEmpty ());

  if (success) {

    // First test was passed. Second test is to check for duplication

    for (int row1 = 0; row1 < m_modelCurvesEntries.count(); row1++) {

      // Use table entry except for the one row that gets overridden
      CurveNameListEntry curvesEntry1 (m_modelCurvesEntries [row1]); // Retrieve entry
      QString curveNameCurrent1 = (row1 == row ?
                                   curveNameNew :
                                   curvesEntry1.curveNameCurrent());

      for (int row2 = row1 + 1; row2 < m_modelCurvesEntries.count(); row2++) {

        // Use table entry except for the one row that gets overridden
        CurveNameListEntry curvesEntry2 (m_modelCurvesEntries [row2]); // Retrieve entry
        QString curveNameCurrent2 = (row2 == row ?
                                     curveNameNew :
                                     curvesEntry2.curveNameCurrent());

        if (curveNameCurrent1 == curveNameCurrent2) {

          // Duplicate!
          success = false;
          break;
        }
      }
    }
  }

  return success;
}

QVariant CurveNameList::data (const QModelIndex &index,
                               int role) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::data"
                               << " isRoot=" << (index.isValid () ? "no" : "yes")
                               << " role=" << roleAsString (role).toLatin1 ().data ();

  if (!index.isValid ()) {
    // Root item
    return QVariant ();
  }

  int row = index.row ();
  if (row < 0 || row >= m_modelCurvesEntries.count ()) {
    return QVariant();
  }

  if ((role != Qt::DisplayRole) &&
      (role != Qt::EditRole)) {
    return QVariant();
  }

  CurveNameListEntry curvesEntry (m_modelCurvesEntries.at (row));

  if (index.column () == 0) {
    return curvesEntry.curveNameCurrent();
  } else if (index.column () == 1) {
    return curvesEntry.curveNameOriginal();
  } else if (index.column () == 2) {
    return curvesEntry.numPoints ();
  } else {
    ENGAUGE_ASSERT (false);
    return curvesEntry.curveNameOriginal(); // Default if asserts are disabled
 }
}


Qt::ItemFlags CurveNameList::flags (const QModelIndex &index) const
{
  // Only the root item can accept drops, or else dragging one entry onto another
  // would result in the drop target getting overwritten

  if (index.isValid ()) {

    // Not root item
    return QAbstractTableModel::flags (index) |
        Qt::ItemIsDragEnabled |
        Qt::ItemIsEnabled |
        Qt::ItemIsSelectable |
        Qt::ItemIsEditable;

  } else {

    // Root item
    return QAbstractTableModel::flags (index) |
        Qt::ItemIsDropEnabled;

  }
}

bool CurveNameList::insertRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
  bool skip = (count != 1 || row < 0 || row > rowCount () || parent.isValid());

  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::insertRows"
                              << " row=" << row
                              << " count=" << count
                              << " isRoot=" << (parent.isValid () ? "no" : "yes")
                              << " skip=" << (skip ? "yes" : "no");

  if (skip) {

    // Parent should be root item which is not valid
    return false;
  }

  beginInsertRows (QModelIndex (),
                   row,
                   row + count - 1);

  CurveNameListEntry emptyCurvesEntry;

  m_modelCurvesEntries.insert (row,
                               emptyCurvesEntry.toString ());

  endInsertRows ();

  return true;
}

bool CurveNameList::removeRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
  bool skip = (count != 1 || row < 0 || row > rowCount () || parent.isValid());

  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::removeRows"
                               << " row=" << row
                               << " count=" << count
                               << " isRoot=" << (parent.isValid () ? "no" : "yes")
                               << " skip=" << (skip ? "yes" : "no");

  bool success = false;

  beginRemoveRows (QModelIndex (),
                   row,
                   row + count - 1);

  m_modelCurvesEntries.removeAt (row);

  endRemoveRows ();

  return success;
}

int CurveNameList::rowCount (const QModelIndex & /* parent */) const
{
  int count = m_modelCurvesEntries.count ();

  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::rowCount count=" << count;

  return count;
}

bool CurveNameList::setData (const QModelIndex &index,
                             const QVariant &value,
                             int role)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::setData"
                              << " indexRow=" << index.row ()
                              << " value=" << (value.isValid () ? "valid" : "invalid")
                              << " role=" << roleAsString (role).toLatin1 ().data ();

  bool success = false;

  int row = index.row ();
  if (row < m_modelCurvesEntries.count ()) {

    success = true; // This method will be successful except in the rare case when a curve name is a duplicate

    if (!value.isValid () && (role == Qt::EditRole)) {

      // Remove the entry
      m_modelCurvesEntries.removeAt (row);

    } else {

      // Modify the entry
      CurveNameListEntry curvesEntry (m_modelCurvesEntries [row]); // Retrieve entry

      if (index.column () == 0) {
        curvesEntry.setCurveNameCurrent (value.toString ());
        success = curveNameIsAcceptable (value.toString (),
                                         row);
      } else if (index.column () == 1) {
        curvesEntry.setCurveNameOriginal (value.toString ());
      } else if (index.column () == 2) {
        curvesEntry.setNumPoints (value.toInt ());
      } else {
        ENGAUGE_ASSERT (false);
      }

      if (success) {
        m_modelCurvesEntries [row] = curvesEntry.toString (); // Save update entry
      }
    }

    if (success) {
      emit dataChanged (index,
                        index);
    }
  }

  return success;
}

Qt::DropActions CurveNameList::supportedDropActions () const
{
  return Qt::MoveAction;
}
