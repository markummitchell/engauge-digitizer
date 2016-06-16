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

const QString PIPE ("|");
const QString SPACE (" ");
const QString TAB ("\t");

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
  if (index.isValid ()) {

    // Not root item. ItemIsDropEnabled is unwanted during dragging since dragged entry would overwrite
    // another entry if user forgets to drop into the space between successive entries
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

QModelIndex CurveNameList::indexForValue (const QModelIndex &indexToSkip,
                                          const QVariant &value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::indexForValue";

  for (int row = 0; row < rowCount(); row++) {

    QModelIndex indexSearch = index (row, 0);

    if (indexToSkip != indexSearch) {

      if (data (indexSearch) == value) {

        return indexSearch;

      }
    }
  }

  QModelIndex invalid;
  return invalid;
}

bool CurveNameList::insertRows (int row,
                                int count,
                                const QModelIndex &parent)
{
  bool skip = (count != 1 || row < 0 || row > rowCount () || parent.isValid());

  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::insertRows"
                              << " row=" << row
                              << " count=" << count
                              << " parentRow=" << parent.row()
                              << " parentCol=" << parent.column()
                              << " isRoot=" << (parent.isValid () ? "no" : "yes")
                              << " skip=" << (skip ? "yes" : "no");

  if (skip) {

    // Comments:
    // 1) Row=-1 means the drag is AFTER the last entry. Although this method can deal with that easily by treating it
    //    as a drag to row=rowCount(), the later call to setData will fail since the row gets set to 0 (which is ambiguous
    //    with a drag to the 0th entry)
    // 2) Valid parent means we are not adding to the root node, which is what we want to do
    return false;
  }

  QString before = m_modelCurvesEntries.join (PIPE).replace (TAB, SPACE);

  beginInsertRows (QModelIndex (),
                   row,
                   row + count - 1);

  CurveNameListEntry emptyCurvesEntry;

  m_modelCurvesEntries.insert (row,
                               emptyCurvesEntry.toString ());

  endInsertRows ();

  QString after = m_modelCurvesEntries.join (PIPE).replace (TAB, SPACE);

  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::insertRows"
                              << " before=" << before.toLatin1().data()
                              << " after=" << after.toLatin1().data();

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

bool CurveNameList::rowIsUnpopulated (int row) const
{
  // Special case - in a drag to the white space after the last entry (and NOT to the legal drop line just after
  //                the last entry), our insertRows method has already rejected the insert. In this case, at this
  //                point row=0 so we need to check if variable 'row' points to an empty entry (empty+empty+0) or
  //                to a fully-populated entry (nonempty+maybeEmpty+number)
  QString fields = m_modelCurvesEntries.at (row);
  CurveNameListEntry entryAtRow (fields);
  return entryAtRow.entryHasNotBeenPopulated ();
}

bool CurveNameList::setData (const QModelIndex &index,
                             const QVariant &value,
                             int role)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::setData"
                              << " indexRow=" << index.row ()
                              << " indexCol=" << index.column ()
                              << " indexValid=" << (index.isValid() ? "valid" : "invalid")
                              << " valueValid=" << (value.isValid () ? "valid" : "invalid")
                              << " value=" << value.toString().toLatin1().data()
                              << " role=" << roleAsString (role).toLatin1 ().data ();

  bool success = false;

  if (index.isValid()) {

    // Process the new entry
    int row = index.row ();
    if (row < m_modelCurvesEntries.count ()) {

      // Variable 'row' points to an empty entry (created by insertRows) so we populate it here
      success = true;

      QString before = m_modelCurvesEntries.join (PIPE).replace (TAB, SPACE);

      if (!value.isValid () && (role == Qt::EditRole)) {

        // Remove the entry
        m_modelCurvesEntries.removeAt (row);

      } else {

        // Modify the entry
        CurveNameListEntry curvesEntry (m_modelCurvesEntries [row]); // Retrieve entry

        if (index.column () == 0) {

          if (role == Qt::EditRole) {

            // Does new curve name meet the requirements
            if (curveNameIsAcceptable (value.toString (),
                                       row)) {

              curvesEntry.setCurveNameCurrent (value.toString ());
              m_modelCurvesEntries [row] = curvesEntry.toString (); // Save update entry

            } else {

              success = false;
            }

          } else if ((role == Qt::DisplayRole) ||
                     (curveNameIsAcceptable (value.toString(),
                                             row))) {

            // Above we skipped curve name uniqueness check for Qt::DisplayRole since that role is used when dragging
            // curve from one place to another, since for a short time the new curve name will coexist
            // with the old curve name (until the old entry is removed)

            if (rowIsUnpopulated (row)) {
              success = true;
              curvesEntry.setCurveNameCurrent (value.toString ());
              curvesEntry.setNumPoints (0);
              m_modelCurvesEntries [row] = curvesEntry.toString (); // Save update entry
              tryToRemoveOriginalCopy (index,
                                       value,
                                       role);
            } else {
              success = false;
            }
          }
        } else if (index.column () == 1) {
          curvesEntry.setCurveNameOriginal (value.toString ());
          m_modelCurvesEntries [row] = curvesEntry.toString (); // Save update entry
        } else if (index.column () == 2) {
          curvesEntry.setNumPoints (value.toInt ());
          m_modelCurvesEntries [row] = curvesEntry.toString (); // Save update entry
        } else {
          ENGAUGE_ASSERT (false);
        }

        if (success) {
          emit dataChanged (index,
                            index);
        }

        QString after = m_modelCurvesEntries.join (PIPE).replace (TAB, SPACE);

        LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::setData setting"
                                    << " before=" << before.toLatin1().data()
                                    << " after=" << after.toLatin1().data();

      }
    }
  }

  return success;
}

Qt::DropActions CurveNameList::supportedDropActions () const
{
  return Qt::MoveAction;
}

void CurveNameList::tryToRemoveOriginalCopy (const QModelIndex &index,
                                             const QVariant &value,
                                             int role)
{
  // After the copy part of a move maneuver, the old entry must be identified and removed
  if (index.column () == 0 && role == Qt::DisplayRole) {
    QModelIndex indexToRemove = indexForValue (index,
                                               value); // Returns Invalid if no duplicate entry was found
    if (indexToRemove.isValid()) {

      QString before = m_modelCurvesEntries.join (PIPE).replace (TAB, SPACE);

      beginRemoveRows (QModelIndex (),
                       indexToRemove.row(),
                   indexToRemove.row());
      m_modelCurvesEntries.removeAt (indexToRemove.row ());
      endRemoveRows ();

      emit dataChanged (indexToRemove,
                        indexToRemove);

      QString after = m_modelCurvesEntries.join (PIPE).replace (TAB, SPACE);

      LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::setData removed"
                                  << " indexRow=" << indexToRemove.row ()
                                  << " indexCol=" << indexToRemove.column ()
                                  << " before=" << before.toLatin1().data()
                                  << " after=" << after.toLatin1().data();
    }
  }
}
