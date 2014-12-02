#include "DocumentModelCurvesEntry.h"
#include "DocumentModelCurves.h"
#include "Logger.h"
#include "QtToString.h"
#include <QVariant>
#include <QXmlStreamWriter>

DocumentModelCurves::DocumentModelCurves()
{
}

int DocumentModelCurves::columnCount (const QModelIndex & /* parent */) const
{
  return 3;
}

bool DocumentModelCurves::containsCurveNameCurrent (const QString &curveName) const
{
  QStringList::const_iterator itr;
  for (itr = m_modelCurvesEntries.begin (); itr != m_modelCurvesEntries.end (); itr++) {

    DocumentModelCurvesEntry curvesEntry (*itr);
    if (curveName == curvesEntry.curveNameCurrent()) {

      return true;
    }
  }

  return false;
}

QVariant DocumentModelCurves::data (const QModelIndex &index,
                               int role) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DocumentModelCurves::data"
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

  DocumentModelCurvesEntry curvesEntry (m_modelCurvesEntries.at (row));

  if (index.column () == 0) {
    return curvesEntry.curveNameCurrent();
  } else if (index.column () == 1) {
    return curvesEntry.curveNameOriginal();
  } else if (index.column () == 2) {
    return curvesEntry.numPoints ();
  } else {
    Q_ASSERT (false);
  }
}


Qt::ItemFlags DocumentModelCurves::flags (const QModelIndex &index) const
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

bool DocumentModelCurves::insertRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
  bool skip = (count != 1 || row < 0 || row > rowCount () || parent.isValid());

  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCurves::insertRows"
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

  DocumentModelCurvesEntry emptyCurvesEntry;

  m_modelCurvesEntries.insert (row,
                              emptyCurvesEntry.toString ());

  endInsertRows ();

  return true;
}

bool DocumentModelCurves::removeRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
  bool skip = (count != 1 || row < 0 || row > rowCount () || parent.isValid());

  LOG4CPP_DEBUG_S ((*mainCat)) << "DocumentModelCurves::removeRows"
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

int DocumentModelCurves::rowCount (const QModelIndex & /* parent */) const
{
  int count = m_modelCurvesEntries.count ();

  LOG4CPP_DEBUG_S ((*mainCat)) << "DocumentModelCurves::rowCount count=" << count;

  return count;
}

void DocumentModelCurves::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCurves::saveModel";

  stream.writeStartElement("DocumentModelCurves");
  stream.writeEndElement();
}

bool DocumentModelCurves::setData (const QModelIndex &index,
                              const QVariant &value,
                              int role)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCurves::setData"
                              << " indexRow=" << index.row ()
                              << " value=" << (value.isValid () ? "valid" : "invalid")
                              << " role=" << roleAsString (role).toLatin1 ().data ();

  bool success = false;

  int row = index.row ();
  if (row < m_modelCurvesEntries.count ()) {

    if (!value.isValid () && (role == Qt::EditRole)) {

      // Remove the entry
      m_modelCurvesEntries.removeAt (row);

    } else {

      // Modify the entry
      DocumentModelCurvesEntry curvesEntry (m_modelCurvesEntries [row]); // Retrieve entry

      if (index.column () == 0) {
        curvesEntry.setCurveNameCurrent (value.toString ());
      } else if (index.column () == 1) {
        curvesEntry.setCurveNameOriginal (value.toString ());
      } else if (index.column () == 2) {
        curvesEntry.setNumPoints (value.toInt ());
      } else {
        Q_ASSERT (false);
      }

      m_modelCurvesEntries [row] = curvesEntry.toString (); // Save update entry
    }

    emit dataChanged (index,
                      index);

    success = true;
  }

  return success;
}

Qt::DropActions DocumentModelCurves::supportedDropActions () const
{
  return Qt::MoveAction;
}
