/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURVE_NAME_LIST_H
#define CURVE_NAME_LIST_H

#include <QHash>
#include <QStandardItemModel>
#include <QString>
#include <QVector>

// Data associated with the current curve names in the QStandardItemModel
typedef QHash<QString, QString> CurrentCurveToOriginalCurve;
typedef QHash<QString, unsigned int> OriginalCurveToPointCount;

// There is only one column, which is visible
enum CurveNameListColumns {
  CURVE_NAME_LIST_COLUMN_CURRENT,
  NUMBER_CURVE_NAME_LIST_COLUMNS
};

/// Model for DlgSettingsCurveAddRemove and CmdSettingsCurveAddRemove. This is displayed as a QListView, with visible first column
/// showing current curve name. Second column is hidden with curve name at the start of editing, or empty if none.
class CurveNameList : public QStandardItemModel
{
public:
  /// Default constructor.
  CurveNameList();

  /// One column
  virtual int columnCount (const QModelIndex &parent) const;

  /// Return true if specified curve name is already in the list.
  bool containsCurveNameCurrent (const QString &curveName) const;

  /// For debugging we dump the curve names
  QString currentCurvesAsString () const;

  /// Return the original curve for the specified current curve
  QString currentCurveToOriginalCurve (const QString &currentCurve) const;

  /// Return the point count for the specified current curve
  unsigned int currentCurveToPointCount (const QString &currentCurve) const;

  /// Override normal flags with additional editing flags.
  virtual Qt::ItemFlags flags (const QModelIndex &index) const;

  /// Create a new entry at the specified row
  void insertRow (int row,
                  const QString &curveCurrent,
                  const QString &curveOriginal,
                  unsigned int pointCount);

  /// Retrieve data from model
  virtual QStandardItem *item(int row, int column = 0) const;

  /// Return the number of points associated with the selected curves, as specified by their row numbers
  unsigned int numPointsForSelectedCurves (const QList<unsigned int> &rowsSelected) const;

  /// Remove one row.
  virtual bool removeRows (int row, int count, const QModelIndex &parent);

  /// Clear all information
  void reset ();

  /// One row per curve name.
  virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;

  /// Store data for one curve name
  virtual bool setData (const QModelIndex &index,
                        const QVariant &value,
                        int role);

  /// Store one curve name data.
  virtual void setItem(int row, int column, QStandardItem *item);

  /// Allow dragging for reordering.
  virtual Qt::DropActions supportedDropActions () const;

private:

  /// Ensure curve names are never duplicated or else nasty bugs will appear when duplicates occur. Also prevent empty curve names
  bool curveNameIsAcceptable (const QString &curveNameNew,
                              int row) const;

  // Data from original curves
  CurrentCurveToOriginalCurve m_currentCurveToOriginalCurve;
  OriginalCurveToPointCount m_originalCurveToPointCount;
};

#endif // CURVE_NAME_LIST_H
