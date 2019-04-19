/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveNameList.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <qdebug.h>
#include <QHash>
#include <QTextStream>
#include "QtToString.h"
#include <QVariant>
#include <QXmlStreamWriter>

CurveNameList::CurveNameList() :
  QStandardItemModel()
{
}

int CurveNameList::columnCount (const QModelIndex &  /* parent */) const
{
  return NUMBER_CURVE_NAME_LIST_COLUMNS;
}

bool CurveNameList::containsCurveNameCurrent (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::containsCurveNameCurrent";

  // Search for curve with matching name
  CurrentCurveToOriginalCurve::const_iterator itr;
  for (itr = m_currentCurveToOriginalCurve.begin (); itr != m_currentCurveToOriginalCurve.end (); ++itr) {

    if (itr.key () == curveName) {
      return true;
    }
  }

  return false;
}

QString CurveNameList::currentCurvesAsString () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::currentCurvesAsString";

  QString out;
  QTextStream str (&out);

  for (int row = 0; row < rowCount (); row++) {

    QString curveCurrent = data (index (row, CURVE_NAME_LIST_COLUMN_CURRENT)).toString ();
    QString curveOriginal;
    unsigned int points = 0;
    if (m_currentCurveToOriginalCurve.contains (curveCurrent)) {
      curveOriginal = m_currentCurveToOriginalCurve [curveCurrent];
      if (m_originalCurveToPointCount.contains (curveOriginal)) {

        points = m_originalCurveToPointCount [curveOriginal];
      }
    }

    str << "\n   current=" << curveCurrent.toLatin1().data()
        << " original=" << curveOriginal
        << " points=" << points;
  }

  return out;
}

QString CurveNameList::currentCurveToOriginalCurve (const QString &currentCurve) const
{
  return m_currentCurveToOriginalCurve [currentCurve];
}

unsigned int CurveNameList::currentCurveToPointCount (const QString &currentCurve) const
{
  QString originalCurve = m_currentCurveToOriginalCurve [currentCurve];

  return m_originalCurveToPointCount [originalCurve];
}

bool CurveNameList::curveNameIsAcceptable (const QString &curveNameNew,
                                           int row) const
{
  // First test is to verify curve name is not empty
  bool success = (!curveNameNew.isEmpty ());

  if (success) {

    // First test was passed. Second test is to check for duplication
    for (int row1 = 0; row1 < rowCount(); row1++) {

      // Use table entry except for the one row that gets overridden
      QModelIndex index1 = index (row1, CURVE_NAME_LIST_COLUMN_CURRENT);
      QString curveNameCurrent1 = (row1 == row ?
                                   curveNameNew :
                                   data (index1).toString ());

      for (int row2 = row1 + 1; row2 < rowCount(); row2++) {

        // Use table entry except for the one row that gets overridden
        QModelIndex index2 = index (row2, CURVE_NAME_LIST_COLUMN_CURRENT);
        QString curveNameCurrent2 = (row2 == row ?
                                     curveNameNew :
                                     data (index2).toString ());

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

Qt::ItemFlags CurveNameList::flags (const QModelIndex &index) const
{
  if (index.isValid ()) {

    // Not root item. ItemIsDropEnabled is unwanted during dragging since dragged entry would overwrite
    // another entry if user forgets to drop into the space between successive entries
    return (QStandardItemModel::flags (index) |
        Qt::ItemIsDragEnabled |
        Qt::ItemIsEnabled |
        Qt::ItemIsSelectable |
        Qt::ItemIsEditable) & ~Qt::ItemIsDropEnabled;

  } else {

    // Root item
    return QStandardItemModel::flags (index) |
        Qt::ItemIsDropEnabled;

  }
}

void CurveNameList::insertRow (int row,
                               const QString &curveCurrent,
                               const QString &curveOriginal,
                               unsigned int pointCount)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::insertRow"
                               << " row=" <<row
                               << " curveCurrent=" << curveCurrent.toLatin1().data()
                               << " curveOriginal=" << curveOriginal.toLatin1().data()
                               << " points=" << pointCount;

  QStandardItem *item = new QStandardItem (curveCurrent);
  QStandardItemModel::insertRow (row, item);

  // Documentation for QAbstractItemModels says beginInsertRows/endInsertRows send off a rowsAboutToBeInserted signal
  beginInsertRows (QModelIndex (),
                   row,
                   row);

  m_currentCurveToOriginalCurve [curveCurrent] = curveOriginal;
  m_originalCurveToPointCount [curveOriginal] = pointCount;

  endInsertRows ();
}

QStandardItem *CurveNameList::item(int row, int column) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::item"
                               << " row=" << row;

  ENGAUGE_ASSERT (row < rowCount ());

  return QStandardItemModel::item (row, column);
}

unsigned int CurveNameList::numPointsForSelectedCurves (const QList<unsigned int> &rowsSelected) const
{
  int numPoints = 0;
  for (int i = 0; i < rowsSelected.count(); i++) {
    int row = signed (rowsSelected [i]);

    QModelIndex idx = index (row, CURVE_NAME_LIST_COLUMN_CURRENT);
    QString currentCurve = data (idx).toString ();
    if (m_currentCurveToOriginalCurve.contains (currentCurve)) {

      QString originalCurve = m_currentCurveToOriginalCurve [currentCurve];
      if (m_originalCurveToPointCount.contains (originalCurve)) {

        numPoints += m_originalCurveToPointCount [originalCurve];
      }
    }
  }

  return unsigned (numPoints);
}

bool CurveNameList::removeRows (int row,
                                int count,
                                const QModelIndex &parent)
{
  // LOG4CPP is below

  bool skip = (count != 1 || row < 0 || row > rowCount () || parent.isValid());

  QString before, after;
  if (!skip) {

    before = currentCurvesAsString ();

    // As documented for QAbstractItemModel, beginRemoveRows "emits the rowsAboutToBeRemoved() signal which connected views
    // (or proxies) must handle before the data is removed. Otherwise, the views may end up in an invalid state."
    beginRemoveRows (QModelIndex (),
                     row,
                     row + count - 1);

    // We do not call QStandardItemModel::removeRow or QAbstractItemModel::removeRow here since that leads to an infinite loop when it calls this method
    for (int rowRemove = row; rowRemove < row + count; rowRemove++) {
      QStandardItemModel::removeRows (row,
                                      count,
                                      parent);
    }

    endRemoveRows ();

    after = currentCurvesAsString ();
  }

  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::removeRows"
                               << " row=" << row
                               << " count=" << count
                               << " isRoot=" << (parent.isValid () ? "no" : "yes")
                               << " skip=" << (skip ? "yes" : "no")
                               << " before=" << before.toLatin1().data()
                               << " after=" << after.toLatin1().data();
  return true;
}

void CurveNameList::reset()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveNameList::reset";

  clear();
  m_currentCurveToOriginalCurve.clear();
  m_originalCurveToPointCount.clear();
}

int CurveNameList::rowCount (const QModelIndex & /* parent */) const
{
  int count = QStandardItemModel::rowCount ();

//  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::rowCount"
//                               << " count=" << count;

  return count;
}

bool CurveNameList::setData (const QModelIndex &index,
                             const QVariant &value,
                             int role)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::setData"
                               << " row=" << index.row()
                               << " value=" << value.toString().toLatin1().data()
                               << " role=" << roleAsString (role).toLatin1().data();

  bool success;
  if (role == Qt::EditRole) {

    // Each curve name must be unique
    if (curveNameIsAcceptable (value.toString(),
                               index.row())) {

      // Curve name is fine
      QModelIndex idxOld = QStandardItemModel::index (index.row(), CURVE_NAME_LIST_COLUMN_CURRENT);

      // Old and new curve names
      QString curveCurrentOld = data (idxOld).toString ();
      QString curveCurrentNew = value.toString ();

      // Remove old entry after saving original curve name
      QString curveOriginal;
      if (m_currentCurveToOriginalCurve.contains (curveCurrentOld)) {

        // Remember old original curve name
        curveOriginal = m_currentCurveToOriginalCurve [curveCurrentOld];

        // Remove old entry
        m_currentCurveToOriginalCurve.remove (curveCurrentOld);

        // Add new entry
        m_currentCurveToOriginalCurve [curveCurrentNew] = curveOriginal;
      }

      success = QStandardItemModel::setData (index,
                                             value,
                                             role);
    } else {

      // Curve name is unacceptable
      success = false;

    }
  } else {

    // For non-edits, this method just calls the superclass method
    success = QStandardItemModel::setData (index,
                                           value,
                                           role);
  }

  return success;
}

void CurveNameList::setItem(int row,
                            int column,
                            QStandardItem *item)
{
  // LOG4CPP is below

  ENGAUGE_ASSERT (column == CURVE_NAME_LIST_COLUMN_CURRENT);

  QString before = currentCurvesAsString ();

  QStandardItemModel::setItem (row,
                               column,
                               item);

  QString after = currentCurvesAsString ();

  LOG4CPP_DEBUG_S ((*mainCat)) << "CurveNameList::setItem"
                               << " row=" << row
                               << " before=" << before.toLatin1().data()
                               << " after=" << after.toLatin1().data();
}

Qt::DropActions CurveNameList::supportedDropActions () const
{
  return Qt::MoveAction;
}
